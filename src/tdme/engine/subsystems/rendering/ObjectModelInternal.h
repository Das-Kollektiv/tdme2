
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectBase.h>

using tdme::engine::model::Model;
using tdme::engine::subsystems::rendering::ObjectBase;

/**
 * Object model
 * To be used in non engine context
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::ObjectModelInternal
	: public ObjectBase
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(ObjectModelInternal)

	/**
	 * Public constructor
	 * @param model model
	 */
	ObjectModelInternal(Model* model);

	/**
	 * Destructor
	 */
	~ObjectModelInternal();
};
