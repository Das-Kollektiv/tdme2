#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/math/Vector2.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptVector2.h>

using std::span;
using std::string;

using tdme::math::Vector2;
using tdme::utilities::Float;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptVector2;

const string MiniScriptVector2::CLASS_NAME = "vec2";
const string MiniScriptVector2::TYPE_NAME = "Vector2";

void MiniScriptVector2::registerMethods() const {
}

void MiniScriptVector2::unsetScriptVariableValue(MiniScript::MiniScript::ScriptVariable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Vector2*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptVector2::setScriptVariableValue(MiniScript::MiniScript::ScriptVariable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Vector2 vector2Value;
	if (value != 0ll) {
		vector2Value = *static_cast<const Vector2*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Vector2*>((void*)variable.getValuePtr()) = vector2Value;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Vector2(vector2Value)));
}

void MiniScriptVector2::copyScriptVariable(MiniScript::MiniScript::ScriptVariable& to, const MiniScript::MiniScript::ScriptVariable& from) const {
	//
	Vector2 vector2Value;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		vector2Value = *static_cast<Vector2*>((void*)from.getValuePtr());
	}
	//
	to.setType(static_cast<MiniScript::ScriptVariableType>(getType()));
	*static_cast<Vector2*>((void*)to.getValuePtr()) = vector2Value;
}

bool MiniScriptVector2::mul(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR2 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptVector2::div(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR2 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptVector2::add(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR2 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptVector2::sub(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR2 = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

const string& MiniScriptVector2::getClassName() const {
	return CLASS_NAME;
}

const string& MiniScriptVector2::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptVector2::getValueAsString(const MiniScript::MiniScript::ScriptVariable& variable) const {
	//
	Vector2 vector2Value;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		vector2Value = *static_cast<Vector2*>((void*)variable.getValuePtr());
	}
	//
	return
		"Vector2(" +
		to_string(vector2Value.getX()) + ", " +
		to_string(vector2Value.getY()) + ")";

}

