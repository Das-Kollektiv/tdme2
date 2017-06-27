// Generated from /tdme/src/tdme/gui/nodes/GUINodeConditions.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * GUI node conditions
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUINodeConditions final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	_ArrayList* conditions {  };
protected:

	/** 
	 * Constructor
	 */
	void ctor();

public:

	/** 
	 * @return conditions
	 */
	_ArrayList* getConditions();

	/** 
	 * Add a condition
	 * @param condition
	 */
	void add(String* condition);

	/** 
	 * Remove a condition
	 * @param condition
	 */
	void remove(String* condition);

	/** 
	 * Remove all
	 */
	void removeAll();
	String* toString() override;

	// Generated
	GUINodeConditions();
protected:
	GUINodeConditions(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
