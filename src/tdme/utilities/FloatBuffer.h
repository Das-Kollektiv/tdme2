#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Buffer.h>

using std::array;

using tdme::utilities::Buffer;

/**
 * Float buffer class
 * @author Andreas Drewke
 */
class tdme::utilities::FloatBuffer final: public Buffer
{
public:
	/**
	 * Default constructor
	 */
	FloatBuffer() : Buffer() {
	}

	/**
	 * Public constructor
	 * @param buffer buffer
	 */
	FloatBuffer(Buffer* buffer) : Buffer() {
		this->ownsBuffer = false;
		this->buffer = buffer->buffer;
	}

	/**
	 * @returns capacity
	 */
	inline virtual int64_t getCapacity() {
		return Buffer::getCapacity() / sizeof(float);
	}

	/**
	 * @returns position
	 */
	inline virtual int64_t getPosition() {
		return Buffer::getPosition() / sizeof(float);
	}

	/**
	 * Get a value at given position
	 * @param position position
	 * @returns value at given position
	 */
	inline float get(int64_t position) {
		uint32_t floatAsInt = 0;
		floatAsInt+= (uint32_t)Buffer::get(position);
		floatAsInt+= (uint32_t)Buffer::get(position + 1) << 8;
		floatAsInt+= (uint32_t)Buffer::get(position + 2) << 16;
		floatAsInt+= (uint32_t)Buffer::get(position + 3) << 24;
		return *((float*)&floatAsInt);
	}

	/**
	 * Put a float value into float buffer
	 * @param value value
	 */
	inline FloatBuffer* put(float value) {
		Buffer::put((const uint8_t*)&value, sizeof(float));
		return this;
	}

	/**
	 * Put float values into float buffer
	 * @param values values
	 */
	inline FloatBuffer* put(const array<float, 2>& values) {
		Buffer::put((const uint8_t*)values.data(), 2 * sizeof(float));
		return this;
	}

	/**
	 * Put float values into float buffer
	 * @param values values
	 */
	inline FloatBuffer* put(const array<float, 3>& values) {
		Buffer::put((const uint8_t*)values.data(), 3 * sizeof(float));
		return this;
	}

	/**
	 * Put float values into float buffer
	 * @param values values
	 */
	inline FloatBuffer* put(const array<float, 4>& values) {
		Buffer::put((const uint8_t*)values.data(), 4 * sizeof(float));
		return this;
	}

	/**
	 * Put float values into float buffer
	 * @param values values
	 */
	inline FloatBuffer* put(const array<float, 16>& values) {
		Buffer::put((const uint8_t*)values.data(), 16 * sizeof(float));
		return this;
	}

};
