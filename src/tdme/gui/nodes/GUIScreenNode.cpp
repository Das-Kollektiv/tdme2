#include <tdme/gui/nodes/GUIScreenNode.h>

#include <algorithm>
#include <map>
#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIContextMenuRequestListener.h>
#include <tdme/gui/events/GUIDragRequestListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUIInputEventHandler.h>
#include <tdme/gui/events/GUIMouseOverListener.h>
#include <tdme/gui/events/GUIMoveListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode_SizeConstraints.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/scripting/GUIMiniScript.h>
#include <tdme/gui/GUI.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MutableString.h>

using std::map;
using std::remove;
using std::reverse;
using std::span;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIContextMenuRequestListener;
using tdme::gui::events::GUIDragRequestListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUIInputEventHandler;
using tdme::gui::events::GUIMouseOverListener;
using tdme::gui::events::GUIMoveListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIScreenNode_SizeConstraints;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::scripting::GUIMiniScript;
using tdme::gui::GUI;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Integer;
using tdme::utilities::MiniScript;
using tdme::utilities::MutableString;

GUIScreenNode::GUIScreenNode(
	const string& fileName,
	const string& applicationRootPathName,
	const string& applicationSubPathName,
	const string& id,
	GUINode_Flow* flow,
	GUIParentNode_Overflow* overflowX,
	GUIParentNode_Overflow* overflowY,
	const GUINode_Alignments& alignments,
	const GUINode_RequestedConstraints& requestedConstraints,
	const GUIColor& backgroundColor,
	const string& backgroundImage,
	const GUINode_Scale9Grid& backgroundImageScale9Grid,
	const GUIColor& backgroundImageEffectColorMul,
	const GUIColor& backgroundImageEffectColorAdd,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUIScreenNode_SizeConstraints& sizeConstraints,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& tooltip,
	bool scrollable,
	bool popUp,
	const string& script
):
	GUIParentNode(this, nullptr, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn, tooltip)
{
	this->fileName = fileName;
	this->applicationRootPathName = applicationRootPathName;
	this->applicationSubPathName = applicationSubPathName;
	this->sizeConstraints = sizeConstraints;
	this->gui = nullptr;
	this->nodeCounter = 0;
	this->screenWidth = 0;
	this->screenHeight = 0;
	this->inputEventHandler = nullptr;
	this->screenNode = this;
	this->parentNode = nullptr;
	this->visible = true;
	this->popUp = popUp;
	if (script.empty() == false) {
		this->script = new GUIMiniScript(this);
		this->script->loadScript(
			FileSystem::getInstance()->getPathName(script),
			FileSystem::getInstance()->getFileName(script)
		);
		//
		Console::println(this->script->getInformation());
		//
		this->scriptOnActionAvailable = this->script->hasFunction("onAction");
		this->scriptOnChangeAvailable = this->script->hasFunction("onChange");
		this->scriptOnMouseOverAvailable = this->script->hasFunction("onMouseOver");
		this->scriptOnContextMenuRequestAvailable = this->script->hasFunction("onContextMenuRequest");
		this->scriptOnFocusAvailable = this->script->hasFunction("onFocus");
		this->scriptOnUnfocusAvailable = this->script->hasFunction("onUnfocus");
		this->scriptOnMoveAvailable = this->script->hasFunction("onMove");
		this->scriptOnMoveReleaseAvailable = this->script->hasFunction("onMoveRelease");
		this->scriptOnTooltipShowRequestAvailable = this->script->hasFunction("onTooltipShowRequest");
		this->scriptOnTooltipCloseRequestAvailable = this->script->hasFunction("onTooltipCloseRequest");
		this->scriptOnDragRequestAvailable = this->script->hasFunction("onDragRequest");
		this->scriptOnTickAvailable = this->script->hasFunction("onTick");
		//
		Console::println("Available event script handler functions:");
		Console::println("onAction: " + string(this->scriptOnActionAvailable == true?"YES":"NO"));
		Console::println("onChange: " + string(this->scriptOnChangeAvailable == true?"YES":"NO"));
		Console::println("onMouseOver: " + string(this->scriptOnMouseOverAvailable == true?"YES":"NO"));
		Console::println("onContextMenuRequest: " + string(this->scriptOnContextMenuRequestAvailable == true?"YES":"NO"));
		Console::println("onFocus: " + string(this->scriptOnFocusAvailable == true?"YES":"NO"));
		Console::println("onUnfocus: " + string(this->scriptOnUnfocusAvailable == true?"YES":"NO"));
		Console::println("onMove: " + string(this->scriptOnMoveAvailable == true?"YES":"NO"));
		Console::println("onMoveRelease: " + string(this->scriptOnMoveReleaseAvailable == true?"YES":"NO"));
		Console::println("onTooltipShowRequest: " + string(this->scriptOnTooltipShowRequestAvailable == true?"YES":"NO"));
		Console::println("onTooltipCloseRequest: " + string(this->scriptOnTooltipCloseRequestAvailable == true?"YES":"NO"));
		Console::println("onDragRequest: " + string(this->scriptOnDragRequestAvailable == true?"YES":"NO"));
		Console::println("onTick: " + string(this->scriptOnTickAvailable == true?"YES":"NO"));
		Console::println();
	}
}

