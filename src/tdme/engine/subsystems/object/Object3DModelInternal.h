// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DModelInternal.java

#pragma once

#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/object/Object3DBase.h>

using tdme::engine::subsystems::object::Object3DBase;
using tdme::engine::model::Model;


struct default_init_tag;

/** 
 * Object 3D Model
 * To be used in non engine context
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::Object3DModelInternal
	: public Object3DBase
{

public:
	typedef Object3DBase super;
protected:

	/** 
	 * Public constructor
	 * @param model
	 */
	void ctor(Model* model);

	// Generated

public:
	Object3DModelInternal(Model* model);
protected:
	Object3DModelInternal(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
