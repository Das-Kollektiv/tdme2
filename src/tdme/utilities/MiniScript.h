#pragma once

#include <algorithm>
#include <array>
#include <span>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::array;
using std::remove;
using std::stack;
using std::string;
using std::string_view;
using std::to_string;
using std::unordered_map;
using std::vector;
using std::span;

using tdme::engine::Transform;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::math::Quaternion;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

namespace tdme {
namespace tools {
namespace cli {
	class MiniscriptTranspiler;
}
}
}

/**
 * Miniscript
 * @author Andreas Drewke
 */
class tdme::utilities::MiniScript {
	friend class tdme::tools::cli::MiniscriptTranspiler;

public:
	enum ScriptOperator {
		OPERATOR_NONE,
		// priority 3
		OPERATOR_NOT,
		// priority 5
		OPERATOR_DIVISION,
		OPERATOR_MULTIPLICATION,
		OPERATOR_REMAINDER, // TODO: not yet
		// priority 6
		OPERATOR_ADDITION,
		OPERATOR_SUBTRACTION,
		// priority 9
		OPERATOR_LESSER,
		OPERATOR_LESSEREQUALS,
		OPERATOR_GREATER,
		OPERATOR_GREATEREQUALS,
		// priority 10
		OPERATOR_EQUALS,
		OPERATOR_NOTEQUAL,
		// priority 14
		OPERATOR_AND,
		// priority 15
		OPERATOR_OR,
		// priority 16
		OPERATOR_SET,
		//
		OPERATOR_MAX
	};

	enum StateMachineState {
		STATEMACHINESTATE_NONE = -1,
		STATEMACHINESTATE_NEXT_STATEMENT,
		STATEMACHINESTATE_WAIT,
		STATEMACHINESTATE_WAIT_FOR_CONDITION
	};

	struct ScriptStatement {
		int line;
		int statementIdx;
		string statement;
		int gotoStatementIdx;
	};

	enum ScriptVariableType {
		TYPE_VOID,
		TYPE_BOOLEAN,
		TYPE_INTEGER,
		TYPE_FLOAT,
		TYPE_STRING,
		TYPE_VECTOR2,
		TYPE_VECTOR3,
		TYPE_VECTOR4,
		TYPE_QUATERNION,
		TYPE_MATRIX3x3,
		TYPE_MATRIX4x4,
		TYPE_TRANSFORM,
		TYPE_ARRAY,
		TYPE_MAP,
		TYPE_PSEUDO_NUMBER
	};

	/**
	 * MiniScript script variable
	 */
	class ScriptVariable {
		friend class MiniScript;

	private:

		ScriptVariableType type { TYPE_VOID };
		void* valuePtr { nullptr };

		/**
		 * @return boolean value reference
		 */
		inline bool& getBooleanValueReference() {
			return *static_cast<bool*>(valuePtr);
		}

		/**
		 * @return const boolean value reference
		 */
		inline const bool& getBooleanValueReference() const {
			return *static_cast<bool*>(valuePtr);
		}

		/**
		 * @return integer value reference
		 */
		inline int64_t& getIntegerValueReference() {
			return *static_cast<int64_t*>(valuePtr);
		}

		/**
		 * @return const integer value reference
		 */
		inline const int64_t& getIntegerValueReference() const {
			return *static_cast<int64_t*>(valuePtr);
		}

		/**
		 * @return float value reference
		 */
		inline float& getFloatValueReference() {
			return *static_cast<float*>(valuePtr);
		}

		/**
		 * @return const float value reference
		 */
		inline const float& getFloatValueReference() const {
			return *static_cast<float*>(valuePtr);
		}

		/**
		 * @return string value reference
		 */
		inline string& getStringValueReference() {
			return *static_cast<string*>(valuePtr);
		}

		/**
		 * @return const string value reference
		 */
		inline const string& getStringValueReference() const {
			return *static_cast<string*>(valuePtr);
		}

		/**
		 * @return vector2 value reference
		 */
		inline Vector2& getVector2ValueReference() {
			return *static_cast<Vector2*>(valuePtr);
		}

		/**
		 * @return const vector2 value reference
		 */
		inline const Vector2& getVector2ValueReference() const {
			return *static_cast<Vector2*>(valuePtr);
		}

		/**
		 * @return vector3 value reference
		 */
		inline Vector3& getVector3ValueReference() {
			return *static_cast<Vector3*>(valuePtr);
		}

		/**
		 * @return const vector3 value reference
		 */
		inline const Vector3& getVector3ValueReference() const {
			return *static_cast<Vector3*>(valuePtr);
		}

		/**
		 * @return vector4 value reference
		 */
		inline Vector4& getVector4ValueReference() {
			return *static_cast<Vector4*>(valuePtr);
		}

		/**
		 * @return const vector4 value reference
		 */
		inline const Vector4& getVector4ValueReference() const {
			return *static_cast<Vector4*>(valuePtr);
		}

		/**
		 * @return quaternion value reference
		 */
		inline Quaternion& getQuaternionValueReference() {
			return *static_cast<Quaternion*>(valuePtr);
		}

		/**
		 * @return const quaternion value reference
		 */
		inline const Quaternion& getQuaternionValueReference() const {
			return *static_cast<Quaternion*>(valuePtr);
		}

		/**
		 * @return matrix3x3 value reference
		 */
		inline Matrix2D3x3& getMatrix3x3ValueReference() {
			return *static_cast<Matrix2D3x3*>(valuePtr);
		}

		/**
		 * @return const matrix3x3 value reference
		 */
		inline const Matrix2D3x3& getMatrix3x3ValueReference() const {
			return *static_cast<Matrix2D3x3*>(valuePtr);
		}

		/**
		 * @return matrix4x4 value reference
		 */
		inline Matrix4x4& getMatrix4x4ValueReference() {
			return *static_cast<Matrix4x4*>(valuePtr);
		}

		/**
		 * @return const matrix4x4 value reference
		 */
		inline const Matrix4x4& getMatrix4x4ValueReference() const {
			return *static_cast<Matrix4x4*>(valuePtr);
		}

		/**
		 * @return transform value reference
		 */
		inline Transform& getTransformValueReference() {
			return *static_cast<Transform*>(valuePtr);
		}

		/**
		 * @return const transform value reference
		 */
		inline const Transform& getTransformValueReference() const {
			return *static_cast<Transform*>(valuePtr);
		}

		/**
		 * @return array value reference
		 */
		inline vector<ScriptVariable>& getArrayValueReference() {
			return *static_cast<vector<ScriptVariable>*>(valuePtr);
		}

		/**
		 * @return const array value reference
		 */
		inline const vector<ScriptVariable>& getArrayValueReference() const {
			return *static_cast<vector<ScriptVariable>*>(valuePtr);
		}

		/**
		 * @return map value reference
		 */
		inline unordered_map<string, ScriptVariable>& getMapValueReference() {
			return *static_cast<unordered_map<string, ScriptVariable>*>(valuePtr);
		}

		/**
		 * @return const map value reference
		 */
		inline const unordered_map<string, ScriptVariable>& getMapValueReference() const {
			return *static_cast<unordered_map<string, ScriptVariable>*>(valuePtr);
		}

	public:
		/**
		 * Assignment operator
		 * @param scriptVariable script variable to copy
		 * @return this script variable
		 */
		inline ScriptVariable& operator=(const ScriptVariable& scriptVariable) {
			switch(scriptVariable.type) {
				case TYPE_VOID:
					break;
				case TYPE_BOOLEAN:
					setValue(scriptVariable.getBooleanValueReference());
					break;
				case TYPE_INTEGER:
					setValue(scriptVariable.getIntegerValueReference());
					break;
				case TYPE_FLOAT:
					setValue(scriptVariable.getFloatValueReference());
					break;
				case TYPE_STRING:
					setValue(scriptVariable.getStringValueReference());
					break;
				case TYPE_VECTOR2:
					setValue(scriptVariable.getVector2ValueReference());
					break;
				case TYPE_VECTOR3:
					setValue(scriptVariable.getVector3ValueReference());
					break;
				case TYPE_VECTOR4:
					setValue(scriptVariable.getVector4ValueReference());
					break;
				case TYPE_QUATERNION:
					setValue(scriptVariable.getQuaternionValueReference());
					break;
				case TYPE_MATRIX3x3:
					setValue(scriptVariable.getMatrix3x3ValueReference());
					break;
				case TYPE_MATRIX4x4:
					setValue(scriptVariable.getMatrix4x4ValueReference());
					break;
				case TYPE_TRANSFORM:
					setValue(scriptVariable.getTransformValueReference());
					break;
				case TYPE_ARRAY:
					setValue(scriptVariable.getArrayValueReference());
					break;
				case TYPE_MAP:
					setValue(scriptVariable.getMapValueReference());
					break;
			}
			return *this;
		}

