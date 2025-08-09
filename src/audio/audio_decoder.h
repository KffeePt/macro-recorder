#ifndef AUDIO_DECODER_H
#define AUDIO_DECODER_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QAudioFormat>

class AudioDecoder : public QObject
{
    Q_OBJECT
public:
    explicit AudioDecoder(QObject *parent = nullptr);

    QByteArray decodeFile(const QByteArray &fileData, QAudioFormat &format);
};

#endif // AUDIO_DECODER_H