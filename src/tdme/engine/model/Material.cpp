#include <tdme/engine/model/Material.h>

#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>

#include <string>

using std::string;

using tdme::engine::model::Material;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::SpecularMaterialProperties;

Material::Material(const string& id)
{
	this->id = id;
	this->textureMatrix.identity();
	this->specularMaterialProperties = new SpecularMaterialProperties();
}

void Material::setSpecularMaterialProperties(SpecularMaterialProperties* specularMaterialProperties) {
	if (this->specularMaterialProperties != nullptr && this->specularMaterialProperties != specularMaterialProperties) {
		delete this->specularMaterialProperties;
	}
	this->specularMaterialProperties = specularMaterialProperties;
}

void Material::setPBRMaterialProperties(PBRMaterialProperties* pbrMaterialProperties) {
	if (this->pbrMaterialProperties != nullptr && this->pbrMaterialProperties != pbrMaterialProperties) {
		delete this->pbrMaterialProperties;
	}
	this->pbrMaterialProperties = pbrMaterialProperties;
}

Material::~Material() {
	if (this->specularMaterialProperties != nullptr) delete this->specularMaterialProperties;
	if (this->pbrMaterialProperties != nullptr) delete this->pbrMaterialProperties;
}

string Material::defaultMaterialId = "tdme.default_material";
Material* Material::defaultMaterial = new Material(Material::defaultMaterialId);
