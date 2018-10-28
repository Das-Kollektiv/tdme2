#pragma once

#include <vector>
#include <string>
#include <map>

#include <tdme/tdme.h>
#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/model/ModelProperties.h>
#include <tdme/tools/shared/model/ModelProperties.h>
#include <tdme/tools/shared/model/LevelEditorEntityLODLevel.h>

using std::vector;
using std::string;

using tdme::engine::LODObject3D;
using tdme::engine::model::Model;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorEntityModel;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityPhysics;
using tdme::tools::shared::model::ModelProperties;
using tdme::tools::shared::model::LevelEditorEntityLODLevel;

/** 
 * Level Editor Model
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntity final
	: public ModelProperties
{
	friend class LevelEditorEntity_EntityType;

public:
	static constexpr int32_t ID_NONE { -1 };
	static constexpr int32_t MODEL_BOUNDINGVOLUME_COUNT { 24 };
	static char MODEL_BOUNDINGVOLUME_IDS[][MODEL_BOUNDINGVOLUME_COUNT];

private:
	int32_t id {  };
	LevelEditorEntity_EntityType* type {  };
	string name {  };
	string description {  };
	string entityFileName {  };
	string fileName {  };
	string thumbnail {  };
	Model* model {  };
	Vector3 pivot {  };
	LevelEditorEntityLODLevel* lodLevel2;
	LevelEditorEntityLODLevel* lodLevel3;
	vector<LevelEditorEntityBoundingVolume*> boundingVolumes {  };
	LevelEditorEntityPhysics* physics {  };
	LevelEditorEntityParticleSystem* particleSystem {  };
	LevelEditorEntityModel* modelSettings;
	bool renderGroups {  };
	string shaderId {  };
	bool dynamicShadowing {  };
public:

	/** 
	 * @return id
	 */
	inline int32_t getId() {
		return id;
	}

	/** 
	 * @return entity type
	 */
	inline LevelEditorEntity_EntityType* getType() {
		return type;
	}

	/** 
	 * @return name
	 */
	inline const string& getName() {
		return name;
	}

	/** 
	 * Set up model name
	 * @param name name
	 */
	inline void setName(const string& name) {
		this->name = name;
	}

	/** 
	 * @return description
	 */
	inline const string& getDescription() {
		return description;
	}

	/** 
	 * Set up model description
	 * @param description description
	 */
	inline void setDescription(const string& description) {
		this->description = description;
	}

	/** 
	 * @return entity file name
	 */
	inline const string& getEntityFileName() {
		return entityFileName;
	}

	/** 
	 * Set entity file name
	 * @param entityFileName entity file name
	 */
	inline void setEntityFileName(const string& entityFileName) {
		this->entityFileName = entityFileName;
	}

	/** 
	 * @return file name
	 */
	inline const string& getFileName() {
		return fileName;
	}

	/** 
	 * @return thumbnail
	 */
	inline const string& getThumbnail() {
		return thumbnail;
	}

	/** 
	 * @return model
	 */
	inline Model* getModel() {
		return model;
	}

	/** 
	 * Set model
	 * @param model model
	 */
	inline void setModel(Model* model) {
		if (this->model != nullptr) delete this->model;
		this->model = model;
	}

	/**
	 * @return pivot
	 */
	inline Vector3& getPivot() {
		return pivot;
	}

	/** 
	 * @return bounding volume count
	 */
	inline int32_t getBoundingVolumeCount() {
		return boundingVolumes.size();
	}

	/** 
	 * Get bounding volume at
	 * @param idx idx
	 * @return level editor object bounding volume
	 */
	inline LevelEditorEntityBoundingVolume* getBoundingVolumeAt(int32_t idx) {
		return boundingVolumes[idx];
	}

	/** 
	 * Add bounding volume
	 * @param idx idx
	 * @param levelEditorEntityBoundingVolume level editor entity bounding volume
	 * @return level editor bounding volume
	 */
	bool addBoundingVolume(int32_t idx, LevelEditorEntityBoundingVolume* levelEditorEntityBoundingVolume);

	/** 
	 * Set default (up to 24) bounding volumes, to be used with LevelEditor
	 */
	void setDefaultBoundingVolumes();

	/**
	 * @return physics
	 */
	inline LevelEditorEntityPhysics* getPhysics() {
		return physics;
	}

	/**
	 * @return lod level 2
	 */
	inline LevelEditorEntityLODLevel* getLODLevel2() {
		return lodLevel2;
	}

	/**
	 * Set LOD level 2
	 * @param lodLevel lod level settings
	 */
	void setLODLevel2(LevelEditorEntityLODLevel* lodLevel);

	/**
	 * @return lod level 3
	 */
	inline LevelEditorEntityLODLevel* getLODLevel3() {
		return lodLevel3;
	}

	/**
	 * Set LOD level 3
	 * @param lodLevel lod level settings
	 */
	void setLODLevel3(LevelEditorEntityLODLevel* lodLevel);

	/** 
	 * @return level editor entity particle system
	 */
	inline LevelEditorEntityParticleSystem* getParticleSystem() {
		return particleSystem;
	}

	/**
	 * @return model settings
	 */
	inline LevelEditorEntityModel* getModelSettings() {
		return modelSettings;
	}

	/**
	 * Is dynamic shadowing
	 * @return dynamic shadowing enabled
	 */
	inline bool isDynamicShadowing() {
		return dynamicShadowing;
	}

	/**
	 * Set dynamic shadowing
	 * @param dynamicShadowing dynamic shadowing enabled
	 */
	inline void setDynamicShadowing(bool dynamicShadowing) {
		this->dynamicShadowing = dynamicShadowing;
	}

	/**
	 * Is using render groups
	 * @return render groups enabled
	 */
	inline bool isRenderGroups() {
		return renderGroups;
	}

	/**
	 * Set using render groups
	 * @param renderGroups use render groups
	 */
	inline void setRenderGroups(bool renderGroups) {
		this->renderGroups = renderGroups;
	}

	/**
	 * Get shader
	 * @return shader id
	 */
	inline const string& getShader() {
		return shaderId;
	}

	/**
	 * Set shader
	 * @param id shader id
	 */
	inline void setShader(const string& id) {
		this->shaderId = id;
	}

	/**
	 * Creates a level editor model
	 * @param id id
	 * @param entityType entity type
	 * @param name name
	 * @param description description
	 * @param entityFileName entity file name
	 * @param fileName file name
	 * @param thumbnail thumbnail
	 * @param model model
	 * @param pivot pivot
	 */
	LevelEditorEntity(int32_t id, LevelEditorEntity_EntityType* entityType, const string& name, const string& description, const string& entityFileName, const string& fileName, const string& thumbnail, Model* model, const Vector3& pivot);

	/**
	 * Destructor
	 */
	virtual ~LevelEditorEntity();
};
