#include <miniscript/utilities/FileSystem.h>

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

using miniscript::utilities::FileSystem;

using miniscript::utilities::Console;
using miniscript::utilities::Exception;
using miniscript::utilities::StringTokenizer;
using miniscript::utilities::StringTools;

const string FileSystem::getFileName(const string& pathName, const string& fileName) {
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
					if (fileExists(fileName + "/") == true) files.insert(files.begin() + (drive - 'C'), fileName);
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
	return StringTools::regexMatch(pathName, "^[a-zA-Z]\\:[\\/\\\\]?$");
}

bool FileSystem::fileExists(const string& fileName) {
	try {
		return std::filesystem::exists(std::filesystem::u8path(fileName));
	} catch (Exception& exception) {
		throw FileSystemException("Unable to check if file exists: " + fileName + ": " + string(exception.what()));
	}
	//
	return false;
}

const string FileSystem::getContentAsString(const string& pathName, const string& fileName) {
	ifstream ifs(std::filesystem::u8path(getFileName(pathName, fileName)));
	if (ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	stringstream stringStream;
	stringStream << ifs.rdbuf();
	ifs.close();
	return (stringStream.str());
}

void FileSystem::setContentFromString(const string& pathName, const string& fileName, const string& content) {
	ofstream ofs(std::filesystem::u8path(getFileName(pathName, fileName)));
	if (ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}
	ofs << (content);
	ofs.close();
	return;
}

void FileSystem::getContentAsStringArray(const string& pathName, const string& fileName, vector<string>& content)
{
	ifstream ifs(std::filesystem::u8path(getFileName(pathName, fileName)));
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
	ofstream ofs(std::filesystem::u8path(getFileName(pathName, fileName)), ofstream::binary);
	if(ofs.is_open() == false) {
		throw FileSystemException("Unable to open file for writing(" + to_string(errno) + "): " + pathName + "/" + fileName);
	}

	for (auto i = 0; i < content.size(); i++) {
		ofs << (content.at(i)) << "\n";
	}

	ofs.close();
	return;
}

const string FileSystem::getPathName(const string& fileName) {
	auto unixFileName = StringTools::replace(fileName, '\\', '/');
	auto lastPathSeparator = StringTools::lastIndexOf(unixFileName, '/');
	if (lastPathSeparator == -1) return ".";
	return StringTools::substring(unixFileName, 0, lastPathSeparator);
}

const string FileSystem::getFileName(const string& fileName) {
	auto unixFileName = StringTools::replace(fileName, '\\', '/');
	auto lastPathSeparator = StringTools::lastIndexOf(unixFileName, '/');
	if (lastPathSeparator == -1) return fileName;
	return StringTools::substring(unixFileName, lastPathSeparator + 1, unixFileName.length());
}

const string FileSystem::removeFileExtension(const string& fileName)
{
	auto idx = fileName.rfind('.');
	if (idx == string::npos) {
		return fileName;
	} else {
		return fileName.substr(0, idx);
	}
}
