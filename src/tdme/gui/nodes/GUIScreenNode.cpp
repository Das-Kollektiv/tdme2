// Generated from /tdme/src/tdme/gui/nodes/GUIScreenNode.java
#include <tdme/gui/nodes/GUIScreenNode.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/effects/GUIEffect.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIInputEventHandler.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap_ValuesIterator.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::nodes::GUIScreenNode;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using tdme::gui::GUI;
using tdme::gui::effects::GUIEffect;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIInputEventHandler;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::renderer::GUIRenderer;
using tdme::utils::MutableString;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap_ValuesIterator;
using tdme::utils::_HashMap;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUIScreenNode::GUIScreenNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIScreenNode::GUIScreenNode(String* id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, bool scrollable, bool popUp)  /* throws(GUIParserException) */
	: GUIScreenNode(*static_cast< ::default_init_tag* >(0))
{
	ctor(id,flow,overflowX,overflowY,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn,scrollable,popUp);
}

void GUIScreenNode::init()
{
	guiEffectOffsetX = 0;
	guiEffectOffsetY = 0;
}

void GUIScreenNode::ctor(String* id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, bool scrollable, bool popUp) /* throws(GUIParserException) */
{
	super::ctor(nullptr, nullptr, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn);
	init();
	this->gui = nullptr;
	this->nodeCounter = 0;
	this->screenWidth = 0;
	this->screenHeight = 0;
	this->nodesById = new _HashMap();
	this->floatingNodes = new _ArrayList();
	this->actionListener = new _ArrayList();
	this->changeListener = new _ArrayList();
	this->inputEventHandler = nullptr;
	this->childControllerNodes = new _ArrayList();
	this->screenNode = this;
	this->parentNode = nullptr;
	this->visible = true;
	this->popUp = popUp;
	this->effects = new _HashMap();
}

GUI* GUIScreenNode::getGUI()
{
	return gui;
}

void GUIScreenNode::setGUI(GUI* gui)
{
	this->gui = gui;
}

int32_t GUIScreenNode::getScreenWidth()
{
	return screenWidth;
}

int32_t GUIScreenNode::getScreenHeight()
{
	return screenHeight;
}

bool GUIScreenNode::isVisible()
{
	return visible;
}

void GUIScreenNode::setVisible(bool visible)
{
	this->visible = visible;
	if (gui != nullptr)
		gui->invalidateFocussedNode();

}

bool GUIScreenNode::isPopUp()
{
	return popUp;
}

void GUIScreenNode::setPopUp(bool popUp)
{
	this->popUp = popUp;
}

_ArrayList* GUIScreenNode::getFloatingNodes()
{
	return floatingNodes;
}

int32_t GUIScreenNode::getGUIEffectOffsetX()
{
	return guiEffectOffsetX;
}

void GUIScreenNode::setGUIEffectOffsetX(int32_t guiEffectOffsetX)
{
	this->guiEffectOffsetX = guiEffectOffsetX;
}

int32_t GUIScreenNode::getGUIEffectOffsetY()
{
	return guiEffectOffsetY;
}

void GUIScreenNode::setGUIEffectOffsetY(int32_t guiEffectOffsetY)
{
	this->guiEffectOffsetY = guiEffectOffsetY;
}

bool GUIScreenNode::isContentNode()
{
	return false;
}

int32_t GUIScreenNode::getContentWidth()
{
	return -1;
}

int32_t GUIScreenNode::getContentHeight()
{
	return -1;
}

void GUIScreenNode::layout()
{
	for (auto i = 0; i < subNodes->size(); i++) {
		java_cast< GUINode* >(subNodes->get(i))->layout();
	}
	getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes->size(); i++) {
		auto node = java_cast< GUINode* >(childControllerNodes->get(i));
		auto controller = node->getController();
		if (controller != nullptr) {
			controller->postLayout();
		}
	}
}

