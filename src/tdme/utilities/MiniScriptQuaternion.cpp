#include <span>
#include <string>

#include <tdme/utilities/MiniScriptQuaternion.h>

#include <tdme/tdme.h>
#include <tdme/math/Quaternion.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMatrix4x4.h>
#include <tdme/utilities/MiniScriptVector3.h>

using std::span;
using std::string;

using tdme::utilities::MiniScriptQuaternion;

using tdme::math::Quaternion;
using tdme::utilities::Float;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMatrix4x4;
using tdme::utilities::MiniScriptVector3;

const string MiniScriptQuaternion::CLASS_NAME = "quaternion";
const string MiniScriptQuaternion::TYPE_NAME = "Quaternion";

void MiniScriptQuaternion::registerMethods(MiniScript* miniScript) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(miniScript->getDataTypeByClassName("vec3")->getType());
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::ScriptVariableType>(miniScript->getDataTypeByClassName("mat4")->getType());
	{
		//
		class ScriptMethodQuaternionIdentity: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_QUATERNION;
		public:
			ScriptMethodQuaternionIdentity(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_QUATERNION
			):
				MiniScript::ScriptMethod({}, TYPE_QUATERNION),
				miniScript(miniScript), TYPE_QUATERNION(TYPE_QUATERNION) {
				//
			}
			const string getMethodName() override {
				return "quaternion.identity";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				auto result = Quaternion().identity();
				returnValue.setType(TYPE_QUATERNION);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new ScriptMethodQuaternionIdentity(miniScript, TYPE_QUATERNION));
	}
	{
		//
		class ScriptMethodQuaternionInvert: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_QUATERNION;
		public:
			ScriptMethodQuaternionInvert(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_QUATERNION
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_QUATERNION
				),
				miniScript(miniScript), TYPE_QUATERNION(TYPE_QUATERNION) {
				//
			}
			const string getMethodName() override {
				return "quaternion.invert";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 0, quaternion, false) == true) {
					auto result = quaternion.invert();
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodQuaternionInvert(miniScript, TYPE_QUATERNION));
	}
	{
		//
		class ScriptMethodQuaternionRotate: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_QUATERNION;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodQuaternionRotate(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_QUATERNION,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_QUATERNION
				),
				miniScript(miniScript),
				TYPE_QUATERNION(TYPE_QUATERNION),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "quaternion.rotate";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 axis;
				float angle;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					auto result = Quaternion().rotate(axis, angle);
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodQuaternionRotate(miniScript, TYPE_QUATERNION, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodQuaternionNormalize: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_QUATERNION;
		public:
			ScriptMethodQuaternionNormalize(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_QUATERNION
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_QUATERNION
				),
				miniScript(miniScript), TYPE_QUATERNION(TYPE_QUATERNION) {}
			const string getMethodName() override {
				return "quaternion.normalize";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 0, quaternion, false) == true) {
					auto result = quaternion.normalize();
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodQuaternionNormalize(miniScript, TYPE_QUATERNION));
	}
	{
		//
		class ScriptMethodQuaternionInvert: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_QUATERNION;
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodQuaternionInvert(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_QUATERNION,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript),
				TYPE_QUATERNION(TYPE_QUATERNION),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "quaternion.computeEulerAngles";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 0, quaternion, false) == true) {
					auto result = quaternion.computeEulerAngles();
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodQuaternionInvert(miniScript, TYPE_QUATERNION, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodQuaternionComputeMatrix: public MiniScript::ScriptMethod {
		private:
			MiniScript::ScriptVariableType TYPE_QUATERNION;
			MiniScript::ScriptVariableType TYPE_MATRIX4x4;
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodQuaternionComputeMatrix(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_QUATERNION,
				MiniScript::ScriptVariableType TYPE_MATRIX4x4
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript),	TYPE_QUATERNION(TYPE_QUATERNION), TYPE_MATRIX4x4(TYPE_MATRIX4x4) {
					//
				}
			const string getMethodName() override {
				return "quaternion.computeMatrix";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 0, quaternion, false) == true) {
					auto result = quaternion.computeMatrix();
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodQuaternionComputeMatrix(miniScript, TYPE_QUATERNION, TYPE_MATRIX4x4));
	}
}

