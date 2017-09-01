// Generated from /tdme/src/tdme/tools/shared/files/ModelMetaDataFileImport.java
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>

#include <java/lang/Float.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
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
#include <tdme/os/_FileSystemException.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

#include <ext/jsonbox/Value.h>
#include <ext/jsonbox/Array.h>
#include <ext/jsonbox/JsonException.h>

using tdme::tools::shared::files::ModelMetaDataFileImport;
using java::lang::Float;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::math::Vector3;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
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
using tdme::utils::StringConverter;
using tdme::utils::_Console;
using tdme::utils::_Exception;

using tdme::ext::jsonbox::JsonException;

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

LevelEditorEntity* ModelMetaDataFileImport::doImport(int32_t id, String* pathName, String* fileName) throw (_FileSystemException, JsonException, ModelFileIOException)
{
	auto jsonContent = _FileSystem::getInstance()->getContentAsString(pathName->getCPPWString(), fileName->getCPPWString());

	Value jEntityRoot;
	jEntityRoot.loadFromString(
		StringConverter::toString(jsonContent)
	);

	auto levelEditorEntity = doImportFromJSON(id, pathName, jEntityRoot);

	levelEditorEntity->setEntityFileName(
		::java::lang::StringBuilder().
		 	 append(pathName)->
			 append(u"/"_j)->
			 append(fileName)->
			 toString());

	return levelEditorEntity;
}

