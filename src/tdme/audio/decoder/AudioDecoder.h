#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/decoder/fwd-tdme.h>
#include <tdme/audio/decoder/AudioDecoderException.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using tdme::audio::decoder::AudioDecoderException;
using tdme::os::filesystem::FileSystemException;
using tdme::utilities::ByteBuffer;

/**
 * Audio decoder base class
 * @author Andreas Drewke
 */
class tdme::audio::decoder::AudioDecoder
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
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::audio::decoder::AudioDecoderException
	 */
	virtual void openFile(const string& pathName, const string& fileName) = 0;

	/**
	 * Resets this audio decoder, if a stream was open it will be rewinded
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::audio::decoder::AudioDecoderException
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
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::audio::decoder::AudioDecoderException
	 * @returns number of bytes read
	 */
	virtual int64_t readFromStream(ByteBuffer* data) = 0;

	/**
	 * Closes the audio file
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::audio::decoder::AudioDecoderException
	 */
	virtual void close() = 0;

};
