#include <span>

#include <tdme/tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMath.h>

using std::span;

using tdme::math::Math;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMath;

void MiniScriptMath::registerMethods(MiniScript* miniScript) {
	// operator methods
	{
		//
		class ScriptMethodAdd: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAdd(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .assignBack = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .assignBack = false }
					},
					MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "add";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_ADDITION;
			}
		};
		miniScript->registerMethod(new ScriptMethodAdd(miniScript));
	}
	{
		//
		class ScriptMethodSub: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSub(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .assignBack = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .assignBack = false }
					},
					MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "sub";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_SUBTRACTION;
			}
		};
		miniScript->registerMethod(new ScriptMethodSub(miniScript));
	}
	{
		//
		class ScriptMethodMul: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMul(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .assignBack = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .assignBack = false }
					},
					MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mul";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_MULTIPLICATION;
			}
		};
		miniScript->registerMethod(new ScriptMethodMul(miniScript));
	}
	{
		//
		class ScriptMethodDiv: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodDiv(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .assignBack = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .assignBack = false }
					},
					MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "div";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_DIVISION;
			}
		};
		miniScript->registerMethod(new ScriptMethodDiv(miniScript));
	}
	{
		//
		class ScriptMethodMod: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMod(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .assignBack = false },
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "range", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER
			), miniScript(miniScript) {}
			const string getMethodName() override {
				return "mod";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_INTEGER) == true) {
					int64_t value;
					int64_t range;
					if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == true &&
						MiniScript::getIntegerValue(argumentValues, 1, range, false) == true) {
						returnValue.setValue(Math::mod(value, range));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: number expected, @ argument 1: number expected");
						miniScript->startErrorScript();
					}
				} else {
					float value;
					float range;
					if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
						returnValue.setValue(Math::mod(value, range));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: number expected, @ argument 1: number expected");
						miniScript->startErrorScript();
					}
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_MODULO;
			}
		};
		miniScript->registerMethod(new ScriptMethodMod(miniScript));
	}
	// constants
	{
		//
		class ScriptMethodPi: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodPi(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.PI";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setValue(Math::PI);
			}
		};
		miniScript->registerMethod(new ScriptMethodPi(miniScript));
	}
	{
		//
		class ScriptMethodEpsilon: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEpsilon(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.EPSILON";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setValue(Math::EPSILON);
			}
		};
		miniScript->registerMethod(new ScriptMethodEpsilon(miniScript));
	}
	{
		//
		class ScriptMethodEpsilon: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEpsilon(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.DEG2RAD";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setValue(Math::DEG2RAD);
			}
		};
		miniScript->registerMethod(new ScriptMethodEpsilon(miniScript));
	}
	{
		//
		class ScriptMethodEpsilon: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEpsilon(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.G";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setValue(Math::G);
			}
		};
		miniScript->registerMethod(new ScriptMethodEpsilon(miniScript));
	}
	{
		//
		class ScriptMethodAcos: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAcos(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.acos";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::acos(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodAcos(miniScript));
	}
	{
		//
		class ScriptMethodAsin: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAsin(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.asin";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::asin(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodAsin(miniScript));
	}
	{
		//
		class ScriptMethodAtan: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAtan(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.atan";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::atan(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodAtan(miniScript));
	}
	{
		//
		class ScriptMethodAtan2: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAtan2(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "y", .optional = false, .assignBack = false },
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "x", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.atan2";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float y;
				float x;
				if (MiniScript::getFloatValue(argumentValues, 0, y, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, x, false) == true) {
					returnValue.setValue(Math::atan2(y, x));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodAtan2(miniScript));
	}
	{
		//
		class ScriptMethodTan: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTan(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.tan";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::tan(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodTan(miniScript));
	}
	{
		//
		class ScriptMethodCos: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodCos(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.cos";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::cos(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodCos(miniScript));
	}
	{
		//
		class ScriptMethodSin: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSin(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.sin";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::sin(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodSin(miniScript));
	}
	{
		//
		class ScriptMethodFloor: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodFloor(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.floor";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::floor(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodFloor(miniScript));
	}
	{
		//
		class ScriptMethodCeil: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodCeil(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.ceil";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::ceil(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodCeil(miniScript));
	}
	{
		//
		class ScriptMethodRound: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodRound(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.round";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::round(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodRound(miniScript));
	}
	{
		//
		class ScriptMethodSqrt: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSqrt(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.sqrt";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::sqrt(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodSqrt(miniScript));
	}
	{
		//
		class ScriptMethodRandom: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodRandom(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.random";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setValue(Math::random());
			}
		};
		miniScript->registerMethod(new ScriptMethodRandom(miniScript));
	}
	{
		//
		class ScriptMethodExp: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodExp(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.exp";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::exp(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodExp(miniScript));
	}
	{
		//
		class ScriptMethodLog: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodLog(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.log";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
					returnValue.setValue(Math::log(value));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodLog(miniScript));
	}
	{
		//
		class ScriptMethodSign: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSign(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.sign";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t intValue;
				float floatValue;
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					returnValue.setValue(Math::sign(floatValue));
				} else
				if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
					returnValue.setValue(Math::sign(intValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodSign(miniScript));
	}
	{
		//
		class ScriptMethodSquare: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSquare(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.square";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t intValue;
				float floatValue;
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					returnValue.setValue(Math::square(floatValue));
				} else
				if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
					returnValue.setValue(Math::square(intValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodSquare(miniScript));
	}
	{
		//
		class ScriptMethodMin: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMin(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "a", .optional = false, .assignBack = false },
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "b", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.min";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t intValueA;
				int64_t intValueB;
				float floatValueA;
				float floatValueB;
				if (argumentValues.size() != 2) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
					miniScript->startErrorScript();
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
					MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(Math::min(floatValueA, floatValueB));
				} else
				if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true) {
					returnValue.setValue(Math::min(intValueA, intValueB));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMin(miniScript));
	}
	{
		//
		class ScriptMethodMax: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMax(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "a", .optional = false, .assignBack = false },
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "b", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.max";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t intValueA;
				int64_t intValueB;
				float floatValueA;
				float floatValueB;
				if (argumentValues.size() != 2) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
					miniScript->startErrorScript();
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
					MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(Math::max(floatValueA, floatValueB));
				} else
				if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true) {
					returnValue.setValue(Math::max(intValueA, intValueB));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMax(miniScript));
	}
	{
		//
		class ScriptMethodAbs: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAbs(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.abs";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t intValue;
				float floatValue;
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					returnValue.setValue(Math::abs(floatValue));
				} else
				if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
					returnValue.setValue(Math::abs(intValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodAbs(miniScript));
	}
	{
		//
		class ScriptMethodClamp: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodClamp(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .assignBack = false },
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "min", .optional = false, .assignBack = false },
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "max", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.clamp";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t intValueA;
				int64_t intValueB;
				int64_t intValueC;
				float floatValueA;
				float floatValueB;
				float floatValueC;
				if (argumentValues.size() != 3) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
					miniScript->startErrorScript();
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
					MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, floatValueC, false) == true) {
					returnValue.setValue(Math::clamp(floatValueA, floatValueB, floatValueC));
				} else
				if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 2, intValueC, false) == true) {
					returnValue.setValue(Math::clamp(intValueA, intValueB, intValueC));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodClamp(miniScript));
	}
	{
		//
		class ScriptMethodPow: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodPow(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "a", .optional = false, .assignBack = false },
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "b", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.pow";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t intValueA;
				int64_t intValueB;
				float floatValueA;
				float floatValueB;
				if (argumentValues.size() != 2) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
					miniScript->startErrorScript();
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
					MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(Math::pow(floatValueA, floatValueB));
				} else
				if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true) {
					returnValue.setValue(Math::pow(intValueA, intValueB));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodPow(miniScript));
	}
	{
		//
		class ScriptMethodMod: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMod(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .assignBack = false },
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "range", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER
			), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.mod";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_INTEGER) == true) {
					int64_t value;
					int64_t range;
					if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == true &&
						MiniScript::getIntegerValue(argumentValues, 1, range, false) == true) {
						returnValue.setValue(Math::mod(value, range));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: number expected, @ argument 1: number expected");
						miniScript->startErrorScript();
					}
				} else {
					float value;
					float range;
					if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
						returnValue.setValue(Math::mod(value, range));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: number expected, @ argument 1: number expected");
						miniScript->startErrorScript();
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMod(miniScript));
	}
	{
		//
		class ScriptMethodAbsMod: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAbsMod(MiniScript* miniScript): MiniScript::ScriptMethod(
				{
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .assignBack = false },
					{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER, .name = "range", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER
			), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.absmod";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_INTEGER) == true) {
					int64_t value;
					int64_t range;
					if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == true &&
						MiniScript::getIntegerValue(argumentValues, 1, range, false) == true) {
						returnValue.setValue(Math::absmod(value, range));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: number expected, @ argument 1: number expected");
						miniScript->startErrorScript();
					}
				} else {
					float value;
					float range;
					if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
						returnValue.setValue(Math::absmod(value, range));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: number expected, @ argument 1: number expected");
						miniScript->startErrorScript();
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodAbsMod(miniScript));
	}
}

