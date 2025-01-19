#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/audio/decoder/VorbisDecoder.h>
#include <agui/audio/AudioStream.h>

using std::string;

// namespaces
namespace agui {
namespace audio {
	using ::agui::audio::decoder::VorbisDecoder;
	using ::agui::utilities::ByteBuffer;
}
}

/**
 * Vorbis audio stream
 * @author Andreas Drewke
 */
class agui::audio::VorbisAudioStream final
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
	FORBID_CLASS_COPY(VorbisAudioStream)

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

	/**
	 * Protected destructor
	 */
	inline ~VorbisAudioStream() {
	}

	// overridden methods
	void rewind() override;

protected:
	// overridden methods
	bool initialize() override;
	void dispose() override;

	// overridden methods
	void fillBuffer(ByteBuffer* data) override;
};
