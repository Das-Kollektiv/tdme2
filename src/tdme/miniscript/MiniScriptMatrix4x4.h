#pragma once

#include <span>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/miniscript/fwd-tdme.h>

using std::span;

using miniscript::miniscript::MiniScript;

using tdme::math::Matrix4x4;

/**
 * MiniScript Matrix4x4 data type
 * @author Andreas Drewke
 */
class tdme::miniscript::MiniScriptMatrix4x4 final: public MiniScript::DataType {
private:
	// overridden methods
	void registerConstants(MiniScript* miniScript) const override;
	void registerMethods(MiniScript* miniScript) const override;
	void unsetVariableValue(MiniScript::Variable& variable) const override;
	void setVariableValue(MiniScript::Variable& variable) const override;
	void setVariableValue(MiniScript::Variable& variable, const void* value) const override;
	void copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const override;
	bool mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	bool sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const override;
	void* createScriptContext() const override;
	void deleteScriptContext(void* context) const override;
	void garbageCollection(void* context) const override;

	//
	STATIC_DLL_IMPEXT static MiniScript::VariableType TYPE_MATRIX4x4;
	STATIC_DLL_IMPEXT static MiniScript::VariableType TYPE_VECTOR3;
	STATIC_DLL_IMPEXT static MiniScript::VariableType TYPE_VECTOR4;

public:
	STATIC_DLL_IMPEXT static const string TYPE_NAME;

	/**
	 * Initialize
	 */
	static void initialize();

	/**
	 * Get matrix4x4 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static inline bool getMatrix4x4Value(const span<MiniScript::Variable>& arguments, int idx, Matrix4x4& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == TYPE_MATRIX4x4) {
			value = *static_cast<Matrix4x4*>(argument.getValuePtr());
			return true;
		}
		return optional;
	}

	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptMatrix4x4)

	/**
	 * MiniScript Matrix4x4 data type
	 */
	MiniScriptMatrix4x4(): MiniScript::DataType(true) {
		//
	}

	// overridden methods
	const string& getTypeAsString() const override;
	const string getValueAsString(const MiniScript::Variable& variable) const override;

};
