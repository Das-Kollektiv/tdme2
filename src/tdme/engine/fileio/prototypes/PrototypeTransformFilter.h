#pragma once

#include <tdme/engine/fileio/prototypes/fwd-tdme.h>

#include <tdme/engine/prototype/BaseProperties.h>

using tdme::engine::prototype::BaseProperties;

/**
 * Prototype transform filter
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::fileio::prototypes::PrototypeTransformFilter
{
	/**
	 * Filter a prototype to be transformed to a empty depending on its properties
	 * @param properties properties
	 * @return true if prototype should be transformed to a empty
	 */
	virtual bool filterEmptyTransform(BaseProperties& properties) = 0;

	/**
	 * Destructor
	 */
	virtual ~PrototypeTransformFilter() {}
};
