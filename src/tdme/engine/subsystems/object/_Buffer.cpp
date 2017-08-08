// Generated from /tdme/src/tdme/engine/subsystems/object/_Buffer.java
#include <tdme/engine/subsystems/object/_Buffer.h>

#include <java/nio/ByteBuffer.h>
#include <tdme/utils/_Console.h>

using tdme::engine::subsystems::object::_Buffer;
using java::nio::ByteBuffer;
using java::nio::ByteOrder;
using tdme::utils::_Console;

_Buffer::_Buffer()
{
}

ByteBuffer* _Buffer::byteBuffer = nullptr;

ByteBuffer* _Buffer::getByteBuffer(int32_t bytes)
{
	if (byteBuffer == nullptr || bytes > byteBuffer->capacity()) {
		if (byteBuffer != nullptr) {
			delete byteBuffer;
		}
		byteBuffer = ByteBuffer::allocateDirect(bytes);
	} else {
		byteBuffer->clear();
	}
	return byteBuffer;
}
