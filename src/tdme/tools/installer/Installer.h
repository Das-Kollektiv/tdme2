#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/installer/fwd-tdme.h>
#include <tdme/utilities/Properties.h>

using std::string;
using std::vector;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::os::filesystem::ArchiveFileSystem;
using tdme::os::threading::Mutex;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Properties;

/**
 * Installer
 * @author Andreas Drewke
 */
class tdme::tools::installer::Installer final
	: public virtual Application, public virtual GUIActionListener, public virtual GUIChangeListener
{
private:
	Engine* engine { nullptr };
	PopUps* popUps { nullptr };
	enum Screen { SCREEN_WELCOME, SCREEN_LICENSE, SCREEN_CHECKFORUPDATE, SCREEN_COMPONENTS, SCREEN_PATH, SCREEN_INSTALLING, SCREEN_FINISHED, SCREEN_MAX, SCREEN_WELCOME2, SCREEN_UNINSTALLING  };
	enum InstallerMode { INSTALLERMODE_NONE, INSTALLERMODE_INSTALL, INSTALLERMODE_UNINSTALL, INSTALLERMODE_UPDATE, INSTALLERMODE_REPAIR };
	InstallerMode installerMode;
	volatile Screen screen;
	Properties installerProperties;
	string homeFolder;
	Mutex installThreadMutex;
	bool installed;
	string timestamp;
	bool remountInstallerArchive;
	vector<string> downloadedFiles;

	/**
	 * Mount installer file system
	 */
	static void mountInstallerFileSystem(const string& timestamp = string(), bool remountInstallerArchive = false);

	/**
	 * Initialize screens
	 */
	void initializeScreens();

	/**
	 * Perform screen action
	 */
	void performScreenAction();

	/**
	 * Scan archive file system
	 * @oaram archive archive file system
	 * @param totalFiles total files
	 * @param pathName path name
	 */
	static void scanArchive(ArchiveFileSystem* archiveFileSystem, vector<string>& totalFiles, const string& pathName = string());

	/**
	 * Create a path recursively
	 * @param pathName path name
	 */
	static void createPathRecursively(const string& pathName);
public:
	/**
	 * Public constructor
	 */
	Installer();

	// overridden methods
	void initialize() override;
	void dispose() override;
	void reshape(int width, int height) override;
	void display() override;
	void onClose() override;
	void onAction(GUIActionListenerType type, GUIElementNode* node) override;
	void onChange(GUIElementNode* node) override;

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

};
