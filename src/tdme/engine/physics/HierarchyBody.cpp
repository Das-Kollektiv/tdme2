#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/HierarchyBody.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::physics::Body;
using tdme::engine::physics::HierarchyBody;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utilities::Console;

HierarchyBody::HierarchyBody(World* world, const string& id, BodyType type, bool enabled, uint16_t collisionTypeId, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*>& boundingVolumes)
	: Body(world, id, type, enabled, collisionTypeId, transform, restitution, friction, mass, inertiaTensor, boundingVolumes)
{
}

HierarchyBody::~HierarchyBody() {
}


void HierarchyBody::resetColliders() {
	Body::resetColliders();
	//
	for (auto& subBodyIt: subBodies) {
		auto& subBody = subBodyIt.second;
		Body::resetColliders(subBody.colliders, subBody.boundingVolumes, subBody.transform);
	}
}

void HierarchyBody::addBody(const string& id, const Transform& parentTransform, const Transform& transform, const vector<BoundingVolume*>& boundingVolumes) {
	//
	removeBody(id);
	//
	Transform rootScaleTransform;
	rootScaleTransform.setScale(transformScale);
	auto finalTransform = rootScaleTransform * (parentTransform) * transform;
	//
	subBodies[id] = {
		.id = id,
		.boundingVolumes = {},
		.colliders = {},
		.transform = finalTransform
	};
	//
	auto subBody = getBody(id);
	if (subBody == nullptr) return;
	//
	for (auto boundingVolume: boundingVolumes) {
		subBody->boundingVolumes.push_back(boundingVolume->clone());
	}
	//
	Body::resetColliders(subBody->colliders, subBody->boundingVolumes, finalTransform);
}

void HierarchyBody::updateBody(const string& id, const Transform& parentTransform, const Transform& transform) {
	auto subBody = getBody(id);
	if (subBody == nullptr) return;
	//
	Transform rootScaleTransform;
	rootScaleTransform.setScale(transformScale);
	auto finalTransform = rootScaleTransform * (parentTransform) * transform;
	//
	subBody->transform = finalTransform;
	Body::resetColliders(subBody->colliders, subBody->boundingVolumes, finalTransform);
}

void HierarchyBody::removeBody(const string& id) {
	auto subBody = getBody(id);
	if (subBody == nullptr) return;
	//
	removeColliders(subBody->colliders, subBody->boundingVolumes);
	//
	subBodies.erase(id);
}

