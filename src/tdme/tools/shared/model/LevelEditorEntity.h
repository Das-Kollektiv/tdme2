// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntity.java

#pragma once

#include <vector>
#include <string>

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/model/ModelProperties.h>

using std::vector;
using std::wstring;

using tdme::tools::shared::model::ModelProperties;
using tdme::engine::model::Model;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;

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
	typedef ModelProperties super;
	static constexpr int32_t ID_NONE { -1 };

public: /* protected */
	int32_t id {  };
	LevelEditorEntity_EntityType* type {  };
	wstring name {  };
	wstring description {  };
	wstring entityFileName {  };
	wstring fileName {  };
	wstring thumbnail {  };
	Model* model {  };
	Vector3 pivot {  };
	LevelEditorEntityParticleSystem* particleSystem {  };
	vector<LevelEditorEntityBoundingVolume*> boundingVolumes {  };

public:

	/** 
	 * @return id
	 */
	int32_t getId();

	/** 
	 * @return entity type
	 */
	LevelEditorEntity_EntityType* getType();

	/** 
	 * @return name
	 */
	const wstring& getName();

	/** 
	 * Set up model name
	 * @param name
	 */
	void setName(const wstring& name);

	/** 
	 * @return description
	 */
	const wstring& getDescription();

	/** 
	 * Set up model description
	 * @param description
	 */
	void setDescription(const wstring& description);

	/** 
	 * @return entity file name
	 */
	const wstring& getEntityFileName();

	/** 
	 * Set entity file name
	 * @param entity file name
	 */
	void setEntityFileName(const wstring& entityFileName);

	/** 
	 * @return file name
	 */
	const wstring& getFileName();

	/** 
	 * @return thumbnail
	 */
	const wstring& getThumbnail();

	/** 
	 * @return model
	 */
	Model* getModel();

public:

	/** 
	 * @return pivot
	 */
	Vector3* getPivot();

	/** 
	 * @return bounding volume count
	 */
	int32_t getBoundingVolumeCount();

	/** 
	 * Get bounding volume at
	 * @param idx
	 * @return level editor object bounding volume
	 */
	LevelEditorEntityBoundingVolume* getBoundingVolumeAt(int32_t idx);

	/** 
	 * Add bounding volume
	 * @param idx
	 * @param level editor entity bounding volume
	 * @return level editor bounding volume
	 */
	bool addBoundingVolume(int32_t idx, LevelEditorEntityBoundingVolume* levelEditorEntityBoundingVolume);

	/** 
	 * Set default (up to 8) bounding volumes, to be used with LevelEditor
	 */
	void setDefaultBoundingVolumes();

	/** 
	 * @return level editor entity particle system
	 */
	LevelEditorEntityParticleSystem* getParticleSystem();

	/**
	 * Creates a level editor model
	 * @param id
	 * @param entity type
	 * @param name
	 * @param description
	 * @param entity file name
	 * @param file name
	 * @param thumbnail
	 * @param model
	 * @param pivot
	 */
	LevelEditorEntity(int32_t id, LevelEditorEntity_EntityType* entityType, const wstring& name, const wstring& description, const wstring& entityFileName, const wstring& fileName, const wstring& thumbnail, Model* model, Vector3* pivot);
};
