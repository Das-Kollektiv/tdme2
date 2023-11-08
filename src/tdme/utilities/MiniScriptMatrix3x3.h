#pragma once

#include <span>

#include <tdme/tdme.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/utilities/MiniScript.h>

using std::span;

using tdme::math::Matrix3x3;
using tdme::utilities::MiniScript;

/**
 * MiniScript Matrix3x3 data type
 * @author Andreas Drewke
 */
class tdme::utilities::MiniScriptMatrix3x3 final: public MiniScript::ScriptDataType {
private:
	MiniScript* miniScript { nullptr };

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

	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptMatrix3x3)

	/**
	 * MiniScript Matrix3x3 data type
	 * @param miniScript mini script instance
	 */
	MiniScriptMatrix3x3(MiniScript* miniScript): MiniScript::ScriptDataType(miniScript, true) {
		//
	}

	// overridden methods
	const string& getClassName() const override;
	const string& getTypeAsString() const override;
	const string getValueAsString(const MiniScript::ScriptVariable& variable) const override;

};
