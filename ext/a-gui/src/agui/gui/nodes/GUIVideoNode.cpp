#include <agui/gui/nodes/GUIVideoNode.h>

#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/audio/PacketAudioStream.h>
#include <agui/gui/misc/GUIDynamicColorTexture.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUINode_Border.h>
#include <agui/gui/nodes/GUINode_Clipping.h>
#include <agui/gui/nodes/GUINode_ComputedConstraints.h>
#include <agui/gui/nodes/GUINode_Padding.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <agui/gui/nodes/GUINode_Scale9Grid.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUITextureBaseNode.h>
#include <agui/math/Math.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemInterface.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/Exception.h>
#include <agui/utilities/StringTools.h>
#include <agui/utilities/Time.h>

using agui::gui::nodes::GUIVideoNode;

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;

using agui::audio::PacketAudioStream;
using agui::gui::misc::GUIDynamicColorTexture;
using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_Clipping;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using agui::gui::nodes::GUINode_Scale9Grid;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextureBaseNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemInterface;
using agui::utilities::ByteBuffer;
using agui::utilities::Console;
using agui::utilities::Exception;
using agui::utilities::StringTools;
using agui::utilities::Time;
using agui::video::decoder::MPEG1Decoder;

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
	videoTexture = make_unique<GUIDynamicColorTexture>(videoDecoder.getVideoWidth(), videoDecoder.getVideoHeight());
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
	this->textureId = videoTexture->getTextureId();
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
		videoAudioStream->addPacket(videoAudioBuffer.get());
	}

	//
	timeLast = timeNow;
}
