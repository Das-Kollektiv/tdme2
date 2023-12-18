#include <span>
#include <string>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/utilities/MiniScriptMatrix4x4.h>

#include <tdme/tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScriptVector3.h>
#include <tdme/utilities/MiniScriptVector4.h>

using std::span;
using std::string;

using miniscript::miniscript::MiniScript;

using tdme::utilities::MiniScriptMatrix4x4;

using tdme::math::Matrix4x4;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::utilities::MiniScriptVector3;
using tdme::utilities::MiniScriptVector4;

const string MiniScriptMatrix4x4::TYPE_NAME = "Matrix4x4";

void MiniScriptMatrix4x4::registerMethods(MiniScript* miniScript) const {
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::VariableType>(getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Vector3")->getType());
	//
	{
		//
		class MethodMatrix4x4Identity: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX4x4;
		public:
			MethodMatrix4x4Identity(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX4x4
			):
				MiniScript::Method({}, TYPE_MATRIX4x4),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4) {}
			const string getMethodName() override {
				return "Matrix4x4::identity";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				const auto result = Matrix4x4().identity();
				returnValue.setType(TYPE_MATRIX4x4);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new MethodMatrix4x4Identity(miniScript, TYPE_MATRIX4x4));
	}
	{
		//
		class MethodMatrix4x4Translate: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX4x4;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodMatrix4x4Translate(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX4x4,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Matrix4x4::translate";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 translation;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 0, translation, false) == true) {
					const auto result = Matrix4x4().identity().setTranslation(translation);
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMatrix4x4Translate(miniScript, TYPE_MATRIX4x4, TYPE_VECTOR3));
	}
	{
		//
		class MethodMatrix4x4Rotate: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX4x4;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodMatrix4x4Rotate(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX4x4,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Matrix4x4::rotate";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 axis;
				float angle;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 0, axis, false) == true &&
					MiniScript::getFloatValue(arguments, 1, angle, false) == true) {
					const auto result = Matrix4x4().identity().setAxes(axis, angle);
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMatrix4x4Rotate(miniScript, TYPE_MATRIX4x4, TYPE_VECTOR3));
	}
	{
		//
		class MethodMatrix4x4Scale: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX4x4;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodMatrix4x4Scale(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX4x4,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method({}, TYPE_MATRIX4x4),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Matrix4x4::scale";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 vec3Value;
				float floatValue;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 0, vec3Value, false) == true) {
					const auto result = Matrix4x4().identity().scale(vec3Value);
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else
				if (MiniScript::getFloatValue(arguments, 0, floatValue, false) == true) {
					const auto result = Matrix4x4().identity().scale(floatValue);
					returnValue.setType(TYPE_MATRIX4x4);
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
		miniScript->registerMethod(new MethodMatrix4x4Scale(miniScript, TYPE_MATRIX4x4, TYPE_VECTOR3));
	}
	{
		//
		class MethodMatrix4x4Invert: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX4x4;
		public:
			MethodMatrix4x4Invert(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX4x4
			):
				MiniScript::Method(
					{
						{ .type = TYPE_MATRIX4x4, .name = "matrix4x4", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4) {}
			const string getMethodName() override {
				return "Matrix4x4::invert";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Matrix4x4 mat4;
				if (MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, arguments, 0, mat4, false) == true) {
					const auto result = mat4.invert();
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMatrix4x4Invert(miniScript, TYPE_MATRIX4x4));
	}
	{
		//
		class MethodMatrix4x4EulerAngles: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_MATRIX4x4;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodMatrix4x4EulerAngles(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_MATRIX4x4,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_MATRIX4x4, .name = "matrix4x4", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Matrix4x4::computeEulerAngles";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Matrix4x4 mat4;
				if (MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, arguments, 0, mat4, false) == true) {
					const auto result = mat4.computeEulerAngles();
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMatrix4x4EulerAngles(miniScript, TYPE_MATRIX4x4, TYPE_VECTOR3));
	}
}

void MiniScriptMatrix4x4::unsetVariableValue(MiniScript::Variable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Matrix4x4*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptMatrix4x4::setVariableValue(MiniScript::Variable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Matrix4x4 matrix4x4Value;
	if (value != 0ll) {
		matrix4x4Value = *static_cast<const Matrix4x4*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Matrix4x4*>((void*)variable.getValuePtr()) = matrix4x4Value;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Matrix4x4(matrix4x4Value)));
}

void MiniScriptMatrix4x4::copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const {
	//
	Matrix4x4 matrix4x4Value;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		matrix4x4Value = *static_cast<Matrix4x4*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::VariableType>(getType());
	to.setType(TYPE_MATRIX4x4);
	*static_cast<Matrix4x4*>((void*)to.getValuePtr()) = matrix4x4Value;
}

bool MiniScriptMatrix4x4::mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::VariableType>(getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Vector3")->getType());
	const auto TYPE_VECTOR4 = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Vector4")->getType());
	//
	if (MiniScript::hasType(arguments, TYPE_MATRIX4x4) == true) {
		// matrix4x4 * matrix
		if (arguments[0].getType() == TYPE_MATRIX4x4 &&
			arguments[1].getType() == TYPE_MATRIX4x4) {
			Matrix4x4 a;
			Matrix4x4 b;
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, arguments, 0, a, false);
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, arguments, 1, b, false);
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
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, arguments, 0, a, false);
			MiniScriptVector4::getVector4Value(TYPE_VECTOR4, arguments, 1, b, false);
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
			MiniScriptVector4::getVector4Value(TYPE_VECTOR4, arguments, 0, a, false);
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, arguments, 1, b, false);
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
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, arguments, 0, a, false);
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 1, b, false);
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
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 0, a, false);
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, arguments, 1, b, false);
			//
			const auto result = b * a;
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// matrix4x4 * float
		if (arguments[0].getType() == TYPE_MATRIX4x4 &&
			MiniScript::Variable::isExpectedType(arguments[1].getType(), MiniScript::TYPE_PSEUDO_NUMBER) == true) {
			Matrix4x4 a;
			float b;
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, arguments, 0, a, false);
			MiniScript::getFloatValue(arguments, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_MATRIX4x4);
			returnValue.setValue(&result);
			//
			return true;

		} else
		// float * matrix4x4
		if (MiniScript::Variable::isExpectedType(arguments[0].getType(), MiniScript::TYPE_PSEUDO_NUMBER) == true &&
			arguments[1].getType() == TYPE_MATRIX4x4) {
			float a;
			Matrix4x4 b;
			MiniScript::getFloatValue(arguments, 0, a, false);
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, arguments, 1, b, false);
			//
			const auto result = b * a;
			returnValue.setType(TYPE_MATRIX4x4);
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

