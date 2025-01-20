#include <span>
#include <string>

#include <minitscript/minitscript/MinitScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/minitscript/MinitScriptVector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>

using minitscript::minitscript::MinitScript;

using std::span;
using std::string;

using tdme::math::Vector3;
using tdme::minitscript::MinitScriptVector3;
using tdme::utilities::Console;
using tdme::utilities::Float;

const string MinitScriptVector3::TYPE_NAME = "Vector3";

MinitScript::VariableType MinitScriptVector3::TYPE_VECTOR3 = MinitScript::TYPE_NULL;

void MinitScriptVector3::initialize() {
	TYPE_VECTOR3 = MinitScript::getDataTypeByClassName("Vector3")->getType();
}

void MinitScriptVector3::registerConstants(MinitScript* minitScript) const {
}

void MinitScriptVector3::registerMethods(MinitScript* minitScript) const {
	{
		//
		class MethodVec3: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec3(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "z", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MinitScript::getFloatValue(arguments, 0, xValue, false) == true &&
					MinitScript::getFloatValue(arguments, 1, yValue, false) == true &&
					MinitScript::getFloatValue(arguments, 2, zValue, false) == true) {
					auto result = Vector3(xValue, yValue, zValue);
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec3(minitScript));
	}
	{
		//
		class MethodVec3ComputeLength: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec3ComputeLength(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::computeLength";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 vec3;
				if (MinitScriptVector3::getVector3Value(arguments, 0, vec3, false) == true) {
					auto length = vec3.computeLength();
					returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec3ComputeLength(minitScript));
	}
	{
		//
		class MethodVec3ComputeLengthSquared: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec3ComputeLengthSquared(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::computeLengthSquared";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 vec3;
				if (MinitScriptVector3::getVector3Value( arguments, 0, vec3, false) == true) {
					returnValue.setValue(vec3.computeLengthSquared());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec3ComputeLengthSquared(minitScript));
	}
	{
		//
		class MethodVec3ComputeDotProduct: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec3ComputeDotProduct(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::computeDotProduct";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 a;
				Vector3 b;
				if (MinitScriptVector3::getVector3Value( arguments, 0, a, false) == true &&
					MinitScriptVector3::getVector3Value( arguments, 1, b, false) == true) {
					returnValue.setValue(Vector3::computeDotProduct(a, b));
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec3ComputeDotProduct(minitScript));
	}
	{
		//
		class MethodVec3ComputeCrossProduct: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec3ComputeCrossProduct(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::computeCrossProduct";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 a;
				Vector3 b;
				if (MinitScriptVector3::getVector3Value( arguments, 0, a, false) == true &&
					MinitScriptVector3::getVector3Value( arguments, 1, b, false) == true) {
					auto result = Vector3::computeCrossProduct(a, b);
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec3ComputeCrossProduct(minitScript));
	}
	{
		//
		class MethodVec3Normalize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec3Normalize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::normalize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 vec3;
				if (MinitScriptVector3::getVector3Value( arguments, 0, vec3, false) == true) {
					auto length = vec3.computeLength();
					auto result = length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector3(0.0f, 0.0f, 0.0f):vec3.normalize();
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec3Normalize(minitScript));
	}
	{
		//
		class MethodVec3ComputeAngle: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec3ComputeAngle(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "n", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::computeAngle";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 a;
				Vector3 b;
				Vector3 n;
				if (MinitScriptVector3::getVector3Value( arguments, 0, a, false) == true &&
					MinitScriptVector3::getVector3Value( arguments, 1, b, false) == true &&
					MinitScriptVector3::getVector3Value( arguments, 2, n, false) == true) {
					returnValue.setValue(Vector3::computeAngle(a, b, n));
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec3ComputeAngle(minitScript));
	}
	{
		//
		class MethodVec3GetX: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec3GetX(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::getX";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 vec3;
				if (MinitScriptVector3::getVector3Value( arguments, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getX());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec3GetX(minitScript));
	}
	{
		//
		class MethodVec3GetY: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec3GetY(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::getY";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 vec3;
				if (MinitScriptVector3::getVector3Value( arguments, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getY());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec3GetY(minitScript));
	}
	{
		//
		class MethodVec3GetZ: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodVec3GetZ(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::getZ";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 vec3;
				if (MinitScriptVector3::getVector3Value( arguments, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getZ());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodVec3GetZ(minitScript));
	}
}

void MinitScriptVector3::unsetVariableValue(MinitScript::MinitScript::Variable& variable) const {
	delete static_cast<Vector3*>(variable.getValuePtr());
}

void MinitScriptVector3::setVariableValue(MinitScript::MinitScript::Variable& variable) const {
	variable.setValuePtr(new Vector3());
}

void MinitScriptVector3::setVariableValue(MinitScript::MinitScript::Variable& variable, const void* value) const {
	*static_cast<Vector3*>(variable.getValuePtr()) = *static_cast<const Vector3*>(value);
}

void MinitScriptVector3::copyVariable(MinitScript::MinitScript::Variable& to, const MinitScript::MinitScript::Variable& from) const {
	to.setType(TYPE_VECTOR3);
	*static_cast<Vector3*>(to.getValuePtr()) = *static_cast<Vector3*>(from.getValuePtr());
}

bool MinitScriptVector3::mul(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	// vector3
	if (MinitScript::hasType(arguments, TYPE_VECTOR3) == true) {
		float f;
		// a
		Vector3 a;
		if (arguments[0].getType() == TYPE_VECTOR3) {
			MinitScriptVector3::getVector3Value(arguments, 0, a, false);
		} else
		if (MinitScript::getFloatValue(arguments, 0, f, false) == true) {
			a = Vector3(f, f, f);
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "mul"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
		// b
		Vector3 b;
		if (arguments[1].getType() == TYPE_VECTOR3) {
			MinitScriptVector3::getVector3Value(arguments, 1, b, false);
		} else
		if (MinitScript::getFloatValue(arguments, 1, f, false) == true) {
			b = Vector3(f, f, f);
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "mul"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
		//
		auto result = a.clone().scale(b);
		returnValue.setType(TYPE_VECTOR3);
		returnValue.setValue(&result);
		//
		return true;
	}
	//
	return false;
}

bool MinitScriptVector3::div(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	// vector3
	if (arguments[0].getType() == TYPE_VECTOR3) {
		Vector3 a;
		Vector3 b;
		float f;
		// a
		MinitScriptVector3::getVector3Value(arguments, 0, a, false);
		// b
		if (arguments[1].getType() == TYPE_VECTOR3 &&
			MinitScriptVector3::getVector3Value(arguments, 1, b, false) == true) {
			// nop
		} else
		if (MinitScript::getFloatValue(arguments, 1, f, false) == true) {
			b = Vector3(f, f, f);
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "div"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
		//
		auto result = a / b;
		returnValue.setType(TYPE_VECTOR3);
		returnValue.setValue(&result);
		//
		return true;
	}
	//
	return false;
}

bool MinitScriptVector3::add(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	// vector3
	if (MinitScript::hasType(arguments, TYPE_VECTOR3) == true) {
		Vector3 a;
		Vector3 b;
		if (MinitScriptVector3::getVector3Value(arguments, 0, a, false) == true &&
			MinitScriptVector3::getVector3Value(arguments, 1, b, false) == true) {
			auto result = a.clone().add(b);
			returnValue.setType(TYPE_VECTOR3);
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

bool MinitScriptVector3::sub(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	// vector3
	if (MinitScript::hasType(arguments, TYPE_VECTOR3) == true) {
		Vector3 a;
		Vector3 b;
		if (MinitScriptVector3::getVector3Value(arguments, 0, a, false) == true &&
			MinitScriptVector3::getVector3Value(arguments, 1, b, false) == true) {
			auto result = a.clone().sub(b);
			returnValue.setType(TYPE_VECTOR3);
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

const string& MinitScriptVector3::getTypeAsString() const {
	return TYPE_NAME;
}

const string MinitScriptVector3::getValueAsString(const MinitScript::MinitScript::Variable& variable) const {
	//
	const auto& vector3 = *static_cast<Vector3*>(variable.getValuePtr());
	//
	return
		"Vector3(" +
		to_string(vector3.getX()) + ", " +
		to_string(vector3.getY()) + ", " +
		to_string(vector3.getZ()) + ")";

}

MinitScript::DataType::ScriptContext* MinitScriptVector3::createScriptContext() const {
	return nullptr;
}

void MinitScriptVector3::deleteScriptContext(ScriptContext* context) const {
}

void MinitScriptVector3::garbageCollection(ScriptContext* context) const {
}
