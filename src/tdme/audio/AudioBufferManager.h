// Generated from /tdme/src/tdme/audio/AudioBufferManager.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::audio::AudioBufferManager_AudioBufferManaged;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * Audio buffer manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::AudioBufferManager final
	: public Object
{

public:
	typedef Object super;

private:
	_HashMap* audioBuffers {  };
protected:

	/** 
	 * Protected constructor
	 */
	void ctor();

public: /* protected */

	/** 
	 * Adds a audio buffer to manager / open al stack
	 * @param id
	 * @param int audio buffer al id
	 * @return audio buffer managed
	 */
	AudioBufferManager_AudioBufferManaged* addAudioBuffer(String* id);

	/** 
	 * Removes a texture from manager / open gl stack
	 * @param id
	 * @return true if caller has to remove the audio buffer from open AL
	 */
	bool removeAudioBuffer(String* id);

	// Generated
	AudioBufferManager();
protected:
	AudioBufferManager(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class AudioBufferManager_AudioBufferManaged;
};
