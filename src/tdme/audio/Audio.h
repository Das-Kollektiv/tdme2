// Generated from /tdme/src/tdme/audio/Audio.java

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/openal/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::openal::AL;
using java::lang::String;
using tdme::audio::AudioBufferManager;
using tdme::audio::AudioEntity;
using tdme::math::Vector3;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * Interface to TDME audio methods
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::Audio final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	static constexpr int32_t ALBUFFERID_NONE { -1 };
	static constexpr int32_t ALSOURCEID_NONE { -1 };
	static Audio* instance;

private:
	static _HashMap* audioEntities;

public: /* protected */
	AudioBufferManager* audioBufferManager {  };
	static AL* al;
	Vector3* listenerPosition {  };
	Vector3* listenerVelocity {  };
	Vector3* listenerOrientationAt {  };
	Vector3* listenerOrientationUp {  };

public:

	/** 
	 * @return audio singleton instance
	 */
	static Audio* getInstance();
protected:

	/** 
	 * Private constructor
	 */
	void ctor();

public:

	/** 
	 * @return listener position
	 */
	Vector3* getListenerPosition();

	/** 
	 * @return listener velocity
	 */
	Vector3* getListenerVelocity();

	/** 
	 * @return listener orientation at
	 */
	Vector3* getListenerOrientationAt();

	/** 
	 * @return listener orientation up
	 */
	Vector3* getListenerOrientationUp();

	/** 
	 * Returns an audio entity identified by given id
	 * @param id
	 * @return audio entity
	 */
	AudioEntity* getEntity(String* id);

	/** 
	 * Adds an stream
	 * the only format supported by now is ogg vorbis
	 * @param id
	 * @param path name
	 * @param file name
	 * @return audio entity
	 */
	AudioEntity* addStream(String* id, String* pathName, String* fileName);

	/** 
	 * Adds an sound
	 * the only format supported by now is ogg vorbis
	 * @param id
	 * @param path name
	 * @param file name
	 * @return audio entity
	 */
	AudioEntity* addSound(String* id, String* pathName, String* fileName);

	/** 
	 * Removes an audio entity
	 * @param id
	 */
	void removeEntity(String* id);

	/** 
	 * Clears all audio entities
	 */
	void reset();

	/** 
	 * Shuts the audio down
	 */
	void shutdown();

	/** 
	 * Update and transfer audio entity states to open AL
	 */
	void update();

	// Generated

private:
	Audio();
protected:
	Audio(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