		/**
		 * Copy constructor
		 * @param scriptVariable script variable to copy
		 */
		inline ScriptVariable(const ScriptVariable& scriptVariable) {
			switch(scriptVariable.type) {
				case TYPE_VOID:
					break;
				case TYPE_BOOLEAN:
					setValue(scriptVariable.getBooleanValueReference());
					break;
				case TYPE_INTEGER:
					setValue(scriptVariable.getIntegerValueReference());
					break;
				case TYPE_FLOAT:
					setValue(scriptVariable.getFloatValueReference());
					break;
				case TYPE_STRING:
					setValue(scriptVariable.getStringValueReference());
					break;
				case TYPE_VECTOR2:
					setValue(scriptVariable.getVector2ValueReference());
					break;
				case TYPE_VECTOR3:
					setValue(scriptVariable.getVector3ValueReference());
					break;
				case TYPE_VECTOR4:
					setValue(scriptVariable.getVector4ValueReference());
					break;
				case TYPE_QUATERNION:
					setValue(scriptVariable.getQuaternionValueReference());
					break;
				case TYPE_MATRIX3x3:
					setValue(scriptVariable.getMatrix3x3ValueReference());
					break;
				case TYPE_MATRIX4x4:
					setValue(scriptVariable.getMatrix4x4ValueReference());
					break;
				case TYPE_TRANSFORM:
					setValue(scriptVariable.getTransformValueReference());
					break;
				case TYPE_ARRAY:
					setValue(scriptVariable.getArrayValueReference());
					break;
				case TYPE_MAP:
					setValue(scriptVariable.getMapValueReference());
					break;
			}
		}

		/**
		 * Constructor
		 */
		inline ScriptVariable() {
		}

