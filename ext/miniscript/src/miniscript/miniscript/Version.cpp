#include <miniscript/miniscript/Version.h>

#include <string>

#include <miniscript/miniscript.h>

using std::string;

using miniscript::miniscript::Version;

string Version::getVersion() {
	return "0.9.12 PRE-BETA";
}

string Version::getCopyright() {
	return "Developed 2012-2023 by Andreas Drewke, Dominik Hepp, Kolja Gumpert, drewke.net, mindty.com. Please see the license @ https://github.com/Mindty-Kollektiv/miniscript/blob/master/LICENSE";
}
