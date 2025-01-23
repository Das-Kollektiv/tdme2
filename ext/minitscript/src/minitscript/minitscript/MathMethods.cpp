#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/math/Math.h>
#include <minitscript/minitscript/MathMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/Console.h>

using std::span;

using minitscript::minitscript::MathMethods;

using minitscript::minitscript::MinitScript;

using _Math = minitscript::math::Math;
using _Console = minitscript::utilities::Console;

void MathMethods::registerDataType(MinitScript::DataType* dataType) {
	dataTypes.push_back(dataType);
}

void MathMethods::registerConstants() {
	minitScript->setConstant("$math::DEG2RAD", MinitScript::Variable(_Math::DEG2RAD));
	minitScript->setConstant("$math::EPSILON", MinitScript::Variable(_Math::EPSILON));
	minitScript->setConstant("$math::PI", MinitScript::Variable(_Math::PI));
}

void MathMethods::registerMethods() {
	// operator methods
	{
		//
		class MethodAdd: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodAdd(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "add";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				minitScript->getMathMethods()->add(arguments, returnValue, subStatement);
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_ADDITION;
			}
		};
		minitScript->registerMethod(new MethodAdd(minitScript));
	}
	{
		//
		class MethodSub: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSub(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "sub";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				minitScript->getMathMethods()->sub(arguments, returnValue, subStatement);
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_SUBTRACTION;
			}
		};
		minitScript->registerMethod(new MethodSub(minitScript));
	}
	{
		//
		class MethodMul: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMul(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "mul";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				minitScript->getMathMethods()->mul(arguments, returnValue, subStatement);
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_MULTIPLICATION;
			}
		};
		minitScript->registerMethod(new MethodMul(minitScript));
	}
	{
		//
		class MethodDiv: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodDiv(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "div";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				minitScript->getMathMethods()->div(arguments, returnValue, subStatement);
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_DIVISION;
			}
		};
		minitScript->registerMethod(new MethodDiv(minitScript));
	}
	{
		//
		class MethodMod: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMod(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false, .nullable = false },
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "range", .optional = false, .reference = false, .nullable = false },
					{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
				},
				MinitScript::TYPE_PSEUDO_NUMBER
			), minitScript(minitScript) {}
			const string getMethodName() override {
				return "mod";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2 || arguments.size() == 3) {
					if (MinitScript::hasType(arguments, MinitScript::TYPE_INTEGER) == true) {
						int64_t value;
						int64_t range;
						// TODO: correct complains
						if (MinitScript::getIntegerValue(arguments, 0, value, false) == true &&
							MinitScript::getIntegerValue(arguments, 1, range, false) == true) {
							returnValue.setValue(_Math::mod(value, range));
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
						}
					} else {
						float value;
						float range;
						// TODO: correct complains
						if (MinitScript::getFloatValue(arguments, 0, value, false) == true &&
							MinitScript::getFloatValue(arguments, 1, range, false) == true) {
							returnValue.setValue(_Math::mod(value, range));
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_MODULO;
			}
		};
		minitScript->registerMethod(new MethodMod(minitScript));
	}
	{
		//
		class MethodAcos: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodAcos(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.acos";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float x;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, x) == true) {
					returnValue.setValue(_Math::acos(x));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodAcos(minitScript));
	}
	{
		//
		class MethodAsin: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodAsin(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.asin";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float x;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, x) == true) {
					returnValue.setValue(_Math::asin(x));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodAsin(minitScript));
	}
	{
		//
		class MethodAtan: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodAtan(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.atan";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float x;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, x) == true) {
					returnValue.setValue(_Math::atan(x));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodAtan(minitScript));
	}
	{
		//
		class MethodAtan2: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodAtan2(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false },
					{ .type = MinitScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.atan2";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float y;
				float x;
				if (arguments.size() == 2 &&
					MinitScript::getFloatValue(arguments, 0, y) == true &&
					MinitScript::getFloatValue(arguments, 1, x) == true) {
					returnValue.setValue(_Math::atan2(y, x));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodAtan2(minitScript));
	}
	{
		//
		class MethodTan: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTan(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.tan";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float x;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, x) == true) {
					returnValue.setValue(_Math::tan(x));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodTan(minitScript));
	}
	{
		//
		class MethodCos: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodCos(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.cos";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float x;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, x) == true) {
					returnValue.setValue(_Math::cos(x));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodCos(minitScript));
	}
	{
		//
		class MethodSin: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSin(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.sin";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float x;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, x) == true) {
					returnValue.setValue(_Math::sin(x));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSin(minitScript));
	}
	{
		//
		class MethodFloor: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodFloor(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "value", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.floor";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float value;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, value) == true) {
					returnValue.setValue(_Math::floor(value));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodFloor(minitScript));
	}
	{
		//
		class MethodCeil: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodCeil(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "value", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.ceil";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float value;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, value) == true) {
					returnValue.setValue(_Math::ceil(value));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodCeil(minitScript));
	}
	{
		//
		class MethodRound: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodRound(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "value", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.round";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float value;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, value) == true) {
					returnValue.setValue(_Math::round(value));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodRound(minitScript));
	}
	{
		//
		class MethodSqrt: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSqrt(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "value", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.sqrt";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float value;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, value) == true) {
					returnValue.setValue(_Math::sqrt(value));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSqrt(minitScript));
	}
	{
		//
		class MethodRandom: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodRandom(MinitScript* minitScript): MinitScript::Method({}, MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.random";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					returnValue.setValue(_Math::random());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodRandom(minitScript));
	}
	{
		//
		class MethodExp: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodExp(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "power", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.exp";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float power;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, power) == true) {
					returnValue.setValue(_Math::exp(power));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodExp(minitScript));
	}
	{
		//
		class MethodLog: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodLog(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_FLOAT, .name = "value", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_FLOAT), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.log";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float value;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, value) == true) {
					returnValue.setValue(_Math::log(value));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodLog(minitScript));
	}
	{
		//
		class MethodSign: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSign(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_PSEUDO_NUMBER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.sign";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1) {
					int64_t intValue;
					float floatValue;
					if (MinitScript::hasType(arguments, MinitScript::TYPE_FLOAT) == true && MinitScript::getFloatValue(arguments, 0, floatValue) == true) {
						returnValue.setValue(_Math::sign(floatValue));
					} else
					if (MinitScript::getIntegerValue(arguments, 0, intValue) == true) {
						returnValue.setValue(_Math::sign(intValue));
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSign(minitScript));
	}
	{
		//
		class MethodSquare: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSquare(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_PSEUDO_NUMBER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.square";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1) {
					int64_t intValue;
					float floatValue;
					if (MinitScript::hasType(arguments, MinitScript::TYPE_FLOAT) == true && MinitScript::getFloatValue(arguments, 0, floatValue) == true) {
						returnValue.setValue(_Math::square(floatValue));
					} else
					if (MinitScript::getIntegerValue(arguments, 0, intValue) == true) {
						returnValue.setValue(_Math::square(intValue));
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSquare(minitScript));
	}
	{
		//
		class MethodMin: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMin(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "value1", .optional = false, .reference = false, .nullable = false },
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "value2", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_PSEUDO_NUMBER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.min";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2) {
					int64_t intValue1;
					int64_t intValue2;
					float floatValue1;
					float floatValue2;
					if (MinitScript::hasType(arguments, MinitScript::TYPE_FLOAT) == true &&
						MinitScript::getFloatValue(arguments, 0, floatValue1) == true &&
						MinitScript::getFloatValue(arguments, 1, floatValue2) == true) {
						returnValue.setValue(_Math::min(floatValue1, floatValue2));
					} else
					if (MinitScript::getIntegerValue(arguments, 0, intValue1) == true &&
						MinitScript::getIntegerValue(arguments, 1, intValue2) == true) {
						returnValue.setValue(_Math::min(intValue1, intValue2));
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMin(minitScript));
	}
	{
		//
		class MethodMax: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMax(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "value1", .optional = false, .reference = false, .nullable = false },
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "value2", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_PSEUDO_NUMBER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.max";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2) {
					int64_t intValue1;
					int64_t intValue2;
					float floatValue1;
					float floatValue2;
					if (MinitScript::hasType(arguments, MinitScript::TYPE_FLOAT) == true &&
						MinitScript::getFloatValue(arguments, 0, floatValue1) == true &&
						MinitScript::getFloatValue(arguments, 1, floatValue2) == true) {
						returnValue.setValue(_Math::max(floatValue1, floatValue2));
					} else
					if (MinitScript::getIntegerValue(arguments, 0, intValue1) == true &&
						MinitScript::getIntegerValue(arguments, 1, intValue2) == true) {
						returnValue.setValue(_Math::max(intValue1, intValue2));
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMax(minitScript));
	}
	{
		//
		class MethodAbs: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodAbs(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_PSEUDO_NUMBER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.abs";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1) {
					int64_t intValue;
					float floatValue;
					if (MinitScript::hasType(arguments, MinitScript::TYPE_FLOAT) == true && MinitScript::getFloatValue(arguments, 0, floatValue) == true) {
						returnValue.setValue(_Math::abs(floatValue));
					} else
					if (MinitScript::getIntegerValue(arguments, 0, intValue) == true) {
						returnValue.setValue(_Math::abs(intValue));
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodAbs(minitScript));
	}
	{
		//
		class MethodClamp: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodClamp(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false, .nullable = false },
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "min", .optional = false, .reference = false, .nullable = false },
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "max", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_PSEUDO_NUMBER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.clamp";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 3) {
					int64_t intValueA;
					int64_t intValueB;
					int64_t intValueC;
					float floatValueA;
					float floatValueB;
					float floatValueC;
					if (MinitScript::hasType(arguments, MinitScript::TYPE_FLOAT) == true &&
						MinitScript::getFloatValue(arguments, 0, floatValueA) == true &&
						MinitScript::getFloatValue(arguments, 1, floatValueB) == true &&
						MinitScript::getFloatValue(arguments, 2, floatValueC) == true) {
						returnValue.setValue(_Math::clamp(floatValueA, floatValueB, floatValueC));
					} else
					if (MinitScript::getIntegerValue(arguments, 0, intValueA) == true &&
						MinitScript::getIntegerValue(arguments, 1, intValueB) == true &&
						MinitScript::getIntegerValue(arguments, 2, intValueC) == true) {
						returnValue.setValue(_Math::clamp(intValueA, intValueB, intValueC));
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodClamp(minitScript));
	}
	{
		//
		class MethodPow: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodPow(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "base", .optional = false, .reference = false, .nullable = false },
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "power", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_PSEUDO_NUMBER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.pow";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2) {
					int64_t intValueBase;
					int64_t intValuePower;
					float floatValueBase;
					float floatValuePower;
					if (MinitScript::hasType(arguments, MinitScript::TYPE_FLOAT) == true &&
						MinitScript::getFloatValue(arguments, 0, floatValueBase) == true &&
						MinitScript::getFloatValue(arguments, 1, floatValuePower) == true) {
						returnValue.setValue(_Math::pow(floatValueBase, floatValuePower));
					} else
					if (MinitScript::getIntegerValue(arguments, 0, intValueBase) == true &&
						MinitScript::getIntegerValue(arguments, 1, intValuePower) == true) {
						returnValue.setValue(static_cast<int64_t>(_Math::pow(intValueBase, intValuePower)));
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodPow(minitScript));
	}
	{
		//
		class MethodMod: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMod(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false, .nullable = false },
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "range", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_PSEUDO_NUMBER
			), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.mod";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2) {
					if (MinitScript::hasType(arguments, MinitScript::TYPE_INTEGER) == true) {
						int64_t value;
						int64_t range;
						if (MinitScript::getIntegerValue(arguments, 0, value) == true &&
							MinitScript::getIntegerValue(arguments, 1, range) == true) {
							returnValue.setValue(_Math::mod(value, range));
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
						}
					} else {
						float value;
						float range;
						if (MinitScript::getFloatValue(arguments, 0, value) == true &&
							MinitScript::getFloatValue(arguments, 1, range) == true) {
							returnValue.setValue(_Math::mod(value, range));
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMod(minitScript));
	}
	{
		//
		class MethodAbsMod: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodAbsMod(MinitScript* minitScript): MinitScript::Method(
				{
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "value", .optional = false, .reference = false, .nullable = false },
					{ .type = MinitScript::TYPE_PSEUDO_NUMBER, .name = "range", .optional = false, .reference = false, .nullable = false },
				},
				MinitScript::TYPE_PSEUDO_NUMBER
			), minitScript(minitScript) {}
			const string getMethodName() override {
				return "math.absmod";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2) {
					if (MinitScript::hasType(arguments, MinitScript::TYPE_INTEGER) == true) {
						int64_t value;
						int64_t range;
						if (MinitScript::getIntegerValue(arguments, 0, value) == true &&
							MinitScript::getIntegerValue(arguments, 1, range) == true) {
							returnValue.setValue(_Math::absmod(value, range));
						} else {
							minitScript->complain(getMethodName(), subStatement);
							minitScript->startErrorScript();
						}
					} else {
						float value;
						float range;
						if (MinitScript::getFloatValue(arguments, 0, value) == true &&
							MinitScript::getFloatValue(arguments, 1, range) == true) {
							returnValue.setValue(_Math::absmod(value, range));
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodAbsMod(minitScript));
	}
}

void MathMethods::mul(const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) {
	if (arguments.size() != 2 && arguments.size() != 3) {
		minitScript->complain(MinitScript::decodeOperator(arguments, 2, "mul"), subStatement); minitScript->startErrorScript();
		return;
	}
	// custom data types
	for (const auto dataType: dataTypes) {
		if (dataType->mul(minitScript, arguments, returnValue, subStatement) == true) return;
	}
	// float
	if (MinitScript::hasTypeForOperatorArguments(arguments, MinitScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		auto isAFloat = MinitScript::getFloatValue(arguments, 0, a, false);
		auto isBFloat = MinitScript::getFloatValue(arguments, 1, b, false);
		if (isAFloat == true &&
			isBFloat == true) {
			returnValue.setValue(a * b);
			return;
		} else  {
			minitScript->complainOperator(
				"mul",
				MinitScript::decodeOperator(arguments, 2, "mul"),
				subStatement,
				"Can not multiply " + arguments[0].getValueAsString() + " by " + arguments[1].getValueAsString()
			);
			minitScript->startErrorScript();
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		auto isAInteger = MinitScript::getIntegerValue(arguments, 0, a, false) == true;
		auto isBInteger = MinitScript::getIntegerValue(arguments, 1, b, false) == true;
		if (isAInteger == true &&
			isBInteger == true) {
			returnValue.setValue(a * b);
			return;
		} else  {
			minitScript->complainOperator(
				"mul",
				MinitScript::decodeOperator(arguments, 2, "mul"),
				subStatement,
				"Can not multiply " + arguments[0].getValueAsString() + " by " + arguments[1].getValueAsString()
			);
			minitScript->startErrorScript();
			return;
		}
	}
}

void MathMethods::div(const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) {
	if (arguments.size() != 2 && arguments.size() != 3) {
		minitScript->complain(MinitScript::decodeOperator(arguments, 2, "div"), subStatement); minitScript->startErrorScript();
		return;
	}
	// custom data types
	for (const auto dataType: dataTypes) {
		if (dataType->div(minitScript, arguments, returnValue, subStatement) == true) return;
	}
	// float
	if (MinitScript::hasTypeForOperatorArguments(arguments, MinitScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		auto isAFloat = MinitScript::getFloatValue(arguments, 0, a, false);
		auto isBFloat = MinitScript::getFloatValue(arguments, 1, b, false);
		if (isAFloat == true &&
			isBFloat == true) {
			returnValue.setValue(a / b);
			return;
		} else  {
			minitScript->complainOperator(
				"div",
				MinitScript::decodeOperator(arguments, 2, "div"),
				subStatement,
				"Can not divide " + arguments[0].getValueAsString() + " by " + arguments[1].getValueAsString()
			);
			minitScript->startErrorScript();
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		auto isAInteger = MinitScript::getIntegerValue(arguments, 0, a, false) == true;
		auto isBInteger = MinitScript::getIntegerValue(arguments, 1, b, false) == true;
		if (isAInteger == true &&
			isBInteger == true) {
			returnValue.setValue(a / b);
			return;
		} else  {
			minitScript->complainOperator(
				"div",
				MinitScript::decodeOperator(arguments, 2, "div"),
				subStatement,
				"Can not divide " + arguments[0].getValueAsString() + " by " + arguments[1].getValueAsString()
			);
			minitScript->startErrorScript();
			return;
		}
	}
}

void MathMethods::add(const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) {
	if (arguments.size() != 2 && arguments.size() != 3) {
		minitScript->complain(MinitScript::decodeOperator(arguments, 2, "add"), subStatement); minitScript->startErrorScript();
		return;
	}
	// string concatenation
	if (MinitScript::hasTypeForOperatorArguments(arguments, MinitScript::TYPE_STRING) == true) {
		string result;
		for (auto i = 0; i < arguments.size() - 1; i++) {
			result+= arguments[i].getValueAsString();
		}
		returnValue.setValue(result);
		return;
	}
	// custom data types
	for (const auto dataType: dataTypes) {
		if (dataType->add(minitScript, arguments, returnValue, subStatement) == true) return;
	}
	// array
	if (arguments[0].getType() == MinitScript::TYPE_ARRAY &&
		arguments[1].getType() == MinitScript::TYPE_ARRAY) {
		returnValue.setType(MinitScript::TYPE_ARRAY);
		{
			auto arrayPtr = arguments[0].getArrayPointer();
			if (arrayPtr != nullptr) {
				for (auto arrayEntry: *arrayPtr) returnValue.pushArrayEntry(MinitScript::Variable::createNonReferenceVariable(arrayEntry));
			}
		}
		{
			auto arrayPtr = arguments[1].getArrayPointer();
			if (arrayPtr != nullptr) {
				for (auto arrayEntry: *arrayPtr) returnValue.pushArrayEntry(MinitScript::Variable::createNonReferenceVariable(arrayEntry));
			}
		}
	} else
	// map
	if (arguments[0].getType() == MinitScript::TYPE_MAP &&
		arguments[1].getType() == MinitScript::TYPE_MAP) {
		returnValue.setType(MinitScript::TYPE_MAP);
		{
			auto mapPtr = arguments[0].getMapPointer();
			if (mapPtr != nullptr) {
				for (const auto& [mapKey, mapValue]: *mapPtr) returnValue.setMapEntry(mapKey, MinitScript::Variable::createNonReferenceVariable(mapValue));
			}
		}
		{
			auto mapPtr = arguments[1].getMapPointer();
			if (mapPtr != nullptr) {
				for (const auto& [mapKey, mapValue]: *mapPtr) returnValue.setMapEntry(mapKey, MinitScript::Variable::createNonReferenceVariable(mapValue));
			}
		}
	} else
	// set
	if (arguments[0].getType() == MinitScript::TYPE_SET &&
		arguments[1].getType() == MinitScript::TYPE_SET) {
		returnValue.setType(MinitScript::TYPE_SET);
		{
			auto setPtr = arguments[0].getSetPointer();
			if (setPtr != nullptr) {
				for (auto setKey: *setPtr) returnValue.insertSetKey(setKey);
			}
		}
		{
			auto setPtr = arguments[1].getSetPointer();
			if (setPtr != nullptr) {
				for (auto setKey: *setPtr) returnValue.insertSetKey(setKey);
			}
		}
	} else
	// float
	if (MinitScript::hasTypeForOperatorArguments(arguments, MinitScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		auto isAFloat = MinitScript::getFloatValue(arguments, 0, a, false);
		auto isBFloat = MinitScript::getFloatValue(arguments, 1, b, false);
		if (isAFloat == true &&
			isBFloat == true) {
			returnValue.setValue(a + b);
			return;
		} else  {
			minitScript->complainOperator(
				"add",
				MinitScript::decodeOperator(arguments, 2, "add"),
				subStatement,
				"Can not add " + arguments[0].getValueAsString() + " to " + arguments[1].getValueAsString()
			);
			minitScript->startErrorScript();
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		auto isAInteger = MinitScript::getIntegerValue(arguments, 0, a, false) == true;
		auto isBInteger = MinitScript::getIntegerValue(arguments, 1, b, false) == true;
		if (isAInteger == true &&
			isBInteger == true) {
			returnValue.setValue(a + b);
			return;
		} else  {
			minitScript->complainOperator(
				"add",
				MinitScript::decodeOperator(arguments, 2, "add"),
				subStatement,
				"Can not add " + arguments[0].getValueAsString() + " to " + arguments[1].getValueAsString()
			);
			minitScript->startErrorScript();
			return;
		}
	}
}

void MathMethods::sub(const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) {
	if (arguments.size() != 2 && arguments.size() != 3) {
		minitScript->complain(MinitScript::decodeOperator(arguments, 2, "sub"), subStatement); minitScript->startErrorScript();
		return;
	}
	// custom data types
	for (const auto dataType: dataTypes) {
		if (dataType->sub(minitScript, arguments, returnValue, subStatement) == true) return;
	}
	// float
	if (MinitScript::hasTypeForOperatorArguments(arguments, MinitScript::TYPE_FLOAT) == true) {
		float a;
		float b;
		auto isAFloat = MinitScript::getFloatValue(arguments, 0, a, false);
		auto isBFloat = MinitScript::getFloatValue(arguments, 1, b, false);
		if (isAFloat == true &&
			isBFloat == true) {
			returnValue.setValue(a - b);
			return;
		} else  {
			minitScript->complainOperator(
				"sub",
				MinitScript::decodeOperator(arguments, 2, "sub"),
				subStatement,
				"Can not subtract " + arguments[0].getValueAsString() + " to " + arguments[1].getValueAsString()
			);
			minitScript->startErrorScript();
			return;
		}
	} else {
		// int
		int64_t a;
		int64_t b;
		auto isAInteger = MinitScript::getIntegerValue(arguments, 0, a, false) == true;
		auto isBInteger = MinitScript::getIntegerValue(arguments, 1, b, false) == true;
		if (isAInteger == true &&
			isBInteger == true) {
			returnValue.setValue(a - b);
			return;
		} else  {
			minitScript->complainOperator(
				"sub",
				MinitScript::decodeOperator(arguments, 2, "sub"),
				subStatement,
				"Can not subtract " + arguments[0].getValueAsString() + " to " + arguments[1].getValueAsString()
			);
			minitScript->startErrorScript();
			return;
		}
	}
}
