// Generated from /tdme/src/tdme/audio/decoder/AudioDecoder.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/audio/decoder/fwd-tdme.h>

using std::wstring;

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

public: /* protected */
	int32_t channels {  };
	int32_t sampleRate {  };
	int32_t bitsPerSample {  };

public:

	/** 
	 * Open a local file
	 * @param path name
	 * @param file name
	 */
	virtual void openFile(const wstring& pathName, const wstring& fileName) /* throws(IOException, AudioDecoderException) */ = 0;

	/** 
	 * Resets this audio decoder, if a stream was open it will be rewinded
	 */
	virtual void reset() /* throws(IOException, AudioDecoderException) */ = 0;

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
	 * Read raw PCM data from stream 
	 * @param byte buffer
	 * @return number of bytes read
	 */
	virtual int32_t readFromStream(ByteBuffer* data) /* throws(IOException, AudioDecoderException) */ = 0;

	/** 
	 * Closes the audio file
	 */
	virtual void close() = 0;

	/**
	 * Constructor
	 */
	AudioDecoder();
};