void GUIScreenNode::layout(GUINode* node)
{
	if (dynamic_cast< GUIParentNode* >(node) != nullptr) {
		auto parentNode = java_cast< GUIParentNode* >(node);
		parentNode->layoutSubNodes();
		parentNode->getChildControllerNodes(childControllerNodes);
		for (auto i = 0; i < childControllerNodes->size(); i++) {
			auto childNode = java_cast< GUINode* >(childControllerNodes->get(i));
			auto controller = childNode->getController();
			if (controller != nullptr) {
				controller->postLayout();
			}
		}
	} else {
		node->computeContentAlignment();
		auto controller = node->getController();
		if (controller != nullptr) {
			controller->postLayout();
		}
	}
}

void GUIScreenNode::setScreenSize(int32_t width, int32_t height)
{
	this->screenWidth = width;
	this->screenHeight = height;
	this->requestedConstraints->widthType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	this->requestedConstraints->width = width;
	this->requestedConstraints->heightType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	this->requestedConstraints->height = height;
	this->computedConstraints->left = 0;
	this->computedConstraints->top = 0;
	this->computedConstraints->width = width;
	this->computedConstraints->height = height;
}

String* GUIScreenNode::getNodeType()
{
	return u"screen"_j;
}

GUINode* GUIScreenNode::getNodeById(String* nodeId)
{
	return java_cast< GUINode* >(nodesById->get(nodeId));
}

String* GUIScreenNode::allocateNodeId()
{
	return ::java::lang::StringBuilder().append(u"tdme_gui_anonymous_node_"_j)->append((nodeCounter++))->toString();
}

bool GUIScreenNode::addNode(GUINode* node)
{
	if (node->id->length() == 0) {
		node->id = allocateNodeId();
	}
	if (java_cast< GUINode* >(nodesById->get(node->id)) != nullptr) {
		return false;
	}
	nodesById->put(node->id, node);
	return true;
}

bool GUIScreenNode::removeNode(GUINode* node)
{
	nodesById->remove(node->id);
	if (dynamic_cast< GUIParentNode* >(node) != nullptr) {
		auto parentNode = java_cast< GUIParentNode* >(node);
		for (auto i = 0; i < parentNode->subNodes->size(); i++) {
			removeNode(java_cast< GUINode* >(parentNode->subNodes->get(i)));
		}
	}
	return true;
}

void GUIScreenNode::render(GUIRenderer* guiRenderer)
{
	guiRenderer->initScreen(this);
	for (auto _i = effects->getValuesIterator()->iterator(); _i->hasNext(); ) {
		GUIEffect* effect = java_cast< GUIEffect* >(_i->next());
		{
			if (effect->isActive() == true) {
				effect->update(guiRenderer);
				effect->apply(guiRenderer);
			}
		}
	}
	floatingNodes->clear();
	super::render(guiRenderer, floatingNodes);
	guiRenderer->doneScreen();
}

void GUIScreenNode::renderFloatingNodes(GUIRenderer* guiRenderer)
{
	guiRenderer->initScreen(this);
	for (auto _i = effects->getValuesIterator()->iterator(); _i->hasNext(); ) {
		GUIEffect* effect = java_cast< GUIEffect* >(_i->next());
		{
			effect->apply(guiRenderer);
		}
	}
	for (auto i = 0; i < floatingNodes->size(); i++) {
		java_cast< GUINode* >(floatingNodes->get(i))->render(guiRenderer, nullptr);
	}
	guiRenderer->doneScreen();
}

void GUIScreenNode::determineFocussedNodes(GUIParentNode* parentNode, _ArrayList* focusableNodes)
{
	if (parentNode->conditionsMet == false) {
		return;
	}
	if (dynamic_cast< GUIElementNode* >(parentNode) != nullptr) {
		auto parentElementNode = java_cast< GUIElementNode* >(parentNode);
		if (parentElementNode->focusable == true && (parentElementNode->getController() == nullptr || parentElementNode->getController()->isDisabled() == false)) {
			focusableNodes->add(java_cast< GUIElementNode* >(parentNode));
		}
	}
	for (auto i = 0; i < parentNode->subNodes->size(); i++) {
		auto subNode = java_cast< GUINode* >(parentNode->subNodes->get(i));
		if (dynamic_cast< GUIParentNode* >(subNode) != nullptr) {
			determineFocussedNodes(java_cast< GUIParentNode* >(subNode), focusableNodes);
		}
	}
}

