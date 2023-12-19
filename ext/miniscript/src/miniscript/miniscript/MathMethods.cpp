#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/math/Math.h>
#include <miniscript/miniscript/MathMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>

using std::span;

using miniscript::miniscript::MathMethods;

using miniscript::miniscript::MiniScript;

using _Math = miniscript::math::Math;
using _Console = miniscript::utilities::Console;

void MathMethods::registerDataType(MiniScript::DataType* dataType) {
	dataTypes.push_back(dataType);
}

void MathMethods::registerMethods() {
	// operator methods
	{
		//
		class MethodAdd: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodAdd(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "add";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				miniScript->getMathMethods()->add(arguments, returnValue, statement);
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_ADDITION;
			}
		};
		miniScript->registerMethod(new MethodAdd(miniScript));
	}
	{
		//
		class MethodSub: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSub(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "sub";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				miniScript->getMathMethods()->sub(arguments, returnValue, statement);
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_SUBTRACTION;
			}
		};
		miniScript->registerMethod(new MethodSub(miniScript));
	}
	{
		//
		class MethodMul: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMul(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mul";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				miniScript->getMathMethods()->mul(arguments, returnValue, statement);
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_MULTIPLICATION;
			}
		};
		miniScript->registerMethod(new MethodMul(miniScript));
	}
	{
		//
		class MethodDiv: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodDiv(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "div";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				miniScript->getMathMethods()->div(arguments, returnValue, statement);
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_DIVISION;
			}
		};
		miniScript->registerMethod(new MethodDiv(miniScript));
	}
	{
		//
		class MethodMod: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMod(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false },
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "range", .optional = false, .reference = false },
				},
				MiniScript::TYPE_PSEUDO_NUMBER
			), miniScript(miniScript) {}
			const string getMethodName() override {
				return "mod";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (MiniScript::hasType(arguments, MiniScript::TYPE_INTEGER) == true) {
					int64_t value;
					int64_t range;
					if (MiniScript::getIntegerValue(arguments, 0, value, false) == true &&
						MiniScript::getIntegerValue(arguments, 1, range, false) == true) {
						returnValue.setValue(_Math::mod(value, range));
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float value;
					float range;
					if (MiniScript::getFloatValue(arguments, 0, value, false) == true &&
						MiniScript::getFloatValue(arguments, 1, range, false) == true) {
						returnValue.setValue(_Math::mod(value, range));
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_MODULO;
			}
		};
		miniScript->registerMethod(new MethodMod(miniScript));
	}
	// constants
	{
		//
		class MethodPI: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodPI(MiniScript* miniScript): MiniScript::Method({}, MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.PI";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setValue(_Math::PI);
			}
		};
		miniScript->registerMethod(new MethodPI(miniScript));
	}
	{
		//
		class MethodEPSILON: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodEPSILON(MiniScript* miniScript): MiniScript::Method({}, MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.EPSILON";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setValue(_Math::EPSILON);
			}
		};
		miniScript->registerMethod(new MethodEPSILON(miniScript));
	}
	{
		//
		class MethodDEG2RAD: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodDEG2RAD(MiniScript* miniScript): MiniScript::Method({}, MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.DEG2RAD";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setValue(_Math::DEG2RAD);
			}
		};
		miniScript->registerMethod(new MethodDEG2RAD(miniScript));
	}
	{
		//
		class MethodG: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodG(MiniScript* miniScript): MiniScript::Method({}, MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.G";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setValue(_Math::G);
			}
		};
		miniScript->registerMethod(new MethodG(miniScript));
	}
	{
		//
		class MethodAcos: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodAcos(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.acos";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float x;
				if (MiniScript::getFloatValue(arguments, 0, x, false) == true) {
					returnValue.setValue(_Math::acos(x));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodAcos(miniScript));
	}
	{
		//
		class MethodAsin: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodAsin(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.asin";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float x;
				if (MiniScript::getFloatValue(arguments, 0, x, false) == true) {
					returnValue.setValue(_Math::asin(x));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodAsin(miniScript));
	}
	{
		//
		class MethodAtan: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodAtan(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.atan";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float x;
				if (MiniScript::getFloatValue(arguments, 0, x, false) == true) {
					returnValue.setValue(_Math::atan(x));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodAtan(miniScript));
	}
	{
		//
		class MethodAtan2: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodAtan2(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "y", .optional = false, .reference = false },
					{ .type = MiniScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.atan2";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float y;
				float x;
				if (MiniScript::getFloatValue(arguments, 0, y, false) == true &&
					MiniScript::getFloatValue(arguments, 1, x, false) == true) {
					returnValue.setValue(_Math::atan2(y, x));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodAtan2(miniScript));
	}
	{
		//
		class MethodTan: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodTan(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.tan";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float x;
				if (MiniScript::getFloatValue(arguments, 0, x, false) == true) {
					returnValue.setValue(_Math::tan(x));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTan(miniScript));
	}
	{
		//
		class MethodCos: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodCos(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.cos";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float x;
				if (MiniScript::getFloatValue(arguments, 0, x, false) == true) {
					returnValue.setValue(_Math::cos(x));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodCos(miniScript));
	}
	{
		//
		class MethodSin: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSin(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.sin";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float x;
				if (MiniScript::getFloatValue(arguments, 0, x, false) == true) {
					returnValue.setValue(_Math::sin(x));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodSin(miniScript));
	}
	{
		//
		class MethodFloor: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodFloor(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "value", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.floor";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float value;
				if (MiniScript::getFloatValue(arguments, 0, value, false) == true) {
					returnValue.setValue(_Math::floor(value));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodFloor(miniScript));
	}
	{
		//
		class MethodCeil: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodCeil(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "value", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.ceil";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float value;
				if (MiniScript::getFloatValue(arguments, 0, value, false) == true) {
					returnValue.setValue(_Math::ceil(value));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodCeil(miniScript));
	}
	{
		//
		class MethodRound: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodRound(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "value", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.round";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float value;
				if (MiniScript::getFloatValue(arguments, 0, value, false) == true) {
					returnValue.setValue(_Math::round(value));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodRound(miniScript));
	}
	{
		//
		class MethodSqrt: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSqrt(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "value", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.sqrt";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float value;
				if (MiniScript::getFloatValue(arguments, 0, value, false) == true) {
					returnValue.setValue(_Math::sqrt(value));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodSqrt(miniScript));
	}
	{
		//
		class MethodRandom: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodRandom(MiniScript* miniScript): MiniScript::Method({}, MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.random";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setValue(_Math::random());
			}
		};
		miniScript->registerMethod(new MethodRandom(miniScript));
	}
	{
		//
		class MethodExp: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodExp(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "power", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.exp";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float power;
				if (MiniScript::getFloatValue(arguments, 0, power, false) == true) {
					returnValue.setValue(_Math::exp(power));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodExp(miniScript));
	}
	{
		//
		class MethodLog: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodLog(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_FLOAT, .name = "value", .optional = false, .reference = false },
				},
				MiniScript::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.log";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float value;
				if (MiniScript::getFloatValue(arguments, 0, value, false) == true) {
					returnValue.setValue(_Math::log(value));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodLog(miniScript));
	}
	{
		//
		class MethodSign: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSign(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false },
				},
				MiniScript::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.sign";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t intValue;
				float floatValue;
				if (MiniScript::hasType(arguments, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(arguments, 0, floatValue, false) == true) {
					returnValue.setValue(_Math::sign(floatValue));
				} else
				if (MiniScript::getIntegerValue(arguments, 0, intValue, false) == true) {
					returnValue.setValue(_Math::sign(intValue));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodSign(miniScript));
	}
	{
		//
		class MethodSquare: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSquare(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false },
				},
				MiniScript::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.square";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t intValue;
				float floatValue;
				if (MiniScript::hasType(arguments, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(arguments, 0, floatValue, false) == true) {
					returnValue.setValue(_Math::square(floatValue));
				} else
				if (MiniScript::getIntegerValue(arguments, 0, intValue, false) == true) {
					returnValue.setValue(_Math::square(intValue));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodSquare(miniScript));
	}
	{
		//
		class MethodMin: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMin(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "value1", .optional = false, .reference = false },
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "value2", .optional = false, .reference = false },
				},
				MiniScript::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.min";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t intValue1;
				int64_t intValue2;
				float floatValue1;
				float floatValue2;
				if (arguments.size() != 2) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else
				if (MiniScript::hasType(arguments, MiniScript::TYPE_FLOAT) == true &&
					MiniScript::getFloatValue(arguments, 0, floatValue1, false) == true &&
					MiniScript::getFloatValue(arguments, 1, floatValue2, false) == true) {
					returnValue.setValue(_Math::min(floatValue1, floatValue2));
				} else
				if (MiniScript::getIntegerValue(arguments, 0, intValue1, false) == true &&
					MiniScript::getIntegerValue(arguments, 1, intValue2, false) == true) {
					returnValue.setValue(_Math::min(intValue1, intValue2));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMin(miniScript));
	}
	{
		//
		class MethodMax: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMax(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "value1", .optional = false, .reference = false },
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "value2", .optional = false, .reference = false },
				},
				MiniScript::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.max";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t intValue1;
				int64_t intValue2;
				float floatValue1;
				float floatValue2;
				if (arguments.size() != 2) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else
				if (MiniScript::hasType(arguments, MiniScript::TYPE_FLOAT) == true &&
					MiniScript::getFloatValue(arguments, 0, floatValue1, false) == true &&
					MiniScript::getFloatValue(arguments, 1, floatValue2, false) == true) {
					returnValue.setValue(_Math::max(floatValue1, floatValue2));
				} else
				if (MiniScript::getIntegerValue(arguments, 0, intValue1, false) == true &&
					MiniScript::getIntegerValue(arguments, 1, intValue2, false) == true) {
					returnValue.setValue(_Math::max(intValue1, intValue2));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMax(miniScript));
	}
	{
		//
		class MethodAbs: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodAbs(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false },
				},
				MiniScript::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.abs";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t intValue;
				float floatValue;
				if (MiniScript::hasType(arguments, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(arguments, 0, floatValue, false) == true) {
					returnValue.setValue(_Math::abs(floatValue));
				} else
				if (MiniScript::getIntegerValue(arguments, 0, intValue, false) == true) {
					returnValue.setValue(_Math::abs(intValue));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodAbs(miniScript));
	}
	{
		//
		class MethodClamp: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodClamp(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false },
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "min", .optional = false, .reference = false },
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "max", .optional = false, .reference = false },
				},
				MiniScript::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.clamp";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t intValueA;
				int64_t intValueB;
				int64_t intValueC;
				float floatValueA;
				float floatValueB;
				float floatValueC;
				if (arguments.size() != 3) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else
				if (MiniScript::hasType(arguments, MiniScript::TYPE_FLOAT) == true &&
					MiniScript::getFloatValue(arguments, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(arguments, 1, floatValueB, false) == true &&
					MiniScript::getFloatValue(arguments, 2, floatValueC, false) == true) {
					returnValue.setValue(_Math::clamp(floatValueA, floatValueB, floatValueC));
				} else
				if (MiniScript::getIntegerValue(arguments, 0, intValueA, false) == true &&
					MiniScript::getIntegerValue(arguments, 1, intValueB, false) == true &&
					MiniScript::getIntegerValue(arguments, 2, intValueC, false) == true) {
					returnValue.setValue(_Math::clamp(intValueA, intValueB, intValueC));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodClamp(miniScript));
	}
	{
		//
		class MethodPow: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodPow(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "base", .optional = false, .reference = false },
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "power", .optional = false, .reference = false },
				},
				MiniScript::TYPE_PSEUDO_NUMBER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.pow";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t intValueBase;
				int64_t intValuePower;
				float floatValueBase;
				float floatValuePower;
				if (arguments.size() != 2) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else
				if (MiniScript::hasType(arguments, MiniScript::TYPE_FLOAT) == true &&
					MiniScript::getFloatValue(arguments, 0, floatValueBase, false) == true &&
					MiniScript::getFloatValue(arguments, 1, floatValuePower, false) == true) {
					returnValue.setValue(_Math::pow(floatValueBase, floatValuePower));
				} else
				if (MiniScript::getIntegerValue(arguments, 0, intValueBase, false) == true &&
					MiniScript::getIntegerValue(arguments, 1, intValuePower, false) == true) {
					returnValue.setValue(static_cast<int64_t>(_Math::pow(intValueBase, intValuePower)));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodPow(miniScript));
	}
	{
		//
		class MethodMod: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMod(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false },
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "range", .optional = false, .reference = false },
				},
				MiniScript::TYPE_PSEUDO_NUMBER
			), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.mod";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (MiniScript::hasType(arguments, MiniScript::TYPE_INTEGER) == true) {
					int64_t value;
					int64_t range;
					if (MiniScript::getIntegerValue(arguments, 0, value, false) == true &&
						MiniScript::getIntegerValue(arguments, 1, range, false) == true) {
						returnValue.setValue(_Math::mod(value, range));
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float value;
					float range;
					if (MiniScript::getFloatValue(arguments, 0, value, false) == true &&
						MiniScript::getFloatValue(arguments, 1, range, false) == true) {
						returnValue.setValue(_Math::mod(value, range));
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
		};
		miniScript->registerMethod(new MethodMod(miniScript));
	}
	{
		//
		class MethodAbsMod: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodAbsMod(MiniScript* miniScript): MiniScript::Method(
				{
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false },
					{ .type = MiniScript::TYPE_PSEUDO_NUMBER, .name = "range", .optional = false, .reference = false },
				},
				MiniScript::TYPE_PSEUDO_NUMBER
			), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.absmod";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (MiniScript::hasType(arguments, MiniScript::TYPE_INTEGER) == true) {
					int64_t value;
					int64_t range;
					if (MiniScript::getIntegerValue(arguments, 0, value, false) == true &&
						MiniScript::getIntegerValue(arguments, 1, range, false) == true) {
						returnValue.setValue(_Math::absmod(value, range));
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float value;
					float range;
					if (MiniScript::getFloatValue(arguments, 0, value, false) == true &&
						MiniScript::getFloatValue(arguments, 1, range, false) == true) {
						returnValue.setValue(_Math::absmod(value, range));
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
		};
		miniScript->registerMethod(new MethodAbsMod(miniScript));
	}
}

