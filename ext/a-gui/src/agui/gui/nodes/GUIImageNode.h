#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/fileio/fwd-agui.h>

#include <agui/gui/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUINode_Clipping.h>
#include <agui/gui/nodes/GUINode_Scale9Grid.h>
#include <agui/gui/nodes/GUITextureBaseNode.h>
#include <agui/gui/renderer/fwd-agui.h>

using std::string;

// namespaces
namespace agui {
namespace gui {
namespace nodes {
	using ::agui::gui::textures::GUITexture;
	using ::agui::gui::misc::GUIDynamicColorTexture;
	using ::agui::gui::misc::GUIRendererTexture;
}
}
}

/**
 * GUI image node
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUIImageNode final
	: public GUITextureBaseNode
{
	friend class agui::gui::GUIParser;

private:
	bool releaseTextureReference { false };
	string source;
	GUITexture* texture { nullptr };
	AGUI_STATIC_DLL_IMPEXT static int thumbnailTextureIdx;

	/**
	 * Release texture
	 */
	void disposeTexture();

protected:
	// forbid class copy
	FORBID_CLASS_COPY(GUIImageNode)

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
	 * @param rotation rotation
	 * @throws agui::gui::GUIParserException
	 */
	GUIImageNode(
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
		float rotation
	);

	/**
	 * @returns node type
	 */
	const string getNodeType() override;

public:
	// overridden methods
	void dispose() override;


	/**
	 * @returns texture
	 */
	inline GUITexture* getTexture() {
		return texture;
	}

	/**
	 * @returns image source
	 */
	const string& getSource();

	/**
	 * Set image source
	 * @param source source
	 */
	void setSource(const string& source);

	/**
	 * Set texture
	 * @param texture texture
	 */
	void setTexture(GUITexture* texture);

	/**
	 * Set texture
	 * @param texture texture
	 */
	void setTexture(GUIDynamicColorTexture* texture);

	/**
	 * Set renderer texture
	 * @param texture texture
	 */
	void setTexture(GUIRendererTexture* texture);

	/**
	 * Rotate image around center
	 */
	void rotate(float rotation);

};
