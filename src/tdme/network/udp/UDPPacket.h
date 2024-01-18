#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>

#include <tdme/network/udp/fwd-tdme.h>

using std::array;
using std::string;
using std::to_string;

using tdme::utilities::Console;

/**
 * UDP Packet
 * @author Andreas Drewke
 */
class tdme::network::udp::UDPPacket final {
private:
	mutable uint16_t position { 0 };
	uint16_t size { 0 };
	array<uint8_t, 512> data;

public:
	static constexpr uint16_t PACKET_MAX_SIZE { 512 };

	/**
	 * Public constructor
	 */
	inline UDPPacket() {
	}

	/**
	 * Get size of packet
	 */
	inline uint16_t getSize() const {
		return size;
	}

	/**
	 * Get data
	 */
	inline const array<uint8_t, 512>& getData() const {
		return data;
	}

	/**
	 * Get position
	 */
	inline uint16_t getPosition() const {
		return position;
	}

	/**
	 * Set position
	 * @param position position
	 * @return UDP client packet
	 */
	inline const UDPPacket* setPosition(uint16_t position) const {
		this->position = position;
		return this;
	}

	/**
	 * Set position
	 * @param position position
	 * @return UDP client packet
	 */
	inline UDPPacket* setPosition(uint16_t position) {
		this->position = position;
		return this;
	}

	/**
	 * Reset position for read
	 */
	inline void reset() const {
		position = 0;
	}

	/**
	 * Get a bool from packet
	 * @return value
	 */
	inline bool getBool() const {
		return getByte() == 1;
	}

	/**
	 * Puts a bool into packet
	 * @param value value
	 * @return UDP client packet
	 */
	inline UDPPacket* putBool(bool value) {
		putByte(value == true?1:0);
		return this;
	}

	/**
	 * Get a byte from packet
	 * @return value
	 */
	inline uint8_t getByte() const {
		if (position >= PACKET_MAX_SIZE) {
			Console::printLine("UDPPacket::getByte(): position out of range: " + to_string(position) + " >= " + to_string(PACKET_MAX_SIZE));
			return 0;
		} else
		if (position >= size) {
			Console::printLine("UDPPacket::getByte(): position out of range: " + to_string(position) + " >= " + to_string(size));
			return 0;
		}
		return data[position++];
	}

	/**
	 * Puts a byte into packet
	 * @param value value
	 * @return UDP client packet
	 */
	inline UDPPacket* putByte(uint8_t value) {
		if (position >= PACKET_MAX_SIZE) {
			Console::printLine("UDPPacket::putByte(): position out of range: " + to_string(position) + " >= " + to_string(PACKET_MAX_SIZE));
			return this;
		}
		data[position++] = value;
		if (position > size) size = position;
		return this;
	}

	/**
	 * Get a int16 from packet
	 * @return value
	 */
	inline uint16_t getInt16() const {
		uint16_t value = 0;
		value+= (uint32_t)getByte();
		value+= (uint32_t)getByte() << 8;
		return value;
	}

	/**
	 * Puts a int16 into packet
	 * @param value value
	 * @return UDP client packet
	 */
	inline UDPPacket* putInt16(uint16_t value) {
		putByte((value) & 0xFF);
		putByte((value >> 8) & 0xFF);
		return this;
	}

	/**
	 * Get a int from packet
	 * @return value
	 */
	inline uint32_t getInt() const {
		uint32_t value = 0;
		value+= (uint32_t)getByte();
		value+= (uint32_t)getByte() << 8;
		value+= (uint32_t)getByte() << 16;
		value+= (uint32_t)getByte() << 24;
		return value;
	}

	/**
	 * Puts a int into packet
	 * @param value value
	 * @return UDP client packet
	 */
	inline UDPPacket* putInt(uint32_t value) {
		putByte((value) & 0xFF);
		putByte((value >> 8) & 0xFF);
		putByte((value >> 16) & 0xFF);
		putByte((value >> 24) & 0xFF);
		return this;
	}

	/**
	 * Get a int64 from packet
	 * @return value
	 */
	inline uint32_t getInt64() const {
		uint64_t value = 0;
		value+= (uint64_t)getByte();
		value+= (uint64_t)getByte() << 8;
		value+= (uint64_t)getByte() << 16;
		value+= (uint64_t)getByte() << 24;
		value+= (uint64_t)getByte() << 32;
		value+= (uint64_t)getByte() << 40;
		value+= (uint64_t)getByte() << 48;
		value+= (uint64_t)getByte() << 56;
		return value;
	}

	/**
	 * Puts a int64 into packet
	 * @param value value
	 * @return UDP client packet
	 */
	inline UDPPacket* putInt64(uint64_t value) {
		putByte((value) & 0xFF);
		putByte((value >> 8) & 0xFF);
		putByte((value >> 16) & 0xFF);
		putByte((value >> 24) & 0xFF);
		putByte((value >> 32) & 0xFF);
		putByte((value >> 40) & 0xFF);
		putByte((value >> 48) & 0xFF);
		putByte((value >> 56) & 0xFF);
		return this;
	}

	/**
	 * Get a float from packet
	 * @return value
	 */
	inline float getFloat() const {
		uint32_t floatAsInt = getInt();
		return *((float*)&floatAsInt);
	}

	/**
	 * Puts a float into packet
	 * @param value value
	 * @return UDP client packet
	 */
	inline UDPPacket* putFloat(float value) {
		uint32_t* floatAsInt = ((uint32_t*)&value);
		putInt(*floatAsInt);
		return this;
	}

	/**
	 * Get a string value
	 * @return value
	 */
	inline string getString() const {
		string value;
		uint8_t length = getByte();
		for (auto i = 0; i < length; i++) value+= getByte();
		return value;
	}

	/**
	 * Puts a string into packet
	 * @param value value
	 * @return UDP client packet
	 */
	inline UDPPacket* putString(const string& value) {
		if (value.size() > 255) {
			Console::printLine("UDPPacket::putString(): string size out of range: string will be clamped to max length of 255 bytes");
		}
		putByte(value.size() > 255?255:value.size());
		for (auto i = 0; i < value.size() && i < 256; i++) {
			putByte(value[i]);
		}
		return this;
	}

	/**
	 * Get raw bytes from packet
	 * @param bytes bytes
	 * @param byteCount byte count
	 * @return UDP client packet
	 */
	inline const UDPPacket* getBytes(uint8_t* bytes, uint16_t byteCount) const {
		for (auto i = 0; i < byteCount; i++) bytes[i] = getByte();
		return this;
	}

	/**
	 * Get raw bytes from packet
	 * @param bytes bytes
	 * @param byteCount byte count
	 * @return UDP client packet
	 */
	inline UDPPacket* getBytes(uint8_t* bytes, uint16_t byteCount) {
		for (auto i = 0; i < byteCount; i++) bytes[i] = getByte();
		return this;
	}

	/**
	 * Puts raw bytes into packet
	 * @param bytes bytes
	 * @param byteCount byte count
	 * @return UDP client packet
	 */
	inline UDPPacket* putBytes(const uint8_t* bytes, uint16_t byteCount) {
		for (auto i = 0; i < byteCount; i++) putByte(bytes[i]);
		return this;
	}

	/**
	 * Puts another packet into this packet
	 * @param value value
	 * @return UDP client packet
	 */
	inline UDPPacket* putPacket(const UDPPacket* packet) {
		for (auto i = 0; i < packet->getSize(); i++) putByte(packet->data[i]);
		return this;
	}

};
