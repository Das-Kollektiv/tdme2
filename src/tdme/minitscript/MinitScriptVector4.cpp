#include <span>
#include <string>

#include <minitscript/minitscript/MinitScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/minitscript/MinitScriptVector4.h>

using std::span;
using std::string;

using minitscript::minitscript::MinitScript;

using tdme::math::Vector4;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::minitscript::MinitScriptVector4;

const string MinitScriptVector4::TYPE_NAME = "Vector4";

MinitScript::VariableType MinitScriptVector4::TYPE_VECTOR4 = MinitScript::TYPE_NULL;

void MinitScriptVector4::initialize() {
	TYPE_VECTOR4 = MinitScript::getDataTypeByClassName("Vector4")->getType();
}

void MinitScriptVector4::registerConstants(MinitScript* minitScript) const {
}

void MinitScriptVector4::registerMethods(MinitScript* minitScript) const {
	{
		//
		class MethodVec4: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec4(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "z", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "w", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR4
				),
				minitScript(minitScript) {
				//
			}

			const string getMethodName() override {
				return "Vector4";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MinitScript::getFloatValue(arguments, 0, xValue, false) == true &&
					MinitScript::getFloatValue(arguments, 1, yValue, false) == true &&
					MinitScript::getFloatValue(arguments, 2, zValue, false) == true &&
					MinitScript::getFloatValue(arguments, 3, wValue, false) == true) {
					auto result = Vector4(xValue, yValue, zValue, wValue);
					returnValue.setType(TYPE_VECTOR4);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec4(minitScript));
	}
	{
		//
		class MethodVec4ComputeLength: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec4ComputeLength(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::computeLength";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector4 vec4;
				if (MinitScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					auto length = vec4.computeLength();
					returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec4ComputeLength(minitScript));
	}
	{
		//
		class MethodVec4ComputeLengthSquared: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec4ComputeLengthSquared(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::computeLengthSquared";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector4 vec4;
				if (MinitScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					returnValue.setValue(vec4.computeLengthSquared());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec4ComputeLengthSquared(minitScript));
	}
	{
		//
		class MethodVec4ComputeDotProduct: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec4ComputeDotProduct(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR4, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::computeDotProduct";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector4 a;
				Vector4 b;
				if (MinitScriptVector4::getVector4Value(arguments, 0, a, false) == true &&
					MinitScriptVector4::getVector4Value(arguments, 1, b, false) == true) {
					returnValue.setValue(Vector4::computeDotProduct(a, b));
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec4ComputeDotProduct(minitScript));
	}
	{
		//
		class MethodVec4Normalize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec4Normalize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR4
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::normalize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector4 vec4;
				if (MinitScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					auto length = vec4.computeLength();
					auto result = length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector4(0.0f, 0.0f, 0.0f, 0.0f):vec4.normalize();
					returnValue.setType(TYPE_VECTOR4);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec4Normalize(minitScript));
	}
	{
		//
		class MethodVec4GetX: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec4GetX(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::getX";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector4 vec4;
				if (MinitScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getX());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec4GetX(minitScript));
	}
	{
		//
		class MethodVec4GetY: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec4GetY(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::getY";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector4 vec4;
				if (MinitScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getY());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec4GetY(minitScript));
	}
	{
		//
		class MethodVec4GetZ: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec4GetZ(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::getZ";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector4 vec4;
				if (MinitScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getZ());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec4GetZ(minitScript));
	}
	{
		//
		class MethodVec4GetW: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec4GetW(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::getW";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector4 vec4;
				if (MinitScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getW());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec4GetW(minitScript));
	}
}

void MinitScriptVector4::unsetVariableValue(MinitScript::Variable& variable) const {
	delete static_cast<Vector4*>(variable.getValuePtr());
}

void MinitScriptVector4::setVariableValue(MinitScript::Variable& variable) const {
	variable.setValuePtr(new Vector4());
}

void MinitScriptVector4::setVariableValue(MinitScript::Variable& variable, const void* value) const {
	*static_cast<Vector4*>(variable.getValuePtr()) = *static_cast<const Vector4*>(value);
}

void MinitScriptVector4::copyVariable(MinitScript::Variable& to, const MinitScript::Variable& from) const {
	to.setType(static_cast<MinitScript::VariableType>(getType()));
	*static_cast<Vector4*>(to.getValuePtr()) = *static_cast<Vector4*>(from.getValuePtr());
}

bool MinitScriptVector4::mul(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	//
	if (MinitScript::hasType(arguments, TYPE_VECTOR4) == true) {
		float f;
		// a
		Vector4 a;
		if (arguments[0].getType() == TYPE_VECTOR4) {
			MinitScriptVector4::getVector4Value(arguments, 0, a, false);
		} else
		if (MinitScript::getFloatValue(arguments, 0, f, false) == true) {
			a = Vector4(f, f, f, f);
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "mul"), subStatement); minitScript->startErrorScript();
			minitScript->startErrorScript();
			//
			return false;
		}
		// b
		Vector4 b;
		if (arguments[1].getType() == TYPE_VECTOR4) {
			MinitScriptVector4::getVector4Value(arguments, 1, b, false);
		} else
		if (MinitScript::getFloatValue(arguments, 1, f, false) == true) {
			b = Vector4(f, f, f, f);
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "mul"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
		//
		auto result = a.clone().scale(b);
		returnValue.setType(TYPE_VECTOR4);
		returnValue.setValue(&result);
		//
		return true;
	}
	//
	return false;
}

bool MinitScriptVector4::div(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	//
	if (arguments[0].getType() == TYPE_VECTOR4) {
		Vector4 a;
		Vector4 b;
		float f;
		// a
		MinitScriptVector4::getVector4Value(arguments, 0, a, false);
		// b
		if (arguments[1].getType() == TYPE_VECTOR4 &&
			MinitScriptVector4::getVector4Value(arguments, 1, b, false) == true) {
			// nop
		} else
		if (MinitScript::getFloatValue(arguments, 1, f, false) == true) {
			b = Vector4(f, f, f, f);
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "div"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
		//
		auto result = a / b;
		returnValue.setType(TYPE_VECTOR4);
		returnValue.setValue(&result);
		//
		return true;

	}
	//
	return false;
}

bool MinitScriptVector4::add(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	// vector4
	if (MinitScript::hasType(arguments, TYPE_VECTOR4) == true) {
		Vector4 a;
		Vector4 b;
		if (MinitScriptVector4::getVector4Value(arguments, 0, a, false) == true &&
			MinitScriptVector4::getVector4Value(arguments, 1, b, false) == true) {
			//
			auto result = a.clone().add(b);
			returnValue.setType(TYPE_VECTOR4);
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

bool MinitScriptVector4::sub(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	// vector4
	if (MinitScript::hasType(arguments, TYPE_VECTOR4) == true) {
		Vector4 a;
		Vector4 b;
		if (MinitScriptVector4::getVector4Value(arguments, 0, a, false) == true &&
			MinitScriptVector4::getVector4Value(arguments, 1, b, false) == true) {
			//
			auto result = a.clone().sub(b);
			returnValue.setType(TYPE_VECTOR4);
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

const string& MinitScriptVector4::getTypeAsString() const {
	return TYPE_NAME;
}

const string MinitScriptVector4::getValueAsString(const MinitScript::Variable& variable) const {
	//
	const auto& vector4 = *static_cast<Vector4*>(variable.getValuePtr());
	//
	return
		"Vector4(" +
		to_string(vector4.getX()) + ", " +
		to_string(vector4.getY()) + ", " +
		to_string(vector4.getZ()) + ", " +
		to_string(vector4.getW()) + ")";

}

MinitScript::DataType::ScriptContext* MinitScriptVector4::createScriptContext() const {
	return nullptr;
}

void MinitScriptVector4::deleteScriptContext(ScriptContext* context) const {
}

void MinitScriptVector4::garbageCollection(ScriptContext* context) const {
}