void MiniScriptQuaternion::unsetScriptVariableValue(MiniScript::ScriptVariable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Quaternion*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptQuaternion::setScriptVariableValue(MiniScript::ScriptVariable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Quaternion quaternionValue;
	if (value != 0ll) {
		quaternionValue = *static_cast<const Quaternion*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Quaternion*>((void*)variable.getValuePtr()) = quaternionValue;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Quaternion(quaternionValue)));
}

void MiniScriptQuaternion::copyScriptVariable(MiniScript::ScriptVariable& to, const MiniScript::ScriptVariable& from) const {
	//
	Quaternion quaternionValue;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		quaternionValue = *static_cast<Quaternion*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(getType());
	to.setType(TYPE_QUATERNION);
	*static_cast<Quaternion*>((void*)to.getValuePtr()) = quaternionValue;
}

bool MiniScriptQuaternion::mul(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(miniScript->getDataTypeByClassName("vec3")->getType());
	// quaternion
	if (MiniScript::hasType(argumentValues, TYPE_QUATERNION) == true) {
		// quaternion * quaternion
		if (argumentValues[0].getType() == TYPE_QUATERNION &&
			argumentValues[1].getType() == TYPE_QUATERNION) {
			Quaternion a;
			Quaternion b;
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 0, a, false);
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 1, b, false);
			//
			auto result = a * b;
			returnValue.setType(TYPE_QUATERNION);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// quaternion * vec3
		if (argumentValues[0].getType() == TYPE_QUATERNION &&
			argumentValues[1].getType() == TYPE_VECTOR3) {
			Quaternion a;
			Vector3 b;
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 0, a, false);
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, b, false);
			//
			auto result = a * b;
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// vec3 * quaternion
		if (argumentValues[0].getType() == TYPE_VECTOR3 &&
			argumentValues[1].getType() == TYPE_QUATERNION) {
			Vector3 a;
			Quaternion b;
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, a, false);
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 1, b, false);
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

bool MiniScriptQuaternion::div(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	return false;
}

bool MiniScriptQuaternion::add(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	if (MiniScript::hasType(argumentValues, TYPE_QUATERNION) == true) {
		Quaternion a;
		Quaternion b;
		if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 0, a, false) == true &&
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 1, b, false) == true) {
			//
			auto result = a.clone().add(b);
			returnValue.setType(TYPE_QUATERNION);
			returnValue.setValue(&result);
			//
			return true;
		} else  {
			Console::println("add(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("add"));
			miniScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

bool MiniScriptQuaternion::sub(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::ScriptVariableType>(getType());
	//
	if (MiniScript::hasType(argumentValues, TYPE_QUATERNION) == true) {
		Quaternion a;
		Quaternion b;
		if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 0, a, false) == true &&
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, argumentValues, 1, b, false) == true) {
			//
			auto result = a.clone().sub(b);
			returnValue.setType(TYPE_QUATERNION);
			returnValue.setValue(&result);
			//
			return true;
		} else  {
			Console::println("sub(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("sub"));
			miniScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

const string& MiniScriptQuaternion::getClassName() const {
	return CLASS_NAME;
}

const string& MiniScriptQuaternion::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptQuaternion::getValueAsString(const MiniScript::ScriptVariable& variable) const {
	//
	Quaternion quaternionValue;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		quaternionValue = *static_cast<Quaternion*>((void*)variable.getValuePtr());
	}
	return
		"Quaternion(" +
		to_string(quaternionValue[0]) + ", " +
		to_string(quaternionValue[1]) + ", " +
		to_string(quaternionValue[2]) + ", " +
		to_string(quaternionValue[3]) + ")";

}

