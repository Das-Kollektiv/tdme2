// Generated from /tdme/src/tdme/tools/shared/files/ModelMetaDataFileImport.java
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>

#include <java/io/File.h>
#include <java/io/IOException.h>
#include <java/io/InputStream.h>
#include <java/lang/Exception.h>
#include <java/lang/Float.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <org/json/JSONArray.h>
#include <org/json/JSONObject.h>
#include <org/json/JSONTokener.h>
#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Emitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_ObjectParticleSystem.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleSystem.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_SphereParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Type.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/utils/_Console.h>

using tdme::tools::shared::files::ModelMetaDataFileImport;
using java::io::File;
using java::io::IOException;
using java::io::InputStream;
using java::lang::Exception;
using java::lang::Float;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using org::json::JSONArray;
using org::json::JSONObject;
using org::json::JSONTokener;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::math::Vector3;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::tools::shared::tools::Tools;
using tdme::utils::_Console;

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
ModelMetaDataFileImport::ModelMetaDataFileImport(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ModelMetaDataFileImport::ModelMetaDataFileImport()
	: ModelMetaDataFileImport(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

LevelEditorEntity* ModelMetaDataFileImport::doImport(int32_t id, String* pathName, String* fileName) /* throws(Exception) */
{
	clinit();
	fileName = fileName->replace(File::separatorChar == u'/' ? u'\\' : u'/', File::separatorChar);
	JSONObject* jEntityRoot = nullptr;
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
			jEntityRoot = new JSONObject(new JSONTokener(new String(_FileSystem::getInstance()->getContent(pathName, fileName))));
		} catch (IOException* ioe) {
			throw ioe;
		}
	}
	auto levelEditorEntity = doImportFromJSON(id, pathName, jEntityRoot);
	levelEditorEntity->setEntityFileName(::java::lang::StringBuilder().append(pathName)->append(u"/"_j)
		->append(fileName)->toString());
	return levelEditorEntity;
}

