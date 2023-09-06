#pragma once

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/LODObject.h>

using std::string;
using std::unique_ptr;

using tdme::engine::Color4;
using tdme::engine::model::Model;
using tdme::engine::LODObject;

/**
 * Prototype LOD level definition
 * @author Andreas Drewke
 */
class tdme::engine::prototype::PrototypeLODLevel final
{
private:
	LODObject::LODLevelType type;
	string fileName;
	unique_ptr<Model> model;
	float minDistance;
	Color4 colorMul;
	Color4 colorAdd;

public:
	// forbid class copy
	FORBID_CLASS_COPY(PrototypeLODLevel)

	/**
	 * Public constructor
	 * @param type file name
	 * @param fileName model
	 * @param model min distance
	 * @param minDistance type
	 */
	PrototypeLODLevel(
		LODObject::LODLevelType type,
		const string& fileName,
		Model* model,
		float minDistance
	);

	/**
	 * Destructor
	 */
	~PrototypeLODLevel();

	/**
	 * @return type
	 */
	inline LODObject::LODLevelType getType() const {
		return type;
	}

	/**
	 * Set type
	 * @param type type
	 */
	inline void setType(LODObject::LODLevelType type) {
		this->type = type;
	}

	/**
	 * @return file name
	 */
	inline const string& getFileName() {
		return fileName;
	}

	/**
	 * Set file name
	 * @param fileName file name
	 */
	inline void setFileName(const string& fileName) {
		this->fileName = fileName;
	}

	/**
	 * @return model
	 */
	inline Model* getModel() {
		return model.get();
	}

	/**
	 * Set model
	 * @param model model
	 */
	inline void setModel(Model* model) {
		this->model = unique_ptr<Model>(model);
	}

	/**
	 * @return min distance
	 */
	inline float getMinDistance() const {
		return minDistance;
	}

	/**
	 * Set min distance
	 * @param minDistance min distance
	 */
	inline void setMinDistance(float minDistance) {
		this->minDistance = minDistance;
	}

	/**
	 * @return color add
	 */
	inline const Color4& getColorAdd() const {
		return colorAdd;
	}

	/**
	 * Set color add
	 * @param colorAdd color add
	 */
	inline void setColorAdd(const Color4& colorAdd) {
		this->colorAdd = colorAdd;
	}

	/**
	 * @return color mul
	 */
	inline const Color4& getColorMul() const {
		return colorMul;
	}

	/**
	 * Set color mul
	 * @param colorMul color mul
	 */
	inline void setColorMul(const Color4& colorMul) {
		this->colorMul = colorMul;
	}

};
