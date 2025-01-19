#pragma once

#include <array>
#include <string>

#include <agui/agui.h>
#include <agui/gui/misc/GUIColor4.h>
#include <agui/gui/renderer/fwd-agui.h>
#include <agui/math/Vector2.h>
#include <agui/math/Vector3.h>
#include <agui/math/Vector4.h>
#include <agui/utilities/Console.h>

using std::array;
using std::string;
using std::to_string;

// namespaces
namespace agui {
namespace gui {
namespace renderer {
	using ::agui::gui::misc::GUIColor4;
	using ::agui::math::Vector2;
	using ::agui::math::Vector3;
	using ::agui::math::Vector4;
	using ::agui::utilities::Console;
}
}
}

/**
 * Shader parameter model class
 */
class agui::gui::renderer::GUIShaderParameter final {
public:
	enum Type { TYPE_NONE, TYPE_BOOLEAN, TYPE_INTEGER, TYPE_FLOAT, TYPE_VECTOR2, TYPE_VECTOR3, TYPE_VECTOR4, TYPE_COLOR4 };

private:
	Type type { TYPE_NONE };
	int integerValue { 0 };
	array<float, 4> floatValues { 0.0f, 0.0f, 0.0f, 0.0f };

	/**
	 * @return value as string
	 */
	inline const string toString(float value) const {
		string floatString = to_string(value);
		return floatString.substr(0, floatString.length() - 3);
	}

public:
	/**
	 * Public default constructor
	 */
	GUIShaderParameter(): type(TYPE_NONE) {
	}

	/**
	 * Public constructor for boolean value
	 * @param booleanValue boolean value
	 */
	GUIShaderParameter(bool booleanValue): type(TYPE_BOOLEAN), integerValue(booleanValue == true?1:0) {
	}

	/**
	 * Public constructor for int value
	 * @param integerValue int value
	 */
	GUIShaderParameter(int integerValue): type(TYPE_INTEGER), integerValue(integerValue) {
	}

	/**
	 * Public constructor for float value
	 * @param floatValue float value
	 */
	GUIShaderParameter(float floatValue): type(TYPE_FLOAT), floatValues( { floatValue, 0.0f, 0.0f, 0.0f} ) {
	}

	/**
	 * Public constructor for Vector2 value
	 * @param vector2Value Vector2 value
	 */
	GUIShaderParameter(const Vector2& vector2Value): type(TYPE_VECTOR2), floatValues( { vector2Value[0], vector2Value[1], 0.0f, 0.0f} ) {
	}

	/**
	 * Public constructor for Vector3 value
	 * @param vector3Value Vector3 value
	 */
	GUIShaderParameter(const Vector3& vector3Value): type(TYPE_VECTOR3), floatValues( { vector3Value[0], vector3Value[1], vector3Value[2], 0.0f} ) {
	}

	/**
	 * Public constructor for Vector4 value
	 * @param vector4Value Vector4 value
	 */
	GUIShaderParameter(const Vector4& vector4Value): type(TYPE_VECTOR4), floatValues( { vector4Value[0], vector4Value[1], vector4Value[2], vector4Value[3]} ) {
	}

	/**
	 * Public constructor for GUIColor4 value
	 * @param color4Value GUIColor4 value
	 */
	GUIShaderParameter(const GUIColor4& color4Value): type(TYPE_COLOR4), floatValues( { color4Value[0], color4Value[1], color4Value[2], color4Value[3]} ) {
	}

	/**
	 * @return type
	 */
	inline Type getType() const {
		return type;
	}

	/**
	 * @return boolean value
	 */
	inline bool getBooleanValue() const {
		return integerValue;
	}

	/**
	 * @return integer value
	 */
	inline float getIntegerValue() const {
		return integerValue;
	}

	/**
	 * @return float value
	 */
	inline float getFloatValue() const {
		return floatValues[0];
	}

	/**
	 * @return Vector2 value
	 */
	inline const Vector2 getVector2Value() const {
		return Vector2(floatValues[0], floatValues[1]);
	}

	/**
	 * @return Vector2 value array
	 */
	inline const array<float, 2> getVector2ValueArray() const {
		return { floatValues[0], floatValues[1] };
	}

	/**
	 * @return Vector3 value
	 */
	inline const Vector3 getVector3Value() const {
		return Vector3(floatValues[0], floatValues[1], floatValues[2]);
	}

	/**
	 * @return Vector3 value array
	 */
	inline const array<float, 3> getVector3ValueArray() const {
		return { floatValues[0], floatValues[1], floatValues[2] };
	}

	/**
	 * @return Vector4 value
	 */
	inline const Vector4 getVector4Value() const {
		return Vector4(floatValues[0], floatValues[1], floatValues[2], floatValues[3]);
	}

	/**
	 * @return Vector4 value array
	 */
	inline const array<float, 4> getVector4ValueArray() const {
		return { floatValues[0], floatValues[1], floatValues[2], floatValues[3] };
	}

	/**
	 * @return GUIColor4 value
	 */
	inline const GUIColor4 getColor4Value() const {
		return GUIColor4(floatValues[0], floatValues[1], floatValues[2], floatValues[3]);
	}

	/**
	 * @return Color3 value array
	 */
	inline const array<float, 3> getColor3ValueArray() const {
		return { floatValues[0], floatValues[1], floatValues[2] };
	}

	/**
	 * @return GUIColor4 value array
	 */
	inline const array<float, 4> getColor4ValueArray() const {
		return { floatValues[0], floatValues[1], floatValues[2], floatValues[3] };
	}

	/**
	 * @return string representation of value
	 */
	inline const string getValueAsString() const {
		switch(type) {
			case GUIShaderParameter::TYPE_NONE:
				return string();
			case GUIShaderParameter::TYPE_BOOLEAN:
				return integerValue == 1?"true":"false";
			case GUIShaderParameter::TYPE_INTEGER:
				return toString(integerValue);
			case GUIShaderParameter::TYPE_FLOAT:
				return toString(floatValues[0]);
			case GUIShaderParameter::TYPE_VECTOR2:
			{
				string result;
				for (auto i = 0; i < 2; i++) {
					if (i != 0) result+= ",";
					result+= toString(floatValues[i]);
				}
				return result;
			}
			case GUIShaderParameter::TYPE_VECTOR3:
			{
				string result;
				for (auto i = 0; i < 3; i++) {
					if (i != 0) result+= ",";
					result+= toString(floatValues[i]);
				}
				return result;
			}
			case GUIShaderParameter::TYPE_VECTOR4:
			case GUIShaderParameter::TYPE_COLOR4:
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
