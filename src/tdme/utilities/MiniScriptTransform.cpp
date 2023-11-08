#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptTransform.h>

using std::span;
using std::string;

using tdme::engine::Transform;
using tdme::utilities::Float;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptTransform;

const string MiniScriptTransform::CLASS_NAME = "transform";
const string MiniScriptTransform::TYPE_NAME = "Transform";

void MiniScriptTransform::registerMethods() const {
	const auto TYPE_TRANSFORM = static_cast<MiniScript::ScriptVariableType>(getType());
}

void MiniScriptTransform::unsetScriptVariableValue(MiniScript::ScriptVariable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Transform*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptTransform::setScriptVariableValue(MiniScript::ScriptVariable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Transform transformValue;
	if (value != 0ll) {
		transformValue = *static_cast<const Transform*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Transform*>((void*)variable.getValuePtr()) = transformValue;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Transform(transformValue)));
}

void MiniScriptTransform::copyScriptVariable(MiniScript::ScriptVariable& to, const MiniScript::ScriptVariable& from) const {
	//
	Transform transformValue;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		transformValue = *static_cast<Transform*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_TRANSFORM = static_cast<MiniScript::ScriptVariableType>(getType());
	to.setType(TYPE_TRANSFORM);
	*static_cast<Transform*>((void*)to.getValuePtr()) = transformValue;
}

bool MiniScriptTransform::mul(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_TRANSFORM = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptTransform::div(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_TRANSFORM = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptTransform::add(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_TRANSFORM = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

bool MiniScriptTransform::sub(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_TRANSFORM = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	return false;
}

const string& MiniScriptTransform::getClassName() const {
	return CLASS_NAME;
}

const string& MiniScriptTransform::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptTransform::getValueAsString(const MiniScript::ScriptVariable& variable) const {
	//
	Transform transformValue;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		transformValue = *static_cast<Transform*>((void*)variable.getValuePtr());
	}
	//
	string result;
	result+=
		"Transform(translation: Vector3(" +
		to_string(transformValue.getTranslation().getX()) + ", " +
		to_string(transformValue.getTranslation().getY()) + ", " +
		to_string(transformValue.getTranslation().getZ()) + "), " +
		"scale: (" +
		to_string(transformValue.getScale().getX()) + ", " +
		to_string(transformValue.getScale().getY()) + ", " +
		to_string(transformValue.getScale().getZ()) + ")";
	for (auto i = 0; i < transformValue.getRotationCount(); i++) {
		result+= ", rotations: (axis: Vector3(" +
				to_string(transformValue.getRotationAxis(i).getX()) + ", " +
				to_string(transformValue.getRotationAxis(i).getY()) + ", " +
				to_string(transformValue.getRotationAxis(i).getZ()) + "), angle: " +
				to_string(transformValue.getRotationAngle(i)) + ")";
	}
	result+= ")";
	//
	return result;
}