bool MiniScriptMatrix4x4::div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

bool MiniScriptMatrix4x4::add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

bool MiniScriptMatrix4x4::sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

const string& MiniScriptMatrix4x4::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptMatrix4x4::getValueAsString(const MiniScript::Variable& variable) const {
	//
	Matrix4x4 matrix4x4Value;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		matrix4x4Value = *static_cast<Matrix4x4*>((void*)variable.getValuePtr());
	}
	return
		"Matrix4x4(" +
		to_string(matrix4x4Value[0]) + ", " +
		to_string(matrix4x4Value[1]) + ", " +
		to_string(matrix4x4Value[2]) + ", " +
		to_string(matrix4x4Value[3]) + ", " +
		to_string(matrix4x4Value[4]) + ", " +
		to_string(matrix4x4Value[5]) + ", " +
		to_string(matrix4x4Value[6]) + ", " +
		to_string(matrix4x4Value[7]) + ", " +
		to_string(matrix4x4Value[8]) + ", " +
		to_string(matrix4x4Value[9]) + ", " +
		to_string(matrix4x4Value[10]) + ", " +
		to_string(matrix4x4Value[11]) + ", " +
		to_string(matrix4x4Value[12]) + ", " +
		to_string(matrix4x4Value[13]) + ", " +
		to_string(matrix4x4Value[14]) + ", " +
		to_string(matrix4x4Value[15]) + ")";

}

