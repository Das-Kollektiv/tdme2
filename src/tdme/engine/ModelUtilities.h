// Generated from /tdme/src/tdme/engine/ModelUtilities.java

#pragma once

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/object/ModelUtilitiesInternal.h>

using tdme::engine::subsystems::object::ModelUtilitiesInternal;


struct default_init_tag;

/** 
 * Model Utilities
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::ModelUtilities final
	: public ModelUtilitiesInternal
{

public:
	typedef ModelUtilitiesInternal super;

	// Generated
	ModelUtilities();
protected:
	ModelUtilities(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
