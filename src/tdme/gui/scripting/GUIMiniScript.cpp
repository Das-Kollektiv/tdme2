#include <tdme/gui/scripting/GUIMiniScript.h>

#include <span>
#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/nodes/GUIVideoNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MutableString.h>

using std::span;
using std::string;
using std::to_string;

using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::nodes::GUIVideoNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
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
		class ScriptMethodGUIScreenGoto: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIScreenGoto(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "fileName", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "arguments", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.screen.goto";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string fileName;
				if (argumentValues.size() > 2 ||
					MiniScript::getStringValue(argumentValues, 0, fileName, false) == false) {
					Console::println("ScriptMethodGUIScreenGoto::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: optional mixed expected");
					miniScript->startErrorScript();
				} else {
					// delete next screen node if given
					if (miniScript->nextScreenNode != nullptr) {
						delete miniScript->nextScreenNode;
						miniScript->nextScreenNode = nullptr;
					}
					// setup next screen node
					try {
						miniScript->nextScreenNode = GUIParser::parse(
							FileSystem::getInstance()->getPathName(fileName),
							FileSystem::getInstance()->getFileName(fileName),
							{},
							argumentValues.size() == 2?argumentValues[1]:MiniScript::ScriptVariable()
						);
					} catch (Exception& exception) {
						Console::println("ScriptMethodGUIScreenGoto::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": an error occurred with goto screen to '" + fileName + "': " + string(exception.what()));
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIScreenGoto(this));
	}
	{
		//
		class ScriptMethodGUIScreenPush: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIScreenPush(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "fileName", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "arguments", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.screen.push";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string fileName;
				if (argumentValues.size() > 2 ||
					MiniScript::getStringValue(argumentValues, 0, fileName, false) == false) {
					Console::println("ScriptMethodGUIScreenPush::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: optional mixed expected");
					miniScript->startErrorScript();
				} else {
					// push screen node
					try {
						auto screenNode = GUIParser::parse(
							FileSystem::getInstance()->getPathName(fileName),
							FileSystem::getInstance()->getFileName(fileName),
							{},
							argumentValues.size() == 2?argumentValues[1]:MiniScript::ScriptVariable()
						);
						miniScript->screenNode->getGUI()->addScreen(screenNode->getId(), screenNode);
						miniScript->screenNode->getGUI()->addRenderScreen(screenNode->getId());
					} catch (Exception& exception) {
						Console::println("ScriptMethodGUIScreenPush::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": an error occurred with pushing screen '" + fileName + "': " + string(exception.what()));
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIScreenPush(this));
	}
	{
		//
		class ScriptMethodGUIScreenPop: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIScreenPop(GUIMiniScript* miniScript):
				ScriptMethod(
					{},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				// mark as popped
				return "gui.screen.pop";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				miniScript->popped = true;
			}
		};
		registerMethod(new ScriptMethodGUIScreenPop(this));
	}
	{
		//
		class ScriptMethodGUIScreenCall: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIScreenCall(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "screenId", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "function", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.screen.call";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string screenId;
				string function;
				if (miniScript->getStringValue(argumentValues, 0, screenId) == false ||
					miniScript->getStringValue(argumentValues, 1, function) == false) {
					Console::println("ScriptMethodGUIScreenCall::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto screen = miniScript->screenNode->getGUI()->getScreen(screenId);
					auto screenMiniScript = screen != nullptr?screen->getMiniScript():nullptr;
					auto scriptIdx = screenMiniScript != nullptr?screenMiniScript->getFunctionScriptIdx(function):SCRIPTIDX_NONE;
					if (screen == nullptr) {
						Console::println("ScriptMethodGUIScreenCall::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": screen not found: " + screenId);
						miniScript->startErrorScript();
					} else
					if (screenMiniScript == nullptr) {
						Console::println("ScriptMethodGUIScreenCall::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": screen mini script not found for given screen: " + screenId);
						miniScript->startErrorScript();
					} else
					if (scriptIdx == SCRIPTIDX_NONE) {
						Console::println("ScriptMethodGUIScreenCall::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": screen: " + screenId + ", function not found: " + function);
						miniScript->startErrorScript();
					} else {
						#if defined (__APPLE__)
							// MACOSX currently does not support initializing span using begin and end iterators,
							// so we need to make a copy of argumentValues beginning from second element
							vector<ScriptVariable> callArgumentValues;
							for (auto i = 2; i < argumentValues.size(); i++) callArgumentValues.push_back(argumentValues[i]);
							// call
							span callArgumentValuesSpan(callArgumentValues);
							screenMiniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
						#else
							span callArgumentValuesSpan(argumentValues.begin() + 2, argumentValues.end());
							screenMiniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
						#endif
					}
				}
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodGUIScreenCall(this));
	}
	{
		//
		class ScriptMethodScreenNodeGetId: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodScreenNodeGetId(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.screennode.getId";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->screenNode->getId());
			}
		};
		registerMethod(new ScriptMethodScreenNodeGetId(this));
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
						{ .type = ScriptVariableType::TYPE_STRING, .name = "nodeId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.node.controller.getValue";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string nodeId;
				if (MiniScript::getStringValue(argumentValues, 0, nodeId, false) == false) {
					Console::println("ScriptMethodGUINodeControllerSetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
				} else {
					auto node = miniScript->screenNode->getNodeById(nodeId);
					auto controller = node != nullptr?node->getController():nullptr;
					if (controller != nullptr) {
						returnValue.setValue(controller->getValue().getString());
					} else {
						Console::println("ScriptMethodGUINodeControllerSetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no node controller found for given node id '" + nodeId + "'");
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
						{ .type = ScriptVariableType::TYPE_STRING, .name = "nodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "value", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.node.controller.setValue";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string nodeId;
				string value;
				if (MiniScript::getStringValue(argumentValues, 0, nodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, value, false) == false) {
					Console::println("ScriptMethodGUINodeControllerSetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto node = miniScript->screenNode->getNodeById(nodeId);
					auto controller = node != nullptr?node->getController():nullptr;
					if (controller != nullptr) {
						controller->setValue(MutableString(value));
					} else {
						Console::println("ScriptMethodGUINodeControllerSetValue::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no node controller found for given node id '" + nodeId + "'");
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
	{
		//
		class ScriptMethodGUIImageNodeGetSource: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIImageNodeGetSource(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "imageNodeId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.imagenode.getSource";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string imageNodeId;
				if (MiniScript::getStringValue(argumentValues, 0, imageNodeId, false) == false) {
					Console::println("ScriptMethodGUIImageNodeGetSource::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
				} else {
					auto imageNode = dynamic_cast<GUIImageNode*>(miniScript->screenNode->getNodeById(imageNodeId));
					if (imageNode != nullptr) {
						returnValue.setValue(imageNode->getSource());
					} else {
						Console::println("ScriptMethodGUIImageNodeGetSource::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no image node found for given image node id '" + imageNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIImageNodeGetSource(this));
	}
	{
		//
		class ScriptMethodGUIImageNodeSetSource: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIImageNodeSetSource(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "imageNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "source", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.imagenode.setSource";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string imageNodeId;
				string source;
				if (MiniScript::getStringValue(argumentValues, 0, imageNodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, source, false) == false) {
					Console::println("ScriptMethodGUIImageNodeSetSource::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto imageNode = dynamic_cast<GUIImageNode*>(miniScript->screenNode->getNodeById(imageNodeId));
					if (imageNode != nullptr) {
						imageNode->setSource(source);
					} else {
						Console::println("ScriptMethodGUIImageNodeSetSource::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no image node found for given image node id '" + imageNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIImageNodeSetSource(this));
	}
	{
		//
		class ScriptMethodGUIVideoNodeGetSource: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIVideoNodeGetSource(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "videoNodeId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.videonode.getSource";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string videoNodeId;
				if (MiniScript::getStringValue(argumentValues, 0, videoNodeId, false) == false) {
					Console::println("ScriptMethodGUIVideoNodeGetSource::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
				} else {
					auto videoNode = dynamic_cast<GUIVideoNode*>(miniScript->screenNode->getNodeById(videoNodeId));
					if (videoNode != nullptr) {
						returnValue.setValue(videoNode->getSource());
					} else {
						Console::println("ScriptMethodGUIVideoNodeGetSource::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no video node found for given video node id '" + videoNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIVideoNodeGetSource(this));
	}
	{
		//
		class ScriptMethodGUIVideoNodeSetSource: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIVideoNodeSetSource(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "videoNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "source", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.videonode.setSource";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string videoNodeId;
				string source;
				if (MiniScript::getStringValue(argumentValues, 0, videoNodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, source, false) == false) {
					Console::println("ScriptMethodGUIVideoNodeSetSource::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto videoNode = dynamic_cast<GUIVideoNode*>(miniScript->screenNode->getNodeById(videoNodeId));
					if (videoNode != nullptr) {
						videoNode->setSource(source);
					} else {
						Console::println("ScriptMethodGUIVideoNodeSetSource::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no video node found for given video node id '" + videoNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIVideoNodeSetSource(this));
	}
	{
		//
		class ScriptMethodGUIParentNodeClearSubNodes: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIParentNodeClearSubNodes(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "parentNodeId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.parentnode.clearSubNodes";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string parentNodeId;
				if (MiniScript::getStringValue(argumentValues, 0, parentNodeId, false) == false) {
					Console::println("ScriptMethodGUIParentNodeClearSubNodes::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
				} else {
					auto parentNode = dynamic_cast<GUIParentNode*>(miniScript->screenNode->getNodeById(parentNodeId));
					if (parentNode != nullptr) {
						parentNode->clearSubNodes();
					} else {
						Console::println("ScriptMethodGUIParentNodeClearSubNodes::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no parent node found for given parent node id '" + parentNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIParentNodeClearSubNodes(this));
	}
	{
		//
		class ScriptMethodGUIParentNodeAddSubNodes: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIParentNodeAddSubNodes(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "parentNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "xml", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "resetScrollOffsets", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.parentnode.addSubNodes";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string parentNodeId;
				string xml;
				bool resetScrollOffsets = true;
				if (MiniScript::getStringValue(argumentValues, 0, parentNodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, xml, false) == false ||
					MiniScript::getBooleanValue(argumentValues, 2, resetScrollOffsets, true) == false) {
					Console::println("ScriptMethodGUIParentNodeAddSubNodes::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto parentNode = dynamic_cast<GUIParentNode*>(miniScript->screenNode->getNodeById(parentNodeId));
					if (parentNode != nullptr) {
						parentNode->addSubNodes(xml, resetScrollOffsets);
					} else {
						Console::println("ScriptMethodGUIParentNodeAddSubNodes::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no parent node found for given parent node id '" + parentNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIParentNodeAddSubNodes(this));
	}
	{
		//
		class ScriptMethodGUIParentNodeReplaceSubNodes: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIParentNodeReplaceSubNodes(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "parentNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "xml", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "resetScrollOffsets", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.parentnode.replaceSubNodes";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string parentNodeId;
				string xml;
				bool resetScrollOffsets = true;
				if (MiniScript::getStringValue(argumentValues, 0, parentNodeId, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, xml, false) == false ||
					MiniScript::getBooleanValue(argumentValues, 2, resetScrollOffsets, true) == false) {
					Console::println("ScriptMethodGUIParentNodeReplaceSubNodes::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: string expected");
					miniScript->startErrorScript();
				} else {
					auto parentNode = dynamic_cast<GUIParentNode*>(miniScript->screenNode->getNodeById(parentNodeId));
					if (parentNode != nullptr) {
						parentNode->replaceSubNodes(xml, resetScrollOffsets);
					} else {
						Console::println("ScriptMethodGUIParentNodeReplaceSubNodes::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no parent node found for given parent node id '" + parentNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
		};
		registerMethod(new ScriptMethodGUIParentNodeReplaceSubNodes(this));
	}
}

void GUIMiniScript::registerVariables() {
}

