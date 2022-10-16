#include <tdme/gui/nodes/GUITextureNode.h>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/DynamicColorTexture.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_Clipping.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextureBaseNode.h>
#include <tdme/gui/GUI.h>

using tdme::gui::nodes::GUITextureNode;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Clipping;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextureBaseNode;
using tdme::gui::GUI;

GUITextureNode::GUITextureNode(
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
	Texture* texture,
	const RequestedDimensionConstraints& requestedDimensionConstraints,
	bool mirrorX,
	bool mirrorY,
	const GUIColor& effectColorMul,
	const GUIColor& effectColorAdd,
	const GUINode_Scale9Grid& scale9Grid,
	const GUINode_Clipping& clipping,
	const string& mask,
	float maskMaxValue):
	GUITextureBaseNode(
		screenNode,
		parentNode,
		id,
		flow,
		alignments,
		requestedConstraints,
		backgroundColor,
		backgroundImage,
		backgroundImageScale9Grid,
		backgroundImageEffectColorMul,
		backgroundImageEffectColorAdd,
		border,
		padding,
		showOn,
		hideOn,
		requestedDimensionConstraints,
		mirrorX,
		mirrorY,
		effectColorMul,
		effectColorAdd,
		scale9Grid,
		clipping,
		mask,
		maskMaxValue
	)
{
	this->setTexture(texture);
}

const string GUITextureNode::getNodeType()
{
	return "texture";
}

void GUITextureNode::dispose()
{
	if (texture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(texture->getId());
		texture->releaseReference();
		texture = nullptr;
	}
	GUITextureBaseNode::dispose();
}

Texture* GUITextureNode::getTexture() {
	return texture;
}

void GUITextureNode::setTexture(Texture* texture) {
	if (this->texture == texture) return;
	if (this->texture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(this->texture->getId());
		this->texture->releaseReference();
	}
	this->texture = texture;
	if (texture == nullptr) {
		textureId = 0;
		textureWidth = 0;
		textureHeight = 0;
		return;
	}
	texture->acquireReference();
	textureId = Engine::getInstance()->getTextureManager()->addTexture(texture, 0);
	textureWidth = texture->getWidth();
	textureHeight = texture->getHeight();
}

void GUITextureNode::setTexture(DynamicColorTexture* texture) {
	if (this->texture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(this->texture->getId());
		this->texture->releaseReference();
	}
	this->texture = nullptr;
	if (texture == nullptr) {
		textureId = 0;
		textureWidth = 0;
		textureHeight = 0;
		return;
	}
	textureId = texture->getColorTextureId();
	textureWidth = texture->getWidth();
	textureHeight = texture->getHeight();
}
