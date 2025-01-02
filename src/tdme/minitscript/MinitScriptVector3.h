#pragma once

#include <span>

#include <minitscript/minitscript/MinitScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/minitscript/fwd-tdme.h>

using std::span;

using minitscript::minitscript::MinitScript;

using tdme::math::Vector3;

/**
 * MinitScript Vector3 data type
 * @author Andreas Drewke
 */
class tdme::minitscript::MinitScriptVector3 final: public MinitScript::DataType {
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
	STATIC_DLL_IMPEXT static MinitScript::VariableType TYPE_VECTOR3;

public:
	STATIC_DLL_IMPEXT static const string TYPE_NAME;

	/**
	 * Initialize
	 */
	static void initialize();

	/**
	 * Get vector3 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static inline bool getVector3Value(const span<MinitScript::Variable>& arguments, int idx, Vector3& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		if (argument.getType() == TYPE_VECTOR3) {
			value = *static_cast<Vector3*>(argument.getValuePtr());
			return true;
		}
		return optional;

	}

	// forbid class copy
	FORBID_CLASS_COPY(MinitScriptVector3)

	/**
	 * MinitScript Vector3 data type
	 */
	MinitScriptVector3(): MinitScript::DataType(true, false) {
		//
	}

	// overridden methods
	const string& getTypeAsString() const override;
	const string getValueAsString(const MinitScript::Variable& variable) const override;

};
