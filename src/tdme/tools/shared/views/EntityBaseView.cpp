// Generated from /tdme/src/tdme/tools/shared/views/EntityBaseView.java
#include <tdme/tools/shared/views/EntityBaseView.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/util/HashMap.h>
#include <java/util/Iterator.h>
#include <java/util/Set.h>
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelPropertyPresets.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/utils/_ArrayList.h>

using tdme::tools::shared::views::EntityBaseView;
using java::lang::ClassCastException;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::util::HashMap;
using java::util::Iterator;
using java::util::Set;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelPropertyPresets;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::utils::_ArrayList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

EntityBaseView::EntityBaseView(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

EntityBaseView::EntityBaseView(EntityBaseSubScreenController* entityBaseSubScreenController) 
	: EntityBaseView(*static_cast< ::default_init_tag* >(0))
{
	ctor(entityBaseSubScreenController);
}

void EntityBaseView::ctor(EntityBaseSubScreenController* entityBaseSubScreenController)
{
	super::ctor();
	this->entityBaseSubScreenController = entityBaseSubScreenController;
}

void EntityBaseView::initialize()
{
	entityBaseSubScreenController->setEntityPresetIds(LevelPropertyPresets::getInstance()->getObjectPropertiesPresets()->keySet());
}

void EntityBaseView::entityPropertiesPreset(LevelEditorEntity* entity, String* presetId)
{
	if (entity == nullptr)
		return;

	entity->clearProperties();
	auto entityPropertyPresetArrayList = java_cast< _ArrayList* >(LevelPropertyPresets::getInstance()->getObjectPropertiesPresets()->get(presetId));
	if (entityPropertyPresetArrayList != nullptr) {
		for (auto _i = entityPropertyPresetArrayList->iterator(); _i->hasNext(); ) {
			PropertyModelClass* entityPropertyPreset = java_cast< PropertyModelClass* >(_i->next());
			{
				entity->addProperty(entityPropertyPreset->getName(), entityPropertyPreset->getValue());
			}
		}
	}
	entityBaseSubScreenController->setEntityProperties(entity, presetId, entity->getProperties(), nullptr);
}

bool EntityBaseView::entityPropertySave(LevelEditorEntity* entity, String* oldName, String* name, String* value)
{
	if (entity == nullptr)
		return false;

	if (entity->updateProperty(oldName, name, value) == true) {
		entityBaseSubScreenController->setEntityProperties(entity, nullptr, entity->getProperties(), name);
		return true;
	}
	return false;
}

bool EntityBaseView::entityPropertyAdd(LevelEditorEntity* entity)
{
	if (entity == nullptr)
		return false;

	if (entity->addProperty(u"new.property"_j, u"new.value"_j)) {
		entityBaseSubScreenController->setEntityProperties(entity, nullptr, entity->getProperties(), u"new.property"_j);
		return true;
	}
	return false;
}

bool EntityBaseView::entityPropertyRemove(LevelEditorEntity* entity, String* name)
{
	if (entity == nullptr)
		return false;

	auto idx = entity->getPropertyIndex(name);
	if (idx != -1 && entity->removeProperty(name) == true) {
		auto property = entity->getPropertyByIndex(idx);
		if (property == nullptr) {
			property = entity->getPropertyByIndex(idx - 1);
		}
		entityBaseSubScreenController->setEntityProperties(entity, nullptr, entity->getProperties(), property == nullptr ? static_cast< String* >(nullptr) : property->getName());
		return true;
	}
	return false;
}

void EntityBaseView::setEntityData(LevelEditorEntity* entity, String* name, String* description)
{
	if (entity == nullptr)
		return;

	entity->setName(name);
	entity->setDescription(description);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* EntityBaseView::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.views.EntityBaseView", 38);
    return c;
}

java::lang::Class* EntityBaseView::getClass0()
{
	return class_();
}

