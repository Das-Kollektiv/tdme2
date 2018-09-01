#include <tdme/os/filesystem/StandardFileSystem.h>

#if defined(_WIN32) && defined(_MSC_VER)
	#include <direct.h>
# else
	#include <unistd.h>
#endif

#include <algorithm>
#include <limits.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/FilenameFilter.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/Console.h>

using std::getline;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::sort;
using std::string;
using std::stringstream;
using std::vector;
using std::to_string;

using tdme::os::filesystem::StandardFileSystem;
using tdme::utils::StringUtils;
using tdme::utils::StringTokenizer;
using tdme::utils::Console;

StandardFileSystem::StandardFileSystem()
{
}

const string StandardFileSystem::getFileName(const string& pathName, const string& fileName) throw (FileSystemException) {
	return pathName + "/" + fileName;
}

void StandardFileSystem::list(const string& pathName, vector<string>& files, FilenameFilter* filter) throw (FileSystemException)
{
	DIR *dir;
	struct dirent *dirent;
	if ((dir = opendir(pathName.c_str())) == NULL) {
		throw FileSystemException("Unable to list path(" + to_string(errno) + "): " + pathName);
	}
	while ((dirent = readdir(dir)) != NULL) {
		string fileName = (dirent->d_name);
		if (filter != nullptr && filter->accept(pathName, fileName) == false) continue;
		files.push_back(fileName);
	}
	sort(files.begin(), files.end());
	closedir(dir);
}

bool StandardFileSystem::isPath(const string& pathName) throw (FileSystemException) {
	struct stat s;
	if (stat(pathName.c_str(), &s) == 0) {
		return (s.st_mode & S_IFDIR) == S_IFDIR;
	} else {
		throw FileSystemException("Unable to check if path(" + to_string(errno) + "): " + pathName);
	}
}

bool StandardFileSystem::fileExists(const string& fileName) throw (FileSystemException) {
	struct stat s;
	return stat(fileName.c_str(), &s) == 0;
}

const string StandardFileSystem::getContentAsString(const string& pathName, const string& fileName) throw (FileSystemException) {
	ifstream ifs(getFileName(pathName, fileName).c_str());
	if (ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	stringstream stringStream;
	stringStream << ifs.rdbuf();
	ifs.close();
	return (stringStream.str());
}

void StandardFileSystem::setContentFromString(const string& pathName, const string& fileName, const string& content) throw (FileSystemException) {
	ofstream ofs(getFileName(pathName, fileName).c_str());
	if (ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	ofs << (content);
	ofs.close();
	return;
}

void StandardFileSystem::getContent(const string& pathName, const string& fileName, vector<uint8_t>& content) throw (FileSystemException)
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

void StandardFileSystem::setContent(const string& pathName, const string& fileName, const vector<uint8_t>& content) throw (FileSystemException) {
	ofstream ofs(getFileName(pathName, fileName).c_str(), ofstream::binary);
	if (ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	ofs.write((char*)content.data(), content.size());
	ofs.close();
}

void StandardFileSystem::getContentAsStringArray(const string& pathName, const string& fileName, vector<string>& content) throw (FileSystemException)
{
	ifstream ifs(getFileName(pathName, fileName).c_str());
	if(ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}

	string line;
	while (getline(ifs, line)) {
		content.push_back((line));
	}

	ifs.close();
}

void StandardFileSystem::setContentFromStringArray(const string& pathName, const string& fileName, const vector<string>& content) throw (FileSystemException)
{
	ofstream ofs(getFileName(pathName, fileName).c_str());
	if(ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}

	for (int i = 0; i < content.size(); i++) {
		ofs << (content.at(i)) << "\n";
	}

	ofs.close();
	return;
}

const string StandardFileSystem::getCanonicalPath(const string& pathName, const string& fileName) throw (FileSystemException) {
	string unixPathName = StringUtils::replace(pathName, "\\", "/");
	string unixFileName = StringUtils::replace(fileName, "\\", "/");

	auto pathString = getFileName(unixPathName, unixFileName);

	// separate into path components
	vector<string> pathComponents;
	StringTokenizer t;
	t.tokenize(pathString, "/");
	while (t.hasMoreTokens()) {
		pathComponents.push_back(t.nextToken());
	}

	// process path components
	for (int i = 0; i < pathComponents.size(); i++) {
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
	bool slash = StringUtils::startsWith(pathString, "/");
	for (int i = 0; i < pathComponents.size(); i++) {
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
		(StringUtils::startsWith(canonicalPathString, "/") == false &&
		StringUtils::matches(canonicalPathString, "^[A-Z]\\:.*$") == false)) {
		canonicalPathString = getCurrentWorkingPathName() + "/" + canonicalPathString;
	}

	//
	return canonicalPathString;
}

const string StandardFileSystem::getCurrentWorkingPathName() throw (FileSystemException) {
	// cwd
	char cwdBuffer[PATH_MAX + 1];
	char* cwdPtr = getcwd(cwdBuffer, sizeof(cwdBuffer));
	if (cwdPtr == nullptr) {
		throw FileSystemException("Unable to get current working path(" + to_string(errno) + ")");
	}
	return (cwdPtr);
}

const string StandardFileSystem::getPathName(const string& fileName) throw (FileSystemException) {
	string unixFileName = StringUtils::replace(fileName, L'\\', L'/');
	int32_t lastPathSeparator = StringUtils::lastIndexOf(unixFileName, L'/');
	if (lastPathSeparator == -1) return ".";
	return StringUtils::substring(unixFileName, 0, lastPathSeparator);
}

const string StandardFileSystem::getFileName(const string& fileName) throw (FileSystemException) {
	string unixFileName = StringUtils::replace(fileName, L'\\', L'/');
	int32_t lastPathSeparator = StringUtils::lastIndexOf(unixFileName, L'/');
	if (lastPathSeparator == -1) return fileName;
	return StringUtils::substring(unixFileName, lastPathSeparator + 1, unixFileName.length());
}

void StandardFileSystem::createPath(const string& pathName) throw (FileSystemException) {
	#if defined(_WIN32)
		int32_t status = mkdir(pathName.c_str());
	#else
		int32_t status = mkdir(pathName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	#endif
	if (status == -1) {
		throw FileSystemException("Unable to create path(" + to_string(errno) + "): " + pathName);
	}
}

void StandardFileSystem::removePath(const string& pathName) throw (FileSystemException) {
	vector<string> files;
	list(pathName, files, nullptr);
	for (int i = 0; i < files.size(); i++) {
		auto file = files[i];
		if (file == "." || file == "..") {
			continue;
		}
		auto completeFileName = getFileName(pathName, file);
		if (isPath(completeFileName)) {
			removePath(completeFileName);
		} else {
			removeFile(pathName, file);
		}
	}
	Console::println(string("StandardFileSystem::removePath(): Removing ") + pathName);
	int32_t status = rmdir(pathName.c_str());
	if (status == -1) {
		throw FileSystemException("Unable to delete folder(" + to_string(errno) + "): " + pathName);
	}
}

void StandardFileSystem::removeFile(const string& pathName, const string& fileName) throw (FileSystemException) {
	Console::println(string("StandardFileSystem::removeFile(): Removing ") + getFileName(pathName, fileName));
	int32_t status = unlink(getFileName(pathName, fileName).c_str());
	if (status == -1) {
		throw FileSystemException("Unable to delete file(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
}
