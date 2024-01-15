#include <span>
#include <string>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector2.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/miniscript/MiniScriptVector2.h>

using std::span;
using std::string;

using miniscript::miniscript::MiniScript;

using tdme::math::Vector2;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::miniscript::MiniScriptVector2;

const string MiniScriptVector2::TYPE_NAME = "Vector2";

MiniScript::VariableType MiniScriptVector2::TYPE_VECTOR2 = MiniScript::TYPE_NULL;

void MiniScriptVector2::initialize() {
	TYPE_VECTOR2 = MiniScript::getDataTypeByClassName("Vector2")->getType();
}

void MiniScriptVector2::registerConstants(MiniScript* miniScript) const {
}

void MiniScriptVector2::registerMethods(MiniScript* miniScript) const {
	{
		//
		class MethodVec2: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec2(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR2
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(arguments, 0, xValue, false) == true &&
					MiniScript::getFloatValue(arguments, 1, yValue, false) == true) {
					auto result = Vector2(xValue, yValue);
					returnValue.setType(TYPE_VECTOR2);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec2(miniScript));
	}
	{
		//
		class MethodVec2ComputeLength: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec2ComputeLength(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vector2", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::computeLength";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 vec2;
				if (MiniScriptVector2::getVector2Value(arguments, 0, vec2, false) == true) {
					auto length = vec2.computeLength();
					returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec2ComputeLength(miniScript));
	}
	{
		//
		class MethodVec2ComputeLengthSquared: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec2ComputeLengthSquared(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vector2", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::computeLengthSquared";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 vec2;
				if (MiniScriptVector2::getVector2Value(arguments, 0, vec2, false) == true) {
					returnValue.setValue(vec2.computeLengthSquared());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec2ComputeLengthSquared(miniScript));
	}
	{
		//
		class MethodVec2ComputeDotProduct: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec2ComputeDotProduct(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR2, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::computeDotProduct";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 a;
				Vector2 b;
				if (MiniScriptVector2::getVector2Value(arguments, 0, a, false) == true &&
					MiniScriptVector2::getVector2Value(arguments, 1, b, false) == true) {
					returnValue.setValue(Vector2::computeDotProduct(a, b));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec2ComputeDotProduct(miniScript));
	}
	{
		//
		class MethodVec2Normalize: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec2Normalize(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vector2", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR2
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::normalize";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 vec2;
				if (MiniScriptVector2::getVector2Value(arguments, 0, vec2, false) == true) {
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
		miniScript->registerMethod(new MethodVec2Normalize(miniScript));
	}
	{
		//
		class MethodVec2GetX: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec2GetX(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vector2", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::getX";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 vec2;
				if (MiniScriptVector2::getVector2Value(arguments, 0, vec2, false) == true) {
					returnValue.setValue(vec2.getX());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec2GetX(miniScript));
	}
	{
		//
		class MethodVec2GetY: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec2GetY(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR2, .name = "vector2", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector2::getY";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector2 vec2;
				if (MiniScriptVector2::getVector2Value(arguments, 0, vec2, false) == true) {
					returnValue.setValue(vec2.getY());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec2GetY(miniScript));
	}
}

void MiniScriptVector2::unsetVariableValue(MiniScript::Variable& variable) const {
	delete static_cast<Vector2*>(variable.getValuePtr());
}

void MiniScriptVector2::setVariableValue(MiniScript::Variable& variable) const {
	variable.setValuePtr(new Vector2());
}

void MiniScriptVector2::setVariableValue(MiniScript::Variable& variable, const void* value) const {
	*static_cast<Vector2*>(variable.getValuePtr()) = *static_cast<const Vector2*>(value);
}

void MiniScriptVector2::copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const {
	to.setType(TYPE_VECTOR2);
	*static_cast<Vector2*>(to.getValuePtr()) = *static_cast<Vector2*>(from.getValuePtr());
}

bool MiniScriptVector2::mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	//
	if (MiniScript::hasType(arguments, TYPE_VECTOR2) == true) {
		float f;
		// a
		Vector2 a;
		if (arguments[0].getType() == TYPE_VECTOR2) {
			MiniScriptVector2::getVector2Value(arguments, 0, a, false);
		} else
		if (MiniScript::getFloatValue(arguments, 0, f, false) == true) {
			a = Vector2(f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
			miniScript->startErrorScript();
			//
			return false;
		}
		// b
		Vector2 b;
		if (arguments[1].getType() == TYPE_VECTOR2) {
			MiniScriptVector2::getVector2Value(arguments, 1, b, false);
		} else
		if (MiniScript::getFloatValue(arguments, 1, f, false) == true) {
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

bool MiniScriptVector2::div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	//
	if (arguments[0].getType() == TYPE_VECTOR2) {
		Vector2 a;
		Vector2 b;
		float f;
		// a
		MiniScriptVector2::getVector2Value(arguments, 0, a, false);
		// b
		if (arguments[1].getType() == TYPE_VECTOR2 &&
			MiniScriptVector2::getVector2Value(arguments, 1, b, false) == true) {
			// nop
		} else
		if (MiniScript::getFloatValue(arguments, 1, f, false) == true) {
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

bool MiniScriptVector2::add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	//
	if (MiniScript::hasType(arguments, TYPE_VECTOR2) == true) {
		Vector2 a;
		Vector2 b;
		if (MiniScriptVector2::getVector2Value(arguments, 0, a, false) == true &&
			MiniScriptVector2::getVector2Value(arguments, 1, b, false) == true) {
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

bool MiniScriptVector2::sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	//
	if (MiniScript::hasType(arguments, TYPE_VECTOR2) == true) {
		Vector2 a;
		Vector2 b;
		if (MiniScriptVector2::getVector2Value(arguments, 0, a, false) == true &&
			MiniScriptVector2::getVector2Value(arguments, 1, b, false) == true) {
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
	const auto& vector2 = *static_cast<Vector2*>(variable.getValuePtr());
	//
	return
		"Vector2(" +
		to_string(vector2.getX()) + ", " +
		to_string(vector2.getY()) + ")";
}

MiniScript::DataType::ScriptContext* MiniScriptVector2::createScriptContext() const {
	return nullptr;
}

void MiniScriptVector2::deleteScriptContext(ScriptContext* context) const {
}

void MiniScriptVector2::garbageCollection(ScriptContext* context) const {
}
