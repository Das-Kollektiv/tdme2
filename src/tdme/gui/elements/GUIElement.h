// Generated from /tdme/src/tdme/gui/elements/GUIElement.java

#pragma once

#include <map>
#include <string>

#include <java/lang/fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::map;
using std::wstring;

using java::lang::Object;
using java::lang::String;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;


struct default_init_tag;

/** 
 * GUI element
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUIElement
	: public virtual Object
{

public:
	typedef Object super;

	/** 
	 * @return name
	 */
	virtual String* getName() = 0;

	/** 
	 * @return template
	 */
	virtual String* getTemplate() = 0;

	/** 
	 * Get default attributes
	 * @param screen node
	 * @return default attributes
	 */
	virtual map<wstring, String*>* getAttributes(GUIScreenNode* screenNode) = 0;

	/** 
	 * Create controller which is attached to this node
	 * @param node
	 * @return
	 */
	virtual GUINodeController* createController(GUINode* node) = 0;

	// Generated
	GUIElement();
protected:
	GUIElement(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