GUIScreenNode::~GUIScreenNode() {
	// remove sub nodes
	for (auto i = 0; i < subNodes.size(); i++) {
		removeNode(subNodes[i]);
	}
	subNodes.clear();

	// dispose
	GUINode::dispose();

	// delete chaches
	for (auto& fontCacheIt: fontCache) {
		delete fontCacheIt.second;
	}
	fontCache.clear();
	for (auto& imageCacheIt: imageCache) {
		imageCacheIt.second->releaseReference();
	}
	imageCache.clear();

	// delete miniscript
	if (script != nullptr) delete script;
}

GUI* GUIScreenNode::getGUI()
{
	return gui;
}

void GUIScreenNode::setGUI(GUI* gui)
{
	this->gui = gui;
}

void GUIScreenNode::setVisible(bool visible)
{
	if (this->visible == visible) return;
	this->visible = visible;
	if (gui != nullptr &&
		((visible == false && gui->getFocussedNode() != nullptr && gui->getFocussedNode()->getScreenNode() == this) ||
		visible == true)) {
		//
		gui->invalidateFocussedNode();
	}
	//
	if (gui != nullptr) gui->applyRenderScreensChange();
}

void GUIScreenNode::setPopUp(bool popUp)
{
	this->popUp = popUp;
}

const vector<GUINode*>& GUIScreenNode::getFloatingNodes()
{
	return floatingNodes;
}

bool GUIScreenNode::isContentNode()
{
	return false;
}

int GUIScreenNode::getContentWidth()
{
	return -1;
}

int GUIScreenNode::getContentHeight()
{
	return -1;
}

void GUIScreenNode::layout()
{
	for (auto i = 0; i < subNodes.size(); i++) {
		subNodes[i]->layout();
	}
	getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto node = childControllerNodes[i];
		auto controller = node->getController();
		if (controller != nullptr && node->layouted == true) {
			controller->postLayout();
		}
	}
	layouted = true;
}

GUINode* GUIScreenNode::forceInvalidateLayout(GUINode* node) {
	{
		auto _node = node;
		while (_node != nullptr) {
			if (_node->conditionsMet == false) {
				return nullptr;
			}
			_node = _node->parentNode;
		}
	}

	// first step, make sure all parents up to screen node are layouted
	auto _node = node;
	auto __node = node;
	if (node->parentNode != nullptr) {
		__node = __node->parentNode;
		while (_node != nullptr) {
			if (_node->layouted == false) __node = _node;
			_node = _node->parentNode;
		}
		_node = __node;
	}

	// invalidate all nodes from node to _node
	for (__node = node; __node != _node; __node = __node->parentNode) {
		__node->layouted = false;
	}

	// find a node that is a valid base for layouting from
	while (
		_node->parentNode != nullptr &&
		// auto depends on its children dimensions, so do relayout the parent
		((_node->requestedConstraints.leftType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO ||
		_node->requestedConstraints.topType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO ||
		_node->requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO ||
		_node->requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) ||
		// percent depend on its parent dimensions so make sure its already layouted
		(_node->layouted == false &&
		(_node->requestedConstraints.leftType == GUINode_RequestedConstraints_RequestedConstraintsType::PERCENT ||
		_node->requestedConstraints.topType == GUINode_RequestedConstraints_RequestedConstraintsType::PERCENT ||
		_node->requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::PERCENT ||
		_node->requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::PERCENT)) ||
		// star depend on its parent dimensions, so make sure its already layouted
		(_node->layouted == false &&
		(_node->requestedConstraints.leftType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR ||
		_node->requestedConstraints.topType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR ||
		_node->requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR ||
		_node->requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR)))) {
		_node->layouted = false;
		_node = _node->parentNode;
	}

	//
	_node->layouted = false;

	//
	auto parentNode = dynamic_cast<GUIParentNode*>(_node);
	if (parentNode != nullptr) parentNode->invalidateRenderCaches();

	//
	return _node;
}

