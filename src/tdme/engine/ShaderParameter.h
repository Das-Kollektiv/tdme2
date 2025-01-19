#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Console.h>

using std::array;
using std::string;
using std::to_string;

using tdme::engine::Color4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Console;

/**
 * Shader parameter model class
 */
class tdme::engine::ShaderParameter final {
public:
	enum Type { TYPE_NONE, TYPE_BOOLEAN, TYPE_INTEGER, TYPE_FLOAT, TYPE_VECTOR2, TYPE_VECTOR3, TYPE_VECTOR4, TYPE_COLOR4 };

private:
	Type type { TYPE_NONE };
	int integerValue { 0 };
	array<float, 4> floatValues { 0.0f, 0.0f, 0.0f, 0.0f };

	/**
	 * @returns value as string
	 */
	inline const string toString(float value) const {
		string floatString = to_string(value);
		return floatString.substr(0, floatString.length() - 3);
	}

public:
	/**
	 * Public default constructor
	 */
	ShaderParameter(): type(TYPE_NONE) {
	}

	/**
	 * Public constructor for boolean value
	 * @param booleanValue boolean value
	 */
	ShaderParameter(bool booleanValue): type(TYPE_BOOLEAN), integerValue(booleanValue == true?1:0) {
	}

	/**
	 * Public constructor for int value
	 * @param integerValue int value
	 */
	ShaderParameter(int integerValue): type(TYPE_INTEGER), integerValue(integerValue) {
	}

	/**
	 * Public constructor for float value
	 * @param floatValue float value
	 */
	ShaderParameter(float floatValue): type(TYPE_FLOAT), floatValues( { floatValue, 0.0f, 0.0f, 0.0f} ) {
	}

	/**
	 * Public constructor for Vector2 value
	 * @param vector2Value Vector2 value
	 */
	ShaderParameter(const Vector2& vector2Value): type(TYPE_VECTOR2), floatValues( { vector2Value[0], vector2Value[1], 0.0f, 0.0f} ) {
	}

	/**
	 * Public constructor for Vector3 value
	 * @param vector3Value Vector3 value
	 */
	ShaderParameter(const Vector3& vector3Value): type(TYPE_VECTOR3), floatValues( { vector3Value[0], vector3Value[1], vector3Value[2], 0.0f} ) {
	}

	/**
	 * Public constructor for Vector4 value
	 * @param vector4Value Vector4 value
	 */
	ShaderParameter(const Vector4& vector4Value): type(TYPE_VECTOR4), floatValues( { vector4Value[0], vector4Value[1], vector4Value[2], vector4Value[3]} ) {
	}

	/**
	 * Public constructor for Color4 value
	 * @param color4Value Color4 value
	 */
	ShaderParameter(const Color4& color4Value): type(TYPE_COLOR4), floatValues( { color4Value[0], color4Value[1], color4Value[2], color4Value[3]} ) {
	}

	/**
	 * @returns type
	 */
	inline Type getType() const {
		return type;
	}

	/**
	 * @returns boolean value
	 */
	inline bool getBooleanValue() const {
		return integerValue;
	}

	/**
	 * @returns integer value
	 */
	inline float getIntegerValue() const {
		return integerValue;
	}

	/**
	 * @returns float value
	 */
	inline float getFloatValue() const {
		return floatValues[0];
	}

	/**
	 * @returns Vector2 value
	 */
	inline const Vector2 getVector2Value() const {
		return Vector2(floatValues[0], floatValues[1]);
	}

	/**
	 * @returns Vector2 value array
	 */
	inline const array<float, 2> getVector2ValueArray() const {
		return { floatValues[0], floatValues[1] };
	}

	/**
	 * @returns Vector3 value
	 */
	inline const Vector3 getVector3Value() const {
		return Vector3(floatValues[0], floatValues[1], floatValues[2]);
	}

	/**
	 * @returns Vector3 value array
	 */
	inline const array<float, 3> getVector3ValueArray() const {
		return { floatValues[0], floatValues[1], floatValues[2] };
	}

	/**
	 * @returns Vector4 value
	 */
	inline const Vector4 getVector4Value() const {
		return Vector4(floatValues[0], floatValues[1], floatValues[2], floatValues[3]);
	}

	/**
	 * @returns Vector4 value array
	 */
	inline const array<float, 4> getVector4ValueArray() const {
		return { floatValues[0], floatValues[1], floatValues[2], floatValues[3] };
	}

	/**
	 * @returns Color4 value
	 */
	inline const Color4 getColor4Value() const {
		return Color4(floatValues[0], floatValues[1], floatValues[2], floatValues[3]);
	}

	/**
	 * @returns Color3 value array
	 */
	inline const array<float, 3> getColor3ValueArray() const {
		return { floatValues[0], floatValues[1], floatValues[2] };
	}

	/**
	 * @returns Color4 value array
	 */
	inline const array<float, 4> getColor4ValueArray() const {
		return { floatValues[0], floatValues[1], floatValues[2], floatValues[3] };
	}

	/**
	 * @returns string representation of value
	 */
	inline const string getValueAsString() const {
		switch(type) {
			case ShaderParameter::TYPE_NONE:
				return string();
			case ShaderParameter::TYPE_BOOLEAN:
				return integerValue == 1?"true":"false";
			case ShaderParameter::TYPE_INTEGER:
				return toString(integerValue);
			case ShaderParameter::TYPE_FLOAT:
				return toString(floatValues[0]);
			case ShaderParameter::TYPE_VECTOR2:
			{
				string result;
				for (auto i = 0; i < 2; i++) {
					if (i != 0) result+= ",";
					result+= toString(floatValues[i]);
				}
				return result;
			}
			case ShaderParameter::TYPE_VECTOR3:
			{
				string result;
				for (auto i = 0; i < 3; i++) {
					if (i != 0) result+= ",";
					result+= toString(floatValues[i]);
				}
				return result;
			}
			case ShaderParameter::TYPE_VECTOR4:
			case ShaderParameter::TYPE_COLOR4:
				{
					string result;
					for (auto i = 0; i < 4; i++) {
						if (i != 0) result+= ",";
						result+= toString(floatValues[i]);
					}
					return result;
				}
				break;
			default:
				return string();
		}
	}

};
