#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/fwd-agui.h>

using std::string;

/**
 * Version
 * @author Andreas Drewke
 */
struct agui::gui::GUIVersion final
{
public:
	/**
	 * @return version
	 */
	static string getVersion();

	/**
	 * @return copyright
	 */
	static string getCopyright();

};
