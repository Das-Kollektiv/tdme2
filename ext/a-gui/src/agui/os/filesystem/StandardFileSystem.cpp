#include <agui/os/filesystem/StandardFileSystem.h>

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/os/filesystem/FileNameFilter.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/Exception.h>
#include <agui/utilities/StringTokenizer.h>
#include <agui/utilities/StringTools.h>

using std::array;
using std::getline;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::sort;
using std::string;
using std::stringstream;
using std::to_string;
using std::vector;

using agui::os::filesystem::StandardFileSystem;

using agui::os::filesystem::FileNameFilter;
using agui::utilities::Console;
using agui::utilities::Exception;
using agui::utilities::StringTokenizer;
using agui::utilities::StringTools;

StandardFileSystem::StandardFileSystem()
{
}

StandardFileSystem::~StandardFileSystem()
{
}

const string StandardFileSystem::composeURI(const string& pathName, const string& fileName) {
	return pathName + "/" + fileName;
}

void StandardFileSystem::list(const string& pathName, vector<string>& files, FileNameFilter* filter, bool addDrives)
{
	auto _pathName = pathName;
	if (StringTools::endsWith(_pathName, "/") == false) _pathName+= "/";

	try {
		for (const auto& entry: std::filesystem::directory_iterator(std::filesystem::u8path(_pathName))) {
			auto u8FileName = entry.path().filename().u8string();
			string fileName(u8FileName.size(), 0);
			for (auto i = 0; i < u8FileName.size(); i++) fileName[i] = u8FileName[i];
			try {
				if (filter != nullptr && filter->accept(pathName, fileName) == false) continue;
			} catch (Exception& exception) {
				Console::printLine("StandardFileSystem::list(): Filter::accept(): " + pathName + "/" + fileName + ": " + string(exception.what()));
				continue;
			}
			files.push_back(fileName);
		}
	} catch (Exception& exception) {
		throw FileSystemException("Unable to list path: " + pathName + ": " + string(exception.what()));
	}

	//
	sort(files.begin(), files.end());

	//
	if (isDrive(_pathName) == false && _pathName.empty() == false && _pathName != "/") {
		if (filter == nullptr || filter->accept(pathName, "..") == true) files.insert(files.begin(), "..");
	}

	#if defined(_WIN32)
		if (addDrives == true) {
			for (char drive = 'A'; drive <= 'Z'; drive++) {
				string fileName;
				fileName+= drive;
				fileName+= ":";
				try {
					if (exists(fileName + "/") == true) files.insert(files.begin() + (drive - 'C'), fileName);
				} catch (Exception& exception) {
					Console::printLine("StandardFileSystem::list(): fileExists(): " + pathName + "/" + fileName + ": " + string(exception.what()));
				}
			}
		}
	#endif
}

bool StandardFileSystem::isPath(const string& pathName) {
	try {
		auto status = std::filesystem::status(std::filesystem::u8path(pathName));
		return std::filesystem::is_directory(status);
	} catch (Exception& exception) {
		throw FileSystemException("Unable to check if path: " + pathName + ": " + string(exception.what()));
	}
	//
	return false;
}

bool StandardFileSystem::isDrive(const string& pathName) {
	return StringTools::regexMatch(pathName, "^[a-zA-Z]{1}\\:.*$");
}

bool StandardFileSystem::exists(const string& uri) {
	try {
		return std::filesystem::exists(std::filesystem::u8path(uri));
	} catch (Exception& exception) {
		throw FileSystemException("Unable to check if file exists: " + uri + ": " + string(exception.what()));
	}
	//
	return false;
}

bool StandardFileSystem::isExecutable(const string& pathName, const string& fileName) {
	try {
		auto permissions = std::filesystem::status(std::filesystem::u8path(pathName + "/" + fileName)).permissions();
		return
			(permissions & std::filesystem::perms::owner_exec) == std::filesystem::perms::owner_exec ||
			(permissions & std::filesystem::perms::group_exec) == std::filesystem::perms::group_exec ||
			(permissions & std::filesystem::perms::others_exec) == std::filesystem::perms::others_exec;
	} catch (Exception& exception) {
		throw FileSystemException("Unable to determine permissions: " + pathName + "/" + fileName + ": " + string(exception.what()));
	}
	//
	return false;
}

void StandardFileSystem::setExecutable(const string& pathName, const string& fileName) {
	try {
		std::filesystem::permissions(
			std::filesystem::u8path(pathName + "/" + fileName),
			std::filesystem::perms::owner_exec,
			std::filesystem::perm_options::add
		);
	} catch (Exception& exception) {
		throw FileSystemException("Unable to set executable permissions: " + pathName + "/" + fileName + ": " + string(exception.what()));
	}
}

uint64_t StandardFileSystem::getFileSize(const string& pathName, const string& fileName) {
	try {
		return std::filesystem::file_size(std::filesystem::u8path(pathName + "/" + fileName));
	} catch (Exception& exception) {
		throw FileSystemException("Unable to determine file size: " + fileName + ": " + string(exception.what()));
	}
	//
	return false;
}

