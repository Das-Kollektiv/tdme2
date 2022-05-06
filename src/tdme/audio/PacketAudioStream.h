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
	/**
	 * Protected constructor
	 * @param id id
	 * @param pathName path name
	 * @param fileName file name
	 */
	inline PacketAudioStream(const string& id): AudioStream(id) {
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

	/**
	 * Protected destructor
	 */
	inline virtual ~PacketAudioStream() {
	}

	// overridden methods
	void fillBuffer(ByteBuffer* data) override;
};
