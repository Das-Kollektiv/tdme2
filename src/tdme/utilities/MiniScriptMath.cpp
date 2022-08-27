#include <span>

#include <tdme/tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMath.h>

using std::span;

using tdme::math::Math;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMath;

void MiniScriptMath::registerMethods(MiniScript* miniScript) {
	// operator methods
	{
		//
		class ScriptMethodAdd: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAdd(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_VOID), miniScript(miniScript) {}
			const string getMethodName() override {
				return "add";
			}
			void executeMethod(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
			}
			bool isVariadic() override {
				return true;
			}
			bool isMixedReturnValue() override {
				return true;
			}
			MiniScript::ScriptOperator getOperator() override {
				return MiniScript::OPERATOR_ADDITION;
			}
		};
		miniScript->registerMethod(new ScriptMethodAdd(miniScript));
	}
	{
		//
		class ScriptMethodSub: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSub(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_VOID), miniScript(miniScript) {}
			const string getMethodName() override {
				return "sub";
			}
			void executeMethod(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
			}
			bool isVariadic() override {
				return true;
			}
			bool isMixedReturnValue() override {
				return true;
			}
			MiniScript::ScriptOperator getOperator() override {
				return MiniScript::OPERATOR_SUBTRACTION;
			}
		};
		miniScript->registerMethod(new ScriptMethodSub(miniScript));
	}
	{
		//
		class ScriptMethodMul: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMul(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_VOID), miniScript(miniScript) {}
			const string getMethodName() override {
				return "mul";
			}
			void executeMethod(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
			}
			bool isVariadic() override {
				return true;
			}
			bool isMixedReturnValue() override {
				return true;
			}
			MiniScript::ScriptOperator getOperator() override {
				return MiniScript::OPERATOR_MULTIPLICATION;
			}
		};
		miniScript->registerMethod(new ScriptMethodMul(miniScript));
	}
	{
		//
		class ScriptMethodDiv: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodDiv(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_VOID), miniScript(miniScript) {}
			const string getMethodName() override {
				return "div";
			}
			void executeMethod(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
			}
			bool isVariadic() override {
				return true;
			}
			bool isMixedReturnValue() override {
				return true;
			}
			MiniScript::ScriptOperator getOperator() override {
				return MiniScript::OPERATOR_DIVISION;
			}
		};
		miniScript->registerMethod(new ScriptMethodDiv(miniScript));
	}
	// constants
	{
		//
		class ScriptMethodPi: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodPi(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.PI";
			}
			void executeMethod(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setValue(Math::PI);
			}
		};
		miniScript->registerMethod(new ScriptMethodPi(miniScript));
	}
	{
		//
		class ScriptMethodEpsilon: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEpsilon(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.EPSILON";
			}
			void executeMethod(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setValue(Math::EPSILON);
			}
		};
		miniScript->registerMethod(new ScriptMethodEpsilon(miniScript));
	}
	{
		//
		class ScriptMethodEpsilon: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEpsilon(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.DEG2RAD";
			}
			void executeMethod(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setValue(Math::DEG2RAD);
			}
		};
		miniScript->registerMethod(new ScriptMethodEpsilon(miniScript));
	}
	{
		//
		class ScriptMethodEpsilon: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEpsilon(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_FLOAT), miniScript(miniScript) {}
			const string getMethodName() override {
				return "math.G";
			}
			void executeMethod(const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setValue(Math::G);
			}
		};
		miniScript->registerMethod(new ScriptMethodEpsilon(miniScript));
	}
}
