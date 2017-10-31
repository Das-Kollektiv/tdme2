
#pragma once

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>

using tdme::utils::ByteBuffer;

/** 
 * Buffer
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::ObjectBuffer
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

};
