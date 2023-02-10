#include <tdme/gui/scripting/GUIMiniScript.h>

#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/nodes/GUIVideoNode.h>
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
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::nodes::GUIVideoNode;
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
				return "gui.screen.getId";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->screenNode->getId());
			}
		};
		registerMethod(new ScriptMethodScreenGetId(this));
	}
	{
		//
		class ScriptMethodGUIEventACTIONTYPE_PERFORMING: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIEventACTIONTYPE_PERFORMING(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.event.ACTIONTYPE_PERFORMING";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(static_cast<int64_t>(GUIActionListenerType::PERFORMING));
			}
		};
		registerMethod(new ScriptMethodGUIEventACTIONTYPE_PERFORMING(this));
	}
	{
		//
		class ScriptMethodGUIEventACTIONTYPE_PERFORMED: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIEventACTIONTYPE_PERFORMED(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.event.ACTIONTYPE_PERFORMED";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(static_cast<int64_t>(GUIActionListenerType::PERFORMED));
			}
		};
		registerMethod(new ScriptMethodGUIEventACTIONTYPE_PERFORMED(this));
	}
	{
		//
		class ScriptMethodGUINodeControllerGetValue: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUINodeControllerGetValue(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.node.controller.getValue";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false) {
					Console::println("ScriptMethodGUINodeControllerSetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					auto controller = elementNode != nullptr?elementNode->getController():nullptr;
					if (controller != nullptr) {
						returnValue.setValue(controller->getValue().getString());
					} else {
						Console::println("ScriptMethodGUINodeControllerSetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no node controller found for given element node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUINodeControllerGetValue(this));
	}
	{
		//
		class ScriptMethodGUINodeControllerSetValue: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUINodeControllerSetValue(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "value", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.node.controller.setValue";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				string value;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, value, false) == false) {
					Console::println("ScriptMethodGUINodeControllerSetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					auto controller = elementNode != nullptr?elementNode->getController():nullptr;
					if (controller != nullptr) {
						controller->setValue(MutableString(value));
					} else {
						Console::println("ScriptMethodGUINodeControllerSetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no node controller found for given element node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUINodeControllerSetValue(this));
	}
	{
		//
		class ScriptMethodGUITextNodeGetText: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUITextNodeGetText(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "textNodeId", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.textnode.getText";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string textNodeId;
				string text;
				if (MiniScript::getStringValue(argumentValues, 0, textNodeId, false) == false) {
					Console::println("ScriptMethodGUITextNodeGetText::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto textNode = dynamic_cast<GUITextNode*>(miniScript->screenNode->getNodeById(textNodeId));
					auto styledTextNode = textNode == nullptr?dynamic_cast<GUIStyledTextNode*>(miniScript->screenNode->getNodeById(textNodeId)):nullptr;
					if (textNode != nullptr) {
						returnValue.setValue(textNode->getText().getString());
					} else
					if (styledTextNode != nullptr) {
						returnValue.setValue(styledTextNode->getText().getString());
					} else {
						Console::println("ScriptMethodGUITextNodeGetText::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no text or styled text node found for given node id '" + textNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUITextNodeGetText(this));
	}
	{
		//
		class ScriptMethodGUITextNodeSetText: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUITextNodeSetText(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "textNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "text", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.textnode.setText";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string textNodeId;
				string text;
				if (MiniScript::getStringValue(argumentValues, 0, textNodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, text, false) == false) {
					Console::println("ScriptMethodGUITextNodeGetText::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto textNode = dynamic_cast<GUITextNode*>(miniScript->screenNode->getNodeById(textNodeId));
					auto styledTextNode = textNode == nullptr?dynamic_cast<GUIStyledTextNode*>(miniScript->screenNode->getNodeById(textNodeId)):nullptr;
					if (textNode != nullptr) {
						textNode->setText(MutableString(text));
					} else
					if (styledTextNode != nullptr) {
						styledTextNode->setText(MutableString(text));
					} else {
						Console::println("ScriptMethodGUITextNodeGetText::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no text or styled text node found for given node id '" + textNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUITextNodeSetText(this));
	}
}

void GUIMiniScript::registerVariables() {
}

