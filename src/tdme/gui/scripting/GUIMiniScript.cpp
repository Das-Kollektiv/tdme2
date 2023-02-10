#include <tdme/gui/scripting/GUIMiniScript.h>

#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using std::span;
using std::string;
using std::to_string;

using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::scripting::GUIMiniScript;


GUIMiniScript::GUIMiniScript(GUIScreenNode* screenNode): MiniScript(), screenNode(screenNode) {
}

GUIMiniScript::~GUIMiniScript() {
}

void GUIMiniScript::registerStateMachineStates() {
	MiniScript::registerStateMachineStates();
}

void GUIMiniScript::registerMethods() {
	MiniScript::registerMethods();
	{
		//
		class ScriptMethodGUIGetId: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIGetId(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "screen.getId";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->screenNode->getId());
			}
		};
		registerMethod(new ScriptMethodGUIGetId(this));
	}
}

void GUIMiniScript::registerVariables() {
}

