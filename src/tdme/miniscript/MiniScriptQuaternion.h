#pragma once

#include <span>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Quaternion.h>
#include <tdme/miniscript/fwd-tdme.h>

using std::span;

using miniscript::miniscript::MiniScript;

using tdme::miniscript::MiniScriptQuaternion;

using tdme::math::Quaternion;

/**
 * MiniScript Quaternion data type
 * @author Andreas Drewke
 */
class tdme::miniscript::MiniScriptQuaternion final: public MiniScript::DataType {
private:
	// overridden methods
	void registerMethods(MiniScript* miniScript) const override;
	void unsetVariableValue(MiniScript::Variable& variable) const override;
	void setVariableValue(MiniScript::Variable& variable) const override;
	void setVariableValue(MiniScript::Variable& variable, const void* value) const override;
	void copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const override;
	bool mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;

	//
	STATIC_DLL_IMPEXT static MiniScript::VariableType TYPE_MATRIX4x4;
	STATIC_DLL_IMPEXT static MiniScript::VariableType TYPE_QUATERNION;
	STATIC_DLL_IMPEXT static MiniScript::VariableType TYPE_VECTOR3;

public:
	STATIC_DLL_IMPEXT static const string TYPE_NAME;

	/**
	 * Initialize
	 */
	static void initialize();

	/**
	 * Get quaternion value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static inline bool getQuaternionValue(const span<MiniScript::Variable>& arguments, int idx, Quaternion& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == TYPE_QUATERNION) {
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
	MiniScriptQuaternion(): MiniScript::DataType(true) {
		//
	}

	// overridden methods
	const string& getTypeAsString() const override;
	const string getValueAsString(const MiniScript::Variable& variable) const override;

};
