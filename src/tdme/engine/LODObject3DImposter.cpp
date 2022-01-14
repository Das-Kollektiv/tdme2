#include <tdme/engine/LODObject3DImposter.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transformations.h>

using std::string;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::LODObject3DImposter;
using tdme::engine::Object3D;
using tdme::engine::Partition;
using tdme::engine::Transformations;

LODObject3DImposter::LODObject3DImposter(
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

	objectLOD1 = new Object3D(id + ".lod1", modelLOD1);
	objectLOD1->setParentEntity(this);

	objectLOD2 = new ImposterObject3D(id + ".lod2", imposterModelsLOD2);
	objectLOD2->setParentEntity(this);

	objectLOD1->setRenderPass(renderPass);
	objectLOD2->setRenderPass(renderPass);

	objectLOD1->setShader(shaderId);
	objectLOD2->setShader(shaderId);

	objectLOD1->setDistanceShader(distanceShaderId);
	objectLOD2->setDistanceShader(distanceShaderId);

	objectLOD1->setDistanceShaderDistance(distanceShaderDistance);
	objectLOD2->setDistanceShaderDistance(distanceShaderDistance);

	levelLOD = 1;
}

LODObject3DImposter::~LODObject3DImposter() {
	// delegate to LOD objects
	delete objectLOD1;
	delete objectLOD2;
}

void LODObject3DImposter::setEngine(Engine* engine)
{
	if (this->engine != nullptr) this->engine->deregisterEntity(this);
	this->engine = engine;
	if (engine != nullptr) engine->registerEntity(this);
	objectLOD1->setEngine(engine);
	objectLOD2->setEngine(engine);
}

void LODObject3DImposter::setRenderer(Renderer* renderer)
{
}

void LODObject3DImposter::fromTransformations(const Transformations& transformations)
{
	Transformations::fromTransformations(transformations);
	// delegate to LOD objects
	objectLOD1->fromTransformations(*this);
	objectLOD2->fromTransformations(*this);
	// update entity
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
	// reset current LOD object
	objectLOD = nullptr;
}

void LODObject3DImposter::update()
{
	Transformations::update();
	// delegate to LOD objects
	objectLOD1->fromTransformations(*this);
	objectLOD2->fromTransformations(*this);
	// update entity
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
	// reset current LOD object
	objectLOD = nullptr;
}

void LODObject3DImposter::setEnabled(bool enabled)
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

bool LODObject3DImposter::isFrustumCulling() {
	return frustumCulling;
}

void LODObject3DImposter::setFrustumCulling(bool frustumCulling) {
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

void LODObject3DImposter::dispose()
{
	// delegate to LOD objects
	objectLOD1->dispose();
	objectLOD2->dispose();
}

void LODObject3DImposter::initialize()
{
	// delegate to LOD objects
	objectLOD1->initialize();
	objectLOD2->initialize();
}

void LODObject3DImposter::setEnableEarlyZRejection(bool enableEarlyZRejection) {
	// delegate to LOD objects
	objectLOD1->setEnableEarlyZRejection(enableEarlyZRejection);
	objectLOD2->setEnableEarlyZRejection(enableEarlyZRejection);
}
