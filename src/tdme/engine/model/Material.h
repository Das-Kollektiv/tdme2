#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>

using std::string;

using tdme::engine::model::SpecularMaterialProperties;
using tdme::math::Matrix2D3x3;

/** 
 * Represents a material
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::Material final
{
private:
	static string defaultMaterialId;
	static Material* defaultMaterial;

public:

	/** 
	 * @return default material
	 */
	inline static Material* getDefaultMaterial() {
		return defaultMaterial;
	}

private:
	string id;
	SpecularMaterialProperties* specularMaterialProperties { nullptr };
	Matrix2D3x3 textureMatrix;

public:

	/** 
	 * @return material id
	 */
	inline const string& getId() const {
		return id;
	}

	/**
	 * @return specular material properties
	 */
	inline const SpecularMaterialProperties* getSpecularMaterialProperties() const {
		return specularMaterialProperties;
	}

	/**
	 * @return specular material properties
	 */
	inline SpecularMaterialProperties* getSpecularMaterialProperties() {
		return specularMaterialProperties;
	}

	/**
	 * Set specular material properties
	 * @param specularMaterialProperties specular material properties
	 */
	void setSpecularMaterialProperties(SpecularMaterialProperties* specularMaterialProperties);

	/**
	 * @return texture matrix
	 */
	inline const Matrix2D3x3& getTextureMatrix() const {
		return textureMatrix;
	}

	/**
	 * Set texture matrix
	 * @param texture matrix
	 */
	inline void setTextureMatrix(const Matrix2D3x3& textureMatrix) {
		this->textureMatrix = textureMatrix;
	}

	/**
	 * Public constructor
	 * @param id id
	 */
	Material(const string& id);

	/**
	 * Destructor
	 */
	~Material();
};
