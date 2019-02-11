#pragma once

#include <array>

#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Buffer.h>

using std::array;

using tdme::utils::Buffer;

/**
 * Float buffer class
 * @author Andreas Drewke
 */
class tdme::utils::FloatBuffer: public Buffer
{
public:
	/**
	 * @return capacity
	 */
	inline virtual int32_t getCapacity() {
		return Buffer::getCapacity() / sizeof(float);
	}

	/**
	 * @return position
	 */
	inline virtual int32_t getPosition() {
		return Buffer::getPosition() / sizeof(float);
	}

	/**
	 * Get a value at given position
	 * @param position position
	 * @return value at given position
	 */
	inline float get(int32_t position) {
		int floatAsInt = 0;
		floatAsInt+= (int32_t)Buffer::get(position);
		floatAsInt+= (int32_t)Buffer::get(position + 1) << 8;
		floatAsInt+= (int32_t)Buffer::get(position + 2) << 16;
		floatAsInt+= (int32_t)Buffer::get(position + 3) << 24;
		return *((float*)&floatAsInt);
	}

	/**
	 * Put a float value into float buffer
	 * @param value value
	 */
	inline FloatBuffer* put(float value) {
		uint8_t* floatAsInt8 = ((uint8_t*)&value);
		Buffer::put(floatAsInt8[0]);
		Buffer::put(floatAsInt8[1]);
		Buffer::put(floatAsInt8[2]);
		Buffer::put(floatAsInt8[3]);
		return this;
	}

	/**
	 * Put float values into float buffer
	 * @param values values
	 */
	inline FloatBuffer* put(const array<float, 2>& values) {
		for (int i = 0; i < values.size(); i++) {
			put(values[i]);
		}
		return this;
	}

	/**
	 * Put float values into float buffer
	 * @param values values
	 */
	inline FloatBuffer* put(array<float, 3>& values) {
		for (int i = 0; i < values.size(); i++) {
			put(values[i]);
		}
		return this;
	}

	/**
	 * Put float values into float buffer
	 * @param values values
	 */
	inline FloatBuffer* put(array<float, 4>& values) {
		for (int i = 0; i < values.size(); i++) {
			put(values[i]);
		}
		return this;
	}

	/**
	 * Put float values into float buffer
	 * @param values values
	 */
	inline FloatBuffer* put(array<float, 16>& values) {
		for (int i = 0; i < values.size(); i++) {
			put(values[i]);
		}
		return this;
	}

public:
	/**
	 * Default constructor
	 */
	FloatBuffer() : Buffer(static_cast<Buffer*>(nullptr)) {
	}

	/**
	 * Public constructor
	 * @param buffer buffer
	 */
	FloatBuffer(Buffer* buffer) : Buffer(buffer) {
	}

};
