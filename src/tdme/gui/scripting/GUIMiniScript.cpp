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
					ScriptVariableType::TYPE_VOID
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
	{
		//
		class ScriptMethodGUIElementNodeConditionsHas: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIElementNodeConditionsHas(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "condition", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.has";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				string condition;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, condition, false) == false) {
					Console::println("ScriptMethodGUIElementNodeConditionsHas::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						returnValue.setValue(elementNode->getActiveConditions().has(condition));
					} else {
						Console::println("ScriptMethodGUIElementNodeConditionsHas::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIElementNodeConditionsHas(this));
	}
	{
		//
		class ScriptMethodGUIElementNodeConditionsGet: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIElementNodeConditionsGet(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.get";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false) {
					Console::println("ScriptMethodGUIElementNodeConditionsGet::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						auto conditions = elementNode->getActiveConditions().getConditions();
						returnValue.setType(TYPE_ARRAY);
						for (auto& condition: conditions) {
							returnValue.pushArrayValue(condition);
						}
					} else {
						Console::println("ScriptMethodGUIElementNodeConditionsGet::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIElementNodeConditionsGet(this));
	}
	{
		//
		class ScriptMethodGUIElementNodeConditionsSet: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIElementNodeConditionsSet(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "condition", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.set";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				string condition;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, condition, false) == false) {
					Console::println("ScriptMethodGUIElementNodeConditionsSet::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().set(condition);
					} else {
						Console::println("ScriptMethodGUIElementNodeConditionsSet::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIElementNodeConditionsSet(this));
	}
	{
		//
		class ScriptMethodGUIElementNodeConditionsAdd: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIElementNodeConditionsAdd(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "condition", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.add";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				string condition;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, condition, false) == false) {
					Console::println("ScriptMethodGUIElementNodeConditionsAdd::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().add(condition);
					} else {
						Console::println("ScriptMethodGUIElementNodeConditionsAdd::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIElementNodeConditionsAdd(this));
	}
	{
		//
		class ScriptMethodGUIElementNodeConditionsSetAll: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIElementNodeConditionsSetAll(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "conditions", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.setAll";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false ||
					argumentValues.size() <= 1 || argumentValues[1].getType() != ScriptVariableType::TYPE_ARRAY) {
					Console::println("ScriptMethodGUIElementNodeConditionsSetAll::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: array of string expected");
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						vector<string> conditions;
						for (auto i = 0; i < argumentValues[1].getArraySize(); i++) {
							string condition;
							if (argumentValues[1].getArrayValue(i).getStringValue(condition, false) == false) {
								Console::println("ScriptMethodGUIElementNodeConditionsSet::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 1: array of strings expected");
							} else {
								conditions.push_back(condition);
							}
						}
						elementNode->getActiveConditions().set(conditions);
					} else {
						Console::println("ScriptMethodGUIElementNodeConditionsSetAll::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIElementNodeConditionsSetAll(this));
	}
	{
		//
		class ScriptMethodGUIElementNodeConditionsRemove: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIElementNodeConditionsRemove(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "condition", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.remove";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				string condition;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, condition, false) == false) {
					Console::println("ScriptMethodGUIElementNodeConditionsRemove::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().remove(condition);
					} else {
						Console::println("ScriptMethodGUIElementNodeConditionsRemove::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIElementNodeConditionsRemove(this));
	}
	{
		//
		class ScriptMethodGUIElementNodeConditionsRemoveAll: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIElementNodeConditionsRemoveAll(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.removeAll";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false) {
					Console::println("ScriptMethodGUIElementNodeConditionsRemoveAll::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().removeAll();
					} else {
						Console::println("ScriptMethodGUIElementNodeConditionsRemoveAll::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIElementNodeConditionsRemoveAll(this));
	}
}

void GUIMiniScript::registerVariables() {
}

