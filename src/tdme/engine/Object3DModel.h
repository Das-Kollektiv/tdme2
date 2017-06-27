// Generated from /tdme/src/tdme/engine/Object3DModel.java

#pragma once

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/Object3DModelInternal.h>

using tdme::engine::subsystems::object::Object3DModelInternal;
using tdme::engine::model::Model;


struct default_init_tag;

/** 
 * Object 3D model
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Object3DModel final
	: public Object3DModelInternal
{

public:
	typedef Object3DModelInternal super;
protected:

	/** 
	 * Public constructor
	 * @param model
	 */
	void ctor(Model* model);

	// Generated

public:
	Object3DModel(Model* model);
protected:
	Object3DModel(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
