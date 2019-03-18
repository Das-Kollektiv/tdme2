#include <tdme/tools/shared/files/ModelMetaDataFileExport.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityAudio.h>
#include <tdme/tools/shared/model/LevelEditorEntityLODLevel.h>
#include <tdme/tools/shared/model/LevelEditorEntityModel.h>
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
#include <tdme/tools/shared/model/LevelEditorEntityPhysics.h>
#include <tdme/tools/shared/model/LevelEditorEntityPhysics_BodyType.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

#include <ext/jsonbox/Array.h>
#include <ext/jsonbox/JsonException.h>
#include <ext/jsonbox/Object.h>

using std::ostringstream;
using std::string;

using tdme::engine::LODObject3D;
using tdme::tools::shared::files::ModelMetaDataFileExport;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::Triangle;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
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
using tdme::tools::shared::model::PropertyModelClass;
using tdme::tools::shared::tools::Tools;
using tdme::utils::StringUtils;
using tdme::utils::Console;
using tdme::utils::Exception;

void ModelMetaDataFileExport::copyFile(const string& source, const string& dest) throw (FileSystemException)
{
}

void ModelMetaDataFileExport::export_(const string& pathName, const string& fileName, LevelEditorEntity* entity) throw (FileSystemException, JsonException, ModelFileIOException)
{
	entity->setEntityFileName(FileSystem::getInstance()->getCanonicalPath(pathName, fileName));
	auto jEntityRoot = exportToJSON(entity);

	ostringstream json;
	json << jEntityRoot;

	FileSystem::getInstance()->setContentFromString(pathName, fileName, (json.str()));
}

tdme::ext::jsonbox::Object ModelMetaDataFileExport::exportLODLevelToJSON(LevelEditorEntityLODLevel* lodLevel) {
	ext::jsonbox::Object jLodLevelRoot;
	jLodLevelRoot["t"] = static_cast<int>(lodLevel->getType());
	if (lodLevel->getType() == LODObject3D::LODLEVELTYPE_MODEL) {
		//
		auto modelPathName = Tools::getPath(lodLevel->getFileName());
		auto modelFileName =
			 Tools::getFileName(lodLevel->getFileName()) +
			 (StringUtils::endsWith(lodLevel->getFileName(), ".tm") == false ? ".tm" : "");
		TMWriter::write(
			lodLevel->getModel(),
			modelPathName,
			modelFileName
		);
		jLodLevelRoot["f"] = (modelPathName + "/" + modelFileName);
	}
	jLodLevelRoot["d"] = lodLevel->getMinDistance();
	jLodLevelRoot["cmr"] = lodLevel->getColorMul().getRed();
	jLodLevelRoot["cmg"] = lodLevel->getColorMul().getGreen();
	jLodLevelRoot["cmb"] = lodLevel->getColorMul().getBlue();
	jLodLevelRoot["cma"] = lodLevel->getColorMul().getAlpha();
	jLodLevelRoot["car"] = lodLevel->getColorAdd().getRed();
	jLodLevelRoot["cag"] = lodLevel->getColorAdd().getGreen();
	jLodLevelRoot["cab"] = lodLevel->getColorAdd().getBlue();
	jLodLevelRoot["caa"] = lodLevel->getColorAdd().getAlpha();
	return jLodLevelRoot;
}

