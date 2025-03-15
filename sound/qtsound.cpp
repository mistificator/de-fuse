
extern "C" {
#ifdef HAVE_CONFIG
    #include "config.h"
#endif
    #include "settings.h"
    #include "sound.h"
}

#include "qtsound.hpp"
#include <QtMultimedia/QAudioFormat>
#include <QApplication>
#include <QDebug>

class AudioStream: public QIODevice
{
public:
    AudioStream(): QIODevice()
    {
        open(QIODevice::ReadWrite);
    }
    qint64 writePos() const { return write_pos; }
    qint64 readPos() const { return read_pos; }
protected:
    qint64 readData(char *data, qint64 maxSize) override final
    {
        const auto sz = qMin<qint64>(maxSize, buffer.count());
        memcpy(data, buffer.constData(), sz);
        buffer.remove(0, sz);
        read_pos += sz;
        return sz;
    }
    qint64 writeData(const char *data, qint64 maxSize) override final
    {
        buffer.append(data, maxSize);
        write_pos += maxSize;
        return maxSize;
    }
private:
    qint64 write_pos = 0;
    qint64 read_pos = 0;
    QByteArray buffer;
};

static QtSoundDevice * device = nullptr;

QtSoundDevice::QtSoundDevice(int samplerate, bool stereo): QObject()
{
    QAudioFormat format;
    format.setSampleRate(samplerate);
    format.setChannelCount(stereo ? 2 : 1);
    format.setSampleSize(settings_current.sound_force_8bit ? 8 : 16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format))
    {
        qCritical() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    audio = new QAudioOutput(format);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
}

QtSoundDevice::~QtSoundDevice()
{
    if (!audio)
    {
        qCritical() << "Couldn't stop audio.";
        return;
    }
    audio->stop();
    delete audio;
    delete stream;
}

void QtSoundDevice::play(const QByteArray & samples)
{
    if (!audio)
        return;
    if (!stream)
    {
        stream = new AudioStream();
        audio->start(stream);
    }
    stream->write(samples);
}

qint64 QtSoundDevice::processed() const
{
    if (!audio || !stream)
        return 0;
    return stream->readPos() / (audio->format().sampleSize() / 8);
}

qint64 QtSoundDevice::written() const
{
    if (!audio || !stream)
        return 0;
    return stream->writePos() / (audio->format().sampleSize() / 8);
}

bool QtSoundDevice::isOk() const
{
    return audio && audio->error() == QAudio::NoError;
}

void QtSoundDevice::handleStateChanged(QAudio::State newState)
{
    qDebug() << "QAudio::State" << newState;
    switch (newState)
    {
        case QAudio::IdleState:
            break;
        case QAudio::StoppedState:
            if (audio->error() != QAudio::NoError)
                qCritical() << "Audio error";
            delete stream;
            stream = nullptr;
            break;
        default:
            break;
    }
}

extern "C"
int sound_lowlevel_init( const char *, int *freqptr, int *stereoptr )
{
    sound_lowlevel_end();
    device = new QtSoundDevice(*freqptr, *stereoptr);
    return device->isOk() ? 0 : 1;
}

extern "C"
void sound_lowlevel_end( void )
{
    if (!device)
        return;
    delete device;
    device = nullptr;
}

extern "C"
void sound_lowlevel_frame( libspectrum_signed_word *data, int len )
{
    if (!device)
        return;

    QByteArray buf;
    if (!settings_current.sound_force_8bit)
        buf = QByteArray(reinterpret_cast<const char *>(data), len * sizeof(data[0]));
    else
    {
        buf.resize(len);
        for (int i = 0; i < len; ++i)
            buf[i] = data[i] / 256;
    }

    device->play(buf);

    while (device->written() - device->processed() > 0)
        qApp->processEvents();
}
