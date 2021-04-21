#pragma once

#include <string>
#include <vector>

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/controller/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/controller/ScreenController.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::views::EditorView;
using tdme::tools::shared::controller::ScreenController;
using tdme::utilities::MutableString;

/**
 * Editor screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::controller::EditorScreenController final
	: public ScreenController
	, public GUIActionListener
	, public GUIChangeListener
{
private:
	EditorView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	GUIParentNode* projectPathsScrollArea { nullptr };
	GUIParentNode* projectPathFilesScrollArea { nullptr };
	GUIParentNode* tabsHeader { nullptr };
	GUIParentNode* tabsContent { nullptr };
	string projectPath;
	vector<string> tabIds;

public:
	/**
	 * Public constructor
	 * @param view view
	 */
	EditorScreenController(EditorView* view);

	// overridden methods
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;

	/**
	 * Set screen caption
	 * @param text text
	 */
	void setScreenCaption(const string& text);

	// overridden methods
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;

	/**
	 * On open project
	 */
	void onOpenProject();

	/**
	 * Scan project paths
	 */
	void scanProjectPaths();

	/**
	 * Scan project paths
	 * @param path path
	 * @param xml xml
	 */
	void scanProjectPaths(const string& path, string& xml);

	/**
	 * Scan project path files
	 * @param relativeProjectPath relative project path
	 * @param xml xml
	 */
	void scanProjectPathFiles(const string& relativeProjectPath, string& xml);

	/**
	 * On open file
	 * @param relativeProjectFileName relative project file name
	 */
	void onOpenFile(const string& relativeProjectFileName);
	/**
	 * Get viewport rectangle
	 * @param left left
	 * @param top top
	 * @param width width
	 * @param height height
	 */
	void getViewPort(int& left, int& top, int& width, int& height);

	/**
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

	/**
	 * On quit
	 */
	void onQuit();
};
