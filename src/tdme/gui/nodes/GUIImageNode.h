#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_Clipping.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUITextureBaseNode.h>
#include <tdme/gui/renderer/fwd-tdme.h>

using std::string;

using tdme::engine::fileio::textures::Texture;
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

/**
 * GUI image node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIImageNode final
	: public GUITextureBaseNode
{
	friend class tdme::gui::GUIParser;

private:
	Texture* texture { nullptr };
	string source;

protected:
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
	 * @param source source
	 * @param effectColorMul effect color mul
	 * @param effectColorAdd effect color add
	 * @param scale9Grid scale 9 grid
	 * @param clipping clipping
	 * @param mask mask image
	 * @param maskMaxValue maximum value of mask to display image
	 * @throws tdme::gui::GUIParserException
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
		const string& source,
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

	/**
	 * @return texture
	 */
	inline Texture* getTexture() {
		return texture;
	}

};
