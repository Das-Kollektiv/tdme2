#pragma once

#include <map>
#include <string>

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/elements/GUIElement.h>
#include <tdme/os/filesystem/FileSystemException.h>

using std::map;
using std::string;

using tdme::gui::elements::GUIElement;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystemException;

/** 
 * GUI radio button element
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUIRadioButton final: public GUIElement
{

private:
	static string NAME;
	map<string, string> attributes {  };
	string template_ {  };

public:
	const string& getName() override;
	const string& getTemplate() override;
	map<string, string>* getAttributes(GUIScreenNode* screenNode) override;
	GUINodeController* createController(GUINode* node) override;

	GUIRadioButton() throw (FileSystemException);
};
