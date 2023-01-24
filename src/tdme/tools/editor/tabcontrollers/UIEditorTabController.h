#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIContextMenuRequestListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

#include <ext/tinyxml/tinyxml.h>

using std::string;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIContextMenuRequestListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::UIEditorTabView;
using tdme::utilities::MutableString;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

/**
 * UI editor tab controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::UIEditorTabController final
	: public TabController
{

private:
	UIEditorTabView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };
	string prototypeFileName;
	string prototypeMeshNode;
	string prototypeMeshAnimation;

	bool firstSearch { true };
	int searchIndex { -1 };

public:
	/**
	 * Public constructor
	 * @param view view
	 */
	UIEditorTabController(UIEditorTabView* view);

	/**
	 * Destructor
	 */
	virtual ~UIEditorTabController();

	/**
	 * Get view
	 */
	UIEditorTabView* getView();

	// overridden method
	GUIScreenNode* getScreenNode() override;

	// overridden methods
	void initialize(GUIScreenNode* screenNode) override;
	void dispose() override;
	void onChange(GUIElementNode* node) override;
	void onAction(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) override;
	void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) override;
	void onTooltipCloseRequest() override;
	void onCommand(TabControllerCommand command) override;
	void onDrop(const string& payload, int mouseX, int mouseY) override;

	/**
	 * Create outliner GUI parent node nodes xml
	 * @param xmlParentNode XML parent node
	 * @param xml xml
	 * @param screenIdx screen index
	 * @param nodeIdx node index
	 */
	void createOutlinerParentNodeNodesXML(TiXmlElement* xmlParentNode, string& xml, int screenIdx, int& nodeIdx);

	/**
	 * Set outliner content
	 */
	void setOutlinerContent();

	/**
	 * Set outliner add drop down content
	 */
	void setOutlinerAddDropDownContent();

	/**
	 * Update details panel
	 * @param outlinerNode outliner node
	 */
	void updateDetails(const string& outlinerNode);

	/**
	 * Update screen details
	 */
	void updateScreenDetails();

	/**
	 * Update screens details
	 */
	void updateScreensDetails();

	/**
	 * On load screen
	 */
	void onLoadScreen();

	/**
	 * On remove screen
	 */
	void onUnsetScreen();

	/**
	 * On browse to screen
	 */
	void onBrowseToScreen();

	/**
	 * Reload screens
	 */
	void reloadScreens();

	/**
	 * On load prototype
	 */
	void onLoadPrototype();

	/**
	 * On load prototype
	 */
	void onRemovePrototype();

	/**
	 * On browse to prototype
	 */
	void onBrowseToPrototype();

	/**
	 * Set screen
	 * @param screenIdx screen index
	 * @param fileName file name
	 */
	void setScreen(int screenIdx, const string& fileName);

	/**
	 * Set prototype
	 * @param pathName path name
	 * @param fileName file name
	 * @param modelMeshNode model mesh node
	 * @param modelMeshAnimation model mesh animation
	 */
	void setPrototype(const string& pathName, const string& fileName, const string& modelMeshNode, const string& modelMeshAnimation);

	/**
	 * Close find/replace window
	 */
	void closeFindReplaceWindow();

	/**
	 * Save
	 */
	void save();

	/**
	 * Save as
	 */
	void saveAs();

	/**
	 * Show the information pop up / modal
	 * @param caption caption
	 * @param message message
	 */
	void showInfoPopUp(const string& caption, const string& message);

};
