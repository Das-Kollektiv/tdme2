#pragma once

#include <memory>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/ObjectDeleter.h>
#include <tdme/video/decoder/MPEG1Decoder.h>

using std::unique_ptr;

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::audio::Audio;
using tdme::audio::PacketAudioStream;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
using tdme::utilities::ByteBuffer;
using tdme::utilities::ObjectDeleter;
using tdme::video::decoder::MPEG1Decoder;

/**
 * Video test
 * @author andreas.drewke
 */
class tdme::tests::VideoTest final
	: public virtual Application, public virtual InputEventHandler
{
private:
	Audio* audio { nullptr };
	Engine* engine { nullptr };

	bool keyLeft { false };
	bool keyRight { false };
	bool keyUp { false };
	bool keyDown { false };
	bool keyW { false };
	bool keyA { false };
	bool keyS { false };
	bool keyD { false };
	bool keyMinus { false };
	bool keyPlus { false };
	float camRotationY { 0.0f };
	float camRotationX { 0.0f };

	ObjectDeleter<Model> modelDeleter;
	ObjectDeleter<BoundingVolume> bvDeleter;
	MPEG1Decoder videoDecoder;
	unique_ptr<DynamicColorTexture> videoTexture;
	unique_ptr<ByteBuffer> videoAudioBuffer;
	PacketAudioStream* videoAudioStream { nullptr };

	/**
	 * @return wall model
	 */
	Model* createWallModel();

public:
	// forbid class copy
	FORBID_CLASS_COPY(VideoTest)

	/**
	 * Public constructor
	 */
	VideoTest();

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

	// overridden methods
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;
	void onChar(int key, int x, int y) override;
	void onKeyDown(int key, int keyCode, int x, int y, bool repeat, int modifiers) override;
	void onKeyUp(int key, int keyCode, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;
	void onMouseWheel(int button, int direction, int x, int y) override;

};
