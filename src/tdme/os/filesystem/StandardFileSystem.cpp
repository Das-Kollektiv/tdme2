#include <tdme/os/filesystem/StandardFileSystem.h>

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/FilenameFilter.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/Console.h>

using std::getline;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;
using std::to_string;

using tdme::os::filesystem::StandardFileSystem;
using tdme::utils::StringConverter;
using tdme::utils::StringUtils;
using tdme::utils::StringTokenizer;
using tdme::utils::Console;

StandardFileSystem::StandardFileSystem()
{
}

const wstring StandardFileSystem::getFileName(const wstring& pathName, const wstring& fileName) throw (FileSystemException) {
	return pathName + L"/" + fileName;
}

void StandardFileSystem::list(const wstring& pathName, vector<wstring>* files, FilenameFilter* filter) throw (FileSystemException)
{
	DIR *dir;
	struct dirent *dirent;
	if ((dir = opendir(StringConverter::toString(pathName).c_str())) == NULL) {
		throw FileSystemException("Unable to list path(" + to_string(errno) + ")");
	}
	while ((dirent = readdir(dir)) != NULL) {
		wstring fileName = StringConverter::toWideString(dirent->d_name);
		if (filter != nullptr && filter->accept(pathName, fileName) == false) continue;
		files->push_back(fileName);
	}
	closedir(dir);
}

bool StandardFileSystem::isPath(const wstring& pathName) throw (FileSystemException) {
	struct stat s;
	if (stat(StringConverter::toString(pathName).c_str(), &s) == 0) {
		return (s.st_mode & S_IFDIR) == S_IFDIR;
	} else {
		throw FileSystemException("Unable to check if path(" + to_string(errno) + ")");
	}
}

bool StandardFileSystem::fileExists(const wstring& fileName) throw (FileSystemException) {
	struct stat s;
	return stat(StringConverter::toString(fileName).c_str(), &s) == 0;
}

const wstring StandardFileSystem::getContentAsString(const wstring& pathName, const wstring& fileName) throw (FileSystemException) {
	ifstream ifs(StringConverter::toString(getFileName(pathName, fileName)).c_str());
	if (ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + ")");
	}
	stringstream stringStream;
	stringStream << ifs.rdbuf();
	ifs.close();
	return StringConverter::toWideString(stringStream.str());
}

void StandardFileSystem::setContentFromString(const wstring& pathName, const wstring& fileName, const wstring& content) throw (FileSystemException) {
	ofstream ofs(StringConverter::toString(getFileName(pathName, fileName)).c_str());
	if (ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + ")");
	}
	ofs << StringConverter::toString(content);
	ofs.close();
	return;
}

void StandardFileSystem::getContent(const wstring& pathName, const wstring& fileName, vector<uint8_t>* content) throw (FileSystemException)
{
	ifstream ifs(StringConverter::toString(getFileName(pathName, fileName)).c_str());
	if (ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + ")");
	}
	ifs.seekg( 0, ios::end );
	size_t size = ifs.tellg();
	content->resize(size);
	ifs.seekg(0, ios::beg);
	ifs.read((char*)content->data(), size);
	ifs.close();
}

void StandardFileSystem::setContent(const wstring& pathName, const wstring& fileName, vector<uint8_t>* content) throw (FileSystemException) {
	ofstream ofs(StringConverter::toString(getFileName(pathName, fileName)).c_str());
	if (ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + ")");
	}
	ofs.write((char*)content->data(), content->size());
	ofs.close();
}

void StandardFileSystem::getContentAsStringArray(const wstring& pathName, const wstring& fileName, vector<wstring>* content) throw (FileSystemException)
{
	ifstream ifs(StringConverter::toString(getFileName(pathName, fileName)).c_str());
	if(ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + ")");
	}

	string line;
	while (getline(ifs, line)) {
		content->push_back(StringConverter::toWideString(line));
	}

	ifs.close();
}

void StandardFileSystem::setContentFromStringArray(const wstring& pathName, const wstring& fileName, vector<wstring>* content) throw (FileSystemException)
{
	ofstream ofs(StringConverter::toString(getFileName(pathName, fileName)).c_str());
	if(ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + ")");
	}

	for (int i = 0; i < content->size(); i++) {
		ofs << StringConverter::toString(content->at(i)) << "\n";
	}

	ofs.close();
	return;
}

