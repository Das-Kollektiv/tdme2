#include <span>
#include <string>

#include <minitscript/minitscript/MinitScript.h>

#include <tdme/tdme.h>
#include <tdme/minitscript/MinitScriptMatrix4x4.h>

#include <tdme/math/Matrix4x4.h>
#include <tdme/minitscript/MinitScriptVector3.h>
#include <tdme/minitscript/MinitScriptVector4.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>

using std::span;
using std::string;

using minitscript::minitscript::MinitScript;

using tdme::minitscript::MinitScriptMatrix4x4;

using tdme::math::Matrix4x4;
using tdme::minitscript::MinitScriptVector3;
using tdme::minitscript::MinitScriptVector4;
using tdme::utilities::Console;
using tdme::utilities::Float;

const string MinitScriptMatrix4x4::TYPE_NAME = "Matrix4x4";

MinitScript::VariableType MinitScriptMatrix4x4::TYPE_MATRIX4x4 = MinitScript::TYPE_NULL;
MinitScript::VariableType MinitScriptMatrix4x4::TYPE_VECTOR3 = MinitScript::TYPE_NULL;
MinitScript::VariableType MinitScriptMatrix4x4::TYPE_VECTOR4 = MinitScript::TYPE_NULL;

void MinitScriptMatrix4x4::initialize() {
	TYPE_MATRIX4x4 = MinitScript::getDataTypeByClassName("Matrix4x4")->getType();
	TYPE_VECTOR3 = MinitScript::getDataTypeByClassName("Vector3")->getType();
	TYPE_VECTOR4 = MinitScript::getDataTypeByClassName("Vector4")->getType();
}

void MinitScriptMatrix4x4::registerConstants(MinitScript* minitScript) const {
}

