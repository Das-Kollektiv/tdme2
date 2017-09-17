// Generated from /tdme/src/tdme/audio/Sound.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/audio/AudioEntity.h>

using std::wstring;

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
	wstring pathName {  };
	wstring fileName {  };
	wstring bufferId {  };
	int32_t alBufferId {  };
	int32_t alSourceId {  };

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
	Sound(const wstring& id, const wstring& pathName, const wstring& fileName);
};
