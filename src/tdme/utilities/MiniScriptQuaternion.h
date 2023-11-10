#pragma once

#include <span>

#include <tdme/tdme.h>
#include <tdme/math/Quaternion.h>
#include <tdme/utilities/MiniScript.h>

using std::span;

using tdme::math::Quaternion;
using tdme::utilities::MiniScript;

/**
 * MiniScript Quaternion data type
 * @author Andreas Drewke
 */
class tdme::utilities::MiniScriptQuaternion final: public MiniScript::ScriptDataType {
private:
	// overridden methods
	void registerMethods(MiniScript* miniScript) const override;
	void unsetScriptVariableValue(MiniScript::ScriptVariable& variable) const override;
	void setScriptVariableValue(MiniScript::ScriptVariable& variable, const void* value) const override;
	void copyScriptVariable(MiniScript::ScriptVariable& to, const MiniScript::ScriptVariable& from) const override;
	bool mul(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const override;
	bool div(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const override;
	bool add(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const override;
	bool sub(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const override;

public:
	static const string CLASS_NAME;
	static const string TYPE_NAME;

	/**
	 * Get quaternion value from given variable
	 * @param TYPE_QUATERNION custom data type for vector3
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static inline bool getQuaternionValue(MiniScript::ScriptVariableType TYPE_QUATERNION, const span<MiniScript::ScriptVariable>& arguments, int idx, Quaternion& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == TYPE_QUATERNION) {
			if (argument.getValuePtr() == 0ll) return optional;
			value = *static_cast<Quaternion*>((void*)argument.getValuePtr());
			return true;
		}
		return optional;

	}

	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptQuaternion)

	/**
	 * MiniScript Quaternion data type
	 */
	MiniScriptQuaternion(): MiniScript::ScriptDataType(true) {
		//
	}

	// overridden methods
	const string& getClassName() const override;
	const string& getTypeAsString() const override;
	const string getValueAsString(const MiniScript::ScriptVariable& variable) const override;

};
