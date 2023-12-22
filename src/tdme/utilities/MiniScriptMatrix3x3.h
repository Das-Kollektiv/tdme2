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
class tdme::utilities::MiniScriptMatrix3x3 final: public MiniScript::DataType {
private:
	// overridden methods
	void registerMethods(MiniScript* miniScript) const override;
	void unsetVariableValue(MiniScript::Variable& variable) const override;
	void setVariableValue(MiniScript::Variable& variable, const void* value) const override;
	void copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const override;
	bool mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;

	//
	STATIC_DLL_IMPEXT static MiniScript::VariableType TYPE_MATRIX3x3;
	STATIC_DLL_IMPEXT static MiniScript::VariableType TYPE_VECTOR2;

public:
	STATIC_DLL_IMPEXT static const string TYPE_NAME;

	/**
	 * Initialize
	 */
	static void initialize();

	/**
	 * Get matrix3x3 value from given variable
	 * @param TYPE_MATRIX3x3 custom data type for vector3
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static inline bool getMatrix3x3Value(MiniScript::VariableType TYPE_MATRIX3x3, const span<MiniScript::Variable>& arguments, int idx, Matrix3x3& value, bool optional = false) {
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
	MiniScriptMatrix3x3(): MiniScript::DataType(true) {
		//
	}

	// overridden methods
	const string& getTypeAsString() const override;
	const string getValueAsString(const MiniScript::Variable& variable) const override;

};
