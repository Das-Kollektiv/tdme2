#include <tdme/gui/nodes/GUIScreenNode.h>

#include <algorithm>
#include <map>
#include <string>

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

using std::map;
using std::wstring;
using std::to_wstring;

using tdme::gui::nodes::GUIScreenNode;
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

GUIScreenNode::GUIScreenNode(const wstring& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, bool scrollable, bool popUp)  /* throws(GUIParserException) */
	: GUIParentNode(nullptr, nullptr, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn)
{
	init();
	this->gui = nullptr;
	this->nodeCounter = 0;
	this->screenWidth = 0;
	this->screenHeight = 0;
	this->inputEventHandler = nullptr;
	this->screenNode = this;
	this->parentNode = nullptr;
	this->visible = true;
	this->popUp = popUp;
}

void GUIScreenNode::init()
{
	guiEffectOffsetX = 0;
	guiEffectOffsetY = 0;
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

vector<GUINode*>* GUIScreenNode::getFloatingNodes()
{
	return &floatingNodes;
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
	for (auto i = 0; i < subNodes.size(); i++) {
		subNodes.at(i)->layout();
	}
	getChildControllerNodes(&childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto node = childControllerNodes.at(i);
		auto controller = node->getController();
		if (controller != nullptr) {
			controller->postLayout();
		}
	}
}

void GUIScreenNode::layout(GUINode* node)
{
	if (dynamic_cast< GUIParentNode* >(node) != nullptr) {
		auto parentNode = dynamic_cast< GUIParentNode* >(node);
		parentNode->layoutSubNodes();
		parentNode->getChildControllerNodes(&childControllerNodes);
		for (auto i = 0; i < childControllerNodes.size(); i++) {
			auto childNode = childControllerNodes.at(i);
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

const wstring GUIScreenNode::getNodeType()
{
	return L"screen";
}

GUINode* GUIScreenNode::getNodeById(const wstring& nodeId)
{
	auto nodesByIdIt = nodesById.find(nodeId);
	if (nodesByIdIt == nodesById.end()) {
		return nullptr;
	}
	return nodesByIdIt->second;
}

const wstring GUIScreenNode::allocateNodeId()
{
	return L"tdme_gui_anonymous_node_" + to_wstring(nodeCounter++);
}

bool GUIScreenNode::addNode(GUINode* node)
{
	if (node->id.length() == 0) {
		node->id = allocateNodeId();
	}
	if (nodesById.find(node->id) != nodesById.end()) {
		return false;
	}
	nodesById[node->id] = node;
	return true;
}

bool GUIScreenNode::removeNode(GUINode* node)
{
	nodesById.erase(node->id);
	if (dynamic_cast< GUIParentNode* >(node) != nullptr) {
		auto parentNode = dynamic_cast< GUIParentNode* >(node);
		for (auto i = 0; i < parentNode->subNodes.size(); i++) {
			removeNode(parentNode->subNodes.at(i));
		}
	}
	return true;
}

void GUIScreenNode::render(GUIRenderer* guiRenderer)
{
	guiRenderer->initScreen(this);
	for (const auto& i : effects) {
		auto effect = i.second;
		if (effect->isActive() == true) {
			effect->update(guiRenderer);
			effect->apply(guiRenderer);
		}
	}
	floatingNodes.clear();
	GUIParentNode::render(guiRenderer, &floatingNodes);
	guiRenderer->doneScreen();
}

void GUIScreenNode::renderFloatingNodes(GUIRenderer* guiRenderer)
{
	guiRenderer->initScreen(this);
	for (const auto& i : effects) {
		auto effect = i.second;
		effect->apply(guiRenderer);
	}
	for (auto i = 0; i < floatingNodes.size(); i++) {
		floatingNodes.at(i)->render(guiRenderer, nullptr);
	}
	guiRenderer->doneScreen();
}

void GUIScreenNode::determineFocussedNodes(GUIParentNode* parentNode, vector<GUIElementNode*>* focusableNodes)
{
	if (parentNode->conditionsMet == false) {
		return;
	}
	if (dynamic_cast< GUIElementNode* >(parentNode) != nullptr) {
		auto parentElementNode = dynamic_cast< GUIElementNode* >(parentNode);
		if (parentElementNode->focusable == true && (parentElementNode->getController() == nullptr || parentElementNode->getController()->isDisabled() == false)) {
			focusableNodes->push_back(dynamic_cast< GUIElementNode* >(parentNode));
		}
	}
	for (auto i = 0; i < parentNode->subNodes.size(); i++) {
		auto subNode = parentNode->subNodes.at(i);
		if (dynamic_cast< GUIParentNode* >(subNode) != nullptr) {
			determineFocussedNodes(dynamic_cast< GUIParentNode* >(subNode), focusableNodes);
		}
	}
}

void GUIScreenNode::handleMouseEvent(GUIMouseEvent* event)
{
	mouseEventProcessedByFloatingNode = false;
	for (auto i = 0; i < floatingNodes.size(); i++) {
		auto floatingNode = floatingNodes.at(i);
		floatingNode->handleMouseEvent(event);
	}
	GUIParentNode::handleMouseEvent(event);
}

void GUIScreenNode::handleKeyboardEvent(GUIKeyboardEvent* event)
{
}

void GUIScreenNode::addActionListener(GUIActionListener* listener)
{
	actionListener.push_back(listener);
}

void GUIScreenNode::removeActionListener(GUIActionListener* listener)
{
	actionListener.erase(std::remove(actionListener.begin(), actionListener.end(), listener), actionListener.end());
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
	for (auto i = 0; i < actionListener.size(); i++) {
		actionListener.at(i)->onActionPerformed(type, node);
	}
}

void GUIScreenNode::addChangeListener(GUIChangeListener* listener)
{
	changeListener.push_back(listener);
}

void GUIScreenNode::removeChangeListener(GUIChangeListener* listener)
{
	changeListener.erase(std::remove(changeListener.begin(), changeListener.end(), listener), changeListener.end());
}

void GUIScreenNode::delegateValueChanged(GUIElementNode* node)
{
	for (auto i = 0; i < changeListener.size(); i++) {
		changeListener.at(i)->onValueChanged(node);
	}
}

void GUIScreenNode::getValues(map<wstring, MutableString*>* values)
{
	values->clear();
	getChildControllerNodes(&childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes.at(i);
		if (dynamic_cast< GUIElementNode* >(childControllerNode) != nullptr == false)
			continue;

		auto guiElementNode = (dynamic_cast< GUIElementNode* >(childControllerNode));
		auto guiElementNodeController = guiElementNode->getController();
		if (guiElementNodeController->hasValue()) {
			auto name = guiElementNode->getName();
			auto value = guiElementNodeController->getValue();
			auto currentValueIt = values->find(name);
			if (currentValueIt == values->end() || currentValueIt->second->length() == 0) {
				(*values)[name] = value;
			}
		}
	}
}

void GUIScreenNode::setValues(map<wstring, MutableString*>* values)
{
	getChildControllerNodes(&childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes.at(i);
		if (dynamic_cast< GUIElementNode* >(childControllerNode) != nullptr == false)
			continue;

		auto guiElementNode = (dynamic_cast< GUIElementNode* >(childControllerNode));
		auto guiElementNodeController = guiElementNode->getController();
		if (guiElementNodeController->hasValue()) {
			auto name = guiElementNode->getName();
			auto newValueIt = values->find(name);
			if (newValueIt == values->end())
				continue;

			guiElementNodeController->setValue(newValueIt->second);
		}
	}
}

bool GUIScreenNode::addEffect(const wstring& id, GUIEffect* effect)
{
	if (effects.find(id) != effects.end()) {
		return false;
	}
	effects[id] = effect;
	return true;
}

GUIEffect* GUIScreenNode::getEffect(const wstring& id)
{
	auto effectsIt = effects.find(id);
	if (effectsIt == effects.end()) {
		return nullptr;
	}
	return effectsIt->second;
}

bool GUIScreenNode::removeEffect(const wstring& id)
{
	auto eraseCount = effects.erase(id);
	if (eraseCount == 0) {
		return false;
	}
	return true;
}

void GUIScreenNode::render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes)
{
	GUIParentNode::render(guiRenderer, floatingNodes);
}

