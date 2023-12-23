#pragma once

#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/miniscript/fwd-tdme.h>
#include <tdme/miniscript/MiniScriptMatrix3x3.h>
#include <tdme/miniscript/MiniScriptMatrix4x4.h>
#include <tdme/miniscript/MiniScriptMatrix4x4.h>
#include <tdme/miniscript/MiniScriptQuaternion.h>
#include <tdme/miniscript/MiniScriptTransform.h>
#include <tdme/miniscript/MiniScriptVector2.h>
#include <tdme/miniscript/MiniScriptVector3.h>
#include <tdme/miniscript/MiniScriptVector4.h>

using std::span;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using miniscript::miniscript::MiniScript;

using tdme::engine::Transform;
using tdme::math::Matrix3x3;
using tdme::math::Matrix4x4;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::miniscript::MiniScriptMatrix3x3;
using tdme::miniscript::MiniScriptMatrix4x4;
using tdme::miniscript::MiniScriptMatrix4x4;
using tdme::miniscript::MiniScriptQuaternion;
using tdme::miniscript::MiniScriptTransform;
using tdme::miniscript::MiniScriptVector2;
using tdme::miniscript::MiniScriptVector3;
using tdme::miniscript::MiniScriptVector4;

using tdme::utilities::Console;

/**
 * Engine MiniScript
 * @author Andreas Drewke
 */
class tdme::miniscript::EngineMiniScript: public MiniScript {
public:
	// forbid class copy
	FORBID_CLASS_COPY(EngineMiniScript)

	// custom data types, which needs to be created in this particular order
	//	we could also read the types dynamically, but this works for now :)
	static constexpr VariableType TYPE_TRANSFORM { static_cast<VariableType>(VariableType::TYPE_PSEUDO_CUSTOM_DATATYPES) };
	static constexpr VariableType TYPE_MATRIX4x4 { static_cast<VariableType>(VariableType::TYPE_PSEUDO_CUSTOM_DATATYPES + 1) };
	static constexpr VariableType TYPE_MATRIX3x3 { static_cast<VariableType>(VariableType::TYPE_PSEUDO_CUSTOM_DATATYPES + 2) };
	static constexpr VariableType TYPE_QUATERNION { static_cast<VariableType>(VariableType::TYPE_PSEUDO_CUSTOM_DATATYPES + 3) };
	static constexpr VariableType TYPE_VECTOR2 { static_cast<VariableType>(VariableType::TYPE_PSEUDO_CUSTOM_DATATYPES + 4) };
	static constexpr VariableType TYPE_VECTOR3 { static_cast<VariableType>(VariableType::TYPE_PSEUDO_CUSTOM_DATATYPES + 5) };
	static constexpr VariableType TYPE_VECTOR4 { static_cast<VariableType>(VariableType::TYPE_PSEUDO_CUSTOM_DATATYPES + 6) };

	/**
	 * Register data types
	 */
	static void registerDataTypes();

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

	// overridden methods
	const string getBaseClass();
	const vector<string> getTranspilationUnits();

	/**
	 * Get vector2 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline bool getVector2Value(const span<Variable>& arguments, int idx, Vector2& value, bool optional = false) {
		return MiniScriptVector2::getVector2Value(TYPE_VECTOR2, arguments, idx, value, optional);
	}

	/**
	 * Get vector3 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline bool getVector3Value(const span<Variable>& arguments, int idx, Vector3& value, bool optional = false) {
		return MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, idx, value, optional);
	}

	/**
	 * Get vector4 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline bool getVector4Value(const span<Variable>& arguments, int idx, Vector4& value, bool optional = false) {
		return MiniScriptVector4::getVector4Value(TYPE_VECTOR4, arguments, idx, value, optional);
	}

	/**
	 * Get vector4 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getQuaternionValue(const span<Variable>& arguments, int idx, Quaternion& value, bool optional = false) {
		return MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, idx, value, optional);
	}

	/**
	 * Get matrix3x3 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getMatrix3x3Value(const span<Variable>& arguments, int idx, Matrix3x3& value, bool optional = false) {
		return MiniScriptMatrix3x3::getMatrix3x3Value(TYPE_MATRIX3x3, arguments, idx, value, optional);
	}

	/**
	 * Get matrix4x4 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getMatrix4x4Value(const span<Variable>& arguments, int idx, Matrix4x4& value, bool optional = false) {
		return MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, arguments, idx, value, optional);
	}

	/**
	 * Get transform value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getTransformValue(const span<Variable>& arguments, int idx, Transform& value, bool optional = false) {
		return MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, idx, value, optional);
	}

	/**
	 * Set boolean value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, bool value) {
		variable.setValue(value);
	}

	/**
	 * Set integer value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, int64_t value) {
		variable.setValue(value);
	}

	/**
	 * Set float value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, float value) {
		variable.setValue(value);
	}

	/**
	 * Set string value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, const string& value) {
		variable.setValue(value);
	}

	/**
	 * Set array value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, const vector<Variable*>& value) {
		variable.setValue(value);
	}

	/**
	 * Set map value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, const unordered_map<string, Variable*>& value) {
		variable.setValue(value);
	}

	/**
	 * Set set value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, const unordered_set<string>& value) {
		variable.setValue(value);
	}

	/**
	 * Set vector2 value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, const Vector2& value) {
		variable.setType(TYPE_VECTOR2);
		variable.setValue(&value);
	}

	/**
	 * Set vector3 value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, const Vector3& value) {
		variable.setType(TYPE_VECTOR3);
		variable.setValue(&value);
	}

	/**
	 * Set vector3 value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, const Vector4& value) {
		variable.setType(TYPE_VECTOR4);
		variable.setValue(&value);
	}

	/**
	 * Set vector3 value from given value into variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, const Quaternion& value) {
		variable.setType(TYPE_QUATERNION);
		variable.setValue(&value);
	}

	/**
	 * Set matrix3x3 value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, const Matrix3x3& value) {
		variable.setType(TYPE_MATRIX3x3);
		variable.setValue(&value);
	}

	/**
	 * Set matrix4x4 value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, const Matrix4x4& value) {
		variable.setType(TYPE_MATRIX4x4);
		variable.setValue(&value);
	}

	/**
	 * Set transform value from given value into variable
	 * @param variable variable
	 * @param value value
	 */
	inline void setValue(Variable& variable, const Transform& value) {
		variable.setType(TYPE_TRANSFORM);
		variable.setValue(&value);
	}

};
