#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>

#include <string>

#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityAudio.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/model/LevelEditorEntityModel.h>
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
#include <tdme/tools/shared/model/LevelEditorEntityPhysics.h>
#include <tdme/tools/shared/model/LevelEditorEntityPhysics_BodyType.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

#include <ext/jsonbox/Value.h>
#include <ext/jsonbox/Array.h>
#include <ext/jsonbox/JsonException.h>

using std::string;

using tdme::engine::LODObject3D;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityAudio;
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
using tdme::tools::shared::model::LevelEditorEntityPhysics;
using tdme::tools::shared::model::LevelEditorEntityPhysics_BodyType;
using tdme::tools::shared::tools::Tools;
using tdme::utils::Float;
using tdme::utils::StringUtils;
using tdme::utils::Console;
using tdme::utils::Exception;

using tdme::ext::jsonbox::JsonException;

LevelEditorEntity* ModelMetaDataFileImport::doImport(int32_t id, const string& pathName, const string& fileName) throw (FileSystemException, JsonException, ModelFileIOException)
{
	auto jsonContent = FileSystem::getInstance()->getContentAsString(pathName, fileName);

	Value jEntityRoot;
	jEntityRoot.loadFromString(
		(jsonContent)
	);

	auto levelEditorEntity = doImportFromJSON(id, pathName, jEntityRoot);
	levelEditorEntity->setEntityFileName(pathName + "/" + fileName);
	return levelEditorEntity;
}

