// Generated from /tdme/src/tdme/tools/shared/controller/EntityDisplaySubScreenController.java
#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Exception.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/shared/views/EntityDisplayView.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using java::lang::ClassCastException;
using java::lang::Exception;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::utils::MutableString;
using tdme::utils::_Console;
using tdme::utils::_Exception;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

EntityDisplaySubScreenController::EntityDisplaySubScreenController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

EntityDisplaySubScreenController::EntityDisplaySubScreenController() 
	: EntityDisplaySubScreenController(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

MutableString* EntityDisplaySubScreenController::CHECKBOX_CHECKED;

MutableString* EntityDisplaySubScreenController::CHECKBOX_UNCHECKED;

void EntityDisplaySubScreenController::ctor()
{
	super::ctor();
	view = new EntityDisplayView(this);
}

EntityDisplayView* EntityDisplaySubScreenController::getView()
{
	return view;
}

void EntityDisplaySubScreenController::initialize(GUIScreenNode* screenNode)
{
	try {
		displayBoundingVolume = java_cast< GUIElementNode* >(screenNode->getNodeById(u"display_boundingvolume"_j));
		displayShadowing = java_cast< GUIElementNode* >(screenNode->getNodeById(u"display_shadowing"_j));
		displayGround = java_cast< GUIElementNode* >(screenNode->getNodeById(u"display_ground"_j));
	} catch (_Exception& exception) {
		_Console::print(string("EntityDisplaySubScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
}

void EntityDisplaySubScreenController::setupDisplay()
{
	displayShadowing->getController()->setValue(view->isDisplayShadowing() == true ? CHECKBOX_CHECKED : CHECKBOX_UNCHECKED);
	displayGround->getController()->setValue(view->isDisplayGroundPlate() == true ? CHECKBOX_CHECKED : CHECKBOX_UNCHECKED);
	displayBoundingVolume->getController()->setValue(view->isDisplayBoundingVolume() == true ? CHECKBOX_CHECKED : CHECKBOX_UNCHECKED);
}

void EntityDisplaySubScreenController::onDisplayApply()
{
	view->setDisplayShadowing(displayShadowing->getController()->getValue()->equals(CHECKBOX_CHECKED));
	view->setDisplayGroundPlate(displayGround->getController()->getValue()->equals(CHECKBOX_CHECKED));
	view->setDisplayBoundingVolume(displayBoundingVolume->getController()->getValue()->equals(CHECKBOX_CHECKED));
}

bool EntityDisplaySubScreenController::getDisplayShadowing()
{
	return displayShadowing->getController()->getValue()->equals(CHECKBOX_CHECKED);
}

bool EntityDisplaySubScreenController::getDisplayGround()
{
	return displayGround->getController()->getValue()->equals(CHECKBOX_CHECKED);
}

bool EntityDisplaySubScreenController::getDisplayBoundingVolume()
{
	return displayBoundingVolume->getController()->getValue()->equals(CHECKBOX_CHECKED);
}

void EntityDisplaySubScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED)) {
{
				if (node->getId()->equals(u"button_display_apply"_j)) {
					onDisplayApply();
				} else {
					_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ModelViewerScreenController::onActionPerformed()::unknown, type='"_j)->append(static_cast< Object* >(type))
						->append(u"', id = '"_j)
						->append(node->getId())
						->append(u"'"_j)
						->append(u", name = '"_j)
						->append(node->getName())
						->append(u"'"_j)->toString()));
				}
				goto end_switch0;;
			}		}
		if ((v == GUIActionListener_Type::PERFORMED) || (v == GUIActionListener_Type::PERFORMING)) {
{
				goto end_switch0;;
			}		}
end_switch0:;
	}

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* EntityDisplaySubScreenController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.controller.EntityDisplaySubScreenController", 61);
    return c;
}

void EntityDisplaySubScreenController::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		CHECKBOX_CHECKED = new MutableString(u"1"_j);
		CHECKBOX_UNCHECKED = new MutableString(u""_j);
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* EntityDisplaySubScreenController::getClass0()
{
	return class_();
}