		/**
		 * Destructor
		 */
		inline ~ScriptVariable() {
			setType(TYPE_VOID);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(bool value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(int64_t value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(float value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const string& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const Vector2& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const Vector3& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const Vector4& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const Quaternion& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const Matrix2D3x3& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const Matrix4x4& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const Transform& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const vector<ScriptVariable>& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const unordered_map<string, ScriptVariable>& value) {
			setValue(value);
		}

		/**
		 * @return type
		 */
		inline ScriptVariableType getType() const {
			return type;
		}

		/**
		 * Set type
		 * @param newType new type
		 */
		inline void setType(ScriptVariableType newType) {
			if (type == newType) return;
			switch(type) {
				case TYPE_VOID:
					break;
				case TYPE_BOOLEAN:
					delete static_cast<bool*>(valuePtr);
					break;
				case TYPE_INTEGER:
					delete static_cast<int64_t*>(valuePtr);
					break;
				case TYPE_FLOAT:
					delete static_cast<float*>(valuePtr);
					break;
				case TYPE_STRING:
					delete static_cast<string*>(valuePtr);
					break;
				case TYPE_VECTOR2:
					delete static_cast<Vector2*>(valuePtr);
					break;
				case TYPE_VECTOR3:
					delete static_cast<Vector3*>(valuePtr);
					break;
				case TYPE_VECTOR4:
					delete static_cast<Vector4*>(valuePtr);
					break;
				case TYPE_QUATERNION:
					delete static_cast<Quaternion*>(valuePtr);
					break;
				case TYPE_MATRIX3x3:
					delete static_cast<Matrix2D3x3*>(valuePtr);
					break;
				case TYPE_MATRIX4x4:
					delete static_cast<Matrix4x4*>(valuePtr);
					break;
				case TYPE_TRANSFORM:
					delete static_cast<Transform*>(valuePtr);
					break;
				case TYPE_ARRAY:
					delete static_cast<vector<ScriptVariable>*>(valuePtr);
					break;
				case TYPE_MAP:
					delete static_cast<unordered_map<string, ScriptVariable>*>(valuePtr);
					break;
			}
			this->valuePtr = nullptr;
			this->type = newType;
			switch(type) {
				case TYPE_VOID:
					break;
				case TYPE_BOOLEAN:
					valuePtr = new bool();
					break;
				case TYPE_INTEGER:
					valuePtr = new int64_t();
					break;
				case TYPE_FLOAT:
					valuePtr = new float();
					break;
				case TYPE_STRING:
					valuePtr = new string();
					break;
				case TYPE_VECTOR2:
					valuePtr = new Vector2();
					break;
				case TYPE_VECTOR3:
					valuePtr = new Vector3();
					break;
				case TYPE_VECTOR4:
					valuePtr = new Vector4();
					break;
				case TYPE_QUATERNION:
					valuePtr = new Quaternion();
					break;
				case TYPE_MATRIX3x3:
					valuePtr = new Matrix2D3x3();
					break;
				case TYPE_MATRIX4x4:
					valuePtr = new Matrix4x4();
					break;
				case TYPE_TRANSFORM:
					valuePtr = new Transform();
					break;
				case TYPE_ARRAY:
					valuePtr = new vector<ScriptVariable>();
					break;
				case TYPE_MAP:
					valuePtr = new unordered_map<string, ScriptVariable>();
					break;
			}
		}

		/**
		 * Get boolean value from given variable
		 * @param value value
		 * @param optional optionalfalse
		 * @return success
		 */
		inline bool getBooleanValue(bool& value, bool optional = false) const {
			switch(type) {
				case TYPE_BOOLEAN:
					value = getBooleanValueReference();
					return true;
					break;
				case TYPE_INTEGER:
					value = getIntegerValueReference() != 0;
					return true;
				case TYPE_FLOAT:
					value = getFloatValueReference() != 0.0f;
					return true;
				case TYPE_STRING:
					{
						auto& stringValue = getStringValueReference();
						auto lowerCaseString = StringTools::toLowerCase(stringValue);
						if (lowerCaseString != "false" && lowerCaseString != "true" && lowerCaseString != "1" && lowerCaseString != "0") return optional;
						value = lowerCaseString == "true" || lowerCaseString == "1";
						return true;
					}
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get integer value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getIntegerValue(int64_t& value, bool optional = false) const {
			switch(type) {
				case TYPE_BOOLEAN:
					value = getBooleanValueReference() == true?1:0;
					return true;
					break;
				case TYPE_INTEGER:
					value = getIntegerValueReference();
					return true;
				case TYPE_FLOAT:
					Console::println("MiniScript::getIntegerValue(): converting float to integer: precision loss");
					value = getFloatValueReference();
					return true;
				case TYPE_STRING:
					{
						auto& stringValue = getStringValueReference();
						if (Integer::is(stringValue) == true) {
							value = Integer::parse(stringValue);
							return true;
						} else
						if (Float::is(stringValue) == true) {
							Console::println("MiniScript::getIntegerValue(): converting float to integer: precision loss");
							value = static_cast<int64_t>(Float::parse(stringValue));
							return true;
						} else {
							return optional;
						}
					}
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get float value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getFloatValue(float& value, bool optional = false) const {
			switch(type) {
				case TYPE_BOOLEAN:
					value = getBooleanValueReference() == true?1.0f:0.0f;
					return true;
					break;
				case TYPE_INTEGER:
					value = getIntegerValueReference();
					return true;
				case TYPE_FLOAT:
					value = getFloatValueReference();
					return true;
				case TYPE_STRING:
					{
						auto& stringValue = getStringValueReference();
						if (Float::is(stringValue) == false) return optional;
						value = Float::parse(stringValue);
					}
					return true;
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get string value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getStringValue(string& value, bool optional = false) const {
			switch(type) {
				case TYPE_BOOLEAN:
					value = getBooleanValueReference() == true?"true":"false";
					return true;
				case TYPE_INTEGER:
					value = to_string(getIntegerValueReference());
					return true;
				case TYPE_FLOAT:
					value = to_string(getFloatValueReference());
					return true;
				case TYPE_STRING:
					value = getStringValueReference();
					return true;
				default:
					return false;
			}
			return false;
		}

		/**
		 * Get vector2 value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getVector2Value(Vector2& value, bool optional = false) const {
			switch(type) {
				case TYPE_VECTOR2:
					value = getVector2ValueReference();
					return true;
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get vector3 value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getVector3Value(Vector3& value, bool optional = false) const {
			switch(type) {
				case TYPE_VECTOR3:
					value = getVector3ValueReference();
					return true;
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get vector4 value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getVector4Value(Vector4& value, bool optional = false) const {
			switch(type) {
				case TYPE_VECTOR4:
					value = getVector4ValueReference();
					return true;
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get quaternion value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getQuaternionValue(Quaternion& value, bool optional = false) const {
			switch(type) {
				case TYPE_QUATERNION:
					value = getQuaternionValueReference();
					return true;
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get matrix3x3 value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getMatrix3x3Value(Matrix2D3x3& value, bool optional = false) const {
			switch(type) {
				case TYPE_MATRIX3x3:
					value = getMatrix3x3ValueReference();
					return true;
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get matrix4x4 value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getMatrix4x4Value(Matrix4x4& value, bool optional = false) const {
			switch(type) {
				case TYPE_MATRIX4x4:
					value = getMatrix4x4ValueReference();
					return true;
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get transform value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getTransformValue(Transform& value, bool optional = false) const {
			switch(type) {
				case TYPE_TRANSFORM:
					value = getTransformValueReference();
					return true;
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get array value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getArrayValue(vector<ScriptVariable>& value, bool optional = false) const {
			switch(type) {
				case TYPE_ARRAY:
					value = getArrayValueReference();
					return true;
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get map value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getMapValue(unordered_map<string, ScriptVariable>& value, bool optional = false) const {
			switch(type) {
				case TYPE_MAP:
					value = getMapValueReference();
					return true;
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Set boolean value from given value into variable
		 * @param value value
		 */
		inline void setValue(bool value) {
			setType(TYPE_BOOLEAN);
			getBooleanValueReference() = value;
		}

		/**
		 * Set integer value from given value into variable
		 * @param value value
		 */
		inline void setValue(int64_t value) {
			setType(TYPE_INTEGER);
			getIntegerValueReference() = value;
		}

		/**
		 * Set float value from given value into variable
		 * @param value value
		 */
		inline void setValue(float value) {
			setType(TYPE_FLOAT);
			getFloatValueReference() = value;
		}

		/**
		 * Set string value from given value into variable
		 * @param value value
		 */
		inline void setValue(const string& value) {
			setType(TYPE_STRING);
			getStringValueReference() = value;
		}

		/**
		 * Set vector2 value from given value into variable
		 * @param value value
		 */
		inline void setValue(const Vector2& value) {
			setType(TYPE_VECTOR2);
			getVector2ValueReference() = value;
		}

		/**
		 * Set vector3 value from given value into variable
		 * @param value value
		 */
		inline void setValue(const Vector3& value) {
			setType(TYPE_VECTOR3);
			getVector3ValueReference() = value;
		}

		/**
		 * Set vector3 value from given value into variable
		 * @param value value
		 */
		inline void setValue(const Vector4& value) {
			setType(TYPE_VECTOR4);
			getVector4ValueReference() = value;
		}

		/**
		 * Set vector3 value from given value into variable
		 * @param value value
		 */
		inline void setValue(const Quaternion& value) {
			setType(TYPE_QUATERNION);
			getQuaternionValueReference() = value;
		}

		/**
		 * Set matrix3x3 value from given value into variable
		 * @param value value
		 */
		inline void setValue(const Matrix2D3x3& value) {
			setType(TYPE_MATRIX3x3);
			getMatrix3x3ValueReference() = value;
		}

		/**
		 * Set matrix4x4 value from given value into variable
		 * @param value value
		 */
		inline void setValue(const Matrix4x4& value) {
			setType(TYPE_MATRIX4x4);
			getMatrix4x4ValueReference() = value;
		}

		/**
		 * Set transform value from given value into variable
		 * @param value value
		 */
		inline void setValue(const Transform& value) {
			setType(TYPE_TRANSFORM);
			getTransformValueReference() = value;
		}

		/**
		 * Set array value from given value into variable
		 * @param value value
		 */
		inline void setValue(const vector<ScriptVariable>& value) {
			// TODO: be verbose about misuse
			setType(TYPE_ARRAY);
			getArrayValueReference() = value;
		}

		/**
		 * Set map value from given value into variable
		 * @param value value
		 */
		inline void setValue(const unordered_map<string, ScriptVariable>& value) {
			// TODO: be verbose about misuse
			setType(TYPE_MAP);
			getMapValueReference() = value;
		}

		/**
		 * Get array size
		 * @return array size
		 */
		inline int64_t getArraySize() const {
			// TODO: be verbose about misuse
			if (getType() != TYPE_ARRAY) return 0;
			return getArrayValueReference().size();
		}

		/**
		 * Get value from array with given index
		 * @param idx index
		 * @return value from array with given index
		 */
		inline const ScriptVariable getArrayValue(int idx) const {
			// TODO: be verbose about misuse
			if (type != TYPE_ARRAY) return ScriptVariable();
			auto& arrayValue = getArrayValueReference();
			if (idx >= 0 && idx < arrayValue.size()) return arrayValue[idx];
			return ScriptVariable();
		}

		/**
		 * Set value to array with given index
		 * @param idx index
		 */
		inline void setArrayValue(int idx, const ScriptVariable& value) {
			// TODO: be verbose about misuse
			setType(TYPE_ARRAY);
			if (idx < 0) return;
			auto& arrayValue = getArrayValueReference();
			while (arrayValue.size() <= idx) pushArrayValue(ScriptVariable());
			arrayValue[idx] = value;
		}

		/**
		 * Push value to array
		 * @param value value
		 */
		inline void pushArrayValue(const ScriptVariable& value) {
			// TODO: be verbose about misuse
			setType(TYPE_ARRAY);
			getArrayValueReference().push_back(value);
		}

		/**
		 * Remove array value at given index
		 * @param idx index
		 */
		inline void removeArrayValue(int idx) {
			// TODO: be verbose about misuse
			if (type != TYPE_ARRAY) return;
			auto& arrayValue = getArrayValueReference();
			if (idx >= 0 && idx < arrayValue.size()) arrayValue.erase(arrayValue.begin() + idx);
			return;
		}

		/**
		 * Get map size
		 */
		inline int64_t getMapSize() const {
			// TODO: be verbose about misuse
			if (getType() != TYPE_MAP) return 0;
			return getMapValueReference().size();
		}

		/**
		 * Map has value with given key
		 * @param key key
		 * @return key exists
		 */
		inline bool hasMapValue(const string& key) const {
			// TODO: be verbose about misuse
			if (type != TYPE_MAP) return false;
			auto& mapValue = getMapValueReference();
			auto it = mapValue.find(key);
			if (it != mapValue.end()) return true;
			return false;
		}

		/**
		 * Get value from map with given key
		 * @param key key
		 * @return map value from given key
		 */
		inline const ScriptVariable getMapValue(const string& key) const {
			// TODO: be verbose about misuse
			if (type != TYPE_MAP) return ScriptVariable();
			auto& mapValue = getMapValueReference();
			auto it = mapValue.find(key);
			if (it != mapValue.end()) return it->second;
			return ScriptVariable();
		}

		/**
		 * Set value in map with given key
		 * @param key key
		 * @param value value
		 */
		inline void setMapValue(const string& key, const ScriptVariable& value) {
			// TODO: be verbose about misuse
			setType(TYPE_MAP);
			getMapValueReference()[key] = value;
		}

		/**
		 * Remove value in map with given key
		 * @param key key
		 */
		inline void removeMapValue(const string& key) {
			// TODO: be verbose about misuse
			if (type != TYPE_MAP) return;
			auto& mapValue = getMapValueReference();
			auto it = mapValue.find(key);
			if (it != mapValue.end()) {
				mapValue.erase(it);
			}
		}

		/**
		 * Get map keys
		 * @return keys
		 */
		inline const vector<string> getMapKeys() const {
			vector<string> keys;
			// TODO: be verbose about misuse
			if (type != TYPE_MAP) return keys;
			auto& mapValue = getMapValueReference();
			for (auto& it: mapValue) {
				keys.push_back(it.first);
			}
			return keys;
		}

		/**
		 * Get map values
		 * @return values
		 */
		inline const vector<ScriptVariable> getMapValues() const {
			vector<ScriptVariable> values;
			// TODO: be verbose about misuse
			if (type != TYPE_MAP) return values;
			auto& mapValue = getMapValueReference();
			for (auto& it: mapValue) {
				values.push_back(it.second);
			}
			return values;
		}

		/**
		 * Set implicit typed value given by value string
		 * @param value value
		 */
		inline void setImplicitTypedValue(const string& value) {
			if (value == "true") {
				setValue(true);
			} else
			if (value == "false") {
				setValue(false);
			} else
			if (Integer::is(value) == true) {
				setValue(static_cast<int64_t>(Integer::parse(value)));
			} else
			if (Float::is(value) == true) {
				setValue(Float::parse(value));
			} else {
				setValue(value);
			}
		}

		/**
		 * Set implicit typed value given by value string
		 * @param value value
		 */
		inline void setImplicitTypedValueFromStringView(const string_view& value) {
			if (value == "true") {
				setValue(true);
			} else
			if (value == "false") {
				setValue(false);
			} else
			if (Integer::viewIs(value) == true) {
				setValue(static_cast<int64_t>(Integer::viewParse(value)));
			} else
			if (Float::viewIs(value) == true) {
				setValue(Float::viewParse(value));
			} else {
				setValue(string(value));
			}
		}

		/**
		 * Check if given variable type does match expected variable type
		 * @param type type
		 * @param expectedType expected type
		 * @return given variable type does match expected variable type
		 */
		inline static bool isExpectedType(ScriptVariableType type, ScriptVariableType expectedType) {
			if (type == expectedType) return true;
			switch(expectedType) {
				case TYPE_PSEUDO_NUMBER:
					return type == TYPE_INTEGER || type == TYPE_FLOAT;
				default:
					return false;
			}
		}

		/**
		 * @return string representation of script variable type
		 */
		inline static const string getTypeAsString(ScriptVariableType type) {
			switch(type) {
				case TYPE_VOID: return "Void";
				case TYPE_BOOLEAN: return "Boolean";
				case TYPE_INTEGER: return "Integer";
				case TYPE_FLOAT: return "Float";
				case TYPE_STRING: return "String";
				case TYPE_VECTOR2: return "Vector2";
				case TYPE_VECTOR3: return "Vector3";
				case TYPE_VECTOR4: return "Vector4";
				case TYPE_QUATERNION: return "Quaternion";
				case TYPE_MATRIX3x3: return "Matrix3x3";
				case TYPE_MATRIX4x4: return "Matrix4x4";
				case TYPE_TRANSFORM: return "Transform";
				case TYPE_ARRAY: return "Array";
				case TYPE_MAP: return "Map";
				case TYPE_PSEUDO_NUMBER: return "Number";
			}
			return string();
		}

		/**
		 * @return string representation of script variable type
		 */
		inline const string getTypeAsString() {
			return getTypeAsString(type);
		}

		/**
		 * @return string representation of script variable type
		 */
		inline const string getAsString() {
			string result;
			result+= getTypeAsString();
			result+= "(";
			result+= getValueString();
			result+= ")";
			return result;
		}

		/**
		 * @return string representation of script variable type
		 */
		inline const string getValueString() const {
			string result;
			switch (type) {
				case TYPE_VOID:
					result+= "<VOID>";
					break;
				case TYPE_BOOLEAN:
					result+= getBooleanValueReference() == true?"1":"0";
					break;
				case TYPE_INTEGER:
					result+= to_string(getIntegerValueReference());
					break;
				case TYPE_FLOAT:
					result+= to_string(getFloatValueReference());
					break;
				case TYPE_STRING:
					result+= getStringValueReference();
					break;
				case TYPE_VECTOR2:
					{
						auto& vector2Value = getVector2ValueReference();
						result+=
							"Vector2(" +
							to_string(vector2Value.getX()) + ", " +
							to_string(vector2Value.getY()) + ")";
					}
					break;
				case TYPE_VECTOR3:
					{
						auto& vector3Value = getVector3ValueReference();
						result+=
							"Vector3(" +
							to_string(vector3Value.getX()) + ", " +
							to_string(vector3Value.getY()) + ", " +
							to_string(vector3Value.getZ()) + ")";
					}
					break;
				case TYPE_VECTOR4:
					{
						auto& vector4Value = getVector4ValueReference();
						result+=
							"Vector4(" +
							to_string(vector4Value.getX()) + ", " +
							to_string(vector4Value.getY()) + ", " +
							to_string(vector4Value.getZ()) + ", " +
							to_string(vector4Value.getW()) + ")";
					}
					break;
				case TYPE_QUATERNION:
					{
						auto& quaternionValue = getQuaternionValueReference();
						result+=
							"Quaternion(" +
							to_string(quaternionValue.getX()) + ", " +
							to_string(quaternionValue.getY()) + ", " +
							to_string(quaternionValue.getZ()) + ", " +
							to_string(quaternionValue.getW()) + ")";
					}
					break;
				case TYPE_MATRIX3x3:
					{
						auto& matrix3x3Value = getMatrix3x3ValueReference();
						result+=
							"Matrix3x3(" +
							to_string(matrix3x3Value[0]) + ", " +
							to_string(matrix3x3Value[1]) + ", " +
							to_string(matrix3x3Value[2]) + ", " +
							to_string(matrix3x3Value[3]) + ", " +
							to_string(matrix3x3Value[4]) + ", " +
							to_string(matrix3x3Value[5]) + ", " +
							to_string(matrix3x3Value[6]) + ", " +
							to_string(matrix3x3Value[7]) + ", " +
							to_string(matrix3x3Value[8]) + ")";
					}
					break;
				case TYPE_MATRIX4x4:
					{
						auto& matrix4x4Value = getMatrix4x4ValueReference();
						result+=
							"Matrix4x4(" +
							to_string(matrix4x4Value[0]) + ", " +
							to_string(matrix4x4Value[1]) + ", " +
							to_string(matrix4x4Value[2]) + ", " +
							to_string(matrix4x4Value[3]) + ", " +
							to_string(matrix4x4Value[4]) + ", " +
							to_string(matrix4x4Value[5]) + ", " +
							to_string(matrix4x4Value[6]) + ", " +
							to_string(matrix4x4Value[7]) + ", " +
							to_string(matrix4x4Value[8]) + ", " +
							to_string(matrix4x4Value[9]) + ", " +
							to_string(matrix4x4Value[10]) + ", " +
							to_string(matrix4x4Value[11]) + ", " +
							to_string(matrix4x4Value[12]) + ", " +
							to_string(matrix4x4Value[13]) + ", " +
							to_string(matrix4x4Value[14]) + ", " +
							to_string(matrix4x4Value[15]) + ")";
					}
					break;
				case TYPE_TRANSFORM:
					{
						auto& transformValue = getTransformValueReference();
						result+=
							"Transform(translation = Vector3(" +
							to_string(transformValue.getTranslation().getX()) + ", " +
							to_string(transformValue.getTranslation().getY()) + ", " +
							to_string(transformValue.getTranslation().getZ()) + "), " +
							"scale = Vector3(" +
							to_string(transformValue.getScale().getX()) + ", " +
							to_string(transformValue.getScale().getY()) + ", " +
							to_string(transformValue.getScale().getZ()) + ")";
						for (auto i = 0; i < transformValue.getRotationCount(); i++) {
							result+= ", rotations = (axis = Vector3(" +
									to_string(transformValue.getRotationAxis(i).getX()) + ", " +
									to_string(transformValue.getRotationAxis(i).getY()) + ", " +
									to_string(transformValue.getRotationAxis(i).getZ()) + "), angle = " +
									to_string(transformValue.getRotationAngle(i)) + ")";
						}
						result+= ")";
					}
					break;
				case TYPE_ARRAY:
					{
						auto& arrayValue = getArrayValueReference();
						result+="[";
						string valuesString;
						for (auto& value: arrayValue) {
							if (valuesString.empty() == false) valuesString+= ", ";
							valuesString+= value.getValueString();
						}
						result+= valuesString;
						result+="]";
						break;
					}
				case TYPE_MAP:
					{
						auto& mapValue = getMapValueReference();
						result+="[";
						string valuesString;
						for (auto& it: mapValue) {
							if (valuesString.empty() == false) valuesString+= ", ";
							valuesString+= it.first +  " = " + it.second.getValueString();
						}
						result+= valuesString;
						result+="]";
						break;
					}
				case TYPE_PSEUDO_NUMBER:
					result+= "Number";

			}
			return result;
		}
	};

	/**
	 * Script State Machine State
	 */
	class ScriptStateMachineState {
	public:
		/**
		 * Constructor
		 */
		ScriptStateMachineState() {}

		/**
		 * Destructor
		 */
		virtual ~ScriptStateMachineState() {}

		/**
		 * @return name
		 */
		virtual const string getName() = 0;

		/**
		 * @return id
		 */
		virtual int getId() = 0;

		/**
		 * Execute script state machine state
		 */
		virtual void execute() = 0;
	};

	/**
	 * Script
	 */
	struct Script {
		enum ScriptType { SCRIPTTYPE_NONE, SCRIPTTYPE_FUNCTION, SCRIPTTYPE_ON, SCRIPTTYPE_ONENABLED };
		ScriptType scriptType;
		int line;
		string condition;
		string name;
		bool emitCondition;
		vector<ScriptStatement> statements;
	};

	/**
	 * Script method
	 */
	class ScriptMethod {
	public:
		struct ArgumentType {
			ScriptVariableType type;
			string name;
			bool optional;
		};

		/**
		 * Constructor
		 * @param argumentTypes argument types
		 * @param returnValueType return value type
		 */
		ScriptMethod(const vector<ArgumentType>& argumentTypes = {}, ScriptVariableType returnValueType = ScriptVariableType::TYPE_VOID): returnValueType(returnValueType), argumentTypes(argumentTypes) {}

		/**
		 * Destructor
		 */
		virtual ~ScriptMethod() {}

		/**
		 * @return script method name
		 */
		virtual const string getMethodName() = 0;

		/**
		 * Execute script method
		 * @param argumentValues argument values
		 * @param returnValue return value
		 * @param statement statement
		 */
		virtual void executeMethod(const span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) = 0;

		/**
		 * @return arguments
		 */
		const vector<ArgumentType>& getArgumentTypes() {
			return argumentTypes;
		}

		/**
		 * @return return value type
		 */
		const ScriptVariableType& getReturnValueType() {
			return returnValueType;
		}

		/**
		 * @return if variadic method
		 */
		virtual bool isVariadic() {
			return false;
		}

		/**
		 * @return if mixed return value
		 */
		virtual bool isMixedReturnValue() {
			return false;
		}

		/**
		 * @return operator
		 */
		virtual ScriptOperator getOperator() {
			return OPERATOR_NONE;
		}

		/**
		 * @return description
		 */
		virtual string getDescription() {
			return "No description.";
		}

	private:
		vector<ArgumentType> argumentTypes;
		ScriptVariableType returnValueType;
	};

protected:
	static constexpr int ARRAYIDX_NONE { -1 };
	static constexpr int ARRAYIDX_ADD { -2 };
	static constexpr int STATE_NONE { -1 };
	static constexpr int STATEMENTIDX_NONE { -1 };
	static constexpr int SCRIPTIDX_NONE { -1 };
	static constexpr int ARGUMENTIDX_NONE { -1 };
	static constexpr int OPERATORIDX_NONE { -1 };
	static constexpr int LINEIDX_NONE { -1 };
	static constexpr int64_t TIME_NONE { -1LL };

	struct ScriptState {
		enum EndType { ENDTYPE_FOR, ENDTYPE_IF };
		enum ConditionType {
			SCRIPT,
			CONDITIONTYPE_FORTIME
		};
		int state { STATE_NONE };
		int lastState { STATE_NONE };
		ScriptStateMachineState* lastStateMachineState { nullptr };
		bool running { false };
		int scriptIdx { SCRIPTIDX_NONE };
		int statementIdx { STATEMENTIDX_NONE };
		int64_t timeWaitStarted { TIME_NONE };
		int64_t timeWaitTime { TIME_NONE };
		string id;
		unordered_map<string, ScriptVariable*> variables;
		unordered_map<int, int64_t> forTimeStarted;
		stack<bool> conditionStack;
		stack<EndType> endTypeStack;
		// applies for functions only
		ScriptVariable returnValue;
	};

	//
	string hash;
	bool native;
	vector<Script> scripts;
	vector<Script> nativeScripts;
	vector<ScriptState> scriptStateStack;

	// root context variables
	vector<string> enabledNamedConditions;
	int64_t timeEnabledConditionsCheckLast { TIME_NONE };

	/**
	 * Initialize native mini script
	 */
	virtual void initializeNative();

	/**
	 * @return if this script was compiled to C++ and is executed nativly
	 */
	inline bool getNative() {
		return native;
	}

	/**
	 * Set native
	 * @param native native
	 */
	inline void setNative(bool native) {
		this->native = native;
	}

	/**
	 * Set hash
	 * @param hash hash
	 */
	inline void setHash(const string& hash) {
		this->hash = hash;
	}

	/**
	 * Goto statement from given statements goto statement
	 * @param statement statement
	 */
	void gotoStatementGoto(const ScriptStatement& statement) {
		getScriptState().statementIdx = statement.gotoStatementIdx;
	}

	/**
	 * @return native script
	 */
	inline vector<Script> getNativeScripts() {
		return nativeScripts;
	}

	/**
	 * Set native scripts
	 * @param native native scripts
	 */
	inline void setNativeScripts(const vector<Script>& nativeScripts) {
		this->nativeScripts = nativeScripts;
	}

	/**
	 * Execute state machine
	 */
	void executeStateMachine();

	/**
	 * Reset script execution state
	 * @param scriptIdx script index
	 * @param stateMachineState state machine state
	 */
	inline void resetScriptExecutationState(int scriptIdx, StateMachineState stateMachineState) {
		auto& scriptState = getScriptState();
		if (isFunctionRunning() == false) enabledNamedConditions.clear();
		scriptState.forTimeStarted.clear();
		while (scriptState.conditionStack.empty() == false) scriptState.conditionStack.pop();
		while (scriptState.endTypeStack.empty() == false) scriptState.endTypeStack.pop();
		scriptState.id.clear();
		scriptState.scriptIdx = scriptIdx;
		scriptState.statementIdx = 0;
		scriptState.timeWaitStarted = Time::getCurrentMillis();
		scriptState.timeWaitTime = 0LL;
		setScriptStateState(stateMachineState);
	}

	/**
	 * Stop script execution
	 */
	inline void stopScriptExecutation() {
		auto& scriptState = getScriptState();
		//
		scriptState.running = false;
		for (auto& scriptVariableIt: scriptState.variables) delete scriptVariableIt.second;
		scriptState.variables.clear();
		if (isFunctionRunning() == false) timeEnabledConditionsCheckLast = TIME_NONE;
		resetScriptExecutationState(SCRIPTIDX_NONE, STATEMACHINESTATE_NONE);
	}

	/**
	 * Set script state machine state
	 * @param state state
	 */
	inline void setScriptStateState(int state) {
		auto& scriptState = getScriptState();
		scriptState.state = state;
		scriptState.lastState = STATE_NONE;
		scriptState.lastStateMachineState = nullptr;
	}

	/**
	 * @return is function running
	 */
	inline bool isFunctionRunning() {
		return scriptStateStack.size() > 1;
	}

	/**
	 * Push a new script state
	 */
	inline void pushScriptState() {
		scriptStateStack.push_back(ScriptState());
	}

	/**
	 * Pop script state
	 */
	inline void popScriptState() {
		auto& scriptState = getScriptState();
		for (auto& scriptVariableIt: scriptState.variables) delete scriptVariableIt.second;
		scriptStateStack.erase(scriptStateStack.begin() + scriptStateStack.size() - 1);
	}

	/**
	 * Determine script index to start
	 * @return script index or SCRIPTIDX_NONE if no script to start
	 */
	virtual int determineScriptIdxToStart();

	/**
	 * Determine named script index to start
	 * @return script index or SCRIPTIDX_NONE if no script to start
	 */
	virtual int determineNamedScriptIdxToStart();

private:
	static constexpr bool VERBOSE { false };

	//
	STATIC_DLL_IMPEXT static string OPERATOR_CHARS;

	// TODO: maybe we need a better naming for this
	// script functions defined by script itself
	unordered_map<string, int> scriptFunctions;
	// script methods defined by using ScriptMethod
	unordered_map<string, ScriptMethod*> scriptMethods;
	unordered_map<int, ScriptStateMachineState*> scriptStateMachineStates;
	unordered_map<uint8_t, ScriptMethod*> scriptOperators;
	string scriptPathName;
	string scriptFileName;
	bool scriptValid { false };

	//
	struct ScriptStatementOperator {
		int idx { OPERATORIDX_NONE };
		ScriptOperator scriptOperator;
	};

	/**
	 * Returns arguments as string placed in a vector of string_views
	 * @param arguments arguments
	 * @return arguments as string
	 */
	inline const string getArgumentsAsString(const vector<string_view>& arguments) {
		string argumentsString;
		for (auto& argument: arguments) argumentsString+= (argumentsString.empty() == false?", ":"") + string("'") + string(argument) + string("'");
		return argumentsString;
	}

	/**
	 * Execute a single script line
	 */
	void executeScriptLine();

	/**
	 * Parse a script statement
	 * @param statement statement 
	 * @param method method
	 * @param arguments arguments
	 * @return success
	 */
	bool parseScriptStatement(const string_view& statement, string_view& method, vector<string_view>& arguments);

	/**
	 * Execute a script statement
	 * @param method method 
	 * @param arguments arguments
	 * @param statement statement
	 * @return return value as script variablle
	 */
	ScriptVariable executeScriptStatement(const string_view& method, const vector<string_view>& arguments, const ScriptStatement& statement);

	/**
	 * Returns if char is operator char
	 * @param c char to test
	 * @return if char is operator char
	 */
	static inline const bool isOperatorChar(char c) {
		return OPERATOR_CHARS.find(c) != string::npos;
	}

	/**
	 * Determine next not substituted operator in statement
	 * @param statement statement
	 * @param nextOperator next operator
	 */
	bool getNextStatementOperator(const string& statement, ScriptStatementOperator& nextOperator);

	/**
	 * Trim argument and remove unnessessary parenthesis
	 * @param argument argument
	 * @return processed argument
	 */
	const string trimArgument(const string& argument);

	/**
	 * Find right argument in statement beginning from position
	 * @param statement statement
	 * @param position position
	 * @param length argument length
	 * @param brackets barrier brackets
	 */
	const string findRightArgument(const string statement, int position, int& length, string& brackets);

	/**
	 * Find left argument in statement beginning from position
	 * @param statement statement
	 * @param position position
	 * @param length argument length
	 * @param brackets barrier brackets
	 */
	const string findLeftArgument(const string statement, int position, int& length, string& brackets);

	/**
	 * Do statement pre processing, 1) replace operators with corresponding methods
	 * @param statement statement
	 */
	const string doStatementPreProcessing(const string& statement);

	/**
	 * Transpile script statement
	 * @param generatedCode generated code
	 * @param method method
	 * @param arguments arguments
	 * @param statement script statement
	 * @param scriptIdx script index
	 * @param statementIdx statement index
	 * @param methodCodeMap method code map
	 * @param scriptStateChanged script could have state changed
	 * @param scriptStopped script could have been stopped
	 * @param enabledNamedConditions enabled named conditions
	 * @param depth depth
	 * @param argumentIdx argument index
	 * @param parentArgumentIdx parent argument index
	 * @param returnValue return value
	 * @param injectCode code to additionally inject
	 * @param additionalIndent additional indent
	 */
	bool transpileScriptStatement(string& generatedCode, const string_view& method, const vector<string_view>& arguments, const ScriptStatement& statement, int scriptIdx, int& statementIdx, const unordered_map<string, vector<string>>& methodCodeMap, bool& scriptStateChanged, bool& scriptStopped, vector<string>& enabledNamedConditions, int depth = 0, int argumentIdx = ARGUMENTIDX_NONE, int parentArgumentIdx = ARGUMENTIDX_NONE, const string& returnValue = string(), const string& injectCode = string(), int additionalIndent = 0);

	/**
	 * Get access operator left and right indices
	 * @param name name
	 * @param callerMethod caller method
	 * @param accessOperatorLeftIdx access operator left idx
	 * @param accessOperatorRightIdx access operator right idx
	 * @param statement statement
	 * @param startIdx startIdx
	 */
	inline bool getVariableAccessOperatorLeftRightIndices(const string& name, const string& callerMethod, string::size_type& accessOperatorLeftIdx, string::size_type& accessOperatorRightIdx, const ScriptStatement* statement = nullptr, int startIdx = 0) {
		accessOperatorLeftIdx = string::npos;
		accessOperatorRightIdx = string::npos;
		auto haveKey = false;
		auto squareBracketsCount = 0;
		// improve me!
		if (startIdx > 0) {
			haveKey = name[startIdx - 1] == '.';
			if (haveKey == true) accessOperatorLeftIdx = startIdx - 1;
		}
		for (auto i = startIdx; i < name.length(); i++) {
			auto c = name[i];
			if (haveKey == true) {
				if (c == '.') {
					//
					accessOperatorRightIdx = i;
					//
					return true;
				} else
				if (c == '[') {
					//
					accessOperatorRightIdx = i;
					//
					return true;
				}
				if (c == ']') {
					if (statement != nullptr) {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': unexpected char: ']'");
					} else {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': variable: '" + name + "': unexpected char: ']'");
					}
					return false;
				}
			} else
			if (c == '.' && squareBracketsCount == 0) {
				haveKey = true;
				accessOperatorLeftIdx = i;
			} else
			if (c == '[') {
				if (squareBracketsCount == 0) accessOperatorLeftIdx = i;
				squareBracketsCount++;
			} else
			if (c == ']') {
				squareBracketsCount--;
				if (squareBracketsCount == 0) {
					//
					accessOperatorRightIdx = i + 1;
					//
					return true;
				} else
				if (squareBracketsCount < 0) {
					if (statement != nullptr) {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': unexpected char: ']'");
					} else {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': variable: '" + name + "': unexpected char: ']'");
					}
					return false;
				}
			}
		}
		//
		if (haveKey == true) accessOperatorRightIdx = name.size();
		//
		return true;
	}

	/**
	 * Evaluate access
	 * @param name name
	 * @param callerMethod caller method
	 * @param arrayAccessOperatorLeftIdx array access operator left idx
	 * @param arrayAccessOperatorRightIdx array access operator right idx
	 * @param arrayIdx array index
	 * @param key map key
	 * @param statement statement
	 */
	inline bool evaluateAccess(const string& name, const string& callerMethod, string::size_type& arrayAccessOperatorLeftIdx, string::size_type& arrayAccessOperatorRightIdx, int64_t& arrayIdx, string& key, const ScriptStatement* statement = nullptr) {
		key.clear();
		arrayIdx = ARRAYIDX_NONE;
		// check for dot access
		if (name.data()[arrayAccessOperatorLeftIdx] == '.') {
			key = string(StringTools::viewTrim(string_view(&name.data()[arrayAccessOperatorLeftIdx + 1], arrayAccessOperatorRightIdx - arrayAccessOperatorLeftIdx - 1)));
			return true;
		}
		// evaluate array index
		auto arrayIdxExpressionStringView = StringTools::viewTrim(string_view(&name.data()[arrayAccessOperatorLeftIdx + 1], arrayAccessOperatorRightIdx - arrayAccessOperatorLeftIdx - 2));
		if (arrayIdxExpressionStringView.empty() == false) {
			ScriptVariable statementReturnValue;
			if (evaluate(string(arrayIdxExpressionStringView), statementReturnValue) == false || statementReturnValue.getIntegerValue(arrayIdx, false) == false) {
				if (statement != nullptr) {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': failed to evaluate expression: '" + string(arrayIdxExpressionStringView) + "'");
				} else {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': failed to evaluate expression: '" + string(arrayIdxExpressionStringView) + "'");
				}
				return false;
			}
		} else {
			arrayIdx = ARRAYIDX_ADD;
		}
		//
		return true;
	}

	/**
	 * Returns pointer of variable with given name or nullptr
	 * @param name name
	 * @param callerMethod caller method
	 * @param parentVariable parent variable
	 * @param arrayIdx array index whereas there is ARRAYIDX_ADD for [] or ARRAYIDX_NONE for no array access
	 * @param key key
	 * @param statement optional statement the variable is read in
	 * @param expectVariable expect variable which controls verbosity
	 * @return pointer to variable
	 */
	inline ScriptVariable* getVariableIntern(const string& name, const string& callerMethod, ScriptVariable*& parentVariable, int64_t& arrayIdx, string& key, const ScriptStatement* statement = nullptr, bool expectVariable = true) {
		//
		if (StringTools::startsWith(name, "$") == false) {
			if (statement != nullptr) {
				Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': variable names must start with an $");
			} else {
				Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': variable names must start with an $");
			}
			return nullptr;
		}
		// get root variable
		key.clear();
		// no array idx by default
		arrayIdx = ARRAYIDX_NONE;
		// determine left and right access operator position if there are any
		auto accessOperatorLeftIdx = string::npos;
		auto accessOperatorRightIdx = string::npos;
		if (getVariableAccessOperatorLeftRightIndices(name, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, statement) == false) {
			return nullptr;
		}
		// access operator, if we have any, evaluate the array index
		auto haveAccessOperator = accessOperatorLeftIdx != string::npos && accessOperatorRightIdx != string::npos;
		auto extractedVariableName = haveAccessOperator == true?StringTools::substring(name, 0, accessOperatorLeftIdx):string();
		if (haveAccessOperator == true &&
			evaluateAccess(name, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, arrayIdx, key, statement) == false) {
			return nullptr;
		}
		// retrieve variable from function script state
		ScriptVariable* variablePtr = nullptr;
		{
			auto& scriptState = getScriptState();
			auto scriptVariableIt = scriptState.variables.find(extractedVariableName.empty() == false?extractedVariableName:name);
			if (scriptVariableIt == scriptState.variables.end()) {
				if (isFunctionRunning() == false) {
					if (expectVariable == true) {
						if (statement != nullptr) {
							Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "' does not exist");
						} else {
							Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "' does not exist");
						}
					}
					return nullptr;
				}
			} else {
				variablePtr = scriptVariableIt->second;
			}
		}
		// if no success try to retrieve variable from root script state
		if (variablePtr == nullptr) {
			auto& scriptState = getRootScriptState();
			auto scriptVariableIt = scriptState.variables.find(extractedVariableName.empty() == false?extractedVariableName:name);
			if (scriptVariableIt == scriptState.variables.end()) {
				if (expectVariable == true) {
					if (statement != nullptr) {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "' does not exist");
					} else {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "' does not exist");
					}
				}
				return nullptr;
			} else {
				variablePtr = scriptVariableIt->second;
			}
		}
		// get pointer to children variable
		if (haveAccessOperator == false) {
			//
			return variablePtr;
		} else {
			// resolve first parsed access pattern and repeat until resolved
			while (haveAccessOperator == true) {
				// map key access
				if (key.empty() == false) {
					if (variablePtr->getType() != TYPE_MAP) {
						if (statement != nullptr) {
							Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': map access operator, but variable is not of type map");
						} else {
							Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': map access operator, but variable is not of type map");
						}
						return nullptr;
					}
					//
					auto& mapValueReference = variablePtr->getMapValueReference();
					// key
					auto mapIt = mapValueReference.find(key);
					if (mapIt != mapValueReference.end()) {
						//
						parentVariable = variablePtr;
						//
						variablePtr = &mapIt->second;
					} else {
						if (expectVariable == true) {
							if (statement != nullptr) {
								Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': key not found: '" + key + "'");
							} else {
								Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': key not found: '" + key + "'");
							}
						}
						// we have our parent
						parentVariable = variablePtr;
						//
						return nullptr;
					}
				} else {
					if (variablePtr->getType() != TYPE_ARRAY) {
						if (statement != nullptr) {
							Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': array access operator, but variable is not of type array");
						} else {
							Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': array access operator, but variable is not of type array");
						}
						return nullptr;
					}
					auto& arrayValueReference = variablePtr->getArrayValueReference();
					// otherwise array
					if (arrayIdx == ARRAYIDX_ADD) {
						// we have our parent
						parentVariable = variablePtr;
						//
						return nullptr;
					} else
					if (arrayIdx >= 0 && arrayIdx < arrayValueReference.size()) {
						//
						parentVariable = variablePtr;
						//
						variablePtr = &arrayValueReference[arrayIdx];
					} else {
						if (statement != nullptr) {
							Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': index out of bounds: 0 <= " + to_string(arrayIdx) + " < " + to_string(arrayValueReference.size()));
						} else {
							Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': index out of bounds: 0 <= " + to_string(arrayIdx) + " <= " + to_string(arrayValueReference.size()));
						}
						return nullptr;
					}
				}

				//
				auto accessOperatorStartIdx = accessOperatorRightIdx;
				accessOperatorLeftIdx = string::npos;
				accessOperatorRightIdx = string::npos;
				if (getVariableAccessOperatorLeftRightIndices(name, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, statement, accessOperatorStartIdx) == false) {
					// fail
					return nullptr;
				}

				// do we have a next array access next to previous one?
				haveAccessOperator = accessOperatorLeftIdx != string::npos && accessOperatorRightIdx != string::npos;
				if (haveAccessOperator == false) {
					return variablePtr;
				} else {
					// yep, evaluate it
					if (evaluateAccess(name, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, arrayIdx, key, statement) == false) {
						return nullptr;
					}

				}
			}
			//
			return variablePtr;
		}
	}