void MiniScriptMath::mul(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) {
	if (argumentValues.size() != 2) {
		Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: mixed expected, @ argument 1: mixed expected");
		miniScript->startErrorScript();
		return;
	}
	// matrix4x4
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_MATRIX4x4) == true) {
		// matrix4x4 * matrix
		if (argumentValues[0].getType() == MiniScript::TYPE_MATRIX4x4 &&
			argumentValues[1].getType() == MiniScript::TYPE_MATRIX4x4) {
			Matrix4x4 a;
			Matrix4x4 b;
			MiniScript::getMatrix4x4Value(argumentValues, 0, a, false);
			MiniScript::getMatrix4x4Value(argumentValues, 1, b, false);
			returnValue.setValue(a * b);
		} else
		// matrix4x4 * vec4
		if (argumentValues[0].getType() == MiniScript::TYPE_MATRIX4x4 &&
			argumentValues[1].getType() == MiniScript::TYPE_VECTOR4) {
			Matrix4x4 a;
			Vector4 b;
			MiniScript::getMatrix4x4Value(argumentValues, 0, a, false);
			MiniScript::getVector4Value(argumentValues, 1, b, false);
			returnValue.setValue(a * b);
		} else
		// vec4 * matrix4x4
		if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR4 &&
			argumentValues[1].getType() == MiniScript::TYPE_MATRIX4x4) {
			Vector4 a;
			Matrix4x4 b;
			MiniScript::getVector4Value(argumentValues, 0, a, false);
			MiniScript::getMatrix4x4Value(argumentValues, 1, b, false);
			returnValue.setValue(b * a);
		} else
		// matrix4x4 * vec3
		if (argumentValues[0].getType() == MiniScript::TYPE_MATRIX4x4 &&
			argumentValues[1].getType() == MiniScript::TYPE_VECTOR3) {
			Matrix4x4 a;
			Vector3 b;
			MiniScript::getMatrix4x4Value(argumentValues, 0, a, false);
			MiniScript::getVector3Value(argumentValues, 1, b, false);
			returnValue.setValue(a * b);
		} else
		// vec3 * matrix4x4
		if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3 &&
			argumentValues[1].getType() == MiniScript::TYPE_MATRIX4x4) {
			Vector3 a;
			Matrix4x4 b;
			MiniScript::getVector3Value(argumentValues, 0, a, false);
			MiniScript::getMatrix4x4Value(argumentValues, 1, b, false);
			returnValue.setValue(b * a);
		} else
		// matrix4x4 * float
		if (argumentValues[0].getType() == MiniScript::TYPE_MATRIX4x4 &&
			MiniScript::ScriptVariable::isExpectedType(argumentValues[1].getType(), MiniScript::TYPE_PSEUDO_NUMBER) == true) {
			Matrix4x4 a;
			float b;
			MiniScript::getMatrix4x4Value(argumentValues, 0, a, false);
			MiniScript::getFloatValue(argumentValues, 1, b, false);
			returnValue.setValue(a * b);
		} else
		// float * matrix4x4
		if (MiniScript::ScriptVariable::isExpectedType(argumentValues[0].getType(), MiniScript::TYPE_PSEUDO_NUMBER) == true &&
			argumentValues[1].getType() == MiniScript::TYPE_MATRIX4x4) {
			float a;
			Matrix4x4 b;
			MiniScript::getFloatValue(argumentValues, 0, a, false);
			MiniScript::getMatrix4x4Value(argumentValues, 1, b, false);
			returnValue.setValue(b * a);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4/vec4/vec3/float expected, @ argument 1: matrix3x3/vec4/vec3/float expected");
			miniScript->startErrorScript();
			return;
		}
	} else
	// matrix3x3
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_MATRIX3x3) == true) {
		// matrix3x3 * matrix
		if (argumentValues[0].getType() == MiniScript::TYPE_MATRIX3x3 &&
			argumentValues[1].getType() == MiniScript::TYPE_MATRIX3x3) {
			Matrix2D3x3 a;
			Matrix2D3x3 b;
			MiniScript::getMatrix3x3Value(argumentValues, 0, a, false);
			MiniScript::getMatrix3x3Value(argumentValues, 1, b, false);
			returnValue.setValue(a * b);
		} else
		// matrix3x3 * vec2
		if (argumentValues[0].getType() == MiniScript::TYPE_MATRIX3x3 &&
			argumentValues[1].getType() == MiniScript::TYPE_VECTOR2) {
			Matrix2D3x3 a;
			Vector2 b;
			MiniScript::getMatrix3x3Value(argumentValues, 0, a, false);
			MiniScript::getVector2Value(argumentValues, 1, b, false);
			returnValue.setValue(a * b);
		} else
		// vec2 * matrix3x3
		if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR2 &&
			argumentValues[1].getType() == MiniScript::TYPE_MATRIX3x3) {
			Vector2 a;
			Matrix2D3x3 b;
			MiniScript::getVector2Value(argumentValues, 0, a, false);
			MiniScript::getMatrix3x3Value(argumentValues, 1, b, false);
			returnValue.setValue(b * a);
		} else
		// matrix3x3 * float
		if (argumentValues[0].getType() == MiniScript::TYPE_MATRIX3x3 &&
			MiniScript::ScriptVariable::isExpectedType(argumentValues[1].getType(), MiniScript::TYPE_PSEUDO_NUMBER) == true) {
			Matrix2D3x3 a;
			float b;
			MiniScript::getMatrix3x3Value(argumentValues, 0, a, false);
			MiniScript::getFloatValue(argumentValues, 1, b, false);
			returnValue.setValue(a * b);
		} else
		// float * matrix3x3
		if (MiniScript::ScriptVariable::isExpectedType(argumentValues[0].getType(), MiniScript::TYPE_PSEUDO_NUMBER) == true &&
			argumentValues[1].getType() == MiniScript::TYPE_MATRIX3x3) {
			float a;
			Matrix2D3x3 b;
			MiniScript::getFloatValue(argumentValues, 0, a, false);
			MiniScript::getMatrix3x3Value(argumentValues, 1, b, false);
			returnValue.setValue(b * a);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix3x3/vec2/float expected, @ argument 1: matrix3x3/vec2/float expected");
			miniScript->startErrorScript();
			return;
		}
	} else
	// quaternion
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_QUATERNION) == true) {
		// quaternion * quaternion
		if (argumentValues[0].getType() == MiniScript::TYPE_QUATERNION &&
			argumentValues[1].getType() == MiniScript::TYPE_QUATERNION) {
			Quaternion a;
			Quaternion b;
			MiniScript::getQuaternionValue(argumentValues, 0, a, false);
			MiniScript::getQuaternionValue(argumentValues, 1, b, false);
			returnValue.setValue(a * b);
		} else
		// quaternion * vec3
		if (argumentValues[0].getType() == MiniScript::TYPE_QUATERNION &&
			argumentValues[1].getType() == MiniScript::TYPE_VECTOR3) {
			Quaternion a;
			Vector3 b;
			MiniScript::getQuaternionValue(argumentValues, 0, a, false);
			MiniScript::getVector3Value(argumentValues, 1, b, false);
			returnValue.setValue(a * b);
		} else
		// vec3 * quaternion
		if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3 &&
			argumentValues[1].getType() == MiniScript::TYPE_QUATERNION) {
			Vector3 a;
			Quaternion b;
			MiniScript::getVector3Value(argumentValues, 0, a, false);
			MiniScript::getQuaternionValue(argumentValues, 1, b, false);
			returnValue.setValue(b * a);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: quaternion/vec3 expected, @ argument 1: quaternion/vec3 expected");
			miniScript->startErrorScript();
			return;
		}
	} else
	// vector2
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR2) == true) {
		float f;
		// a
		Vector2 a;
		if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR2) {
			argumentValues[0].getVector2Value(a, false);
		} else
		if (MiniScript::getFloatValue(argumentValues, 0, f, false) == true) {
			a = Vector2(f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2/float expected, @ argument 1: vector2/float expected");
			miniScript->startErrorScript();
			return;
		}
		// b
		Vector2 b;
		if (argumentValues[1].getType() == MiniScript::TYPE_VECTOR2) {
			argumentValues[1].getVector2Value(b);
		} else
		if (MiniScript::getFloatValue(argumentValues, 1, f, false) == true) {
			b = Vector2(f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2/float expected, @ argument 1: vector2/float expected");
			miniScript->startErrorScript();
			return;
		}
		//
		returnValue.setValue(a.clone().scale(b));
	} else
	// vector3
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
		float f;
		// a
		Vector3 a;
		if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
			argumentValues[0].getVector3Value(a, false);
		} else
		if (MiniScript::getFloatValue(argumentValues, 0, f, false) == true) {
			a = Vector3(f, f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3/float expected, @ argument 1: vector3/float expected");
			miniScript->startErrorScript();
			return;
		}
		// b
		Vector3 b;
		if (argumentValues[1].getType() == MiniScript::TYPE_VECTOR3) {
			argumentValues[1].getVector3Value(b);
		} else
		if (MiniScript::getFloatValue(argumentValues, 1, f, false) == true) {
			b = Vector3(f, f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3/float expected, @ argument 1: vector3/float expected");
			miniScript->startErrorScript();
			return;
		}
		//
		returnValue.setValue(a.clone().scale(b));
	} else
	// vector4
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR4) == true) {
		float f;
		// a
		Vector4 a;
		if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR4) {
			argumentValues[0].getVector4Value(a, false);
		} else
		if (MiniScript::getFloatValue(argumentValues, 0, f, false) == true) {
			a = Vector4(f, f, f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4/float expected, @ argument 1: vector4/float expected");
			miniScript->startErrorScript();
			return;
		}
		// b
		Vector4 b;
		if (argumentValues[1].getType() == MiniScript::TYPE_VECTOR4) {
			argumentValues[1].getVector4Value(b);
		} else
		if (MiniScript::getFloatValue(argumentValues, 1, f, false) == true) {
			b = Vector4(f, f, f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4/float expected, @ argument 1: vector4/float expected");
			miniScript->startErrorScript();
			return;
		}
		//
		returnValue.setValue(a.clone().scale(b));
	} else
	// float
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		if (MiniScript::getFloatValue(argumentValues, 0, a, false) == true &&
			MiniScript::getFloatValue(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a * b);
		} else  {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
			miniScript->startErrorScript();
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		if (MiniScript::getIntegerValue(argumentValues, 0, a, false) == true &&
			MiniScript::getIntegerValue(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a * b);
		} else  {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected, @ argument 1: integer expected");
			miniScript->startErrorScript();
			return;
		}
	}
}

