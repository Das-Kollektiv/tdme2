// Generated from /tdme/src/tdme/audio/AudioStream.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/audio/decoder/fwd-tdme.h>
#include <tdme/audio/AudioEntity.h>

using tdme::audio::AudioEntity;
using java::lang::String;
using tdme::utils::ByteBuffer;
using tdme::audio::decoder::AudioDecoder;


struct default_init_tag;

/** 
 * Audio Stream 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::AudioStream final
	: public AudioEntity
{

public:
	typedef AudioEntity super;

private:
	static constexpr int32_t BUFFER_COUNT { 3 };
	static constexpr int32_t BUFFER_SIZE { 32768 };
	bool initiated {  };
	String* pathName {  };
	String* fileName {  };
	int32_tArray* alBufferIds {  };
	int32_t alSourceId {  };
	AudioDecoder* decoder {  };
	int32_t format {  };
	int32_t frequency {  };
	ByteBuffer* data {  };
protected:

	/** 
	 * Protected constructor
	 * @param id
	 * @param path name
	 * @param file name
	 */
	void ctor(String* id, String* pathName, String* fileName);

public:
	bool isPlaying() override;
	void rewind() override;
	void play() override;
	void pause() override;
	void stop() override;

public: /* protected */
	bool initialize() override;
	void update() override;

private:

	/** 
	 * Updates properties to Open AL
	 */
	void updateProperties();

public: /* protected */
	void dispose() override;

	// Generated
	AudioStream(String* id, String* pathName, String* fileName);
protected:
	AudioStream(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