	/**
	 * Transpile a script statement
	 * @param generatedCode generated code
	 * @param scriptIdx script index
	 * @param methodCodeMap method code map
	 * @return success
	 */
	bool transpile(string& generatedCode, int scriptIdx, const unordered_map<string, vector<string>>& methodCodeMap);

	/**
	 * Transpile a script condition
	 * @param generatedCode generated code
	 * @param scriptIdx script index
	 * @param methodCodeMap method code map
	 * @param returnValue return value
	 * @param injectCode inject code
	 * @return success
	 */
	bool transpileScriptCondition(string& generatedCode, int scriptIdx, const unordered_map<string, vector<string>>& methodCodeMap, const string& returnValue, const string& injectCode, int depth = 0);

public:
	/**
	 * Default constructor
	 */
	MiniScript();

	/**
	 * Destructor
	 */
	virtual ~MiniScript();

	/**
	 * @return script hash
	 */
	inline const string& getHash() {
		return hash;
	}

	/**
	 * @return scripts
	 */
	const vector<Script>& getScripts() {
		return scripts;
	}

	/**
	 * @return script state
	 */
	inline ScriptState& getRootScriptState() {
		return scriptStateStack[0];
	}

	/**
	 * @return script state
	 */
	inline ScriptState& getScriptState() {
		return scriptStateStack[scriptStateStack.size() - 1];
	}

