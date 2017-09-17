// Generated from /tdme/src/tdme/audio/AudioEntity.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using std::wstring;

using tdme::math::Vector3;

/** 
 * Audio Entity Class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::AudioEntity
{
public: /* protected */
	wstring id {  };
	bool looping {  };
	bool fixed {  };
	float pitch {  };
	float gain {  };
	Vector3 sourcePosition {  };
	Vector3 sourceDirection {  };
	Vector3 sourceVelocity {  };

public:

	/** 
	 * @return id
	 */
	virtual const wstring& getId();

	/** 
	 * @return if sound will be looped
	 */
	virtual bool isLooping();

	/** 
	 * @return if sound will be looped
	 */
	virtual void setLooping(bool looping);

	/** 
	 * @return fixed, means the sound will always played no matter where the position and listener is located
	 */
	virtual bool isFixed();

	/** 
	 * Set this entity fixed, means the sound will always played no matter where the position and listener is located
	 * @param fixed
	 */
	virtual void setFixed(bool fixed);

	/** 
	 * @return pitch
	 */
	virtual float getPitch();

	/** 
	 * Set up pitch
	 * @param pitch
	 */
	virtual void setPitch(float pitch);

	/** 
	 * @return gain
	 */
	virtual float getGain();

	/** 
	 * Set up gain
	 * @param gain
	 */
	virtual void setGain(float gain);

	/** 
	 * @return source position
	 */
	virtual Vector3* getSourcePosition();

	/** 
	 * @return source direction
	 */
	virtual Vector3* getSourceDirection();

	/** 
	 * @return source velocity
	 */
	virtual Vector3* getSourceVelocity();

	/** 
	 * @return if stream is playing
	 */
	virtual bool isPlaying() = 0;

	/** 
	 * Rewinds this audio entity
	 */
	virtual void rewind() = 0;

	/** 
	 * Plays this audio entity
	 */
	virtual void play() = 0;

	/** 
	 * Pauses this audio entity
	 */
	virtual void pause() = 0;

	/** 
	 * Stops this audio entity
	 */
	virtual void stop() = 0;

public: /* protected */

	/** 
	 * Initiates this OpenAL entity to OpenAl
	 */
	virtual bool initialize() = 0;

	/** 
	 * Commits properties to OpenAl
	 */
	virtual void update() = 0;

	/** 
	 * Dispose this entity from OpenAL
	 */
	virtual void dispose() = 0;

	/**
	 * Constructor
	 */
	AudioEntity(const wstring& id);
};
