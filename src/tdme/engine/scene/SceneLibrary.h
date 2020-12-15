#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::map;
using std::vector;
using std::string;

using tdme::math::Vector3;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;

/**
 * Model Editor Entity Library
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::scene::SceneLibrary final
{
public:
	static constexpr int ID_ALLOCATE { -1 };

private:
	Scene* level { nullptr };
	map<int, Prototype*> entitiesById;
	vector<Prototype*> entities;
	int entityIdx;

	/**
	 * Allocata a unique entity idx
	 * @return
	 */
	int allocateEntityId();

public:
	/**
	 * Public constructor
	 */
	SceneLibrary(Scene* level);

	/**
	 * Destructor
	 */
	~SceneLibrary();

	/**
	 * Clears this model library
	 */
	void clear();

	/**
	 * Adds a model
	 * @param id id
	 * @param name name
	 * @param description description
	 * @param pathName path name
	 * @param fileName file name
	 * @param pivot pivot
	 * @return level editor entity
	 * @throws tdme::utilities::Exception
	 */
	Prototype* addModel(int id, const string& name, const string& description, const string& pathName, const string& fileName, const Vector3& pivot);

	/**
	 * Add a trigger
	 * @param id id
	 * @param name name
	 * @param description description
	 * @param width width
	 * @param height height
	 * @param depth depth
	 * @return level editor entity
	 * @throws tdme::utilities::Exception
	 */
	Prototype* addTrigger(int id, const string& name, const string& description, float width, float height, float depth);

	/**
	 * Add a environment mapping
	 * @param id id
	 * @param name name
	 * @param description description
	 * @param width width
	 * @param height height
	 * @param depth depth
	 * @return level editor entity
	 * @throws tdme::utilities::Exception
	 */
	Prototype* addEnvironmentMapping(int id, const string& name, const string& description, float width, float height, float depth);

	/**
	 * Add a empty
	 * @param id id
	 * @param name name
	 * @param description description
	 * @return level editor entity
	 * @throws tdme::utilities::Exception
	 */
	Prototype* addEmpty(int id, const string& name, const string& description);

	/**
	 * Add a empty
	 * @param id id
	 * @param name name
	 * @param description description
	 * @return level editor entity
	 * @throws tdme::utilities::Exception
	 */
	Prototype* addParticleSystem(int id, const string& name, const string& description);

	/**
	 * Add a entity
	 * @param levelEditorEntity model
	 */
	void addEntity(Prototype* levelEditorEntity);

	/**
	 * @param idx idx
	 * @return entity
	 */
	Prototype* getEntityAt(int idx);

	/**
	 * Retrieve a entity
	 * @param id id
	 * @return level editor entity
	 */
	Prototype* getEntity(int id);

	/**
	 * Remove a entity
	 * @param id id
	 */
	void removeEntity(int id);

	/**
	 * @return entity count
	 */
	int getEntityCount();

};
