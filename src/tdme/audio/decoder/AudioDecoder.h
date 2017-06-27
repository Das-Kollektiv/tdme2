// Generated from /tdme/src/tdme/audio/decoder/AudioDecoder.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <tdme/audio/decoder/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using java::nio::ByteBuffer;


struct default_init_tag;

/** 
 * Audio decoder base class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::decoder::AudioDecoder
	: public virtual Object
{

public:
	typedef Object super;
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
	virtual void openFile(String* pathName, String* fileName) /* throws(IOException, AudioDecoderException) */ = 0;

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

	// Generated
	AudioDecoder();
protected:
	void ctor();
	AudioDecoder(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
