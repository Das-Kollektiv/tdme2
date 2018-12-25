#pragma once

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/fwd-tdme.h>

using std::ifstream;
using std::map;
using std::string;
using std::vector;

using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::FilenameFilter;

/**
 * Archive file system, no endianness yet
 */
class tdme::os::filesystem::ArchiveFileSystem final
	: public FileSystemInterface
{
private:
	struct FileInformation {
		string name;
		uint64_t bytes;
		uint8_t compressed;
		uint64_t bytesCompressed;
		uint64_t offset;
	};
	ifstream ifs;
	map<string, FileInformation> fileInformations;

	/**
	 * Decompress from archive
	 * @param inContent compressed content
	 * @param outContent uncompressed out content
	 * @throws FileSystemException
	 */
	void decompress(vector<uint8_t>& inContent, vector<uint8_t>& outContent) throw (FileSystemException);

public:
	const string getFileName(const string& path, const string& fileName) throw (FileSystemException) override;
	void list(const string& pathName, vector<string>& files, FilenameFilter* filter = nullptr, bool addDrives = false) throw (FileSystemException) override;
	bool isPath(const string& pathName) throw (FileSystemException) override;
	bool isDrive(const string& pathName) throw (FileSystemException) override;
	bool fileExists(const string& fileName) throw (FileSystemException) override;
	const string getContentAsString(const string& pathName, const string& fileName) throw (FileSystemException) override;
	void setContentFromString(const string& pathName, const string& fileName, const string& content) throw (FileSystemException) override;
	void getContent(const string& pathName, const string& fileName, vector<uint8_t>& content) throw (FileSystemException) override;
	void setContent(const string& pathName, const string& fileName, const vector<uint8_t>& content) throw (FileSystemException) override;
	void getContentAsStringArray(const string& pathName, const string& fileName, vector<string>& content) throw (FileSystemException) override;
	void setContentFromStringArray(const string& pathName, const string& fileName, const vector<string>& content) throw (FileSystemException) override;
	const string getCanonicalPath(const string& pathName, const string& fileName) throw (FileSystemException) override;
	const string getCurrentWorkingPathName() throw (FileSystemException) override;
	const string getPathName(const string& fileName) throw (FileSystemException) override;
	const string getFileName(const string& fileName) throw (FileSystemException) override;
	void createPath(const string& pathName) throw (FileSystemException) override;
	void removePath(const string& pathName) throw (FileSystemException) override;
	void removeFile(const string& pathName, const string& fileName) throw (FileSystemException) override;
	ArchiveFileSystem();
	~ArchiveFileSystem();
};
