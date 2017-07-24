// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityLibrary.java
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>

#include <algorithm>
#include <map>
#include <vector>

#include <java/lang/CharSequence.h>
#include <java/lang/Integer.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_ExceptionBase.h>

using std::map;
using std::remove;
using std::vector;

using tdme::tools::shared::model::LevelEditorEntityLibrary;
using java::lang::CharSequence;
using java::lang::Integer;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::math::Vector3;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::utils::StringConverter;
using tdme::utils::_Console;
using tdme::utils::_ExceptionBase;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

LevelEditorEntityLibrary::LevelEditorEntityLibrary(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntityLibrary::LevelEditorEntityLibrary(LevelEditorLevel* level) 
	: LevelEditorEntityLibrary(*static_cast< ::default_init_tag* >(0))
{
	ctor(level);
}

constexpr int32_t LevelEditorEntityLibrary::ID_ALLOCATE;

void LevelEditorEntityLibrary::ctor(LevelEditorLevel* level)
{
	super::ctor();
	this->level = level;
	this->entityIdx = 0;
}

void LevelEditorEntityLibrary::clear()
{
	this->entitiesById.clear();
	this->entities.clear();
	this->entityIdx = 0;
}

int32_t LevelEditorEntityLibrary::allocateEntityId()
{
	return entityIdx++;
}

LevelEditorEntity* LevelEditorEntityLibrary::addModel(int32_t id, String* name, String* description, String* pathName, String* fileName, Vector3* pivot) /* throws(Exception) */
{
	LevelEditorEntity* levelEditorEntity = nullptr;
	if (fileName->toLowerCase()->endsWith(u".dae"_j)) {
		auto model = DAEReader::read(pathName, fileName);
		levelEditorEntity = new LevelEditorEntity(
			id == ID_ALLOCATE ? allocateEntityId() : id,
			LevelEditorEntity_EntityType::MODEL,
			name,
			description,
			nullptr,
			::java::lang::StringBuilder().
			 	 append(pathName)->
				 append(u"/"_j)->
				 append(fileName)->
				 toString()
			, ::java::lang::StringBuilder().
				append(
					(new String(model->getId()))->
						replace(static_cast< CharSequence* >(u"\\"_j), static_cast< CharSequence* >(u"_"_j))->
						replace(static_cast< CharSequence* >(u"/"_j), static_cast< CharSequence* >(u"_"_j))->
						replace(static_cast< CharSequence* >(u":"_j), static_cast< CharSequence* >(u"_"_j)))->
						append(u".png"_j)->
						toString(),
			model,
			new Vector3(0.0f, 0.0f, 0.0f)
		);
	} else
	if (fileName->toLowerCase()->endsWith(u".tm"_j)) {
		auto model = TMReader::read(pathName, fileName);
		levelEditorEntity = new LevelEditorEntity(
			id == ID_ALLOCATE ? allocateEntityId() : id,
			LevelEditorEntity_EntityType::MODEL,
			name,
			description,
			nullptr,
			::java::lang::StringBuilder().
			 	 append(pathName)->
				 append(u"/"_j)->
				 append(fileName)->
				 toString(),
			::java::lang::StringBuilder().
			 	 append(
			 		(new String(model->getId()))->
			 			replace(static_cast< CharSequence* >(u"\\"_j), static_cast< CharSequence* >(u"_"_j))->
						replace(static_cast< CharSequence* >(u"/"_j), static_cast< CharSequence* >(u"_"_j))->
						replace(static_cast< CharSequence* >(u":"_j), static_cast< CharSequence* >(u"_"_j)))->
						append(u".png"_j)->
						toString(),
			model,
			new Vector3(0.0f, 0.0f, 0.0f)
		);
	} else
	if (fileName->toLowerCase()->endsWith(u".tmm"_j)) {
		levelEditorEntity = ModelMetaDataFileImport::doImport(id == ID_ALLOCATE ? allocateEntityId() : id, pathName, fileName);
	} else {
		throw _ExceptionBase(
			StringConverter::toString(pathName->getCPPWString()) +
			"/" +
			StringConverter::toString(pathName->getCPPWString()) +
			string(": Unknown model file format")
		 );
	}
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

LevelEditorEntity* LevelEditorEntityLibrary::addTrigger(int32_t id, String* name, String* description, float width, float height, float depth) /* throws(Exception) */
{
	auto cacheId = ::java::lang::StringBuilder().append(u"leveleditor.trigger."_j)->append(width)
		->append(u"mx"_j)
		->append(height)
		->append(u"mx"_j)
		->append(depth)
		->append(u"m"_j)->toString();
	LevelEditorEntity* levelEditorEntity = nullptr;
	auto boundingBox = new BoundingBox(new Vector3(-width / 2.0f, 0.0f, -depth / 2.0f), new Vector3(+width / 2.0f, height, +depth / 2.0f));
	auto model = PrimitiveModel::createModel(boundingBox, ::java::lang::StringBuilder().append(cacheId)->append(u"_bv"_j)->toString());
	levelEditorEntity = new LevelEditorEntity(
		id == ID_ALLOCATE ? allocateEntityId() : id,
		LevelEditorEntity_EntityType::TRIGGER,
		name,
		description,
		nullptr,
		cacheId,
		::java::lang::StringBuilder().append(
			(new String(model->getId()))->
				replace(static_cast< CharSequence* >(u"\\"_j), static_cast< CharSequence* >(u"_"_j))->
				replace(static_cast< CharSequence* >(u"/"_j), static_cast< CharSequence* >(u"_"_j))->
				replace(static_cast< CharSequence* >(u":"_j), static_cast< CharSequence* >(u"_"_j))
		)->append(u".png"_j)->toString(),
		model,
		new Vector3()
	);
	levelEditorEntity->addBoundingVolume(0, new LevelEditorEntityBoundingVolume(0, levelEditorEntity));
	levelEditorEntity->getBoundingVolumeAt(0)->setupAabb(boundingBox->getMin(), boundingBox->getMax());
	id = levelEditorEntity->getId();
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

LevelEditorEntity* LevelEditorEntityLibrary::addEmpty(int32_t id, String* name, String* description) /* throws(Exception) */
{
	auto cacheId = u"leveleditor.empty"_j;
	LevelEditorEntity* levelEditorEntity = nullptr;
	auto model = DAEReader::read(u"resources/tools/leveleditor/models"_j, u"arrow.dae"_j);
	levelEditorEntity = new LevelEditorEntity(
		id == ID_ALLOCATE ? allocateEntityId() : id,
		LevelEditorEntity_EntityType::EMPTY,
		name,
		description,
		nullptr,
		cacheId,
		::java::lang::StringBuilder().
		 append(
			(new String(model->getId()))->
				replace(static_cast< CharSequence* >(u"\\"_j), static_cast< CharSequence* >(u"_"_j))->
				replace(static_cast< CharSequence* >(u"/"_j), static_cast< CharSequence* >(u"_"_j))->
				replace(static_cast< CharSequence* >(u":"_j), static_cast< CharSequence* >(u"_"_j)))->
				append(u".png"_j)->toString(),
		model,
		new Vector3()
	);
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

LevelEditorEntity* LevelEditorEntityLibrary::addParticleSystem(int32_t id, String* name, String* description) /* throws(Exception) */
{
	auto levelEditorEntity = new LevelEditorEntity(
		id == ID_ALLOCATE ? allocateEntityId() : id,
		LevelEditorEntity_EntityType::PARTICLESYSTEM,
		name,
		description,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		new Vector3()
	);
	addEntity(levelEditorEntity);
	return levelEditorEntity;
}

void LevelEditorEntityLibrary::addEntity(LevelEditorEntity* levelEditorEntity) /* throws(Exception) */
{

	auto entityByIdIt = entitiesById.find(levelEditorEntity->getId());
	if (entityByIdIt != entitiesById.end()) {
		throw _ExceptionBase("Entity id already in use");
	}
	entities.push_back(levelEditorEntity);
	entitiesById[levelEditorEntity->getId()] = levelEditorEntity;
	if (levelEditorEntity->getId() >= entityIdx)
		entityIdx = levelEditorEntity->getId() + 1;

}

LevelEditorEntity* LevelEditorEntityLibrary::getEntityAt(int32_t idx)
{
	return entities.at(idx);
}

LevelEditorEntity* LevelEditorEntityLibrary::getEntity(int32_t id)
{
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		return entityByIdIt->second;
	}
	return nullptr;
}

void LevelEditorEntityLibrary::removeEntity(int32_t id)
{
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		entitiesById.erase(entityByIdIt);
		entities.erase(remove(entities.begin(), entities.end(), entityByIdIt->second), entities.end());
	}
}

int32_t LevelEditorEntityLibrary::getEntityCount()
{
	return entities.size();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntityLibrary::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorEntityLibrary", 48);
    return c;
}

java::lang::Class* LevelEditorEntityLibrary::getClass0()
{
	return class_();
}

