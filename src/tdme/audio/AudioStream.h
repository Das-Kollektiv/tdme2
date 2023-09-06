#pragma once

#include <array>
#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/audio/AudioEntity.h>
#include <tdme/utilities/ByteBuffer.h>

using std::array;
using std::string;
using std::unique_ptr;

using tdme::audio::AudioEntity;
using tdme::utilities::ByteBuffer;

/**
 * Audio stream
 * @author Andreas Drewke
 */
class tdme::audio::AudioStream
	: public AudioEntity
{
	friend class Audio;

private:
	bool initiated { false };
	array<uint32_t, 2> alBufferIds { 0, 0 };
	uint32_t alSourceId { 0 };
	uint32_t sampleRate { 0 };
	uint8_t channels { 0 };
	unique_ptr<ByteBuffer> data;
	int32_t format { 0 };
	bool playing { false };

protected:
	// forbid class copy
	FORBID_CLASS_COPY(AudioStream)

	/**
	 * Protected constructor
	 * @param id id
	 */
	inline AudioStream(const string& id): AudioEntity(id) {
		//
	}

	/**
	 * Destructor
	 */
	inline virtual ~AudioStream() {}

	// overridden methods
	virtual bool initialize() override;
	virtual void update() override;
	virtual void dispose() override;

	/**
	 * Fill buffer
	 * @param data data
	 */
	virtual void fillBuffer(ByteBuffer* data) = 0;

public:
	/**
	 * Set audio initialization parameters
	 * @param sampleRate sample rate
	 * @param channels channels
	 * @param bufferSize buffer size
	 */
	virtual void setParameters(uint32_t sampleRate, uint8_t channels, const int64_t bufferSize = 32768);

	// overridden methods
	virtual bool isPlaying() override;
	virtual void rewind() override;
	virtual void play() override;
	virtual void pause() override;
	virtual void stop() override;

private:
	/**
	 * @return having buffers that are currently played
	 */
	bool isPlayingBuffers();

	/**
	 * Updates properties to Open AL
	 */
	void updateProperties();

};
