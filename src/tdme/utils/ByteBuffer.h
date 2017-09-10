#// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <vector>

#include <fwd-tdme.h>

using std::vector;

using tdme::utils::Buffer;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;
using tdme::utils::ShortBuffer;

class tdme::utils::ByteBuffer
	: public Buffer
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
	inline FloatBuffer* asFloatBuffer() {
		return new FloatBuffer(this);
	}

	/**
	 * @return this buffer as int buffer
	 */
	inline IntBuffer* asIntBuffer() {
		return new IntBuffer(this);
	}

	/**
	 * @return this buffer as short buffer
	 */
	inline ShortBuffer* asShortBuffer() {
		return new ShortBuffer(this);
	}

public:
	/**
	 * Public constructor
	 * @param capacity
	 */
	inline ByteBuffer(int32_t capacity) {
		Buffer::Buffer(capacity);
	}

	/**
	 * Public constructor
	 * @param capacity
	 * @param data
	 */
	inline ByteBuffer(int32_t _capacity, vector<uint8_t>* data) {
		Buffer::Buffer(capacity, data);
	}
};
