#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/decoder/VorbisDecoder.h>
#include <tdme/audio/AudioStream.h>

using std::string;

using tdme::audio::decoder::VorbisDecoder;
using tdme::audio::AudioStream;
using tdme::utilities::ByteBuffer;

/**
 * Vorbis audio stream
 * @author Andreas Drewke
 */
class tdme::audio::VorbisAudioStream final
	: public AudioStream
{
	friend class Audio;

private:
	string pathName;
	string fileName;
	VorbisDecoder decoder;
	bool initiated { false };

public:
	// forbid class copy
	CLASS_FORBID_COPY(VorbisAudioStream)

	/**
	 * Protected constructor
	 * @param id id
	 * @param pathName path name
	 * @param fileName file name
	 */
	inline VorbisAudioStream(const string& id, const string& pathName, const string& fileName): AudioStream(id) {
		this->pathName = pathName;
		this->fileName = fileName;
	}

	// overridden methods
	void rewind() override;

protected:
	// overridden methods
	bool initialize() override;
	void dispose() override;

	/**
	 * Protected destructor
	 */
	inline virtual ~VorbisAudioStream() {
	}

	// overridden methods
	void fillBuffer(ByteBuffer* data) override;
};
