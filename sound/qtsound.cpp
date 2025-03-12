
extern "C" {
    #include "config.h"
    #include "settings.h"
    #include "sound.h"

    typedef enum ui_error_level {

      UI_ERROR_INFO,		/* Informational message */
      UI_ERROR_WARNING,		/* Something is wrong, but it's not that
                       important */
      UI_ERROR_ERROR,		/* An actual error */

    } ui_error_level;
    int ui_error( ui_error_level severity, const char *format, ... );
}

#include "qtsound.hpp"
#include <QtMultimedia/QAudioFormat>

static QtSoundDevice * device = nullptr;

QtSoundDevice::QtSoundDevice(int samplerate, bool stereo): QObject()
{
    QAudioFormat format;
    format.setSampleRate(samplerate);
    format.setChannelCount(stereo ? 2 : 1);
    format.setSampleSize(settings_current.sound_force_8bit ? 8 : 16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format))
    {
        ui_error( UI_ERROR_ERROR, "Raw audio format not supported by backend, cannot play audio." );
        return;
    }

    audio = new QAudioOutput(format);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
}

QtSoundDevice::~QtSoundDevice()
{
    if (!audio)
    {
        ui_error( UI_ERROR_ERROR, "Couldn't stop audio." );
        return;
    }
    audio->stop();
    audio->deleteLater();
}

void QtSoundDevice::play(const QByteArray & samples)
{
    if (!audio)
        return;
    if (!stream)
        stream = audio->start();
    stream->write(samples);
}

bool QtSoundDevice::isOk() const
{
    return audio && audio->error() == QAudio::NoError;
}

void QtSoundDevice::handleStateChanged(QAudio::State newState)
{
    switch (newState)
    {
        case QAudio::IdleState:
            break;
        case QAudio::StoppedState:
            if (audio->error() != QAudio::NoError)
            {
                ui_error( UI_ERROR_ERROR, "Audio error" );
            }
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
    if (!device || !device->isOk())
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
}
