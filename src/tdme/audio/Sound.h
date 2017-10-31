#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/audio/AudioEntity.h>

using std::string;

using tdme::audio::AudioEntity;

/** 
 * Simple sound implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::Sound final
	: public AudioEntity
{
private:
	bool initiated {  };
	string pathName {  };
	string fileName {  };
	string bufferId {  };
	uint32_t alBufferId {  };
	uint32_t alSourceId {  };

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

	/**
	 * Protected constructor
	 * @param id
	 * @param path name
	 * @param file name
	 */
	Sound(const string& id, const string& pathName, const string& fileName);
};
