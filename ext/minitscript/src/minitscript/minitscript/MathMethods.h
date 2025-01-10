#pragma once

#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>

using std::span;

/**
 * MinitScript math methods
 * @author Andreas Drewke
 */
class minitscript::minitscript::MathMethods {
public:
	/**
	 * Constructor
	 * @param minitScript minitScript
	 */
	MathMethods(MinitScript* minitScript): minitScript(minitScript) {}

	/**
	 * Register data type
	 * @param dataType data type
	 */
	void registerDataType(MinitScript::DataType* dataType);

	/**
	 * Register constants
	 */
	void registerConstants();

	/**
	 * Register methods
	 */
	void registerMethods();

	/**
	 * Multiply
	 * @param arguments argument values
	 * @param returnValue return value
	 * @param subStatement sub statement
	 */
	void mul(const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement);

	/**
	 * Division
	 * @param arguments argument values
	 * @param returnValue return value
	 * @param subStatement sub statement
	 */
	void div(const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement);

	/**
	 * Addition
	 * @param arguments argument values
	 * @param returnValue return value
	 * @param subStatement sub statement
	 */
	void add(const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement);

	/**
	 * Subtraction
	 * @param arguments argument values
	 * @param returnValue return value
	 * @param subStatement sub statement
	 */
	void sub(const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement);

private:
	MinitScript* minitScript;
	vector<MinitScript::DataType*> dataTypes;

};