void MiniScriptMath::div(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) {
	if (argumentValues.size() != 2) {
		Console::println("div(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: mixed expected, @ argument 1: mixed expected");
		miniScript->startErrorScript();
		return;
	}
	// vector2
	if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR2) {
		Vector2 a;
		Vector2 b;
		float f;
		// a
		MiniScript::getVector2Value(argumentValues, 0, a, false);
		// b
		if (argumentValues[1].getType() == MiniScript::TYPE_VECTOR2 &&
			MiniScript::getVector2Value(argumentValues, 1, b, false) == true) {
			// nop
		} else
		if (MiniScript::getFloatValue(argumentValues, 1, f, false) == true) {
			b = Vector2(f, f);
		} else {
			Console::println("div(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vec2 expected, @ argument 1: vec2/float expected");
			miniScript->startErrorScript();
			return;
		}
		returnValue.setValue(a / b);
	} else
	// vector3
	if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
		Vector3 a;
		Vector3 b;
		float f;
		// a
		MiniScript::getVector3Value(argumentValues, 0, a, false);
		// b
		if (argumentValues[1].getType() == MiniScript::TYPE_VECTOR3 &&
			MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
			// nop
		} else
		if (MiniScript::getFloatValue(argumentValues, 1, f, false) == true) {
			b = Vector3(f, f, f);
		} else {
			Console::println("div(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vec3 expected, @ argument 1: vec3/float expected");
			miniScript->startErrorScript();
			return;
		}
		returnValue.setValue(a / b);
	} else
	// vector4
	if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR4) {
		Vector4 a;
		Vector4 b;
		float f;
		// a
		MiniScript::getVector4Value(argumentValues, 0, a, false);
		// b
		if (argumentValues[1].getType() == MiniScript::TYPE_VECTOR4 &&
			MiniScript::getVector4Value(argumentValues, 1, b, false) == true) {
			// nop
		} else
		if (MiniScript::getFloatValue(argumentValues, 1, f, false) == true) {
			b = Vector4(f, f, f, f);
		} else {
			Console::println("div(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vec4 expected, @ argument 1: vec4/float expected");
			miniScript->startErrorScript();
			return;
		}
		returnValue.setValue(a / b);
	} else
	// float
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		if (MiniScript::getFloatValue(argumentValues, 0, a, false) == true &&
			MiniScript::getFloatValue(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a / b);
		} else  {
			Console::println("div(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
			miniScript->startErrorScript();
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		if (MiniScript::getIntegerValue(argumentValues, 0, a, false) == true &&
			MiniScript::getIntegerValue(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a / b);
		} else  {
			Console::println("div(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected, @ argument 1: integer expected");
			miniScript->startErrorScript();
			return;
		}
	}
}

