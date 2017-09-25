// Generated from /tdme/src/tdme/gui/elements/GUISelectBox.java

#pragma once

#include <map>
#include <string>

#include <java/lang/fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/elements/GUIElement.h>
#include <tdme/os/_FileSystemException.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUIElement;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystemException;

struct default_init_tag;

/** 
 * GUI select box
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUISelectBox final
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
	 * @throws file system exception
	 */
	void ctor() throw (_FileSystemException);

public:
	const wstring& getName() override;
	const wstring& getTemplate() override;
	map<wstring, wstring>* getAttributes(GUIScreenNode* screenNode) override;
	GUINodeController* createController(GUINode* node) override;

	// Generated
	GUISelectBox() throw (_FileSystemException);
protected:
	GUISelectBox(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
