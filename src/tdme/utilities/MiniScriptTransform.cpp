#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMatrix4x4.h>
#include <tdme/utilities/MiniScriptQuaternion.h>
#include <tdme/utilities/MiniScriptTransform.h>
#include <tdme/utilities/MiniScriptVector3.h>

using std::span;
using std::string;

using tdme::engine::Transform;
using tdme::utilities::Float;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMatrix4x4;
using tdme::utilities::MiniScriptQuaternion;
using tdme::utilities::MiniScriptTransform;
using tdme::utilities::MiniScriptVector3;

const string MiniScriptTransform::CLASS_NAME = "transform";
const string MiniScriptTransform::TYPE_NAME = "Transform";

void MiniScriptTransform::registerMethods() const {
	const auto TYPE_TRANSFORM = static_cast<MiniScript::ScriptVariableType>(getType());
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::ScriptVariableType>(miniScript->getDataTypeByClassName("mat4")->getType());
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(miniScript->getDataTypeByClassName("quaternion")->getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(miniScript->getDataTypeByClassName("vec3")->getType());
	//
	{
		//
		class ScriptMethodTransformAxisZ: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodTransformAxisZ(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod({}, TYPE_VECTOR3),
				miniScript(miniScript), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform.AXIS_Z";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				auto result = Vector3(0.0f, 0.0f, 1.0f);
				returnValue.setType(TYPE_VECTOR3);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new ScriptMethodTransformAxisZ(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodTransformAxisY: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodTransformAxisY(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod({}, TYPE_VECTOR3),
				miniScript(miniScript), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform.AXIS_Y";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				auto result = Vector3(0.0f, 1.0f, 0.0f);
				returnValue.setType(TYPE_VECTOR3);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new ScriptMethodTransformAxisY(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodTransformAxisX: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodTransformAxisX(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod({}, TYPE_VECTOR3),
				miniScript(miniScript), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform.AXIS_X";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				auto result = Vector3(1.0f, 0.0f, 0.0f);
				returnValue.setType(TYPE_VECTOR3);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new ScriptMethodTransformAxisX(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodTransform: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodTransform(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "translation", .optional = true, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "scale", .optional = true, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "rotationZ", .optional = true, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "rotationY", .optional = true, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "rotationX", .optional = true, .reference = false, .nullable = false },
					},
					TYPE_TRANSFORM),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Transform result;
				Vector3 vec3Value;
				float floatValue;
				// translation
				if (argumentValues.size() >= 1) {
					if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, vec3Value, true) == true) {
						result.setTranslation(vec3Value);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
				// scale
				if (argumentValues.size() >= 2) {
					if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, vec3Value, true) == true) {
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
				for (auto i = 2; i < argumentValues.size() && i < 5; i++) {
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, true) == true) {
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
		miniScript->registerMethod(new ScriptMethodTransform(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodTransformGetTranslation: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodTransformGetTranslation(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform.getTranslation";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, transform, false) == true) {
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
		miniScript->registerMethod(new ScriptMethodTransformGetTranslation(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodTransformSetTranslation: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodTransformSetTranslation(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_NULL),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform.setTranslation";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Transform transform;
				Vector3 translation;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, transform, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, translation, false) == true) {
					transform.setTranslation(translation);
					transform.update();
					//
					argumentValues[0].setType(TYPE_TRANSFORM);
					argumentValues[0].setValue(&transform);

				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodTransformSetTranslation(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodTransformGetScale: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodTransformGetScale(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform.getScale";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, transform, false) == true) {
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
		miniScript->registerMethod(new ScriptMethodTransformGetScale(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodTransformSetScale: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodTransformSetScale(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "scale", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_NULL),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform.setScale";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Transform transform;
				Vector3 scale;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, transform, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, scale, false) == true) {
					transform.setScale(scale);
					transform.update();
					//
					argumentValues[0].setType(TYPE_TRANSFORM);
					argumentValues[0].setValue(&transform);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodTransformSetScale(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodTransformGetRotationAxis: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodTransformGetRotationAxis(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform.getRotationAxis";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t idx;
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, transform, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
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
		miniScript->registerMethod(new ScriptMethodTransformGetRotationAxis(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodTransformGetRotationAngle: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
		public:
			ScriptMethodTransformGetRotationAngle(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM) {}
			const string getMethodName() override {
				return "transform.getRotationAngle";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t idx;
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, transform, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
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
		miniScript->registerMethod(new ScriptMethodTransformGetRotationAngle(miniScript, TYPE_TRANSFORM));
	}
	{
		//
		class ScriptMethodTransformSetRotationAngle: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
		public:
			ScriptMethodTransformSetRotationAngle(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_NULL),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM) {}
			const string getMethodName() override {
				return "transform.setRotationAngle";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t idx;
				Transform transform;
				float angle;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, transform, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, angle, false) == true) {
					if (idx < transform.getRotationCount()) {
						transform.setRotationAngle(idx, angle);
						transform.update();
						//
						argumentValues[0].setType(TYPE_TRANSFORM);
						argumentValues[0].setValue(&transform);
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
		miniScript->registerMethod(new ScriptMethodTransformSetRotationAngle(miniScript, TYPE_TRANSFORM));
	}
	{
		//
		class ScriptMethodTransformRotate: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodTransformRotate(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform.rotate";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Transform transform;
				Vector3 vec3;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, transform, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, vec3, false) == true) {
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
		miniScript->registerMethod(new ScriptMethodTransformRotate(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodTransformApplyRotation: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodTransformApplyRotation(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_NULL),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_VECTOR3(TYPE_VECTOR3) {}
			const string getMethodName() override {
				return "transform.applyRotation";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Transform transform;
				Vector3 axis;
				float angle;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, transform, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, angle, false) == true) {
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
					argumentValues[0].setType(TYPE_TRANSFORM);
					argumentValues[0].setValue(&transform);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodTransformApplyRotation(miniScript, TYPE_TRANSFORM, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodTransformInterpolateRotation: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformInterpolateRotation(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "currentAngle", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "targetAngle", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "timePassedSeconds", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "degreesPerSeconds", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "interpolatedAngle", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.interpolateRotation";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float currentAngle;
				float targetAngle;
				float timePassedSeconds;
				float degreesPerSeconds;
				float interpolatedAngle = 0.0f;
				if (argumentValues.size() == 5 &&
					MiniScript::getFloatValue(argumentValues, 0, currentAngle) == true &&
					MiniScript::getFloatValue(argumentValues, 1, targetAngle) == true &&
					MiniScript::getFloatValue(argumentValues, 2, timePassedSeconds) == true &&
					MiniScript::getFloatValue(argumentValues, 3, degreesPerSeconds) == true) {
					returnValue = Rotation::interpolate(currentAngle, targetAngle, timePassedSeconds, degreesPerSeconds, interpolatedAngle);
					argumentValues[4].setValue(interpolatedAngle);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodTransformInterpolateRotation(miniScript));
	}
	{
		//
		class ScriptMethodTransformGetTransformMatrix: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
			MiniScript::ScriptVariableType TYPE_MATRIX4x4;
		public:
			ScriptMethodTransformGetTransformMatrix(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM,
				MiniScript::ScriptVariableType TYPE_MATRIX4x4
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4),
					miniScript(miniScript),TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_MATRIX4x4(TYPE_MATRIX4x4) {}
			const string getMethodName() override {
				return "transform.getTransformMatrix";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, transform, false) == true) {
					const auto& result = transform.getTransformMatrix();
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodTransformGetTransformMatrix(miniScript, TYPE_TRANSFORM, TYPE_MATRIX4x4));
	}
	{
		//
		class ScriptMethodTransformGetRotationsQuaternion: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
			MiniScript::ScriptVariableType TYPE_QUATERNION;
		public:
			ScriptMethodTransformGetRotationsQuaternion(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM,
				MiniScript::ScriptVariableType TYPE_QUATERNION
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_QUATERNION),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_QUATERNION(TYPE_QUATERNION) {}
			const string getMethodName() override {
				return "transform.getRotationsQuaternion";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Transform transform;
				if (MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, transform, false) == true) {
					const auto& result = transform.getRotationsQuaternion();
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodTransformGetRotationsQuaternion(miniScript, TYPE_TRANSFORM, TYPE_QUATERNION));
	}
	{
		//
		class ScriptMethodTransformFromMatrix: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_TRANSFORM;
			MiniScript::ScriptVariableType TYPE_MATRIX4x4;
		public:
			ScriptMethodTransformFromMatrix(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_TRANSFORM,
				MiniScript::ScriptVariableType TYPE_MATRIX4x4
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_MATRIX4x4, .name = "transformMatrix", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_TRANSFORM),
					miniScript(miniScript), TYPE_TRANSFORM(TYPE_TRANSFORM), TYPE_MATRIX4x4(TYPE_MATRIX4x4) {}
			const string getMethodName() override {
				return "transform.fromMatrix";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Matrix4x4 transformMatrix;
				if (MiniScript::getMatrix4x4Value(argumentValues, 0, transformMatrix, false) == true) {
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
		miniScript->registerMethod(new ScriptMethodTransformFromMatrix(miniScript, TYPE_TRANSFORM, TYPE_MATRIX4x4));
	}
}

void MiniScriptTransform::unsetScriptVariableValue(MiniScript::ScriptVariable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Transform*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptTransform::setScriptVariableValue(MiniScript::ScriptVariable& variable, const void* value) const {
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

void MiniScriptTransform::copyScriptVariable(MiniScript::ScriptVariable& to, const MiniScript::ScriptVariable& from) const {
	//
	Transform transformValue;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		transformValue = *static_cast<Transform*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_TRANSFORM = static_cast<MiniScript::ScriptVariableType>(getType());
	to.setType(TYPE_TRANSFORM);
	*static_cast<Transform*>((void*)to.getValuePtr()) = transformValue;
}

bool MiniScriptTransform::mul(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_TRANSFORM = static_cast<MiniScript::ScriptVariableType>(getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(miniScript->getDataTypeByClassName("vec3")->getType());
	// transform
	if (MiniScript::hasType(argumentValues, TYPE_TRANSFORM) == true) {
		// transform * vec3
		if (argumentValues[0].getType() == TYPE_TRANSFORM &&
			argumentValues[1].getType() == TYPE_VECTOR3) {
			Transform a;
			Vector3 b;
			MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 0, a, false);
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, b, false);
			//
			auto result = a * b;
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// vec3 * transform
		if (argumentValues[0].getType() == TYPE_VECTOR3 &&
			argumentValues[1].getType() == TYPE_TRANSFORM) {
			Vector3 a;
			Transform b;
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, a, false);
			MiniScriptTransform::getTransformValue(TYPE_TRANSFORM, argumentValues, 1, b, false);
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

bool MiniScriptTransform::div(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	return false;
}

bool MiniScriptTransform::add(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	return false;
}

bool MiniScriptTransform::sub(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	return false;
}

const string& MiniScriptTransform::getClassName() const {
	return CLASS_NAME;
}

const string& MiniScriptTransform::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptTransform::getValueAsString(const MiniScript::ScriptVariable& variable) const {
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

