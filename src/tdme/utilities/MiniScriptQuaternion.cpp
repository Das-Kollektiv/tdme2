#include <span>
#include <string>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/utilities/MiniScriptQuaternion.h>

#include <tdme/tdme.h>
#include <tdme/math/Quaternion.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScriptMatrix4x4.h>
#include <tdme/utilities/MiniScriptVector3.h>

using std::span;
using std::string;

using miniscript::miniscript::MiniScript;

using tdme::utilities::MiniScriptQuaternion;

using tdme::math::Quaternion;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::utilities::MiniScriptMatrix4x4;
using tdme::utilities::MiniScriptVector3;

const string MiniScriptQuaternion::TYPE_NAME = "Quaternion";

void MiniScriptQuaternion::registerMethods(MiniScript* miniScript) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::VariableType>(getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Vector3")->getType());
	const auto TYPE_MATRIX4x4 = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Matrix4x4")->getType());
	{
		//
		class MethodQuaternionIdentity: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_QUATERNION;
		public:
			MethodQuaternionIdentity(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_QUATERNION
			):
				MiniScript::Method({}, TYPE_QUATERNION),
				miniScript(miniScript), TYPE_QUATERNION(TYPE_QUATERNION) {
				//
			}
			const string getMethodName() override {
				return "Quaternion::identity";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				auto result = Quaternion().identity();
				returnValue.setType(TYPE_QUATERNION);
				returnValue.setValue(&result);
			}
		};
		miniScript->registerMethod(new MethodQuaternionIdentity(miniScript, TYPE_QUATERNION));
	}
	{
		//
		class MethodQuaternionInvert: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_QUATERNION;
		public:
			MethodQuaternionInvert(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_QUATERNION
			):
				MiniScript::Method(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_QUATERNION
				),
				miniScript(miniScript), TYPE_QUATERNION(TYPE_QUATERNION) {
				//
			}
			const string getMethodName() override {
				return "Quaternion::invert";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 0, quaternion, false) == true) {
					auto result = quaternion.invert();
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodQuaternionInvert(miniScript, TYPE_QUATERNION));
	}
	{
		//
		class MethodQuaternionRotate: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_QUATERNION;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodQuaternionRotate(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_QUATERNION,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_QUATERNION
				),
				miniScript(miniScript),
				TYPE_QUATERNION(TYPE_QUATERNION),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "Quaternion::rotate";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 axis;
				float angle;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 0, axis, false) == true &&
					MiniScript::getFloatValue(arguments, 1, angle, false) == true) {
					auto result = Quaternion().rotate(axis, angle);
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodQuaternionRotate(miniScript, TYPE_QUATERNION, TYPE_VECTOR3));
	}
	{
		//
		class MethodQuaternionNormalize: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_QUATERNION;
		public:
			MethodQuaternionNormalize(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_QUATERNION
			):
				MiniScript::Method(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_QUATERNION
				),
				miniScript(miniScript), TYPE_QUATERNION(TYPE_QUATERNION) {}
			const string getMethodName() override {
				return "Quaternion::normalize";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 0, quaternion, false) == true) {
					auto result = quaternion.normalize();
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodQuaternionNormalize(miniScript, TYPE_QUATERNION));
	}
	{
		//
		class MethodQuaternionInvert: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_QUATERNION;
			MiniScript::VariableType TYPE_VECTOR3;
		public:
			MethodQuaternionInvert(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_QUATERNION,
				MiniScript::VariableType TYPE_VECTOR3
			):
				MiniScript::Method(
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
				return "Quaternion::computeEulerAngles";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 0, quaternion, false) == true) {
					auto result = quaternion.computeEulerAngles();
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodQuaternionInvert(miniScript, TYPE_QUATERNION, TYPE_VECTOR3));
	}
	{
		//
		class MethodQuaternionComputeMatrix: public MiniScript::Method {
		private:
			MiniScript::VariableType TYPE_QUATERNION;
			MiniScript::VariableType TYPE_MATRIX4x4;
			MiniScript* miniScript { nullptr };
		public:
			MethodQuaternionComputeMatrix(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_QUATERNION,
				MiniScript::VariableType TYPE_MATRIX4x4
			):
				MiniScript::Method(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript),	TYPE_QUATERNION(TYPE_QUATERNION), TYPE_MATRIX4x4(TYPE_MATRIX4x4) {
					//
				}
			const string getMethodName() override {
				return "Quaternion::computeMatrix";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 0, quaternion, false) == true) {
					auto result = quaternion.computeMatrix();
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodQuaternionComputeMatrix(miniScript, TYPE_QUATERNION, TYPE_MATRIX4x4));
	}
}

void MiniScriptQuaternion::unsetVariableValue(MiniScript::Variable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Quaternion*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptQuaternion::setVariableValue(MiniScript::Variable& variable, const void* value) const {
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

void MiniScriptQuaternion::copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const {
	//
	Quaternion quaternionValue;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		quaternionValue = *static_cast<Quaternion*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_QUATERNION = static_cast<MiniScript::VariableType>(getType());
	to.setType(TYPE_QUATERNION);
	*static_cast<Quaternion*>((void*)to.getValuePtr()) = quaternionValue;
}

bool MiniScriptQuaternion::mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::VariableType>(getType());
	const auto TYPE_VECTOR3 = static_cast<MiniScript::VariableType>(miniScript->getDataTypeByClassName("Vector3")->getType());
	// quaternion
	if (MiniScript::hasType(arguments, TYPE_QUATERNION) == true) {
		// quaternion * quaternion
		if (arguments[0].getType() == TYPE_QUATERNION &&
			arguments[1].getType() == TYPE_QUATERNION) {
			Quaternion a;
			Quaternion b;
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 0, a, false);
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 1, b, false);
			//
			auto result = a * b;
			returnValue.setType(TYPE_QUATERNION);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// quaternion * vec3
		if (arguments[0].getType() == TYPE_QUATERNION &&
			arguments[1].getType() == TYPE_VECTOR3) {
			Quaternion a;
			Vector3 b;
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 0, a, false);
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 1, b, false);
			//
			auto result = a * b;
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else
		// vec3 * quaternion
		if (arguments[0].getType() == TYPE_VECTOR3 &&
			arguments[1].getType() == TYPE_QUATERNION) {
			Vector3 a;
			Quaternion b;
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, arguments, 0, a, false);
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 1, b, false);
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

bool MiniScriptQuaternion::div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

bool MiniScriptQuaternion::add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::VariableType>(getType());
	//
	if (MiniScript::hasType(arguments, TYPE_QUATERNION) == true) {
		Quaternion a;
		Quaternion b;
		if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 0, a, false) == true &&
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 1, b, false) == true) {
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

bool MiniScriptQuaternion::sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	const auto TYPE_QUATERNION = static_cast<MiniScript::VariableType>(getType());
	//
	if (MiniScript::hasType(arguments, TYPE_QUATERNION) == true) {
		Quaternion a;
		Quaternion b;
		if (MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 0, a, false) == true &&
			MiniScriptQuaternion::getQuaternionValue(TYPE_QUATERNION, arguments, 1, b, false) == true) {
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

const string& MiniScriptQuaternion::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptQuaternion::getValueAsString(const MiniScript::Variable& variable) const {
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

