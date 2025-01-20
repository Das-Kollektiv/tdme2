#pragma once

#include <memory>
#include <string>
#include <vector>

using std::make_unique;
using std::unique_ptr;

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/prototype/PrototypeTerrainBrushPrototype.h>
#include <tdme/utilities/UniquePtrSequenceIterator.h>

using std::string;
using std::vector;

using tdme::engine::prototype::PrototypeTerrainBrushPrototype;
using tdme::utilities::UniquePtrSequenceIterator;

/**
 * Prototype terrain brush prototype definition
 * @author Andreas Drewke
 */
class tdme::engine::prototype::PrototypeTerrainBrush final
{
private:
	float size { 1.0f };
	float density { 1.0f };
	string fileName { "resources/engine/textures/terrain_brush.png" };
	vector<unique_ptr<PrototypeTerrainBrushPrototype>> prototypes;

public:
	// forbid class copy
	FORBID_CLASS_COPY(PrototypeTerrainBrush)

	/**
	 * Public constructor
	 */
	inline PrototypeTerrainBrush() {
	}

	/**
	 * Destructor
	 */
	~PrototypeTerrainBrush() {
	}

	/**
	 * @returns size
	 */
	inline float getSize() const {
		return size;
	}

	/**
	 * Set size
	 * @param size size
	 */
	inline void setSize(float size) {
		this->size = size;
	}

	/**
	 * @returns density
	 */
	inline float getDensity() const {
		return density;
	}

	/**
	 * Set density
	 * @param density density
	 */
	inline void setDensity(float density){
		this->density = density;
	}

	/**
	 * @returns texture file name
	 */
	inline const string& getFileName() const {
		return fileName;
	}

	/**
	 * Set texture file name
	 * @param textureFileName texture file name
	 */
	void setFileName(const string &fileName) {
		this->fileName = fileName;
	}

	/**
	 * @returns Prototypes iterator
	 */
	inline UniquePtrSequenceIterator<PrototypeTerrainBrushPrototype> getPrototypes() {
		return UniquePtrSequenceIterator<PrototypeTerrainBrushPrototype>(&(*prototypes.begin()), &(*prototypes.end()));
	}

	/**
	 * Get prototype count
	 * @returns prototype count
	 */
	inline int getPrototypeCount() {
		return prototypes.size();
	}

	/**
	 * Get prototype terrain brush prototype
	 * @param idx index
	 * @returns prototype terrain brush prototype
	 */
	inline PrototypeTerrainBrushPrototype* getPrototype(int idx) {
		if (idx < 0 || idx >= prototypes.size()) return nullptr;
		return prototypes[idx].get();
	}

	/**
	 * Remove prototype terrain brush prototype
	 * @param idx index
	 */
	PrototypeTerrainBrushPrototype* addPrototype() {
		prototypes.push_back(make_unique<PrototypeTerrainBrushPrototype>());
		return prototypes[prototypes.size() - 1].get();
	}

	/**
	 * Remove prototype terrain brush prototype
	 * @param idx index
	 */
	bool removePrototype(int idx) {
		if (idx < 0 || idx >= prototypes.size()) return false;
		prototypes.erase(prototypes.begin() + idx);
		return true;
	}

};
