#include <span>
#include <string>

#include <tdme/utilities/MiniScriptTransform.h>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScriptMatrix4x4.h>
#include <tdme/utilities/MiniScriptQuaternion.h>
#include <tdme/utilities/MiniScriptVector3.h>
#include <tdme/utilities/Console.h>

using std::span;
using std::string;

using miniscript::miniscript::MiniScript;

using tdme::utilities::MiniScriptTransform;

using tdme::engine::Transform;
using tdme::utilities::Float;
using tdme::utilities::MiniScriptMatrix4x4;
using tdme::utilities::MiniScriptQuaternion;
using tdme::utilities::MiniScriptVector3;
using tdme::utilities::Console;

const string MiniScriptTransform::TYPE_NAME = "Transform";

void MiniScriptTransform::registerMethods(MiniScript* miniScript) const {
	const auto TYPE_TRANSFORM = static_cast<MiniScript::VariableType>(getType());
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Matrix4x4")->getType());
	const auto TYPE_QUATERNION = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Quaternion")->getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Vector3")->getType());
	//
	{
		//
		class MethodTransformAxisZ: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodTransformAxisZ(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method({}, TYPE_VECTOR3),
				miniScript(miniScript), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Transform::AXIS_Z";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				auto result = Vector3(0.0f, 0.0f, 1.0f);
				returnValue.setType(TYPE_VECTOR3);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new MethodTransformAxisZ(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class MethodTransformAxisY: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodTransformAxisY(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method({}, TYPE_VECTOR3),
				miniScript(miniScript), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Transform::AXIS_Y";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				auto result = Vector3(0.0f, 1.0f, 0.0f);
				returnValue.setType(TYPE_VECTOR3);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new MethodTransformAxisY(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class MethodTransformAxisX: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodTransformAxisX(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method({}, TYPE_VECTOR3),
				miniScript(miniScript), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Transform::AXIS_X";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				auto result = Vector3(1.0f, 0.0f, 0.0f);
				returnValue.setType(TYPE_VECTOR3);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new MethodTransformAxisX(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class MethodTransform: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodTransform(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "translation", .optional = true, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "scale", .optional = true, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "rotationZ", .optional = true, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "rotationY", .optional = true, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "rotationX", .optional = true, .reference = false, .nullable = false },
					},
					TYPE_TRANSFORM
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Transform result;
				Vector3 vec3Value;
				float floatValue;
				// translation
				if (arguments.size() >= 1) {
					if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 0, vec3Value, true) == true) {
						result.setTranslation(vec3Value);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
				// scale
				if (arguments.size() >= 2) {
					if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 1, vec3Value, true) == true) {
						result.setScale(vec3Value);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
				// rotations: we always use euler angles here
				result.addRotation(Vector3(0.0f, 0.0f, 1.0f), 0.0f);
				result.addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
				result.addRotation(Vector3(1.0f, 0.0f, 0.0f), 0.0f);
				//
				for (auto i = 2; i < arguments.size() && i < 5; i++) {
					if (MiniScript::getFloatValue(arguments, i, floatValue, true) == true) {
						result.setRotationAngle(i - 2, floatValue);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
				result.update();
				//
				returnValue.setType(TYPE_TRANSFORM);
				returnValue.setValue(&result);

			}
		};
		miniScript->registerMethod(new MethodTransform(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class MethodTransformGetTranslation: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodTransformGetTranslation(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Transform::getTranslation";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, transform, false) == true) {
					const auto& result = transform.getTranslation();
					//
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformGetTranslation(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class MethodTransformSetTranslation: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodTransformSetTranslation(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_NULL
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Transform::setTranslation";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Transform transform;
				Vector3 translation;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, transform, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 1, translation, false) == true) {
					transform.setTranslation(translation);
					transform.update();
					//
					arguments[0].setType(TYPE_TRANSFORM);
					arguments[0].setValue(&transform);

				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformSetTranslation(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class MethodTransformGetScale: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodTransformGetScale(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Transform::getScale";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, transform, false) == true) {
					const auto& result = transform.getScale();
					//
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformGetScale(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class MethodTransformSetScale: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodTransformSetScale(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "scale", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_NULL
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Transform::setScale";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Transform transform;
				Vector3 scale;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, transform, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 1, scale, false) == true) {
					transform.setScale(scale);
					transform.update();
					//
					arguments[0].setType(TYPE_TRANSFORM);
					arguments[0].setValue(&transform);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformSetScale(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class MethodTransformGetRotationAxis: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodTransformGetRotationAxis(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Transform::getRotationAxis";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t idx;
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, transform, false) == true &&
					MiniScript::getIntegerValue(arguments, 1, idx, false) == true) {
					if (idx < transform.getRotationCount()) {
						auto result = transform.getRotationAxis(idx);
						//
						returnValue.setType(TYPE_VECTOR3);
						returnValue.setValue(&result);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformGetRotationAxis(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class MethodTransformGetRotationAngle: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
		public:
			MethodTransformGetRotationAngle(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM
			):
				MiniScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM) {}
			const string getMethodName() override {
				return "Transform::getRotationAngle";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t idx;
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, transform, false) == true &&
					MiniScript::getIntegerValue(arguments, 1, idx, false) == true) {
					if (idx < transform.getRotationCount()) {
						returnValue.setValue(transform.getRotationAngle(idx));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformGetRotationAngle(miniScript, TYPE_TRANSFORM));
	}
	{
		//
		class MethodTransformSetRotationAngle: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
		public:
			MethodTransformSetRotationAngle(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM
			):
				MiniScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_NULL
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM) {}
			const string getMethodName() override {
				return "Transform::setRotationAngle";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t idx;
				Transform transform;
				float angle;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, transform, false) == true &&
					MiniScript::getIntegerValue(arguments, 1, idx, false) == true &&
					MiniScript::getFloatValue(arguments, 2, angle, false) == true) {
					if (idx < transform.getRotationCount()) {
						transform.setRotationAngle(idx, angle);
						transform.update();
						//
						arguments[0].setType(TYPE_TRANSFORM);
						arguments[0].setValue(&transform);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformSetRotationAngle(miniScript, TYPE_TRANSFORM));
	}
	{
		//
		class MethodTransformRotate: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodTransformRotate(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Transform::rotate";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Transform transform;
				Vector3 vec3;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, transform, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 1, vec3, false) == true) {
					//
					auto result = transform.getRotationsQuaternion() * vec3;
					//
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformRotate(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class MethodTransformApplyRotation: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodTransformApplyRotation(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_NULL
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "Transform::applyRotation";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Transform transform;
				Vector3 axis;
				float angle;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, transform, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 1, axis, false) == true &&
					MiniScript::getFloatValue(arguments, 2, angle, false) == true) {
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformApplyRotation(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class MethodTransformInterpolateRotation: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodTransformInterpolateRotation(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "currentAngle", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "targetAngle", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "timePassedSeconds", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "degreesPerSeconds", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "interpolatedAngle", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Transform::interpolateRotation";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float currentAngle;
				float targetAngle;
				float timePassedSeconds;
				float degreesPerSeconds;
				float interpolatedAngle = 0.0f;
				if (arguments.size() == 5 &&
					MiniScript::getFloatValue(arguments, 0, currentAngle) == true &&
					MiniScript::getFloatValue(arguments, 1, targetAngle) == true &&
					MiniScript::getFloatValue(arguments, 2, timePassedSeconds) == true &&
					MiniScript::getFloatValue(arguments, 3, degreesPerSeconds) == true) {
					returnValue = Rotation::interpolate(currentAngle, targetAngle, timePassedSeconds, degreesPerSeconds, interpolatedAngle);
					arguments[4].setValue(interpolatedAngle);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformInterpolateRotation(miniScript));
	}
	{
		//
		class MethodTransformGetTransformMatrix: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
			MiniScript::VariableType TYPE_MATRIX4x4;
		public:
			MethodTransformGetTransformMatrix(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM,
				MiniScript::VariableType TYPE_MATRIX4x4
			):
				MiniScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_MATRIX4x4(TYPE_MATRIX4x4) {}
			const string getMethodName() override {
				return "Transform::getTransformMatrix";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, transform, false) == true) {
					const auto& result = transform.getTransformMatrix();
					//
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformGetTransformMatrix(miniScript, TYPE_TRANSFORM, TYPE_MATRIX4x4));
	}
	{
		//
		class MethodTransformGetRotationsQuaternion: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
			MiniScript::VariableType TYPE_QUATERNION;
		public:
			MethodTransformGetRotationsQuaternion(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM,
				MiniScript::VariableType TYPE_QUATERNION
			):
				MiniScript::Method(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_QUATERNION
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_QUATERNION(TYPE_QUATERNION) {}
			const string getMethodName() override {
				return "Transform::getRotationsQuaternion";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, transform, false) == true) {
					const auto& result = transform.getRotationsQuaternion();
					//
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformGetRotationsQuaternion(miniScript, TYPE_TRANSFORM, TYPE_QUATERNION));
	}
	{
		//
		class MethodTransformFromMatrix: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_TRANSFORM;
			MiniScript::VariableType TYPE_MATRIX4x4;
		public:
			MethodTransformFromMatrix(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_TRANSFORM,
				MiniScript::VariableType TYPE_MATRIX4x4
			):
				MiniScript::Method(
					{
						{ .type = TYPE_MATRIX4x4, .name = "transformMatrix", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_TRANSFORM
				),
				miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_MATRIX4x4(TYPE_MATRIX4x4) {}
			const string getMethodName() override {
				return "Transform::fromMatrix";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Matrix4x4 transformMatrix;
				if (MiniScriptMatrix4x4::getMatrix4x4Value(TYPE_TRANSFORM, arguments, 0, transformMatrix, false) == true) {
					Transform result;
					result.fromMatrix(transformMatrix, RotationOrder::ZYX);
					returnValue.setType(TYPE_TRANSFORM);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodTransformFromMatrix(miniScript, TYPE_TRANSFORM, TYPE_MATRIX4x4));
	}
}

void MiniScriptTransform::unsetVariableValue(MiniScript::Variable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Transform*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptTransform::setVariableValue(MiniScript::Variable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Transform transformValue;
	if (value != 0ll) {
		transformValue = *static_cast<const Transform*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Transform*>((void*)variable.getValuePtr()) = transformValue;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Transform(transformValue)));
}

void MiniScriptTransform::copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const {
	//
	Transform transformValue;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		transformValue = *static_cast<Transform*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_TRANSFORM = static_cast<MiniScript::VariableType>(getType());
	to.setType(TYPE_TRANSFORM);
	*static_cast<Transform*>((void*)to.getValuePtr()) = transformValue;
}

bool MiniScriptTransform::mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	const auto TYPE_TRANSFORM = static_cast<MiniScript::VariableType>(getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Vector3")->getType());
	// transform
	if (MiniScript::hasType(arguments, TYPE_TRANSFORM) == true) {
		// transform * vec3
		if (arguments[0].getType() == TYPE_TRANSFORM &&
			arguments[1].getType() == TYPE_VECTOR3) {
			Transform a;
			Vector3 b;
			MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 0, a, false);
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 1, b, false);
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
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 0, a, false);
			MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, arguments, 1, b, false);
			//
			auto result = b * a;
			returnValue.setType(TYPE_VECTOR3);
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

bool MiniScriptTransform::div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

bool MiniScriptTransform::add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

bool MiniScriptTransform::sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

const string& MiniScriptTransform::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptTransform::getValueAsString(const MiniScript::Variable& variable) const {
	//
	Transform transformValue;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		transformValue = *static_cast<Transform*>((void*)variable.getValuePtr());
	}
	//
	string result;
	result+=
		"Transform(translation: Vector3(" +
		to_string(transformValue.getTranslation().getX()) + ", " +
		to_string(transformValue.getTranslation().getY()) + ", " +
		to_string(transformValue.getTranslation().getZ()) + "), " +
		"scale: (" +
		to_string(transformValue.getScale().getX()) + ", " +
		to_string(transformValue.getScale().getY()) + ", " +
		to_string(transformValue.getScale().getZ()) + ")";
	for (auto i = 0; i < transformValue.getRotationCount(); i++) {
		result+= ", rotations: (axis: Vector3(" +
				to_string(transformValue.getRotationAxis(i).getX()) + ", " +
				to_string(transformValue.getRotationAxis(i).getY()) + ", " +
				to_string(transformValue.getRotationAxis(i).getZ()) + "), angle: " +
				to_string(transformValue.getRotationAngle(i)) + ")";
	}
	result+= ")";
	//
	return result;
}

