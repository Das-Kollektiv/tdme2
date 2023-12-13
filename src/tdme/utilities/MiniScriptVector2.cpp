#include <span>
#include <string>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector2.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MiniScriptVector2.h>

using std::span;
using std::string;

using miniscript::miniscript::MiniScript;

using tdme::math::Vector2;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::utilities::MiniScriptVector2;

const string MiniScriptVector2::TYPE_NAME = "Vector2";

void MiniScriptVector2::registerMethods(MiniScript* miniScript) const {
	const auto TYPE_VECTOR2 = static_cast<MiniScript::VariableType>(getType());
	{
		//
		class ScriptMethodVec2: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_VECTOR2;
		public:
			ScriptMethodVec2(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_VECTOR2
			):
				MiniScript::Method(
					{
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR2
				),
				miniScript(miniScript),
				TYPE_VECTOR2(TYPE_VECTOR2) {
				//
			}
			const string getMethodName() override {
				return "Vector2";
			}
			void executeMethod(span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					auto result = Vector2(xValue, yValue);
					returnValue.setType(TYPE_VECTOR2);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec2(miniScript, TYPE_VECTOR2));
	}
	{
		//
		class ScriptMethodVec2ComputeLength: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_VECTOR2;
		public:
			ScriptMethodVec2ComputeLength(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_VECTOR2
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vec2", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR2(TYPE_VECTOR2) {
				//
			}
			const string getMethodName() override {
				return "Vector2::computeLength";
			}
			void executeMethod(span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 vec2;
				if (MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 0, vec2, false) == true) {
					auto length = vec2.computeLength();
					returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec2ComputeLength(miniScript, TYPE_VECTOR2));
	}
	{
		//
		class ScriptMethodVec2ComputeLengthSquared: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_VECTOR2;
		public:
			ScriptMethodVec2ComputeLengthSquared(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_VECTOR2
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vec2", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR2(TYPE_VECTOR2) {
				//
			}
			const string getMethodName() override {
				return "Vector2::computeLengthSquared";
			}
			void executeMethod(span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 vec2;
				if (MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 0, vec2, false) == true) {
					returnValue.setValue(vec2.computeLengthSquared());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec2ComputeLengthSquared(miniScript, TYPE_VECTOR2));
	}
	{
		//
		class ScriptMethodVec2ComputeDotProduct: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_VECTOR2;
		public:
			ScriptMethodVec2ComputeDotProduct(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_VECTOR2
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR2, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR2(TYPE_VECTOR2) {
				//
			}
			const string getMethodName() override {
				return "Vector2::computeDotProduct";
			}
			void executeMethod(span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 a;
				Vector2 b;
				if (MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 0, a, false) == true &&
					MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 1, b, false) == true) {
					returnValue.setValue(Vector2::computeDotProduct(a, b));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec2ComputeDotProduct(miniScript, TYPE_VECTOR2));
	}
	{
		//
		class ScriptMethodVec2Normalize: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_VECTOR2;
		public:
			ScriptMethodVec2Normalize(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_VECTOR2
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vec2", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR2
				),
				miniScript(miniScript),
				TYPE_VECTOR2(TYPE_VECTOR2) {
				//
			}
			const string getMethodName() override {
				return "Vector2::normalize";
			}
			void executeMethod(span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 vec2;
				if (MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 0, vec2, false) == true) {
					auto length = vec2.computeLength();
					auto result = length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector2(0.0f, 0.0f):vec2.normalize();
					returnValue.setType(TYPE_VECTOR2);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec2Normalize(miniScript, TYPE_VECTOR2));
	}
	{
		//
		class ScriptMethodVec2GetX: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_VECTOR2;
		public:
			ScriptMethodVec2GetX(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_VECTOR2
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vec2", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR2(TYPE_VECTOR2) {
				//
			}
			const string getMethodName() override {
				return "Vector2::getX";
			}
			void executeMethod(span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 vec2;
				if (MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 0, vec2, false) == true) {
					returnValue.setValue(vec2.getX());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec2GetX(miniScript, TYPE_VECTOR2));
	}
	{
		//
		class ScriptMethodVec2GetY: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
			MiniScript::VariableType TYPE_VECTOR2;
		public:
			ScriptMethodVec2GetY(
				MiniScript* miniScript,
				MiniScript::VariableType TYPE_VECTOR2
			):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vec2", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript),
				TYPE_VECTOR2(TYPE_VECTOR2) {
				//
			}
			const string getMethodName() override {
				return "Vector2::getY";
			}
			void executeMethod(span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 vec2;
				if (MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 0, vec2, false) == true) {
					returnValue.setValue(vec2.getY());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodVec2GetY(miniScript, TYPE_VECTOR2));
	}
}

void MiniScriptVector2::unsetVariableValue(MiniScript::Variable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Vector2*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptVector2::setVariableValue(MiniScript::Variable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Vector2 vector2Value;
	if (value != 0ll) {
		vector2Value = *static_cast<const Vector2*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Vector2*>((void*)variable.getValuePtr()) = vector2Value;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Vector2(vector2Value)));
}

void MiniScriptVector2::copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const {
	//
	Vector2 vector2Value;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		vector2Value = *static_cast<Vector2*>((void*)from.getValuePtr());
	}
	//
	const auto TYPE_VECTOR2 = static_cast<MiniScript::VariableType>(getType());
	to.setType(TYPE_VECTOR2);
	*static_cast<Vector2*>((void*)to.getValuePtr()) = vector2Value;
}

