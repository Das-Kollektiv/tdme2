#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectModelInternal.h>

using tdme::engine::model::Model;
using tdme::engine::subsystems::rendering::ObjectModelInternal;

/**
 * Object model
 * @author Andreas Drewke
 */
class tdme::engine::ObjectModel final
	: public ObjectModelInternal
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(ObjectModel)

	/**
	 * Public constructor
	 * @param model model
	 */
	ObjectModel(Model* model);
};
