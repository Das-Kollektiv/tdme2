#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>

using tdme::engine::subsystems::manager::TextureManager;

using std::string;

/** 
 * Managed texture entity
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::TextureManager_TextureManaged
{
	friend class TextureManager;
private:
	string id {  };
	int32_t rendererId {  };
	int32_t referenceCounter {  };
private:

	/** 
	 * @return texture id
	 */
	const string& getId();

	/** 
	 * @return texture renderer id
	 */
	int32_t getRendererId();

	/** 
	 * @return reference counter
	 */
	int32_t getReferenceCounter();

	/** 
	 * decrement reference counter
	 * @return if reference counter = 0
	 */
	bool decrementReferenceCounter();

	/** 
	 * increment reference counter
	 */
	void incrementReferenceCounter();

	/**
	 * Protected constructor
	 * @param id id
	 * @param rendererId renderer id
	 */
	TextureManager_TextureManaged(const string& id, int32_t rendererId);
};