	/**
	 * Start error script
	 */
	inline void startErrorScript() {
		emit("error");
	}

	/**
	 * Register state machine states
	 */
	virtual void registerStateMachineStates();

	/**
	 * Register methods
	 */
	virtual void registerMethods();

	/**
	 * Register variables
	 */
	virtual void registerVariables();

	/**
	 * Get operator as string
	 * @param scriptOperator script operator
	 * @return script operator as string
	 */
	inline static string getOperatorAsString(ScriptOperator scriptOperator) {
		switch(scriptOperator) {
			case(OPERATOR_NONE): return "NONE";
			case(OPERATOR_NOT): return "!";
			case(OPERATOR_MULTIPLICATION): return "*";
			case(OPERATOR_DIVISION): return "/";
			case(OPERATOR_REMAINDER): return "%";
			case(OPERATOR_ADDITION): return "+";
			case(OPERATOR_SUBTRACTION): return "-";
			case(OPERATOR_LESSER): return "<";
			case(OPERATOR_LESSEREQUALS): return "<=";
			case(OPERATOR_GREATER): return ">";
			case(OPERATOR_GREATEREQUALS): return ">=";
			case(OPERATOR_EQUALS): return "==";
			case(OPERATOR_NOTEQUAL): return "!=";
			case(OPERATOR_AND): return "&&";
			case(OPERATOR_OR): return "||";
			case(OPERATOR_SET): return "=";
			case(OPERATOR_MAX): return "MAX";
			default: return "INVALID";
		}
	}

