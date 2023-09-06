#include <tdme/engine/EntityHierarchy.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transform.h>
#include <tdme/utilities/Console.h>

using std::string;

using tdme::engine::Engine;
using tdme::engine::EntityHierarchy;
using tdme::engine::Object;
using tdme::engine::Partition;
using tdme::engine::Transform;
using tdme::utilities::Console;

EntityHierarchy::EntityHierarchy(const string& id): id(id)
{
	this->enabled = true;
	this->pickable = false;
	this->contributesShadows = false;
	this->receivesShadows = false;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->entityTransformMatrix.identity();
	this->entityTransformMatrixInverted.identity();
}

EntityHierarchy::~EntityHierarchy()
{
	for (auto entity: entities) delete entity;
	for (const auto& [childEntityId, childEntity]: entityRoot.children) deleteHierarchy(childEntity, 0);
}

void EntityHierarchy::deleteHierarchy(EntityHierarchyLevel* entityHierarchyLevel, int depth) {
	for (const auto& [childEntityId, childEntity]: entityHierarchyLevel->children) deleteHierarchy(childEntity, depth + 1);
	delete entityHierarchyLevel;
}

void EntityHierarchy::setEngine(Engine* engine)
{
	if (this->engine != nullptr) this->engine->deregisterEntity(this);
	this->engine = engine;
	if (engine != nullptr) engine->registerEntity(this);
	for (auto entity: entities) entity->setEngine(engine);
}

void EntityHierarchy::setRenderer(Renderer* renderer)
{
	this->renderer = renderer;
	for (auto entity: entities) entity->setRenderer(renderer);
}

void EntityHierarchy::addEntity(Entity* entity, const string& parentId) {
	auto _entity = getEntity(entity->getId());
	if (_entity == entity) {
		Console::println("EntityHierarchy::addEntity(): " + entity->getId() + ": entity already added!");
		return;
	}

	//
	removeEntity(entity->getId());

	// base properties
	entity->setParentEntity(this);
	entity->setEngine(engine);
	entity->setRenderer(renderer);
	entity->setPickable(pickable);
	entity->setContributesShadows(contributesShadows);
	entity->setReceivesShadows(receivesShadows);
	entity->setEffectColorMul(effectColorMul);
	entity->setEffectColorAdd(effectColorAdd);
	if (initialized == true) entity->initialize();

	// add to hierarchy
	auto parentEntityHierarchyLevel = getEntityHierarchyLevel(parentId);
	if (parentEntityHierarchyLevel == nullptr) {
		Console::println("EntityHierarchy::addEntity(): parent '" + parentId + "': not found");
		return;
	}
	parentEntityHierarchyLevel->children[entity->getId()] = new EntityHierarchyLevel(entity->getId(), parentEntityHierarchyLevel, entity);

	// and entities
	entities.push_back(entity);
}

void EntityHierarchy::removeEntity(const string& id) {
	// remove from hierarchy and entities
	auto entityHierarchyLevel = getEntityHierarchyLevel(id);
	if (entityHierarchyLevel == nullptr || entityHierarchyLevel->parent == nullptr) {
		return;
	}

	//
	vector<string> children;
	for (const auto& [childEntityId, childEntity]: entityHierarchyLevel->children) children.push_back(childEntityId);
	for (const auto& child: children) removeEntity(child);

	//
	auto entity = entityHierarchyLevel->entity;
	entities.erase(remove(entities.begin(), entities.end(), entity), entities.end());

	//
	auto entityHierarchyLevelIt = entityHierarchyLevel->parent->children.find(id);
	if (entityHierarchyLevelIt != entityHierarchyLevel->parent->children.end()) {
		delete entityHierarchyLevelIt->second;
		entityHierarchyLevel->parent->children.erase(entityHierarchyLevelIt);
	}

	//
	if (engine != nullptr) engine->removeEntityFromLists(entity);

	// dispose
	entity->dispose();
	delete entity;
}

const vector<Entity*> EntityHierarchy::query(const string& parentId) {
	vector<Entity*> entities;
	auto parentEntityHierarchyLevel = getEntityHierarchyLevel(parentId);
	if (parentEntityHierarchyLevel == nullptr) {
		return entities;
	}
	for (const auto& [childEntityId, childEntity]: parentEntityHierarchyLevel->children) {
		entities.push_back(childEntity->entity);
	}
	return entities;
}

void EntityHierarchy::updateHierarchy(const Transform& parentTransform, EntityHierarchyLevel* entityHierarchyLevel, int depth, bool& firstEntity) {
	BoundingBox entityBoundingBox;
	auto levelParentTransform = parentTransform;
	if (entityHierarchyLevel->entity != nullptr) levelParentTransform*= entityHierarchyLevel->entity->getTransform();
	for (const auto& [childEntityId, childEntity]: entityHierarchyLevel->children) {
		auto entity = childEntity->entity;
		entity->setParentTransform(levelParentTransform);
		entityBoundingBox.fromBoundingVolumeWithTransformMatrix(entity->getWorldBoundingBox(), entityTransformMatrixInverted);
		if (firstEntity == true) {
			boundingBox = entityBoundingBox;
			firstEntity = false;
		} else {
			boundingBox.extend(&entityBoundingBox);
		}
	}
	for (const auto& [childEntityId, childEntity]: entityHierarchyLevel->children) {
		updateHierarchy(levelParentTransform, childEntity, depth + 1, firstEntity);
	}
	if (depth == 0) {
		// bounding boxes
		boundingBox.update();
		worldBoundingBox.fromBoundingVolumeWithTransformMatrix(&boundingBox, entityTransformMatrix);
		// update entity
		if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
	}
}

void EntityHierarchy::setTransform(const Transform& transform)
{
	//
	Transform::setTransform(transform);
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	//
	this->entityTransformMatrixInverted = entityTransformMatrix.clone().invert();
	// update hierarchy
	auto firstEntity = true;
	updateHierarchy(entityTransform, &entityRoot, 0, firstEntity);
}

void EntityHierarchy::update()
{
	//
	Transform::update();
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	//
	this->entityTransformMatrixInverted = entityTransformMatrix.clone().invert();
	// update hierarchy
	auto firstEntity = true;
	updateHierarchy(entityTransform, &entityRoot, 0, firstEntity);
}

void EntityHierarchy::setEnabled(bool enabled)
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

bool EntityHierarchy::isFrustumCulling() {
	return frustumCulling;
}

void EntityHierarchy::setFrustumCulling(bool frustumCulling) {
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

void EntityHierarchy::dispose()
{
	//
	initialized = false;
	//
	// delegate to entities
	for (auto entity: entities) {
		if (engine != nullptr) engine->removeEntityFromLists(entity);
		entity->dispose();
	}
}

void EntityHierarchy::initialize()
{
	//
	initialized = true;
	// delegate to entities
	for (auto entity: entities) entity->initialize();
}