LevelEditorEntity* ModelMetaDataFileImport::doImportFromJSON(int32_t id, String* pathName, Value& jEntityRoot) throw (_FileSystemException, JsonException, ModelFileIOException)
{
	LevelEditorEntity* levelEditorEntity;
	auto version = Float::parseFloat(new String(StringConverter::toWideString(jEntityRoot["version"].getString())));
	auto pivot = new Vector3(
		static_cast< float >(jEntityRoot["px"].getDouble()),
		static_cast< float >(jEntityRoot["py"].getDouble()),
		static_cast< float >(jEntityRoot["pz"].getDouble())
	);
	auto modelType = LevelEditorEntity_EntityType::valueOf(StringConverter::toWideString(jEntityRoot["type"].getString()));
	String* modelFile = nullptr;
	if (jEntityRoot["file"].isNull() == false) {
		auto modelFileString = new String(StringConverter::toWideString(jEntityRoot["file"].getString()));
		modelFile = new String(_FileSystem::getInstance()->getCanonicalPath(
			(new String(_FileSystem::getInstance()->getPathName(modelFileString->getCPPWString())))->startsWith(u"/"_j) == true?
				_FileSystem::getInstance()->getPathName(modelFileString->getCPPWString()):
				::java::lang::StringBuilder().
				 	 append(pathName)->
					 append(u"/"_j)->
					 append(_FileSystem::getInstance()->getPathName(modelFileString->getCPPWString()))->
					 toString()->
					 getCPPWString(),
			_FileSystem::getInstance()->getFileName(modelFileString->getCPPWString())
		));
	}
	auto modelThumbnail = jEntityRoot["thumbnail"].isNull() == false? new String(StringConverter::toWideString(jEntityRoot["thumbnail"].getString())) : nullptr;
	auto name = new String(StringConverter::toWideString(jEntityRoot["name"].getString()));
	auto description = new String(StringConverter::toWideString(jEntityRoot["descr"].getString()));
	Model* model = nullptr;
	auto gameRoot = Tools::getGameRootPath(pathName);
	String* modelRelativeFileName = nullptr;
	if (modelFile != nullptr) {
		modelRelativeFileName = Tools::getRelativeResourcesFileName(gameRoot, modelFile);
		auto modelPath =
			::java::lang::StringBuilder().
			 	 append((gameRoot->length() > 0 ? ::java::lang::StringBuilder().append(gameRoot)->append(u"/"_j)->toString() : u""_j))->
				 append(Tools::getPath(modelRelativeFileName))->
				 toString();
		auto modelFile = Tools::getFileName(modelRelativeFileName);
		if (modelRelativeFileName->toLowerCase()->endsWith(u".dae"_j)) {
			model = DAEReader::read(
				modelPath->getCPPWString(),
				modelFile->getCPPWString()
			);
		} else
		if (modelRelativeFileName->toLowerCase()->endsWith(u".tm"_j)) {
			model = TMReader::read(
				modelPath->getCPPWString(),
				modelFile->getCPPWString()
			);
		} else {
			throw new ModelFileIOException(string("Unsupported mode file: ") + StringConverter::toString(modelFile->getCPPWString()));
		}
		if (model == nullptr) {
			_Console::println(L"ModelMetaDataFileImport::doImportFromJSON(): Could not read model from '" + modelPath->getCPPWString() + L"/" + modelFile->getCPPWString() + L"'");
			return nullptr;
		}
	} else
	if (modelType == LevelEditorEntity_EntityType::EMPTY) {
		model = DAEReader::read(L"resources/tools/leveleditor/models", L"arrow.dae");
	}

	levelEditorEntity = new LevelEditorEntity(
		id,
		modelType,
		name,
		description,
		nullptr,
		modelFile != nullptr ? new String(_FileSystem::getInstance()->getCanonicalPath(gameRoot->getCPPWString(), modelRelativeFileName->getCPPWString())) : nullptr,
		modelThumbnail,
		model,
		pivot
	);
	auto jProperties = jEntityRoot["properties"].getArray();
	for (auto i = 0; i < jProperties.size(); i++) {
		auto& jProperty = jProperties[i];
		levelEditorEntity->addProperty(
			new String(StringConverter::toWideString(jProperty["name"].getString())),
			new String(StringConverter::toWideString(jProperty["value"].getString()))
		);
	}

	if (jEntityRoot["bv"].isNull() == false) {
		levelEditorEntity->addBoundingVolume(
			0,
			parseBoundingVolume(
				0,
				levelEditorEntity,
				pathName,
				jEntityRoot["bv"]
			)
		);
	} else
	if (jEntityRoot["bvs"].isNull() == false) {
		auto jBoundingVolumes = jEntityRoot["bvs"].getArray();
		for (auto i = 0; i < jBoundingVolumes.size(); i++) {
			auto& jBv = jBoundingVolumes[i];
			levelEditorEntity->addBoundingVolume(i, parseBoundingVolume(i, levelEditorEntity, pathName, jBv));
		}
	}

	if (modelType == LevelEditorEntity_EntityType::PARTICLESYSTEM) {
		auto particleSystem = levelEditorEntity->getParticleSystem();
		auto& jParticleSystem = jEntityRoot["ps"];
		particleSystem->setType(LevelEditorEntityParticleSystem_Type::valueOf(StringConverter::toWideString(jParticleSystem["t"].getString())));
		{
			auto v = particleSystem->getType();
			if ((v == LevelEditorEntityParticleSystem_Type::NONE)) {
				{
					goto end_switch0;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Type::NONE) || (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM)) {
				{
					auto& jObjectParticleSystem = jParticleSystem["ops"];
					auto objectParticleSystem = particleSystem->getObjectParticleSystem();
					objectParticleSystem->setMaxCount(jObjectParticleSystem["mc"].getInt());
					objectParticleSystem->getScale()->setX(static_cast< float >(jObjectParticleSystem["sx"].getDouble()));
					objectParticleSystem->getScale()->setY(static_cast< float >(jObjectParticleSystem["sy"].getDouble()));
					objectParticleSystem->getScale()->setZ(static_cast< float >(jObjectParticleSystem["sz"].getDouble()));
					objectParticleSystem->setAutoEmit(jObjectParticleSystem["ae"].getBoolean());
					try {
						auto particleModelFile = new String(StringConverter::toWideString(jObjectParticleSystem["mf"].getString()));
						auto particleModelRelativeFileName = Tools::getRelativeResourcesFileName(gameRoot, particleModelFile);
						auto particleModelPath =
							::java::lang::StringBuilder().append((gameRoot->length() > 0 ? ::java::lang::StringBuilder().append(gameRoot)->append(u"/"_j)->toString() : u""_j))->
								append(Tools::getPath(particleModelRelativeFileName))->
								toString();
						objectParticleSystem->setModelFile(
							::java::lang::StringBuilder().
							 append(particleModelPath)->
							 append(u"/"_j)->
							 append(Tools::getFileName(particleModelRelativeFileName))->
							 toString());
					} catch (_Exception& exception) {
						_Console::print(string("ModelMetaDataFileImport::doImport(): An error occurred: "));
						_Console::println(string(exception.what()));
					}
					goto end_switch0;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Type::NONE) || (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) || (v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)) {
				{
					auto& jPointParticleSystem = jParticleSystem["pps"];
					particleSystem->getPointParticleSystem()->setMaxPoints(jPointParticleSystem["mp"].getInt());
					particleSystem->getPointParticleSystem()->setAutoEmit(jPointParticleSystem["ae"].getBoolean());
					goto end_switch0;;
				}			}
			if (((v == LevelEditorEntityParticleSystem_Type::NONE) || (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) || (v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM) || ((v != LevelEditorEntityParticleSystem_Type::NONE) && (v != LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) && (v != LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)))) {
				{
					_Console::println(
						static_cast< Object* >(
							::java::lang::StringBuilder().
							 	 append(u"ModelMetaDataFileExport::export(): unknown particle system type '"_j)->
								 append(static_cast< Object* >(particleSystem->getType()))->
								 append(u"'"_j)->
								 toString()
						 )
					 );
					goto end_switch0;;
				}
			}
			end_switch0:;
		}

		particleSystem->setEmitter(LevelEditorEntityParticleSystem_Emitter::valueOf(StringConverter::toWideString(jParticleSystem["e"].getString())));
		{
			auto v = particleSystem->getEmitter();
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE)) {
				{
					goto end_switch1;;
				}
			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER)) {
				{
					auto& jPointParticleEmitter = jParticleSystem["ppe"];
					auto emitter = particleSystem->getPointParticleEmitter();
					emitter->setCount(jPointParticleEmitter["c"].getInt());
					emitter->setLifeTime(jPointParticleEmitter["lt"].getInt());
					emitter->setLifeTimeRnd(jPointParticleEmitter["ltrnd"].getInt());
					emitter->setMass(static_cast< float >(jPointParticleEmitter["m"].getDouble()));
					emitter->setMassRnd(static_cast< float >(jPointParticleEmitter["mrnd"].getDouble()));
					emitter->getPosition()->setX(static_cast< float >(jPointParticleEmitter["px"].getDouble()));
					emitter->getPosition()->setY(static_cast< float >(jPointParticleEmitter["py"].getDouble()));
					emitter->getPosition()->setZ(static_cast< float >(jPointParticleEmitter["pz"].getDouble()));
					emitter->getVelocity()->setX(static_cast< float >(jPointParticleEmitter["vx"].getDouble()));
					emitter->getVelocity()->setY(static_cast< float >(jPointParticleEmitter["vy"].getDouble()));
					emitter->getVelocity()->setZ(static_cast< float >(jPointParticleEmitter["vz"].getDouble()));
					emitter->getVelocityRnd()->setX(static_cast< float >(jPointParticleEmitter["vrndx"].getDouble()));
					emitter->getVelocityRnd()->setY(static_cast< float >(jPointParticleEmitter["vrndy"].getDouble()));
					emitter->getVelocityRnd()->setZ(static_cast< float >(jPointParticleEmitter["vrndz"].getDouble()));
					emitter->getColorStart()->setRed(static_cast< float >(jPointParticleEmitter["csr"].getDouble()));
					emitter->getColorStart()->setGreen(static_cast< float >(jPointParticleEmitter["csg"].getDouble()));
					emitter->getColorStart()->setBlue(static_cast< float >(jPointParticleEmitter["csb"].getDouble()));
					emitter->getColorStart()->setAlpha(static_cast< float >(jPointParticleEmitter["csa"].getDouble()));
					emitter->getColorEnd()->setRed(static_cast< float >(jPointParticleEmitter["cer"].getDouble()));
					emitter->getColorEnd()->setGreen(static_cast< float >(jPointParticleEmitter["ceg"].getDouble()));
					emitter->getColorEnd()->setBlue(static_cast< float >(jPointParticleEmitter["ceb"].getDouble()));
					emitter->getColorEnd()->setAlpha(static_cast< float >(jPointParticleEmitter["cea"].getDouble()));
					goto end_switch1;;
				}
			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER)) {
				{
					auto& jBoundingBoxParticleEmitter = jParticleSystem["bbpe"];
					auto emitter = particleSystem->getBoundingBoxParticleEmitters();
					emitter->setCount(jBoundingBoxParticleEmitter["c"].getInt());
					emitter->setLifeTime(jBoundingBoxParticleEmitter["lt"].getInt());
					emitter->setLifeTimeRnd(jBoundingBoxParticleEmitter["ltrnd"].getInt());
					emitter->setMass(static_cast< float >(jBoundingBoxParticleEmitter["m"].getDouble()));
					emitter->setMassRnd(static_cast< float >(jBoundingBoxParticleEmitter["mrnd"].getDouble()));
					emitter->getVelocity()->setX(static_cast< float >(jBoundingBoxParticleEmitter["vx"].getDouble()));
					emitter->getVelocity()->setY(static_cast< float >(jBoundingBoxParticleEmitter["vy"].getDouble()));
					emitter->getVelocity()->setZ(static_cast< float >(jBoundingBoxParticleEmitter["vz"].getDouble()));
					emitter->getVelocityRnd()->setX(static_cast< float >(jBoundingBoxParticleEmitter["vrndx"].getDouble()));
					emitter->getVelocityRnd()->setY(static_cast< float >(jBoundingBoxParticleEmitter["vrndy"].getDouble()));
					emitter->getVelocityRnd()->setZ(static_cast< float >(jBoundingBoxParticleEmitter["vrndz"].getDouble()));
					emitter->getColorStart()->setRed(static_cast< float >(jBoundingBoxParticleEmitter["csr"].getDouble()));
					emitter->getColorStart()->setGreen(static_cast< float >(jBoundingBoxParticleEmitter["csg"].getDouble()));
					emitter->getColorStart()->setBlue(static_cast< float >(jBoundingBoxParticleEmitter["csb"].getDouble()));
					emitter->getColorStart()->setAlpha(static_cast< float >(jBoundingBoxParticleEmitter["csa"].getDouble()));
					emitter->getColorEnd()->setRed(static_cast< float >(jBoundingBoxParticleEmitter["cer"].getDouble()));
					emitter->getColorEnd()->setGreen(static_cast< float >(jBoundingBoxParticleEmitter["ceg"].getDouble()));
					emitter->getColorEnd()->setBlue(static_cast< float >(jBoundingBoxParticleEmitter["ceb"].getDouble()));
					emitter->getColorEnd()->setAlpha(static_cast< float >(jBoundingBoxParticleEmitter["cea"].getDouble()));
					emitter->getObbCenter()->setX(static_cast< float >(jBoundingBoxParticleEmitter["ocx"].getDouble()));
					emitter->getObbCenter()->setY(static_cast< float >(jBoundingBoxParticleEmitter["ocy"].getDouble()));
					emitter->getObbCenter()->setZ(static_cast< float >(jBoundingBoxParticleEmitter["ocz"].getDouble()));
					emitter->getObbHalfextension()->setX(static_cast< float >(jBoundingBoxParticleEmitter["ohex"].getDouble()));
					emitter->getObbHalfextension()->setY(static_cast< float >(jBoundingBoxParticleEmitter["ohey"].getDouble()));
					emitter->getObbHalfextension()->setZ(static_cast< float >(jBoundingBoxParticleEmitter["ohez"].getDouble()));
					emitter->getObbAxis0()->setX(static_cast< float >(jBoundingBoxParticleEmitter["oa0x"].getDouble()));
					emitter->getObbAxis0()->setY(static_cast< float >(jBoundingBoxParticleEmitter["oa0y"].getDouble()));
					emitter->getObbAxis0()->setZ(static_cast< float >(jBoundingBoxParticleEmitter["oa0z"].getDouble()));
					emitter->getObbAxis1()->setX(static_cast< float >(jBoundingBoxParticleEmitter["oa1x"].getDouble()));
					emitter->getObbAxis1()->setY(static_cast< float >(jBoundingBoxParticleEmitter["oa1y"].getDouble()));
					emitter->getObbAxis1()->setZ(static_cast< float >(jBoundingBoxParticleEmitter["oa1z"].getDouble()));
					emitter->getObbAxis2()->setX(static_cast< float >(jBoundingBoxParticleEmitter["oa2x"].getDouble()));
					emitter->getObbAxis2()->setY(static_cast< float >(jBoundingBoxParticleEmitter["oa2y"].getDouble()));
					emitter->getObbAxis2()->setZ(static_cast< float >(jBoundingBoxParticleEmitter["oa2z"].getDouble()));
					goto end_switch1;;
				}
			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER)) {
				{
					auto& jCircleParticleEmitter = jParticleSystem["cpe"];
					auto emitter = particleSystem->getCircleParticleEmitter();
					emitter->setCount(jCircleParticleEmitter["c"].getInt());
					emitter->setLifeTime(jCircleParticleEmitter["lt"].getInt());
					emitter->setLifeTimeRnd(jCircleParticleEmitter["ltrnd"].getInt());
					emitter->setMass(static_cast< float >(jCircleParticleEmitter["m"].getDouble()));
					emitter->setMassRnd(static_cast< float >(jCircleParticleEmitter["mrnd"].getDouble()));
					emitter->getVelocity()->setX(static_cast< float >(jCircleParticleEmitter["vx"].getDouble()));
					emitter->getVelocity()->setY(static_cast< float >(jCircleParticleEmitter["vy"].getDouble()));
					emitter->getVelocity()->setZ(static_cast< float >(jCircleParticleEmitter["vz"].getDouble()));
					emitter->getVelocityRnd()->setX(static_cast< float >(jCircleParticleEmitter["vrndx"].getDouble()));
					emitter->getVelocityRnd()->setY(static_cast< float >(jCircleParticleEmitter["vrndy"].getDouble()));
					emitter->getVelocityRnd()->setZ(static_cast< float >(jCircleParticleEmitter["vrndz"].getDouble()));
					emitter->getColorStart()->setRed(static_cast< float >(jCircleParticleEmitter["csr"].getDouble()));
					emitter->getColorStart()->setGreen(static_cast< float >(jCircleParticleEmitter["csg"].getDouble()));
					emitter->getColorStart()->setBlue(static_cast< float >(jCircleParticleEmitter["csb"].getDouble()));
					emitter->getColorStart()->setAlpha(static_cast< float >(jCircleParticleEmitter["csa"].getDouble()));
					emitter->getColorEnd()->setRed(static_cast< float >(jCircleParticleEmitter["cer"].getDouble()));
					emitter->getColorEnd()->setGreen(static_cast< float >(jCircleParticleEmitter["ceg"].getDouble()));
					emitter->getColorEnd()->setBlue(static_cast< float >(jCircleParticleEmitter["ceb"].getDouble()));
					emitter->getColorEnd()->setAlpha(static_cast< float >(jCircleParticleEmitter["cea"].getDouble()));
					emitter->getCenter()->setX(static_cast< float >(jCircleParticleEmitter["cx"].getDouble()));
					emitter->getCenter()->setY(static_cast< float >(jCircleParticleEmitter["cy"].getDouble()));
					emitter->getCenter()->setZ(static_cast< float >(jCircleParticleEmitter["cz"].getDouble()));
					emitter->setRadius(static_cast< float >(jCircleParticleEmitter["r"].getDouble()));
					emitter->getAxis0()->setX(static_cast< float >(jCircleParticleEmitter["a0x"].getDouble()));
					emitter->getAxis0()->setY(static_cast< float >(jCircleParticleEmitter["a0y"].getDouble()));
					emitter->getAxis0()->setZ(static_cast< float >(jCircleParticleEmitter["a0z"].getDouble()));
					emitter->getAxis1()->setX(static_cast< float >(jCircleParticleEmitter["a1x"].getDouble()));
					emitter->getAxis1()->setY(static_cast< float >(jCircleParticleEmitter["a1y"].getDouble()));
					emitter->getAxis1()->setZ(static_cast< float >(jCircleParticleEmitter["a1z"].getDouble()));
					goto end_switch1;;
				}
			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY)) {
				{
					auto& jCircleParticleEmitterPlaneVelocity = jParticleSystem["cpeev"];
					auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
					emitter->setCount(jCircleParticleEmitterPlaneVelocity["c"].getInt());
					emitter->setLifeTime(jCircleParticleEmitterPlaneVelocity["lt"].getInt());
					emitter->setLifeTimeRnd(jCircleParticleEmitterPlaneVelocity["ltrnd"].getInt());
					emitter->setMass(static_cast< float >(jCircleParticleEmitterPlaneVelocity["m"].getDouble()));
					emitter->setMassRnd(static_cast< float >(jCircleParticleEmitterPlaneVelocity["mrnd"].getDouble()));
					emitter->setVelocity(static_cast< float >(jCircleParticleEmitterPlaneVelocity["v"].getDouble()));
					emitter->setVelocityRnd(static_cast< float >(jCircleParticleEmitterPlaneVelocity["vrnd"].getDouble()));
					emitter->getColorStart()->setRed(static_cast< float >(jCircleParticleEmitterPlaneVelocity["csr"].getDouble()));
					emitter->getColorStart()->setGreen(static_cast< float >(jCircleParticleEmitterPlaneVelocity["csg"].getDouble()));
					emitter->getColorStart()->setBlue(static_cast< float >(jCircleParticleEmitterPlaneVelocity["csb"].getDouble()));
					emitter->getColorStart()->setAlpha(static_cast< float >(jCircleParticleEmitterPlaneVelocity["csa"].getDouble()));
					emitter->getColorEnd()->setRed(static_cast< float >(jCircleParticleEmitterPlaneVelocity["cer"].getDouble()));
					emitter->getColorEnd()->setGreen(static_cast< float >(jCircleParticleEmitterPlaneVelocity["ceg"].getDouble()));
					emitter->getColorEnd()->setBlue(static_cast< float >(jCircleParticleEmitterPlaneVelocity["ceb"].getDouble()));
					emitter->getColorEnd()->setAlpha(static_cast< float >(jCircleParticleEmitterPlaneVelocity["cea"].getDouble()));
					emitter->getCenter()->setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["cx"].getDouble()));
					emitter->getCenter()->setY(static_cast< float >(jCircleParticleEmitterPlaneVelocity["cy"].getDouble()));
					emitter->getCenter()->setZ(static_cast< float >(jCircleParticleEmitterPlaneVelocity["cz"].getDouble()));
					emitter->setRadius(static_cast< float >(jCircleParticleEmitterPlaneVelocity["r"].getDouble()));
					emitter->getAxis0()->setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a0x"].getDouble()));
					emitter->getAxis0()->setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a0y"].getDouble()));
					emitter->getAxis0()->setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a0z"].getDouble()));
					emitter->getAxis1()->setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a1x"].getDouble()));
					emitter->getAxis1()->setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a1y"].getDouble()));
					emitter->getAxis1()->setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a1z"].getDouble()));
					goto end_switch1;;
				}
			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)) {
				{
					auto& jSphereParticleEmitter = jParticleSystem["spe"];
					auto emitter = particleSystem->getSphereParticleEmitter();
					emitter->setCount(jSphereParticleEmitter["c"].getInt());
					emitter->setLifeTime(jSphereParticleEmitter["lt"].getInt());
					emitter->setLifeTimeRnd(jSphereParticleEmitter["ltrnd"].getInt());
					emitter->setMass(static_cast< float >(jSphereParticleEmitter["m"].getDouble()));
					emitter->setMassRnd(static_cast< float >(jSphereParticleEmitter["mrnd"].getDouble()));
					emitter->getVelocity()->setX(static_cast< float >(jSphereParticleEmitter["vx"].getDouble()));
					emitter->getVelocity()->setY(static_cast< float >(jSphereParticleEmitter["vy"].getDouble()));
					emitter->getVelocity()->setZ(static_cast< float >(jSphereParticleEmitter["vz"].getDouble()));
					emitter->getVelocityRnd()->setX(static_cast< float >(jSphereParticleEmitter["vrndx"].getDouble()));
					emitter->getVelocityRnd()->setY(static_cast< float >(jSphereParticleEmitter["vrndy"].getDouble()));
					emitter->getVelocityRnd()->setZ(static_cast< float >(jSphereParticleEmitter["vrndz"].getDouble()));
					emitter->getColorStart()->setRed(static_cast< float >(jSphereParticleEmitter["csr"].getDouble()));
					emitter->getColorStart()->setGreen(static_cast< float >(jSphereParticleEmitter["csg"].getDouble()));
					emitter->getColorStart()->setBlue(static_cast< float >(jSphereParticleEmitter["csb"].getDouble()));
					emitter->getColorStart()->setAlpha(static_cast< float >(jSphereParticleEmitter["csa"].getDouble()));
					emitter->getColorEnd()->setRed(static_cast< float >(jSphereParticleEmitter["cer"].getDouble()));
					emitter->getColorEnd()->setGreen(static_cast< float >(jSphereParticleEmitter["ceg"].getDouble()));
					emitter->getColorEnd()->setBlue(static_cast< float >(jSphereParticleEmitter["ceb"].getDouble()));
					emitter->getColorEnd()->setAlpha(static_cast< float >(jSphereParticleEmitter["cea"].getDouble()));
					emitter->getCenter()->setX(static_cast< float >(jSphereParticleEmitter["cx"].getDouble()));
					emitter->getCenter()->setY(static_cast< float >(jSphereParticleEmitter["cy"].getDouble()));
					emitter->getCenter()->setZ(static_cast< float >(jSphereParticleEmitter["cz"].getDouble()));
					emitter->setRadius(static_cast< float >(jSphereParticleEmitter["r"].getDouble()));
					goto end_switch1;;
				}
			}
			if (((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) || ((v != LevelEditorEntityParticleSystem_Emitter::NONE) && (v != LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) && (v != LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)))) {
				_Console::println(
					static_cast< Object* >(
						::java::lang::StringBuilder().
						 	 append(u"ModelMetaDataFileExport::export(): unknown particle system emitter '"_j)->
							 append(static_cast< Object* >(particleSystem->getEmitter()))->
							 append(u"'"_j)->toString()
					 )
				 );
			}
			end_switch1:;
		}

	}
	return levelEditorEntity;
}

