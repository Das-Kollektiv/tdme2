#include <span>
#include <string>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/miniscript/MiniScriptQuaternion.h>

#include <tdme/tdme.h>
#include <tdme/math/Quaternion.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/miniscript/MiniScriptMatrix4x4.h>
#include <tdme/miniscript/MiniScriptVector3.h>

using std::span;
using std::string;

using miniscript::miniscript::MiniScript;

using tdme::miniscript::MiniScriptQuaternion;

using tdme::math::Quaternion;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::miniscript::MiniScriptMatrix4x4;
using tdme::miniscript::MiniScriptVector3;

const string MiniScriptQuaternion::TYPE_NAME = "Quaternion";

MiniScript::VariableType MiniScriptQuaternion::TYPE_MATRIX4x4 = MiniScript::TYPE_NULL;
MiniScript::VariableType MiniScriptQuaternion::TYPE_QUATERNION = MiniScript::TYPE_NULL;
MiniScript::VariableType MiniScriptQuaternion::TYPE_VECTOR3 = MiniScript::TYPE_NULL;

void MiniScriptQuaternion::initialize() {
	TYPE_MATRIX4x4 = MiniScript::getDataTypeByClassName("Matrix4x4")->getType();
	TYPE_QUATERNION = MiniScript::getDataTypeByClassName("Quaternion")->getType();
	TYPE_VECTOR3 = MiniScript::getDataTypeByClassName("Vector3")->getType();
}

void MiniScriptQuaternion::registerConstants(MiniScript* miniScript) const {
}

void MiniScriptQuaternion::registerMethods(MiniScript* miniScript) const {
	{
		//
		class MethodQuaternionIdentity: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodQuaternionIdentity(MiniScript* miniScript):
				MiniScript::Method({}, TYPE_QUATERNION),
				miniScript(miniScript) {
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
		miniScript->registerMethod(new MethodQuaternionIdentity(miniScript));
	}
	{
		//
		class MethodQuaternionInvert: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodQuaternionInvert(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_QUATERNION
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Quaternion::invert";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(arguments, 0, quaternion, false) == true) {
					auto result = quaternion.invert();
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodQuaternionInvert(miniScript));
	}
	{
		//
		class MethodQuaternionRotate: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodQuaternionRotate(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_QUATERNION
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Quaternion::rotate";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 axis;
				float angle;
				if (MiniScriptVector3::getVector3Value(arguments, 0, axis, false) == true &&
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
		miniScript->registerMethod(new MethodQuaternionRotate(miniScript));
	}
	{
		//
		class MethodQuaternionNormalize: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodQuaternionNormalize(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_QUATERNION
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Quaternion::normalize";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(arguments, 0, quaternion, false) == true) {
					auto result = quaternion.normalize();
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodQuaternionNormalize(miniScript));
	}
	{
		//
		class MethodQuaternionInvert: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodQuaternionInvert(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Quaternion::computeEulerAngles";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(arguments, 0, quaternion, false) == true) {
					auto result = quaternion.computeEulerAngles();
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodQuaternionInvert(miniScript));
	}
	{
		//
		class MethodQuaternionComputeMatrix: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodQuaternionComputeMatrix(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript) {
					//
				}
			const string getMethodName() override {
				return "Quaternion::computeMatrix";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Quaternion quaternion;
				if (MiniScriptQuaternion::getQuaternionValue(arguments, 0, quaternion, false) == true) {
					auto result = quaternion.computeMatrix();
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodQuaternionComputeMatrix(miniScript));
	}
}

void MiniScriptQuaternion::unsetVariableValue(MiniScript::Variable& variable) const {
	delete static_cast<Quaternion*>(variable.getValuePtr());
}

void MiniScriptQuaternion::setVariableValue(MiniScript::Variable& variable) const {
	variable.setValuePtr(new Quaternion());
}

void MiniScriptQuaternion::setVariableValue(MiniScript::Variable& variable, const void* value) const {
	*static_cast<Quaternion*>(variable.getValuePtr()) = *static_cast<const Quaternion*>(value);
}

void MiniScriptQuaternion::copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const {
	to.setType(TYPE_QUATERNION);
	*static_cast<Quaternion*>(to.getValuePtr()) = *static_cast<Quaternion*>(from.getValuePtr());
}

bool MiniScriptQuaternion::mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	// quaternion
	if (MiniScript::hasType(arguments, TYPE_QUATERNION) == true) {
		// quaternion * quaternion
		if (arguments[0].getType() == TYPE_QUATERNION &&
			arguments[1].getType() == TYPE_QUATERNION) {
			Quaternion a;
			Quaternion b;
			MiniScriptQuaternion::getQuaternionValue(arguments, 0, a, false);
			MiniScriptQuaternion::getQuaternionValue(arguments, 1, b, false);
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
			MiniScriptQuaternion::getQuaternionValue(arguments, 0, a, false);
			MiniScriptVector3::getVector3Value(arguments, 1, b, false);
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
			MiniScriptVector3::getVector3Value(arguments, 0, a, false);
			MiniScriptQuaternion::getQuaternionValue(arguments, 1, b, false);
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
	//
	if (MiniScript::hasType(arguments, TYPE_QUATERNION) == true) {
		Quaternion a;
		Quaternion b;
		if (MiniScriptQuaternion::getQuaternionValue(arguments, 0, a, false) == true &&
			MiniScriptQuaternion::getQuaternionValue(arguments, 1, b, false) == true) {
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
	//
	if (MiniScript::hasType(arguments, TYPE_QUATERNION) == true) {
		Quaternion a;
		Quaternion b;
		if (MiniScriptQuaternion::getQuaternionValue(arguments, 0, a, false) == true &&
			MiniScriptQuaternion::getQuaternionValue(arguments, 1, b, false) == true) {
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
	const auto& quaternion = *static_cast<Quaternion*>(variable.getValuePtr());
	//
	return
		"Quaternion(" +
		to_string(quaternion[0]) + ", " +
		to_string(quaternion[1]) + ", " +
		to_string(quaternion[2]) + ", " +
		to_string(quaternion[3]) + ")";

}

void* MiniScriptQuaternion::createScriptContext() const {
	return nullptr;
}

void MiniScriptQuaternion::deleteScriptContext(void* context) const {
}

void MiniScriptQuaternion::garbageCollection(void* context) const {
}
