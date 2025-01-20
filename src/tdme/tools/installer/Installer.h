#pragma once

#include <memory>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/nodes/fwd-agui.h>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/installer/fwd-tdme.h>
#include <tdme/utilities/Properties.h>

using std::string;
using std::unique_ptr;
using std::vector;

using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUIChangeListener;
using agui::gui::nodes::GUIElementNode;

using tdme::application::Application;
using tdme::engine::Engine;
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
	unique_ptr<PopUps> popUps;
	enum Screen { SCREEN_WELCOME, SCREEN_LICENSE, SCREEN_CHECKFORUPDATE, SCREEN_COMPONENTS, SCREEN_PATH, SCREEN_INSTALLING, SCREEN_FINISHED, SCREEN_MAX, SCREEN_WELCOME2, SCREEN_UNINSTALLING  };
	enum InstallerMode { INSTALLERMODE_NONE, INSTALLERMODE_INSTALL, INSTALLERMODE_UNINSTALL, INSTALLERMODE_UPDATE, INSTALLERMODE_REPAIR };
	InstallerMode installerMode;
	volatile Screen screen;
	Properties installerProperties;
	string homePath;
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
	// forbid class copy
	FORBID_CLASS_COPY(Installer)

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
	 * @returns exit code
	 */
	static int main(int argc, char** argv);

};