const wstring StandardFileSystem::getCanonicalPath(const wstring& pathName, const wstring& fileName) throw (FileSystemException) {
	wstring unixPathName = StringUtils::replace(pathName, L"\\", L"/");
	wstring unixFileName = StringUtils::replace(fileName, L"\\", L"/");

	auto pathString = getFileName(unixPathName, unixFileName);

	// separate into path components
	vector<wstring> pathComponents;
	StringTokenizer t;
	t.tokenize(pathString, L"/");
	while (t.hasMoreTokens()) {
		pathComponents.push_back(t.nextToken());
	}

	// process path components
	for (int i = 0; i < pathComponents.size(); i++) {
		auto pathComponent = pathComponents.at(i);
		if (pathComponent == L".") {
			pathComponents[i] = L"";
		} else
		if (pathComponent == L"..") {
			pathComponents[i]= L"";
			int j = i - 1;
			for (int pathComponentReplaced = 0; pathComponentReplaced < 1 && j >= 0; ) {
				if (pathComponents.at(j) != L"") {
					pathComponents[j] = L"";
					pathComponentReplaced++;
				}
				j--;
			}
		}
	}

	// process path components
	wstring canonicalPath = L"";
	bool slash = StringUtils::startsWith(pathString, L"/");
	for (int i = 0; i < pathComponents.size(); i++) {
		auto pathComponent = pathComponents.at(i);
		if (pathComponent == L"") {
			// no op
		} else {
			canonicalPath = canonicalPath + (slash == true?L"/":L"") + pathComponent;
			slash = true;
		}
	}

	// add cwd if required
	auto canonicalPathString = canonicalPath;
	if (canonicalPathString.length() == 0 ||
		StringUtils::startsWith(canonicalPathString, L"/") == false) {
		canonicalPathString = getCurrentWorkingPathName() + L"/" + canonicalPathString;
	}

	//
	return canonicalPathString;
}

const wstring StandardFileSystem::getCurrentWorkingPathName() throw (FileSystemException) {
	// cwd
	char cwdBuffer[PATH_MAX + 1];
	char* cwdPtr = getcwd(cwdBuffer, sizeof(cwdBuffer));
	if (cwdPtr == nullptr) {
		throw FileSystemException("Unable to get current working path(" + to_string(errno) + ")");
	}
	return StringConverter::toWideString(cwdPtr);
}

const wstring StandardFileSystem::getPathName(const wstring& fileName) throw (FileSystemException) {
	wstring unixFileName = StringUtils::replace(fileName, L'\\', L'/');
	int32_t lastPathSeparator = StringUtils::lastIndexOf(unixFileName, L'/');
	if (lastPathSeparator == -1) return L".";
	return StringUtils::substring(unixFileName, 0, lastPathSeparator);
}

const wstring StandardFileSystem::getFileName(const wstring& fileName) throw (FileSystemException) {
	wstring unixFileName = StringUtils::replace(fileName, L'\\', L'/');
	int32_t lastPathSeparator = StringUtils::lastIndexOf(unixFileName, L'/');
	if (lastPathSeparator == -1) return fileName;
	return StringUtils::substring(unixFileName, lastPathSeparator + 1, unixFileName.length());
}

void StandardFileSystem::createPath(const wstring& pathName) throw (FileSystemException) {
	int32_t status = mkdir(StringConverter::toString(pathName).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (status == -1) {
		throw FileSystemException("Unable to create path(" + to_string(errno) + ")");
	}
}

void StandardFileSystem::removePath(const wstring& pathName) throw (FileSystemException) {
	vector<wstring> files;
	list(pathName, &files, nullptr);
	for (int i = 0; i < files.size(); i++) {
		auto file = files.at(i);
		if (file == L"." || file == L"..") {
			continue;
		}
		auto completeFileName = getFileName(pathName, file);
		if (isPath(completeFileName)) {
			removePath(completeFileName);
		} else {
			removeFile(pathName, file);
		}
	}
	Console::println(wstring(L"StandardFileSystem::removePath(): Removing ") + pathName);
	int32_t status = rmdir(StringConverter::toString(pathName).c_str());
	if (status == -1) {
		throw FileSystemException("Unable to delete folder(" + to_string(errno) + ")");
	}
}

void StandardFileSystem::removeFile(const wstring& pathName, const wstring& fileName) throw (FileSystemException) {
	Console::println(wstring(L"StandardFileSystem::removeFile(): Removing ") + getFileName(pathName, fileName));
	int32_t status = unlink(StringConverter::toString(getFileName(pathName, fileName)).c_str());
	if (status == -1) {
		throw FileSystemException("Unable to delete file(" + to_string(errno) + ")");
	}
}
