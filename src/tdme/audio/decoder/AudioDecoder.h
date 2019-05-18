#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/decoder/fwd-tdme.h>
#include <tdme/audio/decoder/AudioDecoderException.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/utils/fwd-tdme.h>

using std::string;

using tdme::audio::decoder::AudioDecoderException;
using tdme::os::filesystem::FileSystemException;
using tdme::utils::ByteBuffer;

/** 
 * Audio decoder base class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::decoder::AudioDecoder
{
public:
	static constexpr int32_t CHANNELS_NONE { -1 };
	static constexpr int32_t SAMPLERATE_NONE { -1 };
	static constexpr int32_t BITSPERSAMPLES_NONE { -1 };
	static constexpr int32_t SAMPLES_NONE { -1 };

protected:
	int32_t channels {  };
	int32_t sampleRate {  };
	int32_t bitsPerSample {  };
	int32_t samples { };

public:

	/** 
	 * Open a local file
	 * @param pathName path name
	 * @param fileName file name
	 */
	virtual void openFile(const string& pathName, const string& fileName) throw (FileSystemException, AudioDecoderException) = 0;

	/** 
	 * Resets this audio decoder, if a stream was open it will be rewinded
	 */
	virtual void reset() throw (FileSystemException, AudioDecoderException) = 0;

	/** 
	 * @return number of channels or CHANNELS_NONE
	 */
	virtual int32_t getChannels();

	/** 
	 * @return sample rate in hz or SAMPLERATE_NONE
	 */
	virtual int32_t getSampleRate();

	/** 
	 * @return bits per sample or BITSPERSAMPLES_NONE
	 */
	virtual int32_t getBitsPerSample();

	/** 
	 * @return samples or SAMPLES_NONE
	 */
	virtual int32_t getSamples();

	/**
	 * Read raw PCM data from stream 
	 * @param data byte buffer
	 * @return number of bytes read
	 */
	virtual int32_t readFromStream(ByteBuffer* data) throw (FileSystemException, AudioDecoderException) = 0;

	/** 
	 * Closes the audio file
	 */
	virtual void close() throw (FileSystemException, AudioDecoderException) = 0;

	/**
	 * Constructor
	 */
	AudioDecoder();
};
