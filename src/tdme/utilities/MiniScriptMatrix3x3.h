#pragma once

#include <span>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/utilities/fwd-tdme.h>

using std::span;

using miniscript::miniscript::MiniScript;

using tdme::math::Matrix3x3;

/**
 * MiniScript Matrix3x3 data type
 * @author Andreas Drewke
 */
class tdme::utilities::MiniScriptMatrix3x3 final: public MiniScript::ScriptDataType {
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
	 * Get matrix3x3 value from given variable
	 * @param TYPE_MATRIX3x3 custom data type for vector3
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static inline bool getMatrix3x3Value(MiniScript::ScriptVariableType TYPE_MATRIX3x3, const span<MiniScript::ScriptVariable>& arguments, int idx, Matrix3x3& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == TYPE_MATRIX3x3) {
			if (argument.getValuePtr() == 0ll) return optional;
			value = *static_cast<Matrix3x3*>((void*)argument.getValuePtr());
			return true;
		}
		return optional;

	}

	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptMatrix3x3)

	/**
	 * MiniScript Matrix3x3 data type
	 * @param miniScript mini script instance
	 */
	MiniScriptMatrix3x3(): MiniScript::ScriptDataType(true) {
		//
	}

	// overridden methods
	const string& getClassName() const override;
	const string& getTypeAsString() const override;
	const string getValueAsString(const MiniScript::ScriptVariable& variable) const override;

};
