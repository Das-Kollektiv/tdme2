#include <tdme/gui/nodes/GUIVideoNode.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/PacketAudioStream.h>
#include <tdme/engine/DynamicColorTexture.h>
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
#include <tdme/utilities/Time.h>

using tdme::gui::nodes::GUIVideoNode;

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;

using tdme::audio::PacketAudioStream;
using tdme::engine::DynamicColorTexture;
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
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;
using tdme::utilities::Time;
using tdme::video::decoder::MPEG1Decoder;

GUIVideoNode::GUIVideoNode(
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
}

const string GUIVideoNode::getNodeType()
{
	return "video";
}

void GUIVideoNode::dispose()
{
	disposeVideo();
	GUITextureBaseNode::dispose();
}

const string& GUIVideoNode::getSource() {
	return source;
}

void GUIVideoNode::disposeVideo() {
	if (videoTexture != nullptr) {
		videoTexture->dispose();
		videoTexture = nullptr;
	}
	if (videoAudioBuffer != nullptr) {
		videoAudioBuffer = nullptr;
	}
}

void GUIVideoNode::setSource(const string& source) {
	disposeVideo();

	//
	this->source = source;

	// video
	videoDecoder.openFile(
		FileSystem::getInstance()->getPathName(source),
		FileSystem::getInstance()->getFileName(source)
	);
	videoTexture = make_unique<DynamicColorTexture>(videoDecoder.getVideoWidth(), videoDecoder.getVideoHeight());
	videoTexture->initialize();

	// audio
	videoAudioBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(32768));
	/*
	videoAudioStream = new PacketAudioStream("video");
	videoAudioStream->setParameters(videoDecoder.getAudioSampleRate(), videoDecoder.getAudioChannels(), 32768);
	// videoAudioStream->play();
	*/

	//
	timeLast = -1LL;

	//
	this->textureId = videoTexture->getColorTextureId();
	this->textureWidth = videoDecoder.getVideoWidth();
	this->textureHeight = videoDecoder.getVideoHeight();
}

void GUIVideoNode::onRenderTexture() {
	// time
	auto timeNow = Time::getCurrentMillis();
	auto timeDelta = timeLast == -1LL?0:timeNow - timeLast;

	// video
	videoDecoder.update(static_cast<float>(timeDelta) / 1000.0f);
	auto videoTextureData = videoTexture->getByteBuffer();
	videoTextureData->clear();
	if (videoDecoder.readVideoFromStream(videoTextureData) > 0) {
		videoTexture->update();
	}
	videoAudioBuffer->clear();
	if (videoDecoder.readAudioFromStream(videoAudioBuffer.get()) > 0) {
		// videoAudioStream->addPacket(videoAudioBuffer);
	}

	//
	timeLast = timeNow;
}
