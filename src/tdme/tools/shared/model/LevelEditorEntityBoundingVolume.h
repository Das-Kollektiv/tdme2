
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;

using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntity;

/** 
 * Level Editor Entity Bouning Volume
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityBoundingVolume
{
private:
	volatile static uint32_t modelIdx;
	int32_t id {  };
	LevelEditorEntity* levelEditorEntity {  };
	string modelMeshFile {  };
	Model* model {  };
	BoundingVolume* boundingVolume {  };

public:

	/** 
	 * @return id
	 */
	int32_t getId();

	/** 
	 * @return level editor entity
	 */
	LevelEditorEntity* getLevelEditorEntity();

	/** 
	 * @return model mesh file
	 */
	const string& getModelMeshFile();

	/** 
	 * @return model
	 */
	Model* getModel();

	/** 
	 * @return bounding volume
	 */
	BoundingVolume* getBoundingVolume();

	/**
	 * @return bounding volume model index
	 */
	int32_t allocateModelIdx();

	/** 
	 * Setup bounding volume none
	 */
	void setupNone();

	/** 
	 * Setup bounding volume sphere
	 * @param center center
	 * @param radius radius
	 */
	void setupSphere(const Vector3& center, float radius);

	/** 
	 * Setup bounding volume capsule
	 * @param a a
	 * @param b b
	 * @param radius radius
	 */
	void setupCapsule(const Vector3& a, const Vector3& b, float radius);

	/** 
	 * Setup bounding volume oriented bounding box
	 * @param center center
	 * @param axis0 axis 0
	 * @param axis1 axis 1
	 * @param axis2 axis 2
	 * @param halfExtension half extension
	 */
	void setupObb(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension);

	/** 
	 * Setup bounding volume bounding box
	 * @param min min
	 * @param max max
	 */
	void setupAabb(const Vector3& min, const Vector3& max);

	/** 
	 * Setup bounding volume sphere
	 * @param pathName path name
	 * @param fileName file name
	 */
	void setupConvexMesh(const string& pathName, const string& fileName);

private:

	/** 
	 * Update level editor entity
	 */
	void updateLevelEditorEntity();

public:
	/**
	 * Public constructor
	 * @param id id
	 * @param levelEditorEntity level editor entity
	 */
	LevelEditorEntityBoundingVolume(int32_t id, LevelEditorEntity* levelEditorEntity);

	/**
	 * Destructor
	 */
	~LevelEditorEntityBoundingVolume();

};
