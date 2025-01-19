#pragma once

#include <agui/agui.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/Buffer.h>

/**
 * Short buffer class
 * @author Andreas Drewke
 */
class agui::utilities::ShortBuffer final: public Buffer
{
public:
	/**
	 * Default constructor
	 */
	ShortBuffer() : Buffer() {
	}

	/**
	 * Public constructor
	 * @param buffer buffer
	 */
	ShortBuffer(Buffer* buffer) : Buffer() {
		this->ownsBuffer = false;
		this->buffer = buffer->buffer;
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
