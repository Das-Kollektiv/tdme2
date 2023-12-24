#include <span>
#include <string>

#include <miniscript/miniscript/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/miniscript/MiniScriptVector4.h>

using std::span;
using std::string;

using miniscript::miniscript::MiniScript;

using tdme::math::Vector4;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::miniscript::MiniScriptVector4;

const string MiniScriptVector4::TYPE_NAME = "Vector4";

MiniScript::VariableType MiniScriptVector4::TYPE_VECTOR4 = MiniScript::TYPE_NULL;

void MiniScriptVector4::initialize() {
	TYPE_VECTOR4 = static_cast<MiniScript::VariableType>(MiniScript::getDataTypeByClassName("Vector4")->getType());
}

void MiniScriptVector4::registerMethods(MiniScript* miniScript) const {
	{
		//
		class MethodVec4: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec4(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "z", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::VariableType::TYPE_FLOAT, .name = "w", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR4
				),
				miniScript(miniScript) {
				//
			}

			const string getMethodName() override {
				return "Vector4";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(arguments, 0, xValue, false) == true &&
					MiniScript::getFloatValue(arguments, 1, yValue, false) == true &&
					MiniScript::getFloatValue(arguments, 2, zValue, false) == true &&
					MiniScript::getFloatValue(arguments, 3, wValue, false) == true) {
					auto result = Vector4(xValue, yValue, zValue, wValue);
					returnValue.setType(TYPE_VECTOR4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec4(miniScript));
	}
	{
		//
		class MethodVec4ComputeLength: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec4ComputeLength(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::computeLength";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector4 vec4;
				if (MiniScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					auto length = vec4.computeLength();
					returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec4ComputeLength(miniScript));
	}
	{
		//
		class MethodVec4ComputeLengthSquared: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec4ComputeLengthSquared(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::computeLengthSquared";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector4 vec4;
				if (MiniScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					returnValue.setValue(vec4.computeLengthSquared());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec4ComputeLengthSquared(miniScript));
	}
	{
		//
		class MethodVec4ComputeDotProduct: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec4ComputeDotProduct(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR4, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::computeDotProduct";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector4 a;
				Vector4 b;
				if (MiniScriptVector4::getVector4Value(arguments, 0, a, false) == true &&
					MiniScriptVector4::getVector4Value(arguments, 1, b, false) == true) {
					returnValue.setValue(Vector4::computeDotProduct(a, b));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec4ComputeDotProduct(miniScript));
	}
	{
		//
		class MethodVec4Normalize: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec4Normalize(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false },
					},
					TYPE_VECTOR4
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::normalize";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector4 vec4;
				if (MiniScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					auto length = vec4.computeLength();
					auto result = length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector4(0.0f, 0.0f, 0.0f, 0.0f):vec4.normalize();
					returnValue.setType(TYPE_VECTOR4);
					returnValue.setValue(&result);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec4Normalize(miniScript));
	}
	{
		//
		class MethodVec4GetX: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec4GetX(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::getX";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector4 vec4;
				if (MiniScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getX());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec4GetX(miniScript));
	}
	{
		//
		class MethodVec4GetY: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec4GetY(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::getY";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector4 vec4;
				if (MiniScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getY());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec4GetY(miniScript));
	}
	{
		//
		class MethodVec4GetZ: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec4GetZ(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::getZ";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector4 vec4;
				if (MiniScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getZ());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec4GetZ(miniScript));
	}
	{
		//
		class MethodVec4GetW: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodVec4GetW(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = TYPE_VECTOR4, .name = "vector4", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "Vector4::getW";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				Vector4 vec4;
				if (MiniScriptVector4::getVector4Value(arguments, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getW());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodVec4GetW(miniScript));
	}
}

void MiniScriptVector4::unsetVariableValue(MiniScript::Variable& variable) const {
	if (variable.getType() != getType()) return;
	if (variable.getValuePtr() == 0ll) return;
	//
	delete static_cast<Vector4*>((void*)variable.getValuePtr());
	variable.setValuePtr(0ll);
}

void MiniScriptVector4::setVariableValue(MiniScript::Variable& variable, const void* value) const {
	if (variable.getType() != getType()) return;
	//
	Vector4 vector4Value;
	if (value != 0ll) {
		vector4Value = *static_cast<const Vector4*>(value);
	}
	//
	if (variable.getValuePtr() != 0ll) {
		*static_cast<Vector4*>((void*)variable.getValuePtr()) = vector4Value;
		return;
	}
	//
	variable.setValuePtr((uint64_t)(new Vector4(vector4Value)));
}

void MiniScriptVector4::copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const {
	//
	Vector4 vector4Value;
	if (from.getType() == getType() && from.getValuePtr() != 0ll) {
		vector4Value = *static_cast<Vector4*>((void*)from.getValuePtr());
	}
	//
	to.setType(static_cast<MiniScript::VariableType>(getType()));
	*static_cast<Vector4*>((void*)to.getValuePtr()) = vector4Value;
}

bool MiniScriptVector4::mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	//
	if (MiniScript::hasType(arguments, TYPE_VECTOR4) == true) {
		float f;
		// a
		Vector4 a;
		if (arguments[0].getType() == TYPE_VECTOR4) {
			MiniScriptVector4::getVector4Value(arguments, 0, a, false);
		} else
		if (MiniScript::getFloatValue(arguments, 0, f, false) == true) {
			a = Vector4(f, f, f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
			miniScript->startErrorScript();
			//
			return false;
		}
		// b
		Vector4 b;
		if (arguments[1].getType() == TYPE_VECTOR4) {
			MiniScriptVector4::getVector4Value(arguments, 1, b, false);
		} else
		if (MiniScript::getFloatValue(arguments, 1, f, false) == true) {
			b = Vector4(f, f, f, f);
		} else {
			Console::println("mul(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("mul"));
			miniScript->startErrorScript();
			//
			return false;
		}
		//
		auto result = a.clone().scale(b);
		returnValue.setType(TYPE_VECTOR4);
		returnValue.setValue(&result);
		//
		return true;
	}
	//
	return false;
}

bool MiniScriptVector4::div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	//
	if (arguments[0].getType() == TYPE_VECTOR4) {
		Vector4 a;
		Vector4 b;
		float f;
		// a
		MiniScriptVector4::getVector4Value(arguments, 0, a, false);
		// b
		if (arguments[1].getType() == TYPE_VECTOR4 &&
			MiniScriptVector4::getVector4Value(arguments, 1, b, false) == true) {
			// nop
		} else
		if (MiniScript::getFloatValue(arguments, 1, f, false) == true) {
			b = Vector4(f, f, f, f);
		} else {
			Console::println("div(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation("div"));
			miniScript->startErrorScript();
			//
			return false;
		}
		//
		auto result = a / b;
		returnValue.setType(TYPE_VECTOR4);
		returnValue.setValue(&result);
		//
		return true;

	}
	//
	return false;
}

bool MiniScriptVector4::add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	// vector4
	if (MiniScript::hasType(arguments, TYPE_VECTOR4) == true) {
		Vector4 a;
		Vector4 b;
		if (MiniScriptVector4::getVector4Value(arguments, 0, a, false) == true &&
			MiniScriptVector4::getVector4Value(arguments, 1, b, false) == true) {
			//
			auto result = a.clone().add(b);
			returnValue.setType(TYPE_VECTOR4);
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

bool MiniScriptVector4::sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	// vector4
	if (MiniScript::hasType(arguments, TYPE_VECTOR4) == true) {
		Vector4 a;
		Vector4 b;
		if (MiniScriptVector4::getVector4Value(arguments, 0, a, false) == true &&
			MiniScriptVector4::getVector4Value(arguments, 1, b, false) == true) {
			//
			auto result = a.clone().sub(b);
			returnValue.setType(TYPE_VECTOR4);
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

const string& MiniScriptVector4::getTypeAsString() const {
	return TYPE_NAME;
}

const string MiniScriptVector4::getValueAsString(const MiniScript::Variable& variable) const {
	//
	Vector4 vector4Value;
	if (variable.getType() == getType() && variable.getValuePtr() != 0ll) {
		vector4Value = *static_cast<Vector4*>((void*)variable.getValuePtr());
	}
	//
	return
		"Vector4(" +
		to_string(vector4Value.getX()) + ", " +
		to_string(vector4Value.getY()) + ", " +
		to_string(vector4Value.getZ()) + ", " +
		to_string(vector4Value.getW()) + ")";

}

