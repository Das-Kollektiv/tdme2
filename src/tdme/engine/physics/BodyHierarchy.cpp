#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/BodyHierarchy.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::physics::Body;
using tdme::engine::physics::BodyHierarchy;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utilities::Console;

BodyHierarchy::BodyHierarchy(World* world, const string& id, BodyType type, bool enabled, uint16_t collisionTypeId, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor)
	: Body(world, id, type, enabled, collisionTypeId, transform, restitution, friction, mass, inertiaTensor, {})
{
}

BodyHierarchy::~BodyHierarchy() {
}


void BodyHierarchy::resetColliders() {
	Body::resetColliders();
	//
	for (auto subBody: bodies) {
		Body::resetColliders(subBody->colliders, subBody->boundingVolumes, subBody->transform);
	}
}

void BodyHierarchy::updateHierarchy(const Transform& parentTransform, BodyHierarchyLevel* bodyHierarchyLevel, int depth) {
	BoundingBox entityBoundingBox;
	auto levelParentTransform = parentTransform.clone();
	levelParentTransform*= bodyHierarchyLevel->transform;
	for (auto& childBodyIt: bodyHierarchyLevel->children) {
		auto child = childBodyIt.second;
		//
		Body::resetColliders(child->colliders, child->boundingVolumes, levelParentTransform * child->transform);
	}
	for (auto& childBodyIt: bodyHierarchyLevel->children) {
		updateHierarchy(levelParentTransform, childBodyIt.second, depth + 1);
	}
}

void BodyHierarchy::addBody(const string& id, const Transform& transform, const vector<BoundingVolume*>& boundingVolumes, const string& parentId) {
	auto _entity = getBody(id);
	if (_entity != nullptr) {
		Console::println("BodyHierarchy::addEntity(): " + id + ": body already added!");
		return;
	}

	//
	removeBody(id);

	// add to hierarchy
	auto parentBodyHierarchyLevel = getBodyHierarchyLevel(parentId);
	if (parentBodyHierarchyLevel == nullptr) {
		Console::println("BodyHierarchy::addBody(): parent '" + parentId + "': not found");
		return;
	}
	auto bodyHierarchyLevel = new BodyHierarchyLevel(id, parentBodyHierarchyLevel, transform, boundingVolumes);
	parentBodyHierarchyLevel->children[id] = bodyHierarchyLevel;
	// finally create collision shapes
	for (auto boundingVolume: bodyHierarchyLevel->boundingVolumes) {
		boundingVolume->createCollisionShape(world);
	}

	// and bodies
	bodies.push_back(bodyHierarchyLevel);
}

void BodyHierarchy::updateBody(const string& id, const Transform& transform) {
	auto bodyHierarchyLevel = getBodyHierarchyLevel(id);
	if (bodyHierarchyLevel == nullptr || bodyHierarchyLevel->parent == nullptr) {
		return;
	}
	//
	bodyHierarchyLevel->transform = transform;
}

void BodyHierarchy::removeBody(const string& id) {
	// remove from hierarchy and bodies
	auto bodyHierarchyLevel = getBodyHierarchyLevel(id);
	if (bodyHierarchyLevel == nullptr || bodyHierarchyLevel->parent == nullptr) {
		Console::println("BodyHierarchy::removeBody(): '" + id + "': not found");
		return;
	}

	//
	vector<string> children;
	for (auto& childIt: bodyHierarchyLevel->children) children.push_back(childIt.first);
	for (auto child: children) removeBody(child);

	//
	removeColliders(bodyHierarchyLevel->colliders, bodyHierarchyLevel->boundingVolumes);
	bodies.erase(remove(bodies.begin(), bodies.end(), bodyHierarchyLevel), bodies.end());

	//
	auto bodyHierarchyLevelIt = bodyHierarchyLevel->parent->children.find(id);
	if (bodyHierarchyLevelIt != bodyHierarchyLevel->parent->children.end()) {
		delete bodyHierarchyLevelIt->second;
		bodyHierarchyLevel->parent->children.erase(bodyHierarchyLevelIt);
	}
}

const vector<BodyHierarchy::SubBody*> BodyHierarchy::query(const string& parentId) {
	vector<SubBody*> entities;
	auto parentBodyHierarchyLevel = getBodyHierarchyLevel(parentId);
	if (parentBodyHierarchyLevel == nullptr) {
		return entities;
	}
	for (auto& entityIt: parentBodyHierarchyLevel->children) {
		entities.push_back(entityIt.second);
	}
	return entities;
}

void BodyHierarchy::update() {
	// we need the scale from our body transform to be passed as local transform when resetting colliders
	Transform scaleTransform;
	scaleTransform.setScale(transform.getScale());
	scaleTransform.update();
	// update hierarchy
	updateHierarchy(scaleTransform, &bodyRoot, 0);
}
