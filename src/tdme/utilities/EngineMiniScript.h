#pragma once

#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/MiniScript.h>

using std::span;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::utilities::EngineMiniScript;

using tdme::engine::Transform;
using tdme::math::Matrix3x3;
using tdme::math::Matrix4x4;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;

using tdme::utilities::Console;
using tdme::utilities::MiniScript;

/**
 * Engine MiniScript
 * @author Andreas Drewke
 */
class EngineMiniScript: public MiniScript {
public:
	// forbid class copy
	FORBID_CLASS_COPY(EngineMiniScript)

	static constexpr ScriptVariableType TYPE_VECTOR2 { static_cast<ScriptVariableType>(-1) };
	static constexpr ScriptVariableType TYPE_VECTOR3 { static_cast<ScriptVariableType>(-1) };
	static constexpr ScriptVariableType TYPE_VECTOR4 { static_cast<ScriptVariableType>(-1) };
	static constexpr ScriptVariableType TYPE_QUATERNION { static_cast<ScriptVariableType>(-1) };
	static constexpr ScriptVariableType TYPE_MATRIX3x3 { static_cast<ScriptVariableType>(-1) };
	static constexpr ScriptVariableType TYPE_MATRIX4x4 { static_cast<ScriptVariableType>(-1) };
	static constexpr ScriptVariableType TYPE_TRANSFORM { static_cast<ScriptVariableType>(-1) };

	/**
	 * Load script
	 * @param pathName path name
	 * @param fileName file name
	 */
	static EngineMiniScript* loadScript(const string& pathName, const string& fileName);

	/**
	 * Public constructor
	 */
	EngineMiniScript();


	/**
	 * Get vector2 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline bool getVector2Value(const span<ScriptVariable>& arguments, int idx, Vector2& value, bool optional = false) {
		return false;
	}

	/**
	 * Get vector3 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline bool getVector3Value(const span<ScriptVariable>& arguments, int idx, Vector3& value, bool optional = false) {
		return false;
	}

	/**
	 * Get vector4 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline bool getVector4Value(const span<ScriptVariable>& arguments, int idx, Vector4& value, bool optional = false) {
		return false;
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
		return false;
	}

	/**
	 * Get matrix3x3 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getMatrix3x3Value(const span<ScriptVariable>& arguments, int idx, Matrix3x3& value, bool optional = false) {
		return false;
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
		return false;
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
		return false;
	}

	/**
	 * Set boolean value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, bool value) {
	}

	/**
	 * Set integer value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, int64_t value) {
	}

	/**
	 * Set float value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, float value) {
	}

	/**
	 * Set string value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, const string& value) {
	}

	/**
	 * Set vector2 value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, const Vector2& value) {
	}

	/**
	 * Set vector3 value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, const Vector3& value) {
	}

	/**
	 * Set vector3 value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, const Vector4& value) {
	}

	/**
	 * Set vector3 value from given value into variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, const Quaternion& value) {
	}

	/**
	 * Set matrix3x3 value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, const Matrix3x3& value) {
	}

	/**
	 * Set matrix4x4 value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, const Matrix4x4& value) {
	}

	/**
	 * Set transform value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, const Transform& value) {
	}

	/**
	 * Set array value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, const vector<ScriptVariable*>& value) {
	}

	/**
	 * Set map value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, const unordered_map<string, ScriptVariable*>& value) {
	}

	/**
	 * Set set value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(ScriptVariable& variable, const unordered_set<string>& value) {
	}
};