	/**
	 * Check if arguments contain argument with given type
	 * @param arguments arguments
	 * @param type type
	 * @return has type
	 */
	inline static bool hasType(const span<ScriptVariable>& arguments, ScriptVariableType type) {
		for (auto& argument: arguments) if (argument.getType() == type) return true;
		return false;
	}

	/**
	 * Get boolean value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optionalfalse
	 * @return success
	 */
	inline static bool getBooleanValue(const span<ScriptVariable>& arguments, int idx, bool& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getBooleanValue(value, optional);
	}

	/**
	 * Get integer value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getIntegerValue(const span<ScriptVariable>& arguments, int idx, int64_t& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getIntegerValue(value, optional);
	}

	/**
	 * Get float value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getFloatValue(const span<ScriptVariable>& arguments, int idx, float& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getFloatValue(value, optional);
	}

	/**
	 * Get string value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getStringValue(const span<ScriptVariable>& arguments, int idx, string& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getStringValue(value, optional);
	}

	/**
	 * Get vector2 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getVector2Value(const span<ScriptVariable>& arguments, int idx, Vector2& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getVector2Value(value, optional);
	}

	/**
	 * Get vector3 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getVector3Value(const span<ScriptVariable>& arguments, int idx, Vector3& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getVector3Value(value, optional);
	}

	/**
	 * Get vector4 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getVector4Value(const span<ScriptVariable>& arguments, int idx, Vector4& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getVector4Value(value, optional);
	}

	/**
	 * Get vector4 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getQuaternionValue(const span<ScriptVariable>& arguments, int idx, Quaternion& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getQuaternionValue(value, optional);
	}

	/**
	 * Get matrix3x3 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getMatrix3x3Value(const span<ScriptVariable>& arguments, int idx, Matrix2D3x3& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getMatrix3x3Value(value, optional);
	}

	/**
	 * Get matrix4x4 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getMatrix4x4Value(const span<ScriptVariable>& arguments, int idx, Matrix4x4& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getMatrix4x4Value(value, optional);
	}

	/**
	 * Get transform value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getTransformValue(const span<ScriptVariable>& arguments, int idx, Transform& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getTransformValue(value, optional);
	}

	/**
	 * Get array value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getArrayValue(const span<ScriptVariable>& arguments, int idx, vector<ScriptVariable>& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getArrayValue(value, optional);
	}

	/**
	 * Get map value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getMapValue(const span<ScriptVariable>& arguments, int idx, unordered_map<string, ScriptVariable>& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getMapValue(value, optional);
	}

	/**
	 * Register script state machine state
	 * @param state state
	 */
	void registerStateMachineState(ScriptStateMachineState* state);

