#include "audio_decoder.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include <QDebug>

AudioDecoder::AudioDecoder(QObject *parent) : QObject(parent)
{
}

QByteArray AudioDecoder::decodeFile(const QByteArray &fileData, QAudioFormat &format)
{
    ma_decoder_config config = ma_decoder_config_init(ma_format_f32, 0, 0);
    ma_decoder decoder;

    ma_result result = ma_decoder_init_memory(fileData.constData(), fileData.size(), &config, &decoder);
    if (result != MA_SUCCESS) {
        qWarning() << "Failed to open and decode file from memory";
        return QByteArray();
    }

    format.setSampleRate(decoder.outputSampleRate);
    format.setChannelCount(decoder.outputChannels);
    format.setSampleFormat(QAudioFormat::Float);

    ma_uint64 pcmFrameCount = 0;
    ma_decoder_get_length_in_pcm_frames(&decoder, &pcmFrameCount);

    QByteArray byteArray(pcmFrameCount * decoder.outputChannels * sizeof(float), 0);

    ma_uint64 framesRead = 0;
    ma_decoder_read_pcm_frames(&decoder, byteArray.data(), pcmFrameCount, &framesRead);

    ma_decoder_uninit(&decoder);

    return byteArray;
}