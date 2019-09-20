#include <tdme/engine/subsystems/earlyzrejection/EZRShaderPre.h>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShaderPreDefaultImplementation.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShaderPreFoliageImplementation.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShaderPreImplementation.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::earlyzrejection::EZRShaderPre;
using tdme::engine::subsystems::earlyzrejection::EZRShaderPreBaseImplementation;
using tdme::engine::subsystems::earlyzrejection::EZRShaderPreDefaultImplementation;
using tdme::engine::subsystems::earlyzrejection::EZRShaderPreFoliageImplementation;
using tdme::engine::subsystems::earlyzrejection::EZRShaderPreImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;
using tdme::utils::Console;

EZRShaderPre::EZRShaderPre(Renderer* renderer): renderer(renderer)
{
	if (EZRShaderPreDefaultImplementation::isSupported(renderer) == true) shader["default"] = new EZRShaderPreDefaultImplementation(renderer);
	if (EZRShaderPreFoliageImplementation::isSupported(renderer) == true) shader["foliage"] = new EZRShaderPreFoliageImplementation(renderer);
	mvMatrix.identity();
	mvpMatrix.identity();
}

EZRShaderPre::~EZRShaderPre() {
	for (auto shaderIt: shader) {
		delete shaderIt.second;
	}
}

bool EZRShaderPre::isInitialized()
{
	bool initialized = true;
	for (auto shaderIt: shader) {
		initialized&= shaderIt.second->isInitialized();
	}
	return initialized;
}

void EZRShaderPre::initialize()
{
	for (auto shaderIt: shader) {
		shaderIt.second->initialize();
	}
}

void EZRShaderPre::useProgram(Engine* engine)
{
	running = true;
	this->engine = engine;
}

void EZRShaderPre::unUseProgram()
{
	running = false;
	if (implementation != nullptr) {
		implementation->unUseProgram();;
	}
	implementation = nullptr;
	engine = nullptr;
}

void EZRShaderPre::updateMatrices(void* context)
{
	if (implementation == nullptr) return;
	// model view matrix
	mvMatrix.set(renderer->getModelViewMatrix());
	// object to screen matrix
	mvpMatrix.set(mvMatrix).multiply(renderer->getProjectionMatrix());
	//
	implementation->updateMatrices(context, mvpMatrix);
}

void EZRShaderPre::updateTextureMatrix(Renderer* renderer, void* context) {
	if (implementation == nullptr) return;
	implementation->updateTextureMatrix(renderer, context);
}

void EZRShaderPre::updateMaterial(Renderer* renderer, void* context)
{
	if (implementation == nullptr) return;
	implementation->updateMaterial(renderer, context);
}

void EZRShaderPre::bindTexture(Renderer* renderer, void* context, int32_t textureId)
{
	if (implementation == nullptr) return;
	implementation->bindTexture(renderer, context, textureId);
}

void EZRShaderPre::setShader(void* context, const string& id) {
	if (running == false) return;

	auto currentImplementation = implementation;

	auto shaderIt = shader.find(id);
	if (shaderIt == shader.end()) {
		shaderIt = shader.find("default");
	}
	implementation = shaderIt->second;

	if (currentImplementation != implementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram();
		implementation->useProgram(engine, context);
	}
}
