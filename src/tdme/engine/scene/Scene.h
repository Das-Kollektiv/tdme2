#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/prototype/BaseProperties.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/scene/SceneLight.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/UniquePtrSequenceIterator.h>

using std::make_unique;
using std::map;
using std::set;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::BaseProperties;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::scene::SceneLight;
using tdme::engine::EntityShaderParameters;
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
	EntityShaderParameters skyShaderParameters;
	unordered_set<string> enabledPostProcessingShaders;
	unordered_map<string, EntityShaderParameters> postProcessingShaderParameters;
	string guiFileName;

	/**
	 * Computes scene bounding box
	 * @returns dimension
	 */
	void computeBoundingBox();

	/**
	 * @returns scene center
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
	 * @returns application root path name
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
	 * @returns scene file name including relative path
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
	 * @returns rotation order
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
	 * @returns Lights iterator
	 */
	inline UniquePtrSequenceIterator<SceneLight> getLights() {
		return UniquePtrSequenceIterator<SceneLight>(&(*lights.begin()), &(*lights.end()));
	}

	/**
	 * @returns number of lights
	 */
	inline int getLightCount() {
		return lights.size();
	}

	/**
	 * Get light at given index
	 * @param i index
	 * @returns light
	 */
	inline SceneLight* getLightAt(int i) {
		if (i < 0 || i >= lights.size()) return nullptr;
		return lights[i].get();
	}

	/**
	 * Add light
	 * @returns light
	 */
	inline SceneLight* addLight() {
		lights.push_back(make_unique<SceneLight>(static_cast<int>(lights.size())));
		return lights[lights.size() - 1].get();
	}

	/**
	 * Remove light at given index i
	 * @param i index
	 * @returns success
	 */
	bool removeLightAt(int i) {
		if (i < 0 || i >= lights.size()) return false;
		lights.erase(lights.begin() + i);
		return true;
	}

	/**
	 * @returns scene prototype library
	 */
	inline SceneLibrary* getLibrary() {
		return library.get();
	}

	/**
	 * @returns dimension
	 */
	inline const Vector3& getDimension() {
		return dimension;
	}

	/**
	 * @returns scene bounding box
	 */
	inline BoundingBox* getBoundingBox() {
		return &boundingBox;
	}

	/**
	 * @returns scene center
	 */
	inline const Vector3& getCenter() {
		return center;
	}

	/**
	 * @returns new entity id
	 */
	inline int allocateEntityId() {
		return entityIdx++;
	}

	/**
	 * @returns entity idx
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
	 * @returns environment mapping object ids
	 */
	inline set<string> getEnvironmentMappingIds() {
		return environmentMappingIds;
	}

	/**
	 * @returns Entities iterator
	 */
	inline UniquePtrSequenceIterator<SceneEntity> getEntities() {
		return UniquePtrSequenceIterator<SceneEntity>(&(*entities.begin()), &(*entities.end()));
	}

	/**
	 * @returns number of entities
	 */
	inline int getEntityCount() {
		return entities.size();
	}

	/**
	 * Returns entity at given index
	 * @param idx index
	 * @returns scene entity
	 */
	inline SceneEntity* getEntityAt(int idx) {
		if (idx < 0 || idx >= entities.size()) return nullptr;
		return entities[idx].get();
	}

	/**
	 * Returns scene entity by id
	 * @param id id
	 * @returns scene entity
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
	 * @returns success
	 */
	bool removeEntity(const string& id);

	/**
	 * Rename an entity from scene
	 * @param id id
	 * @param newId new id
	 * @returns success
	 */
	bool renameEntity(const string& id, const string& newId);

	/**
	 * Get sky shader parameters
	 * @returns shader parameters
	 */
	inline const EntityShaderParameters& getSkyShaderParameters() {
		return skyShaderParameters;
	}

	/**
	 * Set sky shader parameters
	 * @param parameters shader parameters
	 */
	inline void setSkyShaderParameters(EntityShaderParameters& parameters) {
		skyShaderParameters = parameters;
	}

	/**
	 * Return enabled processing shader
	 * @returns enabled post processing shader
	 */
	inline unordered_set<string> getEnabledPostProcessingShader() {
		return enabledPostProcessingShaders;
	}

	/**
	 * Is post processing shader enabled
	 * @param shaderId shader id
	 * @returns processing shader enabled
	 */
	inline bool isPostProcessingShaderEnabled(const string& shaderId) {
		return enabledPostProcessingShaders.contains(shaderId);
	}

	/**
	 * Enable post processing shader
	 * @param shaderId shader id
	 */
	inline void enablePostProcessingShader(const string& shaderId) {
		enabledPostProcessingShaders.insert(shaderId);
	}

	/**
	 * Disable post processing shader
	 * @param shaderId shader id
	 */
	inline void disablePostProcessingShader(const string& shaderId) {
		enabledPostProcessingShaders.erase(shaderId);
	}

	/**
	 * Get post processing shader parameters
	 * @param shaderId shader id
	 * @returns shader parameters
	 */
	inline const EntityShaderParameters* getPostProcessingShaderParameters(const string& shaderId) {
		auto postProcessingShaderParametersIt = postProcessingShaderParameters.find(shaderId);
		if (postProcessingShaderParametersIt == postProcessingShaderParameters.end()) return nullptr;
		return &postProcessingShaderParametersIt->second;
	}

	/**
	 * Set post processing shader parameters
	 * @param parameters shader parameters
	 */
	inline void setPostProcessingShaderParameters(const string& shaderId, const EntityShaderParameters& parameters) {
		postProcessingShaderParameters[shaderId] = parameters;
	}

	/**
	 * @returns Scene GUI file name including relative path
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
