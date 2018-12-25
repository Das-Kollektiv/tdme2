#include <tdme/os/filesystem/ArchiveFileSystem.h>

#include <fstream>
#include <string>
#include <vector>

#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/FilenameFilter.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using std::ifstream;
using std::ios;
using std::string;
using std::to_string;
using std::vector;

using tdme::os::filesystem::ArchiveFileSystem;
using tdme::utils::StringUtils;
using tdme::utils::StringTokenizer;
using tdme::utils::Console;
using tdme::utils::Exception;

ArchiveFileSystem::ArchiveFileSystem()
{
	// open
	ifs.open("archive.ta", ifstream::binary);
	if (ifs.is_open() == false) {
		throw FileSystemException("Unable to open file for reading(" + to_string(errno) + "): archive.ta");
	}

	// read toc offset
	int64_t fileInformationOffset;
	ifs.seekg(-sizeof(fileInformationOffset), ios::end);
	ifs.read((char*)&fileInformationOffset, sizeof(fileInformationOffset));
	ifs.seekg(fileInformationOffset, ios::beg);

	// read toc
	while (true == true) {
		uint32_t nameSize;
		ifs.read((char*)&nameSize, sizeof(nameSize));
		if (nameSize == 0) break;

		FileInformation fileInformation;
		auto buffer = new char[nameSize];
		ifs.read(buffer, nameSize);
		fileInformation.name.append(buffer, nameSize);
		delete [] buffer;
		ifs.read((char*)&fileInformation.bytes, sizeof(fileInformation.bytes));
		ifs.read((char*)&fileInformation.compressed, sizeof(fileInformation.compressed));
		ifs.read((char*)&fileInformation.bytesCompressed, sizeof(fileInformation.bytesCompressed));
		ifs.read((char*)&fileInformation.offset, sizeof(fileInformation.offset));
		fileInformations[fileInformation.name] = fileInformation;
	}
}

ArchiveFileSystem::~ArchiveFileSystem()
{
	ifs.close();
}

const string ArchiveFileSystem::getFileName(const string& pathName, const string& fileName) throw (FileSystemException) {
	return pathName + "/" + fileName;
}

void ArchiveFileSystem::list(const string& pathName, vector<string>& files, FilenameFilter* filter, bool addDrives) throw (FileSystemException)
{
	throw FileSystemException("ArchiveFileSystem::list(): Not implemented yet");
}

bool ArchiveFileSystem::isPath(const string& pathName) throw (FileSystemException) {
	throw FileSystemException("ArchiveFileSystem::isPath(): Not implemented yet");
}

bool ArchiveFileSystem::isDrive(const string& pathName) throw (FileSystemException) {
	throw FileSystemException("ArchiveFileSystem::isDrive(): Not implemented yet");
}

bool ArchiveFileSystem::fileExists(const string& fileName) throw (FileSystemException) {
	return fileInformations.find(fileName) != fileInformations.end();
}

const string ArchiveFileSystem::getContentAsString(const string& pathName, const string& fileName) throw (FileSystemException) {
	// compose relative file name and remove ./
	auto relativeFileName = pathName + "/" + fileName;
	if (StringUtils::startsWith(relativeFileName, "./")  == true) relativeFileName = StringUtils::substring(relativeFileName, 2);

	// determine file
	auto fileInformationIt = fileInformations.find(relativeFileName);
	if (fileInformationIt == fileInformations.end()) {
		throw FileSystemException("Unable to open file for reading: " + relativeFileName);
	}
	auto& fileInformation = fileInformationIt->second;

	// seek
	ifs.seekg(fileInformation.offset, ios::beg);

	// result
	string result;
	auto buffer = new char[fileInformation.bytes];
	ifs.read(buffer, fileInformation.bytes);
	result.append(buffer, fileInformation.bytes);
	delete [] buffer;
	return result;
}

void ArchiveFileSystem::setContentFromString(const string& pathName, const string& fileName, const string& content) throw (FileSystemException) {
	throw FileSystemException("ArchiveFileSystem::setContentFromString(): Not implemented yet");
}

void ArchiveFileSystem::getContent(const string& pathName, const string& fileName, vector<uint8_t>& content) throw (FileSystemException)
{
	// compose relative file name and remove ./
	auto relativeFileName = pathName + "/" + fileName;
	if (StringUtils::startsWith(relativeFileName, "./")  == true) relativeFileName = StringUtils::substring(relativeFileName, 2);

	// determine file
	auto fileInformationIt = fileInformations.find(relativeFileName);
	if (fileInformationIt == fileInformations.end()) {
		throw FileSystemException("Unable to open file for reading: " + relativeFileName);
	}
	auto& fileInformation = fileInformationIt->second;


	// seek
	ifs.seekg(fileInformation.offset, ios::beg);

	// result
	content.resize(fileInformation.bytes);
	ifs.read((char*)content.data(), fileInformation.bytes);
}

void ArchiveFileSystem::setContent(const string& pathName, const string& fileName, const vector<uint8_t>& content) throw (FileSystemException) {
	throw FileSystemException("ArchiveFileSystem::setContent(): Not implemented yet");
}

void ArchiveFileSystem::getContentAsStringArray(const string& pathName, const string& fileName, vector<string>& content) throw (FileSystemException)
{
	auto contentAsString = getContentAsString(pathName, fileName);
	contentAsString = StringUtils::replace(contentAsString, "\r", "");
	StringTokenizer t;
	t.tokenize(contentAsString, "\n");
	while (t.hasMoreTokens() == true) {
		content.push_back(t.nextToken());
	}
}

void ArchiveFileSystem::setContentFromStringArray(const string& pathName, const string& fileName, const vector<string>& content) throw (FileSystemException)
{
	throw FileSystemException("ArchiveFileSystem::setContentFromStringArray(): Not implemented yet");
}

const string ArchiveFileSystem::getCanonicalPath(const string& pathName, const string& fileName) throw (FileSystemException) {
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
		StringUtils::matches(canonicalPathString, "^[a-zA-Z]\\:.*$") == false)) {
		canonicalPathString = getCurrentWorkingPathName() + "/" + canonicalPathString;
	}

	//
	return canonicalPathString;
}

const string ArchiveFileSystem::getCurrentWorkingPathName() throw (FileSystemException) {
	return ".";
}

const string ArchiveFileSystem::getPathName(const string& fileName) throw (FileSystemException) {
	string unixFileName = StringUtils::replace(fileName, L'\\', L'/');
	int32_t lastPathSeparator = StringUtils::lastIndexOf(unixFileName, L'/');
	if (lastPathSeparator == -1) return ".";
	return StringUtils::substring(unixFileName, 0, lastPathSeparator);
}

const string ArchiveFileSystem::getFileName(const string& fileName) throw (FileSystemException) {
	string unixFileName = StringUtils::replace(fileName, L'\\', L'/');
	int32_t lastPathSeparator = StringUtils::lastIndexOf(unixFileName, L'/');
	if (lastPathSeparator == -1) return fileName;
	return StringUtils::substring(unixFileName, lastPathSeparator + 1, unixFileName.length());
}

void ArchiveFileSystem::createPath(const string& pathName) throw (FileSystemException) {
	throw FileSystemException("ArchiveFileSystem::createPath(): Not implemented yet");
}

void ArchiveFileSystem::removePath(const string& pathName) throw (FileSystemException) {
	throw FileSystemException("ArchiveFileSystem::removePath(): Not implemented yet");
}

void ArchiveFileSystem::removeFile(const string& pathName, const string& fileName) throw (FileSystemException) {
	throw FileSystemException("ArchiveFileSystem::removeFile(): Not implemented yet");
}
