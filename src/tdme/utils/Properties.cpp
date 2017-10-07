#include <tdme/utils/Properties.h>

#include <map>
#include <vector>
#include <string>

#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/StringUtils.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::utils::Properties;

using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::StringUtils;


Properties::Properties()
{
}

const wstring& Properties::get(const wstring& key, const wstring& defaultValue)
{
	auto it = properties.find(key);
	if (it == properties.end()) return defaultValue;
	return it->second;
}

void Properties::put(const wstring& key, const wstring& value)
{
	properties[key] = value;
}

void Properties::load(const wstring& pathName, const wstring& fileName) throw (FileSystemException)
{
	properties.clear();
	vector<wstring> lines;
	FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, &lines);
	for (int i = 0; i < lines.size(); i++) {
		wstring line = StringUtils::trim(lines.at(i));
		if (line.length() == 0 || StringUtils::startsWith(line, L"#")) continue;
		int separatorPos = line.find(L'=');
		if (separatorPos == -1) continue;
		wstring key = StringUtils::substring(line, 0, separatorPos);
		wstring value = StringUtils::substring(line, 0, separatorPos);
		properties[key] = value;
	}
}

void Properties::store(const wstring& pathName, const wstring& fileName) throw (FileSystemException) {
	vector<wstring> result;
	int32_t idx = 0;
	for (auto it = properties.begin(); it != properties.end(); ++it) {
		wstring key = it->first;
		wstring value = it->second;
		result.push_back(key + L"=" + value);
	}
	FileSystem::getInstance()->setContentFromStringArray(pathName, fileName, &result);
}
