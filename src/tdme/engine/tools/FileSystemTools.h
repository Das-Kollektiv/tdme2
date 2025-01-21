#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/fwd-tdme.h>
#include <tdme/engine/tools/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::application::Application;

/**
 * Additional file system tools
 * @author Andreas Drewke
 */
class tdme::engine::tools::FileSystemTools final
{
public:
	/**
	 * Get relative resources file name
	 * @param applicationRoot application root
	 * @param fileName file name
	 * @returns relative resources file name
	 */
	static const string getRelativeResourcesFileName(const string& applicationRoot, const string& fileName);

	/**
	 * Get application root path name
	 * @param fileName file name
	 * @returns application root path name
	 */
	static const string getApplicationRootPathName(const string& fileName);

	/**
	 * Get application sub path name
	 * @param fileName application sub path name
	 * @returns application sub path name
	 */
	static const string getApplicationSubPathName(const string& fileName);

	/**
	 * Get canonical URI of given path and file name
	 * @param pathName path name
	 * @param fileName file name
	 * @returns path
	 */
	static const string getCanonicalURI(const string& pathName, const string& fileName);

	/**
	 * Get path of given file name
	 * @param fileName file name
	 * @returns path
	 */
	static const string getPathName(const string& fileName);

	/**
	 * Get file name of given file name
	 * @param fileName file name
	 * @returns file name
	 */
	static const string getFileName(const string& fileName);

	/**
	 * Remove file extension, e.g. .dae, .fbx, ...
	 * @param fileName file name
	 * @returns file name
	 */
	static const string removeFileExtension(const string& fileName);

	/**
	 * Ensure file extension
	 * @param fileName file name
	 * @param extension extension
	 * @returns file name
	 */
	static const string ensureFileExtension(const string& fileName, const string& extension);

	/**
	 * Get file extension
	 * @param fileName file name
	 * @returns file extension
	 */
	static const string getFileExtension(const string& fileName);

	/**
	 * Returns if file extension of given file name does match a extension in given extensions
	 * @param fileName file name
	 * @param extensions extensions
	 * @returns success
	 */
	static bool hasFileExtension(const string& fileName, const vector<string>& extensions);

	/**
	 * Enumerate file extensions
	 * @param extensions extensions
	 * @returns file extensions as human readable string
	 */
	inline static const string enumerateFileExtensions(const vector<string>& extensions) {
		string result;
		for (const auto& extension: extensions) {
			if (result.empty() == false) result+= ", ";
			result+= "*." + extension;
		}
		return result;
	}

	/**
	 * Load settings
	 * @param application application
	 */
	static void loadSettings(Application* application);

};
