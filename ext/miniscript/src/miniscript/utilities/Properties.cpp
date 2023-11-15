#include <miniscript/utilities/Properties.h>

#include <map>
#include <string>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/FileSystem.h>
#include <miniscript/utilities/StringTools.h>

using std::map;
using std::string;
using std::vector;

using miniscript::utilities::Properties;

using miniscript::utilities::FileSystem;
using miniscript::utilities::StringTools;

void Properties::load(const string& pathName, const string& fileName)
{
	properties.clear();
	vector<string> lines;
	FileSystem::getContentAsStringArray(pathName, fileName, lines);
	for (auto i = 0; i < lines.size(); i++) {
		string line = StringTools::trim(lines[i]);
		if (line.length() == 0 || StringTools::startsWith(line, "#")) continue;
		auto separatorPos = line.find('=');
		if (separatorPos == -1) continue;
		string key = StringTools::substring(line, 0, separatorPos);
		string value = StringTools::substring(line, separatorPos + 1);
		properties[key] = value;
	}
}

void Properties::store(const string& pathName, const string& fileName) const {
	vector<string> result;
	int32_t idx = 0;
	for (const auto& [key, value]: properties) {
		result.push_back(key + "=" + value);
	}
	FileSystem::setContentFromStringArray(pathName, fileName, result);
}
