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
	 * @returns version
	 */
	static string getVersion();

	/**
	 * @returns copyright
	 */
	static string getCopyright();

};