const string StandardFileSystem::getContentAsString(const string& pathName, const string& fileName) {
	ifstream ifs(std::filesystem::u8path(composeURI(pathName, fileName)));
	if (ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	stringstream stringStream;
	stringStream << ifs.rdbuf();
	ifs.close();
	return (stringStream.str());
}

void StandardFileSystem::setContentFromString(const string& pathName, const string& fileName, const string& content) {
	ofstream ofs(std::filesystem::u8path(composeURI(pathName, fileName)));
	if (ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	ofs << (content);
	ofs.close();
	return;
}

void StandardFileSystem::getContent(const string& pathName, const string& fileName, vector<uint8_t>& content)
{
	ifstream ifs(std::filesystem::u8path(composeURI(pathName, fileName)), ifstream::binary);
	if (ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	ifs.seekg( 0, ios::end );
	size_t size = ifs.tellg();
	content.resize(size);
	ifs.seekg(0, ios::beg);
	ifs.read((char*)content.data(), size);
	ifs.close();
}

void StandardFileSystem::setContent(const string& pathName, const string& fileName, const vector<uint8_t>& content) {
	ofstream ofs(std::filesystem::u8path(composeURI(pathName, fileName)), ofstream::binary);
	if (ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	ofs.write((char*)content.data(), content.size());
	ofs.close();
}

void StandardFileSystem::getContentAsStringArray(const string& pathName, const string& fileName, vector<string>& content)
{
	ifstream ifs(std::filesystem::u8path(composeURI(pathName, fileName)));
	if(ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}

	string line;
	while (getline(ifs, line)) {
		content.push_back(StringTools::replace(line, "\r", ""));
	}

	ifs.close();
}

void StandardFileSystem::setContentFromStringArray(const string& pathName, const string& fileName, const vector<string>& content)
{
	ofstream ofs(std::filesystem::u8path(composeURI(pathName, fileName)), ofstream::binary);
	if(ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}

	for (auto i = 0; i < content.size(); i++) {
		ofs << (content.at(i)) << "\n";
	}

	ofs.close();
	return;
}

const string StandardFileSystem::getCanonicalURI(const string& pathName, const string& fileName) {
	string unixPathName = StringTools::replace(pathName, "\\", "/");
	string unixFileName = StringTools::replace(fileName, "\\", "/");

	//
	auto pathString = composeURI(unixPathName, unixFileName);

	// separate into path components
	vector<string> pathComponents;
	StringTokenizer t;
	t.tokenize(pathString, "/");
	while (t.hasMoreTokens()) {
		pathComponents.push_back(t.nextToken());
	}

	// process path components
	for (auto i = 0; i < pathComponents.size(); i++) {
		auto pathComponent = pathComponents[i];
		if (pathComponent == ".") {
			pathComponents[i].clear();
		} else
		if (pathComponent == "..") {
			pathComponents[i].clear();
			int j = i - 1;
			for (int pathComponentReplaced = 0; pathComponentReplaced < 1 && j >= 0; ) {
				if (pathComponents[j].empty() == false) {
					pathComponents[j].clear();
					pathComponentReplaced++;
				}
				j--;
			}
		}
	}

	// process path components
	string canonicalPath = "";
	bool slash = StringTools::startsWith(pathString, "/");
	for (auto i = 0; i < pathComponents.size(); i++) {
		auto pathComponent = pathComponents[i];
		if (pathComponent.empty() == true) {
			// no op
		} else {
			canonicalPath = canonicalPath + (slash == true?"/":"") + pathComponent;
			slash = true;
		}
	}

	// add cwd if required
	auto canonicalPathString = canonicalPath.empty() == true?"/":canonicalPath;
	/*
	if (canonicalPathString.length() == 0 ||
		(StringTools::startsWith(canonicalPathString, "/") == false &&
		StringTools::regexMatch(canonicalPathString, "^[a-zA-Z]\\:.*$") == false)) {
		canonicalPathString = getCurrentWorkingPathName() + "/" + canonicalPathString;
	}
	*/

	//
	return canonicalPathString;
}

const string StandardFileSystem::getCurrentWorkingPathName() {
	try {
		auto u8Cwd = std::filesystem::current_path().u8string();
		string cwd(u8Cwd.size(), 0);
		for (auto i = 0; i < u8Cwd.size(); i++) cwd[i] = u8Cwd[i];
		return cwd;
	} catch (Exception& exception) {
		throw FileSystemException("Unable to get current path: " + string(exception.what()));
	}
	//
	return string(".");
}

void StandardFileSystem::changePath(const string& pathName) {
	try {
		return std::filesystem::current_path(std::filesystem::u8path(pathName));
	} catch (Exception& exception) {
		throw FileSystemException("Unable to change path: " + pathName + ": " + string(exception.what()));
	}
}

const string StandardFileSystem::getPathName(const string& uri) {
	auto unixFileName = StringTools::replace(uri, '\\', '/');
	auto lastPathSeparator = StringTools::lastIndexOf(unixFileName, '/');
	if (lastPathSeparator == -1) return ".";
	return StringTools::substring(unixFileName, 0, lastPathSeparator);
}

const string StandardFileSystem::getFileName(const string& uri) {
	auto unixFileName = StringTools::replace(uri, '\\', '/');
	auto lastPathSeparator = StringTools::lastIndexOf(unixFileName, '/');
	if (lastPathSeparator == -1) return uri;
	return StringTools::substring(unixFileName, lastPathSeparator + 1, unixFileName.length());
}

const string StandardFileSystem::removeFileExtension(const string& fileName) {
	auto idx = fileName.rfind('.');
	if (idx == string::npos) {
		return fileName;
	} else {
		return fileName.substr(0, idx);
	}
}

void StandardFileSystem::createPath(const string& pathName) {
	try {
		if (std::filesystem::create_directory(std::filesystem::u8path(pathName)) == false) {
			throw FileSystemException("Unable to create path: " + pathName);
		}
	} catch (Exception& exception) {
		throw FileSystemException("Unable to create path: " + pathName + ": " + string(exception.what()));
	}
}

void StandardFileSystem::removePath(const string& pathName, bool recursive) {
	try {
		if (recursive == false) {
			if (std::filesystem::remove(std::filesystem::u8path(pathName)) == false) {
				throw FileSystemException("Unable to remove path: " + pathName);
			}
		} else {
			if (std::filesystem::remove_all(std::filesystem::u8path(pathName)) == false) {
				throw FileSystemException("Unable to remove path recursively: " + pathName);
			}
		}
	} catch (Exception& exception) {
		throw FileSystemException("Unable to remove path: " + pathName + ": " + string(exception.what()));
	}
}

void StandardFileSystem::removeFile(const string& pathName, const string& fileName) {
	try {
		if (std::filesystem::remove(std::filesystem::u8path(composeURI(pathName, fileName))) == false) {
			throw FileSystemException("Unable to remove file: " + pathName + "/" + fileName);
		}
	} catch (Exception& exception) {
		throw FileSystemException("Unable to remove file: " + pathName + "/" + fileName + ": " + string(exception.what()));
	}
}

void StandardFileSystem::rename(const string& fileNameFrom, const string& fileNameTo) {
	try {
		std::filesystem::rename(std::filesystem::u8path(fileNameFrom), std::filesystem::u8path(fileNameTo));
	} catch (Exception& exception) {
		throw FileSystemException("Unable to rename file: " + fileNameFrom + " -> " + fileNameTo + ": " + string(exception.what()));
	}
}


bool StandardFileSystem::getThumbnailAttachment(const string& pathName, const string& fileName, vector<uint8_t>& thumbnailAttachmentContent) {
	ifstream ifs(std::filesystem::u8path(getCanonicalURI(pathName, fileName)), ifstream::binary);
	if (ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}

	// check size
	ifs.seekg( 0, ios::end );
	size_t size = ifs.tellg();
	if (size < 12) return false;

	array<uint8_t, 12> id;

	ifs.seekg(size - 12, ios::beg);
	ifs.read((char*)id.data(), 12);

	// attachment
	if (id[8] != 'A' || id[9] != 'T' || id[10] != 'M' || id[11] != 'T') {
		return false;
	}
	// thumbnail
	if (id[4] != 'T' || id[5] != 'M' || id[6] != 'B' || id[7] != 'N') {
		return false;
	}
	// attachment size
	int32_t attachmentSize =
		((static_cast<int32_t>(id[0]) & 0xFF) << 24) +
		((static_cast<int32_t>(id[1]) & 0xFF) << 16) +
		((static_cast<int32_t>(id[2]) & 0xFF) << 8) +
		((static_cast<int32_t>(id[3]) & 0xFF) << 0);

	// do read the attachment
	thumbnailAttachmentContent.resize(attachmentSize);
	ifs.seekg(size - 12 - attachmentSize, ios::beg);
	ifs.read((char*)thumbnailAttachmentContent.data(), attachmentSize);
	ifs.close();

	//
	return thumbnailAttachmentContent.empty() == false;
}

bool StandardFileSystem::getThumbnailAttachment(const vector<uint8_t>& content, vector<uint8_t>& thumbnailAttachmentContent) {
	if (content.size() < 12) return false;

	array<uint8_t, 12> id;

	//
	for (auto i = 0; i < 12; i++) id[i] = content[content.size() - 12 + i];

	// attachment
	if (id[8] != 'A' || id[9] != 'T' || id[10] != 'M' || id[11] != 'T') {
		return false;
	}
	// thumbnail
	if (id[4] != 'T' || id[5] != 'M' || id[6] != 'B' || id[7] != 'N') {
		return false;
	}
	// attachment size
	int32_t attachmentSize =
		((static_cast<int32_t>(id[0]) & 0xFF) << 24) +
		((static_cast<int32_t>(id[1]) & 0xFF) << 16) +
		((static_cast<int32_t>(id[2]) & 0xFF) << 8) +
		((static_cast<int32_t>(id[3]) & 0xFF) << 0);

	// do read the attachment
	thumbnailAttachmentContent.resize(attachmentSize);
	for (auto i = 0; i < attachmentSize; i++) thumbnailAttachmentContent[i] = content[content.size() - 12 - attachmentSize + i];

	//
	return thumbnailAttachmentContent.empty() == false;
}
