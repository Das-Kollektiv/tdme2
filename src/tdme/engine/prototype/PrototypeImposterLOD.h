#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/prototype/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::engine::Color4;
using tdme::engine::model::Model;

/**
 * Prototype imposter LOD
 * @author Andreas Drewke
 */
class tdme::engine::prototype::PrototypeImposterLOD final
{
private:
	vector<string> fileNames;
	vector<Model*> models;
	float minDistance;
	Color4 colorMul;
	Color4 colorAdd;

public:
	// forbid class copy
	FORBID_CLASS_COPY(PrototypeImposterLOD)

	/**
	 * Public constructor
	 * @param fileNames file names
	 * @param models models
	 * @param minDistance type
	 */
	PrototypeImposterLOD(
		const vector<string>& fileNames,
		const vector<Model*>& models,
		float minDistance
	);

	/**
	 * Destructor
	 */
	~PrototypeImposterLOD();

	/**
	 * @return file name
	 */
	inline const vector<string>& getFileNames() {
		return fileNames;
	}

	/**
	 * Set file names
	 * @param fileNames file names
	 */
	inline void setFileNames(const vector<string>& fileNames) {
		this->fileNames = fileNames;
	}

	/**
	 * @return model
	 */
	inline const vector<Model*>& getModels() {
		return models;
	}

	/**
	 * Set model
	 * @param model model
	 */
	inline void setModels(const vector<Model*>& models) {
		this->models.resize(models.size());
		for (auto i = 0; i < models.size(); i++) {
			if (i < this->models.size() && this->models[i] == models[i]) continue;
			if (i < this->models.size() && this->models[i] != nullptr) delete this->models[i];
			this->models[i] = models[i];
		}
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
