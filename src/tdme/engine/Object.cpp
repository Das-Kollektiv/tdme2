#include <tdme/engine/Object.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/ShaderModel.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transformations.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::engine::model::ShaderModel;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::Engine;
using tdme::engine::Object;
using tdme::engine::Partition;
using tdme::engine::Transformations;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utilities::StringTools;

Object::Object(const string& id, Model* model, int instances): ObjectInternal(id, model, instances)
{
	setShader("default");
	setDistanceShader("default");
}

Object::Object(const string& id, Model* model): ObjectInternal(id, model, 1)
{
	setShader("default");
	setDistanceShader("default");
}

void Object::setEngine(Engine* engine)
{
	if (this->engine != nullptr) this->engine->deregisterEntity(this);
	this->engine = engine;
	if (engine != nullptr) engine->registerEntity(this);
}

void Object::setRenderer(Renderer* renderer)
{
}

void Object::fromTransformations(const Transformations& transformations)
{
	ObjectInternal::fromTransformations(transformations);
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void Object::update()
{
	ObjectInternal::update();
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void Object::setEnabled(bool enabled)
{
	// return if enable state has not changed
	if (this->enabled == enabled) return;

	// frustum if root entity
	if (parentEntity == nullptr) {
		// frustum culling enabled?
		if (frustumCulling == true) {
			// yeo, add or remove from partition
			if (enabled == true) {
				if (engine != nullptr) engine->partition->addEntity(this);
			} else {
				if (engine != nullptr) engine->partition->removeEntity(this);
			}
		}
	}
	// call parent class::setEnabled()
	ObjectInternal::setEnabled(enabled);
}

bool Object::isFrustumCulling() {
	return frustumCulling;
}

void Object::setFrustumCulling(bool frustumCulling) {
	// check if enabled and engine attached
	if (enabled == true && engine != nullptr) {
		// had frustum culling
		if (this->frustumCulling == true) {
			// yep, remove if set to false now
			if (frustumCulling == false) engine->partition->removeEntity(this);
		} else {
			// yep, add if set to true now
			if (frustumCulling == true) engine->partition->addEntity(this);
		}
	}
	this->frustumCulling = frustumCulling;
	// delegate change to engine
	if (engine != nullptr) engine->registerEntity(this);
}

void Object::dispose()
{
	ObjectInternal::dispose();
}

void Object::initialize()
{
	ObjectInternal::initialize();
}

void Object::setShader(const string& id) {
	if (model->getShaderModel() == ShaderModel::PBR || model->getShaderModel() == ShaderModel::SPECULARPBR) {
		shaderId = StringTools::startsWith(id, "pbr-") == true || id.empty() == true?id:"pbr-" + id;
		shaderParameters.setShader(shaderId);
	} else
	if (model->getShaderModel() == ShaderModel::SPECULAR) {
		shaderId = StringTools::startsWith(id, "pbr-") == true?StringTools::substring(id, string("pbr-").size()):id;
		shaderParameters.setShader(shaderId);
	}
	uniqueShaderId = Engine::getUniqueShaderId(shaderId);
	needsForwardShading =
		Engine::getLightingShader()->hasShader("defer_" + shaderId) == false ||
		Engine::getLightingShader()->hasShader("defer_" + distanceShaderId) == false;
	//
	if (engine != nullptr) {
		engine->deregisterEntity(this);
		engine->registerEntity(this);
	}
}

void Object::setDistanceShader(const string& id) {
	if (model->getShaderModel() == ShaderModel::PBR || model->getShaderModel() == ShaderModel::SPECULARPBR) {
		distanceShaderId = StringTools::startsWith(id, "pbr-") == true || id.empty() == true?id:"pbr-" + id;
		distanceShaderParameters.setShader(distanceShaderId);
	} else
	if (model->getShaderModel() == ShaderModel::SPECULAR) {
		distanceShaderId = StringTools::startsWith(id, "pbr-") == true?StringTools::substring(id, string("pbr-").size()):id;
		distanceShaderParameters.setShader(distanceShaderId);
	}
	uniqueDistanceShaderId = Engine::getUniqueShaderId(distanceShaderId);
	needsForwardShading =
		Engine::getLightingShader()->hasShader("defer_" + shaderId) == false ||
		Engine::getLightingShader()->hasShader("defer_" + distanceShaderId) == false;
	//
	if (engine != nullptr) {
		engine->deregisterEntity(this);
		engine->registerEntity(this);
	}
}