LevelEditorEntity* ModelMetaDataFileImport::doImportFromJSON(int32_t id, const string& pathName, Value& jEntityRoot) throw (FileSystemException, JsonException, ModelFileIOException)
{
	LevelEditorEntity* levelEditorEntity;
	auto version = Float::parseFloat((jEntityRoot["version"].getString()));
	auto pivot = Vector3(
		static_cast< float >(jEntityRoot["px"].getDouble()),
		static_cast< float >(jEntityRoot["py"].getDouble()),
		static_cast< float >(jEntityRoot["pz"].getDouble())
	);
	auto modelType = LevelEditorEntity_EntityType::valueOf((jEntityRoot["type"].getString()));
	auto modelThumbnail = jEntityRoot["thumbnail"].isNull() == false? (jEntityRoot["thumbnail"].getString()) : "";
	auto name = (jEntityRoot["name"].getString());
	auto description = (jEntityRoot["descr"].getString());
	string modelFileName = "";
	string modelPathName = "";
	if (jEntityRoot["file"].isNull() == false) {
		modelFileName = (jEntityRoot["file"].getString());
	}
	Model* model = nullptr;
	if (modelFileName.length() > 0) {
		modelPathName = getResourcePathName(pathName, modelFileName);
		model = ModelReader::read(
			modelPathName,
			FileSystem::getInstance()->getFileName(modelFileName)
		);
	} else
	if (modelType == LevelEditorEntity_EntityType::EMPTY) {
		model = ModelReader::read("resources/tools/leveleditor/models", "empty.dae");
	}

	levelEditorEntity = new LevelEditorEntity(
		id,
		modelType,
		name,
		description,
		"",
		modelFileName.length() > 0 ? modelPathName + "/" + FileSystem::getInstance()->getFileName(modelFileName) : "",
		modelThumbnail,
		model,
		pivot
	);
	auto jProperties = jEntityRoot["properties"].getArray();
	for (auto i = 0; i < jProperties.size(); i++) {
		auto& jProperty = jProperties[i];
		levelEditorEntity->addProperty(
			(jProperty["name"].getString()),
			(jProperty["value"].getString())
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
	if (jEntityRoot["p"].isNull() == false && levelEditorEntity->getPhysics() != nullptr) {
		auto physics = levelEditorEntity->getPhysics();
		auto& jPhysics = jEntityRoot["p"];
		physics->setType(LevelEditorEntityPhysics_BodyType::valueOf(jPhysics["type"].getString()));
		physics->setMass(static_cast<float>(jPhysics["mass"].getDouble()));
		physics->setRestitution(static_cast<float>(jPhysics["restitution"].getDouble()));
		physics->setFriction(static_cast<float>(jPhysics["friction"].getDouble()));
		physics->setInertiaTensor(
			Vector3(
				static_cast<float>(jPhysics["itx"].getDouble()),
				static_cast<float>(jPhysics["ity"].getDouble()),
				static_cast<float>(jPhysics["itz"].getDouble())
			)
		);
	}
	if (modelType == LevelEditorEntity_EntityType::MODEL) {
		levelEditorEntity->getModelSettings()->setTerrainMesh(jEntityRoot["tm"].getBoolean());
		// TODO: remove me, this is a work around for haveing a UE terrain FBX with normals only showing up
		if (levelEditorEntity->getModelSettings()->isTerrainMesh() == true) ModelHelper::computeNormals(model);
		if (jEntityRoot["ll2"].isNull() == false) levelEditorEntity->setLODLevel2(parseLODLevel(pathName, jEntityRoot["ll2"]));
		if (jEntityRoot["ll3"].isNull() == false) levelEditorEntity->setLODLevel3(parseLODLevel(pathName, jEntityRoot["ll3"]));
		if (jEntityRoot["as"].isNull() == false) {
			for (auto jAnimationSound: jEntityRoot["as"].getArray()) {
				auto animationName = jAnimationSound["i"].getString();
				auto animationSound = levelEditorEntity->getModelSettings()->createAnimationSound(animationName);
				animationSound->setFileName(jAnimationSound["file"].getString());
				animationSound->setGain(static_cast<float>(jAnimationSound["g"].getDouble()));
				animationSound->setPitch(static_cast<float>(jAnimationSound["p"].getDouble()));
				animationSound->setOffset(static_cast<float>(jAnimationSound["o"].getInt()));
				animationSound->setLooping(jAnimationSound["l"].getBoolean());
				animationSound->setFixed(jAnimationSound["f"].getBoolean());
			}
		}
	} else
	if (modelType == LevelEditorEntity_EntityType::PARTICLESYSTEM) {
		auto particleSystem = levelEditorEntity->getParticleSystem();
		auto& jParticleSystem = jEntityRoot["ps"];
		particleSystem->setType(LevelEditorEntityParticleSystem_Type::valueOf((jParticleSystem["t"].getString())));
		{
			auto v = particleSystem->getType();
			if (v == LevelEditorEntityParticleSystem_Type::NONE) {
				// no op
			} else
			if (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) {
				auto& jObjectParticleSystem = jParticleSystem["ops"];
				auto objectParticleSystem = particleSystem->getObjectParticleSystem();
				objectParticleSystem->setMaxCount(jObjectParticleSystem["mc"].getInt());
				objectParticleSystem->getScale().setX(static_cast< float >(jObjectParticleSystem["sx"].getDouble()));
				objectParticleSystem->getScale().setY(static_cast< float >(jObjectParticleSystem["sy"].getDouble()));
				objectParticleSystem->getScale().setZ(static_cast< float >(jObjectParticleSystem["sz"].getDouble()));
				objectParticleSystem->setAutoEmit(jObjectParticleSystem["ae"].getBoolean());
				try {
					auto particleModelFile = (jObjectParticleSystem["mf"].getString());
					auto particleModelPath = getResourcePathName(pathName, particleModelFile);
					objectParticleSystem->setModelFile(
						particleModelPath + "/" + Tools::getFileName(particleModelFile)
					);
				} catch (Exception& exception) {
					Console::print(string("ModelMetaDataFileImport::doImport(): An error occurred: "));
					Console::println(string(exception.what()));
				}
			} else
			if (v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM) {
				auto& jPointParticleSystem = jParticleSystem["pps"];
				particleSystem->getPointParticleSystem()->setMaxPoints(jPointParticleSystem["mp"].getInt());
				particleSystem->getPointParticleSystem()->setAutoEmit(jPointParticleSystem["ae"].getBoolean());
			} else {
				Console::println(
					string(
						 "ModelMetaDataFileExport::export(): unknown particle system type '" +
						 particleSystem->getType()->getName() +
						 "'"
					 )
				 );
			}
		}

		particleSystem->setEmitter(LevelEditorEntityParticleSystem_Emitter::valueOf((jParticleSystem["e"].getString())));
		{
			auto v = particleSystem->getEmitter();
			if (v == LevelEditorEntityParticleSystem_Emitter::NONE) {
				// no op
			} else
			if (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) {
				auto& jPointParticleEmitter = jParticleSystem["ppe"];
				auto emitter = particleSystem->getPointParticleEmitter();
				emitter->setCount(jPointParticleEmitter["c"].getInt());
				emitter->setLifeTime(jPointParticleEmitter["lt"].getInt());
				emitter->setLifeTimeRnd(jPointParticleEmitter["ltrnd"].getInt());
				emitter->setMass(static_cast< float >(jPointParticleEmitter["m"].getDouble()));
				emitter->setMassRnd(static_cast< float >(jPointParticleEmitter["mrnd"].getDouble()));
				emitter->getPosition().setX(static_cast< float >(jPointParticleEmitter["px"].getDouble()));
				emitter->getPosition().setY(static_cast< float >(jPointParticleEmitter["py"].getDouble()));
				emitter->getPosition().setZ(static_cast< float >(jPointParticleEmitter["pz"].getDouble()));
				emitter->getVelocity().setX(static_cast< float >(jPointParticleEmitter["vx"].getDouble()));
				emitter->getVelocity().setY(static_cast< float >(jPointParticleEmitter["vy"].getDouble()));
				emitter->getVelocity().setZ(static_cast< float >(jPointParticleEmitter["vz"].getDouble()));
				emitter->getVelocityRnd().setX(static_cast< float >(jPointParticleEmitter["vrndx"].getDouble()));
				emitter->getVelocityRnd().setY(static_cast< float >(jPointParticleEmitter["vrndy"].getDouble()));
				emitter->getVelocityRnd().setZ(static_cast< float >(jPointParticleEmitter["vrndz"].getDouble()));
				emitter->getColorStart().setRed(static_cast< float >(jPointParticleEmitter["csr"].getDouble()));
				emitter->getColorStart().setGreen(static_cast< float >(jPointParticleEmitter["csg"].getDouble()));
				emitter->getColorStart().setBlue(static_cast< float >(jPointParticleEmitter["csb"].getDouble()));
				emitter->getColorStart().setAlpha(static_cast< float >(jPointParticleEmitter["csa"].getDouble()));
				emitter->getColorEnd().setRed(static_cast< float >(jPointParticleEmitter["cer"].getDouble()));
				emitter->getColorEnd().setGreen(static_cast< float >(jPointParticleEmitter["ceg"].getDouble()));
				emitter->getColorEnd().setBlue(static_cast< float >(jPointParticleEmitter["ceb"].getDouble()));
				emitter->getColorEnd().setAlpha(static_cast< float >(jPointParticleEmitter["cea"].getDouble()));
			} else
			if (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) {
				auto& jBoundingBoxParticleEmitter = jParticleSystem["bbpe"];
				auto emitter = particleSystem->getBoundingBoxParticleEmitters();
				emitter->setCount(jBoundingBoxParticleEmitter["c"].getInt());
				emitter->setLifeTime(jBoundingBoxParticleEmitter["lt"].getInt());
				emitter->setLifeTimeRnd(jBoundingBoxParticleEmitter["ltrnd"].getInt());
				emitter->setMass(static_cast< float >(jBoundingBoxParticleEmitter["m"].getDouble()));
				emitter->setMassRnd(static_cast< float >(jBoundingBoxParticleEmitter["mrnd"].getDouble()));
				emitter->getVelocity().setX(static_cast< float >(jBoundingBoxParticleEmitter["vx"].getDouble()));
				emitter->getVelocity().setY(static_cast< float >(jBoundingBoxParticleEmitter["vy"].getDouble()));
				emitter->getVelocity().setZ(static_cast< float >(jBoundingBoxParticleEmitter["vz"].getDouble()));
				emitter->getVelocityRnd().setX(static_cast< float >(jBoundingBoxParticleEmitter["vrndx"].getDouble()));
				emitter->getVelocityRnd().setY(static_cast< float >(jBoundingBoxParticleEmitter["vrndy"].getDouble()));
				emitter->getVelocityRnd().setZ(static_cast< float >(jBoundingBoxParticleEmitter["vrndz"].getDouble()));
				emitter->getColorStart().setRed(static_cast< float >(jBoundingBoxParticleEmitter["csr"].getDouble()));
				emitter->getColorStart().setGreen(static_cast< float >(jBoundingBoxParticleEmitter["csg"].getDouble()));
				emitter->getColorStart().setBlue(static_cast< float >(jBoundingBoxParticleEmitter["csb"].getDouble()));
				emitter->getColorStart().setAlpha(static_cast< float >(jBoundingBoxParticleEmitter["csa"].getDouble()));
				emitter->getColorEnd().setRed(static_cast< float >(jBoundingBoxParticleEmitter["cer"].getDouble()));
				emitter->getColorEnd().setGreen(static_cast< float >(jBoundingBoxParticleEmitter["ceg"].getDouble()));
				emitter->getColorEnd().setBlue(static_cast< float >(jBoundingBoxParticleEmitter["ceb"].getDouble()));
				emitter->getColorEnd().setAlpha(static_cast< float >(jBoundingBoxParticleEmitter["cea"].getDouble()));
				emitter->getObbCenter().setX(static_cast< float >(jBoundingBoxParticleEmitter["ocx"].getDouble()));
				emitter->getObbCenter().setY(static_cast< float >(jBoundingBoxParticleEmitter["ocy"].getDouble()));
				emitter->getObbCenter().setZ(static_cast< float >(jBoundingBoxParticleEmitter["ocz"].getDouble()));
				emitter->getObbHalfextension().setX(static_cast< float >(jBoundingBoxParticleEmitter["ohex"].getDouble()));
				emitter->getObbHalfextension().setY(static_cast< float >(jBoundingBoxParticleEmitter["ohey"].getDouble()));
				emitter->getObbHalfextension().setZ(static_cast< float >(jBoundingBoxParticleEmitter["ohez"].getDouble()));
				emitter->getObbAxis0().setX(static_cast< float >(jBoundingBoxParticleEmitter["oa0x"].getDouble()));
				emitter->getObbAxis0().setY(static_cast< float >(jBoundingBoxParticleEmitter["oa0y"].getDouble()));
				emitter->getObbAxis0().setZ(static_cast< float >(jBoundingBoxParticleEmitter["oa0z"].getDouble()));
				emitter->getObbAxis1().setX(static_cast< float >(jBoundingBoxParticleEmitter["oa1x"].getDouble()));
				emitter->getObbAxis1().setY(static_cast< float >(jBoundingBoxParticleEmitter["oa1y"].getDouble()));
				emitter->getObbAxis1().setZ(static_cast< float >(jBoundingBoxParticleEmitter["oa1z"].getDouble()));
				emitter->getObbAxis2().setX(static_cast< float >(jBoundingBoxParticleEmitter["oa2x"].getDouble()));
				emitter->getObbAxis2().setY(static_cast< float >(jBoundingBoxParticleEmitter["oa2y"].getDouble()));
				emitter->getObbAxis2().setZ(static_cast< float >(jBoundingBoxParticleEmitter["oa2z"].getDouble()));
			} else
			if (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) {
				auto& jCircleParticleEmitter = jParticleSystem["cpe"];
				auto emitter = particleSystem->getCircleParticleEmitter();
				emitter->setCount(jCircleParticleEmitter["c"].getInt());
				emitter->setLifeTime(jCircleParticleEmitter["lt"].getInt());
				emitter->setLifeTimeRnd(jCircleParticleEmitter["ltrnd"].getInt());
				emitter->setMass(static_cast< float >(jCircleParticleEmitter["m"].getDouble()));
				emitter->setMassRnd(static_cast< float >(jCircleParticleEmitter["mrnd"].getDouble()));
				emitter->getVelocity().setX(static_cast< float >(jCircleParticleEmitter["vx"].getDouble()));
				emitter->getVelocity().setY(static_cast< float >(jCircleParticleEmitter["vy"].getDouble()));
				emitter->getVelocity().setZ(static_cast< float >(jCircleParticleEmitter["vz"].getDouble()));
				emitter->getVelocityRnd().setX(static_cast< float >(jCircleParticleEmitter["vrndx"].getDouble()));
				emitter->getVelocityRnd().setY(static_cast< float >(jCircleParticleEmitter["vrndy"].getDouble()));
				emitter->getVelocityRnd().setZ(static_cast< float >(jCircleParticleEmitter["vrndz"].getDouble()));
				emitter->getColorStart().setRed(static_cast< float >(jCircleParticleEmitter["csr"].getDouble()));
				emitter->getColorStart().setGreen(static_cast< float >(jCircleParticleEmitter["csg"].getDouble()));
				emitter->getColorStart().setBlue(static_cast< float >(jCircleParticleEmitter["csb"].getDouble()));
				emitter->getColorStart().setAlpha(static_cast< float >(jCircleParticleEmitter["csa"].getDouble()));
				emitter->getColorEnd().setRed(static_cast< float >(jCircleParticleEmitter["cer"].getDouble()));
				emitter->getColorEnd().setGreen(static_cast< float >(jCircleParticleEmitter["ceg"].getDouble()));
				emitter->getColorEnd().setBlue(static_cast< float >(jCircleParticleEmitter["ceb"].getDouble()));
				emitter->getColorEnd().setAlpha(static_cast< float >(jCircleParticleEmitter["cea"].getDouble()));
				emitter->getCenter().setX(static_cast< float >(jCircleParticleEmitter["cx"].getDouble()));
				emitter->getCenter().setY(static_cast< float >(jCircleParticleEmitter["cy"].getDouble()));
				emitter->getCenter().setZ(static_cast< float >(jCircleParticleEmitter["cz"].getDouble()));
				emitter->setRadius(static_cast< float >(jCircleParticleEmitter["r"].getDouble()));
				emitter->getAxis0().setX(static_cast< float >(jCircleParticleEmitter["a0x"].getDouble()));
				emitter->getAxis0().setY(static_cast< float >(jCircleParticleEmitter["a0y"].getDouble()));
				emitter->getAxis0().setZ(static_cast< float >(jCircleParticleEmitter["a0z"].getDouble()));
				emitter->getAxis1().setX(static_cast< float >(jCircleParticleEmitter["a1x"].getDouble()));
				emitter->getAxis1().setY(static_cast< float >(jCircleParticleEmitter["a1y"].getDouble()));
				emitter->getAxis1().setZ(static_cast< float >(jCircleParticleEmitter["a1z"].getDouble()));
			} else
			if (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
				auto& jCircleParticleEmitterPlaneVelocity = jParticleSystem["cpeev"];
				auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
				emitter->setCount(jCircleParticleEmitterPlaneVelocity["c"].getInt());
				emitter->setLifeTime(jCircleParticleEmitterPlaneVelocity["lt"].getInt());
				emitter->setLifeTimeRnd(jCircleParticleEmitterPlaneVelocity["ltrnd"].getInt());
				emitter->setMass(static_cast< float >(jCircleParticleEmitterPlaneVelocity["m"].getDouble()));
				emitter->setMassRnd(static_cast< float >(jCircleParticleEmitterPlaneVelocity["mrnd"].getDouble()));
				emitter->setVelocity(static_cast< float >(jCircleParticleEmitterPlaneVelocity["v"].getDouble()));
				emitter->setVelocityRnd(static_cast< float >(jCircleParticleEmitterPlaneVelocity["vrnd"].getDouble()));
				emitter->getColorStart().setRed(static_cast< float >(jCircleParticleEmitterPlaneVelocity["csr"].getDouble()));
				emitter->getColorStart().setGreen(static_cast< float >(jCircleParticleEmitterPlaneVelocity["csg"].getDouble()));
				emitter->getColorStart().setBlue(static_cast< float >(jCircleParticleEmitterPlaneVelocity["csb"].getDouble()));
				emitter->getColorStart().setAlpha(static_cast< float >(jCircleParticleEmitterPlaneVelocity["csa"].getDouble()));
				emitter->getColorEnd().setRed(static_cast< float >(jCircleParticleEmitterPlaneVelocity["cer"].getDouble()));
				emitter->getColorEnd().setGreen(static_cast< float >(jCircleParticleEmitterPlaneVelocity["ceg"].getDouble()));
				emitter->getColorEnd().setBlue(static_cast< float >(jCircleParticleEmitterPlaneVelocity["ceb"].getDouble()));
				emitter->getColorEnd().setAlpha(static_cast< float >(jCircleParticleEmitterPlaneVelocity["cea"].getDouble()));
				emitter->getCenter().setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["cx"].getDouble()));
				emitter->getCenter().setY(static_cast< float >(jCircleParticleEmitterPlaneVelocity["cy"].getDouble()));
				emitter->getCenter().setZ(static_cast< float >(jCircleParticleEmitterPlaneVelocity["cz"].getDouble()));
				emitter->setRadius(static_cast< float >(jCircleParticleEmitterPlaneVelocity["r"].getDouble()));
				emitter->getAxis0().setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a0x"].getDouble()));
				emitter->getAxis0().setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a0y"].getDouble()));
				emitter->getAxis0().setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a0z"].getDouble()));
				emitter->getAxis1().setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a1x"].getDouble()));
				emitter->getAxis1().setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a1y"].getDouble()));
				emitter->getAxis1().setX(static_cast< float >(jCircleParticleEmitterPlaneVelocity["a1z"].getDouble()));
			} else
			if (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) {
				auto& jSphereParticleEmitter = jParticleSystem["spe"];
				auto emitter = particleSystem->getSphereParticleEmitter();
				emitter->setCount(jSphereParticleEmitter["c"].getInt());
				emitter->setLifeTime(jSphereParticleEmitter["lt"].getInt());
				emitter->setLifeTimeRnd(jSphereParticleEmitter["ltrnd"].getInt());
				emitter->setMass(static_cast< float >(jSphereParticleEmitter["m"].getDouble()));
				emitter->setMassRnd(static_cast< float >(jSphereParticleEmitter["mrnd"].getDouble()));
				emitter->getVelocity().setX(static_cast< float >(jSphereParticleEmitter["vx"].getDouble()));
				emitter->getVelocity().setY(static_cast< float >(jSphereParticleEmitter["vy"].getDouble()));
				emitter->getVelocity().setZ(static_cast< float >(jSphereParticleEmitter["vz"].getDouble()));
				emitter->getVelocityRnd().setX(static_cast< float >(jSphereParticleEmitter["vrndx"].getDouble()));
				emitter->getVelocityRnd().setY(static_cast< float >(jSphereParticleEmitter["vrndy"].getDouble()));
				emitter->getVelocityRnd().setZ(static_cast< float >(jSphereParticleEmitter["vrndz"].getDouble()));
				emitter->getColorStart().setRed(static_cast< float >(jSphereParticleEmitter["csr"].getDouble()));
				emitter->getColorStart().setGreen(static_cast< float >(jSphereParticleEmitter["csg"].getDouble()));
				emitter->getColorStart().setBlue(static_cast< float >(jSphereParticleEmitter["csb"].getDouble()));
				emitter->getColorStart().setAlpha(static_cast< float >(jSphereParticleEmitter["csa"].getDouble()));
				emitter->getColorEnd().setRed(static_cast< float >(jSphereParticleEmitter["cer"].getDouble()));
				emitter->getColorEnd().setGreen(static_cast< float >(jSphereParticleEmitter["ceg"].getDouble()));
				emitter->getColorEnd().setBlue(static_cast< float >(jSphereParticleEmitter["ceb"].getDouble()));
				emitter->getColorEnd().setAlpha(static_cast< float >(jSphereParticleEmitter["cea"].getDouble()));
				emitter->getCenter().setX(static_cast< float >(jSphereParticleEmitter["cx"].getDouble()));
				emitter->getCenter().setY(static_cast< float >(jSphereParticleEmitter["cy"].getDouble()));
				emitter->getCenter().setZ(static_cast< float >(jSphereParticleEmitter["cz"].getDouble()));
				emitter->setRadius(static_cast< float >(jSphereParticleEmitter["r"].getDouble()));
			} else {
				Console::println(
					"ModelMetaDataFileExport::export(): unknown particle system emitter '" +
					particleSystem->getEmitter()->getName() +
					"'"
				 );
			}
		}
	}
	levelEditorEntity->setDynamicShadowing(jEntityRoot["ds"].getBoolean());
	levelEditorEntity->setRenderGroups(jEntityRoot["rg"].isNull() == false?jEntityRoot["rg"].getBoolean():false);
	levelEditorEntity->setShader(jEntityRoot["s"].isNull() == false?jEntityRoot["s"].getString():"default");
	levelEditorEntity->setDistanceShader(jEntityRoot["sds"].isNull() == false?jEntityRoot["sds"].getString():"default");
	levelEditorEntity->setDistanceShaderDistance(jEntityRoot["sdsd"].isNull() == false?static_cast<float>(jEntityRoot["sds"].getDouble()):10000.0f);
	return levelEditorEntity;
}