void GUIScreenNode::invalidateLayouts() {
	// invalidate layouts and mark nodes that are required to start layouting with
	// in a map with hierarchical id which gets sorted from root -> child node
	map<string, GUINode*> nodesToForceLayout;
	for (auto& nodeId: invalidateLayoutNodeIds) {
		auto node = getNodeById(nodeId);
		if (node == nullptr) continue;
		auto layoutNode = forceInvalidateLayout(node);
		if (layoutNode == nullptr) continue;
		nodesToForceLayout[layoutNode->getHierarchicalId()] = layoutNode;
	}
	//
	invalidateLayoutNodeIds.clear();
	// force layouts
	for (auto& nodesToForceLayoutIt: nodesToForceLayout) {
		// check if parent node was layouted in this layout sequence already
		auto parentNodeLayouted = false;
		auto node = nodesToForceLayoutIt.second;
		auto _node = node->parentNode;
		// check if node's parent nodes were layouted
		while (_node != nullptr) {
			if (nodesToForceLayout.find(_node->getHierarchicalId()) != nodesToForceLayout.end()) {
				parentNodeLayouted = true;
				break;
			}
			_node = _node->parentNode;
		}
		// jup, skip
		if (parentNodeLayouted == true) continue;
		// otherwise layout
		forceLayout(node);
	}
}

void GUIScreenNode::forceLayout(GUINode* node)
{
	// do the magic
	if (dynamic_cast<GUIParentNode*>(node) != nullptr) {
		auto parentNode = required_dynamic_cast<GUIParentNode*>(node);
		parentNode->layouted = true;
		parentNode->layoutSubNodes();
		parentNode->layoutSubNodes();
		parentNode->getScreenNode()->getChildControllerNodes(childControllerNodes, true);
		for (auto i = 0; i < childControllerNodes.size(); i++) {
			auto childNode = childControllerNodes[i];
			auto childController = childNode->getController();
			if (childController != nullptr) childController->postLayout();
		}
	} else {
		node->layout();
		node->getScreenNode()->layoutSubNodes();
		node->computeContentAlignment();
		auto nodeController = node->getController();
		if (nodeController != nullptr) nodeController->postLayout();
	}
}

void GUIScreenNode::scrollToNodes() {
	for (auto& scrollToNodeX: scrollToNodesX) {
		auto node = getNodeById(scrollToNodeX.node);
		auto toNode = scrollToNodeX.toNode.empty() == true?nullptr:dynamic_cast<GUIParentNode*>(getNodeById(scrollToNodeX.toNode));
		if (node != nullptr) node->_scrollToNodeX(toNode);
	}
	scrollToNodesX.clear();
	for (auto& scrollToNodeY: scrollToNodesY) {
		auto node = getNodeById(scrollToNodeY.node);
		auto toNode = scrollToNodeY.toNode.empty() == true?nullptr:dynamic_cast<GUIParentNode*>(getNodeById(scrollToNodeY.toNode));
		if (node != nullptr) node->_scrollToNodeY(toNode);
	}
	scrollToNodesY.clear();
}

void GUIScreenNode::setScreenSize(int width, int height)
{
	this->screenWidth = width;
	this->screenHeight = height;
	this->requestedConstraints.widthType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	this->requestedConstraints.width = width;
	this->requestedConstraints.heightType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	this->requestedConstraints.height = height;
	this->computedConstraints.left = 0;
	this->computedConstraints.top = 0;
	this->computedConstraints.width = width;
	this->computedConstraints.height = height;
	this->layouted = false;
}


const string GUIScreenNode::getNodeType()
{
	return "screen";
}

bool GUIScreenNode::addNode(GUINode* node)
{
	// if node does exist do not insert it and return
	if (nodesById.find(node->id) != nodesById.end()) {
		return false;
	}
	// otherwise go
	nodesById[node->id] = node;

	// add to floating nodes
	if (node->flow == GUINode_Flow::FLOATING) floatingNodes.push_back(node);

	return true;
}

void GUIScreenNode::removeNodeById(const string& nodeId, bool resetScrollOffsets) {
	auto node = getNodeById(nodeId);
	if (node == nullptr) {
		Console::println("GUIScreenNode::removeNodeById(): node not found: " + nodeId);
		return;
	}
	if (node->parentNode != nullptr) node->parentNode->removeSubNode(node, resetScrollOffsets);
	removeNode(node);
}

bool GUIScreenNode::removeNode(GUINode* node)
{
	{
		auto elementNodeToNodeMappingIt = elementNodeToNodeMapping.find(node->getId());
		if (elementNodeToNodeMappingIt != elementNodeToNodeMapping.end()) {
			elementNodeToNodeMapping.erase(elementNodeToNodeMappingIt);
		}
	}
	{
		for (auto& elementNodeToNodeMappingIt: elementNodeToNodeMapping) {
			elementNodeToNodeMappingIt.second.erase(node->getId());
		}
	}
	if (dynamic_cast<GUIParentNode*>(node) != nullptr) {
		auto parentNode = required_dynamic_cast<GUIParentNode*>(node);
		for (auto i = 0; i < parentNode->subNodes.size(); i++) {
			removeNode(parentNode->subNodes[i]);
		}
		parentNode->subNodes.clear();
	}
	nodesById.erase(node->id);
	tickNodesById.erase(node->getId());
	floatingNodes.erase(remove(floatingNodes.begin(), floatingNodes.end(), node), floatingNodes.end());
	node->dispose();
	delete node;
	return true;
}