LevelEditorEntity* ModelMetaDataFileImport::doImportFromJSON(int32_t id, String* pathName, JSONObject* jEntityRoot) /* throws(Exception) */
{
	clinit();
	LevelEditorEntity* levelEditorEntity;
	auto version = Float::parseFloat(jEntityRoot->getString(u"version"_j));
	auto pivot = new Vector3(static_cast< float >(jEntityRoot->getDouble(u"px"_j)), static_cast< float >(jEntityRoot->getDouble(u"py"_j)), static_cast< float >(jEntityRoot->getDouble(u"pz"_j)));
	auto modelType = LevelEditorEntity_EntityType::valueOf(jEntityRoot->getString(u"type"_j));
	auto modelFile = jEntityRoot->has(u"file"_j) == true ? (new File(jEntityRoot->getString(u"file"_j)))->getCanonicalPath() : static_cast< String* >(nullptr);
	auto modelThumbnail = jEntityRoot->has(u"thumbnail"_j) == true ? jEntityRoot->getString(u"thumbnail"_j) : static_cast< String* >(nullptr);
	auto name = jEntityRoot->getString(u"name"_j);
	auto description = jEntityRoot->getString(u"descr"_j);
	Model* model = nullptr;
	auto gameRoot = Tools::getGameRootPath(pathName);
	String* modelRelativeFileName = nullptr;
	if (modelFile != nullptr) {
		modelRelativeFileName = Tools::getRelativeResourcesFileName(gameRoot, modelFile);
		auto modelPath = ::java::lang::StringBuilder().append((gameRoot->length() > 0 ? ::java::lang::StringBuilder().append(gameRoot)->append(u"/"_j)->toString() : u""_j))->append(Tools::getPath(modelRelativeFileName))->toString();
		if (modelFile->toLowerCase()->endsWith(u".dae"_j)) {
			model = DAEReader::read(modelPath, Tools::getFileName(modelRelativeFileName));
		} else if (modelFile->toLowerCase()->endsWith(u".tm"_j)) {
			model = TMReader::read(modelPath, Tools::getFileName(modelRelativeFileName));
		} else {
			throw new Exception(::java::lang::StringBuilder().append(u"Unsupported mode file: "_j)->append(modelFile)->toString());
		}
	} else if (modelType == LevelEditorEntity_EntityType::EMPTY) {
		model = DAEReader::read(u"resources/tools/leveleditor/models"_j, u"arrow.dae"_j);
	}
	levelEditorEntity = new LevelEditorEntity(id, modelType, name, description, nullptr, modelFile != nullptr ? (new File(gameRoot, modelRelativeFileName))->getCanonicalPath() : static_cast< String* >(nullptr), modelThumbnail, model, pivot);
	auto jProperties = jEntityRoot->getJSONArray(u"properties"_j);
	for (auto i = 0; i < jProperties->length(); i++) {
		auto jProperty = jProperties->getJSONObject(i);
		levelEditorEntity->addProperty(jProperty->getString(u"name"_j), jProperty->getString(u"value"_j));
	}
	if (jEntityRoot->has(u"bv"_j) == true) {
		levelEditorEntity->addBoundingVolume(0, parseBoundingVolume(0, levelEditorEntity, jEntityRoot->getJSONObject(u"bv"_j)));
	} else if (jEntityRoot->has(u"bvs"_j) == true) {
		auto jBoundingVolumes = jEntityRoot->getJSONArray(u"bvs"_j);
		for (auto i = 0; i < jBoundingVolumes->length(); i++) {
			auto jBv = jBoundingVolumes->getJSONObject(i);
			levelEditorEntity->addBoundingVolume(i, parseBoundingVolume(i, levelEditorEntity, jBv));
		}
	}
	if (modelType == LevelEditorEntity_EntityType::PARTICLESYSTEM) {
		auto particleSystem = levelEditorEntity->getParticleSystem();
		auto jParticleSystem = jEntityRoot->getJSONObject(u"ps"_j);
		particleSystem->setType(LevelEditorEntityParticleSystem_Type::valueOf(jParticleSystem->getString(u"t"_j)));
		{
			auto v = particleSystem->getType();
			if ((v == LevelEditorEntityParticleSystem_Type::NONE)) {
{
					goto end_switch0;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Type::NONE) || (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM)) {
{
					auto jObjectParticleSystem = jParticleSystem->getJSONObject(u"ops"_j);
					auto objectParticleSystem = particleSystem->getObjectParticleSystem();
					objectParticleSystem->setMaxCount(jObjectParticleSystem->getInt(u"mc"_j));
					objectParticleSystem->getScale()->setX(static_cast< float >(jObjectParticleSystem->getDouble(u"sx"_j)));
					objectParticleSystem->getScale()->setY(static_cast< float >(jObjectParticleSystem->getDouble(u"sy"_j)));
					objectParticleSystem->getScale()->setZ(static_cast< float >(jObjectParticleSystem->getDouble(u"sz"_j)));
					objectParticleSystem->setAutoEmit(jObjectParticleSystem->getBoolean(u"ae"_j));
					try {
						auto particleModelFile = jObjectParticleSystem->getString(u"mf"_j);
						auto particleModelRelativeFileName = Tools::getRelativeResourcesFileName(gameRoot, particleModelFile);
						auto particleModelPath = ::java::lang::StringBuilder().append((gameRoot->length() > 0 ? ::java::lang::StringBuilder().append(gameRoot)->append(u"/"_j)->toString() : u""_j))->append(Tools::getPath(particleModelRelativeFileName))->toString();
						objectParticleSystem->setModelFile(::java::lang::StringBuilder().append(particleModelPath)->append(u"/"_j)
							->append(Tools::getFileName(particleModelRelativeFileName))->toString());
					} catch (Exception* exception) {
						exception->printStackTrace();
						_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ModelMetaDataFileImport::doImport(): Failed to set model file: "_j)->append(exception->getMessage())->toString()));
					}
					goto end_switch0;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Type::NONE) || (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) || (v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)) {
{
					auto jPointParticleSystem = jParticleSystem->getJSONObject(u"pps"_j);
					particleSystem->getPointParticleSystem()->setMaxPoints(jPointParticleSystem->getInt(u"mp"_j));
					particleSystem->getPointParticleSystem()->setAutoEmit(jPointParticleSystem->getBoolean(u"ae"_j));
					goto end_switch0;;
				}			}
			if (((v == LevelEditorEntityParticleSystem_Type::NONE) || (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) || (v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM) || ((v != LevelEditorEntityParticleSystem_Type::NONE) && (v != LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) && (v != LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)))) {
{
					_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ModelMetaDataFileExport::export(): unknown particle system type '"_j)->append(static_cast< Object* >(particleSystem->getType()))
						->append(u"'"_j)->toString()));
					goto end_switch0;;
				}			}
end_switch0:;
		}

		particleSystem->setEmitter(LevelEditorEntityParticleSystem_Emitter::valueOf(jParticleSystem->getString(u"e"_j)));
		{
			auto v = particleSystem->getEmitter();
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE)) {
{
					goto end_switch1;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER)) {
{
					auto jPointParticleEmitter = jParticleSystem->getJSONObject(u"ppe"_j);
					auto emitter = particleSystem->getPointParticleEmitter();
					emitter->setCount(jPointParticleEmitter->getInt(u"c"_j));
					emitter->setLifeTime(jPointParticleEmitter->getLong(u"lt"_j));
					emitter->setLifeTimeRnd(jPointParticleEmitter->getLong(u"ltrnd"_j));
					emitter->setMass(static_cast< float >(jPointParticleEmitter->getDouble(u"m"_j)));
					emitter->setMassRnd(static_cast< float >(jPointParticleEmitter->getDouble(u"mrnd"_j)));
					emitter->getPosition()->setX(static_cast< float >(jPointParticleEmitter->getDouble(u"px"_j)));
					emitter->getPosition()->setY(static_cast< float >(jPointParticleEmitter->getDouble(u"py"_j)));
					emitter->getPosition()->setZ(static_cast< float >(jPointParticleEmitter->getDouble(u"pz"_j)));
					emitter->getVelocity()->setX(static_cast< float >(jPointParticleEmitter->getDouble(u"vx"_j)));
					emitter->getVelocity()->setY(static_cast< float >(jPointParticleEmitter->getDouble(u"vy"_j)));
					emitter->getVelocity()->setZ(static_cast< float >(jPointParticleEmitter->getDouble(u"vz"_j)));
					emitter->getVelocityRnd()->setX(static_cast< float >(jPointParticleEmitter->getDouble(u"vrndx"_j)));
					emitter->getVelocityRnd()->setY(static_cast< float >(jPointParticleEmitter->getDouble(u"vrndy"_j)));
					emitter->getVelocityRnd()->setZ(static_cast< float >(jPointParticleEmitter->getDouble(u"vrndz"_j)));
					emitter->getColorStart()->setRed(static_cast< float >(jPointParticleEmitter->getDouble(u"csr"_j)));
					emitter->getColorStart()->setGreen(static_cast< float >(jPointParticleEmitter->getDouble(u"csg"_j)));
					emitter->getColorStart()->setBlue(static_cast< float >(jPointParticleEmitter->getDouble(u"csb"_j)));
					emitter->getColorStart()->setAlpha(static_cast< float >(jPointParticleEmitter->getDouble(u"csa"_j)));
					emitter->getColorEnd()->setRed(static_cast< float >(jPointParticleEmitter->getDouble(u"cer"_j)));
					emitter->getColorEnd()->setGreen(static_cast< float >(jPointParticleEmitter->getDouble(u"ceg"_j)));
					emitter->getColorEnd()->setBlue(static_cast< float >(jPointParticleEmitter->getDouble(u"ceb"_j)));
					emitter->getColorEnd()->setAlpha(static_cast< float >(jPointParticleEmitter->getDouble(u"cea"_j)));
					goto end_switch1;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER)) {
{
					auto jBoundingBoxParticleEmitter = jParticleSystem->getJSONObject(u"bbpe"_j);
					auto emitter = particleSystem->getBoundingBoxParticleEmitters();
					emitter->setCount(jBoundingBoxParticleEmitter->getInt(u"c"_j));
					emitter->setLifeTime(jBoundingBoxParticleEmitter->getLong(u"lt"_j));
					emitter->setLifeTimeRnd(jBoundingBoxParticleEmitter->getLong(u"ltrnd"_j));
					emitter->setMass(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"m"_j)));
					emitter->setMassRnd(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"mrnd"_j)));
					emitter->getVelocity()->setX(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"vx"_j)));
					emitter->getVelocity()->setY(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"vy"_j)));
					emitter->getVelocity()->setZ(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"vz"_j)));
					emitter->getVelocityRnd()->setX(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"vrndx"_j)));
					emitter->getVelocityRnd()->setY(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"vrndy"_j)));
					emitter->getVelocityRnd()->setZ(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"vrndz"_j)));
					emitter->getColorStart()->setRed(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"csr"_j)));
					emitter->getColorStart()->setGreen(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"csg"_j)));
					emitter->getColorStart()->setBlue(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"csb"_j)));
					emitter->getColorStart()->setAlpha(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"csa"_j)));
					emitter->getColorEnd()->setRed(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"cer"_j)));
					emitter->getColorEnd()->setGreen(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"ceg"_j)));
					emitter->getColorEnd()->setBlue(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"ceb"_j)));
					emitter->getColorEnd()->setAlpha(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"cea"_j)));
					emitter->getObbCenter()->setX(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"ocx"_j)));
					emitter->getObbCenter()->setY(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"ocy"_j)));
					emitter->getObbCenter()->setZ(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"ocz"_j)));
					emitter->getObbHalfextension()->setX(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"ohex"_j)));
					emitter->getObbHalfextension()->setY(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"ohey"_j)));
					emitter->getObbHalfextension()->setZ(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"ohez"_j)));
					emitter->getObbAxis0()->setX(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"oa0x"_j)));
					emitter->getObbAxis0()->setY(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"oa0y"_j)));
					emitter->getObbAxis0()->setZ(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"oa0z"_j)));
					emitter->getObbAxis1()->setX(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"oa1x"_j)));
					emitter->getObbAxis1()->setY(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"oa1y"_j)));
					emitter->getObbAxis1()->setZ(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"oa1z"_j)));
					emitter->getObbAxis2()->setX(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"oa2x"_j)));
					emitter->getObbAxis2()->setY(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"oa2y"_j)));
					emitter->getObbAxis2()->setZ(static_cast< float >(jBoundingBoxParticleEmitter->getDouble(u"oa2z"_j)));
					goto end_switch1;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER)) {
{
					auto jCircleParticleEmitter = jParticleSystem->getJSONObject(u"cpe"_j);
					auto emitter = particleSystem->getCircleParticleEmitter();
					emitter->setCount(jCircleParticleEmitter->getInt(u"c"_j));
					emitter->setLifeTime(jCircleParticleEmitter->getLong(u"lt"_j));
					emitter->setLifeTimeRnd(jCircleParticleEmitter->getLong(u"ltrnd"_j));
					emitter->setMass(static_cast< float >(jCircleParticleEmitter->getDouble(u"m"_j)));
					emitter->setMassRnd(static_cast< float >(jCircleParticleEmitter->getDouble(u"mrnd"_j)));
					emitter->getVelocity()->setX(static_cast< float >(jCircleParticleEmitter->getDouble(u"vx"_j)));
					emitter->getVelocity()->setY(static_cast< float >(jCircleParticleEmitter->getDouble(u"vy"_j)));
					emitter->getVelocity()->setZ(static_cast< float >(jCircleParticleEmitter->getDouble(u"vz"_j)));
					emitter->getVelocityRnd()->setX(static_cast< float >(jCircleParticleEmitter->getDouble(u"vrndx"_j)));
					emitter->getVelocityRnd()->setY(static_cast< float >(jCircleParticleEmitter->getDouble(u"vrndy"_j)));
					emitter->getVelocityRnd()->setZ(static_cast< float >(jCircleParticleEmitter->getDouble(u"vrndz"_j)));
					emitter->getColorStart()->setRed(static_cast< float >(jCircleParticleEmitter->getDouble(u"csr"_j)));
					emitter->getColorStart()->setGreen(static_cast< float >(jCircleParticleEmitter->getDouble(u"csg"_j)));
					emitter->getColorStart()->setBlue(static_cast< float >(jCircleParticleEmitter->getDouble(u"csb"_j)));
					emitter->getColorStart()->setAlpha(static_cast< float >(jCircleParticleEmitter->getDouble(u"csa"_j)));
					emitter->getColorEnd()->setRed(static_cast< float >(jCircleParticleEmitter->getDouble(u"cer"_j)));
					emitter->getColorEnd()->setGreen(static_cast< float >(jCircleParticleEmitter->getDouble(u"ceg"_j)));
					emitter->getColorEnd()->setBlue(static_cast< float >(jCircleParticleEmitter->getDouble(u"ceb"_j)));
					emitter->getColorEnd()->setAlpha(static_cast< float >(jCircleParticleEmitter->getDouble(u"cea"_j)));
					emitter->getCenter()->setX(static_cast< float >(jCircleParticleEmitter->getDouble(u"cx"_j)));
					emitter->getCenter()->setY(static_cast< float >(jCircleParticleEmitter->getDouble(u"cy"_j)));
					emitter->getCenter()->setZ(static_cast< float >(jCircleParticleEmitter->getDouble(u"cz"_j)));
					emitter->setRadius(static_cast< float >(jCircleParticleEmitter->getDouble(u"r"_j)));
					emitter->getAxis0()->setX(static_cast< float >(jCircleParticleEmitter->getDouble(u"a0x"_j)));
					emitter->getAxis0()->setY(static_cast< float >(jCircleParticleEmitter->getDouble(u"a0y"_j)));
					emitter->getAxis0()->setZ(static_cast< float >(jCircleParticleEmitter->getDouble(u"a0z"_j)));
					emitter->getAxis1()->setX(static_cast< float >(jCircleParticleEmitter->getDouble(u"a1x"_j)));
					emitter->getAxis1()->setY(static_cast< float >(jCircleParticleEmitter->getDouble(u"a1y"_j)));
					emitter->getAxis1()->setZ(static_cast< float >(jCircleParticleEmitter->getDouble(u"a1z"_j)));
					goto end_switch1;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY)) {
{
					auto jCircleParticleEmitterPlaneVelocity = jParticleSystem->getJSONObject(u"cpeev"_j);
					auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
					emitter->setCount(jCircleParticleEmitterPlaneVelocity->getInt(u"c"_j));
					emitter->setLifeTime(jCircleParticleEmitterPlaneVelocity->getLong(u"lt"_j));
					emitter->setLifeTimeRnd(jCircleParticleEmitterPlaneVelocity->getLong(u"ltrnd"_j));
					emitter->setMass(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"m"_j)));
					emitter->setMassRnd(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"mrnd"_j)));
					emitter->setVelocity(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"v"_j)));
					emitter->setVelocityRnd(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"vrnd"_j)));
					emitter->getColorStart()->setRed(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"csr"_j)));
					emitter->getColorStart()->setGreen(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"csg"_j)));
					emitter->getColorStart()->setBlue(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"csb"_j)));
					emitter->getColorStart()->setAlpha(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"csa"_j)));
					emitter->getColorEnd()->setRed(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"cer"_j)));
					emitter->getColorEnd()->setGreen(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"ceg"_j)));
					emitter->getColorEnd()->setBlue(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"ceb"_j)));
					emitter->getColorEnd()->setAlpha(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"cea"_j)));
					emitter->getCenter()->setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"cx"_j)));
					emitter->getCenter()->setY(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"cy"_j)));
					emitter->getCenter()->setZ(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"cz"_j)));
					emitter->setRadius(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"r"_j)));
					emitter->getAxis0()->setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"a0x"_j)));
					emitter->getAxis0()->setY(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"a0y"_j)));
					emitter->getAxis0()->setZ(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"a0z"_j)));
					emitter->getAxis1()->setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"a1x"_j)));
					emitter->getAxis1()->setY(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"a1y"_j)));
					emitter->getAxis1()->setZ(static_cast< float >(jCircleParticleEmitterPlaneVelocity->getDouble(u"a1z"_j)));
					goto end_switch1;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)) {
{
					auto jSphereParticleEmitter = jParticleSystem->getJSONObject(u"spe"_j);
					auto emitter = particleSystem->getSphereParticleEmitter();
					emitter->setCount(jSphereParticleEmitter->getInt(u"c"_j));
					emitter->setLifeTime(jSphereParticleEmitter->getLong(u"lt"_j));
					emitter->setLifeTimeRnd(jSphereParticleEmitter->getLong(u"ltrnd"_j));
					emitter->setMass(static_cast< float >(jSphereParticleEmitter->getDouble(u"m"_j)));
					emitter->setMassRnd(static_cast< float >(jSphereParticleEmitter->getDouble(u"mrnd"_j)));
					emitter->getVelocity()->setX(static_cast< float >(jSphereParticleEmitter->getDouble(u"vx"_j)));
					emitter->getVelocity()->setY(static_cast< float >(jSphereParticleEmitter->getDouble(u"vy"_j)));
					emitter->getVelocity()->setZ(static_cast< float >(jSphereParticleEmitter->getDouble(u"vz"_j)));
					emitter->getVelocityRnd()->setX(static_cast< float >(jSphereParticleEmitter->getDouble(u"vrndx"_j)));
					emitter->getVelocityRnd()->setY(static_cast< float >(jSphereParticleEmitter->getDouble(u"vrndy"_j)));
					emitter->getVelocityRnd()->setZ(static_cast< float >(jSphereParticleEmitter->getDouble(u"vrndz"_j)));
					emitter->getColorStart()->setRed(static_cast< float >(jSphereParticleEmitter->getDouble(u"csr"_j)));
					emitter->getColorStart()->setGreen(static_cast< float >(jSphereParticleEmitter->getDouble(u"csg"_j)));
					emitter->getColorStart()->setBlue(static_cast< float >(jSphereParticleEmitter->getDouble(u"csb"_j)));
					emitter->getColorStart()->setAlpha(static_cast< float >(jSphereParticleEmitter->getDouble(u"csa"_j)));
					emitter->getColorEnd()->setRed(static_cast< float >(jSphereParticleEmitter->getDouble(u"cer"_j)));
					emitter->getColorEnd()->setGreen(static_cast< float >(jSphereParticleEmitter->getDouble(u"ceg"_j)));
					emitter->getColorEnd()->setBlue(static_cast< float >(jSphereParticleEmitter->getDouble(u"ceb"_j)));
					emitter->getColorEnd()->setAlpha(static_cast< float >(jSphereParticleEmitter->getDouble(u"cea"_j)));
					emitter->getCenter()->setX(static_cast< float >(jSphereParticleEmitter->getDouble(u"cx"_j)));
					emitter->getCenter()->setY(static_cast< float >(jSphereParticleEmitter->getDouble(u"cy"_j)));
					emitter->getCenter()->setZ(static_cast< float >(jSphereParticleEmitter->getDouble(u"cz"_j)));
					emitter->setRadius(static_cast< float >(jSphereParticleEmitter->getDouble(u"r"_j)));
					goto end_switch1;;
				}			}
			if (((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) || ((v != LevelEditorEntityParticleSystem_Emitter::NONE) && (v != LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) && (v != LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)))) {
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ModelMetaDataFileExport::export(): unknown particle system emitter '"_j)->append(static_cast< Object* >(particleSystem->getEmitter()))
					->append(u"'"_j)->toString()));
			}