	/**
	 * Register script method
	 * @param method method
	 */
	void registerMethod(ScriptMethod* method);

	/**
	 * Returns variable with given name
	 * @param name name
	 * @param statement optional statement the variable is read in
	 * @return variable
	 */
	inline const ScriptVariable getVariable(const string& name, const ScriptStatement* statement = nullptr) {
		ScriptVariable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		auto variablePtr = getVariableIntern(name, __FUNCTION__, parentVariable, arrayIdx, key, statement, false);
		if (variablePtr != nullptr) {
			return *variablePtr;
		} else {
			return ScriptVariable();
		}
	}

	/**
	 * Set script variable
	 * @param name name
	 * @param variable variable
	 * @param statement optional statement the variable is written in
	 */
	inline void setVariable(const string& name, const ScriptVariable& variable, const ScriptStatement* statement = nullptr) {
		ScriptVariable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		auto variablePtr = getVariableIntern(name, __FUNCTION__, parentVariable, arrayIdx, key, statement, false);
		// common case
		if (variablePtr != nullptr) {
			*variablePtr = variable;
			return;
		} else
		// array add operator
		if (key.empty() == false) {
			if (parentVariable == nullptr) {
				string callerMethod = __FUNCTION__;
				if (statement != nullptr) {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': map access operator without map: '" + key + "'");
				} else {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': map access operator without map: '" + key + "'");
				}
			} else
			if (parentVariable->getType() != MiniScript::TYPE_MAP) {
				string callerMethod = __FUNCTION__;
				if (statement != nullptr) {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': map access operator: expected map, but got " + parentVariable->getTypeAsString() + ": '" + key + "'");
				} else {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': map access operator: expected map, but got " + parentVariable->getTypeAsString() + ": '" + key + "'");
				}
			} else {
				// all checks passed, push to map
				parentVariable->setMapValue(key, variable);
			}
			//
			return;
		} else
		if (arrayIdx == ARRAYIDX_ADD) {
			if (parentVariable == nullptr) {
				string callerMethod = __FUNCTION__;
				if (statement != nullptr) {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': [] array push operator without array");
				} else {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': [] array push operator without array");
				}
			} else
			if (parentVariable->getType() != MiniScript::TYPE_ARRAY) {
				string callerMethod = __FUNCTION__;
				if (statement != nullptr) {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': [] array push operator: expected array , but got " + parentVariable->getTypeAsString());
				} else {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': [] array push operator: expected array, but got " + parentVariable->getTypeAsString());
				}
			} else {
				// all checks passed, push variable to array
				auto& arrayValueReference = parentVariable->getArrayValueReference();
				arrayValueReference.push_back(variable);
			}
			//
			return;
		}

		// default
		auto& scriptState = getScriptState();
		auto scriptVariableIt = scriptState.variables.find(name);
		if (scriptVariableIt != scriptState.variables.end()) {
			*scriptVariableIt->second = variable;
			return;
		} else {
			auto scriptVariable = new ScriptVariable();
			*scriptVariable = variable;
			scriptState.variables[name] = scriptVariable;
		}
	}

