#pragma once

#include <string>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/os/filesystem/fwd-miniscript.h>
#include <miniscript/utilities/ExceptionBase.h>

using std::string;
using std::vector;

using miniscript::utilities::ExceptionBase;

/**
 * File system
 * @author Andreas Drewke
 */
class miniscript::os::filesystem::FileSystem final
{

public:
	/**
	 * File system exception
	 * @author Andreas Drewke
	 */
	class FileSystemException: public ExceptionBase
	{
	public:
		/**
		 * @brief Public constructor
		 * @param message message Exception message
		 */
		FileSystemException(const string& message) throw(): ExceptionBase(message) {
			//
		}
	};

	/**
	 * File system file name filter interface
	 * @author Andreas Drewke
	 */
	struct FileNameFilter
	{
		/**
		 * Destructor
		 */
		virtual ~FileNameFilter() {}

		/**
		 * Accept a file
		 * @param path path
		 * @param file file
		 * @return if to accept file
		 */
		virtual bool accept(const string& path, const string& file) = 0;
	};

	/**
	 * Compose URI from path name and file name
	 * @param pathName path name
	 * @param fileName file name
	 * @return complete file URI with path name and file name
	 */
	static const string composeURI(const string& pathName, const string& fileName);

	/**
	 * Return file size of given file
	 * @param pathName path name
	 * @param fileName file name
	 * @return file size
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static uint64_t getFileSize(const string& pathName, const string& fileName);

	/**
	 * Get content as string
	 * @param pathName path name
	 * @param fileName file name
	 * @return string
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static const string getContentAsString(const string& pathName, const string& fileName);

	/**
	 * Set content from string
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content string
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void setContentFromString(const string& pathName, const string& fileName, const string& content);

	/**
	 * Get file content
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content vector
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void getContent(const string& pathName, const string& fileName, vector<uint8_t>& content);

	/**
	 * Set file content
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content vector
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void setContent(const string& pathName, const string& fileName, const vector<uint8_t>& content);

	/**
	 * Get file content as string array
	 * @param pathName path name
	 * @param fileName file name
	 * @param content content vector
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void getContentAsStringArray(const string& pathName, const string& fileName, vector<string>& content);

	/**
	 * Set file content as string array
	 * @param pathName path name
	 * @param fileName file name
	 * @param content string array
	 * @return byte array
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void setContentFromStringArray(const string& pathName, const string& fileName, const vector<string>& content);

	/**
	 * List files for given path and filter by a file name filter if not null
	 * @param pathName path name
	 * @param files files
	 * @param filter filter or null, this filter can be created on stack as ownership will not be taken over
	 * @param addDrives add drives to list(applies to Microsoft Windows only)
	 * @return file names
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void list(const string& pathName, vector<string>& files, FileNameFilter* filter = nullptr, bool addDrives = false);

	/**
	 * Check if file is a path
	 * @param uri uniform resource identifier
	 * @return if file is a path
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static bool isPath(const string& uri);

	/**
	 * Check if file is a drive (applies to Microsoft Windows only)
	 * @param uri uniform resource identifier
	 * @return if file is a drive
	 */
	static bool isDrive(const string& uri);

	/**
	 * Check if file exists
	 * @param uri uniform resource identifier
	 * @return bool if file exists
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static bool exists(const string& uri);

	/**
	 * Get canonical URI from given path name and file name
	 * @param pathName path name
	 * @param fileName file name
	 * @return canonical URI
	 */
	static const string getCanonicalURI(const string& pathName, const string& fileName);

	/**
	 * Get current working path name
	 * @return current working path
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static const string getCurrentWorkingPathName();

	/**
	 * Change path
	 * @param pathName path name
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void changePath(const string& pathName);

	/**
	 * Get path name
	 * @param uri uniform resource identifier
	 * @return canonical path
	 */
	static const string getPathName(const string& uri);

	/**
	 * Get file name
	 * @param uri uniform resource identifier
	 * @return canonical path
	 */
	static const string getFileName(const string& uri);

	/**
	 * Remove file extension, e.g. .dae, .fbx, ...
	 * @param fileName file name
	 * @return file name
	 */
	static const string removeFileExtension(const string& fileName);

	/**
	 * Create path
	 * @param pathName path name
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void createPath(const string& pathName);

	/**
	 * Remove path
	 * @param pathName path name
	 * @param recursive remove recursive
	 * @return success
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void removePath(const string& pathName, bool recursive);

	/**
	 * Remove file
	 * @param pathName path name
	 * @param fileName file name
	 * @return success
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void removeFile(const string& pathName, const string& fileName);

	/**
	 * Rename file
	 * @param fileNameFrom file name from
	 * @param fileNameTo file name to
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void rename(const string& fileNameFrom, const string& fileNameTo);

};
