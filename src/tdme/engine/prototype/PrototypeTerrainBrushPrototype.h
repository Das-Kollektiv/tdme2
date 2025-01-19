#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>

using std::string;

/**
 * Prototype terrain brush prototype definition
 * @author Andreas Drewke
 */
class tdme::engine::prototype::PrototypeTerrainBrushPrototype final
{
private:
	string fileName;
	float count { 1.0f };
	bool normalAlign { false };
	float rotationXMin { -5.0f };
	float rotationXMax { 5.0f };
	float rotationYMin { 0.0f };
	float rotationYMax { 360.0f };
	float rotationZMin { -5.0f };
	float rotationZMax { 5.0f };
	float scaleMin { 0.8f };
	float scaleMax { 1.2f };
	float heightMin { 0.0f };
	float heightMax { 100.0f };
	float slopeMin { 0.0f };
	float slopeMax { 30.0f };

public:
	// forbid class copy
	FORBID_CLASS_COPY(PrototypeTerrainBrushPrototype)

	/**
	 * Public constructor
	 */
	inline PrototypeTerrainBrushPrototype() {
	}

	/**
	 * Destructor
	 */
	~PrototypeTerrainBrushPrototype() {
	}

	/**
	 * @returns prototype file name
	 */
	const string& getFileName() const {
		return fileName;
	}

	/**
	 * Set prototype file name
	 * @param fileName file name
	 */
	void setFileName(const string &fileName) {
		this->fileName = fileName;
	}

	/**
	 * @returns count
	 */
	float getCount() const {
		return count;
	}

	/**
	 * Set count
	 * @param count count
	 */
	void setCount(float count) {
		this->count = count;
	}

	/**
	 * @returns align to normal
	 */
	bool isNormalAlign() const {
		return normalAlign;
	}

	/**
	 * Set align to normal
	 * @param normalAlign normal align
	 */
	void setNormalAlign(bool normalAlign) {
		this->normalAlign = normalAlign;
	}

	/**
	 * @returns rotation x min
	 */
	float getRotationXMin() const {
		return rotationXMin;
	}

	/**
	 * Set rotation x min
	 * @param rotationXMin rotation x min
	 */
	void setRotationXMin(float rotationXMin) {
		this->rotationXMin = rotationXMin;
	}

	/**
	 * @returns rotation x max
	 */
	float getRotationXMax() const {
		return rotationXMax;
	}

	/**
	 * Set rotation x max
	 * @param rotationXMax rotation x max
	 */
	void setRotationXMax(float rotationXMax) {
		this->rotationXMax = rotationXMax;
	}

	/**
	 * @returns rotation y min
	 */
	float getRotationYMin() const {
		return rotationYMin;
	}

	/**
	 * Set rotation y min
	 * @param rotationYMin rotation Y min
	 */
	void setRotationYMin(float rotationYMin) {
		this->rotationYMin = rotationYMin;
	}

	/**
	 * @returns rotation y max
	 */
	float getRotationYMax() const {
		return rotationYMax;
	}

	/**
	 * Set rotation y max
	 * @param rotationYMax rotation y max
	 */
	void setRotationYMax(float rotationYMax) {
		this->rotationYMax = rotationYMax;
	}

	/**
	 * @returns rotation z min
	 */
	float getRotationZMin() const {
		return rotationZMin;
	}

	/**
	 * Set rotation z min
	 * @param rotationZMin rotation Z min
	 */
	void setRotationZMin(float rotationZMin) {
		this->rotationZMin = rotationZMin;
	}

	/**
	 * @returns rotation z max
	 */
	float getRotationZMax() const {
		return rotationZMax;
	}

	/**
	 * Set rotation z max
	 * @param rotationZMax rotation z max
	 */
	void setRotationZMax(float rotationZMax) {
		this->rotationZMax = rotationZMax;
	}

	/**
	 * @returns scale min
	 */
	float getScaleMin() const {
		return scaleMin;
	}

	/**
	 * Set scale min
	 * @param scaleMin scale min
	 */
	void setScaleMin(float scaleMin) {
		this->scaleMin = scaleMin;
	}

	/**
	 * @returns scale max
	 */
	float getScaleMax() const {
		return scaleMax;
	}

	/**
	 * Set scale max
	 * @param scaleMax scale max
	 */
	void setScaleMax(float scaleMax) {
		this->scaleMax = scaleMax;
	}

	/**
	 * @returns height min
	 */
	float getHeightMin() const {
		return heightMin;
	}

	/**
	 * Set height min
	 * @param heightMin height min
	 */
	void setHeightMin(float heightMin) {
		this->heightMin = heightMin;
	}

	/**
	 * @returns height max
	 */
	float getHeightMax() const {
		return heightMax;
	}

	/**
	 * Set height max
	 * @param heightMax height max
	 */
	void setHeightMax(float heightMax) {
		this->heightMax = heightMax;
	}

	/**
	 * @returns slope min
	 */
	float getSlopeMin() const {
		return slopeMin;
	}

	/**
	 * Set slope min
	 * @param slopeMin slope min
	 */
	void setSlopeMin(float slopeMin) {
		this->slopeMin = slopeMin;
	}

	/**
	 * @returns slope max
	 */
	float getSlopeMax() const {
		return slopeMax;
	}

	/**
	 * Set slope max
	 * @param slopeMax slope max
	 */
	void setSlopeMax(float slopeMax) {
		this->slopeMax = slopeMax;
	}

};
