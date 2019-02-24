#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::map;
using std::string;
using std::vector;

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
	bool terrainMesh { false };

public:

	/**
	 * @return entity
	 */
	inline LevelEditorEntity* getEntity() {
		return entity;
	}

	/**
	 * Is terrain mesh
	 * @return terrain mesh
	 */
	inline bool isTerrainMesh() {
		return terrainMesh;
	}

	/**
	 * Set terrain mesh
	 * @param terrainMesh terrain mesh
	 */
	inline void setTerrainMesh(bool terrainMesh) {
		this->terrainMesh = terrainMesh;
	}

	/**
	 * Public constructor
	 * @param levelEditorEntity level editor entity
	 */
	LevelEditorEntityModel(LevelEditorEntity* entity): entity(entity) {
	}

	/**
	 * Destructor
	 */
	~LevelEditorEntityModel();

};
