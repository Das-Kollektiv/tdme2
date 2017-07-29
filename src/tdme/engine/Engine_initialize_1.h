// Generated from /tdme/src/tdme/engine/Engine.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/GL3Renderer.h>

using tdme::engine::subsystems::renderer::GL3Renderer;
using tdme::engine::Engine;


struct default_init_tag;
class tdme::engine::Engine_initialize_1
	: public GL3Renderer
{

public:
	typedef GL3Renderer super;
	void onUpdateProjectionMatrix() override;
	void onUpdateCameraMatrix() override;
	void onUpdateModelViewMatrix() override;
	void onBindTexture(int32_t textureId) override;
	void onUpdateTextureMatrix() override;
	void onUpdateEffect() override;
	void onUpdateLight(int32_t lightId) override;
	void onUpdateMaterial() override;

	// Generated
	Engine_initialize_1(Engine *Engine_this);
	static ::java::lang::Class *class_();
	Engine *Engine_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class Engine;
	friend class Engine_initialize_2;
	friend class Engine_initialize_3;
};
