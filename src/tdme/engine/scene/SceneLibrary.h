#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/scenes/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::math::Vector3;

/**
 * Scene prototype library definition
 * @author Andreas Drewke
 */
class tdme::engine::scene::SceneLibrary final
{
public:
	static constexpr int ID_ALLOCATE { -1 };

private:
	Scene* scene { nullptr };
	map<int, Prototype*> prototypesById;
	vector<Prototype*> prototypes;
	int prototypeIdx;

public:
	/**
	 * Public constructor
	 * @param scene scene
	 */
	SceneLibrary(Scene* scene);

	/**
	 * Destructor
	 */
	~SceneLibrary();

	/**
	 * Allocata a unique prototype index
	 * @return index
	 */
	inline int allocatePrototypeId() {
		return prototypeIdx++;
	}

	/**
	 * Clears this scene prototype library
	 */
	void clear();

	/**
	 * Add a prototype
	 * @param prototype prototype
	 */
	void addPrototype(Prototype* prototype);

	/**
	 * Get prototype at given index
	 * @param idx index
	 * @return prototype
	 */
	inline Prototype* getPrototypeAt(int idx) {
		return prototypes[idx];
	}

	/**
	 * Get a prototype by given id
	 * @param id id
	 * @return prototype
	 */
	Prototype* getPrototype(int id);

	/**
	 * Get a prototype by given name
	 * @param name name
	 * @return prototype
	 */
	Prototype* getPrototypeByName(const string& name);

	/**
	 * Get a terrain prototype
	 * @return terrain prototype
	 */
	Prototype* getTerrainPrototype();

	/**
	 * Remove a prototype
	 * @param id id
	 */
	void removePrototype(int id);

	/**
	 * @return prototype count
	 */
	inline int getPrototypeCount() {
		return prototypes.size();
	}

};
