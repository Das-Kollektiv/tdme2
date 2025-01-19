#pragma once

#include <string>
#include <unordered_map>

#include <agui/agui.h>

#include <agui/agui.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

// namespaces
namespace agui {
namespace utilities {
	using ::agui::os::filesystem::FileSystemException;
	using ::agui::os::filesystem::FileSystemInterface;
}
}

/**
 * Properties class, which helps out with storeing or loading key value pairs from/to property files
 * @author Andreas Drewke
 */
class agui::utilities::Properties
{
private:
	unordered_map<string, string> properties;

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
	 * @param fileSystem file system to use
	 * @throws agui::os::filesystem::FileSystemException
	 */
	void load(const string& pathName, const string& fileName, FileSystemInterface* fileSystem = nullptr);

	/**
	 * Store property file
	 * @param pathName path name
	 * @param fileName file name
	 * @param fileSystem file system to use
	 * @throws agui::os::filesystem::FileSystemException
	 */
	void store(const string& pathName, const string& fileName, FileSystemInterface* fileSystem = nullptr) const;

	/**
	 * @return properties map
	 */
	inline const unordered_map<string, string>& getProperties() {
		return properties;
	}

};