void GUIScreenNode::render(GUIRenderer* guiRenderer)
{
	guiRenderer->initScreen(this);
	GUIParentNode::layoutOnDemand();
	if (hasEffects() == true) applyEffects(guiRenderer);
	GUIParentNode::render(guiRenderer);
	if (hasEffects() == true) undoEffects(guiRenderer);
	guiRenderer->doneScreen();
}

void GUIScreenNode::renderFloatingNodes(GUIRenderer* guiRenderer)
{
	guiRenderer->initScreen(this);
	for (auto i = 0; i < floatingNodes.size(); i++) {
		auto floatingNode = floatingNodes[i];
		auto skipFloatingNode = false;
		auto _floatingNode = floatingNode;
		do {
			if (_floatingNode->conditionsMet == false) {
				skipFloatingNode = true;
				break;
			}
			_floatingNode = _floatingNode->parentNode;
		} while (_floatingNode != nullptr);
		if (skipFloatingNode == true) continue;
		guiRenderer->setRenderAreaLeft(GUIRenderer::SCREEN_LEFT);
		guiRenderer->setRenderAreaTop(GUIRenderer::SCREEN_TOP);
		guiRenderer->setRenderAreaRight(GUIRenderer::SCREEN_RIGHT);
		guiRenderer->setRenderAreaBottom(GUIRenderer::SCREEN_BOTTOM);
		floatingNodes[i]->render(guiRenderer);
	}
	guiRenderer->doneScreen();
}

void GUIScreenNode::determineFocussedNodes(GUIParentNode* parentNode, vector<GUIElementNode*>& focusableNodes)
{
	if (parentNode->conditionsMet == false) {
		return;
	}
	if (dynamic_cast<GUIElementNode*>(parentNode) != nullptr) {
		auto parentElementNode = required_dynamic_cast<GUIElementNode*>(parentNode);
		if (parentElementNode->focusable == true && (parentElementNode->getController() == nullptr || parentElementNode->getController()->isDisabled() == false)) {
			focusableNodes.push_back(required_dynamic_cast<GUIElementNode*>(parentNode));
		}
	}
	for (auto i = 0; i < parentNode->subNodes.size(); i++) {
		auto subNode = parentNode->subNodes[i];
		if (dynamic_cast<GUIParentNode*>(subNode) != nullptr) {
			determineFocussedNodes(required_dynamic_cast<GUIParentNode*>(subNode), focusableNodes);
		}
	}
}

void GUIScreenNode::determineMouseEventNodes(GUIMouseEvent* event, bool floatingNode, unordered_set<string>& eventNodeIds, unordered_set<string>& eventFloatingNodeIds, int flags)
{
	for (auto i = 0; i < floatingNodes.size(); i++) {
		floatingNodes[i]->determineMouseEventNodes(event, floatingNode == true || flow == GUINode_Flow::FLOATING, eventNodeIds, eventFloatingNodeIds, flags);
	}
	GUIParentNode::determineMouseEventNodes(event, floatingNode, eventNodeIds, eventFloatingNodeIds, flags);
}

void GUIScreenNode::addActionListener(GUIActionListener* listener)
{
	removeActionListener(listener);
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

void GUIScreenNode::forwardAction(GUIActionListenerType type, GUIElementNode* node)
{
	forwardEventList.push_back(
		{
			.eventType = ForwardEvent::EVENTTYPE_ACTION,
			.nodeId = node->getId(),
			.mouseX = -1,
			.mouseY = -1,
			.type = type
		}
	);
}

void GUIScreenNode::addChangeListener(GUIChangeListener* listener)
{
	removeChangeListener(listener);
	changeListener.push_back(listener);
}

void GUIScreenNode::removeChangeListener(GUIChangeListener* listener)
{
	changeListener.erase(std::remove(changeListener.begin(), changeListener.end(), listener), changeListener.end());
}

void GUIScreenNode::forwardChange(GUIElementNode* node)
{
	node->executeOnChangeExpression();
	//
	forwardEventList.push_back(
		{
			.eventType = ForwardEvent::EVENTTYPE_CHANGE,
			.nodeId = node->getId(),
			.mouseX = -1,
			.mouseY = -1,
			.type = -1
		}
	);
}

void GUIScreenNode::addMouseOverListener(GUIMouseOverListener* listener)
{
	removeMouseOverListener(listener);
	mouseOverListener.push_back(listener);
}

void GUIScreenNode::removeMouseOverListener(GUIMouseOverListener* listener)
{
	mouseOverListener.erase(std::remove(mouseOverListener.begin(), mouseOverListener.end(), listener), mouseOverListener.end());
}

void GUIScreenNode::forwardMouseOver(GUIElementNode* node)
{
	forwardEventList.push_back(
		{
			.eventType = ForwardEvent::EVENTTYPE_MOUSEOVER,
			.nodeId = node->getId(),
			.mouseX = -1,
			.mouseY = -1,
			.type = -1
		}
	);
}

void GUIScreenNode::addContextMenuRequestListener(GUIContextMenuRequestListener* listener) {
	removeContextMenuRequestListener(listener);
	contextMenuRequestListener.push_back(listener);
}

void GUIScreenNode::removeContextMenuRequestListener(GUIContextMenuRequestListener* listener) {
	contextMenuRequestListener.erase(std::remove(contextMenuRequestListener.begin(), contextMenuRequestListener.end(), listener), contextMenuRequestListener.end());
}

void GUIScreenNode::forwardContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
	forwardEventList.push_back(
		{
			.eventType = ForwardEvent::EVENTTYPE_CONTEXTMENUREQUEST,
			.nodeId = node->getId(),
			.mouseX = mouseX,
			.mouseY = mouseY,
			.type = -1
		}
	);
}

