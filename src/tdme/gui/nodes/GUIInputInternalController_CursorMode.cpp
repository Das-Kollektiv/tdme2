#include <tdme/gui/nodes/GUIInputInternalController_CursorMode.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::string;

using tdme::gui::nodes::GUIInputInternalController_CursorMode;
using tdme::utils::Enum;

GUIInputInternalController_CursorMode::GUIInputInternalController_CursorMode(const string& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUIInputInternalController_CursorMode* tdme::gui::nodes::GUIInputInternalController_CursorMode::SHOW = new GUIInputInternalController_CursorMode("SHOW", 0);
GUIInputInternalController_CursorMode* tdme::gui::nodes::GUIInputInternalController_CursorMode::HIDE = new GUIInputInternalController_CursorMode("HIDE", 1);

GUIInputInternalController_CursorMode* GUIInputInternalController_CursorMode::valueOf(const string& a0)
{
	if (HIDE->getName() == a0) return HIDE;
	if (SHOW->getName() == a0) return SHOW;
	// TODO: throw exception here maybe
	return nullptr;
}