end_switch1:;
		}

	}
	return levelEditorEntity;
}

LevelEditorEntityBoundingVolume* ModelMetaDataFileImport::parseBoundingVolume(int32_t idx, LevelEditorEntity* levelEditorEntity, JSONObject* jBv) /* throws(JSONException) */
{
	clinit();
	auto entityBoundingVolume = new LevelEditorEntityBoundingVolume(idx, levelEditorEntity);
	BoundingVolume* bv;
	auto bvTypeString = jBv->getString(u"type"_j);
	if (bvTypeString->equalsIgnoreCase(u"none"_j) == true) {
		entityBoundingVolume->setupNone();
	} else if (bvTypeString->equalsIgnoreCase(u"sphere"_j) == true) {
		entityBoundingVolume->setupSphere(new Vector3(static_cast< float >(jBv->getDouble(u"cx"_j)), static_cast< float >(jBv->getDouble(u"cy"_j)), static_cast< float >(jBv->getDouble(u"cz"_j))), static_cast< float >(jBv->getDouble(u"r"_j)));
	} else if (bvTypeString->equalsIgnoreCase(u"capsule"_j) == true) {
		entityBoundingVolume->setupCapsule(new Vector3(static_cast< float >(jBv->getDouble(u"ax"_j)), static_cast< float >(jBv->getDouble(u"ay"_j)), static_cast< float >(jBv->getDouble(u"az"_j))), new Vector3(static_cast< float >(jBv->getDouble(u"bx"_j)), static_cast< float >(jBv->getDouble(u"by"_j)), static_cast< float >(jBv->getDouble(u"bz"_j))), static_cast< float >(jBv->getDouble(u"r"_j)));
	} else if (bvTypeString->equalsIgnoreCase(u"aabb"_j) == true) {
		entityBoundingVolume->setupAabb(new Vector3(static_cast< float >(jBv->getDouble(u"mix"_j)), static_cast< float >(jBv->getDouble(u"miy"_j)), static_cast< float >(jBv->getDouble(u"miz"_j))), new Vector3(static_cast< float >(jBv->getDouble(u"max"_j)), static_cast< float >(jBv->getDouble(u"may"_j)), static_cast< float >(jBv->getDouble(u"maz"_j))));
	} else if (bvTypeString->equalsIgnoreCase(u"obb"_j) == true) {
		entityBoundingVolume->setupObb(new Vector3(static_cast< float >(jBv->getDouble(u"cx"_j)), static_cast< float >(jBv->getDouble(u"cy"_j)), static_cast< float >(jBv->getDouble(u"cz"_j))), new Vector3(static_cast< float >(jBv->getDouble(u"a0x"_j)), static_cast< float >(jBv->getDouble(u"a0y"_j)), static_cast< float >(jBv->getDouble(u"a0z"_j))), new Vector3(static_cast< float >(jBv->getDouble(u"a1x"_j)), static_cast< float >(jBv->getDouble(u"a1y"_j)), static_cast< float >(jBv->getDouble(u"a1z"_j))), new Vector3(static_cast< float >(jBv->getDouble(u"a2x"_j)), static_cast< float >(jBv->getDouble(u"a2y"_j)), static_cast< float >(jBv->getDouble(u"a2z"_j))), new Vector3(static_cast< float >(jBv->getDouble(u"hex"_j)), static_cast< float >(jBv->getDouble(u"hey"_j)), static_cast< float >(jBv->getDouble(u"hez"_j))));
	} else if (bvTypeString->equalsIgnoreCase(u"convexmesh"_j) == true) {
		try {
			entityBoundingVolume->setupConvexMesh(jBv->getString(u"file"_j));
		} catch (Exception* e) {
			e->printStackTrace();
		}
	}
	return entityBoundingVolume;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelMetaDataFileImport::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.files.ModelMetaDataFileImport", 47);
    return c;
}

java::lang::Class* ModelMetaDataFileImport::getClass0()
{
	return class_();
}

