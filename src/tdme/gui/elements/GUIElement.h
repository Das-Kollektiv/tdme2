#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unordered_map;

using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;

/**
 * GUI element base class
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIElement
{

public:
	/**
	 * Public constructor
	 */
	GUIElement();

	/**
	 * Destructor
	 */
	virtual ~GUIElement();

	/**
	 * @return name
	 */
	virtual const string& getName() = 0;

	/**
	 * Retrieve template from given path name and optional file name
	 * @param applicationPathName application path name
	 * @param applicationSubPathName sub path name which is usually "project" or "engine"
	 * @param fileName file name
	 * @throws tdme::os::filesystem::FileSystemException
	 * @return template
	 */
	virtual const string getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName = string()) = 0;

	/**
	 * Get default attributes
	 * @param screenNode screen node
	 * @return default attributes
	 */
	virtual unordered_map<string, string> getAttributes(GUIScreenNode* screenNode) = 0;

	/**
	 * Create controller which is attached to this node
	 * @param node node
	 * @return
	 */
	virtual GUINodeController* createController(GUINode* node) = 0;

};
