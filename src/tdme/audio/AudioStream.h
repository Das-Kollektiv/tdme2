#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/audio/decoder/fwd-tdme.h>
#include <tdme/audio/decoder/VorbisDecoder.h>
#include <tdme/audio/AudioEntity.h>

using std::array;
using std::string;

using tdme::audio::AudioEntity;
using tdme::utils::ByteBuffer;
using tdme::audio::decoder::AudioDecoder;
using tdme::audio::decoder::VorbisDecoder;

/** 
 * Audio Stream 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::AudioStream final
	: public AudioEntity
{
private:
	static constexpr int32_t BUFFER_COUNT { 3 };
	static constexpr int32_t BUFFER_SIZE { 32768 };
	bool initiated {  };
	string pathName {  };
	string fileName {  };
	array<uint32_t, BUFFER_COUNT> alBufferIds {  };
	uint32_t alSourceId {  };
	int32_t format {  };
	int32_t frequency {  };
	VorbisDecoder decoder;
	ByteBuffer* data {  };

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

	/**
	 * Protected constructor
	 * @param id
	 * @param path name
	 * @param file name
	 */
	AudioStream(const string& id, const string& pathName, const string& fileName);

	/**
	 * Destructor
	 */
	virtual ~AudioStream();
};
