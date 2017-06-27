// Generated from /tdme/src/tdme/audio/AudioBufferManager.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::audio::AudioBufferManager;


struct default_init_tag;

/** 
 * Managed audio buffer entity
 * @author Andreas Drewke
 */
class tdme::audio::AudioBufferManager_AudioBufferManaged
	: public virtual Object
{

public:
	typedef Object super;

public: /* package */
	String* id {  };
	int32_t alId {  };
	int32_t referenceCounter {  };
protected:

	/** 
	 * Protected constructor
	 * @param id
	 * @param Open AL id
	 * @param referenceCounter
	 */
	void ctor(String* id, int32_t alId);

public: /* protected */

	/** 
	 * @return audio buffer id
	 */
	virtual String* getId();

	/** 
	 * @return Open AL id
	 */
	virtual int32_t getAlId();

	/** 
	 * Set up Open AL audio buffer id
	 * @param al Id
	 */
	virtual void setAlId(int32_t alId);

	/** 
	 * @return reference counter
	 */
	virtual int32_t getReferenceCounter();

private:

	/** 
	 * decrement reference counter
	 * @return if reference counter = 0
	 */
	bool decrementReferenceCounter();

	/** 
	 * increment reference counter
	 */
	void incrementReferenceCounter();

	// Generated
	AudioBufferManager_AudioBufferManaged(AudioBufferManager *AudioBufferManager_this, String* id, int32_t alId);
protected:
	AudioBufferManager_AudioBufferManaged(AudioBufferManager *AudioBufferManager_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	AudioBufferManager *AudioBufferManager_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class AudioBufferManager;
};
