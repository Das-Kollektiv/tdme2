// Generated from /tdme/src/tdme/gui/nodes/GUIParentNode.java

#pragma once

#include <string>

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::utils::Enum;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIParentNode_Overflow;

class tdme::gui::nodes::GUIParentNode_Overflow final
	: public Enum
{
	friend class GUIParentNode;

public:
	static GUIParentNode_Overflow *HIDDEN;
	static GUIParentNode_Overflow *DOWNSIZE_CHILDREN;
	static GUIParentNode_Overflow *SCROLL;
	GUIParentNode_Overflow(const wstring& name, int ordinal);
	static GUIParentNode_Overflow* valueOf(const wstring& a0);
};
