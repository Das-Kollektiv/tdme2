#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_Clipping.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUITextureBaseNode.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/video/decoder/MPEG1Decoder.h>

using std::string;

using tdme::audio::PacketAudioStream;
using tdme::engine::DynamicColorTexture;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Clipping;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextureBaseNode;
using tdme::utilities::ByteBuffer;
using tdme::video::decoder::MPEG1Decoder;

/**
 * GUI video node
 * @author Andreas Drewke
 */
class tdme::gui::nodes::GUIVideoNode final
	: public GUITextureBaseNode
{
	friend class tdme::gui::GUIParser;

private:
	string source;
	MPEG1Decoder videoDecoder;
	DynamicColorTexture* videoTexture { nullptr };
	ByteBuffer* videoAudioBuffer { nullptr };
	PacketAudioStream* videoAudioStream { nullptr };
	int64_t timeLast { -1LL };

protected:
	// forbid class copy
	CLASS_FORBID_COPY(GUIVideoNode)

	/**
	 * Constructor
	 * @param screenNode screen node
	 * @param parentNode parent node
	 * @param id id
	 * @param flow flow
	 * @param alignments alignments
	 * @param requestedConstraints requested constraints
	 * @param backgroundColor background color
	 * @param backgroundImage background image
	 * @param backgroundImageScale9Grid background image scale 9 grid
	 * @param backgroundImageEffectColorMul background image effect color mul
	 * @param backgroundImageEffectColorAdd background image effect color add
	 * @param border border
	 * @param padding padding
	 * @param showOn show on
	 * @param hideOn hide on
	 * @param tooltip tooltip
	 * @param source source
	 * @param requestedDimensionConstraints requested dimension constraints
	 * @param mirrorX mirror X
	 * @param mirrorY mirror Y
	 * @param effectColorMul effect color mul
	 * @param effectColorAdd effect color add
	 * @param scale9Grid scale 9 grid
	 * @param clipping clipping
	 * @param mask mask image
	 * @param maskMaxValue maximum value of mask to display image
	 * @throws tdme::gui::GUIParserException
	 */
	GUIVideoNode(
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
		float maskMaxValue
	);

	/**
	 * @return node type
	 */
	const string getNodeType() override;

	/**
	 * Dispose video related members
	 */
	void disposeVideo();

public:
	// overridden methods
	void dispose() override;

	/**
	 * @return image source
	 */
	const string& getSource();

	/**
	 * Set image source
	 * @param source source
	 */
	void setSource(const string& source);

	// overridden methods
	void onRenderTexture() override;
};
