#include <tdme/os/filesystem/ArchiveFileSystem.h>

#include <cassert>
#include <fstream>
#include <string>
#include <vector>

#include <ext/zlib/zlib.h>

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
	// compose relative file name and remove ./
	auto relativeFileName = fileName;
	if (StringUtils::startsWith(relativeFileName, "./")  == true) relativeFileName = StringUtils::substring(relativeFileName, 2);

	//
	return fileInformations.find(relativeFileName) != fileInformations.end();
}

void ArchiveFileSystem::decompress(vector<uint8_t>& inContent, vector<uint8_t>& outContent) throw (FileSystemException) {
	// see: https://www.zlib.net/zpipe.c

	#define CHUNK	16384

	int ret;
	size_t have;
	z_stream strm;
	unsigned char in[CHUNK];
	unsigned char out[CHUNK];

	// allocate inflate state
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	ret = inflateInit(&strm);
	if (ret != Z_OK) {
		throw FileSystemException("ArchiveFileSystem::decompress(): Error while decompressing: inflate init");
	}

	// decompress until deflate stream ends or end of file */
	size_t outPosition = 0;
	size_t inPosition = 0;
	size_t inBytes = inContent.size();
	do {
		// see: https://www.zlib.net/zpipe.c
		auto inStartPosition = inPosition;
		for (size_t i = 0; i < CHUNK; i++) {
			if (inPosition == inBytes) break;
			in[i] = inContent[inPosition];
			inPosition++;
		}
		strm.avail_in = inPosition - inStartPosition;
		if (strm.avail_in == 0) break;
		strm.next_in = in;

		// run inflate() on input until output buffer not full
		do {
			strm.avail_out = CHUNK;
			strm.next_out = out;
			ret = inflate(&strm, Z_NO_FLUSH);
			assert(ret != Z_STREAM_ERROR); // state not clobbered
			switch (ret) {
				case Z_NEED_DICT:
					throw FileSystemException("ArchiveFileSystem::decompress(): Error while decompressing: Z_NEED_DICT");
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					(void)inflateEnd(&strm);
					throw FileSystemException("ArchiveFileSystem::decompress(): Error while decompressing: Z_DATA_ERROR | Z_MEM_ERROR");
			}
			have = CHUNK - strm.avail_out;
			for (size_t i = 0; i < have; i++) {
				outContent[outPosition++] = out[i];
			}
		} while (strm.avail_out == 0);

		// done when inflate() says it's done
	} while (ret != Z_STREAM_END);

	// clean up and return
	(void) inflateEnd(&strm);

	// check if eof
	if (ret != Z_STREAM_END) {
		throw FileSystemException("ArchiveFileSystem::decompress(): Error while decompressing: missing eof");
	}
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
	if (fileInformation.compressed == 1) {
		vector<uint8_t> compressedBuffer;
		compressedBuffer.resize(fileInformation.bytesCompressed);
		vector<uint8_t> decompressedBuffer;
		decompressedBuffer.resize(fileInformation.bytes);
		ifs.read((char*)compressedBuffer.data(), fileInformation.bytesCompressed);
		decompress(compressedBuffer, decompressedBuffer);
		result.append((char*)decompressedBuffer.data(), fileInformation.bytes);
	} else {
		vector<uint8_t> buffer;
		buffer.resize(fileInformation.bytes);
		ifs.read((char*)buffer.data(), fileInformation.bytes);
		result.append((char*)buffer.data(), fileInformation.bytes);
	}

	// done
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
	if (fileInformation.compressed == 1) {
		vector<uint8_t> compressedContent;
		compressedContent.resize(fileInformation.bytesCompressed);
		content.resize(fileInformation.bytes);
		ifs.read((char*)compressedContent.data(), fileInformation.bytesCompressed);
		decompress(compressedContent, content);
	} else {
		content.resize(fileInformation.bytes);
		ifs.read((char*)content.data(), fileInformation.bytes);
	}
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
