#pragma once

#include <string>

#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/model/Model.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;

using tdme::engine::LODObject3D;
using tdme::engine::model::Model;

/** 
 * Level Editor Entity LOD Level
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityLODLevel final
{
private:
	LODObject3D::LODLevelType type { LODObject3D::LODLEVELTYPE_NONE };
	string fileName {  };
	Model* model {  };
	float minDistance { 0.0f };
	float planeRotationY { 0.0f };

public:
	/**
	 * Public constructor
	 * @param file name
	 * @param model
	 * @param min distance
	 * @param type
	 * @param plane rotation y
	 */
	LevelEditorEntityLODLevel(
		LODObject3D::LODLevelType type,
		const string& fileName,
		Model* model,
		float minDistance,
		float planeRotationY
	);

	/**
	 * Destructor
	 */
	~LevelEditorEntityLODLevel();

	/**
	 * @return type
	 */
	LODObject3D::LODLevelType getType() const;

	/**
	 * Set type
	 * @param type
	 */
	void setType(LODObject3D::LODLevelType type);

	/**
	 * @return file name
	 */
	const string& getFileName();

	/**
	 * Set file name
	 * @param file name
	 */
	void setFileName(const string& fileName);

	/**
	 * @return model
	 */
	Model* getModel();

	/**
	 * Set model
	 * @param model
	 */
	void setModel(Model* model);

	/**
	 * @return min distance
	 */
	float getMinDistance() const;

	/**
	 * Set min distance
	 * @param min distance
	 */
	void setMinDistance(float minDistance);

	/**
	 * @return plane rotation y
	 */
	float getPlaneRotationY() const;

	/**
	 * Set plane rotation y
	 * @param plane rotation y
	 */
	void setPlaneRotationY(float planeRotationY);

};
