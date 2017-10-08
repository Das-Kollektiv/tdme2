
#pragma once

#include <vector>

#include <tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/CollisionResponse_Entity.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Console.h>

using std::vector;

using tdme::engine::physics::CollisionResponse;
using tdme::math::Math;
using tdme::engine::physics::CollisionResponse_Entity;
using tdme::math::MathTools;
using tdme::math::Vector3;
using tdme::utils::Console;

/** 
 * Collision response
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::CollisionResponse final
{
	friend class CollisionResponse_Entity;

public: /* protected */
	static constexpr int32_t HITPOINT_COUNT { 30 };
	vector<CollisionResponse_Entity> entities {  };
	CollisionResponse_Entity* selectedEntity {  };

public:

	/** 
	 * Reset
	 */
	inline void reset() {
		entities.clear();
		selectedEntity = nullptr;
	}

	/** 
	 * Adds a collision response entity 
	 * @param distance
	 * @return Entity or null
	 */
	inline CollisionResponse_Entity* addResponse(float distance) {
		entities.push_back(CollisionResponse_Entity());
		auto& entity = entities.at(entities.size() - 1);
		entity.distance = distance;
		if (selectedEntity == nullptr || distance > selectedEntity->distance) {
			selectedEntity = &entity;
		}
		return &entity;
	}

	/** 
	 * @return entity count
	 */
	inline int32_t getEntityCount() {
		return entities.size();
	}

	/** 
	 * @return selected entity
	 */
	inline CollisionResponse_Entity* getSelectedEntity() {
		return selectedEntity;
	}

	/** 
	 * Selects entity at given index
	 * @param idx
	 * @return
	 */
	inline CollisionResponse_Entity* getEntityAt(int32_t idx) {
		if (idx < 0 || idx >= entities.size()) return nullptr;
		return &entities.at(idx);
	}

	/** 
	 * Selects entity at given index
	 * @param idx
	 * @return
	 */
	inline CollisionResponse* selectEntityAt(int32_t idx) {
		if (idx < 0 || idx >= entities.size()) return this;
		selectedEntity = &entities.at(idx);
		return this;
	}

	inline bool hasEntitySelected() {
		return selectedEntity != nullptr;
	}

	inline float getDistance() {
		if (selectedEntity == nullptr) return 0.0f;
		return selectedEntity->distance;
	}

	inline bool hasPenetration() {
		if (selectedEntity == nullptr) return false;
		return selectedEntity->distance < -MathTools::EPSILON;
	}

	inline float getPenetration() {
		if (selectedEntity == nullptr) return 0.0f;
		return -selectedEntity->distance;
	}

	inline Vector3* getNormal() {
		if (selectedEntity == nullptr) return nullptr;
		return &selectedEntity->normal;
	}

	/**
	 * @return get hit points
	 */
	inline vector<Vector3>* getHitPoints() {
		if (selectedEntity == nullptr) return nullptr;
		return &selectedEntity->hitPoints;
	}

	/** 
	 * @return hit points count
	 */
	inline int32_t getHitPointsCount() {
		if (selectedEntity == nullptr) return 0;
		return selectedEntity->hitPoints.size();
	}

	/** 
	 * Get hit point of given index 
	 * @param i
	 * @return hit point for given hit points index
	 */
	inline Vector3* getHitPointAt(int32_t i) {
		if (selectedEntity == nullptr) return nullptr;
		return &selectedEntity->hitPoints.at(i);
	}

public: /* protected */

	/** 
	 * Invert normals
	 */
	inline void invertNormals() {
		for (auto i = 0; i < entities.size(); i++) {
			entities.at(i).getNormal().scale(-1.0f);
		}
	}

public:

	/** 
	 * Set up response from given collision response
	 * @param response
	 */
	inline CollisionResponse* fromResponse(CollisionResponse* response) {
		selectedEntity = nullptr;
		entities = response->entities;
		if (response->selectedEntity != nullptr)
		for (auto i = 0; i < response->entities.size(); i++) {
			if (&response->entities.at(i) == response->selectedEntity) {
				selectedEntity = &entities.at(i);
				return this;
			}
		}
		return this;
	}

	/** 
	 * Set up response from given collision response
	 * @param response
	 */
	inline CollisionResponse* mergeResponse(CollisionResponse* response) {
		for (auto i = 0; i < response->entities.size(); i++) {
			auto& srcEntity = response->entities.at(i);
			CollisionResponse_Entity* dstEntity = nullptr;
			if (entities.size() > 0) dstEntity = &entities.at(0);
			if (dstEntity == nullptr || srcEntity.distance > dstEntity->distance) {
				if (dstEntity == nullptr) {
					entities.push_back(CollisionResponse_Entity());
					dstEntity = &entities.at(entities.size() - 1);
				}
				dstEntity->distance = srcEntity.distance;
				dstEntity->normal.set(srcEntity.normal);
			}
			selectedEntity = &entities.at(0);
			for (auto j = 0; j < srcEntity.hitPoints.size(); j++) {
				dstEntity->addHitPoint(srcEntity.hitPoints.at(j));
			}
		}
		return this;
	}

	/**
	 * Public constructor
	 * @param distance
	 * @param normal
	 */
	inline CollisionResponse() {
	}

};
