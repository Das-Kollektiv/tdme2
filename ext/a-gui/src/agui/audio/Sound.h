#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/audio/fwd-agui.h>
#include <agui/audio/AudioEntity.h>

using std::string;

/**
 * Sound audio entity implementation
 * @author Andreas Drewke
 */
class agui::audio::Sound final
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
	FORBID_CLASS_COPY(Sound)

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

	/**
	 * Destructor
	 */
	inline ~Sound() {
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
