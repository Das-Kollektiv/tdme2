// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityBoundingVolume.java
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>

#include <java/io/File.h>
#include <java/io/Serializable.h>
#include <java/lang/Exception.h>
#include <java/lang/Integer.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>

using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using java::io::File;
using java::io::Serializable;
using java::lang::Exception;
using java::lang::Integer;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::Object3DModel;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::engine::primitives::Sphere;
using tdme::math::Matrix4x4;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;

LevelEditorEntityBoundingVolume::LevelEditorEntityBoundingVolume(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntityBoundingVolume::LevelEditorEntityBoundingVolume(int32_t id, LevelEditorEntity* levelEditorEntity) 
	: LevelEditorEntityBoundingVolume(*static_cast< ::default_init_tag* >(0))
{
	ctor(id,levelEditorEntity);
}

int32_t LevelEditorEntityBoundingVolume::staticIdx;

void LevelEditorEntityBoundingVolume::ctor(int32_t id, LevelEditorEntity* levelEditorEntity)
{
	super::ctor();
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
	model = PrimitiveModel::createModel(boundingVolume, ::java::lang::StringBuilder().append(static_cast< Object* >((levelEditorEntity->getModel() != nullptr ? static_cast< Serializable* >(levelEditorEntity->getModel()->getId()) : Integer::valueOf(levelEditorEntity->getId()))))->append(u"_model_bv."_j)
		->append(id)
		->append(u"."_j)
		->append((staticIdx++))->toString());
	modelMeshFile = nullptr;
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupCapsule(Vector3* a, Vector3* b, float radius)
{
	boundingVolume = new Capsule(a, b, radius);
	model = PrimitiveModel::createModel(boundingVolume, ::java::lang::StringBuilder().append(static_cast< Object* >((levelEditorEntity->getModel() != nullptr ? static_cast< Serializable* >(levelEditorEntity->getModel()->getId()) : Integer::valueOf(levelEditorEntity->getId()))))->append(u"_model_bv."_j)
		->append(id)
		->append(u"."_j)
		->append((staticIdx++))->toString());
	modelMeshFile = nullptr;
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupObb(Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension)
{
	boundingVolume = new OrientedBoundingBox(center, axis0, axis1, axis2, halfExtension);
	model = PrimitiveModel::createModel(boundingVolume, ::java::lang::StringBuilder().append(static_cast< Object* >((levelEditorEntity->getModel() != nullptr ? static_cast< Serializable* >(levelEditorEntity->getModel()->getId()) : Integer::valueOf(levelEditorEntity->getId()))))->append(u"_model_bv."_j)
		->append(id)
		->append(u"."_j)
		->append((staticIdx++))->toString());
	modelMeshFile = nullptr;
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupAabb(Vector3* min, Vector3* max)
{
	boundingVolume = new BoundingBox(min, max);
	model = PrimitiveModel::createModel(boundingVolume, ::java::lang::StringBuilder().append(static_cast< Object* >((levelEditorEntity->getModel() != nullptr ? static_cast< Serializable* >(levelEditorEntity->getModel()->getId()) : Integer::valueOf(levelEditorEntity->getId()))))->append(u"_model_bv."_j)
		->append(id)
		->append(u"."_j)
		->append((staticIdx++))->toString());
	modelMeshFile = nullptr;
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::setupConvexMesh(String* file)
{
	modelMeshFile = file;
	try {
		auto convexMeshModel = DAEReader::read((new File(levelEditorEntity->getFileName()))->getAbsoluteFile()->getCanonicalFile()->getParentFile()->getPath(), file);
		boundingVolume = new ConvexMesh(new Object3DModel(convexMeshModel));
		convexMeshModel->setId(::java::lang::StringBuilder().append(convexMeshModel->getId())->append(u"_model_bv."_j)
			->append(id)
			->append(u"."_j)
			->append((staticIdx++))->toString());
		convexMeshModel->getImportTransformationsMatrix()->scale(1.01f);
		PrimitiveModel::setupConvexMeshModel(convexMeshModel);
		model = convexMeshModel;
	} catch (Exception* e) {
		e->printStackTrace();
	}
	updateLevelEditorEntity();
}

void LevelEditorEntityBoundingVolume::updateLevelEditorEntity()
{
	if (levelEditorEntity->type == LevelEditorEntity_EntityType::TRIGGER)
		levelEditorEntity->model = model;

}

String* LevelEditorEntityBoundingVolume::toString()
{
	return ::java::lang::StringBuilder().append(u"LevelEditorEntityBoundingVolume [id="_j)->append(id)
		->append(u", modelMeshFile="_j)
		->append(modelMeshFile)
		->append(u", model="_j)
		->append((model != nullptr ? model->getId() : static_cast< String* >(nullptr)))
		->append(u", boundingVolume="_j)
		->append(static_cast< Object* >(boundingVolume))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntityBoundingVolume::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorEntityBoundingVolume", 55);
    return c;
}

void LevelEditorEntityBoundingVolume::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		staticIdx = 0;
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* LevelEditorEntityBoundingVolume::getClass0()
{
	return class_();
}

