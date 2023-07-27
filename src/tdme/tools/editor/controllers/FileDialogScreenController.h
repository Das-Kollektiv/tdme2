#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::controllers::ScreenController;
using tdme::utilities::Action;
using tdme::utilities::MutableString;

/**
 * File dialog screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::FileDialogScreenController final
	: public ScreenController
	, public virtual GUIActionListener
	, public virtual GUIChangeListener
	, public virtual GUIFocusListener
	, public virtual GUITooltipRequestListener
{

private:
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };
	string cwd;
	vector<string> extensions;
	string captionText;
	GUIElementNode* tabsHeaderNode { nullptr };
	GUIElementNode* pathNode { nullptr };
	GUIElementNode* fileNameNode { nullptr };
	GUIElementNode* filesNode { nullptr };
	GUIElementNode* recentsNode { nullptr };
	GUIElementNode* favoritesNode { nullptr };
	GUIElementNode* drivesNode { nullptr };
	GUIElementNode* typeDropDownNode { nullptr };
	Action* applyAction { nullptr };
	Action* cancelAction { nullptr };
	vector<string> fileList;
	bool enableFilter { false };
	bool filtered { false };
	vector<string> favorites;
	vector<string> recents;
	string defaultCwd;
	unordered_map<string, string> defaultCwdByExtensions;
	string settingsPathName;
	string settingsFileName;

	/**
	 * Set up files
	 * @return success
	 */
	bool setupFiles();

	/**
	 * Set up files
	 * @param fileNameList file name list
	 * @param selectedFileName selected file name
	 */
	void setupFiles(const vector<string>& fileNameList, const string& selectedFileName = string());

	/**
	 * Set up favorites
	 */
	void setupFavorites();

	/**
	 * Set up recent
	 */
	void setupRecents();

	/**
	 * Set up drives
	 */
	void setupDrives();

	/**
	 * @return extension hash
	 */
	inline const string getExtensionHash() {
		string extensionHash = "|";
		for (auto& extension: extensions) extensionHash+= extension + "|";
		if (extensions.empty() == true) extensionHash+= "|";
		return extensionHash;
	}

public:
	// forbid class copy
	CLASS_FORBID_COPY(FileDialogScreenController)

	/**
	 * Public constructor
	 * @param popUps pop ups
	 */
	FileDialogScreenController(PopUps* popUps);

	/**
	 * Destructor
	 */
	virtual ~FileDialogScreenController();

	// overridden methods
	GUIScreenNode* getScreenNode() override;

	/**
	 * @return default current working directory
	 */
	inline const string& getDefaultCWD() {
		return defaultCwd;
	}

	/**
	 * Set default current working directory
	 * @param defaultCWD default current working directory
	 */
	void setDefaultCWD(const string& defaultCwd);

	/**
	 * @return path name
	 */
	const string& getPathName();

	/**
	 * @return file name
	 */
	const string getFileName();

	/**
	 * Shows the file dialog pop up
	 * @param cwd current working directory
	 * @param captionText caption text
	 * @param extensions extensions
	 * @param fileName file name
	 * @param enableFilter enable filter
	 * @param applyAction apply action
	 * @param cancelAction cancel action
	 * @param settingsFileName settings file name
	 * @param settingsPathName settings path name
	 * @throws IOException
	 */
	void show(const string& cwd, const string& captionText, const vector<string>& extensions, const string& fileName, bool enableFilter, Action* applyAction, Action* cancelAction = nullptr, const string& settingsFileName = ".filedialog.properties", const string& settingsPathName = string());

	/**
	 * Abort the file dialog pop up
	 */
	void close();

	// overridden methods
	void initialize() override;
	void dispose() override;
	void onChange(GUIElementNode* node) override;
	void onAction(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) override;
	void onTooltipCloseRequest() override;

	/**
	 * Load settings
	 */
	void loadSettings();

	/**
	 * Save settings
	 */
	void saveSettings();

	/**
	 * Get file image name
	 * @param fileName file name
	 * @return file image name
	 */
	static const string getFileImageName(const string& fileName);

};
