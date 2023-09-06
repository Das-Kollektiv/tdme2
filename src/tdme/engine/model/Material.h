#pragma once

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/math/Matrix3x3.h>

using std::string;
using std::unique_ptr;

using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::math::Matrix3x3;

/**
 * Represents a material
 * @author andreas.drewke
 */
class tdme::engine::model::Material final
{
private:
	STATIC_DLL_IMPEXT static string defaultMaterialId;
	STATIC_DLL_IMPEXT static unique_ptr<Material> defaultMaterial;

public:

	/**
	 * @return default material
	 */
	inline static Material* getDefaultMaterial() {
		return defaultMaterial.get();
	}

private:
	string id;
	unique_ptr<SpecularMaterialProperties> specularMaterialProperties;
	unique_ptr<PBRMaterialProperties> pbrMaterialProperties;
	bool doubleSided { false };
	Matrix3x3 textureMatrix;

public:
	// forbid class copy
	FORBID_CLASS_COPY(Material)

	/**
	 * Public constructor
	 * @param id id
	 */
	Material(const string& id);

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
		return specularMaterialProperties.get();
	}

	/**
	 * @return specular material properties
	 */
	inline SpecularMaterialProperties* getSpecularMaterialProperties() {
		return specularMaterialProperties.get();
	}

	/**
	 * @return PBR material properties
	 */
	inline const PBRMaterialProperties* getPBRMaterialProperties() const {
		return pbrMaterialProperties.get();
	}

	/**
	 * @return PBR material properties
	 */
	inline PBRMaterialProperties* getPBRMaterialProperties() {
		return pbrMaterialProperties.get();
	}

	/**
	 * Set specular material properties
	 * @param specularMaterialProperties specular material properties
	 */
	void setSpecularMaterialProperties(SpecularMaterialProperties* specularMaterialProperties);

	/**
	 * Set PBR material properties
	 * @param pbrMaterialProperties PBR material properties
	 */
	void setPBRMaterialProperties(PBRMaterialProperties* pbrMaterialProperties);

	/**
	 * @return is double sided
	 */
	inline bool isDoubleSided() const {
		return doubleSided;
	}

	/**
	 * Set double sided
	 * @param texture matrix
	 */
	inline void setDoubleSided(bool doubleSided) {
		this->doubleSided = doubleSided;
	}

	/**
	 * @return texture matrix
	 */
	inline const Matrix3x3& getTextureMatrix() const {
		return textureMatrix;
	}

	/**
	 * Set texture matrix
	 * @param textureMatrix texture matrix
	 */
	inline void setTextureMatrix(const Matrix3x3& textureMatrix) {
		this->textureMatrix = textureMatrix;
	}

};
