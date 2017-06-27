// Generated from /tdme/src/tdme/tools/shared/files/LevelFileExport.java
#include <tdme/tools/shared/files/LevelFileExport.h>

#include <java/io/File.h>
#include <java/io/FileOutputStream.h>
#include <java/io/IOException.h>
#include <java/io/OutputStream.h>
#include <java/io/PrintStream.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Iterable.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/util/Iterator.h>
#include <org/json/JSONArray.h>
#include <org/json/JSONException.h>
#include <org/json/JSONObject.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/tools/shared/files/ModelMetaDataFileExport.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelEditorLight.h>
#include <tdme/tools/shared/model/LevelEditorObject.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>

using tdme::tools::shared::files::LevelFileExport;
using java::io::File;
using java::io::FileOutputStream;
using java::io::IOException;
using java::io::OutputStream;
using java::io::PrintStream;
using java::lang::ClassCastException;
using java::lang::Iterable;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::util::Iterator;
using org::json::JSONArray;
using org::json::JSONException;
using org::json::JSONObject;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::RotationOrder;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::shared::files::ModelMetaDataFileExport;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorLight;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::tools::shared::model::PropertyModelClass;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

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
LevelFileExport::LevelFileExport(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelFileExport::LevelFileExport()
	: LevelFileExport(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void LevelFileExport::export_(String* fileName, LevelEditorLevel* level) /* throws(Exception) */
{
	clinit();
	FileOutputStream* fos = nullptr;
	PrintStream* fops = nullptr;
	level->setFileName((new File(fileName))->getName());
	{
		auto finally0 = finally([&] {
			if (fops != nullptr)
				fops->close();

			if (fos != nullptr)
				try {
					fos->close();
				} catch (IOException* ioe) {
				}

		});
		try {
			auto entityLibrary = level->getEntityLibrary();
			auto jRoot = new JSONObject();
			jRoot->put(u"version"_j, static_cast< Object* >(u"0.99"_j));
			jRoot->put(u"ro"_j, static_cast< Object* >(level->getRotationOrder()->toString()));
			auto jLights = new JSONArray();
			for (auto i = 0; i < level->getLightCount(); i++) {
				auto light = level->getLightAt(i);
				auto jLight = new JSONObject();
				jLight->put(u"id"_j, i);
				jLight->put(u"ar"_j, static_cast< double >(light->getAmbient()->getRed()));
				jLight->put(u"ag"_j, static_cast< double >(light->getAmbient()->getGreen()));
				jLight->put(u"ab"_j, static_cast< double >(light->getAmbient()->getBlue()));
				jLight->put(u"aa"_j, static_cast< double >(light->getAmbient()->getAlpha()));
				jLight->put(u"dr"_j, static_cast< double >(light->getDiffuse()->getRed()));
				jLight->put(u"dg"_j, static_cast< double >(light->getDiffuse()->getGreen()));
				jLight->put(u"db"_j, static_cast< double >(light->getDiffuse()->getBlue()));
				jLight->put(u"da"_j, static_cast< double >(light->getDiffuse()->getAlpha()));
				jLight->put(u"sr"_j, static_cast< double >(light->getSpecular()->getRed()));
				jLight->put(u"sg"_j, static_cast< double >(light->getSpecular()->getGreen()));
				jLight->put(u"sb"_j, static_cast< double >(light->getSpecular()->getBlue()));
				jLight->put(u"sa"_j, static_cast< double >(light->getSpecular()->getAlpha()));
				jLight->put(u"px"_j, static_cast< double >(light->getPosition()->getX()));
				jLight->put(u"py"_j, static_cast< double >(light->getPosition()->getY()));
				jLight->put(u"pz"_j, static_cast< double >(light->getPosition()->getZ()));
				jLight->put(u"pw"_j, static_cast< double >(light->getPosition()->getW()));
				jLight->put(u"stx"_j, static_cast< double >(light->getSpotTo()->getX()));
				jLight->put(u"sty"_j, static_cast< double >(light->getSpotTo()->getY()));
				jLight->put(u"stz"_j, static_cast< double >(light->getSpotTo()->getZ()));
				jLight->put(u"sdx"_j, static_cast< double >(light->getSpotDirection()->getX()));
				jLight->put(u"sdy"_j, static_cast< double >(light->getSpotDirection()->getY()));
				jLight->put(u"sdz"_j, static_cast< double >(light->getSpotDirection()->getZ()));
				jLight->put(u"se"_j, static_cast< double >(light->getSpotExponent()));
				jLight->put(u"sco"_j, static_cast< double >(light->getSpotCutOff()));
				jLight->put(u"ca"_j, static_cast< double >(light->getConstantAttenuation()));
				jLight->put(u"la"_j, static_cast< double >(light->getLinearAttenuation()));
				jLight->put(u"qa"_j, static_cast< double >(light->getQuadraticAttenuation()));
				jLight->put(u"e"_j, light->isEnabled());
				jLights->put(static_cast< Object* >(jLight));
			}
			jRoot->put(u"lights"_j, static_cast< Object* >(jLights));
			auto jEntityLibrary = new JSONArray();
			for (auto i = 0; i < entityLibrary->getEntityCount(); i++) {
				auto entity = entityLibrary->getEntityAt(i);
				auto jModel = new JSONObject();
				jModel->put(u"id"_j, entity->getId());
				jModel->put(u"type"_j, static_cast< Object* >(entity->getType()));
				jModel->put(u"name"_j, static_cast< Object* >(entity->getName()));
				jModel->put(u"descr"_j, static_cast< Object* >(entity->getDescription()));
				jModel->put(u"entity"_j, static_cast< Object* >(ModelMetaDataFileExport::exportToJSON(entity)));
				jEntityLibrary->put(static_cast< Object* >(jModel));
			}
			auto jMapProperties = new JSONArray();
			for (auto _i = level->getProperties()->iterator(); _i->hasNext(); ) {
				PropertyModelClass* mapProperty = java_cast< PropertyModelClass* >(_i->next());
				{
					auto jMapProperty = new JSONObject();
					jMapProperty->put(u"name"_j, static_cast< Object* >(mapProperty->getName()));
					jMapProperty->put(u"value"_j, static_cast< Object* >(mapProperty->getValue()));
					jMapProperties->put(static_cast< Object* >(jMapProperty));
				}
			}
			jRoot->put(u"properties"_j, static_cast< Object* >(jMapProperties));
			jRoot->put(u"models"_j, static_cast< Object* >(jEntityLibrary));
			auto jObjects = new JSONArray();
			for (auto i = 0; i < level->getObjectCount(); i++) {
				auto levelEditorObject = level->getObjectAt(i);
				auto jObject = new JSONObject();
				auto transformations = levelEditorObject->getTransformations();
				auto translation = transformations->getTranslation();
				auto scale = transformations->getScale();
				auto rotationAroundXAxis = transformations->getRotations()->get(level->getRotationOrder()->getAxisXIndex());
				auto rotationAroundYAxis = transformations->getRotations()->get(level->getRotationOrder()->getAxisYIndex());
				auto rotationAroundZAxis = transformations->getRotations()->get(level->getRotationOrder()->getAxisZIndex());
				jObject->put(u"id"_j, static_cast< Object* >(levelEditorObject->getId()));
				jObject->put(u"descr"_j, static_cast< Object* >(levelEditorObject->getDescription()));
				jObject->put(u"mid"_j, levelEditorObject->getEntity()->getId());
				jObject->put(u"tx"_j, static_cast< double >(translation->getX()));
				jObject->put(u"ty"_j, static_cast< double >(translation->getY()));
				jObject->put(u"tz"_j, static_cast< double >(translation->getZ()));
				jObject->put(u"sx"_j, static_cast< double >(scale->getX()));
				jObject->put(u"sy"_j, static_cast< double >(scale->getY()));
				jObject->put(u"sz"_j, static_cast< double >(scale->getZ()));
				jObject->put(u"rx"_j, static_cast< double >(rotationAroundXAxis->getAngle()));
				jObject->put(u"ry"_j, static_cast< double >(rotationAroundYAxis->getAngle()));
				jObject->put(u"rz"_j, static_cast< double >(rotationAroundZAxis->getAngle()));
				auto jObjectProperties = new JSONArray();
				for (auto _i = levelEditorObject->getProperties()->iterator(); _i->hasNext(); ) {
					PropertyModelClass* objectProperty = java_cast< PropertyModelClass* >(_i->next());
					{
						auto jObjectProperty = new JSONObject();
						jObjectProperty->put(u"name"_j, static_cast< Object* >(objectProperty->getName()));
						jObjectProperty->put(u"value"_j, static_cast< Object* >(objectProperty->getValue()));
						jObjectProperties->put(static_cast< Object* >(jObjectProperty));
					}
				}
				jObject->put(u"properties"_j, static_cast< Object* >(jObjectProperties));
				jObjects->put(static_cast< Object* >(jObject));
			}
			jRoot->put(u"objects"_j, static_cast< Object* >(jObjects));
			jRoot->put(u"objects_eidx"_j, level->getObjectIdx());
			fos = new FileOutputStream(new File(fileName));
			fops = new PrintStream(static_cast< OutputStream* >(fos));
			fops->print(jRoot->toString(2));
		} catch (JSONException* je) {
			je->printStackTrace();
		} catch (IOException* ioe) {
			ioe->printStackTrace();
		}
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelFileExport::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.files.LevelFileExport", 39);
    return c;
}

java::lang::Class* LevelFileExport::getClass0()
{
	return class_();
}

