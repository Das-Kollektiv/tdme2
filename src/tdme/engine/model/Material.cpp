#include <tdme/engine/model/Material.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::engine::model::Material;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::SpecularMaterialProperties;

Material::Material(const string& id)
{
	this->id = id;
	this->textureMatrix.identity();
	this->specularMaterialProperties = make_unique<SpecularMaterialProperties>();
}

void Material::setSpecularMaterialProperties(SpecularMaterialProperties* specularMaterialProperties) {
	this->specularMaterialProperties = unique_ptr<SpecularMaterialProperties>(specularMaterialProperties);
}

void Material::setPBRMaterialProperties(PBRMaterialProperties* pbrMaterialProperties) {
	this->pbrMaterialProperties = unique_ptr<PBRMaterialProperties>(pbrMaterialProperties);
}

string Material::defaultMaterialId = "tdme.default_material";
Material* Material::defaultMaterial = new Material(Material::defaultMaterialId);
