#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMatrix4x4.h>

using std::span;
using std::string;

using tdme::math::Matrix4x4;
using tdme::utilities::Float;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMatrix4x4;

const string MiniScriptMatrix4x4::CLASS_NAME = "mat3";
const string MiniScriptMatrix4x4::TYPE_NAME = "Matrix4x4";

void MiniScriptMatrix4x4::registerMethods() const {
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::ScriptVariableType>(getType());
}

void MiniScriptMatrix4x4::unsetScriptVariableValue(MiniScript::ScriptVariable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Matrix4x4*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptMatrix4x4::setScriptVariableValue(MiniScript::ScriptVariable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Matrix4x4 matrix4x4Value;
	if (value != 0ll) {
		matrix4x4Value = *static_cast<const Matrix4x4*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Matrix4x4*>((void*)variable.getValuePtr()) = matrix4x4Value;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Matrix4x4(matrix4x4Value)));
}

void MiniScriptMatrix4x4::copyScriptVariable(MiniScript::ScriptVariable& to, const MiniScript::ScriptVariable& from) const {
	//
	Matrix4x4 matrix4x4Value;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		matrix4x4Value = *static_cast<Matrix4x4*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::ScriptVariableType>(getType());
	to.setType(TYPE_MATRIX4x4);
	*static_cast<Matrix4x4*>((void*)to.getValuePtr()) = matrix4x4Value;
}

bool MiniScriptMatrix4x4::mul(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptMatrix4x4::div(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptMatrix4x4::add(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptMatrix4x4::sub(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

const string& MiniScriptMatrix4x4::getClassName() const {
	return CLASS_NAME;
}

const string& MiniScriptMatrix4x4::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptMatrix4x4::getValueAsString(const MiniScript::ScriptVariable& variable) const {
	//
	Matrix4x4 matrix4x4Value;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		matrix4x4Value = *static_cast<Matrix4x4*>((void*)variable.getValuePtr());
	}
	return
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
		to_string(matrix4x4Value[12]) + ", " +
		to_string(matrix4x4Value[13]) + ", " +
		to_string(matrix4x4Value[14]) + ", " +
		to_string(matrix4x4Value[15]) + ")";

}