bool MiniScriptVector2::mul(MiniScript* miniScript, const span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	const auto TYPE_VECTOR2 = static_cast<MiniScript::VariableType>(getType());
	//
	if (MiniScript::hasType(argumentValues, TYPE_VECTOR2) == true) {
		float f;
		// a
		Vector2 a;
		if (argumentValues[0].getType() == TYPE_VECTOR2) {
			MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 0, a, false);
		} else
		if (MiniScript::getFloatValue(argumentValues, 0, f, false) == true) {
			a = Vector2(f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
			miniScript->startErrorScript();
			//
			return false;
		}
		// b
		Vector2 b;
		if (argumentValues[1].getType() == TYPE_VECTOR2) {
			MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 1, b, false);
		} else
		if (MiniScript::getFloatValue(argumentValues, 1, f, false) == true) {
			b = Vector2(f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
			miniScript->startErrorScript();
			//
			return false;
		}
		//
		auto result = a.clone().scale(b);
		returnValue.setType(TYPE_VECTOR2);
		returnValue.setValue(&result);
		//
		return true;
	}
	//
	return false;
}

bool MiniScriptVector2::div(MiniScript* miniScript, const span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	const auto TYPE_VECTOR2 = static_cast<MiniScript::VariableType>(getType());
	//
	if (argumentValues[0].getType() == TYPE_VECTOR2) {
		Vector2 a;
		Vector2 b;
		float f;
		// a
		MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 0, a, false);
		// b
		if (argumentValues[1].getType() == TYPE_VECTOR2 &&
			MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 1, b, false) == true) {
			// nop
		} else
		if (MiniScript::getFloatValue(argumentValues, 1, f, false) == true) {
			b = Vector2(f, f);
		} else {
			Console::println("div(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("div"));
			miniScript->startErrorScript();
			//
			return false;
		}
		//
		auto result = a / b;
		returnValue.setType(TYPE_VECTOR2);
		returnValue.setValue(&result);
		//
		return true;
	}
	//
	return false;
}

bool MiniScriptVector2::add(MiniScript* miniScript, const span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	const auto TYPE_VECTOR2 = static_cast<MiniScript::VariableType>(getType());
	//
	if (MiniScript::hasType(argumentValues, TYPE_VECTOR2) == true) {
		Vector2 a;
		Vector2 b;
		if (MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 0, a, false) == true &&
			MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 1, b, false) == true) {
			//
			auto result = a.clone().add(b);
			returnValue.setType(TYPE_VECTOR2);
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

bool MiniScriptVector2::sub(MiniScript* miniScript, const span<MiniScript::Variable>& argumentValues, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	const auto TYPE_VECTOR2 = static_cast<MiniScript::VariableType>(getType());
	//
	if (MiniScript::hasType(argumentValues, TYPE_VECTOR2) == true) {
		Vector2 a;
		Vector2 b;
		if (MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 0, a, false) == true &&
			MiniScriptVector2::getVector2Value(TYPE_VECTOR2, argumentValues, 1, b, false) == true) {
			//
			auto result = a.clone().sub(b);
			returnValue.setType(TYPE_VECTOR2);
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

const string& MiniScriptVector2::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptVector2::getValueAsString(const MiniScript::Variable& variable) const {
	//
	Vector2 vector2Value;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		vector2Value = *static_cast<Vector2*>((void*)variable.getValuePtr());
	}
	//
	return
		"Vector2(" +
		to_string(vector2Value.getX()) + ", " +
		to_string(vector2Value.getY()) + ")";

}

