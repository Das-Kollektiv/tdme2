#pragma once

#include <span>

#include <tdme/tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/MiniScript.h>

using std::span;

using tdme::math::Math;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMath;

/**
 * MiniScript Math
 * @author Andreas Drewke
 */
class tdme::utilities::MiniScriptMath {
public:
	/**
	 * Constructor
	 * @param miniScript miniScript
	 */
	MiniScriptMath(MiniScript* miniScript): miniScript(miniScript) {}

	/**
	 * Register script data type
	 * @param scriptDataType script data type
	 */
	void registerDataType(MiniScript::ScriptDataType* scriptDataType);

	/**
	 * Register methods
	 * @param miniScript mini script instance
	 */
	void registerMethods();

	/**
	 * Multiply
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	void mul(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement);

	/**
	 * Division
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	void div(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement);

	/**
	 * Addition
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	void add(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement);

	/**
	 * Subtraction
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	void sub(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement);

private:
	MiniScript* miniScript;
	vector<MiniScript::ScriptDataType*> scriptDataTypes;

};
