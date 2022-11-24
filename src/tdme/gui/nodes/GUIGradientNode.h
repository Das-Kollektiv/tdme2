#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_Clipping.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>

using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode;
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
using tdme::gui::renderer::GUIRenderer;
using tdme::math::Matrix2D3x3;

/**
 * GUI gradient node
 * @author Andreas Drewke
 */
class tdme::gui::nodes::GUIGradientNode
	: public GUINode
{
	friend class tdme::gui::GUIParser;

public:
	struct Gradient {
		int count { 0 };
		array<GUIColor, 10> colors;
		array<float, 10> colorStarts;
		float rotationAngle { 0.0f };
	};

	/**
	 * Create gradient from string values
	 * @param colors colors
	 * @param rotation rotation
	 */
	static Gradient createGradient(const string& colors, const string& rotation);

private:
	GUIColor effectColorMul;
	GUIColor effectColorAdd;
	GUINode_Clipping clipping;
	Texture* maskTexture { nullptr };
	float maskMaxValue;
	int32_t maskTextureId { 0 };

	Matrix2D3x3 textureMatrix;
	string mask;

	Gradient gradient;
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
	 * @param tooltip tooltip
	 * @param effectColorMul effect color mul
	 * @param effectColorAdd effect color add
	 * @param clipping clipping
	 * @param mask mask image
	 * @param maskMaxValue maximum value of mask to display image
	 * @param gradient gradient
	 * @throws tdme::gui::GUIParserException
	 */
	GUIGradientNode(
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
		const GUIColor& effectColorMul,
		const GUIColor& effectColorAdd,
		const GUINode_Clipping& clipping,
		const string& mask,
		float maskMaxValue,
		const Gradient& gradient
	);

	/**
	 * @return node type
	 */
	const string getNodeType() override;
	bool isContentNode() override;

public:
	// overridden methods
	int getContentWidth() override;
	int getContentHeight() override;
	void dispose() override;
	void render(GUIRenderer* guiRenderer) override;

	/**
	 * Set texture matrix
	 * @param textureMatrix texture matrix
	 */
	void setTextureMatrix(const Matrix2D3x3& textureMatrix);

	/**
	 * @return effect color mul
	 */
	const GUIColor& getEffectColorMul();

	/**
	 * Set effect color mul
	 * @param effectColorMul effect color mul
	 */
	void setEffectColorMul(const GUIColor& effectColorMul);

	/**
	 * @return effect color add
	 */
	const GUIColor& getEffectColorAdd();

	/**
	 * Set effect color add
	 * @param effectColorAdd effect color add
	 */
	void setEffectColorAdd(const GUIColor& effectColorAdd);

	/**
	 * @return clipping
	 */
	GUINode_Clipping& getClipping();

	/**
	 * Create clipping
	 * @param allClipping all sides
	 * @param left left
	 * @param top top
	 * @param right right
	 * @param bottom bottom
	 */
	static GUINode_Clipping createClipping(const string& allClipping, const string& left, const string& top, const string& right, const string& bottom);

	/**
	 * @return mask source
	 */
	const string& getMask();

	/**
	 * Set mask source
	 * @param mask mask source
	 */
	void setMask(const string& mask);

	/**
	 * @return maximum value of mask to display image
	 */
	float getMaskMaxValue() {
		return maskMaxValue;
	}

	/**
	 * Set maximum value of mask to display image
	 * @param maskMinValue value of mask to display image
	 */
	void setMaskMaxValue(float maskMaxValue) {
		this->maskMaxValue = maskMaxValue;
	}

};
