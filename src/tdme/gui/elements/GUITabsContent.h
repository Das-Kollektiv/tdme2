#pragma once

#include <map>
#include <string>

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/elements/GUIElement.h>
#include <tdme/os/filesystem/_FileSystemException.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUIElement;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystemException;


struct default_init_tag;

/** 
 * GUI tabs content element
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUITabsContent final
	: public GUIElement
{

public:
	typedef GUIElement super;

private:
	static wstring NAME;
	map<wstring, wstring> attributes {  };
	wstring template_ {  };
protected:

	/** 
	 * Constructor
	 */
	void ctor() throw (_FileSystemException);

public:
	const wstring& getName() override;
	const wstring& getTemplate() override;
	map<wstring, wstring>* getAttributes(GUIScreenNode* screenNode) override;
	GUINodeController* createController(GUINode* node) override;

	// Generated
	GUITabsContent() throw (_FileSystemException);
protected:
	GUITabsContent(const ::default_init_tag&);
};
