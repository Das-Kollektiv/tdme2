#include <span>
#include <string>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/utilities/MiniScriptMatrix3x3.h>

#include <tdme/tdme.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/math/Vector2.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScriptVector2.h>

using std::span;
using std::string;

using miniscript::miniscript::MiniScript;

using tdme::utilities::MiniScriptMatrix3x3;

using tdme::math::Matrix3x3;
using tdme::math::Vector2;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::utilities::MiniScriptVector2;

const string MiniScriptMatrix3x3::TYPE_NAME = "Matrix3x3";

void MiniScriptMatrix3x3::registerMethods(MiniScript* miniScript) const {
	const auto TYPE_MATRIX3x3 = static_cast<MiniScript::VariableType>(getType());
	const auto TYPE_VECTOR2 = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Vector2")->getType());
	//
	{
		//
		class MethodMatrix3x3Identity: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX3x3;
		public:
			MethodMatrix3x3Identity(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX3x3
			):
				MiniScript::Method({}, TYPE_MATRIX3x3),
				miniScript(miniScript), TYPE_MATRIX3x3(TYPE_MATRIX3x3) {}
			const string getMethodName() override {
				return "Matrix3x3::identity";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				const auto result = Matrix3x3().identity();
				returnValue.setType(TYPE_MATRIX3x3);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new MethodMatrix3x3Identity(miniScript, TYPE_MATRIX3x3));
	}
	{
		//
		class MethodMatrix3x3Translate: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX3x3;
			MiniScript::VariableType TYPE_VECTOR2;
		public:
			MethodMatrix3x3Translate(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX3x3,
				MiniScript::VariableType TYPE_VECTOR2
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX3x3
				),
				miniScript(miniScript), TYPE_MATRIX3x3(TYPE_MATRIX3x3), TYPE_VECTOR2(TYPE_VECTOR2) {}
			const string getMethodName() override {
				return "Matrix3x3::translate";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 translation;
				if (MiniScriptVector2::getVector2Value(TYPE_VECTOR2, arguments, 0, translation, false) == true) {
					const auto result = Matrix3x3().identity().setTranslation(translation);
					returnValue.setType(TYPE_MATRIX3x3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMatrix3x3Translate(miniScript, TYPE_MATRIX3x3, TYPE_VECTOR2));
	}
	{
		//
		class MethodMatrix3x3Rotate: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX3x3;
		public:
			MethodMatrix3x3Rotate(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX3x3
			):
				MiniScript::Method(
					{
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX3x3
				),
				miniScript(miniScript), TYPE_MATRIX3x3(TYPE_MATRIX3x3) {}
			const string getMethodName() override {
				return "Matrix3x3::rotate";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float angle;
				if (MiniScript::getFloatValue(arguments, 0, angle, false) == true) {
					const auto result = Matrix3x3().identity().setAxes(angle);
					returnValue.setType(TYPE_MATRIX3x3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMatrix3x3Rotate(miniScript, TYPE_MATRIX3x3));
	}
	{
		//
		class MethodMatrix3x3RotateAroundTextureCenter: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX3x3;
		public:
			MethodMatrix3x3RotateAroundTextureCenter(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX3x3
			):
				MiniScript::Method(
					{
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX3x3
				),
				miniScript(miniScript), TYPE_MATRIX3x3(TYPE_MATRIX3x3) {}
			const string getMethodName() override {
				return "Matrix3x3::rotateAroundTextureCenter";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float angle;
				if (MiniScript::getFloatValue(arguments, 0, angle, false) == true) {
					const auto result = Matrix3x3::rotateAroundTextureCenter(angle);
					returnValue.setType(TYPE_MATRIX3x3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMatrix3x3RotateAroundTextureCenter(miniScript, TYPE_MATRIX3x3));
	}
	{
		//
		class MethodMatrix3x3RotateAroundPoint: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX3x3;
			MiniScript::VariableType TYPE_VECTOR2;
		public:
			MethodMatrix3x3RotateAroundPoint(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX3x3,
				MiniScript::VariableType TYPE_VECTOR2
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "point", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX3x3
				),
				miniScript(miniScript), TYPE_MATRIX3x3(TYPE_MATRIX3x3), TYPE_VECTOR2(TYPE_VECTOR2) {}
			const string getMethodName() override {
				return "Matrix3x3::rotateAroundPoint";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 point;
				float angle;
				if (MiniScriptVector2::getVector2Value(TYPE_VECTOR2, arguments, 0, point, false) == true &&
					MiniScript::getFloatValue(arguments, 1, angle, false) == true) {
					const auto result = Matrix3x3().rotateAroundPoint(point, angle);
					returnValue.setType(TYPE_MATRIX3x3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMatrix3x3RotateAroundPoint(miniScript, TYPE_MATRIX3x3, TYPE_VECTOR2));
	}
	{
		//
		class MethodMatrix3x3Scale: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX3x3;
			MiniScript::VariableType TYPE_VECTOR2;
		public:
			MethodMatrix3x3Scale(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX3x3,
				MiniScript::VariableType TYPE_VECTOR2
			):
				MiniScript::Method({}, TYPE_MATRIX3x3),
				miniScript(miniScript), TYPE_MATRIX3x3(TYPE_MATRIX3x3), TYPE_VECTOR2(TYPE_VECTOR2) {}
			const string getMethodName() override {
				return "Matrix3x3::scale";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 vec2Value;
				float floatValue;
				if (MiniScriptVector2::getVector2Value(TYPE_VECTOR2, arguments, 0, vec2Value, false) == true) {
					const auto result = Matrix3x3().identity().scale(vec2Value);
					returnValue.setType(TYPE_MATRIX3x3);
					returnValue.setValue(&result);
				} else
				if (MiniScript::getFloatValue(arguments, 0, floatValue, false) == true) {
					const auto result = Matrix3x3().identity().scale(floatValue);
					returnValue.setType(TYPE_MATRIX3x3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}

		};
		miniScript->registerMethod(new MethodMatrix3x3Scale(miniScript, TYPE_MATRIX3x3, TYPE_VECTOR2));
	}
}

void MiniScriptMatrix3x3::unsetVariableValue(MiniScript::Variable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Matrix3x3*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptMatrix3x3::setVariableValue(MiniScript::Variable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Matrix3x3 matrix3x3Value;
	if (value != 0ll) {
		matrix3x3Value = *static_cast<const Matrix3x3*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Matrix3x3*>((void*)variable.getValuePtr()) = matrix3x3Value;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Matrix3x3(matrix3x3Value)));
}

void MiniScriptMatrix3x3::copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const {
	//
	Matrix3x3 matrix3x3Value;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		matrix3x3Value = *static_cast<Matrix3x3*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_MATRIX3x3 = static_cast<MiniScript::VariableType>(getType());
	to.setType(TYPE_MATRIX3x3);
	*static_cast<Matrix3x3*>((void*)to.getValuePtr()) = matrix3x3Value;
}

bool MiniScriptMatrix3x3::mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	const auto TYPE_MATRIX3x3 = static_cast<MiniScript::VariableType>(getType());
	const auto TYPE_VECTOR2 = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Vector2")->getType());
	//
	if (MiniScript::hasType(arguments, TYPE_MATRIX3x3) == true) {
		// matrix3x3 * matrix
		if (arguments[0].getType() == TYPE_MATRIX3x3 &&
			arguments[1].getType() == TYPE_MATRIX3x3) {
			Matrix3x3 a;
			Matrix3x3 b;
			MiniScriptMatrix3x3::getMatrix3x3Value(TYPE_MATRIX3x3, arguments, 0, a, false);
			MiniScriptMatrix3x3::getMatrix3x3Value(TYPE_MATRIX3x3, arguments, 1, b, false);
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
			MiniScriptMatrix3x3::getMatrix3x3Value(TYPE_MATRIX3x3, arguments, 0, a, false);
			MiniScriptVector2::getVector2Value(TYPE_VECTOR2, arguments, 1, b, false);
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
			MiniScriptVector2::getVector2Value(TYPE_VECTOR2, arguments, 0, a, false);
			MiniScriptMatrix3x3::getMatrix3x3Value(TYPE_MATRIX3x3, arguments, 1, b, false);
			//
			const auto result = b * a;
			returnValue.setType(TYPE_VECTOR2);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// matrix3x3 * float
		if (arguments[0].getType() == TYPE_MATRIX3x3 &&
			MiniScript::Variable::isExpectedType(arguments[1].getType(), MiniScript::TYPE_PSEUDO_NUMBER) == true) {
			Matrix3x3 a;
			float b;
			MiniScriptMatrix3x3::getMatrix3x3Value(TYPE_MATRIX3x3, arguments, 0, a, false);
			MiniScript::getFloatValue(arguments, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_MATRIX3x3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// float * matrix3x3
		if (MiniScript::Variable::isExpectedType(arguments[0].getType(), MiniScript::TYPE_PSEUDO_NUMBER) == true &&
			arguments[1].getType() == TYPE_MATRIX3x3) {
			float a;
			Matrix3x3 b;
			MiniScript::getFloatValue(arguments, 0, a, false);
			MiniScriptMatrix3x3::getMatrix3x3Value(TYPE_MATRIX3x3, arguments, 1, b, false);
			//
			const auto result = b * a;
			returnValue.setType(TYPE_MATRIX3x3);
			returnValue.setValue(&result);
			//
			return true;
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
			miniScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

bool MiniScriptMatrix3x3::div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

bool MiniScriptMatrix3x3::add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

bool MiniScriptMatrix3x3::sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

const string& MiniScriptMatrix3x3::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptMatrix3x3::getValueAsString(const MiniScript::Variable& variable) const {
	//
	Matrix3x3 matrix3x3Value;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		matrix3x3Value = *static_cast<Matrix3x3*>((void*)variable.getValuePtr());
	}
	return
		"Matrix3x3(" +
		to_string(matrix3x3Value[0]) + ", " +
		to_string(matrix3x3Value[1]) + ", " +
		to_string(matrix3x3Value[2]) + ", " +
		to_string(matrix3x3Value[3]) + ", " +
		to_string(matrix3x3Value[4]) + ", " +
		to_string(matrix3x3Value[5]) + ", " +
		to_string(matrix3x3Value[6]) + ", " +
		to_string(matrix3x3Value[7]) + ", " +
		to_string(matrix3x3Value[8]) + ")";

}

