#include <agui/utilities/Properties.h>

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include <agui/agui.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemInterface.h>
#include <agui/utilities/StringTools.h>

using std::sort;
using std::string;
using std::unordered_map;
using std::vector;

using agui::utilities::Properties;

using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemInterface;
using agui::utilities::StringTools;

void Properties::load(const string& pathName, const string& fileName, FileSystemInterface* fileSystem)
{
	properties.clear();
	vector<string> lines;
	if (fileSystem == nullptr) fileSystem = FileSystem::getInstance();
	fileSystem->getContentAsStringArray(pathName, fileName, lines);
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

void Properties::store(const string& pathName, const string& fileName, FileSystemInterface* fileSystem) const {
	vector<string> result;
	int32_t idx = 0;
	for (const auto& [key, value]: properties) {
		result.push_back(key + "=" + value);
	}
	sort(result.begin(), result.end());
	if (fileSystem == nullptr) fileSystem = FileSystem::getInstance();
	fileSystem->setContentFromStringArray(pathName, fileName, result);
}
