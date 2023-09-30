#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/prototype/BaseProperties.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/scene/SceneLight.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/UniquePtrSequenceIterator.h>

using std::make_unique;
using std::map;
using std::set;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::BaseProperties;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::scene::SceneLight;
using tdme::math::Vector3;
using tdme::utilities::UniquePtrSequenceIterator;

/**
 * Scene definition
 * @author Andreas Drewke
 */
class tdme::engine::scene::Scene final
	: public BaseProperties
{
private:
	string applicationRootPathName;
	string fileName;
	RotationOrder* rotationOrder { nullptr };
	vector<unique_ptr<SceneLight>> lights;
	unique_ptr<SceneLibrary> library;
	map<string, SceneEntity*> entitiesById;
	vector<unique_ptr<SceneEntity>> entities;
	set<string> environmentMappingIds;
	int entityIdx;
	BoundingBox boundingBox;
	Vector3 dimension;
	Vector3 center;
	string guiFileName;

	/**
	 * Computes scene bounding box
	 * @return dimension
	 */
	void computeBoundingBox();

	/**
	 * @return scene center
	 */
	void computeCenter();

public:
	/**
	 * Public constructor
	 * @param name name
	 * @param description description
	 */
	Scene(const string& name, const string& description);

	/**
	 * Destructor
	 */
	virtual ~Scene();

	/**
	 * @return application root path name
	 */
	inline const string& getApplicationRootPathName() {
		return applicationRootPathName;
	}

	/**
	 * Set application root path name
	 * @param applicationRootPathName application root path name
	 */
	inline void setApplicationRootPathName(const string& applicationRootPathName) {
		this->applicationRootPathName = applicationRootPathName;
	}

	/**
	 * @return scene file name including relative path
	 */
	inline const string& getFileName() {
		return fileName;
	}

	/**
	 * Set up scene file name including relative path
	 * @param fileName scene file name including relative path
	 */
	inline void setFileName(const string& fileName) {
		this->fileName = fileName;
	}

	/**
	 * @return rotation order
	 */
	inline RotationOrder* getRotationOrder() {
		return rotationOrder;
	}

	/**
	 * Set rotation order
	 * @param rotationOrder rotation order
	 */
	inline void setRotationOrder(RotationOrder* rotationOrder) {
		this->rotationOrder = rotationOrder;
	}

	/**
	 * @return Lights iterator
	 */
	inline UniquePtrSequenceIterator<SceneLight> getLights() {
		return UniquePtrSequenceIterator<SceneLight>(&lights[0], &lights[lights.size()]);
	}

	/**
	 * @return number of lights
	 */
	inline int getLightCount() {
		return lights.size();
	}

	/**
	 * Get light at given index
	 * @param i index
	 * @return light
	 */
	inline SceneLight* getLightAt(int i) {
		if (i < 0 || i >= lights.size()) return nullptr;
		return lights[i].get();
	}

	/**
	 * Add light
	 * @return light
	 */
	inline SceneLight* addLight() {
		lights.push_back(make_unique<SceneLight>(lights.size()));
		return lights[lights.size() - 1].get();
	}

	/**
	 * Remove light at given index i
	 * @param i index
	 * @return success
	 */
	bool removeLightAt(int i) {
		if (i < 0 || i >= lights.size()) return false;
		lights.erase(lights.begin() + i);
		return true;
	}

	/**
	 * @return scene prototype library
	 */
	inline SceneLibrary* getLibrary() {
		return library.get();
	}

	/**
	 * @return dimension
	 */
	inline const Vector3& getDimension() {
		return dimension;
	}

	/**
	 * @return scene bounding box
	 */
	inline BoundingBox* getBoundingBox() {
		return &boundingBox;
	}

	/**
	 * @return scene center
	 */
	inline const Vector3& getCenter() {
		return center;
	}

	/**
	 * @return new entity id
	 */
	inline int allocateEntityId() {
		return entityIdx++;
	}

	/**
	 * @return entity idx
	 */
	inline int getEntityIdx() {
		return entityIdx;
	}

	/**
	 * Set entity idx
	 * @param entityIdx objectIdx
	 */
	inline void setEntityIdx(int entityIdx) {
		this->entityIdx = entityIdx;
	}

	/**
	 * Clears all scene entities
	 */
	void clearEntities();

	/**
	 * Get entities with given prototype id
	 * @param prototypeId prototype id
	 * @param entitiesByPrototypeId entities by prototype id
	 */
	void getEntitiesByPrototypeId(int prototypeId, vector<string>& entitiesByPrototypeId);

	/**
	 * Remove entities with given prototype id
	 * @param prototypeId prototype id
	 */
	void removeEntitiesByPrototypeId(int prototypeId);

	/**
	 * Replace prototype of given search prototype with new prototype
	 * @param searchPrototypeId search prototype id
	 * @param newPrototypeId new prototype id
	 */
	void replacePrototypeByIds(int searchPrototypeId, int newPrototypeId);

	/**
	 * @return environment mapping object ids
	 */
	inline set<string> getEnvironmentMappingIds() {
		return environmentMappingIds;
	}

	/**
	 * @return Entities iterator
	 */
	inline UniquePtrSequenceIterator<SceneEntity> getEntities() {
		return UniquePtrSequenceIterator<SceneEntity>(&entities[0], &entities[entities.size()]);
	}

	/**
	 * @return number of entities
	 */
	inline int getEntityCount() {
		return entities.size();
	}

	/**
	 * Returns entity at given index
	 * @param idx index
	 * @return scene entity
	 */
	inline SceneEntity* getEntityAt(int idx) {
		if (idx < 0 || idx >= entities.size()) return nullptr;
		return entities[idx].get();
	}

	/**
	 * Returns scene entity by id
	 * @param id id
	 * @return scene entity
	 */
	SceneEntity* getEntity(const string& id);

	/**
	 * Adds an entity to scene
	 * @param object object
	 */
	void addEntity(SceneEntity* entity);

	/**
	 * Removes an entity from scene
	 * @param id id
	 * @return success
	 */
	bool removeEntity(const string& id);

	/**
	 * Rename an entity from scene
	 * @param id id
	 * @param newId new id
	 * @return success
	 */
	bool renameEntity(const string& id, const string& newId);

	/**
	 * @return Scene GUI file name including relative path
	 */
	inline const string& getGUIFileName() {
		return guiFileName;
	}

	/**
	 * Set up scene GUI file name including relative path
	 * @param fileName scene GUI file name including relative path
	 */
	inline void setGUIFileName(const string& fileName) {
		this->guiFileName = fileName;
	}

	/**
	 * Update scene dimension, bounding box, center
	 */
	void update();

};
