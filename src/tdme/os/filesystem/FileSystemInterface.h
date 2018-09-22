#pragma once

#include <vector>
#include <string>

#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/os/filesystem/FileSystemException.h>

using std::vector;
using std::string;

using tdme::utils::FilenameFilter;

using tdme::os::filesystem::FileSystemException;

/** 
 * Interface to file system
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::os::filesystem::FileSystemInterface
{
	/**
	 * Get file name
	 * @param pathName path name
	 * @param fileName file name
	 * @return complete filename with path and file
	 * @throws FileSystemException
	 */
	virtual const string getFileName(const string& pathName, const string& fileName) throw (FileSystemException) = 0;

	/**
	 * Get content as string
	 * @param pathName path name
	 * @param fileName file name
	 * @return string
	 * @throws FileSystemException
	 */
	virtual const string getContentAsString(const string& pathName, const string& fileName) throw (FileSystemException) = 0;

	/**
	 * Set content from string
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content string
	 * @throws FileSystemException
	 */
	virtual void setContentFromString(const string& pathName, const string& fileName, const string& content) throw (FileSystemException) = 0;

	/** 
	 * Get file content
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content vector
	 * @throws FileSystemException
	 */
	virtual void getContent(const string& pathName, const string& fileName, vector<uint8_t>& content) throw (FileSystemException) = 0;

	/** 
	 * Set file content
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content vector
	 * @throws FileSystemException
	 */
	virtual void setContent(const string& pathName, const string& fileName, const vector<uint8_t>& content) throw (FileSystemException) = 0;

	/**
	 * Get file content as string array
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content vector
	 * @throws FileSystemException
	 */
	virtual void getContentAsStringArray(const string& pathName, const string& fileName, vector<string>& content) throw (FileSystemException) = 0;

	/**
	 * Set file content as string array
	 * @param pathName path name
	 * @param fileName file name
	 * @param content string array
	 * @return byte array
	 * @throws FileSystemException
	 */
	virtual void setContentFromStringArray(const string& pathName, const string& fileName, const vector<string>& content) throw (FileSystemException) = 0;

	/**
	 * List files for given path and filter by a file name filter if not null 
	 * @param pathName path name
	 * @param files files
	 * @param filter filter or null
	 * @param addDrives add drives to list(applies to Microsoft Windows only)
	 * @return file names 
	 */
	virtual void list(const string& pathName, vector<string>& files, FilenameFilter* filter = nullptr, bool addDrives = false) throw (FileSystemException) = 0;

	/**
	 * Check if file is a path
	 * @param pathName path name
	 * @return if file is a path
	 */
	virtual bool isPath(const string& pathName) throw (FileSystemException) = 0;

	/**
	 * Check if file is a drive (applies to Microsoft Windows only)
	 * @param pathName path name
	 * @return if file is a drive
	 */
	virtual bool isDrive(const string& pathName) throw (FileSystemException) = 0;

	/**
	 * Check if file exists
	 * @param fileName file name
	 * @return bool if file exists
	 */
	virtual bool fileExists(const string& fileName) throw (FileSystemException) = 0;

	/**
	 * Get canonical path name
	 * @param pathName path name
	 * @param fileName file name
	 * @return canonical path
	 */
	virtual const string getCanonicalPath(const string& pathName, const string& fileName) throw (FileSystemException) = 0;

	/**
	 * Get current working path name
	 * @return current working path
	 */
	virtual const string getCurrentWorkingPathName() throw (FileSystemException) = 0;

	/**
	 * Get path name
	 * @param fileName file name
	 * @return canonical path
	 */
	virtual const string getPathName(const string& fileName) throw (FileSystemException) = 0;

	/**
	 * Get file name
	 * @param fileName file name
	 * @return canonical path
	 */
	virtual const string getFileName(const string& fileName) throw (FileSystemException) = 0;

	/**
	 * Create path
	 * @param pathName path name
	 */
	virtual void createPath(const string& pathName) throw (FileSystemException) = 0;

	/**
	 * Remove path
	 * @param pathName path name
	 * @return success
	 */
	virtual void removePath(const string& pathName) throw (FileSystemException) = 0;

	/**
	 * Remove file
	 * @param pathName path name
	 * @param fileName file name
	 * @return success
	 */
	virtual void removeFile(const string& pathName, const string& fileName) throw (FileSystemException) = 0;
};
