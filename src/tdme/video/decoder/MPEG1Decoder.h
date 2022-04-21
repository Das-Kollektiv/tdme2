#pragma once

#if !defined(PL_MPEG_IMPLEMENTATION)
	#include <ext/pl_mpeg/pl_mpeg.h>
#endif

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/video/decoder/fwd-tdme.h>
#include <tdme/video/decoder/VideoDecoder.h>

using std::string;
using std::vector;

using tdme::utilities::ByteBuffer;
using tdme::video::decoder::VideoDecoder;

/**
 * PL_MPEG/MPEG1 video decoder
 * @author Andreas Drewke
 */
class tdme::video::decoder::MPEG1Decoder: public VideoDecoder
{
public:
	/**
	 * Constructor
	 */
	inline MPEG1Decoder() {}

	/**
	 * Destructor
	 */
	inline virtual ~MPEG1Decoder() {
		close();
	}

	// overridden methods
	void openFile(const string& pathName, const string& fileName) override;
	void reset() override;
	void update(float deltaTime) override;
	void seek(float time) override;
	int64_t readAudioFromStream(ByteBuffer* data) override;
	int64_t readVideoFromStream(ByteBuffer* data) override;
	void close() override;

private:
	plm_t* plm { nullptr };
	ByteBuffer* videoBuffer { nullptr };
	ByteBuffer* audioBuffer { nullptr };

	/**
	 * PLM on video
	 * @param plm plm
	 * @param frame frame
	 * @param user user data
	 */
	static void plmOnVideo(plm_t* plm, plm_frame_t *frame, void *user);

	/**
	 * PLM on audio
	 * @param plm plm
	 * @param samples samples
	 * @param user user data
	 */
	static void plmOnAudio(plm_t* plm, plm_samples_t *samples, void *user);

};
