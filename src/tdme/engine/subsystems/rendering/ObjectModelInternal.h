
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
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::ObjectModelInternal
	: public ObjectBase
{
public:
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
