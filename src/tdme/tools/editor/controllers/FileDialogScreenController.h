#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/events/GUIFocusListener.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>

#include <tdme/tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUIChangeListener;
using agui::gui::events::GUIFocusListener;
using agui::gui::events::GUITooltipRequestListener;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using agui::utilities::MutableString;

using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Action;

/**
 * File dialog screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::FileDialogScreenController final
	: public ScreenController
	, public GUIActionListener
	, public GUIChangeListener
	, public GUIFocusListener
	, public GUITooltipRequestListener
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
	unique_ptr<Action> applyAction;
	unique_ptr<Action> cancelAction;
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
	 * @returns success
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
	 * @returns extension hash
	 */
	inline const string getExtensionHash() {
		string extensionHash = "|";
		for (const auto& extension: extensions) extensionHash+= extension + "|";
		if (extensions.empty() == true) extensionHash+= "|";
		return extensionHash;
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(FileDialogScreenController)

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
	inline GUIScreenNode* getScreenNode() override {
		return screenNode;
	}

	/**
	 * @returns default current working directory
	 */
	inline const string& getDefaultCWD() {
		return defaultCwd;
	}

	/**
	 * Set default current working directory
	 * @param defaultCWD default current working directory
	 */
	inline void setDefaultCWD(const string& defaultCwd) {
		this->defaultCwd = defaultCwd;
	}

	/**
	 * @returns path name
	 */
	inline const string& getPathName() {
		return cwd;
	}

	/**
	 * @returns file name
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
	 * @returns file image name
	 */
	static const string getFileImageName(const string& fileName);

};
