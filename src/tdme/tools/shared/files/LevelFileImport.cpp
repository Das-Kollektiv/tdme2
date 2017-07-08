// Generated from /tdme/src/tdme/tools/shared/files/LevelFileImport.java
#include <tdme/tools/shared/files/LevelFileImport.h>

#include <java/io/File.h>
#include <java/io/IOException.h>
#include <java/io/InputStream.h>
#include <java/lang/Exception.h>
#include <java/lang/Float.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <org/json/JSONArray.h>
#include <org/json/JSONObject.h>
#include <org/json/JSONTokener.h>
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
#include <Array.h>

using tdme::tools::shared::files::LevelFileImport;
using java::io::File;
using java::io::IOException;
using java::io::InputStream;
using java::lang::Exception;
using java::lang::Float;
using java::lang::String;
using java::lang::StringBuilder;
using org::json::JSONArray;
using org::json::JSONObject;
using org::json::JSONTokener;
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

namespace
{
template<typename F>
struct finally_
{
    finally_(F f) : f(f), moved(false) { }
    finally_(finally_ &&x) : f(x.f), moved(false) { x.moved = true; }
    ~finally_() { if(!moved) f(); }
private:
    finally_(const finally_&); finally_& operator=(const finally_&);
    F f;
    bool moved;
};

template<typename F> finally_<F> finally(F f) { return finally_<F>(f); }
}
LevelFileImport::LevelFileImport(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelFileImport::LevelFileImport()
	: LevelFileImport(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void LevelFileImport::doImport(String* pathName, String* fileName, LevelEditorLevel* level) /* throws(Exception) */
{
	clinit();
	doImport(pathName, fileName, level, nullptr);
}

void LevelFileImport::doImport(String* pathName, String* fileName, LevelEditorLevel* level, String* objectIdPrefix) /* throws(Exception) */
{
	clinit();
	pathName = pathName->replace(File::separatorChar == u'/' ? u'\\' : u'/', File::separatorChar);
	fileName = fileName->replace(File::separatorChar == u'/' ? u'\\' : u'/', File::separatorChar);
	JSONObject* jRoot = nullptr;
	InputStream* is = nullptr;
	{
		auto finally0 = finally([&] {
			if (is != nullptr)
				try {
					is->close();
				} catch (IOException* ioei) {
				}

		});
		try {
			jRoot = new JSONObject(new JSONTokener(new String(_FileSystem::getInstance()->getContent(pathName, fileName))));
		} catch (IOException* ioe) {
			throw ioe;
		}
	}
	level->setGameRoot(Tools::getGameRootPath(pathName));
	auto version = Float::parseFloat(jRoot->getString(u"version"_j));
	level->setRotationOrder(jRoot->has(u"ro"_j) == true ? RotationOrder::valueOf(jRoot->getString(u"ro"_j)) : RotationOrder::XYZ);
	level->clearProperties();
	auto jMapProperties = jRoot->getJSONArray(u"properties"_j);
	for (auto i = 0; i < jMapProperties->length(); i++) {
		auto jMapProperty = jMapProperties->getJSONObject(i);
		level->addProperty(jMapProperty->getString(u"name"_j), jMapProperty->getString(u"value"_j));
	}
	if (jRoot->has(u"lights"_j) == true) {
		auto jLights = jRoot->getJSONArray(u"lights"_j);
		for (auto i = 0; i < jLights->length(); i++) {
			auto jLight = jLights->getJSONObject(i);
			auto light = level->getLightAt(jLight->has(u"id"_j) ? jLight->getInt(u"id"_j) : i);
			light->getAmbient()->set(static_cast< float >(jLight->getDouble(u"ar"_j)), static_cast< float >(jLight->getDouble(u"ag"_j)), static_cast< float >(jLight->getDouble(u"ab"_j)), static_cast< float >(jLight->getDouble(u"aa"_j)));
			light->getDiffuse()->set(static_cast< float >(jLight->getDouble(u"dr"_j)), static_cast< float >(jLight->getDouble(u"dg"_j)), static_cast< float >(jLight->getDouble(u"db"_j)), static_cast< float >(jLight->getDouble(u"da"_j)));
			light->getSpecular()->set(static_cast< float >(jLight->getDouble(u"sr"_j)), static_cast< float >(jLight->getDouble(u"sg"_j)), static_cast< float >(jLight->getDouble(u"sb"_j)), static_cast< float >(jLight->getDouble(u"sa"_j)));
			light->getPosition()->set(static_cast< float >(jLight->getDouble(u"px"_j)), static_cast< float >(jLight->getDouble(u"py"_j)), static_cast< float >(jLight->getDouble(u"pz"_j)), static_cast< float >(jLight->getDouble(u"pw"_j)));
			light->setConstantAttenuation(static_cast< float >(jLight->getDouble(u"ca"_j)));
			light->setLinearAttenuation(static_cast< float >(jLight->getDouble(u"la"_j)));
			light->setQuadraticAttenuation(static_cast< float >(jLight->getDouble(u"qa"_j)));
			light->getSpotTo()->set(static_cast< float >(jLight->getDouble(u"stx"_j)), static_cast< float >(jLight->getDouble(u"sty"_j)), static_cast< float >(jLight->getDouble(u"stz"_j)));
			light->getSpotDirection()->set(static_cast< float >(jLight->getDouble(u"sdx"_j)), static_cast< float >(jLight->getDouble(u"sdy"_j)), static_cast< float >(jLight->getDouble(u"sdz"_j)));
			light->setSpotExponent(static_cast< float >(jLight->getDouble(u"se"_j)));
			light->setSpotCutOff(static_cast< float >(jLight->getDouble(u"sco"_j)));
			light->setEnabled(jLight->getBoolean(u"e"_j));
		}
	}
	level->getEntityLibrary()->clear();
	auto jModels = jRoot->getJSONArray(u"models"_j);
	for (auto i = 0; i < jModels->length(); i++) {
		auto jModel = jModels->getJSONObject(i);
		LevelEditorEntity* levelEditorEntity = nullptr; //ModelMetaDataFileImport::doImportFromJSON(jModel->getInt(u"id"_j), (new File(pathName))->getCanonicalPath(), jModel->getJSONObject(u"entity"_j));
		if (levelEditorEntity == nullptr) {
			throw new Exception(u"Invalid entity"_j);
		}
		level->getEntityLibrary()->addEntity(levelEditorEntity);
		if (jModel->has(u"properties"_j)) {
			auto jModelProperties = jModel->getJSONArray(u"properties"_j);
			for (auto j = 0; j < jModelProperties->length(); j++) {
				auto jModelProperty = jModelProperties->getJSONObject(j);
				levelEditorEntity->addProperty(jModelProperty->getString(u"name"_j), jModelProperty->getString(u"value"_j));
			}
		}
	}
	level->clearObjects();
	auto jObjects = jRoot->getJSONArray(u"objects"_j);
	for (auto i = 0; i < jObjects->length(); i++) {
		auto jObject = jObjects->getJSONObject(i);
		auto model = level->getEntityLibrary()->getEntity(jObject->getInt(u"mid"_j));
		auto transformations = new Transformations();
		transformations->getPivot()->set(model->getPivot());
		transformations->getTranslation()->set(static_cast< float >(jObject->getDouble(u"tx"_j)), static_cast< float >(jObject->getDouble(u"ty"_j)), static_cast< float >(jObject->getDouble(u"tz"_j)));
		transformations->getScale()->set(static_cast< float >(jObject->getDouble(u"sx"_j)), static_cast< float >(jObject->getDouble(u"sy"_j)), static_cast< float >(jObject->getDouble(u"sz"_j)));
		auto rotation = new Vector3(static_cast< float >(jObject->getDouble(u"rx"_j)), static_cast< float >(jObject->getDouble(u"ry"_j)), static_cast< float >(jObject->getDouble(u"rz"_j)));
		transformations->getRotations()->add(new Rotation((*rotation->getArray())[level->getRotationOrder()->getAxis0VectorIndex()], level->getRotationOrder()->getAxis0()));
		transformations->getRotations()->add(new Rotation((*rotation->getArray())[level->getRotationOrder()->getAxis1VectorIndex()], level->getRotationOrder()->getAxis1()));
		transformations->getRotations()->add(new Rotation((*rotation->getArray())[level->getRotationOrder()->getAxis2VectorIndex()], level->getRotationOrder()->getAxis2()));
		transformations->update();
		auto levelEditorObject = new LevelEditorObject(objectIdPrefix != nullptr ? ::java::lang::StringBuilder().append(objectIdPrefix)->append(jObject->getString(u"id"_j))->toString() : jObject->getString(u"id"_j), jObject->has(u"descr"_j) ? jObject->getString(u"descr"_j) : u""_j, transformations, model);
		levelEditorObject->clearProperties();
		if (jObject->has(u"properties"_j)) {
			auto jObjectProperties = jObject->getJSONArray(u"properties"_j);
			for (auto j = 0; j < jObjectProperties->length(); j++) {
				auto jObjectProperty = jObjectProperties->getJSONObject(j);
				levelEditorObject->addProperty(jObjectProperty->getString(u"name"_j), jObjectProperty->getString(u"value"_j));
			}
		}
		level->addObject(levelEditorObject);
	}
	level->setObjectIdx(jRoot->getInt(u"objects_eidx"_j));
	level->setPathName(pathName);
	level->setFileName(fileName);
	level->computeDimension();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelFileImport::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.files.LevelFileImport", 39);
    return c;
}

java::lang::Class* LevelFileImport::getClass0()
{
	return class_();
}

