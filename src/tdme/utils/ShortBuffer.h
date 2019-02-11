#pragma once

#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Buffer.h>

using tdme::utils::Buffer;

/**
 * Short buffer class
 * @author Andreas Drewke
 */
class tdme::utils::ShortBuffer: public Buffer
{
public:
	/**
	 * @returns buffer capacity
	 */
	inline virtual int32_t getCapacity() {
		return Buffer::getCapacity() / sizeof(int16_t);
	}

	/**
	 * @returns buffer position
	 */
	inline virtual int32_t getPosition() {
		return Buffer::getPosition() / sizeof(int16_t);
	}

	/**
	 * Get a value at given position
	 * @param position position
	 */
	inline int16_t get(int32_t position) {
		int16_t value = 0;
		value+= ((int16_t)Buffer::get(position)) & 0xFF;
		value+= ((int16_t)Buffer::get(position + 1) << 8) & 0xFF;
		return value;
	}

	/**
	 * Put a value into current position
	 * @param value value
	 */
	inline ShortBuffer* put(int16_t value) {
		int8_t* shortAsInt8 = ((int8_t*)&value);
		Buffer::put(shortAsInt8[0]);
		Buffer::put(shortAsInt8[1]);
		return this;
	}

	/**
	 * Default constructor
	 */
	ShortBuffer() : Buffer(static_cast<Buffer*>(nullptr)) {
	}

	/**
	 * Public constructor
	 * @param buffer buffer
	 */
	ShortBuffer(Buffer* buffer) : Buffer(buffer) {
	}
};
