#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

#include <tdme/os/filesystem/FileSystemException.h>

using std::string;
using std::vector;

using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystemException;

/**
 * File system interface
 * @author Andreas Drewke
 */
struct tdme::os::filesystem::FileSystemInterface
{
	/**
	 * Public destructor
	 */
	virtual ~FileSystemInterface() {}

	/**
	 * Compose URI from path name and file name
	 * @param pathName path name
	 * @param fileName file name
	 * @return complete file URI with path name and file name
	 */
	virtual const string composeURI(const string& pathName, const string& fileName) = 0;

	/**
	 * Return file size of given file
	 * @param pathName path name
	 * @param fileName file name
	 * @return file size
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual uint64_t getFileSize(const string& pathName, const string& fileName) = 0;

	/**
	 * Get content as string
	 * @param pathName path name
	 * @param fileName file name
	 * @return string
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual const string getContentAsString(const string& pathName, const string& fileName) = 0;

	/**
	 * Set content from string
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content string
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void setContentFromString(const string& pathName, const string& fileName, const string& content) = 0;

	/**
	 * Get file content
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content vector
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void getContent(const string& pathName, const string& fileName, vector<uint8_t>& content) = 0;

	/**
	 * Set file content
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content vector
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void setContent(const string& pathName, const string& fileName, const vector<uint8_t>& content) = 0;

	/**
	 * Get file content as string array
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content vector
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void getContentAsStringArray(const string& pathName, const string& fileName, vector<string>& content) = 0;

	/**
	 * Set file content as string array
	 * @param pathName path name
	 * @param fileName file name
	 * @param content string array
	 * @return byte array
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void setContentFromStringArray(const string& pathName, const string& fileName, const vector<string>& content) = 0;

	/**
	 * List files for given path and filter by a file name filter if not null
	 * @param pathName path name
	 * @param files files
	 * @param filter filter or null, this filter can be created on stack as ownership will not be taken over
	 * @param addDrives add drives to list(applies to Microsoft Windows only)
	 * @return file names
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void list(const string& pathName, vector<string>& files, FileNameFilter* filter = nullptr, bool addDrives = false) = 0;

	/**
	 * Check if file is a path
	 * @param uri uniform resource identifier
	 * @return if file is a path
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual bool isPath(const string& uri) = 0;

	/**
	 * Check if file is a drive (applies to Microsoft Windows only)
	 * @param uri uniform resource identifier
	 * @return if file is a drive
	 */
	virtual bool isDrive(const string& uri) = 0;

	/**
	 * Check if file exists
	 * @param uri uniform resource identifier
	 * @return bool if file exists
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual bool exists(const string& uri) = 0;

	/**
	 * Returns if file is a executable file
	 * @param pathName path name
	 * @param fileName file name
	 * @return is executable
	 */
	virtual bool isExecutable(const string& pathName, const string& fileName) = 0;

	/**
	 * Set up file to be an executable file
	 * @param pathName path name
	 * @param fileName file name
	 * @return success
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void setExecutable(const string& pathName, const string& fileName) = 0;

	/**
	 * Get canonical URI from given path name and file name
	 * @param pathName path name
	 * @param fileName file name
	 * @return canonical URI
	 */
	virtual const string getCanonicalURI(const string& pathName, const string& fileName) = 0;

	/**
	 * Get current working path name
	 * @return current working path
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual const string getCurrentWorkingPathName() = 0;

	/**
	 * Change path
	 * @param pathName path name
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void changePath(const string& pathName) = 0;

	/**
	 * Get path name
	 * @param uri uniform resource identifier
	 * @return canonical path
	 */
	virtual const string getPathName(const string& uri) = 0;

	/**
	 * Get file name
	 * @param uri uniform resource identifier
	 * @return canonical path
	 */
	virtual const string getFileName(const string& uri) = 0;

	/**
	 * Remove file extension, e.g. .dae, .fbx, ...
	 * @param fileName file name
	 * @return file name
	 */
	virtual const string removeFileExtension(const string& fileName) = 0;

	/**
	 * Create path
	 * @param pathName path name
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void createPath(const string& pathName) = 0;

	/**
	 * Remove path
	 * @param pathName path name
	 * @param recursive remove recursive
	 * @return success
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void removePath(const string& pathName, bool recursive) = 0;

	/**
	 * Remove file
	 * @param pathName path name
	 * @param fileName file name
	 * @return success
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void removeFile(const string& pathName, const string& fileName) = 0;

	/**
	 * Rename file
	 * @param fileNameFrom file name from
	 * @param fileNameTo file name to
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	virtual void rename(const string& fileNameFrom, const string& fileNameTo) = 0;

	/**
	 * Reads a thumbnail attachment from binary file
	 * @param pathName path name
	 * @param fileName file name
	 * @param thumbnailAttachmentContent thumbnail attachment content
	 * @return attachment available
	 */
	virtual bool getThumbnailAttachment(const string& pathName, const string& fileName, vector<uint8_t>& thumbnailAttachmentContent) = 0;

	/**
	 * Reads a thumbnail attachment from data vector
	 * @param content content
	 * @param thumbnailAttachmentContent thumbnail attachment content
	 * @return attachment available
	 */
	virtual bool getThumbnailAttachment(const vector<uint8_t>& content, vector<uint8_t>& thumbnailAttachmentContent) = 0;
};
