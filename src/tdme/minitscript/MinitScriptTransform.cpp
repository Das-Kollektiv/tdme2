#include <span>
#include <string>

#include <tdme/minitscript/MinitScriptTransform.h>

#include <minitscript/minitscript/MinitScript.h>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/utilities/Float.h>
#include <tdme/minitscript/MinitScriptMatrix4x4.h>
#include <tdme/minitscript/MinitScriptQuaternion.h>
#include <tdme/minitscript/MinitScriptVector3.h>
#include <tdme/utilities/Console.h>

using std::span;
using std::string;

using minitscript::minitscript::MinitScript;

using tdme::minitscript::MinitScriptTransform;

using tdme::engine::Transform;
using tdme::utilities::Float;
using tdme::minitscript::MinitScriptMatrix4x4;
using tdme::minitscript::MinitScriptQuaternion;
using tdme::minitscript::MinitScriptVector3;
using tdme::utilities::Console;

const string MinitScriptTransform::TYPE_NAME = "Transform";

MinitScript::VariableType MinitScriptTransform::TYPE_MATRIX4x4 = MinitScript::TYPE_NULL;
MinitScript::VariableType MinitScriptTransform::TYPE_QUATERNION = MinitScript::TYPE_NULL;
MinitScript::VariableType MinitScriptTransform::TYPE_TRANSFORM = MinitScript::TYPE_NULL;
MinitScript::VariableType MinitScriptTransform::TYPE_VECTOR3 = MinitScript::TYPE_NULL;

void MinitScriptTransform::initialize() {
	TYPE_MATRIX4x4 = MinitScript::getDataTypeByClassName("Matrix4x4")->getType();
	TYPE_QUATERNION = MinitScript::getDataTypeByClassName("Quaternion")->getType();
	TYPE_TRANSFORM = MinitScript::getDataTypeByClassName("Transform")->getType();
	TYPE_VECTOR3 = MinitScript::getDataTypeByClassName("Vector3")->getType();
}

void MinitScriptTransform::registerConstants(MinitScript* minitScript) const {
}