const string ModelMetaDataFileImport::getResourcePathName(const string& pathName, const string& fileName) {
	string modelFile = FileSystem::getInstance()->getCanonicalPath(
		(
			StringUtils::startsWith(FileSystem::getInstance()->getPathName(fileName), "/") == true?
				FileSystem::getInstance()->getPathName(fileName):
				pathName + "/" +  FileSystem::getInstance()->getPathName(fileName)
		 ),
		FileSystem::getInstance()->getFileName(fileName)
	);
	auto gameRoot = Tools::getGameRootPath(pathName);
	auto modelRelativeFileName = Tools::getRelativeResourcesFileName(gameRoot, modelFile);
	return (gameRoot.length() > 0 ? gameRoot + "/" : "") + Tools::getPath(modelRelativeFileName);
}

LevelEditorEntityBoundingVolume* ModelMetaDataFileImport::parseBoundingVolume(int32_t idx, LevelEditorEntity* levelEditorEntity, const string& pathName, Value& jBv) throw (FileSystemException, JsonException, ModelFileIOException)
{
	auto entityBoundingVolume = new LevelEditorEntityBoundingVolume(idx, levelEditorEntity);
	BoundingVolume* bv;
	auto bvTypeString = (jBv["type"].getString());
	if (StringUtils::equalsIgnoreCase(bvTypeString, "none") == true) {
		entityBoundingVolume->setupNone();
	} else
	if (StringUtils::equalsIgnoreCase(bvTypeString, "sphere") == true) {
		entityBoundingVolume->setupSphere(
			Vector3(
				static_cast< float >(jBv["cx"].getDouble()),
				static_cast< float >(jBv["cy"].getDouble()),
				static_cast< float >(jBv["cz"].getDouble())
			),
			static_cast< float >(jBv["r"].getDouble())
		);
	} else
	if (StringUtils::equalsIgnoreCase(bvTypeString, "capsule") == true) {
		entityBoundingVolume->setupCapsule(
			Vector3(
				static_cast< float >(jBv["ax"].getDouble()),
				static_cast< float >(jBv["ay"].getDouble()),
				static_cast< float >(jBv["az"].getDouble())
			),
			Vector3(
				static_cast< float >(jBv["bx"].getDouble()),
				static_cast< float >(jBv["by"].getDouble()),
				static_cast< float >(jBv["bz"].getDouble())
			),
			static_cast< float >(jBv["r"].getDouble())
		);
	} else
	if (StringUtils::equalsIgnoreCase(bvTypeString, "aabb") == true) {
		entityBoundingVolume->setupAabb(
			Vector3(
				static_cast< float >(jBv["mix"].getDouble()),
				static_cast< float >(jBv["miy"].getDouble()),
				static_cast< float >(jBv["miz"].getDouble())
			),
			Vector3(
				static_cast< float >(jBv["max"].getDouble()),
				static_cast< float >(jBv["may"].getDouble()),
				static_cast< float >(jBv["maz"].getDouble())
			)
		);
	} else
	if (StringUtils::equalsIgnoreCase(bvTypeString, "obb") == true) {
		entityBoundingVolume->setupObb(
			Vector3(
				static_cast< float >(jBv["cx"].getDouble()),
				static_cast< float >(jBv["cy"].getDouble()),
				static_cast< float >(jBv["cz"].getDouble())
			),
			Vector3(
				static_cast< float >(jBv["a0x"].getDouble()),
				static_cast< float >(jBv["a0y"].getDouble()),
				static_cast< float >(jBv["a0z"].getDouble())
			),
			Vector3(
				static_cast< float >(jBv["a1x"].getDouble()),
				static_cast< float >(jBv["a1y"].getDouble()),
				static_cast< float >(jBv["a1z"].getDouble())
			),
			Vector3(
				static_cast< float >(jBv["a2x"].getDouble()),
				static_cast< float >(jBv["a2y"].getDouble()),
				static_cast< float >(jBv["a2z"].getDouble())
			),
			Vector3(
				static_cast< float >(jBv["hex"].getDouble()),
				static_cast< float >(jBv["hey"].getDouble()),
				static_cast< float >(jBv["hez"].getDouble())
			)
		);
	} else
	if (StringUtils::equalsIgnoreCase(bvTypeString, "convexmesh") == true) {
		try {
			string fileName = jBv["file"].getString();
			entityBoundingVolume->setupConvexMesh(
				getResourcePathName(pathName, fileName),
				Tools::getFileName(fileName)
			);
		} catch (Exception& exception) {
			Console::print(string("ModelMetaDataFileImport::parseBoundingVolume(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}
	return entityBoundingVolume;
}

LevelEditorEntityLODLevel* ModelMetaDataFileImport::parseLODLevel(const string& pathName, Value& jLodLevel) {
	auto lodType = static_cast<LODObject3D::LODLevelType>(jLodLevel["t"].getInt());
	LevelEditorEntityLODLevel* lodLevel = new LevelEditorEntityLODLevel(
		lodType,
		lodType == LODObject3D::LODLEVELTYPE_MODEL || lodType == LODObject3D::LODLEVELTYPE_PLANE?jLodLevel["f"].getString():"",
		nullptr,
		static_cast<float>(jLodLevel["d"].getDouble()),
		lodType == LODObject3D::LODLEVELTYPE_PLANE?static_cast<float>(jLodLevel["ry"].getDouble()):0.0f
	);
	if (lodType == LODObject3D::LODLEVELTYPE_MODEL || lodType == LODObject3D::LODLEVELTYPE_PLANE) {
		auto modelFileName = lodLevel->getFileName();
		auto modelPathName = getResourcePathName(pathName, modelFileName);
		lodLevel->setModel(
			ModelReader::read(
				modelPathName,
				FileSystem::getInstance()->getFileName(modelFileName)
			)
		);
		lodLevel->setFileName(modelPathName + "/" + FileSystem::getInstance()->getFileName(modelFileName));
	}
	lodLevel->setColorAdd(
		Color4(
			static_cast<float>(jLodLevel["car"].getDouble()),
			static_cast<float>(jLodLevel["cag"].getDouble()),
			static_cast<float>(jLodLevel["cab"].getDouble()),
			static_cast<float>(jLodLevel["caa"].getDouble())
		)
	);
	lodLevel->setColorMul(
		Color4(
			static_cast<float>(jLodLevel["cmr"].getDouble()),
			static_cast<float>(jLodLevel["cmg"].getDouble()),
			static_cast<float>(jLodLevel["cmb"].getDouble()),
			static_cast<float>(jLodLevel["cma"].getDouble())
		)
	);
	return lodLevel;
}