void MinitScriptMatrix4x4::registerMethods(MinitScript* minitScript) const {
	//
	{
		//
		class MethodMatrix4x4Identity: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix4x4Identity(MinitScript* minitScript):
				MinitScript::Method({}, TYPE_MATRIX4x4),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix4x4::identity";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				const auto result = Matrix4x4().identity();
				returnValue.setType(TYPE_MATRIX4x4);
				returnValue.setValue(&result);
			}
		};
		minitScript->registerMethod(new MethodMatrix4x4Identity(minitScript));
	}
	{
		//
		class MethodMatrix4x4Translate: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix4x4Translate(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix4x4::translate";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 translation;
				if (MinitScriptVector3::getVector3Value(arguments, 0, translation, false) == true) {
					const auto result = Matrix4x4().identity().setTranslation(translation);
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodMatrix4x4Translate(minitScript));
	}
	{
		//
		class MethodMatrix4x4Rotate: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix4x4Rotate(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix4x4::rotate";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 axis;
				float angle;
				if (MinitScriptVector3::getVector3Value(arguments, 0, axis, false) == true &&
					MinitScript::getFloatValue(arguments, 1, angle, false) == true) {
					const auto result = Matrix4x4().identity().setAxes(axis, angle);
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodMatrix4x4Rotate(minitScript));
	}
	{
		//
		class MethodMatrix4x4Scale: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix4x4Scale(MinitScript* minitScript):
				MinitScript::Method({}, TYPE_MATRIX4x4),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix4x4::scale";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 vec3Value;
				float floatValue;
				if (MinitScriptVector3::getVector3Value(arguments, 0, vec3Value, false) == true) {
					const auto result = Matrix4x4().identity().scale(vec3Value);
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else
				if (MinitScript::getFloatValue(arguments, 0, floatValue, false) == true) {
					const auto result = Matrix4x4().identity().scale(floatValue);
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}

		};
		minitScript->registerMethod(new MethodMatrix4x4Scale(minitScript));
	}
	{
		//
		class MethodMatrix4x4Invert: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix4x4Invert(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_MATRIX4x4, .name = "matrix4x4", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix4x4::invert";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Matrix4x4 mat4;
				if (MinitScriptMatrix4x4::getMatrix4x4Value(arguments, 0, mat4, false) == true) {
					const auto result = mat4.invert();
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodMatrix4x4Invert(minitScript));
	}
	{
		//
		class MethodMatrix4x4EulerAngles: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix4x4EulerAngles(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_MATRIX4x4, .name = "matrix4x4", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix4x4::computeEulerAngles";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Matrix4x4 mat4;
				if (MinitScriptMatrix4x4::getMatrix4x4Value(arguments, 0, mat4, false) == true) {
					const auto result = mat4.computeEulerAngles();
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodMatrix4x4EulerAngles(minitScript));
	}
}

void MinitScriptMatrix4x4::unsetVariableValue(MinitScript::Variable& variable) const {
	delete static_cast<Matrix4x4*>(variable.getValuePtr());
}

void MinitScriptMatrix4x4::setVariableValue(MinitScript::Variable& variable) const {
	variable.setValuePtr(new Matrix4x4());
}

void MinitScriptMatrix4x4::setVariableValue(MinitScript::Variable& variable, const void* value) const {
	*static_cast<Matrix4x4*>(variable.getValuePtr()) = *static_cast<const Matrix4x4*>(value);
}

void MinitScriptMatrix4x4::copyVariable(MinitScript::Variable& to, const MinitScript::Variable& from) const {
	to.setType(TYPE_MATRIX4x4);
	*static_cast<Matrix4x4*>(to.getValuePtr()) = *static_cast<Matrix4x4*>(from.getValuePtr());
}

bool MinitScriptMatrix4x4::mul(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	//
	if (MinitScript::hasType(arguments, TYPE_MATRIX4x4) == true) {
		// matrix4x4 * matrix
		if (arguments[0].getType() == TYPE_MATRIX4x4 &&
			arguments[1].getType() == TYPE_MATRIX4x4) {
			Matrix4x4 a;
			Matrix4x4 b;
			MinitScriptMatrix4x4::getMatrix4x4Value(arguments, 0, a, false);
			MinitScriptMatrix4x4::getMatrix4x4Value(arguments, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_MATRIX4x4);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// matrix4x4 * vec4
		if (arguments[0].getType() == TYPE_MATRIX4x4 &&
			arguments[1].getType() == TYPE_VECTOR4) {
			Matrix4x4 a;
			Vector4 b;
			MinitScriptMatrix4x4::getMatrix4x4Value(arguments, 0, a, false);
			MinitScriptVector4::getVector4Value(arguments, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_VECTOR4);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// vec4 * matrix4x4
		if (arguments[0].getType() == TYPE_VECTOR4 &&
			arguments[1].getType() == TYPE_MATRIX4x4) {
			Vector4 a;
			Matrix4x4 b;
			MinitScriptVector4::getVector4Value(arguments, 0, a, false);
			MinitScriptMatrix4x4::getMatrix4x4Value(arguments, 1, b, false);
			//
			const auto result = b * a;
			returnValue.setType(TYPE_VECTOR4);
			returnValue.setValue(&result);
			//
			return true;

		} else
		// matrix4x4 * vec3
		if (arguments[0].getType() == TYPE_MATRIX4x4 &&
			arguments[1].getType() == TYPE_VECTOR3) {
			Matrix4x4 a;
			Vector3 b;
			MinitScriptMatrix4x4::getMatrix4x4Value(arguments, 0, a, false);
			MinitScriptVector3::getVector3Value(arguments, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// vec3 * matrix4x4
		if (arguments[0].getType() == TYPE_VECTOR3 &&
			arguments[1].getType() == TYPE_MATRIX4x4) {
			Vector3 a;
			Matrix4x4 b;
			MinitScriptVector3::getVector3Value(arguments, 0, a, false);
			MinitScriptMatrix4x4::getMatrix4x4Value(arguments, 1, b, false);
			//
			const auto result = b * a;
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// matrix4x4 * float
		if (arguments[0].getType() == TYPE_MATRIX4x4 &&
			MinitScript::Variable::isExpectedType(arguments[1].getType(), MinitScript::TYPE_PSEUDO_NUMBER) == true) {
			Matrix4x4 a;
			float b;
			MinitScriptMatrix4x4::getMatrix4x4Value(arguments, 0, a, false);
			MinitScript::getFloatValue(arguments, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_MATRIX4x4);
			returnValue.setValue(&result);
			//
			return true;

		} else
		// float * matrix4x4
		if (MinitScript::Variable::isExpectedType(arguments[0].getType(), MinitScript::TYPE_PSEUDO_NUMBER) == true &&
			arguments[1].getType() == TYPE_MATRIX4x4) {
			float a;
			Matrix4x4 b;
			MinitScript::getFloatValue(arguments, 0, a, false);
			MinitScriptMatrix4x4::getMatrix4x4Value(arguments, 1, b, false);
			//
			const auto result = b * a;
			returnValue.setType(TYPE_MATRIX4x4);
			returnValue.setValue(&result);
			//
			return true;
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "mul"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

bool MinitScriptMatrix4x4::div(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

bool MinitScriptMatrix4x4::add(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

bool MinitScriptMatrix4x4::sub(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

const string& MinitScriptMatrix4x4::getTypeAsString() const {
	return TYPE_NAME;
}

const string MinitScriptMatrix4x4::getValueAsString(const MinitScript::Variable& variable) const {
	//
	const auto& matrix4x4 = *static_cast<Matrix4x4*>(variable.getValuePtr());
	//
	return
		"Matrix4x4(" +
		to_string(matrix4x4[0]) + ", " +
		to_string(matrix4x4[1]) + ", " +
		to_string(matrix4x4[2]) + ", " +
		to_string(matrix4x4[3]) + ", " +
		to_string(matrix4x4[4]) + ", " +
		to_string(matrix4x4[5]) + ", " +
		to_string(matrix4x4[6]) + ", " +
		to_string(matrix4x4[7]) + ", " +
		to_string(matrix4x4[8]) + ", " +
		to_string(matrix4x4[9]) + ", " +
		to_string(matrix4x4[10]) + ", " +
		to_string(matrix4x4[11]) + ", " +
		to_string(matrix4x4[12]) + ", " +
		to_string(matrix4x4[13]) + ", " +
		to_string(matrix4x4[14]) + ", " +
		to_string(matrix4x4[15]) + ")";
}

MinitScript::DataType::ScriptContext* MinitScriptMatrix4x4::createScriptContext() const {
	return nullptr;
}

void MinitScriptMatrix4x4::deleteScriptContext(ScriptContext* context) const {
}

void MinitScriptMatrix4x4::garbageCollection(ScriptContext* context) const {
}
