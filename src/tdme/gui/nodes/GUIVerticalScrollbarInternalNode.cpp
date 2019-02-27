#include <tdme/gui/nodes/GUIVerticalScrollbarInternalNode.h>

#include <array>
#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIVerticalScrollbarInternalController.h>
#include <tdme/gui/renderer/GUIRenderer.h>

using std::array;
using std::string;

using tdme::gui::nodes::GUIVerticalScrollbarInternalNode;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIVerticalScrollbarInternalController_State;
using tdme::gui::nodes::GUIVerticalScrollbarInternalController;
using tdme::gui::renderer::GUIRenderer;

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
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const GUIColor& barColorNone,
	const GUIColor& barColorMouseOver,
	const GUIColor& barColorDragging
):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, border, padding, showOn, hideOn)
{
	this->controller = new GUIVerticalScrollbarInternalController(this);
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

int32_t GUIVerticalScrollbarInternalNode::getContentWidth()
{
	return computedConstraints.width;
}

int32_t GUIVerticalScrollbarInternalNode::getContentHeight()
{
	return computedConstraints.height;
}

void GUIVerticalScrollbarInternalNode::render(GUIRenderer* guiRenderer)
{
	if (conditionsMet == false) return;

	GUINode::render(guiRenderer);
	auto screenWidth = screenNode->getScreenWidth();
	auto screenHeight = screenNode->getScreenHeight();
	auto controller = dynamic_cast< GUIVerticalScrollbarInternalController* >(this->controller);
	auto barHeight = controller->getBarHeight();
	auto barTop = controller->getBarTop();
	float left = computedConstraints.left + computedConstraints.alignmentLeft + border.left;
	auto top = barTop;
	float width = computedConstraints.width - border.left - border.right;
	auto height = barHeight;
	array<float, 4> barColorArray;
	{
		auto v = controller->getState();
		if (v == GUIVerticalScrollbarInternalController::STATE_NONE) {
			barColorArray = barColorNone.getArray();
		} else
		if (v == GUIVerticalScrollbarInternalController::STATE_MOUSEOVER) {
			barColorArray = barColorMouseOver.getArray();
		} else
		if (v == GUIVerticalScrollbarInternalController::STATE_DRAGGING) {
			barColorArray = barColorDragging.getArray();
		}
	}

	guiRenderer->bindTexture(0);
	guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, barColorArray[0], barColorArray[1], barColorArray[2], barColorArray[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, barColorArray[0], barColorArray[1], barColorArray[2], barColorArray[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, barColorArray[0], barColorArray[1], barColorArray[2], barColorArray[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, barColorArray[0], barColorArray[1], barColorArray[2], barColorArray[3], 0.0f, 0.0f);
	guiRenderer->render();
}

