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
 * @version $Id$
 */
class tdme::audio::decoder::AudioDecoder
{
public:
	static constexpr int8_t CHANNELS_NONE { -1 };
	static constexpr int32_t SAMPLERATE_NONE { -1 };
	static constexpr int8_t BITSPERSAMPLES_NONE { -1 };
	static constexpr int64_t SAMPLES_NONE { -1 };

protected:
	int8_t channels { CHANNELS_NONE };
	int32_t sampleRate { SAMPLERATE_NONE };
	int8_t bitsPerSample { BITSPERSAMPLES_NONE };
	int64_t samples { SAMPLES_NONE };

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
	 * @return number of channels or CHANNELS_NONE
	 */
	inline int8_t getChannels() {
		return channels;
	}

	/**
	 * @return sample rate in hz or SAMPLERATE_NONE
	 */
	inline int32_t getSampleRate() {
		return sampleRate;
	}

	/**
	 * @return bits per sample or BITSPERSAMPLES_NONE
	 */
	inline int8_t getBitsPerSample() {
		return bitsPerSample;
	}

	/**
	 * @return samples or SAMPLES_NONE
	 */
	inline int64_t getSamples() {
		return samples;
	}

	/**
	 * Read raw PCM data from stream
	 * @param data byte buffer
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::audio::decoder::AudioDecoderException
	 * @return number of bytes read
	 */
	virtual int32_t readFromStream(ByteBuffer* data) = 0;

	/**
	 * Closes the audio file
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::audio::decoder::AudioDecoderException
	 */
	virtual void close() = 0;

	/**
	 * Constructor
	 */
	inline AudioDecoder() {}

	/**
	 * Destructor
	 */
	inline virtual ~AudioDecoder() {}
};