void GUIScreenNode::addFocusListener(GUIFocusListener* listener)
{
	removeFocusListener(listener);
	focusListener.push_back(listener);
}

void GUIScreenNode::removeFocusListener(GUIFocusListener* listener)
{
	focusListener.erase(std::remove(focusListener.begin(), focusListener.end(), listener), focusListener.end());
}

void GUIScreenNode::forwardFocus(GUIElementNode* node) {
	forwardEventList.push_back(
		{
			.eventType = ForwardEvent::EVENTTYPE_FOCUS,
			.nodeId = node->getId(),
			.mouseX = -1,
			.mouseY = -1,
			.type = -1
		}
	);
}

void GUIScreenNode::forwardUnfocus(GUIElementNode* node) {
	forwardEventList.push_back(
		{
			.eventType = ForwardEvent::EVENTTYPE_UNFOCUS,
			.nodeId = node->getId(),
			.mouseX = -1,
			.mouseY = -1,
			.type = -1
		}
	);
}

void GUIScreenNode::addMoveListener(GUIMoveListener* listener) {
	removeMoveListener(listener);
	moveListener.push_back(listener);
}

void GUIScreenNode::removeMoveListener(GUIMoveListener* listener) {
	moveListener.erase(std::remove(moveListener.begin(), moveListener.end(), listener), moveListener.end());
}

void GUIScreenNode::forwardMove(GUINode* node) {
	forwardEventList.push_back(
		{
			.eventType = ForwardEvent::EVENTTYPE_MOVE,
			.nodeId = node->getId(),
			.mouseX = -1,
			.mouseY = -1,
			.type = -1
		}
	);
}

void GUIScreenNode::forwardMoveRelease(GUINode* node, int mouseX, int mouseY) {
	forwardEventList.push_back(
		{
			.eventType = ForwardEvent::EVENTTYPE_MOVERELEASE,
			.nodeId = node->getId(),
			.mouseX = mouseX,
			.mouseY = mouseY,
			.type = -1
		}
	);
}

void GUIScreenNode::addTooltipRequestListener(GUITooltipRequestListener* listener) {
	removeTooltipRequestListener(listener);
	tooltipRequestListener.push_back(listener);
}

void GUIScreenNode::removeTooltipRequestListener(GUITooltipRequestListener* listener) {
	tooltipRequestListener.erase(std::remove(tooltipRequestListener.begin(), tooltipRequestListener.end(), listener), tooltipRequestListener.end());
}

void GUIScreenNode::forwardTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	forwardEventList.push_back(
		{
			.eventType = ForwardEvent::EVENTTYPE_TOOLTIPSHOWREQUEST,
			.nodeId = node->getId(),
			.mouseX = mouseX,
			.mouseY = mouseY,
			.type = -1
		}
	);
}

void GUIScreenNode::forwardTooltipCloseRequest() {
	forwardEventList.push_back(
		{
			.eventType = ForwardEvent::EVENTTYPE_TOOLTIPCLOSEREQUEST,
			.nodeId = string(),
			.mouseX = -1,
			.mouseY = -1,
			.type = -1
		}
	);
}

void GUIScreenNode::addDragRequestListener(GUIDragRequestListener* listener) {
	removeDragRequestListener(listener);
	dragRequestListener.push_back(listener);
}

void GUIScreenNode::removeDragRequestListener(GUIDragRequestListener* listener) {
	dragRequestListener.erase(std::remove(dragRequestListener.begin(), dragRequestListener.end(), listener), dragRequestListener.end());
}

void GUIScreenNode::forwardDragRequest(GUIElementNode* node, int mouseX, int mouseY) {
	forwardEventList.push_back(
		{
			.eventType = ForwardEvent::EVENTTYPE_DRAGREQUEST,
			.nodeId = node->getId(),
			.mouseX = mouseX,
			.mouseY = mouseY,
			.type = -1
		}
	);
}

