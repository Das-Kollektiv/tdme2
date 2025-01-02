#pragma once

#include <cstring>
#include <set>
#include <sstream>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Time.h>

#include <yannet/network/udp/UDPPacket.h>

using std::memcpy;
using std::set;
using std::string;
using std::stringstream;

using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::Time;

using yannet::network::udp::UDPPacket;

class tdme::engine::logics::LogicNetworkPacket final {
private:
	int64_t time;
	bool safe { false };
	uint32_t logicTypeId { 0 };
	bool processed { false };
	bool reinjected { false };
	uint32_t messageId { 0 };
	uint8_t retryCount { 0 };
	uint8_t position { 0 };
	uint8_t data[255];
	string sender;
	set<string> recipients;

public:
	static constexpr uint32_t LOGIC_TYPEID_NONE { 0 };

	/**
	 * Public constructor, used to create a network packet
	 * @param safe safe
	 * @param logicTypeId logic network packet type id
	 */
	inline LogicNetworkPacket(bool safe, uint32_t logicTypeId = LOGIC_TYPEID_NONE) {
		this->time = Time::getCurrentMillis();
		this->safe = safe;
		this->logicTypeId = logicTypeId;
	}

	/**
	 * Public constructor
	 * @param messageId message id
	 * @param safe safe
	 * @param retryCount retry count
	 * @param logicTypeId logic network packet type id
	 * @param packet packet
	 * @param size size
	 */
	inline LogicNetworkPacket(uint32_t messageId, bool safe, uint8_t retryCount, uint32_t logicTypeId, const UDPPacket* packet, uint8_t size) {
		this->time = Time::getCurrentMillis();
		this->messageId = messageId;
		this->safe = safe;
		this->retryCount = retryCount;
		this->logicTypeId = logicTypeId;
		packet->getBytes(data, size);
	}

	/**
	 * @return time in milliseconds
	 */
	inline int64_t getTime() {
		return time;
	}

	/**
	 * @return if packet has been processed
	 */
	inline bool isProcessed() {
		return processed;
	}

	/**
	 * Set if packet has been processed
	 * @param processed processed
	 */
	inline void setProcessed(bool processed) {
		this->processed = processed;
	}


	/**
	 * @return if reinjected
	 */
	inline bool isReinjected() const {
		return reinjected;
	}

	/**
	 * Set reinjected
	 */
	inline void setReinjected() {
		this->reinjected = true;
	}

	/**
	 * @return if message is safe message
	 */
	inline bool getSafe() {
		return safe;
	}

	/**
	 * @return logic type id
	 */
	inline uint32_t getLogicTypeId() {
		return logicTypeId;
	}

	/**
	 * Set logic type id
	 * @param logicTypeId logic type id
	 */
	inline void setLogicTypeId(uint32_t logicTypeId) {
		this->logicTypeId = logicTypeId;
	}

	/**
	 * Add recipients, no recipients means broadcast, multiple recipients means multi cast, single recipient means unicast
	 * @param recipient recipient
	 */
	inline void addRecipient(const string& recipient) {
		recipients.insert(recipient);
	}

	/**
	 * @return recipients
	 */
	inline set<string>& getRecipients() {
		return recipients;
	}

	/**
	 * @return sender
	 */
	inline const string& getSender() {
		return sender;
	}

	/**
	 * Set sender
	 * @param sender sender
	 */
	inline void setSender(const string& sender) {
		this->sender = sender;
	}

	/**
	 * @return message id
	 */
	inline uint32_t getMessageId() {
		return messageId;
	}

	/**
	 * Get data
	 */
	inline uint8_t* getData() {
		return data;
	}

	/**
	 * Get position
	 */
	inline uint8_t getPosition() {
		return position;
	}

	/**
	 * Reset position for read
	 */
	inline void reset() {
		position = 0;
	}

	/**
	 * Get a byte from packet
	 * @return value
	 */
	inline uint8_t getByte() {
		if (position == 255) {
			Console::printLine("LogicNetworkPacket::getByte(): position out of range");
			return 0;
		}
		return data[position++];
	}

