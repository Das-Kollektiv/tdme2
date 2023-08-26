#include <tdme/engine/ImposterObject.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transform.h>

using std::string;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::ImposterObject;
using tdme::engine::Object;
using tdme::engine::Partition;
using tdme::engine::Transform;

ImposterObject::ImposterObject(
	const string& id,
	const vector<Model*>& billboardModels
):
	id(id),
	billboardModels(billboardModels)
{
	this->enabled = true;
	this->pickable = false;
	this->contributesShadows = false;
	this->receivesShadows = false;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->entityTransformMatrix.identity();

	billboardObjects.resize(billboardModels.size());
	for (auto i = 0; i < billboardModels.size(); i++) {
		billboardObjects[i] = new Object(id + ".bb-" + to_string(i), billboardModels[i]);
		billboardObjects[i]->setParentEntity(this);
	}

	billboardObject = billboardObjects[0];

	for (auto billboardObject: billboardObjects) billboardObject->setRenderPass(renderPass);
	for (auto billboardObject: billboardObjects) billboardObject->setShader(shaderId);
}

ImposterObject::~ImposterObject() {
	// delegate to billboard objects
	for (auto billboardObject: billboardObjects) delete billboardObject;
}

void ImposterObject::setEngine(Engine* engine)
{
	if (this->engine != nullptr) this->engine->deregisterEntity(this);
	this->engine = engine;
	if (engine != nullptr) engine->registerEntity(this);
	for (auto billboardObject: billboardObjects) billboardObject->setEngine(engine);
}

void ImposterObject::setRenderer(Renderer* renderer)
{
}

void ImposterObject::setTransform(const Transform& transform)
{
	Transform::setTransform(transform);
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	// delegate to billboard objects
	auto imposterObjectTransform = entityTransform;
	imposterObjectTransform.addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
	imposterObjectTransform.update();
	for (auto billboardObject: billboardObjects) {
		billboardObject->setTransform(imposterObjectTransform);
		imposterObjectTransform.setRotationAngle(
			imposterObjectTransform.getRotationCount() - 1,
			imposterObjectTransform.getRotationAngle(imposterObjectTransform.getRotationCount() - 1) -(360.0f / static_cast<float>(billboardModels.size()))
		);
		imposterObjectTransform.update();
	}
	// update entity
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void ImposterObject::update()
{
	Transform::update();
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	// delegate to billboard objects
	auto imposterObjectTransform = entityTransform;
	imposterObjectTransform.addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
	imposterObjectTransform.update();
	for (auto billboardObject: billboardObjects) {
		billboardObject->setTransform(imposterObjectTransform);
		imposterObjectTransform.setRotationAngle(
			imposterObjectTransform.getRotationCount() - 1,
			imposterObjectTransform.getRotationAngle(imposterObjectTransform.getRotationCount() - 1) -(360.0f / static_cast<float>(billboardModels.size()))
		);
		imposterObjectTransform.update();
	}
	//
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void ImposterObject::setEnabled(bool enabled)
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
}

bool ImposterObject::isFrustumCulling() {
	return frustumCulling;
}

void ImposterObject::setFrustumCulling(bool frustumCulling) {
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
	if (engine != nullptr) engine->updateEntityRegistration(this);
}

void ImposterObject::dispose()
{
	// delegate to billboard objects
	for (auto billboardObject: billboardObjects) billboardObject->dispose();
}

void ImposterObject::initialize()
{
	// delegate to billboard objects
	for (auto billboardObject: billboardObjects) billboardObject->initialize();
}
