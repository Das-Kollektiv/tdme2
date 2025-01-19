#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utilities/Enum.h>

using std::string;

using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::utilities::Enum;

/**
 * GUI parent node overflow enum
 * @author Andreas Drewke
 */
class tdme::gui::nodes::GUIParentNode_Overflow final: public Enum
{
public:
	STATIC_DLL_IMPEXT static GUIParentNode_Overflow* HIDDEN;
	STATIC_DLL_IMPEXT static GUIParentNode_Overflow* DOWNSIZE_CHILDREN;
	STATIC_DLL_IMPEXT static GUIParentNode_Overflow* SCROLL;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	GUIParentNode_Overflow(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @returns enum object
	 */
	static GUIParentNode_Overflow* valueOf(const string& name);
};
