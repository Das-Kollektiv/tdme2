#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystemInterface;

/**
 * Standard file system implementation
 * @author Andreas Drewke
 */
class tdme::os::filesystem::StandardFileSystem final: public FileSystemInterface
{

public:
	// forbid class copy
	FORBID_CLASS_COPY(StandardFileSystem)

	/**
	 * Public constructor
	 */
	StandardFileSystem();

	/**
	 * Public destructor
	 */
	~StandardFileSystem();

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
};
