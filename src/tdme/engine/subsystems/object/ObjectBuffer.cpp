#include <tdme/engine/subsystems/object/ObjectBuffer.h>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/Console.h>

using tdme::engine::subsystems::object::ObjectBuffer;
using tdme::utils::ByteBuffer;
using tdme::utils::Console;

ByteBuffer* ObjectBuffer::byteBuffer = nullptr;

ByteBuffer* ObjectBuffer::getByteBuffer(int32_t bytes)
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