void GUIScreenNode::tick() {
	auto now = Time::getCurrentMillis();
	vector<int64_t> timedExpressionsToRemove;
	for (auto& timedExpressionIt: timedExpressions) {
		if (now >= timedExpressionIt.first) {
			timedExpressionsToRemove.push_back(timedExpressionIt.first);
			GUIElementNode::executeExpression(this, timedExpressionIt.second);
		}
	}
	for (auto& timedExpressionToRemove: timedExpressionsToRemove) {
		timedExpressions.erase(timedExpressionToRemove);
	}
	auto _tickNodesById = tickNodesById;
	for (auto tickNodesByIdIt: _tickNodesById) {
		auto node = tickNodesByIdIt.second;
		if (node->controller != nullptr) node->controller->tick();
	}
	//
	if (scriptOnTickAvailable == true) {
		vector<MiniScript::ScriptVariable> argumentValues(0);
		span argumentValuesSpan(argumentValues);
		MiniScript::ScriptVariable returnValue;
		script->call("onTick", argumentValuesSpan, returnValue);
	}
}

void GUIScreenNode::getValues(unordered_map<string, MutableString>& values)
{
	values.clear();
	getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		if (dynamic_cast<GUIElementNode*>(childControllerNode) != nullptr == false)
			continue;

		auto guiElementNode = required_dynamic_cast<GUIElementNode*>(childControllerNode);
		auto guiElementNodeController = guiElementNode->getController();
		if (guiElementNodeController->hasValue()) {
			auto& name = guiElementNode->getName();
			auto& value = guiElementNodeController->getValue();
			auto currentValueIt = values.find(name);
			if (currentValueIt == values.end() || currentValueIt->second.size() == 0) {
				values[name] = value;
			}
		}
	}
}

void GUIScreenNode::setValues(const unordered_map<string, MutableString>& values)
{
	getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		if (dynamic_cast<GUIElementNode*>(childControllerNode) != nullptr == false)
			continue;

		auto guiElementNode = required_dynamic_cast<GUIElementNode*>(childControllerNode);
		auto guiElementNodeController = guiElementNode->getController();
		if (guiElementNodeController->hasValue()) {
			auto name = guiElementNode->getName();
			auto newValueIt = values.find(name);
			if (newValueIt == values.end())
				continue;
			guiElementNodeController->setValue(newValueIt->second);
		}
	}
}

GUIScreenNode_SizeConstraints GUIScreenNode::createSizeConstraints(const string& minWidth, const string& minHeight, const string& maxWidth, const string& maxHeight)
{
	GUIScreenNode_SizeConstraints constraints;
	constraints.minWidth = minWidth.empty() == true?-1:Integer::parse(minWidth);
	constraints.minHeight = minHeight.empty() == true?-1:Integer::parse(minHeight);
	constraints.maxWidth = maxWidth.empty() == true?-1:Integer::parse(maxWidth);
	constraints.maxHeight = maxHeight.empty() == true?-1:Integer::parse(maxHeight);
	return constraints;
}

GUIFont* GUIScreenNode::getFont(const string& applicationRootPath, const string& fileName, int size)
{
	// get canonical file name
	string canonicalFile;
	string path;
	string file;
	GUIFont* font = nullptr;
	try {
		if (FileSystem::getInstance()->fileExists(fileName) == true) {
			canonicalFile = fileName;
		} else {
			canonicalFile = FileSystem::getInstance()->getCanonicalPath(applicationRootPath, fileName);
		}
		path = FileSystem::getInstance()->getPathName(canonicalFile);
		file = FileSystem::getInstance()->getFileName(canonicalFile);
	} catch (Exception& exception) {
		Console::print(string("GUI::getFont(): An error occurred: "));
		Console::println(string(exception.what()));
		return nullptr;
	}

	// use cache or load font
	auto cacheId = canonicalFile + ":" + to_string(size);
	auto fontCacheIt = fontCache.find(cacheId);
	if (fontCacheIt == fontCache.end()) {
		try {
			font = GUIFont::parse(path, file, size);
		} catch (Exception& exception) {
			Console::print(string("GUIScreenNode::getFont(): An error occurred: "));
			Console::println(string(exception.what()));
			return nullptr;
		}
		fontCache[cacheId] = font;
	} else {
		font = fontCacheIt->second;
	}
	return font;
}

