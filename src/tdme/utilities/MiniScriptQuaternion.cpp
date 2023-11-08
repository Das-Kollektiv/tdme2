#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/math/Quaternion.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptQuaternion.h>

using std::span;
using std::string;

using tdme::math::Quaternion;
using tdme::utilities::Float;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptQuaternion;

const string MiniScriptQuaternion::CLASS_NAME = "quaternion";
const string MiniScriptQuaternion::TYPE_NAME = "Quaternion";

void MiniScriptQuaternion::registerMethods() const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(getType());
}

void MiniScriptQuaternion::unsetScriptVariableValue(MiniScript::ScriptVariable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Quaternion*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptQuaternion::setScriptVariableValue(MiniScript::ScriptVariable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Quaternion quaternionValue;
	if (value != 0ll) {
		quaternionValue = *static_cast<const Quaternion*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Quaternion*>((void*)variable.getValuePtr()) = quaternionValue;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Quaternion(quaternionValue)));
}

void MiniScriptQuaternion::copyScriptVariable(MiniScript::ScriptVariable& to, const MiniScript::ScriptVariable& from) const {
	//
	Quaternion quaternionValue;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		quaternionValue = *static_cast<Quaternion*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(getType());
	to.setType(TYPE_QUATERNION);
	*static_cast<Quaternion*>((void*)to.getValuePtr()) = quaternionValue;
}

bool MiniScriptQuaternion::mul(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptQuaternion::div(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptQuaternion::add(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptQuaternion::sub(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

const string& MiniScriptQuaternion::getClassName() const {
	return CLASS_NAME;
}

const string& MiniScriptQuaternion::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptQuaternion::getValueAsString(const MiniScript::ScriptVariable& variable) const {
	//
	Quaternion quaternionValue;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		quaternionValue = *static_cast<Quaternion*>((void*)variable.getValuePtr());
	}
	return
		"Quaternion(" +
		to_string(quaternionValue[0]) + ", " +
		to_string(quaternionValue[1]) + ", " +
		to_string(quaternionValue[2]) + ", " +
		to_string(quaternionValue[3]) + ")";

}

