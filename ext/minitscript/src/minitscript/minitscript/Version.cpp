#include <minitscript/minitscript/Version.h>

#include <string>

#include <minitscript/minitscript.h>

using std::string;

using minitscript::minitscript::Version;

string Version::getVersion() {
	return "0.9.34 PRE-BETA";
}

string Version::getCopyright() {
	return "Developed 2012-2024 by Andreas Drewke, Dominik Hepp, Kolja Gumpert, drewke.net, mindty.com. Please see the license @ https://github.com/andreasdr/minitscript/blob/master/LICENSE";
}