Texture* GUIScreenNode::getImage(const string& applicationRootPath, const string& fileName)
{
	// get canonical file name
	string canonicalFile;
	string path;
	string file;
	try {
		if (FileSystem::getInstance()->fileExists(fileName) == true) {
			canonicalFile = fileName;
		} else {
			canonicalFile = FileSystem::getInstance()->getCanonicalPath(applicationRootPath, fileName);
		}
		path = FileSystem::getInstance()->getPathName(canonicalFile);
		file = FileSystem::getInstance()->getFileName(canonicalFile);
	} catch (Exception& exception) {
		Console::print(string("GUIScreenNode::getImage(): An error occurred: "));
		Console::println(string(exception.what()));
		return nullptr;
	}

	//
	auto imageIt = imageCache.find("tdme.gui." + screenNode->getId() + "." + canonicalFile);
	auto image = imageIt != imageCache.end()?imageIt->second:nullptr;
	if (image == nullptr) {
		try {
			image = TextureReader::read(path, file, false, false, "tdme.gui." + screenNode->getId() + ".");
			if (image != nullptr) {
				image->setUseCompression(false);
				image->setUseMipMap(false);
				image->setRepeat(false);
				image->setClampMode(Texture::CLAMPMODE_TRANSPARENTPIXEL);
			}
		} catch (Exception& exception) {
			Console::print(string("GUIScreenNode::getImage(): An error occurred: "));
			Console::println(string(exception.what()));
			throw;
		}
		if (image != nullptr) imageCache[canonicalFile] = image;
	}
	return image;
}