tdme::ext::jsonbox::Object ModelMetaDataFileExport::exportToJSON(LevelEditorEntity* entity) throw (FileSystemException, JsonException, ModelFileIOException)
{
	ext::jsonbox::Object jEntityRoot;
	if (entity->getType() == LevelEditorEntity_EntityType::MODEL && entity->getFileName().length() > 0) {
		auto modelPathName = Tools::getPath(entity->getFileName());
		auto modelFileName =
			 Tools::getFileName(entity->getFileName()) +
			 (StringUtils::endsWith(entity->getFileName(), ".tm") == false ? ".tm" : "");
		TMWriter::write(
			entity->getModel(),
			modelPathName,
			modelFileName
		);
		jEntityRoot["file"] = (modelPathName + "/" + modelFileName);
		/*
		try {
			auto thumbnail = modelFileName + ".png";
			jEntityRoot["thumbnail] = (thumbnail));
			copyFile("./tmp/ + entity->getThumbnail(), Tools::getPath(entity->getFileName()) + thumbnail));
		} catch (Exception& exception) {
			Console::print(string("ModelMetaDataFileExport::export(): An error occurred: '));
			Console::print(entity->getFileName());
			Console::print(string(": "));
			Console::println(exception.what());
		}
		*/
		jEntityRoot["tm"] = entity->getModelSettings()->isTerrainMesh();
		int lodLevelIdx = 2;
		{
			auto lodLevel = entity->getLODLevel2();
			if (lodLevel != nullptr &&
				(lodLevel->getType() == LODObject3D::LODLEVELTYPE_IGNORE ||
				((lodLevel->getType() == LODObject3D::LODLEVELTYPE_MODEL) &&
				lodLevel->getModel() != nullptr))) {
				//
				jEntityRoot["ll" + to_string(lodLevelIdx++)] = exportLODLevelToJSON(lodLevel);
			}
		}
		{
			auto lodLevel = entity->getLODLevel3();
			if (lodLevel != nullptr &&
				(lodLevel->getType() == LODObject3D::LODLEVELTYPE_IGNORE ||
				((lodLevel->getType() == LODObject3D::LODLEVELTYPE_MODEL) &&
				lodLevel->getModel() != nullptr))) {
				//
				jEntityRoot["ll" + to_string(lodLevelIdx++)] = exportLODLevelToJSON(lodLevel);
			}
		}
	}
	jEntityRoot["version"] = "1.99";
	jEntityRoot["type"] = (entity->getType()->getName());
	jEntityRoot["name"] = (entity->getName());
	jEntityRoot["descr"] = (entity->getDescription());
	jEntityRoot["px"] = static_cast< double >(entity->getPivot().getX());
	jEntityRoot["py"] = static_cast< double >(entity->getPivot().getY());
	jEntityRoot["pz"] = static_cast< double >(entity->getPivot().getZ());
	if (entity->getSounds().size() > 0) {
		ext::jsonbox::Array jSounds;
		for (auto sound: entity->getSounds()) {
			if (sound->getFileName().length() == 0) continue;
			ext::jsonbox::Object jSound;
			jSound["i"] = sound->getId();
			jSound["a"] = sound->getAnimation();
			jSound["file"] = sound->getFileName();
			jSound["g"] = sound->getGain();
			jSound["p"] = sound->getPitch();
			jSound["o"] = sound->getOffset();
			jSound["l"] = sound->isLooping();
			jSound["f"] = sound->isFixed();
			jSounds.push_back(jSound);
		}
		jEntityRoot["sd"] = jSounds;
	}

	if (entity->getType() == LevelEditorEntity_EntityType::PARTICLESYSTEM) {
		ext::jsonbox::Array jParticleSystems;
		for (auto i = 0; i < entity->getParticleSystemsCount(); i++) {
			auto particleSystem = entity->getParticleSystemAt(i);
			ext::jsonbox::Object jParticleSystem;
			jParticleSystem["t"] = (particleSystem->getType()->getName());
			{
				auto v = particleSystem->getType();
				if (v == LevelEditorEntityParticleSystem_Type::NONE) {
					// no op
				} else
				if (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM)
				{
					ext::jsonbox::Object jObjectParticleSystem;
					if (particleSystem->getObjectParticleSystem()->getModelFile().length() > 0) {
						auto modelPathName = Tools::getPath(particleSystem->getObjectParticleSystem()->getModelFile());
						auto modelFileName = Tools::getFileName(particleSystem->getObjectParticleSystem()->getModelFile() + (StringUtils::endsWith(particleSystem->getObjectParticleSystem()->getModelFile(), ".tm") == false ? ".tm" : ""));
						TMWriter::write(
							particleSystem->getObjectParticleSystem()->getModel(),
							modelPathName,
							modelFileName
						);
						particleSystem->getObjectParticleSystem()->setModelFile(modelPathName + "/" + modelFileName);
					}
					jObjectParticleSystem["mc"] = particleSystem->getObjectParticleSystem()->getMaxCount();
					jObjectParticleSystem["sx"] = static_cast< double >(particleSystem->getObjectParticleSystem()->getScale().getX());
					jObjectParticleSystem["sy"] = static_cast< double >(particleSystem->getObjectParticleSystem()->getScale().getY());
					jObjectParticleSystem["sz"] = static_cast< double >(particleSystem->getObjectParticleSystem()->getScale().getZ());
					jObjectParticleSystem["mf"] = (particleSystem->getObjectParticleSystem()->getModelFile());
					jObjectParticleSystem["ae"] = particleSystem->getObjectParticleSystem()->isAutoEmit();
					jParticleSystem["ops"] = jObjectParticleSystem;
				} else
				if (v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)
				{
					ext::jsonbox::Object jPointParticleSystem;
					jPointParticleSystem["mp"] = particleSystem->getPointParticleSystem()->getMaxPoints();
					jPointParticleSystem["ps"] = particleSystem->getPointParticleSystem()->getPointSize();
					jPointParticleSystem["t"] = particleSystem->getPointParticleSystem()->getTextureFileName();
					jPointParticleSystem["tt"] = particleSystem->getPointParticleSystem()->getTransparencyTextureFileName();
					jPointParticleSystem["ae"] = particleSystem->getPointParticleSystem()->isAutoEmit();
					jParticleSystem["pps"] = jPointParticleSystem;
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

			jParticleSystem["e"] = (particleSystem->getEmitter()->getName());
			{
				auto v = particleSystem->getEmitter();
				if (v == LevelEditorEntityParticleSystem_Emitter::NONE)
				{
				} else
				if (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER)
				{
					ext::jsonbox::Object jPointParticleEmitter;
					auto emitter = particleSystem->getPointParticleEmitter();
					jPointParticleEmitter["c"] = emitter->getCount();
					jPointParticleEmitter["lt"] = static_cast< int32_t >(emitter->getLifeTime());
					jPointParticleEmitter["ltrnd"] = static_cast< int32_t >(emitter->getLifeTimeRnd());
					jPointParticleEmitter["m"] = static_cast< double >(emitter->getMass());
					jPointParticleEmitter["mrnd"] = static_cast< double >(emitter->getMassRnd());
					jPointParticleEmitter["px"] = static_cast< double >(emitter->getPosition().getX());
					jPointParticleEmitter["py"] = static_cast< double >(emitter->getPosition().getY());
					jPointParticleEmitter["pz"] = static_cast< double >(emitter->getPosition().getZ());
					jPointParticleEmitter["vx"] = static_cast< double >(emitter->getVelocity().getX());
					jPointParticleEmitter["vy"] = static_cast< double >(emitter->getVelocity().getY());
					jPointParticleEmitter["vz"] = static_cast< double >(emitter->getVelocity().getZ());
					jPointParticleEmitter["vrndx"] = static_cast< double >(emitter->getVelocityRnd().getX());
					jPointParticleEmitter["vrndy"] = static_cast< double >(emitter->getVelocityRnd().getY());
					jPointParticleEmitter["vrndz"] = static_cast< double >(emitter->getVelocityRnd().getZ());
					jPointParticleEmitter["csr"] = static_cast< double >(emitter->getColorStart().getRed());
					jPointParticleEmitter["csg"] = static_cast< double >(emitter->getColorStart().getGreen());
					jPointParticleEmitter["csb"] = static_cast< double >(emitter->getColorStart().getBlue());
					jPointParticleEmitter["csa"] = static_cast< double >(emitter->getColorStart().getAlpha());
					jPointParticleEmitter["cer"] = static_cast< double >(emitter->getColorEnd().getRed());
					jPointParticleEmitter["ceg"] = static_cast< double >(emitter->getColorEnd().getGreen());
					jPointParticleEmitter["ceb"] = static_cast< double >(emitter->getColorEnd().getBlue());
					jPointParticleEmitter["cea"] = static_cast< double >(emitter->getColorEnd().getAlpha());
					jParticleSystem["ppe"] = jPointParticleEmitter;
				} else
				if (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER)
				{
					ext::jsonbox::Object jBoundingBoxParticleEmitter;
					auto emitter = particleSystem->getBoundingBoxParticleEmitters();
					jBoundingBoxParticleEmitter["c"] = emitter->getCount();
					jBoundingBoxParticleEmitter["lt"] = static_cast< int32_t >(emitter->getLifeTime());
					jBoundingBoxParticleEmitter["ltrnd"] = static_cast< int32_t >(emitter->getLifeTimeRnd());
					jBoundingBoxParticleEmitter["m"] = static_cast< double >(emitter->getMass());
					jBoundingBoxParticleEmitter["mrnd"] = static_cast< double >(emitter->getMassRnd());
					jBoundingBoxParticleEmitter["vx"] = static_cast< double >(emitter->getVelocity().getX());
					jBoundingBoxParticleEmitter["vy"] = static_cast< double >(emitter->getVelocity().getY());
					jBoundingBoxParticleEmitter["vz"] = static_cast< double >(emitter->getVelocity().getZ());
					jBoundingBoxParticleEmitter["vrndx"] = static_cast< double >(emitter->getVelocityRnd().getX());
					jBoundingBoxParticleEmitter["vrndy"] = static_cast< double >(emitter->getVelocityRnd().getY());
					jBoundingBoxParticleEmitter["vrndz"] = static_cast< double >(emitter->getVelocityRnd().getZ());
					jBoundingBoxParticleEmitter["csr"] = static_cast< double >(emitter->getColorStart().getRed());
					jBoundingBoxParticleEmitter["csg"] = static_cast< double >(emitter->getColorStart().getGreen());
					jBoundingBoxParticleEmitter["csb"] = static_cast< double >(emitter->getColorStart().getBlue());
					jBoundingBoxParticleEmitter["csa"] = static_cast< double >(emitter->getColorStart().getAlpha());
					jBoundingBoxParticleEmitter["cer"] = static_cast< double >(emitter->getColorEnd().getRed());
					jBoundingBoxParticleEmitter["ceg"] = static_cast< double >(emitter->getColorEnd().getGreen());
					jBoundingBoxParticleEmitter["ceb"] = static_cast< double >(emitter->getColorEnd().getBlue());
					jBoundingBoxParticleEmitter["cea"] = static_cast< double >(emitter->getColorEnd().getAlpha());
					jBoundingBoxParticleEmitter["ocx"] = static_cast< double >(emitter->getObbCenter().getX());
					jBoundingBoxParticleEmitter["ocy"] = static_cast< double >(emitter->getObbCenter().getY());
					jBoundingBoxParticleEmitter["ocz"] = static_cast< double >(emitter->getObbCenter().getZ());
					jBoundingBoxParticleEmitter["ohex"] = static_cast< double >(emitter->getObbHalfextension().getX());
					jBoundingBoxParticleEmitter["ohey"] = static_cast< double >(emitter->getObbHalfextension().getY());
					jBoundingBoxParticleEmitter["ohez"] = static_cast< double >(emitter->getObbHalfextension().getZ());
					jBoundingBoxParticleEmitter["oa0x"] = static_cast< double >(emitter->getObbAxis0().getX());
					jBoundingBoxParticleEmitter["oa0y"] = static_cast< double >(emitter->getObbAxis0().getY());
					jBoundingBoxParticleEmitter["oa0z"] = static_cast< double >(emitter->getObbAxis0().getZ());
					jBoundingBoxParticleEmitter["oa1x"] = static_cast< double >(emitter->getObbAxis1().getX());
					jBoundingBoxParticleEmitter["oa1y"] = static_cast< double >(emitter->getObbAxis1().getY());
					jBoundingBoxParticleEmitter["oa1z"] = static_cast< double >(emitter->getObbAxis1().getZ());
					jBoundingBoxParticleEmitter["oa2x"] = static_cast< double >(emitter->getObbAxis2().getX());
					jBoundingBoxParticleEmitter["oa2y"] = static_cast< double >(emitter->getObbAxis2().getY());
					jBoundingBoxParticleEmitter["oa2z"] = static_cast< double >(emitter->getObbAxis2().getZ());
					jParticleSystem["bbpe"] = jBoundingBoxParticleEmitter;
				} else
				if (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER)
				{
					ext::jsonbox::Object jCircleParticleEmitter;
					auto emitter = particleSystem->getCircleParticleEmitter();
					jCircleParticleEmitter["c"] = emitter->getCount();
					jCircleParticleEmitter["lt"] = static_cast< int32_t >(emitter->getLifeTime());
					jCircleParticleEmitter["ltrnd"] = static_cast< int32_t>(emitter->getLifeTimeRnd());
					jCircleParticleEmitter["m"] = static_cast< double >(emitter->getMass());
					jCircleParticleEmitter["mrnd"] = static_cast< double >(emitter->getMassRnd());
					jCircleParticleEmitter["vx"] = static_cast< double >(emitter->getVelocity().getX());
					jCircleParticleEmitter["vy"] = static_cast< double >(emitter->getVelocity().getY());
					jCircleParticleEmitter["vz"] = static_cast< double >(emitter->getVelocity().getZ());
					jCircleParticleEmitter["vrndx"] = static_cast< double >(emitter->getVelocityRnd().getX());
					jCircleParticleEmitter["vrndy"] = static_cast< double >(emitter->getVelocityRnd().getY());
					jCircleParticleEmitter["vrndz"] = static_cast< double >(emitter->getVelocityRnd().getZ());
					jCircleParticleEmitter["csr"] = static_cast< double >(emitter->getColorStart().getRed());
					jCircleParticleEmitter["csg"] = static_cast< double >(emitter->getColorStart().getGreen());
					jCircleParticleEmitter["csb"] = static_cast< double >(emitter->getColorStart().getBlue());
					jCircleParticleEmitter["csa"] = static_cast< double >(emitter->getColorStart().getAlpha());
					jCircleParticleEmitter["cer"] = static_cast< double >(emitter->getColorEnd().getRed());
					jCircleParticleEmitter["ceg"] = static_cast< double >(emitter->getColorEnd().getGreen());
					jCircleParticleEmitter["ceb"] = static_cast< double >(emitter->getColorEnd().getBlue());
					jCircleParticleEmitter["cea"] = static_cast< double >(emitter->getColorEnd().getAlpha());
					jCircleParticleEmitter["cx"] = static_cast< double >(emitter->getCenter().getX());
					jCircleParticleEmitter["cy"] = static_cast< double >(emitter->getCenter().getY());
					jCircleParticleEmitter["cz"] = static_cast< double >(emitter->getCenter().getZ());
					jCircleParticleEmitter["r"] = static_cast< double >(emitter->getRadius());
					jCircleParticleEmitter["a0x"] = static_cast< double >(emitter->getAxis0().getX());
					jCircleParticleEmitter["a0y"] = static_cast< double >(emitter->getAxis0().getY());
					jCircleParticleEmitter["a0z"] = static_cast< double >(emitter->getAxis0().getZ());
					jCircleParticleEmitter["a1x"] = static_cast< double >(emitter->getAxis1().getX());
					jCircleParticleEmitter["a1y"] = static_cast< double >(emitter->getAxis1().getY());
					jCircleParticleEmitter["a1z"] = static_cast< double >(emitter->getAxis1().getZ());
					jParticleSystem["cpe"] = jCircleParticleEmitter;
				} else
				if (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
					ext::jsonbox::Object jCircleParticleEmitterPlaneVelocity;
					auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
					jCircleParticleEmitterPlaneVelocity["c"] = emitter->getCount();
					jCircleParticleEmitterPlaneVelocity["lt"] = static_cast< int32_t >(emitter->getLifeTime());
					jCircleParticleEmitterPlaneVelocity["ltrnd"] = static_cast< int32_t >(emitter->getLifeTimeRnd());
					jCircleParticleEmitterPlaneVelocity["m"] = static_cast< double >(emitter->getMass());
					jCircleParticleEmitterPlaneVelocity["mrnd"] = static_cast< double >(emitter->getMassRnd());
					jCircleParticleEmitterPlaneVelocity["v"] = static_cast< double >(emitter->getVelocity());
					jCircleParticleEmitterPlaneVelocity["vrnd"] = static_cast< double >(emitter->getVelocityRnd());
					jCircleParticleEmitterPlaneVelocity["csr"] = static_cast< double >(emitter->getColorStart().getRed());
					jCircleParticleEmitterPlaneVelocity["csg"] = static_cast< double >(emitter->getColorStart().getGreen());
					jCircleParticleEmitterPlaneVelocity["csb"] = static_cast< double >(emitter->getColorStart().getBlue());
					jCircleParticleEmitterPlaneVelocity["csa"] = static_cast< double >(emitter->getColorStart().getAlpha());
					jCircleParticleEmitterPlaneVelocity["cer"] = static_cast< double >(emitter->getColorEnd().getRed());
					jCircleParticleEmitterPlaneVelocity["ceg"] = static_cast< double >(emitter->getColorEnd().getGreen());
					jCircleParticleEmitterPlaneVelocity["ceb"] = static_cast< double >(emitter->getColorEnd().getBlue());
					jCircleParticleEmitterPlaneVelocity["cea"] = static_cast< double >(emitter->getColorEnd().getAlpha());
					jCircleParticleEmitterPlaneVelocity["cx"] = static_cast< double >(emitter->getCenter().getX());
					jCircleParticleEmitterPlaneVelocity["cy"] = static_cast< double >(emitter->getCenter().getY());
					jCircleParticleEmitterPlaneVelocity["cz"] = static_cast< double >(emitter->getCenter().getZ());
					jCircleParticleEmitterPlaneVelocity["r"] = static_cast< double >(emitter->getRadius());
					jCircleParticleEmitterPlaneVelocity["a0x"] = static_cast< double >(emitter->getAxis0().getX());
					jCircleParticleEmitterPlaneVelocity["a0y"] = static_cast< double >(emitter->getAxis0().getY());
					jCircleParticleEmitterPlaneVelocity["a0z"] = static_cast< double >(emitter->getAxis0().getZ());
					jCircleParticleEmitterPlaneVelocity["a1x"] = static_cast< double >(emitter->getAxis1().getX());
					jCircleParticleEmitterPlaneVelocity["a1y"] = static_cast< double >(emitter->getAxis1().getY());
					jCircleParticleEmitterPlaneVelocity["a1z"] = static_cast< double >(emitter->getAxis1().getZ());
					jParticleSystem["cpeev"] = jCircleParticleEmitterPlaneVelocity;
				} else
				if (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)
				{
					ext::jsonbox::Object jSphereParticleEmitter;
					auto emitter = particleSystem->getSphereParticleEmitter();
					jSphereParticleEmitter["c"] = emitter->getCount();
					jSphereParticleEmitter["lt"] = static_cast< int32_t >(emitter->getLifeTime());
					jSphereParticleEmitter["ltrnd"] = static_cast< int32_t >(emitter->getLifeTimeRnd());
					jSphereParticleEmitter["m"] = static_cast< double >(emitter->getMass());
					jSphereParticleEmitter["mrnd"] = static_cast< double >(emitter->getMassRnd());
					jSphereParticleEmitter["vx"] = static_cast< double >(emitter->getVelocity().getX());
					jSphereParticleEmitter["vy"] = static_cast< double >(emitter->getVelocity().getY());
					jSphereParticleEmitter["vz"] = static_cast< double >(emitter->getVelocity().getZ());
					jSphereParticleEmitter["vrndx"] = static_cast< double >(emitter->getVelocityRnd().getX());
					jSphereParticleEmitter["vrndy"] = static_cast< double >(emitter->getVelocityRnd().getY());
					jSphereParticleEmitter["vrndz"] = static_cast< double >(emitter->getVelocityRnd().getZ());
					jSphereParticleEmitter["csr"] = static_cast< double >(emitter->getColorStart().getRed());
					jSphereParticleEmitter["csg"] = static_cast< double >(emitter->getColorStart().getGreen());
					jSphereParticleEmitter["csb"] = static_cast< double >(emitter->getColorStart().getBlue());
					jSphereParticleEmitter["csa"] = static_cast< double >(emitter->getColorStart().getAlpha());
					jSphereParticleEmitter["cer"] = static_cast< double >(emitter->getColorEnd().getRed());
					jSphereParticleEmitter["ceg"] = static_cast< double >(emitter->getColorEnd().getGreen());
					jSphereParticleEmitter["ceb"] = static_cast< double >(emitter->getColorEnd().getBlue());
					jSphereParticleEmitter["cea"] = static_cast< double >(emitter->getColorEnd().getAlpha());
					jSphereParticleEmitter["cx"] = static_cast< double >(emitter->getCenter().getX());
					jSphereParticleEmitter["cy"] = static_cast< double >(emitter->getCenter().getY());
					jSphereParticleEmitter["cz"] = static_cast< double >(emitter->getCenter().getZ());
					jSphereParticleEmitter["r"] = static_cast< double >(emitter->getRadius());
					jParticleSystem["spe"] = jSphereParticleEmitter;
				} else
				{
					Console::println(
						string(
							"ModelMetaDataFileExport::export(): unknown particle system emitter '" +
							particleSystem->getEmitter()->getName() +
							"'"
						 )
					 );
				}
			}

			jParticleSystems.push_back(jParticleSystem);
		}
		jEntityRoot["pss"] = jParticleSystems;
	}
	ext::jsonbox::Array jBoundingVolumes;
	for (auto i = 0; i < entity->getBoundingVolumeCount(); i++) {
		auto entityBoundingVolume = entity->getBoundingVolumeAt(i);
		auto bv = entityBoundingVolume->getBoundingVolume();
		if (bv == nullptr) continue;

		ext::jsonbox::Object jBoundingVolume;
		if (bv == nullptr) {
			jBoundingVolume["type"] = "none";
			jBoundingVolumes.push_back(jBoundingVolume);
		} else
		if (dynamic_cast< Sphere* >(bv) != nullptr) {
			auto sphere = dynamic_cast< Sphere* >(bv);
			jBoundingVolume["type"] = "sphere";
			jBoundingVolume["cx"] = static_cast< double >(sphere->getCenter().getX());
			jBoundingVolume["cy"] = static_cast< double >(sphere->getCenter().getY());
			jBoundingVolume["cz"] = static_cast< double >(sphere->getCenter().getZ());
			jBoundingVolume["r"] = static_cast< double >(sphere->getRadius());
			jBoundingVolumes.push_back(jBoundingVolume);
		} else
		if (dynamic_cast< Capsule* >(bv) != nullptr) {
			auto capsule = dynamic_cast< Capsule* >(bv);
			jBoundingVolume["type"] = "capsule";
			jBoundingVolume["ax"] = static_cast< double >(capsule->getA().getX());
			jBoundingVolume["ay"] = static_cast< double >(capsule->getA().getY());
			jBoundingVolume["az"] = static_cast< double >(capsule->getA().getZ());
			jBoundingVolume["bx"] = static_cast< double >(capsule->getB().getX());
			jBoundingVolume["by"] = static_cast< double >(capsule->getB().getY());
			jBoundingVolume["bz"] = static_cast< double >(capsule->getB().getZ());
			jBoundingVolume["r"] = static_cast< double >(capsule->getRadius());
			jBoundingVolumes.push_back(jBoundingVolume);
		} else
		if (dynamic_cast< BoundingBox* >(bv) != nullptr) {
			auto aabb = dynamic_cast< BoundingBox* >(bv);
			jBoundingVolume["type"] = "aabb";
			jBoundingVolume["mix"] = static_cast< double >(aabb->getMin().getX());
			jBoundingVolume["miy"] = static_cast< double >(aabb->getMin().getY());
			jBoundingVolume["miz"] = static_cast< double >(aabb->getMin().getZ());
			jBoundingVolume["max"] = static_cast< double >(aabb->getMax().getX());
			jBoundingVolume["may"] = static_cast< double >(aabb->getMax().getY());
			jBoundingVolume["maz"] = static_cast< double >(aabb->getMax().getZ());
			jBoundingVolumes.push_back(jBoundingVolume);
		} else
		if (dynamic_cast< OrientedBoundingBox* >(bv) != nullptr) {
			auto obb = dynamic_cast< OrientedBoundingBox* >(bv);
			jBoundingVolume["type"] = "obb";
			jBoundingVolume["cx"] = static_cast< double >(obb->getCenter().getX());
			jBoundingVolume["cy"] = static_cast< double >(obb->getCenter().getY());
			jBoundingVolume["cz"] = static_cast< double >(obb->getCenter().getZ());
			jBoundingVolume["a0x"] = static_cast< double >((*obb->getAxes())[0].getX());
			jBoundingVolume["a0y"] = static_cast< double >((*obb->getAxes())[0].getY());
			jBoundingVolume["a0z"] = static_cast< double >((*obb->getAxes())[0].getZ());
			jBoundingVolume["a1x"] = static_cast< double >((*obb->getAxes())[1].getX());
			jBoundingVolume["a1y"] = static_cast< double >((*obb->getAxes())[1].getY());
			jBoundingVolume["a1z"] = static_cast< double >((*obb->getAxes())[1].getZ());
			jBoundingVolume["a2x"] = static_cast< double >((*obb->getAxes())[2].getX());
			jBoundingVolume["a2y"] = static_cast< double >((*obb->getAxes())[2].getY());
			jBoundingVolume["a2z"] = static_cast< double >((*obb->getAxes())[2].getZ());
			jBoundingVolume["hex"] = static_cast< double >(obb->getHalfExtension().getX());
			jBoundingVolume["hey"] = static_cast< double >(obb->getHalfExtension().getY());
			jBoundingVolume["hez"] = static_cast< double >(obb->getHalfExtension().getZ());
			jBoundingVolumes.push_back(jBoundingVolume);
		} else
		if (dynamic_cast< ConvexMesh* >(bv) != nullptr) {
			auto mesh = dynamic_cast< ConvexMesh* >(bv);
			jBoundingVolume["type"] = "convexmesh";
			jBoundingVolume["file"] = (entityBoundingVolume->getModelMeshFile());
			jBoundingVolumes.push_back(jBoundingVolume);
		}
	}
	jEntityRoot["bvs"] = jBoundingVolumes;
	auto physics = entity->getPhysics();
	if (physics != nullptr) {
		ext::jsonbox::Object jPhysics;
		jPhysics["type"] = physics->getType()->getName();
		jPhysics["mass"] = static_cast< double >(physics->getMass());
		jPhysics["restitution"] = static_cast< double >(physics->getRestitution());
		jPhysics["friction"] = static_cast< double >(physics->getFriction());
		jPhysics["itx"] = static_cast< double >(physics->getInertiaTensor().getX());
		jPhysics["ity"] = static_cast< double >(physics->getInertiaTensor().getY());
		jPhysics["itz"] = static_cast< double >(physics->getInertiaTensor().getZ());
		jEntityRoot["p"] = jPhysics;
	}
	ext::jsonbox::Array jModelProperties;
	for (auto i = 0; i < entity->getPropertyCount(); i++) {
		PropertyModelClass* modelProperty = entity->getPropertyByIndex(i);
		ext::jsonbox::Object jObjectProperty;
		jObjectProperty["name"] = (modelProperty->getName());
		jObjectProperty["value"] = (modelProperty->getValue());
		jModelProperties.push_back(jObjectProperty);
	}
	jEntityRoot["properties"] = jModelProperties;
	jEntityRoot["ds"] = entity->isDynamicShadowing();
	jEntityRoot["rg"] = entity->isRenderGroups();
	jEntityRoot["s"] = entity->getShader();
	jEntityRoot["sds"] = entity->getDistanceShader();
	jEntityRoot["sdsd"] = static_cast< double >(entity->getDistanceShaderDistance());
	return jEntityRoot;
}
