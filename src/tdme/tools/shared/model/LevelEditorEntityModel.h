
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
	bool maskedTransparency;

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
	 * Is masked transparency
	 * @return masked transparency
	 */
	bool isMaskedTransparency();

	/**
	 * Set masked transparency
	 * @param dynamic shadowing enabled
	 */
	void setMaskedTransparency(bool maskedTransparency);

	/**
	 * Public constructor
	 * @param level editor entity
	 */
	LevelEditorEntityModel(LevelEditorEntity* levelEditorEntity);

	/**
	 * Destructor
	 */
	~LevelEditorEntityModel();

};
