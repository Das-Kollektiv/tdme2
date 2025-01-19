#pragma once

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utilities/fwd-tdme.h>

using std::ifstream;
using std::map;
using std::string;
using std::vector;

using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::Mutex;

/**
 * Archive file system implementation
 * @author Andreas Drewke
 */
class tdme::os::filesystem::ArchiveFileSystem final: public FileSystemInterface
{
private:
	struct FileInformation {
		string name;
		uint64_t bytes;
		uint8_t compressed;
		uint64_t bytesCompressed;
		uint64_t offset;
		bool executable;
	};
	string fileName;
	Mutex ifsMutex;
	ifstream ifs;
	map<string, FileInformation> fileInformations;

	/**
	 * Decompress from archive
	 * @param inContent compressed content
	 * @param outContent uncompressed out content
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	void decompress(vector<uint8_t>& inContent, vector<uint8_t>& outContent);

public:
	// forbid class copy
	FORBID_CLASS_COPY(ArchiveFileSystem)

	/**
	 * Public constructor
	 * @param fileName archive file name
	 */
	ArchiveFileSystem(const string& fileName = "archive.ta");

	/**
	 * Public destructor
	 */
	virtual ~ArchiveFileSystem();

	/**
	 * @returns Returns underlying TDME2 archive file name
	 */
	const string& getArchiveFileName();

	// overridden methods
	// overridden methods
	const string composeURI(const string& pathName, const string& fileName);
	uint64_t getFileSize(const string& pathName, const string& fileName);
	const string getContentAsString(const string& pathName, const string& fileName);
	void setContentFromString(const string& pathName, const string& fileName, const string& content);
	void getContent(const string& pathName, const string& fileName, vector<uint8_t>& content);
	void setContent(const string& pathName, const string& fileName, const vector<uint8_t>& content);
	void getContentAsStringArray(const string& pathName, const string& fileName, vector<string>& content);
	void setContentFromStringArray(const string& pathName, const string& fileName, const vector<string>& content);
	void list(const string& pathName, vector<string>& files, FileNameFilter* filter = nullptr, bool addDrives = false);
	bool isPath(const string& uri);
	bool isDrive(const string& uri);
	bool exists(const string& uri);
	bool isExecutable(const string& pathName, const string& fileName) override;
	void setExecutable(const string& pathName, const string& fileName) override;
	const string getCanonicalURI(const string& pathName, const string& fileName);
	const string getCurrentWorkingPathName();
	void changePath(const string& pathName);
	const string getPathName(const string& uri);
	const string getFileName(const string& uri);
	const string removeFileExtension(const string& fileName);
	void createPath(const string& pathName);
	void removePath(const string& pathName, bool recursive);
	void removeFile(const string& pathName, const string& fileName);
	void rename(const string& fileNameFrom, const string& fileNameTo);
	bool getThumbnailAttachment(const string& pathName, const string& fileName, vector<uint8_t>& thumbnailAttachmentContent);
	bool getThumbnailAttachment(const vector<uint8_t>& content, vector<uint8_t>& thumbnailAttachmentContent);

	/**
	 * Compute SHA256 hash
	 */
	const string computeSHA256Hash();
};
