#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMatrix4x4.h>
#include <tdme/utilities/MiniScriptVector3.h>
#include <tdme/utilities/MiniScriptVector4.h>

using std::span;
using std::string;

using tdme::math::Matrix4x4;
using tdme::utilities::Float;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMatrix4x4;
using tdme::utilities::MiniScriptVector3;
using tdme::utilities::MiniScriptVector4;

const string MiniScriptMatrix4x4::CLASS_NAME = "mat3";
const string MiniScriptMatrix4x4::TYPE_NAME = "Matrix4x4";

void MiniScriptMatrix4x4::registerMethods() const {
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::ScriptVariableType>(getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(miniScript->getDataTypeByClassName("vec3")->getType());
	//
	{
		//
		class ScriptMethodMatrix4x4Identity: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_MATRIX4x4;
		public:
			ScriptMethodMatrix4x4Identity(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_MATRIX4x4
			):
				MiniScript::ScriptMethod({}, TYPE_MATRIX4x4),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4) {}
			const string getMethodName() override {
				return "mat4.identity";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				const auto result = Matrix4x4().identity();
				returnValue.setType(TYPE_MATRIX4x4);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new ScriptMethodMatrix4x4Identity(miniScript, TYPE_MATRIX4x4));
	}
	{
		//
		class ScriptMethodMatrix4x4Translate: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_MATRIX4x4;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodMatrix4x4Translate(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_MATRIX4x4,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "mat4.translate";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 translation;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, translation, false) == true) {
					const auto result = Matrix4x4().identity().setTranslation(translation);
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMatrix4x4Translate(miniScript, TYPE_MATRIX4x4, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodMatrix4x4Rotate: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_MATRIX4x4;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodMatrix4x4Rotate(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_MATRIX4x4,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "mat4.rotate";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 axis;
				float angle;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					const auto result = Matrix4x4().identity().setAxes(axis, angle);
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMatrix4x4Rotate(miniScript, TYPE_MATRIX4x4, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodMatrix4x4Scale: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_MATRIX4x4;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodMatrix4x4Scale(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_MATRIX4x4,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod({}, TYPE_MATRIX4x4),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "mat4.scale";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 vec3Value;
				float floatValue;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, vec3Value, false) == true) {
					const auto result = Matrix4x4().identity().scale(vec3Value);
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
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
		miniScript->registerMethod(new ScriptMethodMatrix4x4Scale(miniScript, TYPE_MATRIX4x4, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodMatrix4x4Invert: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_MATRIX4x4;
		public:
			ScriptMethodMatrix4x4Invert(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_MATRIX4x4
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_MATRIX4x4, .name = "mat4", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4) {}
			const string getMethodName() override {
				return "mat4.invert";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Matrix4x4 mat4;
				if (MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, argumentValues, 0, mat4, false) == true) {
					const auto result = mat4.invert();
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMatrix4x4Invert(miniScript, TYPE_MATRIX4x4));
	}
	{
		//
		class ScriptMethodMatrix4x4EulerAngles: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_MATRIX4x4;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodMatrix4x4EulerAngles(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_MATRIX4x4,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_MATRIX4x4, .name = "mat4", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript), TYPE_MATRIX4x4(TYPE_MATRIX4x4), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "mat4.computeEulerAngles";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Matrix4x4 mat4;
				if (MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, argumentValues, 0, mat4, false) == true) {
					const auto result = mat4.computeEulerAngles();
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMatrix4x4EulerAngles(miniScript, TYPE_MATRIX4x4, TYPE_VECTOR3));
	}
}

void MiniScriptMatrix4x4::unsetScriptVariableValue(MiniScript::ScriptVariable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Matrix4x4*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptMatrix4x4::setScriptVariableValue(MiniScript::ScriptVariable& variable, const void* value) const {
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

void MiniScriptMatrix4x4::copyScriptVariable(MiniScript::ScriptVariable& to, const MiniScript::ScriptVariable& from) const {
	//
	Matrix4x4 matrix4x4Value;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		matrix4x4Value = *static_cast<Matrix4x4*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::ScriptVariableType>(getType());
	to.setType(TYPE_MATRIX4x4);
	*static_cast<Matrix4x4*>((void*)to.getValuePtr()) = matrix4x4Value;
}

bool MiniScriptMatrix4x4::mul(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::ScriptVariableType>(getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(miniScript->getDataTypeByClassName("vec3")->getType());
	const auto TYPE_VECTOR4 = static_cast<MiniScript::ScriptVariableType>(miniScript->getDataTypeByClassName("vec4")->getType());
	//
	if (MiniScript::hasType(argumentValues, TYPE_MATRIX4x4) == true) {
		// matrix4x4 * matrix
		if (argumentValues[0].getType() == TYPE_MATRIX4x4 &&
			argumentValues[1].getType() == TYPE_MATRIX4x4) {
			Matrix4x4 a;
			Matrix4x4 b;
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, argumentValues, 0, a, false);
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, argumentValues, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_MATRIX4x4);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// matrix4x4 * vec4
		if (argumentValues[0].getType() == TYPE_MATRIX4x4 &&
			argumentValues[1].getType() == TYPE_VECTOR4) {
			Matrix4x4 a;
			Vector4 b;
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, argumentValues, 0, a, false);
			MiniScriptVector4::getVector4Value(TYPE_VECTOR4, argumentValues, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_VECTOR4);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// vec4 * matrix4x4
		if (argumentValues[0].getType() == TYPE_VECTOR4 &&
			argumentValues[1].getType() == TYPE_MATRIX4x4) {
			Vector4 a;
			Matrix4x4 b;
			MiniScriptVector4::getVector4Value(TYPE_VECTOR4, argumentValues, 0, a, false);
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, argumentValues, 1, b, false);
			//
			const auto result = b * a;
			returnValue.setType(TYPE_VECTOR4);
			returnValue.setValue(&result);
			//
			return true;

		} else
		// matrix4x4 * vec3
		if (argumentValues[0].getType() == TYPE_MATRIX4x4 &&
			argumentValues[1].getType() == TYPE_VECTOR3) {
			Matrix4x4 a;
			Vector3 b;
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, argumentValues, 0, a, false);
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// vec3 * matrix4x4
		if (argumentValues[0].getType() == TYPE_VECTOR3 &&
			argumentValues[1].getType() == TYPE_MATRIX4x4) {
			Vector3 a;
			Matrix4x4 b;
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, a, false);
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, argumentValues, 1, b, false);
			//
			const auto result = b * a;
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// matrix4x4 * float
		if (argumentValues[0].getType() == TYPE_MATRIX4x4 &&
			MiniScript::ScriptVariable::isExpectedType(argumentValues[1].getType(), MiniScript::TYPE_PSEUDO_NUMBER) == true) {
			Matrix4x4 a;
			float b;
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, argumentValues, 0, a, false);
			MiniScript::getFloatValue(argumentValues, 1, b, false);
			//
			const auto result = a * b;
			returnValue.setType(TYPE_MATRIX4x4);
			returnValue.setValue(&result);
			//
			return true;

		} else
		// float * matrix4x4
		if (MiniScript::ScriptVariable::isExpectedType(argumentValues[0].getType(), MiniScript::TYPE_PSEUDO_NUMBER) == true &&
			argumentValues[1].getType() == TYPE_MATRIX4x4) {
			float a;
			Matrix4x4 b;
			MiniScript::getFloatValue(argumentValues, 0, a, false);
			MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_MATRIX4x4, argumentValues, 1, b, false);
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

bool MiniScriptMatrix4x4::div(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	return false;
}

bool MiniScriptMatrix4x4::add(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	return false;
}

bool MiniScriptMatrix4x4::sub(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	return false;
}

const string& MiniScriptMatrix4x4::getClassName() const {
	return CLASS_NAME;
}

const string& MiniScriptMatrix4x4::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptMatrix4x4::getValueAsString(const MiniScript::ScriptVariable& variable) const {
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
		to_string(matrix4x4Value[12]) + ", " +
		to_string(matrix4x4Value[13]) + ", " +
		to_string(matrix4x4Value[14]) + ", " +
		to_string(matrix4x4Value[15]) + ")";

}