void MathMethods::mul(const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) {
	if (arguments.size() != 2) {
		_Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
		miniScript->startErrorScript();
		//
		return;
	}
	// custom data types
	for (const auto dataType: dataTypes) {
		if (dataType->mul(miniScript, arguments, returnValue, statement) == true) return;
	}
	// float
	if (MiniScript::hasType(arguments, MiniScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		if (MiniScript::getFloatValue(arguments, 0, a, false) == true &&
			MiniScript::getFloatValue(arguments, 1, b, false) == true) {
			returnValue.setValue(a * b);
			//
			return;
		} else  {
			_Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
			miniScript->startErrorScript();
			//
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		if (MiniScript::getIntegerValue(arguments, 0, a, false) == true &&
			MiniScript::getIntegerValue(arguments, 1, b, false) == true) {
			returnValue.setValue(a * b);
			//
			return;
		} else  {
			_Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
			miniScript->startErrorScript();
			//
			return;
		}
	}
}

void MathMethods::div(const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) {
	if (arguments.size() != 2) {
		_Console::println("div(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("div"));
		miniScript->startErrorScript();
		//
		return;
	}
	// custom data types
	for (const auto dataType: dataTypes) {
		if (dataType->div(miniScript, arguments, returnValue, statement) == true) return;
	}
	// float
	if (MiniScript::hasType(arguments, MiniScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		if (MiniScript::getFloatValue(arguments, 0, a, false) == true &&
			MiniScript::getFloatValue(arguments, 1, b, false) == true) {
			returnValue.setValue(a / b);
			//
			return;
		} else  {
			_Console::println("div(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("div"));
			miniScript->startErrorScript();
			//
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		if (MiniScript::getIntegerValue(arguments, 0, a, false) == true &&
			MiniScript::getIntegerValue(arguments, 1, b, false) == true) {
			returnValue.setValue(a / b);
			//
			return;
		} else  {
			_Console::println("div(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("div"));
			miniScript->startErrorScript();
			//
			return;
		}
	}
}

void MathMethods::add(const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) {
	if (arguments.size() != 2) {
		_Console::println(miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("add"));
		miniScript->startErrorScript();
		return;
	}
	// string concatenation
	if (MiniScript::hasType(arguments, MiniScript::TYPE_STRING) == true) {
		string result;
		for (auto i = 0; i < arguments.size(); i++) {
			result+= arguments[i].getValueAsString();
		}
		returnValue.setValue(result);
		//
		return;
	}
	// custom data types
	for (const auto dataType: dataTypes) {
		if (dataType->add(miniScript, arguments, returnValue, statement) == true) return;
	}
	// float
	if (MiniScript::hasType(arguments, MiniScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		if (MiniScript::getFloatValue(arguments, 0, a, false) == true &&
			MiniScript::getFloatValue(arguments, 1, b, false) == true) {
			returnValue.setValue(a + b);
			//
			return;
		} else  {
			_Console::println("add(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("add"));
			miniScript->startErrorScript();
			//
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		if (MiniScript::getIntegerValue(arguments, 0, a, false) == true &&
			MiniScript::getIntegerValue(arguments, 1, b, false) == true) {
			returnValue.setValue(a + b);
			//
			return;
		} else  {
			_Console::println("add(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("add"));
			miniScript->startErrorScript();
			//
			return;
		}
	}

}

void MathMethods::sub(const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) {
	if (arguments.size() != 2) {
		_Console::println("sub(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("sub"));
		miniScript->startErrorScript();
		//
		return;
	}
	// custom data types
	for (const auto dataType: dataTypes) {
		if (dataType->sub(miniScript, arguments, returnValue, statement) == true) return;
	}
	// float
	if (MiniScript::hasType(arguments, MiniScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		if (MiniScript::getFloatValue(arguments, 0, a, false) == true &&
			MiniScript::getFloatValue(arguments, 1, b, false) == true) {
			returnValue.setValue(a - b);
			//
			return;
		} else  {
			_Console::println("sub(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("sub"));
			miniScript->startErrorScript();
			//
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		if (MiniScript::getIntegerValue(arguments, 0, a, false) == true &&
			MiniScript::getIntegerValue(arguments, 1, b, false) == true) {
			returnValue.setValue(a - b);
			//
			return;
		} else  {
			_Console::println("sub(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("sub"));
			miniScript->startErrorScript();
			//
			return;
		}
	}
}
