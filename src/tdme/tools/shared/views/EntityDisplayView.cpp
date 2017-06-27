// Generated from /tdme/src/tdme/tools/shared/views/EntityDisplayView.java
#include <tdme/tools/shared/views/EntityDisplayView.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Comparable.h>
#include <java/lang/String.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::tools::shared::views::EntityDisplayView;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

EntityDisplayView::EntityDisplayView(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

EntityDisplayView::EntityDisplayView(EntityDisplaySubScreenController* entityDisplaySubScreenController) 
	: EntityDisplayView(*static_cast< ::default_init_tag* >(0))
{
	ctor(entityDisplaySubScreenController);
}

void EntityDisplayView::init()
{
	displayGroundPlate = false;
	displayShadowing = false;
	displayBoundingVolume = false;
}

StringArray* EntityDisplayView::MODEL_BOUNDINGVOLUME_IDS;

void EntityDisplayView::ctor(EntityDisplaySubScreenController* entityDisplaySubScreenController)
{
	super::ctor();
	init();
	this->engine = Engine::getInstance();
	this->entityDisplaySubScreenController = entityDisplaySubScreenController;
}

bool EntityDisplayView::isDisplayGroundPlate()
{
	return displayGroundPlate;
}

void EntityDisplayView::setDisplayGroundPlate(bool groundPlate)
{
	this->displayGroundPlate = groundPlate;
}

bool EntityDisplayView::isDisplayShadowing()
{
	return displayShadowing;
}

void EntityDisplayView::setDisplayShadowing(bool shadowing)
{
	this->displayShadowing = shadowing;
}

bool EntityDisplayView::isDisplayBoundingVolume()
{
	return displayBoundingVolume;
}

void EntityDisplayView::setDisplayBoundingVolume(bool displayBoundingVolume)
{
	this->displayBoundingVolume = displayBoundingVolume;
}

void EntityDisplayView::display(LevelEditorEntity* entity)
{
	if (entity != nullptr) {
		auto model = engine->getEntity(u"model"_j);
		if (model == nullptr)
			return;

		auto ground = engine->getEntity(u"ground"_j);
		model->setDynamicShadowingEnabled(displayShadowing);
		ground->setEnabled(displayGroundPlate);
		for (auto i = 0; i < MODEL_BOUNDINGVOLUME_IDS->length; i++) {
			auto modelBoundingVolume = engine->getEntity((*MODEL_BOUNDINGVOLUME_IDS)[i]);
			if (modelBoundingVolume != nullptr) {
				modelBoundingVolume->setEnabled(displayBoundingVolume);
			}
		}
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* EntityDisplayView::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.views.EntityDisplayView", 41);
    return c;
}

void EntityDisplayView::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		MODEL_BOUNDINGVOLUME_IDS = (new StringArray({
			u"model_bv.0"_j,
			u"model_bv.1"_j,
			u"model_bv.2"_j,
			u"model_bv.3"_j,
			u"model_bv.4"_j,
			u"model_bv.5"_j,
			u"model_bv.6"_j,
			u"model_bv.7"_j
		}));
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* EntityDisplayView::getClass0()
{
	return class_();
}

