#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>

#include <string>

#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/StringUtils.h>

using std::string;
using std::to_string;

using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::engine::Object3DModel;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::engine::primitives::Sphere;
using tdme::math::Matrix4x4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::utils::Exception;
using tdme::utils::Console;
using tdme::utils::StringUtils;

int32_t LevelEditorEntityBoundingVolume::staticIdx = 0;

LevelEditorEntityBoundingVolume::LevelEditorEntityBoundingVolume(int32_t id, LevelEditorEntity* levelEditorEntity) 
{
	this->id = id;
	this->levelEditorEntity = levelEditorEntity;
	modelMeshFile = "";
	model = nullptr;
	boundingVolume = nullptr;
}

LevelEditorEntityBoundingVolume::~LevelEditorEntityBoundingVolume() {
	if (model != nullptr) delete model;
	if (boundingVolume != nullptr) delete boundingVolume;
}

int32_t LevelEditorEntityBoundingVolume::getId()
{
	return id;
}

LevelEditorEntity* LevelEditorEntityBoundingVolume::getLevelEditorEntity()
{
	return levelEditorEntity;
}

const string& LevelEditorEntityBoundingVolume::getModelMeshFile()
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
	modelMeshFile = "";
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupSphere(const Vector3& center, float radius)
{
	if (boundingVolume != nullptr) delete boundingVolume;
	boundingVolume = new Sphere(center, radius);
	if (model != nullptr) delete model;
	model = PrimitiveModel::createModel(
		boundingVolume,
		string(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : "none") +
			string(",") +
			to_string(levelEditorEntity->getId()) +
			string("_model_bv.") +
			to_string(id) +
			string(".") +
			to_string(staticIdx++)
	);
	modelMeshFile = "";
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupCapsule(const Vector3& a, const Vector3& b, float radius)
{
	if (boundingVolume != nullptr) delete boundingVolume;
	boundingVolume = new Capsule(a, b, radius);
	if (model != nullptr) delete model;
	model = PrimitiveModel::createModel(
		boundingVolume,
		string(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : "none") +
			string(",") +
			to_string(levelEditorEntity->getId()) +
			string("_model_bv.") +
			to_string(id) +
			string(".") +
			to_string(staticIdx++)
	);
	modelMeshFile = "";
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupObb(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension)
{
	if (boundingVolume != nullptr) delete boundingVolume;
	boundingVolume = new OrientedBoundingBox(center, axis0, axis1, axis2, halfExtension);
	if (model != nullptr) delete model;
	model = PrimitiveModel::createModel(
		boundingVolume,
		string(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : "none") +
			string(",") +
			to_string(levelEditorEntity->getId()) +
			string("_model_bv.") +
			to_string(id) +
			string(".") +
			to_string(staticIdx++)
	);
	modelMeshFile = "";
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupAabb(const Vector3& min, const Vector3& max)
{
	if (boundingVolume != nullptr) delete boundingVolume;
	boundingVolume = new BoundingBox(min, max);
	if (model != nullptr) delete model;
	model = PrimitiveModel::createModel(
		boundingVolume,
		string(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : "none") +
			string(",") +
			to_string(levelEditorEntity->getId()) +
			string("_model_bv.") +
			to_string(id) +
			string(".") +
			to_string(staticIdx++)
	);
	modelMeshFile = "";
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupConvexMesh(const string& pathName, const string& fileName)
{
	if (boundingVolume != nullptr) delete boundingVolume;
	boundingVolume = new ConvexMesh();
	if (model != nullptr) delete model;
	model = nullptr;
	modelMeshFile = pathName + "/" + fileName;
	try {
		Model* convexMeshModel = ModelReader::read(
			pathName,
			fileName
		);
		boundingVolume = new ConvexMesh(new Object3DModel(convexMeshModel));
		model = PrimitiveModel::createModel(
			boundingVolume,
			string(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : "none") +
				string(",") +
				to_string(levelEditorEntity->getId()) +
				string("_model_bv.") +
				to_string(id) +
				string(".") +
				to_string(staticIdx++)
		);
	} catch (Exception& exception) {
		Console::print(string("LevelEditorEntityBoundingVolume::setupConvexMesh(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::updateLevelEditorEntity()
{
	if (levelEditorEntity->getType() == LevelEditorEntity_EntityType::TRIGGER)
		levelEditorEntity->setModel(model);

}
