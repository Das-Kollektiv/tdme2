#include <span>
#include <string>

#include <minitscript/minitscript/MinitScript.h>

#include <tdme/tdme.h>
#include <tdme/minitscript/MinitScriptQuaternion.h>

#include <tdme/math/Quaternion.h>
#include <tdme/minitscript/MinitScriptMatrix4x4.h>
#include <tdme/minitscript/MinitScriptVector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>

using std::span;
using std::string;

using minitscript::minitscript::MinitScript;

using tdme::minitscript::MinitScriptQuaternion;

using tdme::math::Quaternion;
using tdme::minitscript::MinitScriptMatrix4x4;
using tdme::minitscript::MinitScriptVector3;
using tdme::utilities::Console;
using tdme::utilities::Float;

const string MinitScriptQuaternion::TYPE_NAME = "Quaternion";

MinitScript::VariableType MinitScriptQuaternion::TYPE_MATRIX4x4 = MinitScript::TYPE_NULL;
MinitScript::VariableType MinitScriptQuaternion::TYPE_QUATERNION = MinitScript::TYPE_NULL;
MinitScript::VariableType MinitScriptQuaternion::TYPE_VECTOR3 = MinitScript::TYPE_NULL;

void MinitScriptQuaternion::initialize() {
	TYPE_MATRIX4x4 = MinitScript::getDataTypeByClassName("Matrix4x4")->getType();
	TYPE_QUATERNION = MinitScript::getDataTypeByClassName("Quaternion")->getType();
	TYPE_VECTOR3 = MinitScript::getDataTypeByClassName("Vector3")->getType();
}

void MinitScriptQuaternion::registerConstants(MinitScript* minitScript) const {
}

