#include <tdme/tools/shared/files/LevelFileImport.h>

#include <string>

#include <java/lang/String.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelEditorLight.h>
#include <tdme/tools/shared/model/LevelEditorObject.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <Array.h>

#include <ext/jsonbox/Value.h>
#include <ext/jsonbox/Array.h>

using std::wstring;

using tdme::tools::shared::files::LevelFileImport;
using java::io::File;
using java::io::InputStream;
using java::lang::String;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::RotationOrder;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorLight;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::tools::shared::tools::Tools;
using tdme::utils::Float;
using tdme::utils::StringConverter;
using tdme::utils::_Console;

using tdme::ext::jsonbox::Value;
using tdme::ext::jsonbox::Array;

void LevelFileImport::doImport(const wstring& pathName, const wstring& fileName, LevelEditorLevel* level) throw (_FileSystemException, JsonException, ModelFileIOException)
{
	doImport(pathName, fileName, level, L"");
}

void LevelFileImport::doImport(const wstring& pathName, const wstring& fileName, LevelEditorLevel* level, const wstring& objectIdPrefix) throw (_FileSystemException, JsonException, ModelFileIOException)
{
	auto jsonContent = _FileSystem::getInstance()->getContentAsString(pathName, fileName);

	Value jRoot;
	jRoot.loadFromString(
		StringConverter::toString(jsonContent)
	);

	level->setGameRoot(Tools::getGameRootPath(pathName));
	auto version = Float::parseFloat(StringConverter::toWideString(jRoot["version"].getString()));
	level->setRotationOrder(jRoot["ro"].isNull() == false?RotationOrder::valueOf(StringConverter::toWideString(jRoot["ro"].getString())) : RotationOrder::XYZ);
	level->clearProperties();
	auto jMapProperties = jRoot["properties"].getArray();
	for (auto i = 0; i < jMapProperties.size(); i++) {
		auto& jMapProperty = jMapProperties[i];
		level->addProperty(
			StringConverter::toWideString(jMapProperty["name"].getString()),
			StringConverter::toWideString(jMapProperty["value"].getString())
		);
	}
	if (jRoot["lights"].isNull() == false) {
		auto& jLights = jRoot["lights"].getArray();
		for (auto i = 0; i < jLights.size(); i++) {
			auto jLight = jLights[i];
			auto light = level->getLightAt(jLight["id"].isNull() == false? jLight["id"].getInt() : i);
			light->getAmbient()->set(
				static_cast< float >(jLight["ar"].getDouble()),
				static_cast< float >(jLight["ag"].getDouble()),
				static_cast< float >(jLight["ab"].getDouble()),
				static_cast< float >(jLight["aa"].getDouble())
			);
			light->getDiffuse()->set(
				static_cast< float >(jLight["dr"].getDouble()),
				static_cast< float >(jLight["dg"].getDouble()),
				static_cast< float >(jLight["db"].getDouble()),
				static_cast< float >(jLight["da"].getDouble())
			);
			light->getSpecular()->set(
				static_cast< float >(jLight["sr"].getDouble()),
				static_cast< float >(jLight["sg"].getDouble()),
				static_cast< float >(jLight["sb"].getDouble()),
				static_cast< float >(jLight["sa"].getDouble())
			);
			light->getPosition()->set(
				static_cast< float >(jLight["px"].getDouble()),
				static_cast< float >(jLight["py"].getDouble()),
				static_cast< float >(jLight["pz"].getDouble()),
				static_cast< float >(jLight["pw"].getDouble())
			);
			light->setConstantAttenuation(static_cast< float >(jLight["ca"].getDouble()));
			light->setLinearAttenuation(static_cast< float >(jLight["la"].getDouble()));
			light->setQuadraticAttenuation(static_cast< float >(jLight["qa"].getDouble()));
			light->getSpotTo()->set(
				static_cast< float >(jLight["stx"].getDouble()),
				static_cast< float >(jLight["sty"].getDouble()),
				static_cast< float >(jLight["stz"].getDouble())
			);
			light->getSpotDirection()->set(
				static_cast< float >(jLight["sdx"].getDouble()),
				static_cast< float >(jLight["sdy"].getDouble()),
				static_cast< float >(jLight["sdz"].getDouble())
			);
			light->setSpotExponent(static_cast< float >(jLight["se"].getDouble()));
			light->setSpotCutOff(static_cast< float >(jLight["sco"].getDouble()));
			light->setEnabled(jLight["e"].getBoolean());
		}
	}
	level->getEntityLibrary()->clear();
	auto jModels = jRoot["models"].getArray();
	for (auto i = 0; i < jModels.size(); i++) {
		auto jModel = jModels[i];
		LevelEditorEntity* levelEditorEntity = ModelMetaDataFileImport::doImportFromJSON(
			jModel["id"].getInt(),
			pathName,
			jModel["entity"]
		);
		if (levelEditorEntity == nullptr) {
			_Console::println(L"LevelFileImport::doImport(): Invalid entity = " + to_wstring(jModel["id"].getInt()));
			continue;
		}
		level->getEntityLibrary()->addEntity(levelEditorEntity);
		if (jModel["properties"].isNull() == false) {
			auto jModelProperties = jModel["properties"].getArray();
			for (auto j = 0; j < jModelProperties.size(); j++) {
				auto jModelProperty = jModelProperties[j];
				levelEditorEntity->addProperty(
					StringConverter::toWideString(jModelProperty["name"].getString()),
					StringConverter::toWideString(jModelProperty["value"].getString())
				);
			}
		}
	}
	level->clearObjects();
	auto jObjects = jRoot["objects"].getArray();
	for (auto i = 0; i < jObjects.size(); i++) {
		auto& jObject = jObjects[i];
		auto model = level->getEntityLibrary()->getEntity(jObject["mid"].getInt());
		if (model == nullptr) {
			_Console::println(L"LevelFileImport::doImport(): No entity found with id = " + to_wstring(jObject["mid"].getInt()));
			continue;
		}

		auto transformations = new Transformations();
		transformations->getPivot().set(*model->getPivot());
		transformations->getTranslation().set(
			static_cast< float >(jObject["tx"].getDouble()),
			static_cast< float >(jObject["ty"].getDouble()),
			static_cast< float >(jObject["tz"].getDouble())
		);
		transformations->getScale().set(
			static_cast< float >(jObject["sx"].getDouble()),
			static_cast< float >(jObject["sy"].getDouble()),
			static_cast< float >(jObject["sz"].getDouble())
		);
		auto rotation = new Vector3(
			static_cast< float >(jObject["rx"].getDouble()),
			static_cast< float >(jObject["ry"].getDouble()),
			static_cast< float >(jObject["rz"].getDouble())
		);
		transformations->getRotations()->add(new Rotation(rotation->getArray()[level->getRotationOrder()->getAxis0VectorIndex()], level->getRotationOrder()->getAxis0()));
		transformations->getRotations()->add(new Rotation(rotation->getArray()[level->getRotationOrder()->getAxis1VectorIndex()], level->getRotationOrder()->getAxis1()));
		transformations->getRotations()->add(new Rotation(rotation->getArray()[level->getRotationOrder()->getAxis2VectorIndex()], level->getRotationOrder()->getAxis2()));
		transformations->update();
		auto levelEditorObject = new LevelEditorObject(
			objectIdPrefix != L"" ?
				objectIdPrefix + StringConverter::toWideString(jObject["id"].getString()) :
				StringConverter::toWideString(jObject["id"].getString()),
			 jObject["descr"].isNull() == false?StringConverter::toWideString(jObject["descr"].getString()) : L"",
			 transformations,
			 model
		);
		levelEditorObject->clearProperties();
		if (jObject["properties"].isNull() == false) {
			auto jObjectProperties = jObject["properties"].getArray();
			for (auto j = 0; j < jObjectProperties.size(); j++) {
				auto jObjectProperty = jObjectProperties[j];
				levelEditorObject->addProperty(
					StringConverter::toWideString(jObjectProperty["name"].getString()),
					StringConverter::toWideString(jObjectProperty["value"].getString())
				);
			}
		}
		level->addObject(levelEditorObject);
	}
	level->setObjectIdx(jRoot["objects_eidx"].getInt());
	level->setPathName(pathName);
	level->setFileName(fileName);
	level->computeDimension();
}