void GUIScreenNode::forwardEvents() {
	auto forwardEventCount = 0;
	while (forwardEventList.empty() == false && forwardEventCount++ < 10) {
		auto forwardEventListCopy = forwardEventList;
		forwardEventList.clear();
		for (auto& event: forwardEventListCopy) {
			switch(event.eventType) {
				case ForwardEvent::EVENTTYPE_ACTION:
					{
						for (auto i = 0; i < actionListener.size(); i++) {
							auto elementNode = dynamic_cast<GUIElementNode*>(getNodeById(event.nodeId));
							if (elementNode == nullptr) break;
							actionListener[i]->onAction(static_cast<GUIActionListenerType>(event.type), elementNode);
						}
					}
					//
					if (scriptOnActionAvailable == true) {
						vector<MiniScript::ScriptVariable> argumentValues {
							static_cast<int64_t>(event.type),
							event.nodeId
						};
						span argumentValuesSpan(argumentValues);
						MiniScript::ScriptVariable returnValue;
						script->call("onAction", argumentValuesSpan, returnValue);
					}
					//
					break;
				case ForwardEvent::EVENTTYPE_CHANGE:
					{
						for (auto i = 0; i < changeListener.size(); i++) {
							auto elementNode = dynamic_cast<GUIElementNode*>(getNodeById(event.nodeId));
							if (elementNode == nullptr) break;
							changeListener[i]->onChange(elementNode);
						}
					}
					//
					if (scriptOnChangeAvailable == true) {
						vector<MiniScript::ScriptVariable> argumentValues {
							event.nodeId
						};
						span argumentValuesSpan(argumentValues);
						MiniScript::ScriptVariable returnValue;
						script->call("onChange", argumentValuesSpan, returnValue);
					}
					//
					break;
				case ForwardEvent::EVENTTYPE_MOUSEOVER:
					{
						for (auto i = 0; i < mouseOverListener.size(); i++) {
							auto elementNode = dynamic_cast<GUIElementNode*>(getNodeById(event.nodeId));
							if (elementNode == nullptr) break;
							mouseOverListener[i]->onMouseOver(elementNode);
						}
					}
					//
					if (scriptOnMouseOverAvailable == true) {
						vector<MiniScript::ScriptVariable> argumentValues {
							event.nodeId
						};
						span argumentValuesSpan(argumentValues);
						MiniScript::ScriptVariable returnValue;
						script->call("onMouseOver", argumentValuesSpan, returnValue);
					}
					//
					break;
				case ForwardEvent::EVENTTYPE_CONTEXTMENUREQUEST:
					{
						for (auto i = 0; i < contextMenuRequestListener.size(); i++) {
							auto elementNode = dynamic_cast<GUIElementNode*>(getNodeById(event.nodeId));
							if (elementNode == nullptr) break;
							contextMenuRequestListener[i]->onContextMenuRequest(elementNode, event.mouseX, event.mouseY);
						}
					}
					//
					if (scriptOnContextMenuRequestAvailable == true) {
						vector<MiniScript::ScriptVariable> argumentValues {
							event.nodeId,
							static_cast<int64_t>(event.mouseX),
							static_cast<int64_t>(event.mouseY)
						};
						span argumentValuesSpan(argumentValues);
						MiniScript::ScriptVariable returnValue;
						script->call("onContextMenuRequest", argumentValuesSpan, returnValue);
					}
					//
					break;
				case ForwardEvent::EVENTTYPE_FOCUS:
					{
						for (auto i = 0; i < focusListener.size(); i++) {
							auto elementNode = dynamic_cast<GUIElementNode*>(getNodeById(event.nodeId));
							if (elementNode == nullptr) break;
							focusListener[i]->onFocus(elementNode);
						}
					}
					//
					if (scriptOnFocusAvailable == true) {
						vector<MiniScript::ScriptVariable> argumentValues {
							event.nodeId
						};
						span argumentValuesSpan(argumentValues);
						MiniScript::ScriptVariable returnValue;
						script->call("onFocus", argumentValuesSpan, returnValue);
					}
					//
					break;
				case ForwardEvent::EVENTTYPE_UNFOCUS:
					{
						for (auto i = 0; i < focusListener.size(); i++) {
							auto elementNode = dynamic_cast<GUIElementNode*>(getNodeById(event.nodeId));
							if (elementNode == nullptr) break;
							focusListener[i]->onUnfocus(elementNode);
						}
					}
					//
					if (scriptOnUnfocusAvailable == true) {
						vector<MiniScript::ScriptVariable> argumentValues {
							event.nodeId
						};
						span argumentValuesSpan(argumentValues);
						MiniScript::ScriptVariable returnValue;
						script->call("onUnfocus", argumentValuesSpan, returnValue);
					}
					//
					break;
				case ForwardEvent::EVENTTYPE_MOVE:
					{
						for (auto i = 0; i < moveListener.size(); i++) {
							auto node = getNodeById(event.nodeId);
							if (node == nullptr) break;
							moveListener[i]->onMove(node);
						}
					}
					//
					if (scriptOnMoveAvailable == true) {
						vector<MiniScript::ScriptVariable> argumentValues {
							event.nodeId
						};
						span argumentValuesSpan(argumentValues);
						MiniScript::ScriptVariable returnValue;
						script->call("onMove", argumentValuesSpan, returnValue);
					}
					//
					break;
				case ForwardEvent::EVENTTYPE_MOVERELEASE:
					{
						for (auto i = 0; i < moveListener.size(); i++) {
							auto node = getNodeById(event.nodeId);
							if (node == nullptr) break;
							moveListener[i]->onRelease(node, event.mouseX, event.mouseY);
						}
					}
					//
					if (scriptOnMoveReleaseAvailable == true) {
						vector<MiniScript::ScriptVariable> argumentValues {
							event.nodeId,
							static_cast<int64_t>(event.mouseX),
							static_cast<int64_t>(event.mouseY)
						};
						span argumentValuesSpan(argumentValues);
						MiniScript::ScriptVariable returnValue;
						script->call("onMoveRelease", argumentValuesSpan, returnValue);
					}
					//
					break;
				case ForwardEvent::EVENTTYPE_TOOLTIPSHOWREQUEST:
					{
						for (auto i = 0; i < tooltipRequestListener.size(); i++) {
							auto node = getNodeById(event.nodeId);
							if (node == nullptr) break;
							tooltipRequestListener[i]->onTooltipShowRequest(node, event.mouseX, event.mouseY);
						}
					}
					//
					if (scriptOnTooltipShowRequestAvailable == true) {
						vector<MiniScript::ScriptVariable> argumentValues {
							event.nodeId,
							static_cast<int64_t>(event.mouseX),
							static_cast<int64_t>(event.mouseY)
						};
						span argumentValuesSpan(argumentValues);
						MiniScript::ScriptVariable returnValue;
						script->call("onTooltipShowRequest", argumentValuesSpan, returnValue);
					}
					//
					break;
				case ForwardEvent::EVENTTYPE_TOOLTIPCLOSEREQUEST: {
					{
						for (auto i = 0; i < tooltipRequestListener.size(); i++) {
							tooltipRequestListener[i]->onTooltipCloseRequest();
						}
					}
					//
					if (scriptOnTooltipCloseRequestAvailable == true) {
						vector<MiniScript::ScriptVariable> argumentValues(0);
						span argumentValuesSpan(argumentValues);
						MiniScript::ScriptVariable returnValue;
						script->call("onTooltipCloseRequest", argumentValuesSpan, returnValue);
					}
					//
					break;
				}
				case ForwardEvent::EVENTTYPE_DRAGREQUEST:
					{
						for (auto i = 0; i < dragRequestListener.size(); i++) {
							auto elementNode = dynamic_cast<GUIElementNode*>(getNodeById(event.nodeId));
							if (elementNode == nullptr) break;
							dragRequestListener[i]->onDragRequest(elementNode, event.mouseX, event.mouseY);
						}
					}
					//
					if (scriptOnDragRequestAvailable == true) {
						vector<MiniScript::ScriptVariable> argumentValues {
							event.nodeId,
							static_cast<int64_t>(event.mouseX),
							static_cast<int64_t>(event.mouseY)
						};
						span argumentValuesSpan(argumentValues);
						MiniScript::ScriptVariable returnValue;
						script->call("onDragRequest", argumentValuesSpan, returnValue);
					}
					//
					break;
			}
		}
	}
}
