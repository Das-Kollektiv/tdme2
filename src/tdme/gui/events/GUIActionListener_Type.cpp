#include <tdme/gui/events/GUIActionListener_Type.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::gui::events::GUIActionListener_Type;
using tdme::utils::Enum;

GUIActionListener_Type::GUIActionListener_Type(const wstring& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUIActionListener_Type* tdme::gui::events::GUIActionListener_Type::PERFORMED = new GUIActionListener_Type(L"PERFORMED", 0);
GUIActionListener_Type* tdme::gui::events::GUIActionListener_Type::PERFORMING = new GUIActionListener_Type(L"PERFORMING", 1);

GUIActionListener_Type* GUIActionListener_Type::valueOf(const wstring& a0)
{
	if (PERFORMED->getName() == a0) return PERFORMED;
	if (PERFORMING->getName() == a0) return PERFORMING;
	// TODO: throw exception here maybe
	return nullptr;
}
