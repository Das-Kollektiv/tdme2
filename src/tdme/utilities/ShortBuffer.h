#pragma once

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Buffer.h>

using tdme::utilities::Buffer;

/**
 * Short buffer class
 * @author Andreas Drewke
 */
class tdme::utilities::ShortBuffer: public Buffer
{
public:
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

	/**
	 * @returns buffer capacity
	 */
	inline virtual int64_t getCapacity() {
		return Buffer::getCapacity() / sizeof(uint16_t);
	}

	/**
	 * @returns buffer position
	 */
	inline virtual int64_t getPosition() {
		return Buffer::getPosition() / sizeof(uint16_t);
	}

	/**
	 * Get a value at given position
	 * @param position position
	 */
	inline int16_t get(int64_t position) {
		uint16_t value = 0;
		value+= ((uint16_t)Buffer::get(position)) & 0xFF;
		value+= ((uint16_t)Buffer::get(position + 1) << 8) & 0xFF;
		return value;
	}

	/**
	 * Put a value into current position
	 * @param value value
	 */
	inline ShortBuffer* put(uint16_t value) {
		Buffer::put((const uint8_t*)&value, sizeof(uint16_t));
		return this;
	}

};
