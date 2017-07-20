// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorLevel.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/model/ModelProperties.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::tools::shared::model::ModelProperties;
using java::lang::Object;
using java::lang::String;
using java::util::Iterator;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLight;
using tdme::tools::shared::model::LevelEditorObject;

struct default_init_tag;

/** 
 * Level
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorLevel final
	: public ModelProperties
{

public:
	typedef ModelProperties super;

private:
	String* gameRoot {  };
	String* pathName {  };
	String* fileName {  };
	RotationOrder* rotationOrder {  };
	vector<LevelEditorLight*> lights {  };
	LevelEditorEntityLibrary* entityLibrary {  };
	map<wstring, LevelEditorObject*> objectsById {  };
	vector<LevelEditorObject*> objects {  };
	int32_t objectIdx {  };
	BoundingBox* boundingBox {  };
	Vector3* dimension {  };
protected:

	/** 
	 * Public constructor
	 * @param default map properties or null
	 */
	void ctor();

public:

	/** 
	 * @return game root
	 */
	String* getGameRoot();

	/** 
	 * Set game root
	 * @param gameRoot
	 */
	void setGameRoot(String* gameRoot);

	/** 
	 * @return path name
	 */
	String* getPathName();

	/** 
	 * Set up path name
	 * @param pathName
	 */
	void setPathName(String* pathName);

	/** 
	 * @return file name
	 */
	String* getFileName();

	/** 
	 * Set up level file name
	 * @param file name
	 */
	void setFileName(String* fileName);

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
	Vector3* getDimension();

	/** 
	 * Compute level dimension
	 */
	void computeDimension();

	/** 
	 * @return level bounding box
	 */
	BoundingBox* getBoundingBox();

	/** 
	 * Computes level bounding box
	 */
	void computeBoundingBox();

	/** 
	 * @return level center
	 */
	Vector3* computeCenter();

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
	void updatePivot(int32_t modelId, Vector3* pivot);

	/** 
	 * Adds an object to level
	 * @param object
	 */
	void addObject(LevelEditorObject* object);

	/** 
	 * Removes an object from level 
	 * @param id
	 */
	void removeObject(String* id);

	/** 
	 * Returns level editor object by id
	 * @param id
	 * @return level editor object or null
	 */
	LevelEditorObject* getObjectById(String* id);

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

	String* toString() override;

	// Generated
	LevelEditorLevel();
protected:
	LevelEditorLevel(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

public: /* protected */
	virtual Object* clone();

private:
	virtual ::java::lang::Class* getClass0();
};
