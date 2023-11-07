#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptVector3.h>

using std::span;
using std::string;

using tdme::math::Vector3;
using tdme::utilities::Float;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptVector3;

const string MiniScriptVector3::CLASS_NAME = "vec3";
const string MiniScriptVector3::TYPE_NAME = "Vector3";

void MiniScriptVector3::registerMethods() const {
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(getType());
	{
		//
		class ScriptMethodVec3: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodVec3(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "z", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "vec3";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					auto result = Vector3(xValue, yValue, zValue);
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec3(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodVec3ComputeLength: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodVec3ComputeLength(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "vec3.computeLength";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, vec3, false) == true) {
					auto length = vec3.computeLength();
					returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec3ComputeLength(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodVec3ComputeLengthSquared: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodVec3ComputeLengthSquared(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "vec3.computeLengthSquared";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.computeLengthSquared());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec3ComputeLengthSquared(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodVec3ComputeDotProduct: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodVec3ComputeDotProduct(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "vec3.computeDotProduct";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 a;
				Vector3 b;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 0, a, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 1, b, false) == true) {
					returnValue.setValue(Vector3::computeDotProduct(a, b));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec3ComputeDotProduct(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodVec3ComputeCrossProduct: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodVec3ComputeCrossProduct(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "vec3.computeCrossProduct";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 a;
				Vector3 b;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 0, a, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 1, b, false) == true) {
					auto result = Vector3::computeCrossProduct(a, b);
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec3ComputeCrossProduct(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodVec3Normalize: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodVec3Normalize(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "vec3.normalize";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 0, vec3, false) == true) {
					auto length = vec3.computeLength();
					auto result = length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector3(0.0f, 0.0f, 0.0f):vec3.normalize();
					returnValue.setType(TYPE_VECTOR3);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec3Normalize(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodVec3ComputeAngle: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodVec3ComputeAngle(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "n", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "vec3.computeAngle";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 a;
				Vector3 b;
				Vector3 n;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 0, a, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 1, b, false) == true &&
					MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 2, n, false) == true) {
					returnValue.setValue(Vector3::computeAngle(a, b, n));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec3ComputeAngle(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodVec3GetX: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodVec3GetX(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "vec3.getX";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getX());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec3GetX(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodVec3GetY: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodVec3GetY(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "vec3.getY";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getY());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec3GetY(miniScript, TYPE_VECTOR3));
	}
	{
		//
		class ScriptMethodVec3GetZ: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::ScriptVariableType TYPE_VECTOR3;
		public:
			ScriptMethodVec3GetZ(
				MiniScript* miniScript,
				MiniScript::ScriptVariableType TYPE_VECTOR3
			):
				MiniScript::ScriptMethod(
					{
						{ .type = TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR3(TYPE_VECTOR3) {
				//
			}
			const string getMethodName() override {
				return "vec3.getZ";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3,  argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getZ());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec3GetZ(miniScript, TYPE_VECTOR3));
	}
}

void MiniScriptVector3::unsetScriptVariableValue(MiniScript::MiniScript::ScriptVariable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Vector3*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptVector3::setScriptVariableValue(MiniScript::MiniScript::ScriptVariable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Vector3 vector3Value;
	if (value != 0ll) {
		vector3Value = *static_cast<const Vector3*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Vector3*>((void*)variable.getValuePtr()) = vector3Value;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Vector3(vector3Value)));
}

void MiniScriptVector3::copyScriptVariable(MiniScript::MiniScript::ScriptVariable& to, const MiniScript::MiniScript::ScriptVariable& from) const {
	//
	Vector3 vector3Value;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		vector3Value = *static_cast<Vector3*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(getType());
	to.setType(TYPE_VECTOR3);
	*static_cast<Vector3*>((void*)to.getValuePtr()) = vector3Value;
}

bool MiniScriptVector3::mul(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(getType());
	// vector3
	if (MiniScript::hasType(argumentValues, TYPE_VECTOR3) == true) {
		float f;
		// a
		Vector3 a;
		if (argumentValues[0].getType() == TYPE_VECTOR3) {
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, a, false);
		} else
		if (MiniScript::getFloatValue(argumentValues, 0, f, false) == true) {
			a = Vector3(f, f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
			miniScript->startErrorScript();
			return false;
		}
		// b
		Vector3 b;
		if (argumentValues[1].getType() == TYPE_VECTOR3) {
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, b, false);
		} else
		if (MiniScript::getFloatValue(argumentValues, 1, f, false) == true) {
			b = Vector3(f, f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
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

bool MiniScriptVector3::div(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(getType());
	// vector3
	if (argumentValues[0].getType() == TYPE_VECTOR3) {
		Vector3 a;
		Vector3 b;
		float f;
		// a
		MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, a, false);
		// b
		if (argumentValues[1].getType() == TYPE_VECTOR3 &&
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, b, false) == true) {
			// nop
		} else
		if (MiniScript::getFloatValue(argumentValues, 1, f, false) == true) {
			b = Vector3(f, f, f);
		} else {
			Console::println("div(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("div"));
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

bool MiniScriptVector3::add(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(getType());
	// vector3
	if (MiniScript::hasType(argumentValues, TYPE_VECTOR3) == true) {
		Vector3 a;
		Vector3 b;
		if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, a, false) == true &&
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, b, false) == true) {
			auto result = a.clone().add(b);
			returnValue.setType(TYPE_VECTOR3);
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

bool MiniScriptVector3::sub(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const {
	const auto TYPE_VECTOR3 = static_cast<MiniScript::ScriptVariableType>(getType());
	// vector3
	if (MiniScript::hasType(argumentValues, TYPE_VECTOR3) == true) {
		Vector3 a;
		Vector3 b;
		if (MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 0, a, false) == true &&
			MiniScriptVector3::getVector3Value(TYPE_VECTOR3, argumentValues, 1, b, false) == true) {
			auto result = a.clone().sub(b);
			returnValue.setType(TYPE_VECTOR3);
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

const string& MiniScriptVector3::getClassName() const {
	return CLASS_NAME;
}

const string& MiniScriptVector3::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptVector3::getValueAsString(const MiniScript::MiniScript::ScriptVariable& variable) const {
	//
	Vector3 vector3Value;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		vector3Value = *static_cast<Vector3*>((void*)variable.getValuePtr());
	}
	//
	return
		"Vector3(" +
		to_string(vector3Value.getX()) + ", " +
		to_string(vector3Value.getY()) + ", " +
		to_string(vector3Value.getZ()) + ")";

}

