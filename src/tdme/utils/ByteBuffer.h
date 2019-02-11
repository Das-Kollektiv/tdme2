#pragma once

#include <vector>

#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Buffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/utils/IntBuffer.h>
#include <tdme/utils/ShortBuffer.h>

using std::vector;

using tdme::utils::Buffer;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;
using tdme::utils::ShortBuffer;

/**
 * Byte buffer class
 * @author Andreas Drewke
 */
class tdme::utils::ByteBuffer: public Buffer
{
public:
	/**
	 * Allocate byte buffer
	 */
	inline static ByteBuffer* allocate(int32_t capacity) {
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
	 * @param capacity capacity
	 */
	inline ByteBuffer(int32_t capacity) : Buffer(capacity) {
	}

	/**
	 * Public constructor
	 * @param data data
	 */
	inline ByteBuffer(vector<uint8_t>* data) : Buffer(data) {
	}
};
