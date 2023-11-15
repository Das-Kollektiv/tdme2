#pragma once

#include <string>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/fwd-miniscript.h>
#include <miniscript/utilities/ExceptionBase.h>

using std::string;
using std::vector;

using miniscript::utilities::ExceptionBase;

/**
 * File system
 * @author Andreas Drewke
 */
class miniscript::utilities::FileSystem final
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
	 * Get file name
	 * @param pathName path name
	 * @param fileName file name
	 * @return complete filename with path and file
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static const string getFileName(const string& pathName, const string& fileName);

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
	 */
	static void list(const string& pathName, vector<string>& files, FileNameFilter* filter = nullptr, bool addDrives = false);

	/**
	 * Check if file is a path
	 * @param pathName path name
	 * @return if file is a path
	 */
	static bool isPath(const string& pathName);

	/**
	 * Check if file is a drive (applies to Microsoft Windows only)
	 * @param pathName path name
	 * @return if file is a drive
	 */
	static bool isDrive(const string& pathName);

	/**
	 * Check if file exists
	 * @param fileName file name
	 * @return bool if file exists
	 */
	static bool fileExists(const string& fileName);

	/**
	 * Get path name
	 * @param fileName file name
	 * @return canonical path
	 */
	static const string getPathName(const string& fileName);

	/**
	 * Get file name
	 * @param fileName file name
	 * @return canonical path
	 */
	static const string getFileName(const string& fileName);

	/**
	 * Remove file extension, e.g. .dae, .fbx, ...
	 * @param fileName file name
	 * @return file name
	 */
	static const string removeFileExtension(const string& fileName);

};
