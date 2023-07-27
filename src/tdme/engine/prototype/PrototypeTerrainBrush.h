#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/prototype/PrototypeTerrainBrushPrototype.h>

using std::string;
using std::vector;

using tdme::engine::prototype::PrototypeTerrainBrushPrototype;

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
	vector<PrototypeTerrainBrushPrototype*> prototypes;

public:
	// forbid class copy
	CLASS_FORBID_COPY(PrototypeTerrainBrush)

	/**
	 * Public constructor
	 */
	inline PrototypeTerrainBrush() {
	}

	/**
	 * Destructor
	 */
	~PrototypeTerrainBrush() {
		for (auto prototype: prototypes) delete prototype;
	}

	/**
	 * @return size
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
	 * @return density
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
	 * @return texture file name
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
	 * @return prototypes
	 */
	inline const vector<PrototypeTerrainBrushPrototype*>& getPrototypes() const {
		return prototypes;
	}

	/**
	 * Get prototype terrain brush prototype
	 * @param idx index
	 * @return prototype terrain brush prototype
	 */
	inline PrototypeTerrainBrushPrototype* getPrototype(int idx) {
		if (idx < 0 || idx >= prototypes.size()) return nullptr;
		return prototypes[idx];
	}

	/**
	 * Remove prototype terrain brush prototype
	 * @param idx index
	 */
	PrototypeTerrainBrushPrototype* addPrototype() {
		auto prototype = new PrototypeTerrainBrushPrototype();
		prototypes.push_back(prototype);
		return prototype;
	}

	/**
	 * Remove prototype terrain brush prototype
	 * @param idx index
	 */
	bool removePrototype(int idx) {
		if (idx < 0 || idx >= prototypes.size()) return false;
		auto prototype = prototypes[idx];
		prototypes.erase(prototypes.begin() + idx);
		delete prototype;
		return true;
	}

};
