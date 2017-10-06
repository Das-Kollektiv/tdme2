#include <tdme/tools/shared/files/LevelFileExport.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <java/lang/String.h>

#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>
#include <tdme/tools/shared/files/ModelMetaDataFileExport.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelEditorLight.h>
#include <tdme/tools/shared/model/LevelEditorObject.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/utils/StringConverter.h>

#include <ext/jsonbox/Array.h>
#include <ext/jsonbox/Object.h>

using std::ostringstream;
using std::wstring;

using java::lang::String;

using tdme::tools::shared::files::LevelFileExport;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::RotationOrder;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemInterface;
using tdme::tools::shared::files::ModelMetaDataFileExport;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorLight;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::utils::StringConverter;

void LevelFileExport::export_(const wstring& pathName, const wstring& fileName, LevelEditorLevel* level) throw (_FileSystemException, JsonException, ModelFileIOException)
{
	level->setFileName(pathName + L'/' + fileName);
	auto entityLibrary = level->getEntityLibrary();
	tdme::ext::jsonbox::Object jRoot;
	jRoot["version"] = "0.99";
	jRoot["ro"] = StringConverter::toString(level->getRotationOrder()->getName());
	tdme::ext::jsonbox::Array jLights;
	for (auto i = 0; i < level->getLightCount(); i++) {
		auto light = level->getLightAt(i);
		ext::jsonbox::Object jLight;
		jLight["id"] = i;
		jLight["ar"] = static_cast< double >(light->getAmbient().getRed());
		jLight["ag"] = static_cast< double >(light->getAmbient().getGreen());
		jLight["ab"] = static_cast< double >(light->getAmbient().getBlue());
		jLight["aa"] = static_cast< double >(light->getAmbient().getAlpha());
		jLight["dr"] = static_cast< double >(light->getDiffuse().getRed());
		jLight["dg"] = static_cast< double >(light->getDiffuse().getGreen());
		jLight["db"] = static_cast< double >(light->getDiffuse().getBlue());
		jLight["da"] = static_cast< double >(light->getDiffuse().getAlpha());
		jLight["sr"] = static_cast< double >(light->getSpecular().getRed());
		jLight["sg"] = static_cast< double >(light->getSpecular().getGreen());
		jLight["sb"] = static_cast< double >(light->getSpecular().getBlue());
		jLight["sa"] = static_cast< double >(light->getSpecular().getAlpha());
		jLight["px"] = static_cast< double >(light->getPosition().getX());
		jLight["py"] = static_cast< double >(light->getPosition().getY());
		jLight["pz"] = static_cast< double >(light->getPosition().getZ());
		jLight["pw"] = static_cast< double >(light->getPosition().getW());
		jLight["stx"] = static_cast< double >(light->getSpotTo().getX());
		jLight["sty"] = static_cast< double >(light->getSpotTo().getY());
		jLight["stz"] = static_cast< double >(light->getSpotTo().getZ());
		jLight["sdx"] = static_cast< double >(light->getSpotDirection().getX());
		jLight["sdy"] = static_cast< double >(light->getSpotDirection().getY());
		jLight["sdz"] = static_cast< double >(light->getSpotDirection().getZ());
		jLight["se"] = static_cast< double >(light->getSpotExponent());
		jLight["sco"] = static_cast< double >(light->getSpotCutOff());
		jLight["ca"] = static_cast< double >(light->getConstantAttenuation());
		jLight["la"] = static_cast< double >(light->getLinearAttenuation());
		jLight["qa"] = static_cast< double >(light->getQuadraticAttenuation());
		jLight["e"] = light->isEnabled();
		jLights.push_back(jLight);
	}
	jRoot["lights"] = jLights;
	ext::jsonbox::Array jEntityLibrary;
	for (auto i = 0; i < entityLibrary->getEntityCount(); i++) {
		auto entity = entityLibrary->getEntityAt(i);
		tdme::ext::jsonbox::Object jModel;
		jModel["id"] = entity->getId();
		jModel["type"] = StringConverter::toString(entity->getType()->getName());
		jModel["name"] = StringConverter::toString(entity->getName());
		jModel["descr"] = StringConverter::toString(entity->getDescription());
		jModel["entity"] = ModelMetaDataFileExport::exportToJSON(entity);
		jEntityLibrary.push_back(jModel);
	}
	ext::jsonbox::Array jMapProperties;
	for (auto i = 0; i < level->getPropertyCount(); i++) {
		PropertyModelClass* mapProperty = level->getPropertyByIndex(i);
		tdme::ext::jsonbox::Object jMapProperty;
		jMapProperty["name"] = StringConverter::toString(mapProperty->getName());
		jMapProperty["value"] = StringConverter::toString(mapProperty->getValue());
		jMapProperties.push_back(jMapProperty);
	}
	jRoot["properties"] = jMapProperties;
	jRoot["models"] = jEntityLibrary;
	tdme::ext::jsonbox::Array jObjects;
	for (auto i = 0; i < level->getObjectCount(); i++) {
		auto levelEditorObject = level->getObjectAt(i);
		tdme::ext::jsonbox::Object jObject;
		auto transformations = levelEditorObject->getTransformations();
		auto translation = transformations->getTranslation();
		auto scale = transformations->getScale();
		auto rotationAroundXAxis = transformations->getRotations()->get(level->getRotationOrder()->getAxisXIndex());
		auto rotationAroundYAxis = transformations->getRotations()->get(level->getRotationOrder()->getAxisYIndex());
		auto rotationAroundZAxis = transformations->getRotations()->get(level->getRotationOrder()->getAxisZIndex());
		jObject["id"] = StringConverter::toString(levelEditorObject->getId());
		jObject["descr"] = StringConverter::toString(levelEditorObject->getDescription());
		jObject["mid"] = levelEditorObject->getEntity()->getId();
		jObject["tx"] = static_cast< double >(translation.getX());
		jObject["ty"] = static_cast< double >(translation.getY());
		jObject["tz"] = static_cast< double >(translation.getZ());
		jObject["sx"] = static_cast< double >(scale.getX());
		jObject["sy"] = static_cast< double >(scale.getY());
		jObject["sz"] = static_cast< double >(scale.getZ());
		jObject["rx"] = static_cast< double >(rotationAroundXAxis->getAngle());
		jObject["ry"] = static_cast< double >(rotationAroundYAxis->getAngle());
		jObject["rz"] = static_cast< double >(rotationAroundZAxis->getAngle());
		tdme::ext::jsonbox::Array jObjectProperties;
		for (auto i = 0; i < levelEditorObject->getPropertyCount(); i++) {
			PropertyModelClass* objectProperty = levelEditorObject->getPropertyByIndex(i);
			tdme::ext::jsonbox::Object jObjectProperty;
			jObjectProperty["name"] = StringConverter::toString(objectProperty->getName());
			jObjectProperty["value"] = StringConverter::toString(objectProperty->getValue());
			jObjectProperties.push_back(jObjectProperty);
		}
		jObject["properties"] = jObjectProperties;
		jObjects.push_back(jObject);
	}
	jRoot["objects"] = jObjects;
	jRoot["objects_eidx"] = level->getObjectIdx();

	ostringstream json;
	json << jRoot;

	_FileSystem::getInstance()->setContentFromString(pathName, fileName, StringConverter::toWideString(json.str()));
}
