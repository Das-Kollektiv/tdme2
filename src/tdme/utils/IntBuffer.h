#pragma once

#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Buffer.h>

using tdme::utils::Buffer;

class tdme::utils::IntBuffer
	: public Buffer
{
public:
	/**
	 * @return capacity
	 */
	inline virtual int32_t getCapacity() {
		return Buffer::getCapacity() / sizeof(int32_t);
	}

	/**
	 * @return position
	 */
	inline virtual int32_t getPosition() {
		return Buffer::getPosition() / sizeof(int32_t);
	}

	/**
	 * Get a value at given position
	 * @param position position
	 */
	inline int32_t get(int32_t position) {
		int32_t value = 0;
		value+= ((int32_t)Buffer::get(position)) & 0xFF;
		value+= ((int32_t)Buffer::get(position + 1) << 8) & 0xFF;
		value+= ((int32_t)Buffer::get(position + 2) << 16) & 0xFF;
		value+= ((int32_t)Buffer::get(position + 3) << 24) & 0xFF;
		return value;
	}

	/**
	 * Puts a value into buffer at its current position
	 * @param value value
	 */
	inline IntBuffer* put(int32_t value) {
		int8_t* intAsInt8 = ((int8_t*)&value);
		Buffer::put(intAsInt8[0]);
		Buffer::put(intAsInt8[1]);
		Buffer::put(intAsInt8[2]);
		Buffer::put(intAsInt8[3]);
		return this;
	}

	/**
	 * Default constructor
	 */
	IntBuffer() : Buffer(static_cast<Buffer*>(nullptr)) {
	}

	/**
	 * Public constructor
	 */
	inline IntBuffer(Buffer* buffer) : Buffer(buffer) {
	}

};
