#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Buffer.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/IntBuffer.h>
#include <tdme/utilities/ShortBuffer.h>

using std::vector;

using tdme::utilities::Buffer;
using tdme::utilities::FloatBuffer;
using tdme::utilities::IntBuffer;
using tdme::utilities::ShortBuffer;

/**
 * Byte buffer class
 * @author Andreas Drewke
 */
class tdme::utilities::ByteBuffer: public Buffer
{
public:
	/**
	 * Allocate byte buffer
	 */
	inline static ByteBuffer* allocate(int64_t capacity) {
		return new ByteBuffer(capacity);
	}

	/**
	 * @return this buffer as float buffer
	 */
	inline FloatBuffer asFloatBuffer() {
		return FloatBuffer(this);
	}

	/**
	 * @return this buffer as int buffer
	 */
	inline IntBuffer asIntBuffer() {
		return IntBuffer(this);
	}

	/**
	 * @return this buffer as short buffer
	 */
	inline ShortBuffer asShortBuffer() {
		return ShortBuffer(this);
	}

public:

	/**
	 * Public constructor
	 */
	inline ByteBuffer() : Buffer(static_cast<Buffer*>(nullptr)) {
	}

	/**
	 * Public constructor
	 * @param capacity capacity
	 */
	inline ByteBuffer(int64_t capacity) : Buffer(capacity) {
	}

	/**
	 * Public constructor
	 * @param data data
	 */
	inline ByteBuffer(vector<uint8_t>* data) : Buffer(data) {
	}

	/**
	 * Public constructor
	 * @param bytebuffer byte buffer to use as underlying buffer
	 */
	inline ByteBuffer(ByteBuffer& byteBuffer) : Buffer(byteBuffer.buffer) {
	}
};
