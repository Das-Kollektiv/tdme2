// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <map>
#include <string>

#include <fwd-tdme.h>

#include <tdme/os/_FileSystemException.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

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
	void load(const wstring& pathName, const wstring& fileName) throw (_FileSystemException);

	/**
	 * Store property file
	 * @param path name
	 * @param file name
	 * @throws file system exception
	 */
	void store(const wstring& pathName, const wstring& fileName) throw (_FileSystemException);

	/**
	 * Public constructor
	 */
	Properties();
};
