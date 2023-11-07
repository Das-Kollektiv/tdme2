#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptVector4.h>

using std::span;
using std::string;

using tdme::math::Vector4;
using tdme::utilities::Float;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptVector4;

const string MiniScriptVector4::CLASS_NAME = "vec4";
const string MiniScriptVector4::TYPE_NAME = "Vector4";

void MiniScriptVector4::registerMethods() const {
}

void MiniScriptVector4::unsetScriptVariableValue(MiniScript::MiniScript::ScriptVariable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Vector4*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptVector4::setScriptVariableValue(MiniScript::MiniScript::ScriptVariable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Vector4 vector4Value;
	if (value != 0ll) {
		vector4Value = *static_cast<const Vector4*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Vector4*>((void*)variable.getValuePtr()) = vector4Value;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Vector4(vector4Value)));
}

void MiniScriptVector4::copyScriptVariable(MiniScript::MiniScript::ScriptVariable& to, const MiniScript::MiniScript::ScriptVariable& from) const {
	//
	Vector4 vector4Value;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		vector4Value = *static_cast<Vector4*>((void*)from.getValuePtr());
	}
	//
	to.setType(static_cast<MiniScript::ScriptVariableType>(getType()));
	*static_cast<Vector4*>((void*)to.getValuePtr()) = vector4Value;
}

bool MiniScriptVector4::mul(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR4 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptVector4::div(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR4 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptVector4::add(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR4 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptVector4::sub(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR4 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

const string& MiniScriptVector4::getClassName() const {
	return CLASS_NAME;
}

const string& MiniScriptVector4::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptVector4::getValueAsString(const MiniScript::MiniScript::ScriptVariable& variable) const {
	//
	Vector4 vector4Value;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		vector4Value = *static_cast<Vector4*>((void*)variable.getValuePtr());
	}
	//
	return
		"Vector4(" +
		to_string(vector4Value.getX()) + ", " +
		to_string(vector4Value.getY()) + ", " +
		to_string(vector4Value.getZ()) + ", " +
		to_string(vector4Value.getW()) + ")";

}

