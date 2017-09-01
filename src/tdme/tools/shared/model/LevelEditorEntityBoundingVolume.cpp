// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityBoundingVolume.java
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>

#include <java/io/Serializable.h>
#include <java/lang/Integer.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/utils/_Exception.h>
#include <tdme/utils/_Console.h>

using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using java::io::Serializable;
using java::lang::Integer;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::Object3DModel;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::engine::primitives::Sphere;
using tdme::math::Matrix4x4;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::utils::_Exception;
using tdme::utils::_Console;

int32_t LevelEditorEntityBoundingVolume::staticIdx = 0;

LevelEditorEntityBoundingVolume::LevelEditorEntityBoundingVolume(int32_t id, LevelEditorEntity* levelEditorEntity) 
{
	this->id = id;
	this->levelEditorEntity = levelEditorEntity;
	modelMeshFile = nullptr;
	model = nullptr;
	boundingVolume = nullptr;
}

int32_t LevelEditorEntityBoundingVolume::getId()
{
	return id;
}

LevelEditorEntity* LevelEditorEntityBoundingVolume::getLevelEditorEntity()
{
	return levelEditorEntity;
}

String* LevelEditorEntityBoundingVolume::getModelMeshFile()
{
	return modelMeshFile;
}

Model* LevelEditorEntityBoundingVolume::getModel()
{
	return model;
}

BoundingVolume* LevelEditorEntityBoundingVolume::getBoundingVolume()
{
	return boundingVolume;
}

void LevelEditorEntityBoundingVolume::setupNone()
{
	boundingVolume = nullptr;
	model = nullptr;
	modelMeshFile = nullptr;
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupSphere(Vector3* center, float radius)
{
	boundingVolume = new Sphere(center, radius);
	model = PrimitiveModel::createModel(
		boundingVolume,
		::java::lang::StringBuilder().
		 append(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : L"none")->
		 append(L",")->
		 append(Integer::valueOf(levelEditorEntity->getId()))->
		 append(u"_model_bv."_j)->
		 append(id)->
		 append(u"."_j)->
		 append((staticIdx++))->
		 toString()->
		 getCPPWString()
	);
	modelMeshFile = nullptr;
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupCapsule(Vector3* a, Vector3* b, float radius)
{
	boundingVolume = new Capsule(a, b, radius);
	model = PrimitiveModel::createModel(
		boundingVolume,
		::java::lang::StringBuilder().
		 append(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : L"none")->
		 append(L",")->
		 append(Integer::valueOf(levelEditorEntity->getId()))->
		 append(u"_model_bv."_j)->
		 append(id)->
		 append(u"."_j)->
		 append((staticIdx++))->
		 toString()->
		 getCPPWString()
	);
	modelMeshFile = nullptr;
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupObb(Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension)
{
	boundingVolume = new OrientedBoundingBox(center, axis0, axis1, axis2, halfExtension);
	model = PrimitiveModel::createModel(
		boundingVolume,
		::java::lang::StringBuilder().
		 append(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : L"none")->
		 append(L",")->
		 append(Integer::valueOf(levelEditorEntity->getId()))->
		 append(u"_model_bv."_j)->
		 append(id)->
		 append(u"."_j)->
		 append((staticIdx++))->
		 toString()->
		 getCPPWString()
	);
	modelMeshFile = nullptr;
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupAabb(Vector3* min, Vector3* max)
{
	boundingVolume = new BoundingBox(min, max);
	model = PrimitiveModel::createModel(
		boundingVolume,
		::java::lang::StringBuilder().
		 append(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : L"none")->
		 append(L",")->
		 append(Integer::valueOf(levelEditorEntity->getId()))->
		 append(u"_model_bv."_j)->
		 append(id)->
		 append(u"."_j)->
		 append((staticIdx++))->
		 toString()->
		 getCPPWString()
	);
	modelMeshFile = nullptr;
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupConvexMesh(String* pathName, String* fileName)
{
	modelMeshFile = fileName;
	try {
		Model* convexMeshModel = nullptr;
		if (fileName->toLowerCase()->endsWith(u".dae"_j)) {
			convexMeshModel = DAEReader::read(
				pathName->getCPPWString(),
				fileName->getCPPWString()
			);
		} else
		if (fileName->toLowerCase()->endsWith(u".tm"_j)) {
			convexMeshModel = TMReader::read(
				pathName->getCPPWString(),
				fileName->getCPPWString()
			);
		}
		boundingVolume = new ConvexMesh(new Object3DModel(convexMeshModel));
		convexMeshModel->getImportTransformationsMatrix()->scale(1.01f);
		PrimitiveModel::setupConvexMeshModel(convexMeshModel);
		model = convexMeshModel;
	} catch (_Exception& exception) {
		_Console::print(string("LevelEditorEntityBoundingVolume::setupConvexMesh(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::updateLevelEditorEntity()
{
	if (levelEditorEntity->type == LevelEditorEntity_EntityType::TRIGGER)
		levelEditorEntity->model = model;

}
