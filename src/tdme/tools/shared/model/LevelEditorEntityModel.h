
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;

using tdme::tools::shared::model::LevelEditorEntity;

/** 
 * Level editor model properties
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityModel
{
private:
	LevelEditorEntity* entity;
	bool terrainMesh;

public:

	/**
	 * @return entity
	 */
	LevelEditorEntity* getEntity();

	/**
	 * Is terrain mesh
	 * @return terrain mesh
	 */
	bool isTerrainMesh();

	/**
	 * Set terrain mesh
	 */
	void setTerrainMesh(bool terrainMesh);

	/**
	 * Public constructor
	 * @param levelEditorEntity level editor entity
	 */
	LevelEditorEntityModel(LevelEditorEntity* levelEditorEntity);

	/**
	 * Destructor
	 */
	~LevelEditorEntityModel();

};
