// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DModelInternal.java

#pragma once

#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/object/Object3DBase.h>

using tdme::engine::subsystems::object::Object3DBase;
using tdme::engine::model::Model;

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
	/**
	 * Public constructor
	 * @param model
	 */
	Object3DModelInternal(Model* model);
};
