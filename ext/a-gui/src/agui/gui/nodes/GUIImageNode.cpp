#include <agui/gui/nodes/GUIImageNode.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/fileio/PNGTextureReader.h>
#include <agui/gui/fileio/TextureReader.h>
#include <agui/gui/misc/GUIDynamicColorTexture.h>
#include <agui/gui/misc/GUIFrameBuffer.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/gui/textures/GUITextureManager.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUINode_Border.h>
#include <agui/gui/nodes/GUINode_Clipping.h>
#include <agui/gui/nodes/GUINode_ComputedConstraints.h>
#include <agui/gui/nodes/GUINode_Padding.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <agui/gui/nodes/GUINode_Scale9Grid.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUITextureBaseNode.h>
#include <agui/gui/GUI.h>
#include <agui/math/Math.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemInterface.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/Exception.h>
#include <agui/utilities/StringTools.h>

using agui::gui::nodes::GUIImageNode;

using std::string;
using std::to_string;

using agui::gui::textures::GUITexture;
using agui::gui::fileio::PNGTextureReader;
using agui::gui::fileio::TextureReader;
using agui::gui::misc::GUIDynamicColorTexture;
using agui::gui::misc::GUIFrameBuffer;
using agui::gui::textures::GUITextureManager;
using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_Clipping;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using agui::gui::nodes::GUINode_Scale9Grid;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextureBaseNode;
using agui::gui::GUI;
using agui::math::Math;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemInterface;
using agui::utilities::Console;
using agui::utilities::Exception;
using agui::utilities::StringTools;

int GUIImageNode::thumbnailTextureIdx = 0;

GUIImageNode::GUIImageNode(
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
	const string& source,
	const RequestedDimensionConstraints& requestedDimensionConstraints,
	bool mirrorX,
	bool mirrorY,
	const GUIColor& effectColorMul,
	const GUIColor& effectColorAdd,
	const GUINode_Scale9Grid& scale9Grid,
	const GUINode_Clipping& clipping,
	const string& mask,
	float maskMaxValue,
	float rotation):
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
		tooltip,
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
	this->setSource(source);
	if (Math::abs(rotation) > Math::EPSILON) rotate(rotation);
}

void GUIImageNode::disposeTexture() {
	if (texture != nullptr) {
		GUI::getTextureManager()->removeTexture(texture->getId());
		if (releaseTextureReference == true) {
			texture->releaseReference();
		}
	}
	releaseTextureReference = false;
	source.clear();
	texture = nullptr;
	frameBuffer = nullptr;
}

const string GUIImageNode::getNodeType()
{
	return "image";
}

void GUIImageNode::dispose()
{
	disposeTexture();
	GUITextureBaseNode::dispose();
}

const string& GUIImageNode::getSource() {
	return source;
}

void GUIImageNode::setSource(const string& source) {
	disposeTexture();
	this->source = source;
	if (source.empty() == false) {
		// load it
		if (this->texture == nullptr) {
			this->texture = source.empty() == true?nullptr:screenNode->getImage(source);
			this->releaseTextureReference = false;
		}
	}
	this->textureId = texture == nullptr?0:GUI::getTextureManager()->addTexture(texture, 0);
	this->textureWidth = texture == nullptr?0:texture->getWidth();
	this->textureHeight = texture == nullptr?0:texture->getHeight();
}

void GUIImageNode::setTexture(GUITexture* texture) {
	if (this->texture == texture) return;
	disposeTexture();
	this->texture = texture;
	if (texture == nullptr) {
		textureId = 0;
		textureWidth = 0;
		textureHeight = 0;
		return;
	}
	texture->acquireReference();
	releaseTextureReference = true;
	textureId = GUI::getTextureManager()->addTexture(texture, 0);
	textureWidth = texture->getWidth();
	textureHeight = texture->getHeight();
}

void GUIImageNode::setTexture(GUIDynamicColorTexture* texture) {
	disposeTexture();
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
	releaseTextureReference = false;
}

void GUIImageNode::rotate(float rotation) {
	if (texture == nullptr) return;
	auto rotatedTexture = TextureReader::rotate(texture, rotation);
	if (rotatedTexture == nullptr) return;
	disposeTexture();
	this->texture = rotatedTexture;
	this->textureId = texture == nullptr?0:GUI::getTextureManager()->addTexture(texture, 0);
	this->textureWidth = texture == nullptr?0:texture->getWidth();
	this->textureHeight = texture == nullptr?0:texture->getHeight();
	releaseTextureReference = true;
}

GUIFrameBuffer* GUIImageNode::getFrameBuffer() {
	return frameBuffer;
}

void GUIImageNode::setFrameBuffer(GUIFrameBuffer* frameBuffer) {
	disposeTexture();
	if (frameBuffer == nullptr) {
		textureId = 0;
		textureWidth = 0;
		textureHeight = 0;
		return;
	}
	textureId = frameBuffer->getColorBufferTextureId();
	textureWidth = frameBuffer->getWidth();
	textureHeight = frameBuffer->getHeight();
}
