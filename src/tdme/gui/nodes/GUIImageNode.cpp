#include <tdme/gui/nodes/GUIImageNode.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_Clipping.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextureBaseNode.h>
#include <tdme/math/Math.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using tdme::gui::nodes::GUIImageNode;

using std::string;
using std::to_string;

using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::Engine;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Clipping;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextureBaseNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

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

const string GUIImageNode::getNodeType()
{
	return "image";
}

void GUIImageNode::dispose()
{
	if (texture != nullptr) Engine::getInstance()->getTextureManager()->removeTexture(texture->getId());
	GUITextureBaseNode::dispose();
}

const string& GUIImageNode::getSource() {
	return source;
}

void GUIImageNode::setSource(const string& source) {
	if (texture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(texture->getId());
		texture = nullptr;
	}
	this->source = source;
	if (source.empty() == false) {
		if (StringTools::endsWith(StringTools::toLowerCase(source), ".tm") == true) {
			try {
				vector<uint8_t> thumbnailPNGData;
				if (FileSystem::getInstance()->getThumbnailAttachment(
						FileSystem::getInstance()->getPathName(source),
						FileSystem::getInstance()->getFileName(source),
						thumbnailPNGData
					) == true) {
					//
					auto thumbnailTexture = TextureReader::readPNG("tdme.gui.guiimagenode." + to_string(thumbnailTextureIdx++), thumbnailPNGData, true);
					if (thumbnailTexture != nullptr) {
						thumbnailTexture->acquireReference();
						this->texture = thumbnailTexture;
					} else {
						this->source = "resources/engine/images/mesh.png";
					}
				} else {
					this->source = "resources/engine/images/mesh.png";
				}
			} catch (Exception& exception) {
				Console::println(string() + "GUIImageNode::setSource(): " + exception.what());
			}
		} else
		if (StringTools::endsWith(StringTools::toLowerCase(source), ".tmodel") == true) {
			try {
				vector<uint8_t> thumbnailPNGData;
				if (PrototypeReader::readThumbnail(
						FileSystem::getInstance()->getPathName(source),
						FileSystem::getInstance()->getFileName(source),
						thumbnailPNGData
					) == true) {
					//
					auto thumbnailTexture = TextureReader::readPNG("tdme.gui.guiimagenode." + to_string(thumbnailTextureIdx++), thumbnailPNGData, true);
					if (thumbnailTexture != nullptr) {
						thumbnailTexture->acquireReference();
						this->texture = thumbnailTexture;
					} else {
						this->source = "resources/engine/images/tdme.png";
					}
				} else {
					this->source = "resources/engine/images/tdme.png";
				}
			} catch (Exception& exception) {
				Console::println(string() + "GUIImageNode::setSource(): " + exception.what());
			}
		} else {
			this->texture = source.empty() == true?nullptr:screenNode->getImage(screenNode->getApplicationRootPathName(), source);
		}
	}
	this->textureId = texture == nullptr?0:Engine::getInstance()->getTextureManager()->addTexture(texture, 0);
	this->textureWidth = texture == nullptr?0:texture->getWidth();
	this->textureHeight = texture == nullptr?0:texture->getHeight();
}

void GUIImageNode::rotate(float rotation) {
	if (texture == nullptr) return;
	auto rotatedTexture = TextureReader::rotate(texture, rotation);
	if (rotatedTexture == nullptr) return;
	if (texture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(texture->getId());
		texture = nullptr;
	}
	this->texture = rotatedTexture;
	this->textureId = texture == nullptr?0:Engine::getInstance()->getTextureManager()->addTexture(texture, 0);
	this->textureWidth = texture == nullptr?0:texture->getWidth();
	this->textureHeight = texture == nullptr?0:texture->getHeight();
}
