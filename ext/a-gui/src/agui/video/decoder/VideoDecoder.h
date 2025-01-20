#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/video/decoder/fwd-agui.h>

using std::string;

// namespaces
namespace agui {
namespace video {
namespace decoder {
	using ::agui::utilities::ByteBuffer;
}
}
}

/**
 * Video decoder base class
 * @author Andreas Drewke
 */
class agui::video::decoder::VideoDecoder
{
public:
	static constexpr uint8_t AUDIO_CHANNELS_NONE { 0 };
	static constexpr uint32_t AUDIO_SAMPLERATE_NONE { 0 };
	static constexpr uint8_t AUDIO_BITSPERSAMPLES_NONE { 0 };
	static constexpr uint64_t AUDIO_SAMPLES_NONE { 0 };

	static constexpr float VIDEO_FRAMERATE_NONE { 0.0f };
	static constexpr float VIDEO_DURATION_NONE { 0.0f };
	static constexpr uint16_t VIDEO_WIDTH_NONE { 0 };
	static constexpr uint16_t VIDEO_HEIGHT_NONE { 0 };

protected:
	uint8_t audioChannels { AUDIO_CHANNELS_NONE };
	uint32_t audioSampleRate { AUDIO_SAMPLERATE_NONE };
	uint8_t audioBitsPerSample { AUDIO_BITSPERSAMPLES_NONE };
	uint64_t audioSamples { AUDIO_SAMPLES_NONE };

	float videoFrameRate { VIDEO_FRAMERATE_NONE };
	float videoDuration { VIDEO_DURATION_NONE };
	uint16_t videoWidth { VIDEO_WIDTH_NONE };
	uint16_t videoHeight { VIDEO_WIDTH_NONE };

	// forbid class copy
	FORBID_CLASS_COPY(VideoDecoder)

	/**
	 * Constructor
	 */
	inline VideoDecoder() {}

	/**
	 * Destructor
	 */
	inline virtual ~VideoDecoder() {}

public:
	/**
	 * Open a local file
	 * @param pathName path name
	 * @param fileName file name
	 * @throws agui::video::decoder::VideoDecoderException
	 */
	virtual void openFile(const string& pathName, const string& fileName) = 0;

	/**
	 * Resets this video decoder, if a stream was open it will be rewinded
	 */
	virtual void reset() = 0;

	/**
	 * Update
	 * @param deltaTime delta time
	 */
	virtual void update(float deltaTime) = 0;

	/**
	 * Update
	 * @param deltaTime delta time
	 */
	virtual void seek(float time) = 0;

	/**
	 * @returns number of channels or AUDIO_CHANNELS_NONE
	 */
	inline uint8_t getAudioChannels() const {
		return audioChannels;
	}

	/**
	 * @returns sample rate in hz or AUDIO_SAMPLERATE_NONE
	 */
	inline uint32_t getAudioSampleRate() const {
		return audioSampleRate;
	}

	/**
	 * @returns bits per sample or AUDIO_BITSPERSAMPLES_NONE
	 */
	inline uint8_t getAudioBitsPerSample() const {
		return audioBitsPerSample;
	}

	/**
	 * @returns samples or AUDIO_SAMPLES_NONE
	 */
	inline int64_t getAudioSamples() {
		return audioSamples;
	}

	/**
	 * Read raw PCM data from stream
	 * @param data byte buffer
	 * @returns number of bytes read
	 */
	virtual int64_t readAudioFromStream(ByteBuffer* data) = 0;

	/**
	 * @returns video frame rate
	 */
	inline float getVideoFrameRate() const {
		return videoFrameRate;
	}

	/**
	 * @returns video duration
	 */
	inline float getVideoDuration() const {
		return videoDuration;
	}

	/**
	 * @returns video width
	 */
	inline uint16_t getVideoWidth() const {
		return videoWidth;
	}

	/**
	 * @returns video height
	 */
	inline uint16_t getVideoHeight() const {
		return videoHeight;
	}

	/**
	 * Read raw RGB video data from stream
	 * @param data byte buffer
	 * @returns number of bytes read
	 */
	virtual int64_t readVideoFromStream(ByteBuffer* data) = 0;

	/**
	 * Closes the audio file
	 * @throws agui::os::filesystem::FileSystemException
	 * @throws agui::audio::decoder::AudioDecoderException
	 */
	virtual void close() = 0;

};
