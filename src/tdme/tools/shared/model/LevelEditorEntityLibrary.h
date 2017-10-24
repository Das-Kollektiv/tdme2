
#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorLevel;

/** 
 * Model Editor Entity Library
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityLibrary final
{
public:
	static constexpr int32_t ID_ALLOCATE { -1 };

private:
	LevelEditorLevel* level {  };
	map<int32_t, LevelEditorEntity*> entitiesById {  };
	vector<LevelEditorEntity*> entities {  };
	int32_t entityIdx {  };

public:

	/** 
	 * Clears this model library
	 */
	void clear();

private:

	/** 
	 * Allocata a unique entity idx
	 * @return
	 */
	int32_t allocateEntityId();

public:

	/** 
	 * Adds a model
	 * @param id
	 * @param name
	 * @param description
	 * @param path name
	 * @param file name
	 * @param pivot
	 * @return level editor entity
	 * @throws Exception
	 */
	LevelEditorEntity* addModel(int32_t id, const wstring& name, const wstring& description, const wstring& pathName, const wstring& fileName, const Vector3& pivot) /* throws(Exception) */;

	/** 
	 * Add a trigger
	 * @param name
	 * @param description
	 * @param width
	 * @param height
	 * @param depth
	 * @return level editor entity
	 * @throws Exception
	 */
	LevelEditorEntity* addTrigger(int32_t id, const wstring& name, const wstring& description, float width, float height, float depth) /* throws(Exception) */;

	/** 
	 * Add a empty
	 * @param name
	 * @param description
	 * @return level editor entity
	 * @throws Exception
	 */
	LevelEditorEntity* addEmpty(int32_t id, const wstring& name, const wstring& description) /* throws(Exception) */;

	/** 
	 * Add a empty
	 * @param name
	 * @param description
	 * @return level editor entity
	 * @throws Exception
	 */
	LevelEditorEntity* addParticleSystem(int32_t id, const wstring& name, const wstring& description) /* throws(Exception) */;

	/** 
	 * Add a entity
	 * @param model
	 */
	void addEntity(LevelEditorEntity* levelEditorEntity) /* throws(Exception) */;

	/** 
	 * @param idx
	 * @return entity 
	 */
	LevelEditorEntity* getEntityAt(int32_t idx);

	/** 
	 * Retrieve a entity
	 * @param id
	 * @return level editor entity
	 */
	LevelEditorEntity* getEntity(int32_t id);

	/** 
	 * Remove a entity
	 * @param id
	 */
	void removeEntity(int32_t id);

	/** 
	 * @return entity count 
	 */
	int32_t getEntityCount();

	/**
	 * Public constructor
	 */
	LevelEditorEntityLibrary(LevelEditorLevel* level);

	/**
	 * Destructor
	 */
	~LevelEditorEntityLibrary();
};
