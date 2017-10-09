#pragma once

#include <map>
#include <string>

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/elements/GUIElement.h>
#include <tdme/os/filesystem/FileSystemException.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUIElement;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystemException;

/** 
 * GUI Checkbox
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUIRadioButton final
	: public GUIElement
{

private:
	static wstring NAME;
	map<wstring, wstring> attributes {  };
	wstring template_ {  };

public:
	const wstring& getName() override;
	const wstring& getTemplate() override;
	map<wstring, wstring>* getAttributes(GUIScreenNode* screenNode) override;
	GUINodeController* createController(GUINode* node) override;

	GUIRadioButton() throw (FileSystemException);
};
