#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMatrix3x3.h>

using std::span;
using std::string;

using tdme::math::Matrix3x3;
using tdme::utilities::Float;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMatrix3x3;

const string MiniScriptMatrix3x3::CLASS_NAME = "mat3";
const string MiniScriptMatrix3x3::TYPE_NAME = "Matrix3x3";

void MiniScriptMatrix3x3::registerMethods() const {
	const auto TYPE_MATRIX3x3 = static_cast<MiniScript::ScriptVariableType>(getType());
}

void MiniScriptMatrix3x3::unsetScriptVariableValue(MiniScript::ScriptVariable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Matrix3x3*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptMatrix3x3::setScriptVariableValue(MiniScript::ScriptVariable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Matrix3x3 matrix3x3Value;
	if (value != 0ll) {
		matrix3x3Value = *static_cast<const Matrix3x3*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Matrix3x3*>((void*)variable.getValuePtr()) = matrix3x3Value;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Matrix3x3(matrix3x3Value)));
}

void MiniScriptMatrix3x3::copyScriptVariable(MiniScript::ScriptVariable& to, const MiniScript::ScriptVariable& from) const {
	//
	Matrix3x3 matrix3x3Value;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		matrix3x3Value = *static_cast<Matrix3x3*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_MATRIX3x3 = static_cast<MiniScript::ScriptVariableType>(getType());
	to.setType(TYPE_MATRIX3x3);
	*static_cast<Matrix3x3*>((void*)to.getValuePtr()) = matrix3x3Value;
}

bool MiniScriptMatrix3x3::mul(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_MATRIX3x3 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptMatrix3x3::div(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_MATRIX3x3 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptMatrix3x3::add(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_MATRIX3x3 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptMatrix3x3::sub(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_MATRIX3x3 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

const string& MiniScriptMatrix3x3::getClassName() const {
	return CLASS_NAME;
}

const string& MiniScriptMatrix3x3::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptMatrix3x3::getValueAsString(const MiniScript::ScriptVariable& variable) const {
	//
	Matrix3x3 matrix3x3Value;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		matrix3x3Value = *static_cast<Matrix3x3*>((void*)variable.getValuePtr());
	}
	return
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

