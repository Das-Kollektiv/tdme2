#pragma once

#include <span>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/fwd-tdme.h>

using std::span;

using miniscript::miniscript::MiniScript;

using tdme::math::Vector4;

/**
 * MiniScript Vector4 data type
 * @author Andreas Drewke
 */
class tdme::utilities::MiniScriptVector4 final: public MiniScript::ScriptDataType {
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
	 * Get vector4 value from given variable
	 * @param TYPE_VECTOR4 custom data type for vector3
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static inline bool getVector4Value(MiniScript::ScriptVariableType TYPE_VECTOR4, const span<MiniScript::ScriptVariable>& arguments, int idx, Vector4& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == TYPE_VECTOR4) {
			if (argument.getValuePtr() == 0ll) return optional;
			value = *static_cast<Vector4*>((void*)argument.getValuePtr());
			return true;
		}
		return optional;

	}

	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptVector4)

	/**
	 * MiniScript Vector4 data type
	 */
	MiniScriptVector4(): MiniScript::ScriptDataType(true) {
		//
	}

	// overridden methods
	const string& getClassName() const override;
	const string& getTypeAsString() const override;
	const string getValueAsString(const MiniScript::ScriptVariable& variable) const override;

};
