#include <tdme/engine/subsystems/object/_Buffer.h>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/Console.h>

using tdme::engine::subsystems::object::_Buffer;
using tdme::utils::ByteBuffer;
using tdme::utils::Console;

_Buffer::_Buffer()
{
}

ByteBuffer* _Buffer::byteBuffer = nullptr;

ByteBuffer* _Buffer::getByteBuffer(int32_t bytes)
{
	if (byteBuffer == nullptr || bytes > byteBuffer->getCapacity()) {
		if (byteBuffer != nullptr) {
			delete byteBuffer;
		}
		byteBuffer = ByteBuffer::allocate(bytes);
	} else {
		byteBuffer->clear();
	}
	return byteBuffer;
}
