#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/audio/decoder/fwd-agui.h>
#include <agui/audio/decoder/AudioDecoderException.h>
#include <agui/os/filesystem/fwd-agui.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/utilities/fwd-agui.h>

using std::string;

// namespaces
namespace agui {
namespace audio {
	using ::agui::audio::decoder::AudioDecoderException;
	using ::agui::utilities::ByteBuffer;
}
}

/**
 * Audio decoder base class
 * @author Andreas Drewke
 */
class agui::audio::decoder::AudioDecoder
{
public:
	static constexpr uint8_t CHANNELS_NONE { 0 };
	static constexpr uint32_t SAMPLERATE_NONE { 0 };
	static constexpr uint8_t BITSPERSAMPLES_NONE { 0 };
	static constexpr uint64_t SAMPLES_NONE { 0 };

protected:
	uint8_t channels { CHANNELS_NONE };
	uint32_t sampleRate { SAMPLERATE_NONE };
	uint8_t bitsPerSample { BITSPERSAMPLES_NONE };
	uint64_t samples { SAMPLES_NONE };

	/**
	 * Constructor
	 */
	inline AudioDecoder() {}

	/**
	 * Destructor
	 */
	inline virtual ~AudioDecoder() {}

public:
	/**
	 * Open a local file
	 * @param pathName path name
	 * @param fileName file name
	 * @throws agui::os::filesystem::FileSystemException
	 * @throws agui::audio::decoder::AudioDecoderException
	 */
	virtual void openFile(const string& pathName, const string& fileName) = 0;

	/**
	 * Resets this audio decoder, if a stream was open it will be rewinded
	 * @throws agui::os::filesystem::FileSystemException
	 * @throws agui::audio::decoder::AudioDecoderException
	 */
	virtual void reset() = 0;

	/**
	 * @returns number of channels or CHANNELS_NONE
	 */
	inline uint8_t getChannels() const {
		return channels;
	}

	/**
	 * @returns sample rate in hz or SAMPLERATE_NONE
	 */
	inline uint32_t getSampleRate() const {
		return sampleRate;
	}

	/**
	 * @returns bits per sample or BITSPERSAMPLES_NONE
	 */
	inline uint8_t getBitsPerSample() const {
		return bitsPerSample;
	}

	/**
	 * @returns samples or SAMPLES_NONE
	 */
	inline uint64_t getSamples() const {
		return samples;
	}

	/**
	 * Read raw PCM data from stream
	 * @param data byte buffer
	 * @throws agui::os::filesystem::FileSystemException
	 * @throws agui::audio::decoder::AudioDecoderException
	 * @returns number of bytes read
	 */
	virtual int64_t readFromStream(ByteBuffer* data) = 0;

	/**
	 * Closes the audio file
	 * @throws agui::os::filesystem::FileSystemException
	 * @throws agui::audio::decoder::AudioDecoderException
	 */
	virtual void close() = 0;

};
