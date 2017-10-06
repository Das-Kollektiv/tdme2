// Generated from /tdme/src/tdme/gui/nodes/GUILayoutNode.java

#pragma once

#include <string>

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::utils::Enum;
using tdme::gui::nodes::GUILayoutNode;
using tdme::gui::nodes::GUILayoutNode_Alignment;

class tdme::gui::nodes::GUILayoutNode_Alignment final
	: public Enum
{
	friend class GUILayoutNode;

public: /* package */
	static GUILayoutNode_Alignment *VERTICAL;
	static GUILayoutNode_Alignment *HORIZONTAL;
	static GUILayoutNode_Alignment *NONE;
	GUILayoutNode_Alignment(const wstring& name, int ordinal);
	static GUILayoutNode_Alignment* valueOf(const wstring& a0);
};
