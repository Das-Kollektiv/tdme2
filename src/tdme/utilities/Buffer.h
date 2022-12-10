#pragma once

#include <tdme/tdme.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/fwd-tdme.h>

#include <string>
#include <cstring>
#include <vector>

using std::memcpy;
using std::vector;

using tdme::math::Math;

/**
 * Base class of buffers
 * @author Andreas Drewke
 */
class tdme::utilities::Buffer
{
protected:
	bool createdBuffer;
	mutable int64_t position { 0 };
	vector<uint8_t>* buffer { nullptr };

public:
	/**
	 * Assignment operator
	 * @param buffer buffer
	 * @return this buffer
	 */
	inline Buffer& operator=(const Buffer& buffer) {
		this->createdBuffer = buffer.createdBuffer;
		this->position = buffer.position;
		if (createdBuffer == true) {
			if (buffer.buffer != nullptr) {
				this->buffer = new vector<uint8_t>(0);
				*this->buffer = *buffer.buffer;
			}
		} else {
			this->buffer = buffer.buffer;
		}
		return *this;
	}

	/**
	 * Copy constructor
	 * @param buffer buffer
	 */
	inline Buffer(const Buffer& buffer) {
		this->createdBuffer = buffer.createdBuffer;
		this->position = buffer.position;
		if (createdBuffer == true) {
			if (buffer.buffer != nullptr) {
				this->buffer = new vector<uint8_t>(0);
				*this->buffer = *buffer.buffer;
			}
		} else {
			this->buffer = buffer.buffer;
		}
	}

	/**
	 * Public constructor
	 * @param capacity capacity
	 */
	inline Buffer(int64_t capacity) {
		this->createdBuffer = true;
		this->position = 0;
		this->buffer = new vector<uint8_t>(capacity);
	}

	/**
	 * Public constructor
	 * @param buffer buffer
	 */
	inline Buffer(Buffer* buffer) {
		this->createdBuffer = false;
		this->position = 0;
		this->buffer = buffer == nullptr?nullptr:buffer->buffer;
	}

	/**
	 * Public constructor
	 * @param data data
	 */
	inline Buffer(vector<uint8_t>* data) {
		this->createdBuffer = false;
		this->position = 0;
		this->buffer = data;
	}

	/**
	 * Public constructor
	 * @param data data
	 */
	inline Buffer(const vector<uint8_t>& data) {
		this->createdBuffer = true;
		this->position = 0;
		this->buffer = new vector<uint8_t>(0);
		*this->buffer = data;
	}

	/**
	 * Destructor
	 */
	inline virtual ~Buffer() {
		if (createdBuffer == true && buffer != nullptr) {
			delete buffer;
		}
	}

	/**
	 * Clear
	 */
	inline Buffer* clear() {
		position = 0;
		return this;
	}

	/**
	 * @returns capacity
	 */
	inline virtual int64_t getCapacity() const {
		return buffer->size();
	}

	/**
	 * @returns position
	 */
	inline virtual int64_t getPosition() const {
		return position;
	}

	/**
	 * Set position
	 * @param position position
	 * @returns pointer to this buffer
	 */
	inline virtual Buffer* setPosition(int64_t position) {
		this->position = position;
		return this;
	}

	/**
	 * @returns value at given position
	 * @param position position
	 */
	inline uint8_t get(int64_t position) const {
		return (*buffer)[position];
	}

	/**
	 * Put value into buffer
	 * @param value value
	 */
	inline Buffer* put(uint8_t value) {
		(*buffer)[position++] = value;
		return this;
	}

	/**
	 * Put data into buffer
	 * @param data pointer to data
	 * @param size to put
	 * @returns pointer to this buffer
	 */
	inline Buffer* put(const uint8_t* data, int64_t size) {
		auto sizeUsed = Math::min(size, buffer->size() - position);
		memcpy(&(*buffer)[position], data, sizeUsed);
		position+= sizeUsed;
		return this;
	}

	/**
	 * @returns const pointer to underlying data vector
	 */
	inline const vector<uint8_t>* getBufferVector() const {
		return buffer;
	}

	/**
	 * @returns pointer to underlying data vector
	 */
	inline vector<uint8_t>* getBufferVector() {
		return buffer;
	}

	/**
	 * @returns const pointer to underlying data
	 */
	inline const uint8_t* getBuffer() const {
		return buffer->data();
	}

	/**
	 * @returns pointer to underlying data
	 */
	inline uint8_t* getBuffer() {
		return buffer->data();
	}

};