void GUIScreenNode::handleMouseEvent(GUIMouseEvent* event)
{
	mouseEventProcessedByFloatingNode = false;
	for (auto i = 0; i < floatingNodes->size(); i++) {
		auto floatingNode = java_cast< GUINode* >(floatingNodes->get(i));
		floatingNode->handleMouseEvent(event);
	}
	super::handleMouseEvent(event);
}

void GUIScreenNode::handleKeyboardEvent(GUIKeyboardEvent* event)
{
}

void GUIScreenNode::addActionListener(GUIActionListener* listener)
{
	actionListener->add(listener);
}

void GUIScreenNode::removeActionListener(GUIActionListener* listener)
{
	actionListener->remove(static_cast< Object* >(listener));
}

GUIInputEventHandler* GUIScreenNode::getInputEventHandler()
{
	return inputEventHandler;
}

void GUIScreenNode::setInputEventHandler(GUIInputEventHandler* inputEventHandler)
{
	this->inputEventHandler = inputEventHandler;
}

void GUIScreenNode::delegateActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	for (auto i = 0; i < actionListener->size(); i++) {
		java_cast< GUIActionListener* >(actionListener->get(i))->onActionPerformed(type, node);
	}
}

void GUIScreenNode::addChangeListener(GUIChangeListener* listener)
{
	changeListener->add(listener);
}

void GUIScreenNode::removeChangeListener(GUIChangeListener* listener)
{
	changeListener->remove(static_cast< Object* >(listener));
}

void GUIScreenNode::delegateValueChanged(GUIElementNode* node)
{
	for (auto i = 0; i < changeListener->size(); i++) {
		java_cast< GUIChangeListener* >(changeListener->get(i))->onValueChanged(node);
	}
}

void GUIScreenNode::getValues(_HashMap* values)
{
	values->clear();
	getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes->size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes->get(i));
		if (dynamic_cast< GUIElementNode* >(childControllerNode) != nullptr == false)
			continue;

		auto guiElementNode = (java_cast< GUIElementNode* >(childControllerNode));
		auto guiElementNodeController = guiElementNode->getController();
		if (guiElementNodeController->hasValue()) {
			auto name = guiElementNode->getName();
			auto value = guiElementNodeController->getValue();
			auto currentValue = java_cast< MutableString* >(values->get(name));
			if (currentValue == nullptr || currentValue->length() == 0) {
				values->put(name, value);
			}
		}
	}
}

void GUIScreenNode::setValues(_HashMap* values)
{
	getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes->size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes->get(i));
		if (dynamic_cast< GUIElementNode* >(childControllerNode) != nullptr == false)
			continue;

		auto guiElementNode = (java_cast< GUIElementNode* >(childControllerNode));
		auto guiElementNodeController = guiElementNode->getController();
		if (guiElementNodeController->hasValue()) {
			auto name = guiElementNode->getName();
			auto newValue = java_cast< MutableString* >(values->get(name));
			if (newValue == nullptr)
				continue;

			guiElementNodeController->setValue(newValue);
		}
	}
}

bool GUIScreenNode::addEffect(String* id, GUIEffect* effect)
{
	if (java_cast< GUIEffect* >(effects->get(id)) != nullptr) {
		return false;
	}
	effects->put(id, effect);
	return true;
}

GUIEffect* GUIScreenNode::getEffect(String* id)
{
	return java_cast< GUIEffect* >(effects->get(id));
}

bool GUIScreenNode::removeEffect(String* id)
{
	return java_cast< GUIEffect* >(effects->remove(id)) != nullptr;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIScreenNode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIScreenNode", 28);
    return c;
}

void GUIScreenNode::render(GUIRenderer* guiRenderer, _ArrayList* floatingNodes)
{
	super::render(guiRenderer, floatingNodes);
}

java::lang::Class* GUIScreenNode::getClass0()
{
	return class_();
}

