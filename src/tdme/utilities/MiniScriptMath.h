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
	inline static void mul(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) {
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR2) == true) {
			Vector2 result;
			if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR2) {
				Vector2 vec2Value;
				if (MiniScript::getVector2Value(argumentValues, 0, vec2Value, false) == true) {
					result = vec2Value;
				} else {
					Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(0) + ": vector2 expected");
					miniScript->startErrorScript();
					return;
				}
			} else {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = Vector2(floatValue, floatValue);
				} else {
					Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR2) {
					Vector2 vec2Value;
					if (MiniScript::getVector2Value(argumentValues, i, vec2Value, false) == true) {
						result*= vec2Value;
					} else {
						Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(i) + ": vector2 expected");
						miniScript->startErrorScript();
						return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result*= Vector2(floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
						return;
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
			Vector3 result;
			if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
				Vector3 vec3Value;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
					result = vec3Value;
				} else {
					Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
					miniScript->startErrorScript();
					return;
				}
			} else {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = Vector3(floatValue, floatValue, floatValue);
				} else {
					Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
						result*= vec3Value;
					} else {
						Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
						miniScript->startErrorScript();
						return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result*= Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
						return;
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR4) == true) {
			Vector4 result;
			if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR4) {
				Vector4 vec4Value;
				if (MiniScript::getVector4Value(argumentValues, 0, vec4Value, false) == true) {
					result = vec4Value;
				} else {
					Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(0) + ": vector4 expected");
					miniScript->startErrorScript();
					return;
				}
			} else {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = Vector4(floatValue, floatValue, floatValue, floatValue);
				} else {
					Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR4) {
					Vector4 vec4Value;
					if (MiniScript::getVector4Value(argumentValues, i, vec4Value, false) == true) {
						result*= vec4Value;
					} else {
						Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(i) + ": vector4 expected");
						miniScript->startErrorScript();
						return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result*= Vector4(floatValue, floatValue, floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
						return;
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
			float result = 0.0f;
			{
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = floatValue;
				} else {
					Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
					result*= floatValue;
				} else {
					Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			returnValue.setValue(result);
		} else {
			int64_t result = 0LL;
			{
				int64_t intValue;
				if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
					result = intValue;
				} else {
					Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				int64_t intValue;
				if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
					result*= intValue;
				} else {
					Console::println("MiniScriptMath::mul(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
					miniScript->startErrorScript();
					return;
				}
			}
			returnValue.setValue(result);
		}
	}

	/**
	 * Division
	 * @param miniScript mini script instance
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	inline static void div(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) {
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR2) == true) {
			Vector2 result;
			if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR2) {
				Vector2 vec2Value;
				if (MiniScript::getVector2Value(argumentValues, 0, vec2Value, false) == true) {
					result = vec2Value;
				} else {
					Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(0) + ": vector2 expected");
					miniScript->startErrorScript();
					return;
				}
			} else {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = Vector2(floatValue, floatValue);
				} else {
					Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR2) {
					Vector2 vec2Value;
					if (MiniScript::getVector2Value(argumentValues, i, vec2Value, false) == true) {
						result/= vec2Value;
					} else {
						Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(i) + ": vector2 expected");
						miniScript->startErrorScript();
						return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result/= Vector2(floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
						return;
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
			Vector3 result;
			if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
				Vector3 vec3Value;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
					result = vec3Value;
				} else {
					Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
					miniScript->startErrorScript();
					return;
				}
			} else {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = Vector3(floatValue, floatValue, floatValue);
				} else {
					Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
						result/= vec3Value;
					} else {
						Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
						miniScript->startErrorScript();
						return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result/= Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
						return;
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR4) == true) {
			Vector4 result;
			if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR4) {
				Vector4 vec4Value;
				if (MiniScript::getVector4Value(argumentValues, 0, vec4Value, false) == true) {
					result = vec4Value;
				} else {
					Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(0) + ": vector4 expected");
					miniScript->startErrorScript();
					return;
				}
			} else {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = Vector4(floatValue, floatValue, floatValue, floatValue);
				} else {
					Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR4) {
					Vector4 vec4Value;
					if (MiniScript::getVector4Value(argumentValues, i, vec4Value, false) == true) {
						result/= vec4Value;
					} else {
						Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(i) + ": vector4 expected");
						miniScript->startErrorScript();
						return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result/= Vector4(floatValue, floatValue, floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
						return;
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
			float result = 0.0f;
			{
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = floatValue;
				} else {
					Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
					result/= floatValue;
				} else {
					Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			returnValue.setValue(result);
		} else {
			int64_t result = 0LL;
			{
				int64_t intValue;
				if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
					result = intValue;
				} else {
					Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				int64_t intValue;
				if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
					result/= intValue;
				} else {
					Console::println("MiniScriptMath::div(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
					miniScript->startErrorScript();
					return;
				}
			}
			returnValue.setValue(result);
		}
	}

	/**
	/**
	 * Addition
	 * @param miniScript mini script instance
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	inline static void add(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) {
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
			string result;
			for (auto i = 0; i < argumentValues.size(); i++) {
				string stringValue;
				if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
					result+= argumentValues[i].getValueString();
				} else
				if (argumentValues[i].getType() == MiniScript::TYPE_MAP) {
					result+= argumentValues[i].getValueString();
				} else
				if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
					result+= stringValue;
				} else {
					Console::println("MiniScriptMath::add(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
					miniScript->startErrorScript();
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR2) == true) {
			Vector2 result;
			for (auto i = 0; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR2) {
					Vector2 vec2Value;
					if (MiniScript::getVector2Value(argumentValues, i, vec2Value, false) == true) {
						result+= vec2Value;
					} else {
						Console::println("MiniScriptMath::add(): parameter type mismatch @ argument " + to_string(i) + ": vector2 expected");
						miniScript->startErrorScript();
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result+= Vector2(floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::add(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
			Vector3 result;
			for (auto i = 0; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
						result+= vec3Value;
					} else {
						Console::println("MiniScriptMath::add(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
						miniScript->startErrorScript();
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result+= Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::add(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR4) == true) {
			Vector4 result;
			for (auto i = 0; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR4) {
					Vector4 vec4Value;
					if (MiniScript::getVector4Value(argumentValues, i, vec4Value, false) == true) {
						result+= vec4Value;
					} else {
						Console::println("MiniScriptMath::add(): parameter type mismatch @ argument " + to_string(i) + ": vector4 expected");
						miniScript->startErrorScript();
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result+= Vector4(floatValue, floatValue, floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::add(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
			float result = 0.0f;
			for (auto i = 0; i < argumentValues.size(); i++) {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
					result+= floatValue;
				} else {
					Console::println("MiniScriptMath::add(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
					miniScript->startErrorScript();
				}
			}
			returnValue.setValue(result);
		} else {
			int64_t result = 0.0f;
			for (auto i = 0; i < argumentValues.size(); i++) {
				int64_t intValue;
				if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
					result+= intValue;
				} else {
					Console::println("MiniScriptMath::add(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
					miniScript->startErrorScript();
				}
			}
			returnValue.setValue(result);
		}
	}

	/**
	 * Subtraction
	 * @param miniScript mini script instance
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @param statement statement
	 */
	inline static void sub(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) {
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR2) == true) {
			Vector2 result;
			if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR2) {
				Vector2 vec2Value;
				if (MiniScript::getVector2Value(argumentValues, 0, vec2Value, false) == true) {
					result = vec2Value;
				} else {
					Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(0) + ": vector2 expected");
					miniScript->startErrorScript();
				}
			} else {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = Vector2(floatValue, floatValue);
				} else {
					Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR2) {
					Vector2 vec2Value;
					if (MiniScript::getVector2Value(argumentValues, i, vec2Value, false) == true) {
						result-= vec2Value;
					} else {
						Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(i) + ": vector2 expected");
						miniScript->startErrorScript();
						return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result-= Vector2(floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
						return;
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
			Vector3 result;
			if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
				Vector3 vec3Value;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
					result = vec3Value;
				} else {
					Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
					miniScript->startErrorScript();
				}
			} else {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = Vector3(floatValue, floatValue, floatValue);
				} else {
					Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
						result-= vec3Value;
					} else {
						Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
						miniScript->startErrorScript();
						return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result-= Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
						return;
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR4) == true) {
			Vector4 result;
			if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR4) {
				Vector4 vec4Value;
				if (MiniScript::getVector4Value(argumentValues, 0, vec4Value, false) == true) {
					result = vec4Value;
				} else {
					Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(0) + ": vector4 expected");
					miniScript->startErrorScript();
				}
			} else {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = Vector4(floatValue, floatValue, floatValue, floatValue);
				} else {
					Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR4) {
					Vector4 vec4Value;
					if (MiniScript::getVector4Value(argumentValues, i, vec4Value, false) == true) {
						result-= vec4Value;
					} else {
						Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(i) + ": vector4 expected");
						miniScript->startErrorScript();
						return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result-= Vector4(floatValue, floatValue, floatValue, floatValue);
					} else {
						Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript();
						return;
					}
				}
			}
			returnValue.setValue(result);
		} else
		if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
			float result = 0.0f;
			{
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					result = floatValue;
				} else {
					Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
					result-= floatValue;
				} else {
					Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			returnValue.setValue(result);
		} else {
			int64_t result = 0LL;
			{
				int64_t intValue;
				if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
					result = intValue;
				} else {
					Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
					miniScript->startErrorScript();
					return;
				}
			}
			for (auto i = 1; i < argumentValues.size(); i++) {
				int64_t intValue;
				if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
					result-= intValue;
				} else {
					Console::println("MiniScriptMath::sub(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
					miniScript->startErrorScript();
					return;
				}
			}
			returnValue.setValue(result);
		}
	}

};
