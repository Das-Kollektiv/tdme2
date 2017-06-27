// Generated from /tdme/src/tdme/audio/Sound.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/audio/AudioEntity.h>

using tdme::audio::AudioEntity;
using java::lang::String;


struct default_init_tag;

/** 
 * Simple sound implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::Sound final
	: public AudioEntity
{

public:
	typedef AudioEntity super;

private:
	bool initiated {  };
	String* pathName {  };
	String* fileName {  };
	String* bufferId {  };
	int32_t alBufferId {  };
	int32_t alSourceId {  };
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
	void dispose() override;

	// Generated
	Sound(String* id, String* pathName, String* fileName);
protected:
	Sound(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
