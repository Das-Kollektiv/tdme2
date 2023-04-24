#include <tdme/engine/LODObjectImposter.h>

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
using tdme::engine::LODObjectImposter;
using tdme::engine::Object;
using tdme::engine::Partition;
using tdme::engine::Transform;

LODObjectImposter::LODObjectImposter(
	const string& id,
	Model* modelLOD1,
	const vector<Model*>& imposterModelsLOD2,
	float lod2MinDistance,
	float lodNoneMinDistance
):
	id(id),
	modelLOD1(modelLOD1),
	lod2MinDistance(lod2MinDistance),
	lodNoneMinDistance(lodNoneMinDistance)
{
	this->enabled = true;
	this->pickable = false;
	this->contributesShadows = false;
	this->receivesShadows = false;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->effectColorMulLOD2.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAddLOD2.set(0.0f, 0.0f, 0.0f, 0.0f);

	objectLOD1 = new Object(id + ".lod1", modelLOD1);
	objectLOD1->setParentEntity(this);

	objectLOD2 = new ImposterObject(id + ".lod2", imposterModelsLOD2);
	objectLOD2->setParentEntity(this);

	objectLOD1->setRenderPass(renderPass);
	objectLOD2->setRenderPass(renderPass);

	objectLOD1->setShader(shaderId);
	objectLOD2->setShader(shaderId);

	levelLOD = 1;
}

LODObjectImposter::~LODObjectImposter() {
	// delegate to LOD objects
	delete objectLOD1;
	delete objectLOD2;
}

void LODObjectImposter::setEngine(Engine* engine)
{
	if (this->engine != nullptr) this->engine->deregisterEntity(this);
	this->engine = engine;
	if (engine != nullptr) engine->registerEntity(this);
	objectLOD1->setEngine(engine);
	objectLOD2->setEngine(engine);
}

void LODObjectImposter::setRenderer(Renderer* renderer)
{
}

void LODObjectImposter::setTransform(const Transform& transform)
{
	Transform::setTransform(transform);
	//
	auto entityTransform = parentTransform * (*this);
	transformMatrix = entityTransform.getTransformMatrix();
	// delegate to LOD objects
	objectLOD1->setTransform(entityTransform);
	objectLOD2->setTransform(entityTransform);
	// update entity
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
	// reset current LOD object
	objectLOD = nullptr;
}

void LODObjectImposter::update()
{
	Transform::update();
	//
	auto entityTransform = parentTransform * (*this);
	transformMatrix = entityTransform.getTransformMatrix();
	// delegate to LOD objects
	objectLOD1->setTransform(entityTransform);
	objectLOD2->setTransform(entityTransform);
	// update entity
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
	// reset current LOD object
	objectLOD = nullptr;
}

void LODObjectImposter::setEnabled(bool enabled)
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
	// reset current LOD object
	objectLOD = nullptr;
}

bool LODObjectImposter::isFrustumCulling() {
	return frustumCulling;
}

void LODObjectImposter::setFrustumCulling(bool frustumCulling) {
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

void LODObjectImposter::dispose()
{
	// delegate to LOD objects
	objectLOD1->dispose();
	objectLOD2->dispose();
}

void LODObjectImposter::initialize()
{
	// delegate to LOD objects
	objectLOD1->initialize();
	objectLOD2->initialize();
}

void LODObjectImposter::setEnableEarlyZRejection(bool enableEarlyZRejection) {
	// delegate to LOD objects
	objectLOD1->setEnableEarlyZRejection(enableEarlyZRejection);
	objectLOD2->setEnableEarlyZRejection(enableEarlyZRejection);
}
