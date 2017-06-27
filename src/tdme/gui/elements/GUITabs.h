// Generated from /tdme/src/tdme/gui/elements/GUITabs.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/elements/GUIElement.h>

using tdme::gui::elements::GUIElement;
using java::lang::String;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * GUI tabs element
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUITabs final
	: public GUIElement
{

public:
	typedef GUIElement super;

private:
	static String* NAME;
	_HashMap* attributes {  };
	String* template_ {  };
protected:

	/** 
	 * Constructor
	 */
	void ctor() /* throws(IOException) */;

public:
	String* getName() override;
	String* getTemplate() override;
	_HashMap* getAttributes(GUIScreenNode* screenNode) override;
	GUINodeController* createController(GUINode* node) override;

	// Generated
	GUITabs();
protected:
	GUITabs(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
