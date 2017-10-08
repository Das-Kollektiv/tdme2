
#pragma once

#include <map>
#include <string>

#include <tdme.h>

#include <tdme/os/filesystem/FileSystemException.h>

using std::map;
using std::wstring;

using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

/**
 * This helps out with storeing or loading key value pairs from/to property files
 */
class tdme::utils::Properties
{
private:
	map<wstring, wstring> properties;

public:
	/**
	 * Get property value by key
	 * @param key
	 * @param default value
	 * @return value if found or default value
	 */
	const wstring& get(const wstring& key, const wstring& defaultValue);

	/**
	 * Add property
	 * @param key
	 * @param value
	 *
	 */
	void put(const wstring& key, const wstring& value);

	/**
	 * Load property file
	 * @param path name
	 * @param file name
	 * @throws file system exception
	 */
	void load(const wstring& pathName, const wstring& fileName) throw (FileSystemException);

	/**
	 * Store property file
	 * @param path name
	 * @param file name
	 * @throws file system exception
	 */
	void store(const wstring& pathName, const wstring& fileName) throw (FileSystemException);

	/**
	 * Public constructor
	 */
	Properties();
};