void MinitScriptQuaternion::registerMethods(MinitScript* minitScript) const {
	{
		//
		class MethodQuaternionIdentity: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodQuaternionIdentity(MinitScript* minitScript):
				MinitScript::Method({}, TYPE_QUATERNION),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Quaternion::identity";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				auto result = Quaternion().identity();
				returnValue.setType(TYPE_QUATERNION);
				returnValue.setValue(&result);
			}
		};
		minitScript->registerMethod(new MethodQuaternionIdentity(minitScript));
	}
	{
		//
		class MethodQuaternionInvert: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodQuaternionInvert(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_QUATERNION
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Quaternion::invert";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Quaternion quaternion;
				if (MinitScriptQuaternion::getQuaternionValue(arguments, 0, quaternion, false) == true) {
					auto result = quaternion.invert();
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodQuaternionInvert(minitScript));
	}
	{
		//
		class MethodQuaternionRotate: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodQuaternionRotate(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::VariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_QUATERNION
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Quaternion::rotate";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Vector3 axis;
				float angle;
				if (MinitScriptVector3::getVector3Value(arguments, 0, axis, false) == true &&
					MinitScript::getFloatValue(arguments, 1, angle, false) == true) {
					auto result = Quaternion().rotate(axis, angle);
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodQuaternionRotate(minitScript));
	}
	{
		//
		class MethodQuaternionNormalize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodQuaternionNormalize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_QUATERNION
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Quaternion::normalize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Quaternion quaternion;
				if (MinitScriptQuaternion::getQuaternionValue(arguments, 0, quaternion, false) == true) {
					auto result = quaternion.normalize();
					returnValue.setType(TYPE_QUATERNION);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodQuaternionNormalize(minitScript));
	}
	{
		//
		class MethodQuaternionInvert: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodQuaternionInvert(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "Quaternion::computeEulerAngles";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Quaternion quaternion;
				if (MinitScriptQuaternion::getQuaternionValue(arguments, 0, quaternion, false) == true) {
					auto result = quaternion.computeEulerAngles();
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodQuaternionInvert(minitScript));
	}
	{
		//
		class MethodQuaternionComputeMatrix: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodQuaternionComputeMatrix(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				minitScript(minitScript) {
					//
				}
			const string getMethodName() override {
				return "Quaternion::computeMatrix";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				Quaternion quaternion;
				if (MinitScriptQuaternion::getQuaternionValue(arguments, 0, quaternion, false) == true) {
					auto result = quaternion.computeMatrix();
					returnValue.setType(TYPE_MATRIX4x4);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
		};
		minitScript->registerMethod(new MethodQuaternionComputeMatrix(minitScript));
	}
}

void MinitScriptQuaternion::unsetVariableValue(MinitScript::Variable& variable) const {
	delete static_cast<Quaternion*>(variable.getValuePtr());
}

void MinitScriptQuaternion::setVariableValue(MinitScript::Variable& variable) const {
	variable.setValuePtr(new Quaternion());
}

void MinitScriptQuaternion::setVariableValue(MinitScript::Variable& variable, const void* value) const {
	*static_cast<Quaternion*>(variable.getValuePtr()) = *static_cast<const Quaternion*>(value);
}

void MinitScriptQuaternion::copyVariable(MinitScript::Variable& to, const MinitScript::Variable& from) const {
	to.setType(TYPE_QUATERNION);
	*static_cast<Quaternion*>(to.getValuePtr()) = *static_cast<Quaternion*>(from.getValuePtr());
}

bool MinitScriptQuaternion::mul(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	// quaternion
	if (MinitScript::hasType(arguments, TYPE_QUATERNION) == true) {
		// quaternion * quaternion
		if (arguments[0].getType() == TYPE_QUATERNION &&
			arguments[1].getType() == TYPE_QUATERNION) {
			Quaternion a;
			Quaternion b;
			MinitScriptQuaternion::getQuaternionValue(arguments, 0, a, false);
			MinitScriptQuaternion::getQuaternionValue(arguments, 1, b, false);
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
			MinitScriptQuaternion::getQuaternionValue(arguments, 0, a, false);
			MinitScriptVector3::getVector3Value(arguments, 1, b, false);
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
			MinitScriptVector3::getVector3Value(arguments, 0, a, false);
			MinitScriptQuaternion::getQuaternionValue(arguments, 1, b, false);
			//
			auto result = b * a;
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "mul"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

bool MinitScriptQuaternion::div(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

bool MinitScriptQuaternion::add(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	//
	if (MinitScript::hasType(arguments, TYPE_QUATERNION) == true) {
		Quaternion a;
		Quaternion b;
		if (MinitScriptQuaternion::getQuaternionValue(arguments, 0, a, false) == true &&
			MinitScriptQuaternion::getQuaternionValue(arguments, 1, b, false) == true) {
			//
			auto result = a.clone().add(b);
			returnValue.setType(TYPE_QUATERNION);
			returnValue.setValue(&result);
			//
			return true;
		} else  {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "add"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

bool MinitScriptQuaternion::sub(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	//
	if (MinitScript::hasType(arguments, TYPE_QUATERNION) == true) {
		Quaternion a;
		Quaternion b;
		if (MinitScriptQuaternion::getQuaternionValue(arguments, 0, a, false) == true &&
			MinitScriptQuaternion::getQuaternionValue(arguments, 1, b, false) == true) {
			//
			auto result = a.clone().sub(b);
			returnValue.setType(TYPE_QUATERNION);
			returnValue.setValue(&result);
			//
			return true;
		} else  {
			minitScript->complain(MinitScript::decodeOperator(arguments, 2, "sub"), subStatement); minitScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

const string& MinitScriptQuaternion::getTypeAsString() const {
	return TYPE_NAME;
}

const string MinitScriptQuaternion::getValueAsString(const MinitScript::Variable& variable) const {
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

MinitScript::DataType::ScriptContext* MinitScriptQuaternion::createScriptContext() const {
	return nullptr;
}

void MinitScriptQuaternion::deleteScriptContext(ScriptContext* context) const {
}

void MinitScriptQuaternion::garbageCollection(ScriptContext* context) const {
}
