#pragma once

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>

using std::string;
using std::unordered_map;

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::nodes::GUINodeController;
	using ::agui::gui::nodes::GUIScreenNode;
}
}
}

/**
 * GUI element base class
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIElement
{

public:
	// forbid class copy
	FORBID_CLASS_COPY(GUIElement)

	/**
	 * Public constructor
	 */
	inline GUIElement() {}

	/**
	 * Destructor
	 */
	virtual ~GUIElement() {}

	/**
	 * @returns name
	 */
	virtual const string& getName() = 0;

	/**
	 * Retrieve template from given path name and optional file name
	 * @param applicationPathName application path name
	 * @param applicationSubPathName sub path name which is usually "project" or "engine"
	 * @param fileName file name
	 * @throws agui::os::filesystem::FileSystemException
	 * @returns template
	 */
	virtual const string getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName = string()) = 0;

	/**
	 * Get default attributes
	 * @param screenNode screen node
	 * @returns default attributes
	 */
	virtual unordered_map<string, string> getAttributes(GUIScreenNode* screenNode) = 0;

	/**
	 * Create controller which is attached to this node
	 * @param node node
	 * @returns
	 */
	virtual GUINodeController* createController(GUINode* node) = 0;

};
