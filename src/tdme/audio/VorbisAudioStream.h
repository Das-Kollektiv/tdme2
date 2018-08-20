#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/audio/decoder/VorbisDecoder.h>
#include <tdme/audio/AudioStream.h>

using std::array;
using std::string;

using tdme::audio::AudioStream;
using tdme::audio::decoder::VorbisDecoder;
using tdme::utils::ByteBuffer;

/** 
 * Vorbis Audio Stream
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::VorbisAudioStream final
	: public AudioStream
{
	friend class Audio;

private:
	string pathName {  };
	string fileName {  };
	VorbisDecoder decoder;
	bool initiated { false };

public:
	/**
	 * Protected constructor
	 * @param id id
	 * @param pathName path name
	 * @param fileName file name
	 */
	VorbisAudioStream(const string& id, const string& pathName, const string& fileName);

	// overriden methods
	void rewind() override;

protected:
	// overriden methods
	bool initialize() override;
	void dispose() override;

	/**
	 * Destructor
	 */
	virtual ~VorbisAudioStream();

	// overriden methods
	void fillBuffer(ByteBuffer* data) override;
};
