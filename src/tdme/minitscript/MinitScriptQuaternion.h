#pragma once

#include <span>

#include <minitscript/minitscript/MinitScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Quaternion.h>
#include <tdme/minitscript/fwd-tdme.h>

using std::span;

using minitscript::minitscript::MinitScript;

using tdme::minitscript::MinitScriptQuaternion;

using tdme::math::Quaternion;

/**
 * MinitScript Quaternion data type
 * @author Andreas Drewke
 */
class tdme::minitscript::MinitScriptQuaternion final: public MinitScript::DataType {
private:
	// overridden methods
	void registerConstants(MinitScript* minitScript) const override;
	void registerMethods(MinitScript* minitScript) const override;
	void unsetVariableValue(MinitScript::Variable& variable) const override;
	void setVariableValue(MinitScript::Variable& variable) const override;
	void setVariableValue(MinitScript::Variable& variable, const void* value) const override;
	void copyVariable(MinitScript::Variable& to, const MinitScript::Variable& from) const override;
	bool mul(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const override;
	bool div(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const override;
	bool add(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const override;
	bool sub(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const override;
	ScriptContext* createScriptContext() const override;
	void deleteScriptContext(ScriptContext* context) const override;
	void garbageCollection(ScriptContext* context) const override;

	//
	STATIC_DLL_IMPEXT static MinitScript::VariableType TYPE_MATRIX4x4;
	STATIC_DLL_IMPEXT static MinitScript::VariableType TYPE_QUATERNION;
	STATIC_DLL_IMPEXT static MinitScript::VariableType TYPE_VECTOR3;

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
	static inline bool getQuaternionValue(const span<MinitScript::Variable>& arguments, int idx, Quaternion& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == TYPE_QUATERNION) {
			value = *static_cast<Quaternion*>(argument.getValuePtr());
			return true;
		}
		return optional;

	}

	// forbid class copy
	FORBID_CLASS_COPY(MinitScriptQuaternion)

	/**
	 * MinitScript Quaternion data type
	 */
	MinitScriptQuaternion(): MinitScript::DataType(true, false) {
		//
	}

	// overridden methods
	const string& getTypeAsString() const override;
	const string getValueAsString(const MinitScript::Variable& variable) const override;

};
