#include <tdme/gui/scripting/GUIMiniScript.h>

#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MutableString.h>

using std::span;
using std::string;
using std::to_string;

using tdme::gui::GUI;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::scripting::GUIMiniScript;
using tdme::utilities::MiniScript;
using tdme::utilities::MutableString;


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
		class ScriptMethodScreenGetId: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodScreenGetId(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "screen.getId";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->screenNode->getId());
			}
		};
		registerMethod(new ScriptMethodScreenGetId(this));
	}
	{
		//
		class ScriptMethodActionACTIONTYPE_PERFORMING: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodActionACTIONTYPE_PERFORMING(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "action.ACTIONTYPE_PERFORMING";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(static_cast<int64_t>(GUIActionListenerType::PERFORMING));
			}
		};
		registerMethod(new ScriptMethodActionACTIONTYPE_PERFORMING(this));
	}
	{
		//
		class ScriptMethodActionACTIONTYPE_PERFORMED: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodActionACTIONTYPE_PERFORMED(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "action.ACTIONTYPE_PERFORMED";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(static_cast<int64_t>(GUIActionListenerType::PERFORMED));
			}
		};
		registerMethod(new ScriptMethodActionACTIONTYPE_PERFORMED(this));
	}
	{
		//
		class ScriptMethodNodeControllerGetValue: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodNodeControllerGetValue(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "node.controller.getValue";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false) {
					Console::println("ScriptMethodNodeControllerGetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					auto controller = elementNode != nullptr?elementNode->getController():nullptr;
					if (controller != nullptr) {
						returnValue.setValue(controller->getValue().getString());
					} else {
						Console::println("ScriptMethodNodeControllerGetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no node controller found for given element node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodNodeControllerGetValue(this));
	}
	{
		//
		class ScriptMethodNodeControllerSetValue: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodNodeControllerSetValue(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "value", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "node.controller.setValue";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				string value;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, value, false) == false) {
					Console::println("ScriptMethodNodeControllerSetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					auto controller = elementNode != nullptr?elementNode->getController():nullptr;
					if (controller != nullptr) {
						controller->setValue(MutableString(value));
					} else {
						Console::println("ScriptMethodNodeControllerSetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no node controller found for given element node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodNodeControllerSetValue(this));
	}
}

void GUIMiniScript::registerVariables() {
}

