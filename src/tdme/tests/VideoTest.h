#pragma once

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utilities/ObjectDeleter.h>
#include <tdme/video/decoder/MPEG1Decoder.h>
#include <tdme/utilities/fwd-tdme.h>

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::audio::Audio;
using tdme::audio::PacketAudioStream;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
using tdme::utilities::ObjectDeleter;
using tdme::video::decoder::MPEG1Decoder;
using tdme::utilities::ByteBuffer;

/**
 * Video test
 * @author andreas.drewke
 * @version $Id$
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
	DynamicColorTexture* videoTexture { nullptr };
	ByteBuffer* videoAudioBuffer { nullptr };
	PacketAudioStream* videoAudioStream { nullptr };

	/**
	 * @return wall model
	 */
	Model* createWallModel();
public:

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

	// overriden methods
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;
	void onChar(unsigned int key, int x, int y) override;
	void onKeyDown (unsigned char key, int keyCode, int x, int y, bool repeat) override;
	void onKeyUp(unsigned char key, int keyCode, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;
	void onMouseWheel(int button, int direction, int x, int y) override;

	/**
	 * Public constructor
	 */
	VideoTest();
};
