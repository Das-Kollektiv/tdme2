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
	 * Register methods
	 * @param miniScript mini script instance
	 */
	static void registerMethods(MiniScript* miniScript);

	/**
	 * Multiply
	 * @param miniScript mini script instance
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	static void mul(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement);

	/**
	 * Division
	 * @param miniScript mini script instance
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	static void div(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement);

	/**
	 * Addition
	 * @param miniScript mini script instance
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	static void add(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement);

	/**
	 * Subtraction
	 * @param miniScript mini script instance
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	static void sub(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement);
};