LevelEditorEntityBoundingVolume* ModelMetaDataFileImport::parseBoundingVolume(int32_t idx, LevelEditorEntity* levelEditorEntity, String* pathName, Value& jBv) throw (_FileSystemException, JsonException, ModelFileIOException)
{
	auto entityBoundingVolume = new LevelEditorEntityBoundingVolume(idx, levelEditorEntity);
	BoundingVolume* bv;
	auto bvTypeString = new String(StringConverter::toWideString(jBv["type"].getString()));
	if (bvTypeString->equalsIgnoreCase(u"none"_j) == true) {
		entityBoundingVolume->setupNone();
	} else
	if (bvTypeString->equalsIgnoreCase(u"sphere"_j) == true) {
		entityBoundingVolume->setupSphere(
			new Vector3(
				static_cast< float >(jBv["cx"].getDouble()),
				static_cast< float >(jBv["cy"].getDouble()),
				static_cast< float >(jBv["cz"].getDouble())
			),
			static_cast< float >(jBv["r"].getDouble())
		);
	} else
	if (bvTypeString->equalsIgnoreCase(u"capsule"_j) == true) {
		entityBoundingVolume->setupCapsule(
			new Vector3(
				static_cast< float >(jBv["ax"].getDouble()),
				static_cast< float >(jBv["ay"].getDouble()),
				static_cast< float >(jBv["az"].getDouble())
			),
			new Vector3(
				static_cast< float >(jBv["bx"].getDouble()),
				static_cast< float >(jBv["by"].getDouble()),
				static_cast< float >(jBv["bz"].getDouble())
			),
			static_cast< float >(jBv["r"].getDouble())
		);
	} else
	if (bvTypeString->equalsIgnoreCase(u"aabb"_j) == true) {
		entityBoundingVolume->setupAabb(
			new Vector3(
				static_cast< float >(jBv["mix"].getDouble()),
				static_cast< float >(jBv["miy"].getDouble()),
				static_cast< float >(jBv["miz"].getDouble())
			),
			new Vector3(
				static_cast< float >(jBv["max"].getDouble()),
				static_cast< float >(jBv["may"].getDouble()),
				static_cast< float >(jBv["maz"].getDouble())
			)
		);
	} else
	if (bvTypeString->equalsIgnoreCase(u"obb"_j) == true) {
		entityBoundingVolume->setupObb(
			new Vector3(
				static_cast< float >(jBv["cx"].getDouble()),
				static_cast< float >(jBv["cy"].getDouble()),
				static_cast< float >(jBv["cz"].getDouble())
			),
			new Vector3(
				static_cast< float >(jBv["a0x"].getDouble()),
				static_cast< float >(jBv["a0y"].getDouble()),
				static_cast< float >(jBv["a0z"].getDouble())
			),
			new Vector3(
				static_cast< float >(jBv["a1x"].getDouble()),
				static_cast< float >(jBv["a1y"].getDouble()),
				static_cast< float >(jBv["a1z"].getDouble())
			),
			new Vector3(
				static_cast< float >(jBv["a2x"].getDouble()),
				static_cast< float >(jBv["a2y"].getDouble()),
				static_cast< float >(jBv["a2z"].getDouble())
			),
			new Vector3(
				static_cast< float >(jBv["hex"].getDouble()),
				static_cast< float >(jBv["hey"].getDouble()),
				static_cast< float >(jBv["hez"].getDouble())
			)
		);
	} else
	if (bvTypeString->equalsIgnoreCase(u"convexmesh"_j) == true) {
		try {
			entityBoundingVolume->setupConvexMesh(pathName, new String(StringConverter::toWideString(jBv["file"].getString())));
		} catch (_Exception& exception) {
			_Console::print(string("ModelMetaDataFileImport::parseBoundingVolume(): An error occurred: "));
			_Console::println(string(exception.what()));
		}
	}
	return entityBoundingVolume;
}