	/**
	 * Puts a byte into packet
	 * @param value value
	 * @return this
	 */
	inline LogicNetworkPacket& putByte(uint8_t value) {
		if (position == 255) {
			Console::printLine("LogicNetworkPacket::putByte(): position out of range");
			return *this;
		}
		data[position++] = value;
		return *this;
	}

	/**
	 * Get a bool from packet
	 * @return value
	 */
	inline bool getBool() {
		return getByte() == 1;
	}

	/**
	 * Puts a bool into packet
	 * @param value value
	 * @return this
	 */
	inline LogicNetworkPacket& putBool(bool value) {
		putByte(value == true?1:0);
		return *this;
	}

	/**
	 * Get a int16 from packet
	 * @return value
	 */
	inline uint16_t getInt16() {
		uint16_t value = 0;
		value+= (uint32_t)getByte();
		value+= (uint32_t)getByte() << 8;
		return value;
	}

	/**
	 * Puts a int16 into packet
	 * @param value value
	 * @return this
	 */
	inline LogicNetworkPacket& putInt16(uint16_t value) {
		putByte((value) & 0xFF);
		putByte((value >> 8) & 0xFF);
		return *this;
	}

	/**
	 * Get a int from packet
	 * @return value
	 */
	inline uint32_t getInt() {
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
	 * @return this
	 */
	inline LogicNetworkPacket& putInt(uint32_t value) {
		putByte((value) & 0xFF);
		putByte((value >> 8) & 0xFF);
		putByte((value >> 16) & 0xFF);
		putByte((value >> 24) & 0xFF);
		return *this;
	}

	/**
	 * Get a small int from packet
	 * @return value
	 */
	inline uint16_t getSmallInt() {
		uint16_t value = 0;
		value+= (uint16_t)getByte();
		value+= (uint16_t)getByte() << 8;
		return value;
	}

	/**
	 * Puts a small int into packet
	 * @param value value
	 * @return this
	 */
	inline LogicNetworkPacket& putSmallInt(uint16_t value) {
		putByte((value) & 0xFF);
		putByte((value >> 8) & 0xFF);
		return *this;
	}

	/**
	 * Get a float from packet
	 * @return value
	 */
	inline float getFloat() {
		uint32_t floatAsInt = getInt();
		return *((float*)&floatAsInt);
	}

	/**
	 * Puts a float into packet
	 * @param value value
	 * @return this
	 */
	inline LogicNetworkPacket& putFloat(float value) {
		uint32_t* floatAsInt = ((uint32_t*)&value);
		putInt(*floatAsInt);
		return *this;
	}

	/**
	 * Get a string value
	 * @return value
	 */
	inline string getString() {
		string value;
		uint8_t length = getByte();
		for (auto i = 0; i < length; i++) value+= getByte();
		return value;
	}

	/**
	 * Puts a string into packet
	 * @param value value
	 * @return this
	 */
	inline LogicNetworkPacket& putString(const string& value) {
		putByte(value.size());
		for (auto i = 0; i < value.size(); i++) {
			putByte(value[i]);
		}
		return *this;
	}

	/**
	 * Get a vector3 from packet
	 * @return value
	 */
	inline Vector3 getVector3() {
		Vector3 value;
		value.setX(getFloat());
		value.setY(getFloat());
		value.setZ(getFloat());
		return value;
	}

	/**
	 * Puts a vector3 into packet
	 * @param value value
	 * @return this
	 */
	inline LogicNetworkPacket& putVector3(const Vector3& value) {
		putFloat(value.getX());
		putFloat(value.getY());
		putFloat(value.getZ());
		return *this;
	}

	/**
	 * Get a quaternion from packet
	 * @return value
	 */
	inline Quaternion getQuaternion() {
		Quaternion value;
		value.setX(getFloat());
		value.setY(getFloat());
		value.setZ(getFloat());
		value.setW(getFloat());
		return value;
	}

	/**
	 * Puts a quaternion into packet
	 * @param value value
	 * @return this
	 */
	inline LogicNetworkPacket& putQuaternion(const Quaternion& value) {
		putFloat(value.getX());
		putFloat(value.getY());
		putFloat(value.getZ());
		putFloat(value.getW());
		return *this;
	}

};
