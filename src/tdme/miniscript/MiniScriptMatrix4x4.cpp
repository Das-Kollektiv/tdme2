#include <span>
#include <string>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/miniscript/MiniScriptMatrix4x4.h>

#include <tdme/tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/miniscript/MiniScriptVector3.h>
#include <tdme/miniscript/MiniScriptVector4.h>

using std::span;
using std::string;

using miniscript::miniscript::MiniScript;

using tdme::miniscript::MiniScriptMatrix4x4;

using tdme::math::Matrix4x4;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::miniscript::MiniScriptVector3;
using tdme::miniscript::MiniScriptVector4;

const string MiniScriptMatrix4x4::TYPE_NAME = "Matrix4x4";

MiniScript::VariableType MiniScriptMatrix4x4::TYPE_MATRIX4x4 = MiniScript::TYPE_NULL;
MiniScript::VariableType MiniScriptMatrix4x4::TYPE_VECTOR3 = MiniScript::TYPE_NULL;
MiniScript::VariableType MiniScriptMatrix4x4::TYPE_VECTOR4 = MiniScript::TYPE_NULL;

void MiniScriptMatrix4x4::initialize() {
	TYPE_MATRIX4x4 = MiniScript::getDataTypeByClassName("Matrix4x4")->getType();
	TYPE_VECTOR3 = MiniScript::getDataTypeByClassName("Vector3")->getType();
	TYPE_VECTOR4 = MiniScript::getDataTypeByClassName("Vector4")->getType();
}

void MiniScriptMatrix4x4::registerConstants(MiniScript* miniScript) const {
}

void MiniScriptMatrix4x4::registerMethods(MiniScript* miniScript) const {
	//
	{
		//
		class MethodMatrix4x4Identity: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMatrix4x4Identity(MiniScript* miniScript):
				MiniScript::Method({}, TYPE_MATRIX4x4),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Matrix4x4::identity";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				const auto result = Matrix4x4().identity();
				returnValue.setType(TYPE_MATRIX4x4);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new MethodMatrix4x4Identity(miniScript));
	}
	{
		//
		class MethodMatrix4x4Translate: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMatrix4x4Translate(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Matrix4x4::translate";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 translation;
				if (MiniScriptVector3::getVector3Value(arguments, 0, translation, false) == true) {
					const auto result = Matrix4x4().identity().setTranslation(translation);
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMatrix4x4Translate(miniScript));
	}
	{
		//
		class MethodMatrix4x4Rotate: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMatrix4x4Rotate(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Matrix4x4::rotate";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 axis;
				float angle;
				if (MiniScriptVector3::getVector3Value(arguments, 0, axis, false) == true &&
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
		miniScript->registerMethod(new MethodMatrix4x4Rotate(miniScript));
	}
	{
		//
		class MethodMatrix4x4Scale: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMatrix4x4Scale(MiniScript* miniScript):
				MiniScript::Method({}, TYPE_MATRIX4x4),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Matrix4x4::scale";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 vec3Value;
				float floatValue;
				if (MiniScriptVector3::getVector3Value(arguments, 0, vec3Value, false) == true) {
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
		miniScript->registerMethod(new MethodMatrix4x4Scale(miniScript));
	}
	{
		//
		class MethodMatrix4x4Invert: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMatrix4x4Invert(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_MATRIX4x4, .name = "matrix4x4", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Matrix4x4::invert";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Matrix4x4 mat4;
				if (MiniScriptMatrix4x4::getMatrix4x4Value(arguments, 0, mat4, false) == true) {
					const auto result = mat4.invert();
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMatrix4x4Invert(miniScript));
	}
	{
		//
		class MethodMatrix4x4EulerAngles: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMatrix4x4EulerAngles(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_MATRIX4x4, .name = "matrix4x4", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Matrix4x4::computeEulerAngles";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Matrix4x4 mat4;
				if (MiniScriptMatrix4x4::getMatrix4x4Value(arguments, 0, mat4, false) == true) {
					const auto result = mat4.computeEulerAngles();
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodMatrix4x4EulerAngles(miniScript));
	}
}

void MiniScriptMatrix4x4::unsetVariableValue(MiniScript::Variable& variable) const {
	delete static_cast<Matrix4x4*>(variable.getValuePtr());
}

void MiniScriptMatrix4x4::setVariableValue(MiniScript::Variable& variable) const {
	variable.setValuePtr(new Matrix4x4());
}

void MiniScriptMatrix4x4::setVariableValue(MiniScript::Variable& variable, const void* value) const {
	*static_cast<Matrix4x4*>(variable.getValuePtr()) = *static_cast<const Matrix4x4*>(value);
}

void MiniScriptMatrix4x4::copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const {
	to.setType(TYPE_MATRIX4x4);
	*static_cast<Matrix4x4*>(to.getValuePtr()) = *static_cast<Matrix4x4*>(from.getValuePtr());
}

bool MiniScriptMatrix4x4::mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	//
	if (MiniScript::hasType(arguments, TYPE_MATRIX4x4) == true) {
		// matrix4x4 * matrix
		if (arguments[0].getType() == TYPE_MATRIX4x4 &&
			arguments[1].getType() == TYPE_MATRIX4x4) {
			Matrix4x4 a;
			Matrix4x4 b;
			MiniScriptMatrix4x4::getMatrix4x4Value(arguments, 0, a, false);
			MiniScriptMatrix4x4::getMatrix4x4Value(arguments, 1, b, false);
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
			MiniScriptMatrix4x4::getMatrix4x4Value(arguments, 0, a, false);
			MiniScriptVector4::getVector4Value(arguments, 1, b, false);
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
			MiniScriptVector4::getVector4Value(arguments, 0, a, false);
			MiniScriptMatrix4x4::getMatrix4x4Value(arguments, 1, b, false);
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
			MiniScriptMatrix4x4::getMatrix4x4Value(arguments, 0, a, false);
			MiniScriptVector3::getVector3Value(arguments, 1, b, false);
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
			MiniScriptVector3::getVector3Value(arguments, 0, a, false);
			MiniScriptMatrix4x4::getMatrix4x4Value(arguments, 1, b, false);
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
			MiniScriptMatrix4x4::getMatrix4x4Value(arguments, 0, a, false);
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
			MiniScriptMatrix4x4::getMatrix4x4Value(arguments, 1, b, false);
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

void* MiniScriptMatrix4x4::createScriptContext() const {
	return nullptr;
}

void MiniScriptMatrix4x4::deleteScriptContext(void* context) const {
}

void MiniScriptMatrix4x4::garbageCollection(void* context) const {
}
