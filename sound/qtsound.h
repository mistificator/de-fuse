#ifndef QTSOUND_HPP
#define QTSOUND_HPP

#include <QtMultimedia/QAudioOutput>

class AudioStream;

class QtSoundDevice: public QObject
{
    Q_OBJECT
public:
    QtSoundDevice(int samplerate, bool stereo);
    ~QtSoundDevice();

    void play(const QByteArray & samples);
    qint64 processed() const;
    qint64 written() const;
    bool isOk() const;
private slots:
    void handleStateChanged(QAudio::State newState);
private:
    QAudioOutput * audio = nullptr;
    AudioStream * stream = nullptr;
};

#endif // QTSOUND_HPP
