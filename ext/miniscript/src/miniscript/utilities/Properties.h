#pragma once

#include <map>
#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/fwd-miniscript.h>

using std::map;
using std::string;

/**
 * Properties class, which helps out with storeing or loading key value pairs from/to property files
 * @author Andreas Drewke
 */
class miniscript::utilities::Properties
{
private:
	map<string, string> properties;

public:
	/**
	 * Public constructor
	 */
	Properties() {}

	/**
	 * Clear
	 */
	inline void clear() {
		properties.clear();
	}

	/**
	 * Get property value by key
	 * @param key key
	 * @param defaultValue default value
	 * @return value if found or default value
	 */
	inline const string& get(const string& key, const string& defaultValue) const {
		auto it = properties.find(key);
		if (it == properties.end()) return defaultValue;
		return it->second;
	}

	/**
	 * Add property
	 * @param key key
	 * @param value value
	 *
	 */
	inline void put(const string& key, const string& value) {
		properties[key] = value;
	}

	/**
	 * Load property file
	 * @param pathName path name
	 * @param fileName file name
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	void load(const string& pathName, const string& fileName);

	/**
	 * Store property file
	 * @param pathName path name
	 * @param fileName file name
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	void store(const string& pathName, const string& fileName) const;

	/**
	 * @return properties map
	 */
	inline const map<string, string>& getProperties() {
		return properties;
	}

};
