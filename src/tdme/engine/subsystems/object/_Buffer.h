// Generated from /tdme/src/tdme/engine/subsystems/object/_Buffer.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>

using tdme::utils::ByteBuffer;

/** 
 * Buffer
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::_Buffer
{
private:
	static ByteBuffer* byteBuffer;

public: /* protected */

	/** 
	 * Get byte buffer
	 * @param bytes
	 * @return byte buffer
	 */
	static ByteBuffer* getByteBuffer(int32_t bytes);

	// Generated

public:
	/**
	 * Public constructor
	 */
	_Buffer();
};
