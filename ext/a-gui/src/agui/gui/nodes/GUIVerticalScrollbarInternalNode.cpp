#include <agui/gui/nodes/GUIVerticalScrollbarInternalNode.h>

#include <array>
#include <string>

#include <agui/agui.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUINode_Border.h>
#include <agui/gui/nodes/GUINode_ComputedConstraints.h>
#include <agui/gui/nodes/GUINode_Scale9Grid.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUIVerticalScrollbarInternalController.h>
#include <agui/gui/renderer/GUIRenderer.h>
#include <agui/gui/GUI.h>

using std::array;
using std::string;

using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Scale9Grid;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUIVerticalScrollbarInternalController;
using agui::gui::nodes::GUIVerticalScrollbarInternalController_State;
using agui::gui::nodes::GUIVerticalScrollbarInternalNode;
using agui::gui::renderer::GUIRenderer;
using agui::gui::GUI;

GUIVerticalScrollbarInternalNode::GUIVerticalScrollbarInternalNode(
	GUIScreenNode* screenNode,
	GUIParentNode* parentNode,
	const string& id,
	GUINode_Flow* flow,
	const GUINode_Alignments& alignments,
	const GUINode_RequestedConstraints& requestedConstraints,
	const GUIColor& backgroundColor,
	const string& backgroundImage,
	const GUINode_Scale9Grid& backgroundImageScale9Grid,
	const GUIColor& backgroundImageEffectColorMul,
	const GUIColor& backgroundImageEffectColorAdd,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& tooltip,
	const GUIColor& barColorNone,
	const GUIColor& barColorMouseOver,
	const GUIColor& barColorDragging
):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn, tooltip)
{
	//
	auto controller = new GUIVerticalScrollbarInternalController(this);
	controller->initialize();
	setController(controller);
	//
	this->barColorNone = barColorNone;
	this->barColorMouseOver = barColorMouseOver;
	this->barColorDragging = barColorDragging;
}

const string GUIVerticalScrollbarInternalNode::getNodeType()
{
	return "scrollbar";
}

bool GUIVerticalScrollbarInternalNode::isContentNode()
{
	return false;
}

int GUIVerticalScrollbarInternalNode::getContentWidth()
{
	return computedConstraints.width;
}

int GUIVerticalScrollbarInternalNode::getContentHeight()
{
	return computedConstraints.height;
}

void GUIVerticalScrollbarInternalNode::render(GUIRenderer* guiRenderer)
{
	if (shouldRender() == false) return;

	GUINode::render(guiRenderer);
	auto screenWidth = screenNode->getScreenWidth();
	auto screenHeight = screenNode->getScreenHeight();
	auto controller = required_dynamic_cast<GUIVerticalScrollbarInternalController*>(this->getController());
	auto barHeight = controller->getBarHeight();
	auto barTop = controller->getBarTop();
	float left = computedConstraints.left + computedConstraints.alignmentLeft + border.left;
	auto top = barTop;
	float width = computedConstraints.width - border.left - border.right;
	auto height = barHeight;
	array<float, 4> barColorArray;
	{
		auto state = controller->getState();
		if (state == GUIVerticalScrollbarInternalController::STATE_NONE) {
			barColorArray = barColorNone.getArray();
		} else
		if (state == GUIVerticalScrollbarInternalController::STATE_MOUSEOVER) {
			barColorArray = barColorMouseOver.getArray();
		} else
		if (state == GUIVerticalScrollbarInternalController::STATE_DRAGGING) {
			barColorArray = barColorDragging.getArray();
		}
	}
	guiRenderer->bindTexture(0);
	guiRenderer->addQuad(
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		barColorArray[0],
		barColorArray[1],
		barColorArray[2],
		barColorArray[3],
		0.0f,
		1.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
		barColorArray[0],
		barColorArray[1],
		barColorArray[2],
		barColorArray[3],
		1.0f,
		1.0f,
		((left + width) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		barColorArray[0],
		barColorArray[1],
		barColorArray[2],
		barColorArray[3],
		1.0f, 0.0f,
		((left) / (screenWidth / 2.0f)) - 1.0f,
		((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
		barColorArray[0],
		barColorArray[1],
		barColorArray[2],
		barColorArray[3],
		0.0f,
		0.0f
	);
	guiRenderer->render();
}

