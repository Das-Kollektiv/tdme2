// Generated from /tdme/src/tdme/engine/subsystems/object/_Buffer.java

#pragma once

#include <fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::nio::ByteBuffer;


struct default_init_tag;

/** 
 * Buffer
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::_Buffer
	: public virtual Object
{

public:
	typedef Object super;

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
	_Buffer();
protected:
	_Buffer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
