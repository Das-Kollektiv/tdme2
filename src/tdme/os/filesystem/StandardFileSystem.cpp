#include <tdme/os/filesystem/StandardFileSystem.h>

#if defined(_WIN32) && defined(_MSC_VER)
	#include <direct.h>
# else
	#include <unistd.h>
#endif

#include <algorithm>
#include <array>
#include <dirent.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/os/filesystem/FileNameFilter.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>

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

using tdme::os::filesystem::StandardFileSystem;

using tdme::os::filesystem::FileNameFilter;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;

StandardFileSystem::StandardFileSystem()
{
}

StandardFileSystem::~StandardFileSystem()
{
}

const string StandardFileSystem::getFileName(const string& pathName, const string& fileName) {
	return pathName + "/" + fileName;
}

void StandardFileSystem::list(const string& pathName, vector<string>& files, FileNameFilter* filter, bool addDrives)
{
	auto _pathName = pathName;
	if (StringTools::endsWith(pathName, "/") == false) _pathName+= "/";

	DIR* dir = nullptr;
	struct dirent* dirent = nullptr;
	if ((dir = opendir(_pathName.c_str())) == nullptr) {
		throw FileSystemException("Unable to list path(" + to_string(errno) + "): " + _pathName);
	}
	while ((dirent = readdir(dir)) != nullptr) {
		string fileName = dirent->d_name;
		if (fileName == ".") continue;
		try {
			if (filter != nullptr && filter->accept(pathName, fileName) == false) continue;
		} catch (Exception& exception) {
			Console::println("StandardFileSystem::list(): Filter::accept(): " + pathName + "/" + fileName + ": " + exception.what());
			continue;
		}
		files.push_back(fileName);
	}
	sort(files.begin(), files.end());

	#if defined(_WIN32)
		if (addDrives == true) {
			for (char drive = 'A'; drive <= 'Z'; drive++) {
				string fileName;
				fileName+= drive;
				fileName+= ":";
				try {
					if (fileExists(fileName + "/") == true) files.insert(files.begin() + (drive - 'C'), fileName);
				} catch (Exception& exception) {
					Console::println("StandardFileSystem::list(): fileExists(): " + pathName + "/" + fileName + ": " + exception.what());
				}
			}
		}
	#endif

	closedir(dir);
}

bool StandardFileSystem::isPath(const string& pathName) {
	struct stat s;
	if (stat(pathName.c_str(), &s) == 0) {
		return (s.st_mode & S_IFDIR) == S_IFDIR;
	} else {
		throw FileSystemException("Unable to check if path(" + to_string(errno) + "): " + pathName);
	}
}

bool StandardFileSystem::isDrive(const string& pathName) {
	return StringTools::regexMatch(pathName, "^[a-zA-Z]\\:[\\/\\\\]?$");
}

bool StandardFileSystem::fileExists(const string& fileName) {
	struct stat s;
	return stat(fileName.c_str(), &s) == 0;
}

bool StandardFileSystem::isExecutable(const string& pathName, const string& fileName) {
	struct stat s;
	if (stat((pathName + "/" + fileName).c_str(), &s) != 0) return false;
	return (s.st_mode & S_IXUSR) == S_IXUSR;
}

void StandardFileSystem::setExecutable(const string& pathName, const string& fileName) {
	#if !defined(_MSC_VER)
		struct stat s;
		if (stat((pathName + "/" + fileName).c_str(), &s) != 0) {
			throw FileSystemException("Unable to set file to executable(" + to_string(errno) + "): " + pathName + "/" + fileName);
		}
		auto newMode = s.st_mode;
		if ((s.st_mode & S_IRUSR) == S_IRUSR && (s.st_mode & S_IXUSR) == 0) newMode|= S_IXUSR;
		if ((s.st_mode & S_IRGRP) == S_IRGRP && (s.st_mode & S_IXGRP) == 0) newMode|= S_IXGRP;
		if ((s.st_mode & S_IROTH) == S_IROTH && (s.st_mode & S_IXOTH) == 0) newMode|= S_IXOTH;
		if (chmod((pathName + "/" + fileName).c_str(), newMode) < 0) {
			throw FileSystemException("Unable to set file to executable(" + to_string(errno) + "): " + pathName + "/" + fileName);
		}
	#endif
}

