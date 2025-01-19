#pragma once

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Buffer.h>

using tdme::utilities::Buffer;

/**
 * Integer buffer class
 * @author Andreas Drewke
 */
class tdme::utilities::IntBuffer final: public Buffer
{
public:
	/**
	 * Default constructor
	 */
	IntBuffer() : Buffer() {
	}

	/**
	 * Public constructor
	 */
	inline IntBuffer(Buffer* buffer) : Buffer() {
		this->ownsBuffer = false;
		this->buffer = buffer->buffer;
	}

	/**
	 * @returns capacity
	 */
	inline virtual int64_t getCapacity() {
		return Buffer::getCapacity() / sizeof(uint32_t);
	}

	/**
	 * @returns position
	 */
	inline virtual int64_t getPosition() {
		return Buffer::getPosition() / sizeof(uint32_t);
	}

	/**
	 * Get a value at given position
	 * @param position position
	 */
	inline uint32_t get(int64_t position) {
		uint32_t value = 0;
		value+= ((uint32_t)Buffer::get(position)) & 0xFF;
		value+= ((uint32_t)Buffer::get(position + 1) << 8) & 0xFF;
		value+= ((uint32_t)Buffer::get(position + 2) << 16) & 0xFF;
		value+= ((uint32_t)Buffer::get(position + 3) << 24) & 0xFF;
		return value;
	}

	/**
	 * Puts a value into buffer at its current position
	 * @param value value
	 */
	inline IntBuffer* put(uint32_t value) {
		Buffer::put((const uint8_t*)&value, sizeof(uint32_t));
		return this;
	}

};
