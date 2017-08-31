// Generated from /tdme/src/tdme/gui/elements/GUITabContent.java

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
using java::lang::String;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystemException;

struct default_init_tag;

/** 
 * GUI tab content element
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUITabContent final
	: public GUIElement
{

public:
	typedef GUIElement super;

private:
	static String* NAME;
	map<wstring, String*> attributes {  };
	String* template_ {  };
protected:

	/** 
	 * Constructor
	 */
	void ctor() throw (_FileSystemException);

public:
	String* getName() override;
	String* getTemplate() override;
	map<wstring, String*>* getAttributes(GUIScreenNode* screenNode) override;
	GUINodeController* createController(GUINode* node) override;

	// Generated
	GUITabContent() throw (_FileSystemException);
protected:
	GUITabContent(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
