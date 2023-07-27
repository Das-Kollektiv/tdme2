#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/audio/AudioEntity.h>

using std::string;

using tdme::audio::AudioEntity;

/**
 * Sound audio entity implementation
 * @author Andreas Drewke
 */
class tdme::audio::Sound final
	: public AudioEntity
{
	friend class Audio;

private:
	bool initiated { false };
	string pathName;
	string fileName;
	string bufferId;
	uint32_t alBufferId { 0 };
	uint32_t alSourceId { 0 };

public:
	// forbid class copy
	CLASS_FORBID_COPY(Sound)

	/**
	 * Protected constructor
	 * @param id id
	 * @param pathName path name
	 * @param fileName file name
	 */
	inline Sound(const string& id, const string& pathName, const string& fileName) : AudioEntity(id) {
		this->bufferId = pathName + "/" + fileName;
		this->pathName = pathName;
		this->fileName = fileName;
	}

	// overridden methods
	bool isPlaying() override;
	void rewind() override;
	void play() override;
	void pause() override;
	void stop() override;

protected:
	// overridden methods
	bool initialize() override;
	void update() override;
	void dispose() override;
};
