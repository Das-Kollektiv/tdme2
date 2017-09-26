// Generated from /tdme/src/tdme/gui/elements/GUITabsController.java
#include <tdme/gui/elements/GUITabsController.h>

#include <vector>

#include <java/lang/Object.h>
#include <tdme/gui/elements/GUITabContentController.h>
#include <tdme/gui/elements/GUITabController.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/utils/MutableString.h>

using std::vector;

using tdme::gui::elements::GUITabsController;
using java::lang::Object;
using tdme::gui::elements::GUITabContentController;
using tdme::gui::elements::GUITabController;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::utils::MutableString;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUITabsController::GUITabsController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITabsController::GUITabsController(GUINode* node) 
	: GUITabsController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUITabsController::init()
{
	tabContentNodeId = new MutableString();
}

void GUITabsController::ctor(GUINode* node)
{
	super::ctor(node);
	init();
}

bool GUITabsController::isDisabled()
{
	return false;
}

void GUITabsController::setDisabled(bool disabled)
{
}

void GUITabsController::initialize()
{
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(&childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes.at(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUITabController* >(childController) != nullptr) {
			auto tabController = java_cast< GUITabController* >(childController);
			if (static_cast< GUINode* >(tabController->getNode()->getParentControllerNode()->getParentControllerNode()) != node)
				continue;

			tabController->setSelected(true);
			setTabContentSelected(tabController->getNode()->getId());
			break;
		}
	}
}

void GUITabsController::dispose()
{
}

void GUITabsController::postLayout()
{
}

void GUITabsController::unselect()
{
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(&childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes.at(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUITabController* >(childController) != nullptr) {
			auto tabController = java_cast< GUITabController* >(childController);
			if (static_cast< GUINode* >(tabController->getNode()->getParentControllerNode()->getParentControllerNode()) != node)
				continue;

			tabController->setSelected(false);
		}
	}
}

void GUITabsController::setTabContentSelected(const wstring& id)
{
	tabContentNodeId->set(id + L"-content");
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(&childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes.at(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUITabContentController* >(childController) != nullptr) {
			auto tabContentController = java_cast< GUITabContentController* >(childController);
			if (static_cast< GUINode* >(tabContentController->getNode()->getParentControllerNode()->getParentControllerNode()) != node)
				continue;

			(java_cast< GUITabContentController* >(childController))->setSelected(tabContentNodeId->equals(childController->getNode()->getId()));
		}
	}
}

void GUITabsController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
}

void GUITabsController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUITabsController::tick()
{
}

void GUITabsController::onFocusGained()
{
}

void GUITabsController::onFocusLost()
{
}

bool GUITabsController::hasValue()
{
	return false;
}

MutableString* GUITabsController::getValue()
{
	return nullptr;
}

void GUITabsController::setValue(MutableString* value)
{
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITabsController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITabsController", 35);
    return c;
}

java::lang::Class* GUITabsController::getClass0()
{
	return class_();
}

