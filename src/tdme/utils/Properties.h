#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>

#include <tdme/os/filesystem/FileSystemException.h>

using std::map;
using std::string;

using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

/**
 * This helps out with storeing or loading key value pairs from/to property files
 */
class tdme::utils::Properties
{
private:
	map<string, string> properties;

public:
	/**
	 * Get property value by key
	 * @param key key
	 * @param defaultValue default value
	 * @return value if found or default value
	 */
	const string& get(const string& key, const string& defaultValue);

	/**
	 * Add property
	 * @param key key
	 * @param value value
	 *
	 */
	void put(const string& key, const string& value);

	/**
	 * Load property file
	 * @param pathName path name
	 * @param fileName file name
	 * @throws file system exception
	 */
	void load(const string& pathName, const string& fileName) throw (FileSystemException);

	/**
	 * Store property file
	 * @param pathName path name
	 * @param fileName file name
	 * @throws file system exception
	 */
	void store(const string& pathName, const string& fileName) throw (FileSystemException);

	/**
	 * Public constructor
	 */
	Properties();
};
