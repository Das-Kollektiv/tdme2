#include <miniscript/os/filesystem/FileSystem.h>

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>
#include <miniscript/utilities/StringTokenizer.h>
#include <miniscript/utilities/StringTools.h>

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

using miniscript::os::filesystem::FileSystem;

using miniscript::utilities::Console;
using miniscript::utilities::Exception;
using miniscript::utilities::StringTokenizer;
using miniscript::utilities::StringTools;

const string FileSystem::composeURI(const string& pathName, const string& fileName) {
	return pathName + "/" + fileName;
}

void FileSystem::list(const string& pathName, vector<string>& files, FileNameFilter* filter, bool addDrives)
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
				Console::println("FileSystem::list(): Filter::accept(): " + pathName + "/" + fileName + ": " + string(exception.what()));
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
					Console::println("FileSystem::list(): fileExists(): " + pathName + "/" + fileName + ": " + string(exception.what()));
				}
			}
		}
	#endif
}

bool FileSystem::isPath(const string& pathName) {
	try {
		auto status = std::filesystem::status(std::filesystem::u8path(pathName));
		return std::filesystem::is_directory(status);
	} catch (Exception& exception) {
		throw FileSystemException("Unable to check if path: " + pathName + ": " + string(exception.what()));
	}
	//
	return false;
}

bool FileSystem::isDrive(const string& pathName) {
	return StringTools::regexMatch(pathName, "^[a-zA-Z]{1}\\:.*$");
}

bool FileSystem::exists(const string& uri) {
	try {
		return std::filesystem::exists(std::filesystem::u8path(uri));
	} catch (Exception& exception) {
		throw FileSystemException("Unable to check if file exists: " + uri + ": " + string(exception.what()));
	}
	//
	return false;
}

uint64_t FileSystem::getFileSize(const string& pathName, const string& fileName) {
	try {
		return std::filesystem::file_size(std::filesystem::u8path(pathName + "/" + fileName));
	} catch (Exception& exception) {
		throw FileSystemException("Unable to determine file size: " + fileName + ": " + string(exception.what()));
	}
	//
	return false;
}

const string FileSystem::getContentAsString(const string& pathName, const string& fileName) {
	ifstream ifs(std::filesystem::u8path(composeURI(pathName, fileName)));
	if (ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	stringstream stringStream;
	stringStream << ifs.rdbuf();
	ifs.close();
	return (stringStream.str());
}

void FileSystem::setContentFromString(const string& pathName, const string& fileName, const string& content) {
	ofstream ofs(std::filesystem::u8path(composeURI(pathName, fileName)));
	if (ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	ofs << (content);
	ofs.close();
	return;
}

void FileSystem::getContent(const string& pathName, const string& fileName, vector<uint8_t>& content)
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

void FileSystem::setContent(const string& pathName, const string& fileName, const vector<uint8_t>& content) {
	ofstream ofs(std::filesystem::u8path(composeURI(pathName, fileName)), ofstream::binary);
	if (ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	ofs.write((char*)content.data(), content.size());
	ofs.close();
}

void FileSystem::getContentAsStringArray(const string& pathName, const string& fileName, vector<string>& content)
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

void FileSystem::setContentFromStringArray(const string& pathName, const string& fileName, const vector<string>& content)
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

const string FileSystem::getCanonicalURI(const string& pathName, const string& fileName) {
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

const string FileSystem::getCurrentWorkingPathName() {
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

void FileSystem::changePath(const string& pathName) {
	try {
		return std::filesystem::current_path(std::filesystem::u8path(pathName));
	} catch (Exception& exception) {
		throw FileSystemException("Unable to change path: " + pathName + ": " + string(exception.what()));
	}
}

const string FileSystem::getPathName(const string& uri) {
	auto unixFileName = StringTools::replace(uri, '\\', '/');
	auto lastPathSeparator = StringTools::lastIndexOf(unixFileName, '/');
	if (lastPathSeparator == -1) return ".";
	return StringTools::substring(unixFileName, 0, lastPathSeparator);
}

const string FileSystem::getFileName(const string& uri) {
	auto unixFileName = StringTools::replace(uri, '\\', '/');
	auto lastPathSeparator = StringTools::lastIndexOf(unixFileName, '/');
	if (lastPathSeparator == -1) return uri;
	return StringTools::substring(unixFileName, lastPathSeparator + 1, unixFileName.length());
}

const string FileSystem::removeFileExtension(const string& fileName) {
	auto idx = fileName.rfind('.');
	if (idx == string::npos) {
		return fileName;
	} else {
		return fileName.substr(0, idx);
	}
}

void FileSystem::createPath(const string& pathName) {
	try {
		if (std::filesystem::create_directory(std::filesystem::u8path(pathName)) == false) {
			throw FileSystemException("Unable to create path: " + pathName);
		}
	} catch (Exception& exception) {
		throw FileSystemException("Unable to create path: " + pathName + ": " + string(exception.what()));
	}
}

void FileSystem::removePath(const string& pathName, bool recursive) {
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

void FileSystem::removeFile(const string& pathName, const string& fileName) {
	try {
		if (std::filesystem::remove(std::filesystem::u8path(composeURI(pathName, fileName))) == false) {
			throw FileSystemException("Unable to remove file: " + pathName + "/" + fileName);
		}
	} catch (Exception& exception) {
		throw FileSystemException("Unable to remove file: " + pathName + "/" + fileName + ": " + string(exception.what()));
	}
}

void FileSystem::rename(const string& fileNameFrom, const string& fileNameTo) {
	try {
		std::filesystem::rename(std::filesystem::u8path(fileNameFrom), std::filesystem::u8path(fileNameTo));
	} catch (Exception& exception) {
		throw FileSystemException("Unable to rename file: " + fileNameFrom + " -> " + fileNameTo + ": " + string(exception.what()));
	}
}
