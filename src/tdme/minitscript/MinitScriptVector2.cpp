#include <span>
#include <string>

#include <minitscript/minitscript/MinitScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector2.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/minitscript/MinitScriptVector2.h>

using std::span;
using std::string;

using minitscript::minitscript::MinitScript;

using tdme::math::Vector2;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::minitscript::MinitScriptVector2;

const string MinitScriptVector2::TYPE_NAME = "Vector2";

MinitScript::VariableType MinitScriptVector2::TYPE_VECTOR2 = MinitScript::TYPE_NULL;

void MinitScriptVector2::initialize() {
	TYPE_VECTOR2 = MinitScript::getDataTypeByClassName("Vector2")->getType();
}

void MinitScriptVector2::registerConstants(MinitScript* minitScript) const {
}

void MinitScriptVector2::registerMethods(MinitScript* minitScript) const {
	{
		//
		class MethodVec2: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec2(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR2
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float xValue;
				float yValue;
				if (MinitScript::getFloatValue(arguments, 0, xValue, false) == true &&
					MinitScript::getFloatValue(arguments, 1, yValue, false) == true) {
					auto result = Vector2(xValue, yValue);
					returnValue.setType(TYPE_VECTOR2);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec2(minitScript));
	}
	{
		//
		class MethodVec2ComputeLength: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec2ComputeLength(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vector2", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::computeLength";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector2 vec2;
				if (MinitScriptVector2::getVector2Value(arguments, 0, vec2, false) == true) {
					auto length = vec2.computeLength();
					returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec2ComputeLength(minitScript));
	}
	{
		//
		class MethodVec2ComputeLengthSquared: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec2ComputeLengthSquared(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vector2", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::computeLengthSquared";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector2 vec2;
				if (MinitScriptVector2::getVector2Value(arguments, 0, vec2, false) == true) {
					returnValue.setValue(vec2.computeLengthSquared());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec2ComputeLengthSquared(minitScript));
	}
	{
		//
		class MethodVec2ComputeDotProduct: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec2ComputeDotProduct(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR2, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::computeDotProduct";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector2 a;
				Vector2 b;
				if (MinitScriptVector2::getVector2Value(arguments, 0, a, false) == true &&
					MinitScriptVector2::getVector2Value(arguments, 1, b, false) == true) {
					returnValue.setValue(Vector2::computeDotProduct(a, b));
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec2ComputeDotProduct(minitScript));
	}
	{
		//
		class MethodVec2Normalize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec2Normalize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vector2", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR2
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::normalize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector2 vec2;
				if (MinitScriptVector2::getVector2Value(arguments, 0, vec2, false) == true) {
					auto length = vec2.computeLength();
					auto result = length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector2(0.0f, 0.0f):vec2.normalize();
					returnValue.setType(TYPE_VECTOR2);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec2Normalize(minitScript));
	}
	{
		//
		class MethodVec2GetX: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec2GetX(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vector2", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::getX";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector2 vec2;
				if (MinitScriptVector2::getVector2Value(arguments, 0, vec2, false) == true) {
					returnValue.setValue(vec2.getX());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec2GetX(minitScript));
	}
	{
		//
		class MethodVec2GetY: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec2GetY(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vector2", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::getY";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector2 vec2;
				if (MinitScriptVector2::getVector2Value(arguments, 0, vec2, false) == true) {
					returnValue.setValue(vec2.getY());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec2GetY(minitScript));
	}
}

void MinitScriptVector2::unsetVariableValue(MinitScript::Variable& variable) const {
	delete static_cast<Vector2*>(variable.getValuePtr());
}

void MinitScriptVector2::setVariableValue(MinitScript::Variable& variable) const {
	variable.setValuePtr(new Vector2());
}

void MinitScriptVector2::setVariableValue(MinitScript::Variable& variable, const void* value) const {
	*static_cast<Vector2*>(variable.getValuePtr()) = *static_cast<const Vector2*>(value);
}

void MinitScriptVector2::copyVariable(MinitScript::Variable& to, const MinitScript::Variable& from) const {
	to.setType(TYPE_VECTOR2);
	*static_cast<Vector2*>(to.getValuePtr()) = *static_cast<Vector2*>(from.getValuePtr());
}

bool MinitScriptVector2::mul(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	//
	if (MinitScript::hasType(arguments, TYPE_VECTOR2) == true) {
		float f;
		// a
		Vector2 a;
		if (arguments[0].getType() == TYPE_VECTOR2) {
			MinitScriptVector2::getVector2Value(arguments, 0, a, false);
		} else
		if (MinitScript::getFloatValue(arguments, 0, f, false) == true) {
			a = Vector2(f, f);
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "mul"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
		// b
		Vector2 b;
		if (arguments[1].getType() == TYPE_VECTOR2) {
			MinitScriptVector2::getVector2Value(arguments, 1, b, false);
		} else
		if (MinitScript::getFloatValue(arguments, 1, f, false) == true) {
			b = Vector2(f, f);
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "mul"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
		//
		auto result = a.clone().scale(b);
		returnValue.setType(TYPE_VECTOR2);
		returnValue.setValue(&result);
		//
		return true;
	}
	//
	return false;
}

bool MinitScriptVector2::div(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	//
	if (arguments[0].getType() == TYPE_VECTOR2) {
		Vector2 a;
		Vector2 b;
		float f;
		// a
		MinitScriptVector2::getVector2Value(arguments, 0, a, false);
		// b
		if (arguments[1].getType() == TYPE_VECTOR2 &&
			MinitScriptVector2::getVector2Value(arguments, 1, b, false) == true) {
			// nop
		} else
		if (MinitScript::getFloatValue(arguments, 1, f, false) == true) {
			b = Vector2(f, f);
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "div"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
		//
		auto result = a / b;
		returnValue.setType(TYPE_VECTOR2);
		returnValue.setValue(&result);
		//
		return true;
	}
	//
	return false;
}

bool MinitScriptVector2::add(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	//
	if (MinitScript::hasType(arguments, TYPE_VECTOR2) == true) {
		Vector2 a;
		Vector2 b;
		if (MinitScriptVector2::getVector2Value(arguments, 0, a, false) == true &&
			MinitScriptVector2::getVector2Value(arguments, 1, b, false) == true) {
			//
			auto result = a.clone().add(b);
			returnValue.setType(TYPE_VECTOR2);
			returnValue.setValue(&result);
			//
			return true;
		} else  {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "add"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

bool MinitScriptVector2::sub(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	//
	if (MinitScript::hasType(arguments, TYPE_VECTOR2) == true) {
		Vector2 a;
		Vector2 b;
		if (MinitScriptVector2::getVector2Value(arguments, 0, a, false) == true &&
			MinitScriptVector2::getVector2Value(arguments, 1, b, false) == true) {
			//
			auto result = a.clone().sub(b);
			returnValue.setType(TYPE_VECTOR2);
			returnValue.setValue(&result);
			//
			return true;
		} else  {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "sub"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

const string& MinitScriptVector2::getTypeAsString() const {
	return TYPE_NAME;
}

const string MinitScriptVector2::getValueAsString(const MinitScript::Variable& variable) const {
	//
	const auto& vector2 = *static_cast<Vector2*>(variable.getValuePtr());
	//
	return
		"Vector2(" +
		to_string(vector2.getX()) + ", " +
		to_string(vector2.getY()) + ")";
}

MinitScript::DataType::ScriptContext* MinitScriptVector2::createScriptContext() const {
	return nullptr;
}

void MinitScriptVector2::deleteScriptContext(ScriptContext* context) const {
}

void MinitScriptVector2::garbageCollection(ScriptContext* context) const {
}