	/**
	 * Unset script variable
	 * @param name name
	 * @param statement optional statement the variable is unset in
	 */
	inline void unsetVariable(const string& name, const ScriptStatement* statement = nullptr) {
		// TODO:
	}

	/**
	 * Load script
	 * @param pathName path name
	 * @param fileName file name
	 */
	void loadScript(const string& pathName, const string& fileName);

	/**
	 * Start script
	 */
	virtual void startScript();

	/**
	 * Emit
	 * @param condition condition
	 */
	virtual void emit(const string& condition);

	/**
	 * Execute
	 */
	virtual void execute();

	/**
	 * Evaluate given statement
	 * @param statement
	 * @return return value
	 */
	inline bool evaluate(const string& statement, ScriptVariable& returnValue) {
		auto scriptEvaluateStatement = "script.evaluate(" + statement + ")";
		string_view method;
		vector<string_view> arguments;
		pushScriptState();
		resetScriptExecutationState(SCRIPTIDX_NONE, STATEMACHINESTATE_NEXT_STATEMENT);
		getScriptState().running = true;
		if (parseScriptStatement(scriptEvaluateStatement, method, arguments) == true) {
			returnValue = executeScriptStatement(
				method,
				arguments,
				{
					.line = LINEIDX_NONE,
					.statementIdx = 0,
					.statement = "Evaluate: " + statement,
					.gotoStatementIdx = STATEMENTIDX_NONE
				}
			);
			popScriptState();
			return true;
		} else {
			popScriptState();
			return false;
		}
	}

	/**
	 * Call (script user) function
	 * @param function (script user) function
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @return success
	 */
	inline bool call(const string& function, const span<ScriptVariable>& argumentValues, ScriptVariable& returnValue) {
		auto scriptFunctionsIt = scriptFunctions.find(function);
		if (scriptFunctionsIt == scriptFunctions.end()) {
			Console::println("MiniScript::call(): Script user function not found: " + function);
			return false;
		}
		//
		auto scriptIdx = scriptFunctionsIt->second;
		// push a new script state
		pushScriptState();
		// script state vector could get modified, so
		{
			auto& scriptState = getScriptState();
			auto functionArguments = new ScriptVariable();
			functionArguments->setType(MiniScript::TYPE_ARRAY);
			// push arguments in function context
			for (auto& argumentValue: argumentValues) {
				functionArguments->pushArrayValue(argumentValue);
			}
			//
			scriptState.variables["$arguments"] = functionArguments;
		}
		//
		resetScriptExecutationState(scriptIdx, STATEMACHINESTATE_NEXT_STATEMENT);
		// script state vector could get modified, so
		{
			auto& scriptState = getScriptState();
			// run this function dude
			scriptState.running = true;
		}
		for (;true;) {
			execute();
			//
			auto& scriptState = getScriptState();
			// run this function dude
			if (scriptState.running == false) break;
		}
		// get return value
		{
			auto& scriptState = getScriptState();
			// run this function dude
			returnValue = scriptState.returnValue;
		}
		// done, pop the function script state
		popScriptState();
		//
		return true;
	}

	/**
	 * @return is running
	 */
	inline bool isRunning() {
		return getScriptState().running;
	}

	/**
	 * @return script methods
	 */
	const vector<ScriptMethod*> getMethods();

	/**
	 * @return script operator methods
	 */
	const vector<ScriptMethod*> getOperatorMethods();

	/**
	 * Get miniscript instance information
	 */
	const string getInformation();

};
