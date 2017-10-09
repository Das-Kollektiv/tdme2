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
	/**
	 * Public constructor
	 * @param model
	 */
	Object3DModel(Model* model);
};
