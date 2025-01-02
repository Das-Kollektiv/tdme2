#include <span>
#include <string>

#include <minitscript/minitscript/MinitScript.h>

#include <tdme/minitscript/MinitScriptMatrix3x3.h>

#include <tdme/tdme.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/math/Vector2.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/minitscript/MinitScriptVector2.h>

using std::span;
using std::string;

using minitscript::minitscript::MinitScript;

using tdme::minitscript::MinitScriptMatrix3x3;

using tdme::math::Matrix3x3;
using tdme::math::Vector2;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::minitscript::MinitScriptVector2;

const string MinitScriptMatrix3x3::TYPE_NAME = "Matrix3x3";

MinitScript::VariableType MinitScriptMatrix3x3::TYPE_MATRIX3x3 = MinitScript::TYPE_NULL;
MinitScript::VariableType MinitScriptMatrix3x3::TYPE_VECTOR2 = MinitScript::TYPE_NULL;

void MinitScriptMatrix3x3::initialize() {
	TYPE_MATRIX3x3 = MinitScript::getDataTypeByClassName("Matrix3x3")->getType();
	TYPE_VECTOR2 = MinitScript::getDataTypeByClassName("Vector2")->getType();
}

void MinitScriptMatrix3x3::registerConstants(MinitScript* minitScript) const {
}

