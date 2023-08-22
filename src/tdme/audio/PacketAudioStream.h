#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/audio/AudioStream.h>

using std::string;
using std::vector;

using tdme::audio::AudioStream;
using tdme::utilities::ByteBuffer;

/**
 * Packet audio stream
 * @author Andreas Drewke
 */
class tdme::audio::PacketAudioStream final
	: public AudioStream
{
	friend class Audio;

private:
	bool initiated { false };
	vector<vector<uint8_t>> packets;
	int64_t position { 0LL };

public:
	// forbid class copy
	FORBID_CLASS_COPY(PacketAudioStream)

	/**
	 * Protected constructor
	 * @param id id
	 * @param pathName path name
	 * @param fileName file name
	 */
	inline PacketAudioStream(const string& id): AudioStream(id) {
	}

	/**
	 * Destructor
	 */
	inline ~PacketAudioStream() {
	}

	// overridden methods
	void rewind() override;

	/**
	 * Add audio packet
	 * @param byteBuffer byte buffer packet
	 */
	void addPacket(ByteBuffer* byteBuffer);
protected:
	// overridden methods
	bool initialize() override;
	void dispose() override;

	// overridden methods
	void fillBuffer(ByteBuffer* data) override;
};
