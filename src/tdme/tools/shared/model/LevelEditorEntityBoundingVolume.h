
#pragma once

#include <string>

#include <tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::wstring;

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
	static int32_t staticIdx;
	int32_t id {  };
	LevelEditorEntity* levelEditorEntity {  };
	wstring modelMeshFile {  };
	Model* model {  };
	BoundingVolume* boundingVolume {  };

public:

	/** 
	 * @return id
	 */
	virtual int32_t getId();

	/** 
	 * @return level editor entity
	 */
	virtual LevelEditorEntity* getLevelEditorEntity();

	/** 
	 * @return model mesh file
	 */
	virtual const wstring& getModelMeshFile();

	/** 
	 * @return model
	 */
	virtual Model* getModel();

	/** 
	 * @return bounding volume
	 */
	virtual BoundingVolume* getBoundingVolume();

	/** 
	 * Setup bounding volume none
	 * @param idx
	 */
	virtual void setupNone();

	/** 
	 * Setup bounding volume sphere
	 * @param center
	 * @param radius
	 */
	virtual void setupSphere(const Vector3& center, float radius);

	/** 
	 * Setup bounding volume capsule
	 * @param a
	 * @param b
	 * @param radius
	 */
	virtual void setupCapsule(const Vector3& a, const Vector3& b, float radius);

	/** 
	 * Setup bounding volume oriented bounding box
	 * @param center
	 * @param axis 0
	 * @param axis 1
	 * @param axis 2
	 * @param half extension
	 */
	virtual void setupObb(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension);

	/** 
	 * Setup bounding volume bounding box
	 * @param min
	 * @param max
	 */
	virtual void setupAabb(const Vector3& min, const Vector3& max);

	/** 
	 * Setup bounding volume sphere
	 * @param path name
	 * @param file name
	 */
	virtual void setupConvexMesh(const wstring& pathName, const wstring& fileName);

private:

	/** 
	 * Update level editor entity
	 */
	void updateLevelEditorEntity();

public:
	/**
	 * Public constructor
	 * @param id
	 * @param level editor entity
	 */
	LevelEditorEntityBoundingVolume(int32_t id, LevelEditorEntity* levelEditorEntity);

	/**
	 * Destructor
	 */
	virtual ~LevelEditorEntityBoundingVolume();

};