void MiniScriptMath::add(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) {
	if (argumentValues.size() != 2) {
		Console::println(miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: mixed expected, @ argument 1: mixed expected");
		miniScript->startErrorScript();
		return;
	}
	// string concatenation
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
		string result;
		for (auto i = 0; i < argumentValues.size(); i++) {
			result+= argumentValues[i].getValueString();
		}
		returnValue.setValue(result);
	} else
	// vector2
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR2) == true) {
		Vector2 a;
		Vector2 b;
		if (MiniScript::getVector2Value(argumentValues, 0, a, false) == true &&
			MiniScript::getVector2Value(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a.clone().add(b));
		} else  {
			Console::println("add(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 expected, @ argument 1: vector2 expected");
			miniScript->startErrorScript();
			return;
		}
	} else
	// vector3
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
		Vector3 a;
		Vector3 b;
		if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
			MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a.clone().add(b));
		} else  {
			Console::println("add(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
			miniScript->startErrorScript();
			return;
		}
	} else
	// vector4
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR4) == true) {
		Vector4 a;
		Vector4 b;
		if (MiniScript::getVector4Value(argumentValues, 0, a, false) == true &&
			MiniScript::getVector4Value(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a.clone().add(b));
		} else  {
			Console::println("add(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4 expected, @ argument 1: vector4 expected");
			miniScript->startErrorScript();
			return;
		}
	} else
	// quaternion
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_QUATERNION) == true) {
		Quaternion a;
		Quaternion b;
		if (MiniScript::getQuaternionValue(argumentValues, 0, a, false) == true &&
			MiniScript::getQuaternionValue(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a.clone().add(b));
		} else  {
			Console::println("add(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion expected");
			miniScript->startErrorScript();
			return;
		}
	} else
	// float
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		if (MiniScript::getFloatValue(argumentValues, 0, a, false) == true &&
			MiniScript::getFloatValue(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a + b);
		} else  {
			Console::println("add(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
			miniScript->startErrorScript();
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		if (MiniScript::getIntegerValue(argumentValues, 0, a, false) == true &&
			MiniScript::getIntegerValue(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a + b);
		} else  {
			Console::println("add(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected, @ argument 1: integer expected");
			miniScript->startErrorScript();
			return;
		}
	}
}

