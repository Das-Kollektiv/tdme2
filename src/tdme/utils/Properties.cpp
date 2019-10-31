#include <tdme/utils/Properties.h>

#include <map>
#include <vector>
#include <string>

#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/StringUtils.h>

using std::map;
using std::vector;
using std::string;

using tdme::utils::Properties;

using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::StringUtils;

Properties::Properties()
{
}

const string& Properties::get(const string& key, const string& defaultValue)
{
	auto it = properties.find(key);
	if (it == properties.end()) return defaultValue;
	return it->second;
}

void Properties::put(const string& key, const string& value)
{
	properties[key] = value;
}

void Properties::load(const string& pathName, const string& fileName, FileSystemInterface* fileSystem)
{
	properties.clear();
	vector<string> lines;
	if (fileSystem == nullptr) fileSystem = FileSystem::getInstance();
	fileSystem->getContentAsStringArray(pathName, fileName, lines);
	for (auto i = 0; i < lines.size(); i++) {
		string line = StringUtils::trim(lines[i]);
		if (line.length() == 0 || StringUtils::startsWith(line, "#")) continue;
		auto separatorPos = line.find(L'=');
		if (separatorPos == -1) continue;
		string key = StringUtils::substring(line, 0, separatorPos);
		string value = StringUtils::substring(line, separatorPos + 1);
		properties[key] = value;
	}
}

void Properties::store(const string& pathName, const string& fileName, FileSystemInterface* fileSystem) {
	vector<string> result;
	int32_t idx = 0;
	for (auto it = properties.begin(); it != properties.end(); ++it) {
		string key = it->first;
		string value = it->second;
		result.push_back(key + "=" + value);
	}
	if (fileSystem == nullptr) fileSystem = FileSystem::getInstance();
	fileSystem->setContentFromStringArray(pathName, fileName, result);
}