void MinitScriptTransform::registerMethods(MinitScript* minitScript) const {
	//
	{
		//
		class MethodTransformAxisZ: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformAxisZ(MinitScript* minitScript):
				MinitScript::Method({}, TYPE_VECTOR3),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::AXIS_Z";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				auto result = Vector3(0.0f, 0.0f, 1.0f);
				returnValue.setType(TYPE_VECTOR3);
				returnValue.setValue(&result);
			}
		};
		minitScript->registerMethod(new MethodTransformAxisZ(minitScript));
	}
	{
		//
		class MethodTransformAxisY: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformAxisY(MinitScript* minitScript):
				MinitScript::Method({}, TYPE_VECTOR3),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::AXIS_Y";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				auto result = Vector3(0.0f, 1.0f, 0.0f);
				returnValue.setType(TYPE_VECTOR3);
				returnValue.setValue(&result);
			}
		};
		minitScript->registerMethod(new MethodTransformAxisY(minitScript));
	}
	{
		//
		class MethodTransformAxisX: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformAxisX(MinitScript* minitScript):
				MinitScript::Method({}, TYPE_VECTOR3),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::AXIS_X";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				auto result = Vector3(1.0f, 0.0f, 0.0f);
				returnValue.setType(TYPE_VECTOR3);
				returnValue.setValue(&result);
			}
		};
		minitScript->registerMethod(new MethodTransformAxisX(minitScript));
	}
	{
		//
		class MethodTransform: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransform(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "translation", .optional = true, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "scale", .optional = true, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "rotationZ", .optional = true, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "rotationY", .optional = true, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "rotationX", .optional = true, .reference = false, .nullable = false },
					},
					TYPE_TRANSFORM
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Transform result;
				Vector3 vec3Value;
				float floatValue;
				// translation
				if (arguments.size() >= 1) {
					if (MinitScriptVector3::getVector3Value(arguments, 0, vec3Value, true) == true) {
						result.setTranslation(vec3Value);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
						minitScript->startErrorScript();
					}
				}
				// scale
				if (arguments.size() >= 2) {
					if (MinitScriptVector3::getVector3Value(arguments, 1, vec3Value, true) == true) {
						result.setScale(vec3Value);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
						minitScript->startErrorScript();
					}
				}
				// rotations: we always use euler angles here
				result.addRotation(Vector3(0.0f, 0.0f, 1.0f), 0.0f);
				result.addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
				result.addRotation(Vector3(1.0f, 0.0f, 0.0f), 0.0f);
				//
				for (auto i = 2; i < arguments.size() && i < 5; i++) {
					if (MinitScript::getFloatValue(arguments, i, floatValue, true) == true) {
						result.setRotationAngle(i - 2, floatValue);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
						minitScript->startErrorScript();
					}
				}
				result.update();
				//
				returnValue.setType(TYPE_TRANSFORM);
				returnValue.setValue(&result);

			}
		};
		minitScript->registerMethod(new MethodTransform(minitScript));
	}
	{
		//
		class MethodTransformGetTranslation: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformGetTranslation(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::getTranslation";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Transform transform;
				if (MinitScriptTransform::getTransformValue(arguments, 0, transform, false) == true) {
					const auto& result = transform.getTranslation();
					//
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformGetTranslation(minitScript));
	}
	{
		//
		class MethodTransformSetTranslation: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformSetTranslation(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::setTranslation";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Transform transform;
				Vector3 translation;
				if (MinitScriptTransform::getTransformValue(arguments, 0, transform, false) == true &&
					MinitScriptVector3::getVector3Value(arguments, 1, translation, false) == true) {
					transform.setTranslation(translation);
					transform.update();
					//
					arguments[0].setType(TYPE_TRANSFORM);
					arguments[0].setValue(&transform);

				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformSetTranslation(minitScript));
	}
	{
		//
		class MethodTransformGetScale: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformGetScale(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::getScale";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Transform transform;
				if (MinitScriptTransform::getTransformValue(arguments, 0, transform, false) == true) {
					const auto& result = transform.getScale();
					//
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformGetScale(minitScript));
	}
	{
		//
		class MethodTransformSetScale: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformSetScale(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "scale", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::setScale";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Transform transform;
				Vector3 scale;
				if (MinitScriptTransform::getTransformValue(arguments, 0, transform, false) == true &&
					MinitScriptVector3::getVector3Value(arguments, 1, scale, false) == true) {
					transform.setScale(scale);
					transform.update();
					//
					arguments[0].setType(TYPE_TRANSFORM);
					arguments[0].setValue(&transform);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformSetScale(minitScript));
	}
	{
		//
		class MethodTransformGetRotationAxis: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformGetRotationAxis(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::getRotationAxis";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t idx;
				Transform transform;
				if (MinitScriptTransform::getTransformValue(arguments, 0, transform, false) == true &&
					MinitScript::getIntegerValue(arguments, 1, idx, false) == true) {
					if (idx < transform.getRotationCount()) {
						auto result = transform.getRotationAxis(idx);
						//
						returnValue.setType(TYPE_VECTOR3);
						returnValue.setValue(&result);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
						minitScript->startErrorScript();
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformGetRotationAxis(minitScript));
	}
	{
		//
		class MethodTransformGetRotationAngle: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformGetRotationAngle(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::getRotationAngle";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t idx;
				Transform transform;
				if (MinitScriptTransform::getTransformValue(arguments, 0, transform, false) == true &&
					MinitScript::getIntegerValue(arguments, 1, idx, false) == true) {
					if (idx < transform.getRotationCount()) {
						returnValue.setValue(transform.getRotationAngle(idx));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
						minitScript->startErrorScript();
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformGetRotationAngle(minitScript));
	}
	{
		//
		class MethodTransformSetRotationAngle: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformSetRotationAngle(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::setRotationAngle";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t idx;
				Transform transform;
				float angle;
				if (MinitScriptTransform::getTransformValue(arguments, 0, transform, false) == true &&
					MinitScript::getIntegerValue(arguments, 1, idx, false) == true &&
					MinitScript::getFloatValue(arguments, 2, angle, false) == true) {
					if (idx < transform.getRotationCount()) {
						transform.setRotationAngle(idx, angle);
						transform.update();
						//
						arguments[0].setType(TYPE_TRANSFORM);
						arguments[0].setValue(&transform);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
						minitScript->startErrorScript();
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformSetRotationAngle(minitScript));
	}
	{
		//
		class MethodTransformRotate: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformRotate(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::rotate";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Transform transform;
				Vector3 vec3;
				if (MinitScriptTransform::getTransformValue(arguments, 0, transform, false) == true &&
					MinitScriptVector3::getVector3Value(arguments, 1, vec3, false) == true) {
					//
					auto result = transform.getRotationsQuaternion() * vec3;
					//
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformRotate(minitScript));
	}
	{
		//
		class MethodTransformApplyRotation: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformApplyRotation(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::applyRotation";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Transform transform;
				Vector3 axis;
				float angle;
				if (MinitScriptTransform::getTransformValue(arguments, 0, transform, false) == true &&
					MinitScriptVector3::getVector3Value(arguments, 1, axis, false) == true &&
					MinitScript::getFloatValue(arguments, 2, angle, false) == true) {
					//
					transform.addRotation(axis, angle);
					transform.update();
					// get transform and make sure its a euler transform
					auto euler = transform.getTransformMatrix().computeEulerAngles();
					while (transform.getRotationCount() > 3) transform.removeRotation(transform.getRotationCount() - 1);
					while (transform.getRotationCount() < 3) transform.addRotation(Vector3(), 0.0f);
					transform.setRotationAxis(0, Vector3(0.0f, 0.0f, 1.0f));
					transform.setRotationAxis(1, Vector3(0.0f, 1.0f, 0.0f));
					transform.setRotationAxis(2, Vector3(1.0f, 0.0f, 0.0f));
					transform.setRotationAngle(0, euler.getZ());
					transform.setRotationAngle(1, euler.getY());
					transform.setRotationAngle(2, euler.getX());
					transform.update();
					//
					arguments[0].setType(TYPE_TRANSFORM);
					arguments[0].setValue(&transform);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformApplyRotation(minitScript));
	}
	{
		//
		class MethodTransformInterpolateRotation: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformInterpolateRotation(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "currentAngle", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "targetAngle", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "timePassedSeconds", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "degreesPerSeconds", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "interpolatedAngle", .optional = false, .reference = true, .nullable = false },
					},
					MinitScript::VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::interpolateRotation";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float currentAngle;
				float targetAngle;
				float timePassedSeconds;
				float degreesPerSeconds;
				float interpolatedAngle = 0.0f;
				if (arguments.size() == 5 &&
					MinitScript::getFloatValue(arguments, 0, currentAngle) == true &&
					MinitScript::getFloatValue(arguments, 1, targetAngle) == true &&
					MinitScript::getFloatValue(arguments, 2, timePassedSeconds) == true &&
					MinitScript::getFloatValue(arguments, 3, degreesPerSeconds) == true) {
					returnValue = Rotation::interpolate(currentAngle, targetAngle, timePassedSeconds, degreesPerSeconds, interpolatedAngle);
					arguments[4].setValue(interpolatedAngle);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformInterpolateRotation(minitScript));
	}
	{
		//
		class MethodTransformGetTransformMatrix: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformGetTransformMatrix(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::getTransformMatrix";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Transform transform;
				if (MinitScriptTransform::getTransformValue(arguments, 0, transform, false) == true) {
					const auto& result = transform.getTransformMatrix();
					//
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformGetTransformMatrix(minitScript));
	}
	{
		//
		class MethodTransformGetRotationsQuaternion: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformGetRotationsQuaternion(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_QUATERNION
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::getRotationsQuaternion";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Transform transform;
				if (MinitScriptTransform::getTransformValue(arguments, 0, transform, false) == true) {
					const auto& result = transform.getRotationsQuaternion();
					//
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformGetRotationsQuaternion(minitScript));
	}
	{
		//
		class MethodTransformFromMatrix: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTransformFromMatrix(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_MATRIX4x4, .name = "transformMatrix", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_TRANSFORM
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Transform::fromMatrix";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Matrix4x4 transformMatrix;
				if (MinitScriptMatrix4x4::getMatrix4x4Value(arguments, 0, transformMatrix, false) == true) {
					Transform result;
					result.fromMatrix(transformMatrix, RotationOrder::ZYX);
					returnValue.setType(TYPE_TRANSFORM);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodTransformFromMatrix(minitScript));
	}
}

void MinitScriptTransform::unsetVariableValue(MinitScript::Variable& variable) const {
	delete static_cast<Transform*>(variable.getValuePtr());
}

void MinitScriptTransform::setVariableValue(MinitScript::Variable& variable) const {
	variable.setValuePtr(new Transform());
}

void MinitScriptTransform::setVariableValue(MinitScript::Variable& variable, const void* value) const {
	*static_cast<Transform*>(variable.getValuePtr()) = *static_cast<const Transform*>(value);
}

void MinitScriptTransform::copyVariable(MinitScript::Variable& to, const MinitScript::Variable& from) const {
	to.setType(TYPE_TRANSFORM);
	*static_cast<Transform*>(to.getValuePtr()) = *static_cast<Transform*>(from.getValuePtr());
}

bool MinitScriptTransform::mul(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	// transform
	if (MinitScript::hasType(arguments, TYPE_TRANSFORM) == true) {
		// transform * vec3
		if (arguments[0].getType() == TYPE_TRANSFORM &&
			arguments[1].getType() == TYPE_VECTOR3) {
			Transform a;
			Vector3 b;
			MinitScriptTransform::getTransformValue(arguments, 0, a, false);
			MinitScriptVector3::getVector3Value(arguments, 1, b, false);
			//
			auto result = a * b;
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// vec3 * transform
		if (arguments[0].getType() == TYPE_VECTOR3 &&
			arguments[1].getType() == TYPE_TRANSFORM) {
			Vector3 a;
			Transform b;
			MinitScriptVector3::getVector3Value(arguments, 0, a, false);
			MinitScriptTransform::getTransformValue(arguments, 1, b, false);
			//
			auto result = b * a;
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "mul"), subStatement); minitScript->startErrorScript();
			minitScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

bool MinitScriptTransform::div(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

bool MinitScriptTransform::add(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

bool MinitScriptTransform::sub(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

const string& MinitScriptTransform::getTypeAsString() const {
	return TYPE_NAME;
}

const string MinitScriptTransform::getValueAsString(const MinitScript::Variable& variable) const {
	//
	const auto& transform = *static_cast<Transform*>(variable.getValuePtr());
	//
	string result;
	result+=
		"Transform(translation: Vector3(" +
		to_string(transform.getTranslation().getX()) + ", " +
		to_string(transform.getTranslation().getY()) + ", " +
		to_string(transform.getTranslation().getZ()) + "), " +
		"scale: (" +
		to_string(transform.getScale().getX()) + ", " +
		to_string(transform.getScale().getY()) + ", " +
		to_string(transform.getScale().getZ()) + ")";
	for (auto i = 0; i < transform.getRotationCount(); i++) {
		result+= ", rotations: (axis: Vector3(" +
				to_string(transform.getRotationAxis(i).getX()) + ", " +
				to_string(transform.getRotationAxis(i).getY()) + ", " +
				to_string(transform.getRotationAxis(i).getZ()) + "), angle: " +
				to_string(transform.getRotationAngle(i)) + ")";
	}
	result+= ")";
	//
	return result;
}

MinitScript::DataType::ScriptContext* MinitScriptTransform::createScriptContext() const {
	return nullptr;
}

void MinitScriptTransform::deleteScriptContext(ScriptContext* context) const {
}

void MinitScriptTransform::garbageCollection(ScriptContext* context) const {
}
