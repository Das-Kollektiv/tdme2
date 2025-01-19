#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utilities/Enum.h>

using std::string;

using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::utilities::Enum;

/**
 * GUI node vertical alignment enum
 */
class tdme::gui::nodes::GUINode_AlignmentVertical final: public Enum
{
public:
	STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* NONE;
	STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* TOP;
	STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* CENTER;
	STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* BOTTOM;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	GUINode_AlignmentVertical(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @returns enum object
	 */
	static GUINode_AlignmentVertical* valueOf(const string& name);
};
