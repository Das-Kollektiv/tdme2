#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>

#include <string>

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
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/StringUtils.h>

using std::wstring;
using std::to_wstring;

using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
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
	modelMeshFile = L"";
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

const wstring& LevelEditorEntityBoundingVolume::getModelMeshFile()
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
	modelMeshFile = L"";
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupSphere(const Vector3& center, float radius)
{
	boundingVolume = new Sphere(center, radius);
	model = PrimitiveModel::createModel(
		boundingVolume,
		wstring(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : L"none") +
			wstring(L",") +
			to_wstring(levelEditorEntity->getId()) +
			wstring(L"_model_bv.") +
			to_wstring(id) +
			wstring(L".") +
			to_wstring(staticIdx++)
	);
	modelMeshFile = L"";
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupCapsule(const Vector3& a, const Vector3& b, float radius)
{
	boundingVolume = new Capsule(a, b, radius);
	model = PrimitiveModel::createModel(
		boundingVolume,
		wstring(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : L"none") +
			wstring(L",") +
			to_wstring(levelEditorEntity->getId()) +
			wstring(L"_model_bv.") +
			to_wstring(id) +
			wstring(L".") +
			to_wstring(staticIdx++)
	);
	modelMeshFile = L"";
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupObb(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension)
{
	boundingVolume = new OrientedBoundingBox(center, axis0, axis1, axis2, halfExtension);
	model = PrimitiveModel::createModel(
		boundingVolume,
		wstring(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : L"none") +
			wstring(L",") +
			to_wstring(levelEditorEntity->getId()) +
			wstring(L"_model_bv.") +
			to_wstring(id) +
			wstring(L".") +
			to_wstring(staticIdx++)
	);
	modelMeshFile = L"";
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupAabb(const Vector3& min, const Vector3& max)
{
	boundingVolume = new BoundingBox(min, max);
	model = PrimitiveModel::createModel(
		boundingVolume,
		wstring(levelEditorEntity->getModel() != nullptr ? levelEditorEntity->getModel()->getId() : L"none") +
			wstring(L",") +
			to_wstring(levelEditorEntity->getId()) +
			wstring(L"_model_bv.") +
			to_wstring(id) +
			wstring(L".") +
			to_wstring(staticIdx++)
	);
	modelMeshFile = L"";
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupConvexMesh(const wstring& pathName, const wstring& fileName)
{
	modelMeshFile = fileName;
	try {
		Model* convexMeshModel = nullptr;
		if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L".dae") == true) {
			convexMeshModel = DAEReader::read(
				pathName,
				fileName
			);
		} else
			if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L".tm") == true) {
			convexMeshModel = TMReader::read(
				pathName,
				fileName
			);
		}
		boundingVolume = new ConvexMesh(new Object3DModel(convexMeshModel));
		convexMeshModel->getImportTransformationsMatrix().scale(1.01f);
		PrimitiveModel::setupConvexMeshModel(convexMeshModel);
		model = convexMeshModel;
	} catch (Exception& exception) {
		Console::print(string("LevelEditorEntityBoundingVolume::setupConvexMesh(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::updateLevelEditorEntity()
{
	if (levelEditorEntity->type == LevelEditorEntity_EntityType::TRIGGER)
		levelEditorEntity->model = model;

}
