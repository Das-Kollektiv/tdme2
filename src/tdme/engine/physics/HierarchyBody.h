#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <reactphysics3d/collision/Collider.h>

#include <tdme/tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/Transform.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Transform;

/**
 * Dynamic rigid/static rigid/collision body class
 * @author Andreas Drewke
 */
class tdme::engine::physics::HierarchyBody final: public Body
{
	friend class World;

protected:

	/**
	 * Protected constructor
	 * @param world world
	 * @param id id
	 * @param type type
	 * @param enabled enabled
	 * @param collisionTypeId collision type id
	 * @param transform transform
	 * @param restitution restitution
	 * @param friction friction
	 * @param mass mass in kg
	 * @param inertiaTensor inertia tensor vector
	 * @param boundingVolumes bounding volumes
	 */
	HierarchyBody(World* world, const string& id, BodyType type, bool enabled, uint16_t collisionTypeId, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*>& boundingVolumes);

	/**
	 * Destructor
	 */
	~HierarchyBody();

	/**
	 * Reset proxy shapes
	 */
	void resetColliders() override;

private:
	struct SubBody {
		string id;
		vector<BoundingVolume*> boundingVolumes;
		vector<reactphysics3d::Collider*> colliders;
		Transform transform;
	};
	unordered_map<string, SubBody> subBodies;

	/**
	 * Get sub body
	 * @param id id
	 * @return sub body
	 */
	inline SubBody* getBody(const string& id) {
		auto bodyIt = subBodies.find(id);
		if (bodyIt == subBodies.end()) return nullptr;
		return &bodyIt->second;
	}

public:

	/**
	 * Add sub body
	 * @param id id
	 * @param parentTransform hierarchy parent transform
	 * @param transform local transform
	 * @param boundingVolumes bounding volumes
	 */
	void addBody(const string& id, const Transform& parentTransform, const Transform& transform, const vector<BoundingVolume*>& boundingVolumes);

	/**
	 * Update sub body
	 * @param id id
	 * @param parentTransform hierarchy parent transform
	 * @param transform transform
	 */
	void updateBody(const string& id, const Transform& parentTransform, const Transform& transform);

	/**
	 * Remove sub body
	 * @param id id
	 */
	void removeBody(const string& id);

};
