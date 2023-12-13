#pragma once

#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MiniScript.h>

using std::span;

using miniscript::miniscript::MiniScript;

/**
 * MiniScript math methods
 * @author Andreas Drewke
 */
class miniscript::miniscript::MathMethods {
public:
	/**
	 * Constructor
	 * @param miniScript miniScript
	 */
	MathMethods(MiniScript* miniScript): miniScript(miniScript) {}

	/**
	 * Register data type
	 * @param dataType data type
	 */
	void registerDataType(MiniScript::DataType* dataType);

	/**
	 * Register methods
	 */
	void registerMethods();

	/**
	 * Multiply
	 * @param arguments argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	void mul(const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement);

	/**
	 * Division
	 * @param arguments argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	void div(const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement);

	/**
	 * Addition
	 * @param arguments argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	void add(const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement);

	/**
	 * Subtraction
	 * @param arguments argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	void sub(const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement);

private:
	MiniScript* miniScript;
	vector<MiniScript::DataType*> dataTypes;

};
