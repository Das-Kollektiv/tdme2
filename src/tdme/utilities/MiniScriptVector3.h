#pragma once

#include <span>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>

using std::span;

using miniscript::miniscript::MiniScript;

using tdme::math::Vector3;

/**
 * MiniScript Vector3 data type
 * @author Andreas Drewke
 */
class tdme::utilities::MiniScriptVector3 final: public MiniScript::DataType {
private:
	// overridden methods
	void registerMethods(MiniScript* miniScript) const override;
	void unsetVariableValue(MiniScript::Variable& variable) const override;
	void setVariableValue(MiniScript::Variable& variable, const void* value) const override;
	void copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const override;
	bool mul(MiniScript* miniScript, const span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool div(MiniScript* miniScript, const span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool add(MiniScript* miniScript, const span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool sub(MiniScript* miniScript, const span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;

public:
	STATIC_DLL_IMPEXT static const string TYPE_NAME;

	/**
	 * Get vector3 value from given variable
	 * @param TYPE_VECTOR3 custom data type for vector3
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static inline bool getVector3Value(MiniScript::VariableType TYPE_VECTOR3, const span<MiniScript::Variable>& arguments, int idx, Vector3& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == TYPE_VECTOR3) {
			if (argument.getValuePtr() == 0ll) return optional;
			value = *static_cast<Vector3*>((void*)argument.getValuePtr());
			return true;
		}
		return optional;

	}

	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptVector3)

	/**
	 * MiniScript Vector3 data type
	 */
	MiniScriptVector3(): MiniScript::DataType(true) {
		//
	}

	// overridden methods
	const string& getTypeAsString() const override;
	const string getValueAsString(const MiniScript::Variable& variable) const override;

};