void MiniScriptMath::sub(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) {
	if (argumentValues.size() != 2) {
		Console::println("sub(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: mixed expected, @ argument 1: mixed expected");
		miniScript->startErrorScript();
		return;
	}
	// vector2
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR2) == true) {
		Vector2 a;
		Vector2 b;
		if (MiniScript::getVector2Value(argumentValues, 0, a, false) == true &&
			MiniScript::getVector2Value(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a.clone().sub(b));
		} else  {
			Console::println("sub(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 expected, @ argument 1: vector2 expected");
			miniScript->startErrorScript();
			return;
		}
	} else
	// vector3
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
		Vector3 a;
		Vector3 b;
		if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
			MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a.clone().sub(b));
		} else  {
			Console::println("sub(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
			miniScript->startErrorScript();
			return;
		}
	} else
	// vector4
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR4) == true) {
		Vector4 a;
		Vector4 b;
		if (MiniScript::getVector4Value(argumentValues, 0, a, false) == true &&
			MiniScript::getVector4Value(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a.clone().sub(b));
		} else  {
			Console::println("sub(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4 expected, @ argument 1: vector4 expected");
			miniScript->startErrorScript();
			return;
		}
	} else
	// quaternion
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_QUATERNION) == true) {
		Quaternion a;
		Quaternion b;
		if (MiniScript::getQuaternionValue(argumentValues, 0, a, false) == true &&
			MiniScript::getQuaternionValue(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a.clone().sub(b));
		} else  {
			Console::println("sub(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion expected");
			miniScript->startErrorScript();
			return;
		}
	} else
	// float
	if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		if (MiniScript::getFloatValue(argumentValues, 0, a, false) == true &&
			MiniScript::getFloatValue(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a - b);
		} else  {
			Console::println("sub(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
			miniScript->startErrorScript();
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		if (MiniScript::getIntegerValue(argumentValues, 0, a, false) == true &&
			MiniScript::getIntegerValue(argumentValues, 1, b, false) == true) {
			returnValue.setValue(a - b);
		} else  {
			Console::println("sub(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected, @ argument 1: integer expected");
			miniScript->startErrorScript();
			return;
		}
	}
}
