// Generated from /tdme/src/tdme/engine/Engine.java
#include <tdme/engine/Engine_initialize_2.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/gui/renderer/GUIShader.h>

using tdme::engine::Engine_initialize_2;
using tdme::engine::Engine;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::gui::renderer::GUIShader;

Engine_initialize_2::Engine_initialize_2(Engine *Engine_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, Engine_this(Engine_this)
{
	clinit();
	ctor();
}

void Engine_initialize_2::onUpdateProjectionMatrix()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this);

	if (Engine_this->shadowMapping != nullptr)
		Engine_this->shadowMapping->updateMVPMatrices(this);

}

void Engine_initialize_2::onUpdateCameraMatrix()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this);

	if (Engine_this->shadowMapping != nullptr)
		Engine_this->shadowMapping->updateMVPMatrices(this);

}

void Engine_initialize_2::onUpdateModelViewMatrix()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this);

	if (Engine_this->shadowMapping != nullptr)
		Engine_this->shadowMapping->updateMVPMatrices(this);

}

void Engine_initialize_2::onBindTexture(int32_t textureId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->bindTexture(this, textureId);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->bindTexture(this, textureId);

}

void Engine_initialize_2::onUpdateTextureMatrix()
{
}

void Engine_initialize_2::onUpdateEffect()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateEffect(this);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateEffect(this);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->updateEffect(this);

}

void Engine_initialize_2::onUpdateLight(int32_t lightId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateLight(this, lightId);

}

void Engine_initialize_2::onUpdateMaterial()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMaterial(this);

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Engine_initialize_2::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* Engine_initialize_2::getClass0()
{
	return class_();
}

