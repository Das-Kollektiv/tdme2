#pragma once

#if !defined(PL_MPEG_IMPLEMENTATION)
	#include <ext/pl_mpeg/pl_mpeg.h>
#endif

#include <memory>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/utilities/ByteBuffer.h>
#include <agui/video/decoder/fwd-agui.h>
#include <agui/video/decoder/VideoDecoder.h>

using std::string;
using std::unique_ptr;
using std::vector;

// namespaces
namespace agui {
namespace video {
namespace decoder {
	using ::agui::utilities::ByteBuffer;
}
}
}

/**
 * PL_MPEG/MPEG1 video decoder
 * @author Andreas Drewke
 */
class agui::video::decoder::MPEG1Decoder: public VideoDecoder
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(MPEG1Decoder)

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
	unique_ptr<ByteBuffer> videoBuffer;
	unique_ptr<ByteBuffer> audioBuffer;

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
