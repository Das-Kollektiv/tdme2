#include <agui/gui/GUIVersion.h>

#include <string>

#include <agui/agui.h>

using std::string;

using agui::gui::GUIVersion;

string GUIVersion::getVersion() {
	return "0.9.85";
}

string GUIVersion::getCopyright() {
	return "Developed 2012-2023 by Andreas Drewke, Dominik Hepp, Mathias Lenz, Kolja Gumpert, drewke.net, mindty.com, github.com/mahula. Please see the license @ https://github.com/andreasdr/a-gui/blob/master/LICENSE";
}
