// Generated from /tdme/src/tdme/os/_FileSystemInterface.java

#pragma once

#include <vector>
#include <string>

#include <tdme/os/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/os/_FileSystemException.h>

using std::vector;
using std::wstring;

using tdme::utils::FilenameFilter;

using tdme::os::_FileSystemException;

/** 
 * Interface to file system
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::os::_FileSystemInterface
{
	/**
	 * Get file name
	 * @param path name
	 * @param file name
	 * @return complete filename with path and file
	 */
	virtual const wstring getFileName(const wstring& pathName, const wstring& fileName) throw (_FileSystemException) = 0;

	/**
	 * Get content as string
	 * @param path name
	 * @param file name
	 * @return string
	 */
	virtual const wstring getContentAsString(const wstring& pathName, const wstring& fileName) throw (_FileSystemException) = 0;

	/**
	 * Set content from string
	 * @param path name
	 * @param file name
	 * @return string
	 */
	virtual void setContentFromString(const wstring& pathName, const wstring& fileName, const wstring& content) throw (_FileSystemException) = 0;

	/** 
	 * Get file content
	 * @param path name
	 * @param file name
	 * @return byte array
	 * @throws IOException
	 */
	virtual void getContent(const wstring& pathName, const wstring& fileName, vector<uint8_t>* content) throw (_FileSystemException) = 0;

	/** 
	 * Get file content
	 * @param path name
	 * @param file name
	 * @param data
	 * @param length or -1 if data length should be used
	 * @throws IOException
	 */
	virtual void setContent(const wstring& pathName, const wstring& fileName, vector<uint8_t>* content) throw (_FileSystemException) = 0;

	/**
	 * Get file content as string array
	 * @param path name
	 * @param file name
	 * @return byte array
	 * @throws IOException
	 */
	virtual void getContentAsStringArray(const wstring& pathName, const wstring& fileName, vector<wstring>* content) throw (_FileSystemException) = 0;

	/**
	 * Set file content as string array
	 * @param path name
	 * @param file name
	 * @param string array
	 * @return byte array
	 * @throws IOException
	 */
	virtual void setContentFromStringArray(const wstring& pathName, const wstring& fileName, vector<wstring>* content) throw (_FileSystemException) = 0;

	/**
	 * List files for given path and filter by a file name filter if not null 
	 * @param path name
	 * @param filter or null
	 * @return file names 
	 */
	virtual void list(const wstring& pathName, vector<wstring>* files, FilenameFilter* filter = nullptr) throw (_FileSystemException) = 0;

	/**
	 * Check if file is a path
	 * @param path name
	 * @return if file is a path
	 */
	virtual bool isPath(const wstring& pathName) throw (_FileSystemException) = 0;

	/**
	 * Check if file exists
	 * @param file name
	 * @return bool if file exists
	 */
	virtual bool fileExists(const wstring& fileName) throw (_FileSystemException) = 0;

	/**
	 * Get canonical path name
	 * @param path name
	 * @param file name
	 * @return canonical path
	 */
	virtual const wstring getCanonicalPath(const wstring& pathName, const wstring& fileName) throw (_FileSystemException) = 0;

	/**
	 * Get current working path name
	 * @return current working path
	 */
	virtual const wstring getCurrentWorkingPathName() throw (_FileSystemException) = 0;

	/**
	 * Get path name
	 * @param file name
	 * @return canonical path
	 */
	virtual const wstring getPathName(const wstring& fileName) throw (_FileSystemException) = 0;

	/**
	 * Get file name
	 * @param file name
	 * @return canonical path
	 */
	virtual const wstring getFileName(const wstring& fileName) throw (_FileSystemException) = 0;

	/**
	 * Create path
	 * @param path name
	 */
	virtual void createPath(const wstring& pathName) throw (_FileSystemException) = 0;

	/**
	 * Remove path
	 * @param path name
	 * @return success
	 */
	virtual void removePath(const wstring& pathName) throw (_FileSystemException) = 0;

	/**
	 * Remove file
	 * @param path name
	 * @param file name
	 * @return success
	 */
	virtual void removeFile(const wstring& pathName, const wstring& fileName) throw (_FileSystemException) = 0;
};
