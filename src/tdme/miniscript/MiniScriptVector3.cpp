#include <span>
#include <string>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/miniscript/MiniScriptVector3.h>

using miniscript::miniscript::MiniScript;

using std::span;
using std::string;

using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::miniscript::MiniScriptVector3;

const string MiniScriptVector3::TYPE_NAME = "Vector3";

MiniScript::VariableType MiniScriptVector3::TYPE_VECTOR3 = MiniScript::TYPE_NULL;

void MiniScriptVector3::initialize() {
	TYPE_VECTOR3 = MiniScript::getDataTypeByClassName("Vector3")->getType();
}

void MiniScriptVector3::registerConstants(MiniScript* miniScript) const {
}

void MiniScriptVector3::registerMethods(MiniScript* miniScript) const {
	{
		//
		class MethodVec3: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec3(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "z", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(arguments, 0, xValue, false) == true &&
					MiniScript::getFloatValue(arguments, 1, yValue, false) == true &&
					MiniScript::getFloatValue(arguments, 2, zValue, false) == true) {
					auto result = Vector3(xValue, yValue, zValue);
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec3(miniScript));
	}
	{
		//
		class MethodVec3ComputeLength: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec3ComputeLength(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::computeLength";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value(arguments, 0, vec3, false) == true) {
					auto length = vec3.computeLength();
					returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
				} else {
					Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec3ComputeLength(miniScript));
	}
	{
		//
		class MethodVec3ComputeLengthSquared: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec3ComputeLengthSquared(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::computeLengthSquared";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value( arguments, 0, vec3, false) == true) {
					returnValue.setValue(vec3.computeLengthSquared());
				} else {
					Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec3ComputeLengthSquared(miniScript));
	}
	{
		//
		class MethodVec3ComputeDotProduct: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec3ComputeDotProduct(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::computeDotProduct";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 a;
				Vector3 b;
				if (MiniScriptVector3::getVector3Value( arguments, 0, a, false) == true &&
					MiniScriptVector3::getVector3Value( arguments, 1, b, false) == true) {
					returnValue.setValue(Vector3::computeDotProduct(a, b));
				} else {
					Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec3ComputeDotProduct(miniScript));
	}
	{
		//
		class MethodVec3ComputeCrossProduct: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec3ComputeCrossProduct(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::computeCrossProduct";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 a;
				Vector3 b;
				if (MiniScriptVector3::getVector3Value( arguments, 0, a, false) == true &&
					MiniScriptVector3::getVector3Value( arguments, 1, b, false) == true) {
					auto result = Vector3::computeCrossProduct(a, b);
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec3ComputeCrossProduct(miniScript));
	}
	{
		//
		class MethodVec3Normalize: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec3Normalize(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::normalize";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value( arguments, 0, vec3, false) == true) {
					auto length = vec3.computeLength();
					auto result = length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector3(0.0f, 0.0f, 0.0f):vec3.normalize();
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec3Normalize(miniScript));
	}
	{
		//
		class MethodVec3ComputeAngle: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec3ComputeAngle(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "n", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::computeAngle";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 a;
				Vector3 b;
				Vector3 n;
				if (MiniScriptVector3::getVector3Value( arguments, 0, a, false) == true &&
					MiniScriptVector3::getVector3Value( arguments, 1, b, false) == true &&
					MiniScriptVector3::getVector3Value( arguments, 2, n, false) == true) {
					returnValue.setValue(Vector3::computeAngle(a, b, n));
				} else {
					Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec3ComputeAngle(miniScript));
	}
	{
		//
		class MethodVec3GetX: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec3GetX(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::getX";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value( arguments, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getX());
				} else {
					Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec3GetX(miniScript));
	}
	{
		//
		class MethodVec3GetY: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec3GetY(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::getY";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value( arguments, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getY());
				} else {
					Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec3GetY(miniScript));
	}
	{
		//
		class MethodVec3GetZ: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec3GetZ(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR3, .name = "vector3", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector3::getZ";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value( arguments, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getZ());
				} else {
					Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec3GetZ(miniScript));
	}
}

void MiniScriptVector3::unsetVariableValue(MiniScript::MiniScript::Variable& variable) const {
	delete static_cast<Vector3*>(variable.getValuePtr());
}

void MiniScriptVector3::setVariableValue(MiniScript::MiniScript::Variable& variable) const {
	variable.setValuePtr(new Vector3());
}

void MiniScriptVector3::setVariableValue(MiniScript::MiniScript::Variable& variable, const void* value) const {
	*static_cast<Vector3*>(variable.getValuePtr()) = *static_cast<const Vector3*>(value);
}

void MiniScriptVector3::copyVariable(MiniScript::MiniScript::Variable& to, const MiniScript::MiniScript::Variable& from) const {
	to.setType(TYPE_VECTOR3);
	*static_cast<Vector3*>(to.getValuePtr()) = *static_cast<Vector3*>(from.getValuePtr());
}

bool MiniScriptVector3::mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	// vector3
	if (MiniScript::hasType(arguments, TYPE_VECTOR3) == true) {
		float f;
		// a
		Vector3 a;
		if (arguments[0].getType() == TYPE_VECTOR3) {
			MiniScriptVector3::getVector3Value(arguments, 0, a, false);
		} else
		if (MiniScript::getFloatValue(arguments, 0, f, false) == true) {
			a = Vector3(f, f, f);
		} else {
			Console::printLine("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
			miniScript->startErrorScript();
			return false;
		}
		// b
		Vector3 b;
		if (arguments[1].getType() == TYPE_VECTOR3) {
			MiniScriptVector3::getVector3Value(arguments, 1, b, false);
		} else
		if (MiniScript::getFloatValue(arguments, 1, f, false) == true) {
			b = Vector3(f, f, f);
		} else {
			Console::printLine("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
			miniScript->startErrorScript();
			return false;
		}
		//
		auto result = a.clone().scale(b);
		returnValue.setType(TYPE_VECTOR3);
		returnValue.setValue(&result);
		//
		return true;
	}
	//
	return false;
}

bool MiniScriptVector3::div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	// vector3
	if (arguments[0].getType() == TYPE_VECTOR3) {
		Vector3 a;
		Vector3 b;
		float f;
		// a
		MiniScriptVector3::getVector3Value(arguments, 0, a, false);
		// b
		if (arguments[1].getType() == TYPE_VECTOR3 &&
			MiniScriptVector3::getVector3Value(arguments, 1, b, false) == true) {
			// nop
		} else
		if (MiniScript::getFloatValue(arguments, 1, f, false) == true) {
			b = Vector3(f, f, f);
		} else {
			Console::printLine("div(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("div"));
			miniScript->startErrorScript();
			return false;
		}
		//
		auto result = a / b;
		returnValue.setType(TYPE_VECTOR3);
		returnValue.setValue(&result);
		//
		return true;
	}
	//
	return false;
}

bool MiniScriptVector3::add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	// vector3
	if (MiniScript::hasType(arguments, TYPE_VECTOR3) == true) {
		Vector3 a;
		Vector3 b;
		if (MiniScriptVector3::getVector3Value(arguments, 0, a, false) == true &&
			MiniScriptVector3::getVector3Value(arguments, 1, b, false) == true) {
			auto result = a.clone().add(b);
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else  {
			Console::printLine("add(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("add"));
			miniScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

bool MiniScriptVector3::sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	// vector3
	if (MiniScript::hasType(arguments, TYPE_VECTOR3) == true) {
		Vector3 a;
		Vector3 b;
		if (MiniScriptVector3::getVector3Value(arguments, 0, a, false) == true &&
			MiniScriptVector3::getVector3Value(arguments, 1, b, false) == true) {
			auto result = a.clone().sub(b);
			returnValue.setType(TYPE_VECTOR3);
			returnValue.setValue(&result);
			//
			return true;
		} else  {
			Console::printLine("sub(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("sub"));
			miniScript->startErrorScript();
			//
			return false;
		}
	}
	//
	return false;
}

const string& MiniScriptVector3::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptVector3::getValueAsString(const MiniScript::MiniScript::Variable& variable) const {
	//
	const auto& vector3 = *static_cast<Vector3*>(variable.getValuePtr());
	//
	return
		"Vector3(" +
		to_string(vector3.getX()) + ", " +
		to_string(vector3.getY()) + ", " +
		to_string(vector3.getZ()) + ")";

}

MiniScript::DataType::ScriptContext* MiniScriptVector3::createScriptContext() const {
	return nullptr;
}

void MiniScriptVector3::deleteScriptContext(ScriptContext* context) const {
}

void MiniScriptVector3::garbageCollection(ScriptContext* context) const {
}
