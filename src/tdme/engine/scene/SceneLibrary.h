#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/scenes/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::unordered_map;
using std::string;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
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
	unordered_map<int, Prototype*> prototypesById;
	vector<Prototype*> prototypes;
	int prototypeIdx;

public:
	// forbid class copy
	CLASS_FORBID_COPY(SceneLibrary)

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
	inline Prototype* getPrototype(int id) {
		auto prototypeByIdIt = prototypesById.find(id);
		if (prototypeByIdIt != prototypesById.end()) {
			return prototypeByIdIt->second;
		}
		return nullptr;
	}

	/**
	 * Get a prototype by given name
	 * @param name name
	 * @return prototype
	 */
	inline Prototype* getPrototypeByName(const string& name) {
		for (auto prototype: prototypes) {
			if (prototype->getName() == name) return prototype;
		}
		return nullptr;
	}

	/**
	 * Get a terrain prototype
	 * @return terrain prototype
	 */
	inline Prototype* getTerrainPrototype() {
		for (auto prototype: prototypes) {
			if (prototype->getType() == Prototype_Type::TERRAIN) return prototype;
		}
		return nullptr;
	}

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
