#include <tdme/engine/Version.h>

#include <string>

#include <tdme/tdme.h>

using std::string;

using tdme::engine::Version;

string Version::getVersion() {
	return "1.9.158";
}

string Version::getCopyright() {
	return "Developed 2012-2022 by Andreas Drewke, Dominik Hepp, Mathias Lenz, Kolja Gumpert, drewke.net, mindty.com, github.com/mahula. Please see the license @ https://github.com/andreasdr/tdme2/blob/master/LICENSE";
}