void MinitScriptMatrix3x3::registerMethods(MinitScript* minitScript) const {
	//
	{
		//
		class MethodMatrix3x3Identity: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix3x3Identity(MinitScript* minitScript):
				MinitScript::Method({}, TYPE_MATRIX3x3),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix3x3::identity";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				const auto result = Matrix3x3().identity();
				returnValue.setType(TYPE_MATRIX3x3);
				returnValue.setValue(&result);
			}
		};
		minitScript->registerMethod(new MethodMatrix3x3Identity(minitScript));
	}
	{
		//
		class MethodMatrix3x3Translate: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix3x3Translate(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX3x3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix3x3::translate";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector2 translation;
				if (MinitScriptVector2::getVector2Value(arguments, 0, translation, false) == true) {
					const auto result = Matrix3x3().identity().setTranslation(translation);
					returnValue.setType(TYPE_MATRIX3x3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodMatrix3x3Translate(minitScript));
	}
	{
		//
		class MethodMatrix3x3Rotate: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix3x3Rotate(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX3x3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix3x3::rotate";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float angle;
				if (MinitScript::getFloatValue(arguments, 0, angle, false) == true) {
					const auto result = Matrix3x3().identity().setAxes(angle);
					returnValue.setType(TYPE_MATRIX3x3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodMatrix3x3Rotate(minitScript));
	}
	{
		//
		class MethodMatrix3x3RotateAroundTextureCenter: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix3x3RotateAroundTextureCenter(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX3x3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix3x3::rotateAroundTextureCenter";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float angle;
				if (MinitScript::getFloatValue(arguments, 0, angle, false) == true) {
					const auto result = Matrix3x3::rotateAroundTextureCenter(angle);
					returnValue.setType(TYPE_MATRIX3x3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodMatrix3x3RotateAroundTextureCenter(minitScript));
	}
	{
		//
		class MethodMatrix3x3RotateAroundPoint: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix3x3RotateAroundPoint(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "point", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX3x3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix3x3::rotateAroundPoint";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector2 point;
				float angle;
				if (MinitScriptVector2::getVector2Value(arguments, 0, point, false) == true &&
					MinitScript::getFloatValue(arguments, 1, angle, false) == true) {
					const auto result = Matrix3x3().rotateAroundPoint(point, angle);
					returnValue.setType(TYPE_MATRIX3x3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodMatrix3x3RotateAroundPoint(minitScript));
	}
	{
		//
		class MethodMatrix3x3Scale: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMatrix3x3Scale(MinitScript* minitScript):
				MinitScript::Method({}, TYPE_MATRIX3x3),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Matrix3x3::scale";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector2 vec2Value;
				float floatValue;
				if (MinitScriptVector2::getVector2Value(arguments, 0, vec2Value, false) == true) {
					const auto result = Matrix3x3().identity().scale(vec2Value);
					returnValue.setType(TYPE_MATRIX3x3);
					returnValue.setValue(&result);
				} else
				if (MinitScript::getFloatValue(arguments, 0, floatValue, false) == true) {
					const auto result = Matrix3x3().identity().scale(floatValue);
					returnValue.setType(TYPE_MATRIX3x3);
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
		minitScript->registerMethod(new MethodMatrix3x3Scale(minitScript));
	}
}

void MinitScriptMatrix3x3::unsetVariableValue(MinitScript::Variable& variable) const {
	delete static_cast<Matrix3x3*>(variable.getValuePtr());
}

void MinitScriptMatrix3x3::setVariableValue(MinitScript::Variable& variable) const {
	variable.setValuePtr(new Matrix3x3());
}

void MinitScriptMatrix3x3::setVariableValue(MinitScript::Variable& variable, const void* value) const {
	*static_cast<Matrix3x3*>(variable.getValuePtr()) = *static_cast<const Matrix3x3*>(value);
}

void MinitScriptMatrix3x3::copyVariable(MinitScript::Variable& to, const MinitScript::Variable& from) const {
	to.setType(TYPE_MATRIX3x3);
	*static_cast<Matrix3x3*>(to.getValuePtr()) = *static_cast<Matrix3x3*>(from.getValuePtr());
}

bool MinitScriptMatrix3x3::mul(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	//
	if (MinitScript::hasType(arguments, TYPE_MATRIX3x3) == true) {
		// matrix3x3 * matrix
		if (arguments[0].getType() == TYPE_MATRIX3x3 &&
			arguments[1].getType() == TYPE_MATRIX3x3) {
			Matrix3x3 a;
			Matrix3x3 b;
			MinitScriptMatrix3x3::getMatrix3x3Value(arguments, 0, a, false);
			MinitScriptMatrix3x3::getMatrix3x3Value(arguments, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_MATRIX3x3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// matrix3x3 * vec2
		if (arguments[0].getType() == TYPE_MATRIX3x3 &&
			arguments[1].getType() == TYPE_VECTOR2) {
			Matrix3x3 a;
			Vector2 b;
			MinitScriptMatrix3x3::getMatrix3x3Value(arguments, 0, a, false);
			MinitScriptVector2::getVector2Value(arguments, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_VECTOR2);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// vec2 * matrix3x3
		if (arguments[0].getType() == TYPE_VECTOR2 &&
			arguments[1].getType() == TYPE_MATRIX3x3) {
			Vector2 a;
			Matrix3x3 b;
			MinitScriptVector2::getVector2Value(arguments, 0, a, false);
			MinitScriptMatrix3x3::getMatrix3x3Value(arguments, 1, b, false);
			//
			const auto result = b * a;
			returnValue.setType(TYPE_VECTOR2);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// matrix3x3 * float
		if (arguments[0].getType() == TYPE_MATRIX3x3 &&
			MinitScript::Variable::isExpectedType(arguments[1].getType(), MinitScript::TYPE_PSEUDO_NUMBER) == true) {
			Matrix3x3 a;
			float b;
			MinitScriptMatrix3x3::getMatrix3x3Value(arguments, 0, a, false);
			MinitScript::getFloatValue(arguments, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_MATRIX3x3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// float * matrix3x3
		if (MinitScript::Variable::isExpectedType(arguments[0].getType(), MinitScript::TYPE_PSEUDO_NUMBER) == true &&
			arguments[1].getType() == TYPE_MATRIX3x3) {
			float a;
			Matrix3x3 b;
			MinitScript::getFloatValue(arguments, 0, a, false);
			MinitScriptMatrix3x3::getMatrix3x3Value(arguments, 1, b, false);
			//
			const auto result = b * a;
			returnValue.setType(TYPE_MATRIX3x3);
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

bool MinitScriptMatrix3x3::div(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

bool MinitScriptMatrix3x3::add(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

bool MinitScriptMatrix3x3::sub(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

const string& MinitScriptMatrix3x3::getTypeAsString() const {
	return TYPE_NAME;
}

const string MinitScriptMatrix3x3::getValueAsString(const MinitScript::Variable& variable) const {
	const auto& matrix3x3 = *static_cast<Matrix3x3*>(variable.getValuePtr());
	return
		"Matrix3x3(" +
		to_string(matrix3x3[0]) + ", " +
		to_string(matrix3x3[1]) + ", " +
		to_string(matrix3x3[2]) + ", " +
		to_string(matrix3x3[3]) + ", " +
		to_string(matrix3x3[4]) + ", " +
		to_string(matrix3x3[5]) + ", " +
		to_string(matrix3x3[6]) + ", " +
		to_string(matrix3x3[7]) + ", " +
		to_string(matrix3x3[8]) + ")";

}

MinitScript::DataType::ScriptContext* MinitScriptMatrix3x3::createScriptContext() const {
	return nullptr;
}

void MinitScriptMatrix3x3::deleteScriptContext(ScriptContext* context) const {
}

void MinitScriptMatrix3x3::garbageCollection(ScriptContext* context) const {
}
