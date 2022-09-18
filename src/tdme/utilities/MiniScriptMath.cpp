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
			ScriptMethodAdd(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED), miniScript(miniScript) {}
			const string getMethodName() override {
				return "add";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
			}
			bool isVariadic() override {
				return true;
			}
			MiniScript::ScriptOperator getOperator() override {
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
			ScriptMethodSub(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED), miniScript(miniScript) {}
			const string getMethodName() override {
				return "sub";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
			}
			bool isVariadic() override {
				return true;
			}
			MiniScript::ScriptOperator getOperator() override {
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
			ScriptMethodMul(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED), miniScript(miniScript) {}
			const string getMethodName() override {
				return "mul";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
			}
			bool isVariadic() override {
				return true;
			}
			MiniScript::ScriptOperator getOperator() override {
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
			ScriptMethodDiv(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED), miniScript(miniScript) {}
			const string getMethodName() override {
				return "div";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
			}
			bool isVariadic() override {
				return true;
			}
			MiniScript::ScriptOperator getOperator() override {
				return MiniScript::OPERATOR_DIVISION;
			}
		};
		miniScript->registerMethod(new ScriptMethodDiv(miniScript));
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
					Console::println("ScriptMethodAcos::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodAsin::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodAtan::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodAtan2::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
					Console::println("ScriptMethodTan::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodCos::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodSin::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodCeil::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodCeil::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodRound::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodSqrt::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodExp::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodLog::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodSign::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
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
					Console::println("ScriptMethodSquare::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
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
					Console::println("ScriptMethodMin::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
					Console::println("ScriptMethodMin::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
					Console::println("ScriptMethodMax::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
					Console::println("ScriptMethodMax::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
					Console::println("ScriptMethodAbs::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
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
					Console::println("ScriptMethodClamp::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
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
					Console::println("ScriptMethodClamp::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
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
					Console::println("ScriptMethodPow::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
					Console::println("ScriptMethodPow::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "range", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT
			), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.mod";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				float range;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::mod(value, range));
				} else {
					Console::println("ScriptMethodMod::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript();
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
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "value", .optional = false, .assignBack = false },
					{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "range", .optional = false, .assignBack = false },
				},
				MiniScript::ScriptVariableType::TYPE_FLOAT
			), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.absmod";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float value;
				float range;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::absmod(value, range));
				} else {
					Console::println("ScriptMethodAbsMod::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodAbsMod(miniScript));
	}
}
