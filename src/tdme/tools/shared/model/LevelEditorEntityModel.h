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
using tdme::tools::shared::model::LevelEditorEntityAudio;

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
	map<string, LevelEditorEntityAudio*> animationSoundsById;
	vector<LevelEditorEntityAudio*> animationSounds;

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
	 * Get animation sounds
	 * @return level editor entity audio entities
	 */
	vector<LevelEditorEntityAudio*>& getAnimationSounds() {
		return animationSounds;
	}

	/**
	 * Rename animation sound
	 * @param animation animation
	 * @param newAnimationName new animation name
	 */
	void renameAnimationSound(const string& animation, const string& newAnimationName);

	/**
	 * Create animation sound
	 * @param animation animation
	 * @return level editor entity audio
	 */
	LevelEditorEntityAudio* createAnimationSound(const string& animation);

	/**
	 * Get animation sound
	 * @param animation animation
	 * @return level editor entity audio or nullptr
	 */
	LevelEditorEntityAudio* getAnimationSound(const string& animation);

	/**
	 * Remove animation sound
	 * @param animation animation
	 */
	void removeAnimationSound(const string& animation);

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
