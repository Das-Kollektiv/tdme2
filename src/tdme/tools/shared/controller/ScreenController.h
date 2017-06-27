// Generated from /tdme/src/tdme/tools/shared/controller/ScreenController.java

#pragma once

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::gui::nodes::GUIScreenNode;


struct default_init_tag;

/** 
 * Screen controller, which connects GUI screen definition with code
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::ScreenController
	: public virtual Object
{

public:
	typedef Object super;

	/** 
	 * @return screen node
	 */
	virtual GUIScreenNode* getScreenNode() = 0;

	/** 
	 * Init
	 */
	virtual void initialize() = 0;

	/** 
	 * Dispose
	 */
	virtual void dispose() = 0;

	// Generated
	ScreenController();
protected:
	ScreenController(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
