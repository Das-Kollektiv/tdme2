#pragma once

#include <span>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/miniscript/fwd-tdme.h>

using std::span;

using miniscript::miniscript::MiniScript;

using tdme::engine::Transform;

/**
 * MiniScript Transform data type
 * @author Andreas Drewke
 */
class tdme::miniscript::MiniScriptTransform final: public MiniScript::DataType {
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
	ScriptContext* createScriptContext() const override;
	void deleteScriptContext(ScriptContext* context) const override;
	void garbageCollection(ScriptContext* context) const override;

	//
	STATIC_DLL_IMPEXT static MiniScript::VariableType TYPE_MATRIX4x4;
	STATIC_DLL_IMPEXT static MiniScript::VariableType TYPE_QUATERNION;
	STATIC_DLL_IMPEXT static MiniScript::VariableType TYPE_TRANSFORM;
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
	static inline bool getTransformValue(const span<MiniScript::Variable>& arguments, int idx, Transform& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == TYPE_TRANSFORM) {
			value = *static_cast<Transform*>(argument.getValuePtr());
			return true;
		}
		return optional;
	}

	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptTransform)

	/**
	 * MiniScript Transform data type
	 */
	MiniScriptTransform(): MiniScript::DataType(true, false) {
		//
	}

	// overridden methods
	const string& getTypeAsString() const override;
	const string getValueAsString(const MiniScript::Variable& variable) const override;

};