uint64_t StandardFileSystem::getFileSize(const string& pathName, const string& fileName) {
	ifstream ifs(getFileName(pathName, fileName).c_str(), ifstream::binary);
	if (ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	ifs.seekg( 0, ios::end );
	size_t size = ifs.tellg();
	ifs.close();
	return size;
}

const string StandardFileSystem::getContentAsString(const string& pathName, const string& fileName) {
	ifstream ifs(getFileName(pathName, fileName).c_str());
	if (ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	stringstream stringStream;
	stringStream << ifs.rdbuf();
	ifs.close();
	return (stringStream.str());
}

void StandardFileSystem::setContentFromString(const string& pathName, const string& fileName, const string& content) {
	ofstream ofs(getFileName(pathName, fileName).c_str());
	if (ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	ofs << (content);
	ofs.close();
	return;
}

void StandardFileSystem::getContent(const string& pathName, const string& fileName, vector<uint8_t>& content)
{
	ifstream ifs(getFileName(pathName, fileName).c_str(), ifstream::binary);
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
	ofstream ofs(getFileName(pathName, fileName).c_str(), ofstream::binary);
	if (ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	ofs.write((char*)content.data(), content.size());
	ofs.close();
}

void StandardFileSystem::getContentAsStringArray(const string& pathName, const string& fileName, vector<string>& content)
{
	ifstream ifs(getFileName(pathName, fileName).c_str());
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
	ofstream ofs(getFileName(pathName, fileName).c_str(), ofstream::binary);
	if(ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}

	for (auto i = 0; i < content.size(); i++) {
		ofs << (content.at(i)) << "\n";
	}

	ofs.close();
	return;
}

const string StandardFileSystem::getCanonicalPath(const string& pathName, const string& fileName) {
	string unixPathName = StringTools::replace(pathName, "\\", "/");
	string unixFileName = StringTools::replace(fileName, "\\", "/");

	auto pathString = getFileName(unixPathName, unixFileName);

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
			pathComponents[i] = "";
		} else
		if (pathComponent == "..") {
			pathComponents[i]= "";
			int j = i - 1;
			for (int pathComponentReplaced = 0; pathComponentReplaced < 1 && j >= 0; ) {
				if (pathComponents[j] != "") {
					pathComponents[j] = "";
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
		if (pathComponent == "") {
			// no op
		} else {
			canonicalPath = canonicalPath + (slash == true?"/":"") + pathComponent;
			slash = true;
		}
	}

	// add cwd if required
	auto canonicalPathString = canonicalPath;
	if (canonicalPathString.length() == 0 ||
		(StringTools::startsWith(canonicalPathString, "/") == false &&
		StringTools::regexMatch(canonicalPathString, "^[a-zA-Z]\\:.*$") == false)) {
		canonicalPathString = getCurrentWorkingPathName() + "/" + canonicalPathString;
	}

	//
	return canonicalPathString;
}

const string StandardFileSystem::getCurrentWorkingPathName() {
	char cwdBuffer[PATH_MAX + 1];
	char* cwdPtr = getcwd(cwdBuffer, sizeof(cwdBuffer));
	if (cwdPtr == nullptr) {
		throw FileSystemException("Unable to get current working path(" + to_string(errno) + ")");
	}
	auto cwd = string(cwdPtr);
	return StringTools::replace(cwd, "\\", "/");
}

void StandardFileSystem::changePath(const string& pathName) {
	if (chdir(pathName.c_str()) != 0) {
		throw FileSystemException("Unable to change path(" + to_string(errno) + "): " + pathName);
	}
}

const string StandardFileSystem::getPathName(const string& fileName) {
	auto unixFileName = StringTools::replace(fileName, '\\', '/');
	auto lastPathSeparator = StringTools::lastIndexOf(unixFileName, '/');
	if (lastPathSeparator == -1) return ".";
	return StringTools::substring(unixFileName, 0, lastPathSeparator);
}

const string StandardFileSystem::getFileName(const string& fileName) {
	auto unixFileName = StringTools::replace(fileName, '\\', '/');
	auto lastPathSeparator = StringTools::lastIndexOf(unixFileName, '/');
	if (lastPathSeparator == -1) return fileName;
	return StringTools::substring(unixFileName, lastPathSeparator + 1, unixFileName.length());
}

void StandardFileSystem::createPath(const string& pathName) {
	#if defined(_WIN32)
		int32_t status = mkdir(pathName.c_str());
	#else
		int32_t status = mkdir(pathName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	#endif
	if (status == -1) {
		throw FileSystemException("Unable to create path(" + to_string(errno) + "): " + pathName);
	}
}

void StandardFileSystem::removePath(const string& pathName, bool recursive) {
	if (recursive == true) {
		vector<string> files;
		list(pathName, files, nullptr);
		for (auto i = 0; i < files.size(); i++) {
			auto file = files[i];
			if (file == "." || file == "..") {
				continue;
			}
			auto completeFileName = getFileName(pathName, file);
			if (isPath(completeFileName)) {
				removePath(completeFileName, true);
			} else {
				removeFile(pathName, file);
			}
		}
	}
	Console::println(string("StandardFileSystem::removePath(): Removing ") + pathName);
	int32_t status = rmdir(pathName.c_str());
	if (status == -1) {
		throw FileSystemException("Unable to remove folder(" + to_string(errno) + "): " + pathName);
	}
}

void StandardFileSystem::removeFile(const string& pathName, const string& fileName) {
	Console::println(string("StandardFileSystem::removeFile(): Removing ") + getFileName(pathName, fileName));
	int32_t status = unlink(getFileName(pathName, fileName).c_str());
	if (status == -1) {
		throw FileSystemException("Unable to remove file(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
}

void StandardFileSystem::rename(const string& fileNameFrom, const string& fileNameTo) {
	Console::println("StandardFileSystem::rename(): Rename '" + fileNameFrom + "' -> '" + fileNameTo + "'");
	int32_t status = std::rename(fileNameFrom.c_str(), fileNameTo.c_str());
	if (status != 0) {
		throw FileSystemException("Unable to rename file(" + to_string(errno) + "): '" + fileNameFrom + "' -> '" + fileNameTo + "'");
	}
}

bool StandardFileSystem::getThumbnailAttachment(const string& pathName, const string& fileName, vector<uint8_t>& thumbnailAttachmentContent) {
	ifstream ifs(getFileName(pathName, fileName).c_str(), ifstream::binary);
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
