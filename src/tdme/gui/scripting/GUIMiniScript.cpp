#include <tdme/gui/scripting/GUIMiniScript.h>

#include <span>
#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/logics/Context.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicMiniScript.h>
#include <tdme/engine/logics/MiniScriptLogic.h>
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
#include <tdme/os/threading/Mutex.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MutableString.h>

using std::span;
using std::string;
using std::to_string;
using std::unordered_map;

using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::logics::LogicMiniScript;
using tdme::engine::logics::MiniScriptLogic;
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
using tdme::os::threading::Mutex;
using tdme::gui::scripting::GUIMiniScript;
using tdme::utilities::Character;
using tdme::utilities::Console;
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
	// input
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_LEFT: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_LEFT(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_LEFT";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_LEFT);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_LEFT(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_RIGHT: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_RIGHT(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_RIGHT";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_RIGHT);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_RIGHT(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_UP: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_UP(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_UP";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_UP);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_UP(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_DOWN: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_DOWN(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_DOWN";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_DOWN);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_DOWN(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_POS1: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_POS1(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_POS1";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_POS1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_POS1(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_END: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_END(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_END";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_END);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_END(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_PAGEUP: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_PAGEUP(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_PAGEUP";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_PAGE_UP);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_PAGEUP(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_PAGEDOWN: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_PAGEDOWN(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_PAGEDOWN";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_PAGE_DOWN);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_PAGEDOWN(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_BACKSPACE: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_BACKSPACE(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_BACKSPACE";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_BACKSPACE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_BACKSPACE(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_DELETE: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_DELETE(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_DELETE";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_DELETE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_DELETE(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_SPACE: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_SPACE(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_SPACE";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_SPACE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_SPACE(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_RETURN: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_RETURN(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_RETURN";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_RETURN);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_RETURN(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_ESCAPE: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_ESCAPE(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_ESCAPE";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_ESCAPE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_ESCAPE(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F1: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F1(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F1";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F1(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F2: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F2(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F2";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F2);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F2(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F3: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F3(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F3";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F3);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F3(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F4: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F4(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F4";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F4);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F4(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F5: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F5(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F5";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F5);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F5(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F6: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F6(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F6";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F6);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F6(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F7: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F7(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F7";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F7);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F7(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F8: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F8(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F8";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F8);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F8(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F9: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F9(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F9";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F9);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F9(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F10: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F10(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F10";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F10);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F10(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F11: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F11(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F11";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F11);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F11(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F12: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F12(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F12";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F12);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F12(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsKeyDown: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsKeyDown(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "keyCode", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isKeyDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t keyCode;
				if (miniScript->getIntegerValue(argumentValues, 0, keyCode) == true) {
					returnValue = miniScript->keyboardKeys.find(keyCode) != miniScript->keyboardKeys.end();
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsKeyDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsCharDown: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsCharDown(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "charAsString", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isCharDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string charAsString;
				if (miniScript->getStringValue(argumentValues, 0, charAsString) == true) {
					UTF8CharacterIterator u8It(charAsString);
					auto keyChar = u8It.hasNext() == true?u8It.next():-1;
					returnValue = miniScript->keyboardChars.find(keyChar) != miniScript->keyboardChars.end();
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsCharDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardGetTypedString: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardGetTypedString(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.getTypedString";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardTypedChars;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardGetTypedString(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsControlDown: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsControlDown(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isControlDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardControlDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsControlDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsMetaDown: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsMetaDown(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isMetaDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardControlDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsMetaDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsAltDown: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsAltDown(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isAltDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardAltDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsAltDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsShiftDown: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsShiftDown(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isShiftDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardShiftDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsShiftDown(this));
	}
	// mouse input
	{
		//
		class ScriptMethodInputMouseBUTTON_LEFT: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseBUTTON_LEFT(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_LEFT";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_LEFT - 1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseBUTTON_LEFT(this));
	}
	{
		//
		class ScriptMethodInputMouseBUTTON_MIDDLE: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseBUTTON_MIDDLE(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_MIDDLE";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_MIDDLE - 1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseBUTTON_MIDDLE(this));
	}
	{
		//
		class ScriptMethodInputMouseBUTTON_RIGHT: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseBUTTON_RIGHT(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_RIGHT";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_RIGHT - 1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseBUTTON_RIGHT(this));
	}
	{
		//
		class ScriptMethodInputMouseIsButtonDown: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseIsButtonDown(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "button", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.isButtonDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t button;
				if (miniScript->getIntegerValue(argumentValues, 0, button) == true) {
					returnValue = button >= 0 && button <= 3?miniScript->mouseDown[button]:false;
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseIsButtonDown(this));
	}
	{
		//
		class ScriptMethodInputMouseIsButtonUp: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseIsButtonUp(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "button", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.isButtonUp";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t button;
				if (miniScript->getIntegerValue(argumentValues, 0, button) == true) {
					returnValue = button >= 0 && button <= 3?miniScript->mouseUp[button]:false;
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseIsButtonUp(this));
	}
	{
		//
		class ScriptMethodInputMouseIsDragging: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseIsDragging(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "button", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.isDragging";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t button;
				if (miniScript->getIntegerValue(argumentValues, 0, button) == true) {
					returnValue = button >= 0 && button <= 3?miniScript->mouseDragging[button]:false;
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseIsDragging(this));
	}
	{
		//
		class ScriptMethodInputMouseHasMoved: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseHasMoved(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.hasMoved";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->mouseMoved;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseHasMoved(this));
	}
	{
		//
		class ScriptMethodInputMouseGetX: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetX(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getX";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseX);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetX(this));
	}
	{
		//
		class ScriptMethodInputMouseGetXUnscaled: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetXUnscaled(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getXUnscaled";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseXUnscaled);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetXUnscaled(this));
	}
	{
		//
		class ScriptMethodInputMouseGetY: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetY(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getY";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseY);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetY(this));
	}
	{
		//
		class ScriptMethodInputMouseGetYUnscaled: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetYUnscaled(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getYUnscaled";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseYUnscaled);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetYUnscaled(this));
	}
	{
		//
		class ScriptMethodInputMouseGetWheelX: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetWheelX(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelX";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->mouseWheelX;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetWheelX(this));
	}
	{
		//
		class ScriptMethodInputMouseGetWheelY: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetWheelY(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelY";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->mouseWheelY;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetWheelY(this));
	}
	{
		//
		class ScriptMethodInputMouseGetWheelZ: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetWheelZ(GUIMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelZ";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->mouseWheelZ;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetWheelZ(this));
	}
	// gui
	{
		//
		class ScriptMethodGUIScreenSetEnabled: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIScreenSetEnabled(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "screenId", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "enabled", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.screen.setEnabled";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string screenId;
				bool enabled;
				if (miniScript->getStringValue(argumentValues, 0, screenId, false) == false ||
					miniScript->getBooleanValue(argumentValues, 1, enabled, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto screen = miniScript->screenNode->getGUI()->getScreen(screenId);
					if (screen != nullptr) {
						screen->setEnabled(enabled);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no screen with given id: " + screenId);
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodGUIScreenSetEnabled(this));
	}
	{
		//
		class ScriptMethodGUIScreenIsEnabled: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodGUIScreenIsEnabled(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "screenId", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.screen.isEnabled";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string screenId;
				if (miniScript->getStringValue(argumentValues, 0, screenId, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto screen = miniScript->screenNode->getGUI()->getScreen(screenId);
					if (screen != nullptr) {
						returnValue.setValue(screen->isEnabled());
					} else {
						returnValue.setValue(false);
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodGUIScreenIsEnabled(this));
	}
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
						{ .type = ScriptVariableType::TYPE_MAP, .name = "variables", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "arguments", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.screen.goto";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string fileName;
				if (argumentValues.size() > 3 ||
					MiniScript::getStringValue(argumentValues, 0, fileName, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					// delete next screen node if given
					if (miniScript->nextScreenNode != nullptr) {
						delete miniScript->nextScreenNode;
						miniScript->nextScreenNode = nullptr;
					}
					// variables
					unordered_map<string, string> variables;
					if (argumentValues.size() >= 2) {
						auto mapPtr = argumentValues[1].getMapPointer();
						if (mapPtr != nullptr) {
							for (auto& mapIt: *mapPtr) {
								variables[mapIt.first] = mapIt.second.getValueString();
							}
						}
					}
					// setup next screen node
					try {
						string screenPathName;
						string screenFileName;
						miniScript->screenNode->getProjectFilePathNameAndFileName(fileName, screenPathName, screenFileName);
						//
						miniScript->nextScreenNode = GUIParser::parse(
							screenPathName,
							screenFileName,
							variables,
							argumentValues.size() == 3?argumentValues[2]:MiniScript::ScriptVariable(),
							miniScript->screenNode->getContext()
						);
					} catch (Exception& exception) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": an error occurred with goto screen to '" + fileName + "': " + string(exception.what()));
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
						{ .type = ScriptVariableType::TYPE_MAP, .name = "variables", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "arguments", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.screen.push";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string fileName;
				if (argumentValues.size() > 3 ||
					MiniScript::getStringValue(argumentValues, 0, fileName, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					// variables
					unordered_map<string, string> variables;
					if (argumentValues.size() >= 2) {
						auto mapPtr = argumentValues[1].getMapPointer();
						if (mapPtr != nullptr) {
							for (auto& mapIt: *mapPtr) {
								variables[mapIt.first] = mapIt.second.getValueString();
							}
						}
					}
					// push screen node
					try {
						string screenPathName;
						string screenFileName;
						miniScript->screenNode->getProjectFilePathNameAndFileName(fileName, screenPathName, screenFileName);
						//
						auto screenNode = GUIParser::parse(
							screenPathName,
							screenFileName,
							variables,
							argumentValues.size() == 3?argumentValues[2]:MiniScript::ScriptVariable(),
							miniScript->screenNode->getContext()
						);
						miniScript->screenNode->getGUI()->addScreen(screenNode->getId(), screenNode);
						miniScript->screenNode->getGUI()->addRenderScreen(screenNode->getId());
					} catch (Exception& exception) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": an error occurred with pushing screen '" + fileName + "': " + string(exception.what()));
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				// mark as popped
				return "gui.screen.pop";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				miniScript->popped = true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto screen = miniScript->screenNode->getGUI()->getScreen(screenId);
					auto screenMiniScript = screen != nullptr?screen->getMiniScript():nullptr;
					auto scriptIdx = screenMiniScript != nullptr?screenMiniScript->getFunctionScriptIdx(function):SCRIPTIDX_NONE;
					if (screen == nullptr) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": screen not found: " + screenId);
						miniScript->startErrorScript();
					} else
					if (screenMiniScript == nullptr) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": screen mini script not found for given screen: " + screenId);
						miniScript->startErrorScript();
					} else
					if (scriptIdx == SCRIPTIDX_NONE) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": screen: " + screenId + ", function not found: " + function);
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
			bool isVariadic() const override {
				return true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto node = miniScript->screenNode->getNodeById(nodeId);
					auto controller = node != nullptr?node->getController():nullptr;
					if (controller != nullptr) {
						returnValue.setValue(controller->getValue().getString());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no node controller found for given node id '" + nodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto node = miniScript->screenNode->getNodeById(nodeId);
					auto controller = node != nullptr?node->getController():nullptr;
					if (controller != nullptr) {
						controller->setValue(MutableString(value));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no node controller found for given node id '" + nodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
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
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no text or styled text node found for given node id '" + textNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
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
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no text or styled text node found for given node id '" + textNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						returnValue.setValue(elementNode->getActiveConditions().has(condition));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
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
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().set(condition);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().add(condition);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.setAll";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false ||
					argumentValues.size() <= 1 || argumentValues[1].getType() != ScriptVariableType::TYPE_ARRAY) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						vector<string> conditions;
						for (auto i = 0; i < argumentValues[1].getArraySize(); i++) {
							string condition;
							if (argumentValues[1].getArrayValue(i).getStringValue(condition, false) == false) {
								Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
							} else {
								conditions.push_back(condition);
							}
						}
						elementNode->getActiveConditions().set(conditions);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().remove(condition);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.removeAll";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string elementNodeId;
				if (MiniScript::getStringValue(argumentValues, 0, elementNodeId, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(miniScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().removeAll();
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no element node found for given node id '" + elementNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto imageNode = dynamic_cast<GUIImageNode*>(miniScript->screenNode->getNodeById(imageNodeId));
					if (imageNode != nullptr) {
						returnValue.setValue(imageNode->getSource());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no image node found for given image node id '" + imageNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto imageNode = dynamic_cast<GUIImageNode*>(miniScript->screenNode->getNodeById(imageNodeId));
					if (imageNode != nullptr) {
						imageNode->setSource(source);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no image node found for given image node id '" + imageNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto videoNode = dynamic_cast<GUIVideoNode*>(miniScript->screenNode->getNodeById(videoNodeId));
					if (videoNode != nullptr) {
						returnValue.setValue(videoNode->getSource());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no video node found for given video node id '" + videoNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto videoNode = dynamic_cast<GUIVideoNode*>(miniScript->screenNode->getNodeById(videoNodeId));
					if (videoNode != nullptr) {
						videoNode->setSource(source);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no video node found for given video node id '" + videoNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "gui.parentnode.clearSubNodes";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string parentNodeId;
				if (MiniScript::getStringValue(argumentValues, 0, parentNodeId, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto parentNode = dynamic_cast<GUIParentNode*>(miniScript->screenNode->getNodeById(parentNodeId));
					if (parentNode != nullptr) {
						parentNode->clearSubNodes();
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no parent node found for given parent node id '" + parentNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto parentNode = dynamic_cast<GUIParentNode*>(miniScript->screenNode->getNodeById(parentNodeId));
					if (parentNode != nullptr) {
						parentNode->addSubNodes(xml, resetScrollOffsets);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no parent node found for given parent node id '" + parentNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
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
					ScriptVariableType::TYPE_NULL
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
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto parentNode = dynamic_cast<GUIParentNode*>(miniScript->screenNode->getNodeById(parentNodeId));
					if (parentNode != nullptr) {
						parentNode->replaceSubNodes(xml, resetScrollOffsets);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no parent node found for given parent node id '" + parentNodeId + "'");
						miniScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodGUIParentNodeReplaceSubNodes(this));
	}
	{
		//
		class ScriptMethodLogicSignalSend: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalSend(GUIMiniScript* miniScript):
				ScriptMethod({
					{ .type = ScriptVariableType::TYPE_STRING, .name = "logicId", .optional = false, .assignBack = false },
					{ .type = ScriptVariableType::TYPE_STRING, .name = "signal", .optional = false, .assignBack = false }
				}),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.send";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				auto context = miniScript->screenNode->getContext();
				if (context != nullptr) {
					string logicId;
					string signal;
					if (MiniScript::getStringValue(argumentValues, 0, logicId) == true &&
						MiniScript::getStringValue(argumentValues, 1, signal) == true) {
						context->getLogicsMutex()->lock();
						auto logic = static_cast<Logic*>(context->getLogic(logicId));
						if (logic == nullptr) {
							Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no logic with given id: " + logicId);
							miniScript->startErrorScript();
						} else {
							vector<ScriptVariable> arguments(argumentValues.size() - 2);
							for (auto i = 2; i < argumentValues.size(); i++) arguments.push_back(argumentValues[i]);
							logic->addSignal(signal, arguments);
						}
						context->getLogicsMutex()->unlock();
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no application logic context available");
					miniScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodLogicSignalSend(this));
	}
	{
		//
		class ScriptMethodLogicHas: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicHas(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "logicId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "function", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.has";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				auto context = miniScript->screenNode->getContext();
				if (context != nullptr) {
					string logicId;
					string function;
					if (MiniScript::getStringValue(argumentValues, 0, logicId) == false ||
						MiniScript::getStringValue(argumentValues, 1, function) == false) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					} else {
						context->getLogicsMutex()->lock();
						auto logic = dynamic_cast<MiniScriptLogic*>(context->getLogic(logicId));
						if (logic == nullptr || logic->getMiniScript() == nullptr) {
							returnValue.setValue(false);
						} else {
							auto logicMiniScript = logic->getMiniScript();
							auto scriptIdx = logicMiniScript->getFunctionScriptIdx(function);
							if (scriptIdx == SCRIPTIDX_NONE) {
								returnValue.setValue(false);
							} else {
								returnValue.setValue(true);
							}
						}
						context->getLogicsMutex()->unlock();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no application logic context available");
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodLogicHas(this));
	}
	{
		//
		class ScriptMethodLogicCall: public ScriptMethod {
		private:
			GUIMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicCall(GUIMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "logicId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "function", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.call";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				auto context = miniScript->screenNode->getContext();
				if (context != nullptr) {
					string logicId;
					string function;
					if (MiniScript::getStringValue(argumentValues, 0, logicId) == false ||
						MiniScript::getStringValue(argumentValues, 1, function) == false) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					} else {
						context->getLogicsMutex()->lock();
						auto logic = dynamic_cast<MiniScriptLogic*>(context->getLogic(logicId));
						if (logic == nullptr || logic->getMiniScript() == nullptr) {
							Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no mini script logic with given id: " + logicId);
							miniScript->startErrorScript();
						} else {
							auto logicMiniScript = logic->getMiniScript();
							auto scriptIdx = logicMiniScript->getFunctionScriptIdx(function);
							if (scriptIdx == SCRIPTIDX_NONE) {
								Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
								miniScript->startErrorScript();
							} else {
								#if defined (__APPLE__)
									// MACOSX currently does not support initializing span using begin and end iterators,
									// so we need to make a copy of argumentValues beginning from second element
									vector<ScriptVariable> callArgumentValues;
									for (auto i = 2; i < argumentValues.size(); i++) callArgumentValues.push_back(argumentValues[i]);
									// call
									span callArgumentValuesSpan(callArgumentValues);
									logicMiniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
								#else
									span callArgumentValuesSpan(argumentValues.begin() + 2, argumentValues.end());
									logicMiniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
								#endif
							}
						}
						context->getLogicsMutex()->unlock();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no application logic context available");
					miniScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new ScriptMethodLogicCall(this));
	}
}

void GUIMiniScript::registerVariables() {
}

void GUIMiniScript::collectHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents) {
	// keyboard events
	keyboardTypedChars.clear();
	keyboardControlDown = false;
	keyboardMetaDown = false;
	keyboardAltDown = false;
	keyboardShiftDown = false;
	for (auto& event: keyEvents) {
		// processed already?
		if (event.isProcessed() == true) continue;
		// key pressed
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
			keyboardChars.insert(event.getKeyChar());
			keyboardKeys.insert(event.getKeyCode());
		} else
		// key released
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_RELEASED) {
			keyboardChars.erase(event.getKeyChar());
			keyboardKeys.erase(event.getKeyCode());
		} else
		// key typed
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) {
			Character::appendToString(keyboardTypedChars, event.getKeyChar());
		}
		// extra keys
		if (event.isControlDown() == true) keyboardControlDown = true;
		if (event.isMetaDown() == true) keyboardMetaDown = true;
		if (event.isAltDown() == true) keyboardAltDown = true;
		if (event.isShiftDown() == true) keyboardShiftDown = true;
	}

	// mouse
	mouseDown.fill(false);
	mouseUp.fill(false);
	mouseDragging.fill(false);
	mouseMoved = false;
	mouseWheelX = 0.0f;
	mouseWheelY = 0.0f;
	mouseWheelZ = 0.0f;
	for (auto& event: mouseEvents) {
		// mouse move
		if (event.isProcessed() == false && event.getType() == GUIMouseEvent::MOUSEEVENT_MOVED) {
			mouseMoved = true;
		} else
		// on press and drag
		//	store button and mouse dragging properties
		if (event.isProcessed() == false && event.getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
			if (event.getButton() != GUIMouseEvent::MOUSEEVENT_BUTTON_NONE) {
				mouseDown[event.getButton() - 1] = true;
			}
		} else
		if (event.isProcessed() == false && event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
			if (event.getButton() != GUIMouseEvent::MOUSEEVENT_BUTTON_NONE) {
				mouseDragging[event.getButton() - 1] = true;
			}
		} else
		// on release
		//	store release
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
			if (event.getButton() != GUIMouseEvent::MOUSEEVENT_BUTTON_NONE) {
				mouseUp[event.getButton() - 1] = true;
			}
		} else
		// wheel
		if (event.isProcessed() == false && event.getType() == GUIMouseEvent::MOUSEEVENT_WHEEL_MOVED) {
			mouseWheelX+= event.getWheelX();
			mouseWheelY+= event.getWheelY();
			mouseWheelZ+= event.getWheelZ();
		}
		// always store mouse position
		mouseX = event.getX();
		mouseXUnscaled = event.getXUnscaled();
		mouseY = event.getY();
		mouseYUnscaled = event.getYUnscaled();
		// extra keys
		if (event.isControlDown() == true) keyboardControlDown = true;
		if (event.isMetaDown() == true) keyboardMetaDown = true;
		if (event.isAltDown() == true) keyboardAltDown = true;
		if (event.isShiftDown() == true) keyboardShiftDown = true;
	}
}
