#ifndef QTSOUND_HPP
#define QTSOUND_HPP

#include <QtMultimedia/QAudioOutput>

class QtSoundDevice: public QObject
{
    Q_OBJECT
public:
    QtSoundDevice(int samplerate, bool stereo);
    ~QtSoundDevice();

    void play(const QByteArray & samples);
    bool isOk() const;
private slots:
    void handleStateChanged(QAudio::State newState);
private:
    QAudioOutput * audio = nullptr;
    QIODevice * stream = nullptr;
};

#endif // QTSOUND_HPP
