#include <tdme/engine/tools/FileSystemTools.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::engine::tools::FileSystemTools;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::utilities::StringTools;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Integer;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;

const string FileSystemTools::getRelativeResourcesFileName(const string& applicationRoot, const string& fileName)
{
	auto newFileName = StringTools::replace(fileName, '\\', '/');
	auto cutFileNameIdx = string::npos;
	if (cutFileNameIdx == string::npos) {
		cutFileNameIdx = fileName.rfind("/resources/");
		if (cutFileNameIdx != string::npos) {
			newFileName = StringTools::substring(fileName, cutFileNameIdx + 1);
		}
	}
	if (cutFileNameIdx == string::npos) {
		cutFileNameIdx = fileName.rfind("resources/");
		if (cutFileNameIdx != string::npos) {
			newFileName = StringTools::substring(fileName, cutFileNameIdx);
		}
	}
	return newFileName;
}

const string FileSystemTools::getApplicationRootPathName(const string& fileName)
{
	auto newFileName = StringTools::replace(fileName, '\\', '/');
	auto applicationRootPathNameIdx = string::npos;
	if (applicationRootPathNameIdx == string::npos) {
		applicationRootPathNameIdx = fileName.rfind("/resources/");
		if (applicationRootPathNameIdx != string::npos) return StringTools::substring(fileName, 0, applicationRootPathNameIdx);
	}
	if (StringTools::startsWith(fileName, "resources/") == true) {
		return "";
	}
	if (StringTools::endsWith(fileName, "/resources") == true) {
		return StringTools::substring(fileName, 0, fileName.size() - string("/resources").size());
	}
	return "";
}

const string FileSystemTools::getApplicationSubPathName(const string& fileName)
{
	auto newFileName = StringTools::replace(fileName, '\\', '/');
	auto applicationSubPathNameIdx = -1;
	if (applicationSubPathNameIdx == -1) {
		applicationSubPathNameIdx = fileName.rfind("/resources/");
		if (applicationSubPathNameIdx != -1) {
			applicationSubPathNameIdx+= string("/resources/").size();
			auto applicationSubPathName = StringTools::substring(fileName, applicationSubPathNameIdx,  fileName.find("/", applicationSubPathNameIdx));
			if (applicationSubPathName == "engine") return applicationSubPathName; else
			if (applicationSubPathName == "project") return applicationSubPathName; else
			if (applicationSubPathName == "installer") return applicationSubPathName; else
				return "engine";
		}
	}
	if (applicationSubPathNameIdx == -1) {
		applicationSubPathNameIdx = fileName.rfind("resources/");
		if (applicationSubPathNameIdx != -1) {
			applicationSubPathNameIdx+= string("resources/").size();
			auto applicationSubPathName = StringTools::substring(fileName, applicationSubPathNameIdx,  fileName.find("/", applicationSubPathNameIdx));
			if (applicationSubPathName == "engine") return applicationSubPathName; else
			if (applicationSubPathName == "project") return applicationSubPathName; else
			if (applicationSubPathName == "installer") return applicationSubPathName; else
				return "engine";
		}
	}
	return "engine";
}

const string FileSystemTools::getCanonicalURI(const string& pathName, const string& fileName)
{
	return FileSystem::getInstance()->getCanonicalURI(pathName, fileName);
}

const string FileSystemTools::getPathName(const string& fileName)
{
	return FileSystem::getInstance()->getPathName(fileName);
}

const string FileSystemTools::getFileName(const string& fileName)
{
	return FileSystem::getInstance()->getFileName(fileName);
}

const string FileSystemTools::removeFileExtension(const string& fileName)
{
	return FileSystem::getInstance()->removeFileExtension(fileName);
}

const string FileSystemTools::ensureFileExtension(const string& fileName, const string& extension)
{
	if (StringTools::endsWith(StringTools::toLowerCase(fileName), "." + extension) == true) {
		return fileName;
	} else {
		return removeFileExtension(fileName) + "." + extension;
	}
}

const string FileSystemTools::getFileExtension(const string& fileName)
{
	auto idx = fileName.rfind('.');
	if (idx == string::npos) {
		return string();
	} else {
		return fileName.substr(idx + 1);
	}
}

void FileSystemTools::loadSettings(Application* application) {
	Properties settings;

	// settings
	try {
		settings.load("settings", "settings.properties");
	} catch (FileSystemException &exception) {
		Console::printLine("FileSystemTools::loadSettings(): An error occurred: " + string(exception.what()));
	}

	// 4k
	if (settings.get("4k", "false") == "true") {
		Engine::set4K(true);
	}

	// Window
	application->setWindowWidth(Integer::parse(settings.get("window_width", "1024")));
	application->setWindowHeight(Integer::parse(settings.get("window_height", "768")));
	application->setWindowXPosition(Integer::parse(settings.get("window_x", "-1")));
	application->setWindowYPosition(Integer::parse(settings.get("window_y", "-1")));
	application->setFullScreen(settings.get("fullscreen", "false") == "true");
}

bool FileSystemTools::hasFileExtension(const string& fileName, const vector<string>& extensions) {
	auto fileNameLowerCase = StringTools::toLowerCase(fileName);
	for (const auto& extension: extensions) {
		if (StringTools::endsWith(fileNameLowerCase, "." + extension) == true) return true;
	}
	return false;
}
