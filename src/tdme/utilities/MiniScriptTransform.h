#pragma once

#include <span>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/utilities/MiniScript.h>

using std::span;

using tdme::engine::Transform;
using tdme::utilities::MiniScript;

/**
 * MiniScript Transform data type
 * @author Andreas Drewke
 */
class tdme::utilities::MiniScriptTransform final: public MiniScript::ScriptDataType {
private:
	// overridden methods
	void registerMethods() const override;
	void unsetScriptVariableValue(MiniScript::ScriptVariable& variable) const override;
	void setScriptVariableValue(MiniScript::ScriptVariable& variable, const void* value) const override;
	void copyScriptVariable(MiniScript::ScriptVariable& to, const MiniScript::ScriptVariable& from) const override;
	bool mul(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const override;
	bool div(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const override;
	bool add(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const override;
	bool sub(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const override;

public:
	static const string CLASS_NAME;
	static const string TYPE_NAME;

	/**
	 * Get quaternion value from given variable
	 * @param TYPE_TRANSFORM custom data type for vector3
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static inline bool getTransformValue(MiniScript::ScriptVariableType TYPE_TRANSFORM, const span<MiniScript::ScriptVariable>& arguments, int idx, Transform& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == TYPE_TRANSFORM) {
			if (argument.getValuePtr() == 0ll) return optional;
			value = *static_cast<Transform*>((void*)argument.getValuePtr());
			return true;
		}
		return optional;

	}

	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptTransform)

	/**
	 * MiniScript Transform data type
	 * @param miniScript mini script instance
	 */
	MiniScriptTransform(MiniScript* miniScript): MiniScript::ScriptDataType(miniScript, true) {
		//
	}

	// overridden methods
	const string& getClassName() const override;
	const string& getTypeAsString() const override;
	const string getValueAsString(const MiniScript::ScriptVariable& variable) const override;

};
