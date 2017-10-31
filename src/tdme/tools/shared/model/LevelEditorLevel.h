
#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/model/ModelProperties.h>

using std::map;
using std::vector;
using std::string;

using tdme::tools::shared::model::ModelProperties;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLight;
using tdme::tools::shared::model::LevelEditorObject;

/** 
 * Level
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorLevel final
	: public ModelProperties
{
private:
	string gameRoot {  };
	string pathName {  };
	string fileName {  };
	RotationOrder* rotationOrder {  };
	vector<LevelEditorLight*> lights {  };
	LevelEditorEntityLibrary* entityLibrary {  };
	map<string, LevelEditorObject*> objectsById {  };
	vector<LevelEditorObject*> objects {  };
	int32_t objectIdx {  };
	BoundingBox boundingBox {  };
	Vector3 dimension;
	Vector3 center;

	/**
	 * Computes level bounding box
	 * @return dimension
	 */
	void computeBoundingBox();

	/**
	 * @return level center
	 */
	void computeCenter();

public:

	/** 
	 * @return game root
	 */
	const string& getGameRoot();

	/** 
	 * Set game root
	 * @param gameRoot
	 */
	void setGameRoot(const string& gameRoot);

	/** 
	 * @return path name
	 */
	const string& getPathName();

	/** 
	 * Set up path name
	 * @param pathName
	 */
	void setPathName(const string& pathName);

	/** 
	 * @return file name
	 */
	const string& getFileName();

	/** 
	 * Set up level file name
	 * @param file name
	 */
	void setFileName(const string& fileName);

	/** 
	 * @return rotation order
	 */
	RotationOrder* getRotationOrder();

	/** 
	 * Set rotation order
	 * @param rotation order
	 */
	void setRotationOrder(RotationOrder* rotationOrder);

	/** 
	 * @return number of lights
	 */
	int32_t getLightCount();

	/** 
	 * Get light at index i
	 * @param i
	 * @return
	 */
	LevelEditorLight* getLightAt(int32_t i);

	/** 
	 * @return entity library
	 */
	LevelEditorEntityLibrary* getEntityLibrary();

	/** 
	 * @return dimension
	 */
	const Vector3& getDimension();

	/** 
	 * @return level bounding box
	 */
	BoundingBox* getBoundingBox();

	/** 
	 * @return level center
	 */
	const Vector3& getCenter();

	/**
	 * @return new object idx
	 */
	int32_t allocateObjectId();

	/** 
	 * @return object idx
	 */
	int32_t getObjectIdx();

	/** 
	 * Set entity idx
	 * @param objectIdx
	 */
	void setObjectIdx(int32_t entityIdx);

	/** 
	 * Clears all level objects
	 */
	void clearObjects();

	/** 
	 * Remove objects with given entity id
	 * @param entity id
	 */
	void removeObjectsByEntityId(int32_t entityId);

	/** 
	 * Replace entity
	 * @param search model id
	 * @param replace model id 
	 */
	void replaceEntity(int32_t searchEntityId, int32_t replaceEntityId);

	/** 
	 * Updates pivot
	 * @param model id
	 */
	void updatePivot(int32_t modelId, const Vector3& pivot);

	/** 
	 * Adds an object to level
	 * @param object
	 */
	void addObject(LevelEditorObject* object);

	/** 
	 * Removes an object from level 
	 * @param id
	 */
	void removeObject(const string& id);

	/** 
	 * Returns level editor object by id
	 * @param id
	 * @return level editor object or null
	 */
	LevelEditorObject* getObjectById(const string& id);

	/** 
	 * @return number of objects
	 */
	int32_t getObjectCount();

	/** 
	 * Returns object at idx  
	 * @param idx
	 * @return level object
	 */
	LevelEditorObject* getObjectAt(int32_t idx);

	/**
	 * Update level dimension, bounding box, center
	 */
	void update();

	/**
	 * Public constructor
	 * @param default map properties or null
	 */
	LevelEditorLevel();

	/**
	 * Destructor
	 */
	virtual ~LevelEditorLevel();
};
