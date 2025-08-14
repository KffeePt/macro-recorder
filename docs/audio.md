# Audio Module

The Audio module is responsible for all audio-related functionalities within the application. Its primary purpose is to provide auditory feedback to the user, for example, by playing sounds when recording or playback starts and stops.

## Files

*   `audio_decoder.h` / `audio_decoder.cpp`: Decodes audio files to be played.
*   `miniaudio.h`: A third-party library for audio playback.

## Key Classes

### `AudioDecoder`

The `AudioDecoder` class is a crucial component of the audio module. It's responsible for taking compressed audio files (like MP3s) and converting them into a raw PCM format that can be played by Qt's multimedia framework. This is necessary because Qt's `QSoundEffect` class requires uncompressed audio data. The decoding process is handled by the excellent `miniaudio` library, which is a single-header, cross-platform audio library.

#### Implementation Details
- The `decodeFile` method uses the `miniaudio` library to perform the decoding.
- It initializes a `ma_decoder` from the in-memory `fileData` using `ma_decoder_init_memory`.
- It then retrieves the audio format details (sample rate, channels) from the decoder and sets them on the `QAudioFormat` object that was passed by reference.
- It reads the entire decoded audio data (as PCM frames) into a `QByteArray` and returns it.
- Finally, it uninitializes the decoder to free up resources.

**Public Methods:**
- `decodeFile(const QByteArray &fileData, QAudioFormat &format)`: This is the primary public method of the class. It takes the raw byte data of a compressed audio file and a reference to a `QAudioFormat` object. It decodes the audio data and returns it as a `QByteArray`, while also populating the `QAudioFormat` object with the necessary parameters like sample rate, channel count, and sample format. This format object is then used by the `MainWindow` to correctly configure the `QSoundEffect` for playback.