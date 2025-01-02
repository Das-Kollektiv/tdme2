#include <tdme/gui/scripting/GUIMinitScript.h>

#include <memory>
#include <span>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/Context.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicMinitScript.h>
#include <tdme/engine/logics/MinitScriptLogic.h>
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
#include <tdme/minitscript/EngineMinitScript.h>
#include <tdme/utilities/MutableString.h>

using std::make_unique;
using std::span;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::logics::LogicMinitScript;
using tdme::engine::logics::MinitScriptLogic;
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
using tdme::gui::scripting::GUIMinitScript;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::minitscript::EngineMinitScript;
using tdme::utilities::MutableString;

const vector<string> GUIMinitScript::CONTEXTFUNCTION_GUI = {};

GUIMinitScript::GUIMinitScript(GUIScreenNode* screenNode): EngineMinitScript(), screenNode(screenNode) {
}

GUIMinitScript::~GUIMinitScript() {
}

const string GUIMinitScript::getBaseClassHeader() {
	return "tdme/gui/scripting/GUIMinitScript.h";
}

const string GUIMinitScript::getBaseClass() {
	return "tdme::gui::scripting::GUIMinitScript";
}

const vector<string> GUIMinitScript::getTranspilationUnits() {
	auto transpilationUnits = EngineMinitScript::getTranspilationUnits();
	transpilationUnits.push_back("src/tdme/gui/scripting/GUIMinitScript.cpp");
	return transpilationUnits;
}

void GUIMinitScript::registerStateMachineStates() {
	EngineMinitScript::registerStateMachineStates();
}

void GUIMinitScript::registerMethods() {
	EngineMinitScript::registerMethods();
	// input
	{
		//
		class MethodInputKeyboardKEYCODE_LEFT: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_LEFT(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_LEFT";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_LEFT));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_LEFT(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_RIGHT: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_RIGHT(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_RIGHT";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_RIGHT));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_RIGHT(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_UP: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_UP(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_UP";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_UP));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_UP(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_DOWN: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_DOWN(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_DOWN";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_DOWN));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_DOWN(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_POS1: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_POS1(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_POS1";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_POS1));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_POS1(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_END: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_END(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_END";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_END));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_END(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_PAGEUP: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_PAGEUP(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_PAGEUP";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_PAGE_UP));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_PAGEUP(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_PAGEDOWN: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_PAGEDOWN(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_PAGEDOWN";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_PAGE_DOWN));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_PAGEDOWN(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_BACKSPACE: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_BACKSPACE(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_BACKSPACE";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_BACKSPACE));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_BACKSPACE(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_DELETE: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_DELETE(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_DELETE";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_DELETE));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_DELETE(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_SPACE: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_SPACE(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_SPACE";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_SPACE));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_SPACE(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_RETURN: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_RETURN(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_RETURN";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_RETURN));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_RETURN(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_ESCAPE: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_ESCAPE(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_ESCAPE";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_ESCAPE));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_ESCAPE(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F1: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F1(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F1";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F1));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F1(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F2: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F2(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F2";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F2));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F2(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F3: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F3(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F3";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F3));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F3(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F4: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F4(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F4";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F4));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F4(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F5: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F5(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F5";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F5));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F5(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F6: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F6(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F6";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F6));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F6(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F7: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F7(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F7";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F7));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F7(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F8: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F8(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F8";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F8));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F8(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F9: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F9(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F9";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F9));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F9(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F10: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F10(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F10";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F10));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F10(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F11: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F11(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F11";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F11));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F11(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F12: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F12(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F12";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F12));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F12(this));
	}
	{
		//
		class MethodInputKeyboardIsKeyDown: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsKeyDown(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "keyCode", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isKeyDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t keyCode;
				if (minitScript->getIntegerValue(arguments, 0, keyCode) == true) {
					minitScript->setValue(returnValue, minitScript->keyboardKeys.find(keyCode) != minitScript->keyboardKeys.end());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardIsKeyDown(this));
	}
	{
		//
		class MethodInputKeyboardIsCharDown: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsCharDown(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "charAsString", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isCharDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string charAsString;
				if (minitScript->getStringValue(arguments, 0, charAsString) == true) {
					UTF8CharacterIterator u8It(charAsString);
					auto keyChar = u8It.hasNext() == true?u8It.next():-1;
					minitScript->setValue(returnValue, minitScript->keyboardChars.find(keyChar) != minitScript->keyboardChars.end());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardIsCharDown(this));
	}
	{
		//
		class MethodInputKeyboardGetTypedString: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardGetTypedString(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_STRING),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.getTypedString";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->keyboardTypedChars);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardGetTypedString(this));
	}
	{
		//
		class MethodInputKeyboardIsControlDown: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsControlDown(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isControlDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->keyboardControlDown == true);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardIsControlDown(this));
	}
	{
		//
		class MethodInputKeyboardIsMetaDown: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsMetaDown(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isMetaDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->keyboardControlDown == true);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardIsMetaDown(this));
	}
	{
		//
		class MethodInputKeyboardIsAltDown: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsAltDown(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isAltDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->keyboardAltDown == true);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardIsAltDown(this));
	}
	{
		//
		class MethodInputKeyboardIsShiftDown: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsShiftDown(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isShiftDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->keyboardShiftDown == true);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputKeyboardIsShiftDown(this));
	}
	// mouse input
	{
		//
		class MethodInputMouseBUTTON_LEFT: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseBUTTON_LEFT(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_LEFT";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_LEFT - 1));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseBUTTON_LEFT(this));
	}
	{
		//
		class MethodInputMouseBUTTON_MIDDLE: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseBUTTON_MIDDLE(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_MIDDLE";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_MIDDLE - 1));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseBUTTON_MIDDLE(this));
	}
	{
		//
		class MethodInputMouseBUTTON_RIGHT: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseBUTTON_RIGHT(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_RIGHT";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_RIGHT - 1));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseBUTTON_RIGHT(this));
	}
	{
		//
		class MethodInputMouseIsButtonDown: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseIsButtonDown(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "button", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.isButtonDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t button;
				if (minitScript->getIntegerValue(arguments, 0, button) == true) {
					minitScript->setValue(returnValue, button >= 0 && button <= 3?minitScript->mouseDown[button]:false);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseIsButtonDown(this));
	}
	{
		//
		class MethodInputMouseIsButtonUp: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseIsButtonUp(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "button", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.isButtonUp";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t button;
				if (minitScript->getIntegerValue(arguments, 0, button) == true) {
					minitScript->setValue(returnValue, button >= 0 && button <= 3?minitScript->mouseUp[button]:false);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseIsButtonUp(this));
	}
	{
		//
		class MethodInputMouseIsDragging: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseIsDragging(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "button", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.isDragging";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t button;
				if (minitScript->getIntegerValue(arguments, 0, button) == true) {
					minitScript->setValue(returnValue, button >= 0 && button <= 3?minitScript->mouseDragging[button]:false);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseIsDragging(this));
	}
	{
		//
		class MethodInputMouseHasMoved: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseHasMoved(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.hasMoved";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->mouseMoved);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseHasMoved(this));
	}
	{
		//
		class MethodInputMouseGetX: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetX(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getX";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(minitScript->mouseX));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseGetX(this));
	}
	{
		//
		class MethodInputMouseGetXUnscaled: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetXUnscaled(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getXUnscaled";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(minitScript->mouseXUnscaled));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseGetXUnscaled(this));
	}
	{
		//
		class MethodInputMouseGetY: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetY(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getY";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(minitScript->mouseY));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseGetY(this));
	}
	{
		//
		class MethodInputMouseGetYUnscaled: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetYUnscaled(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getYUnscaled";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(minitScript->mouseYUnscaled));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseGetYUnscaled(this));
	}
	{
		//
		class MethodInputMouseGetWheelX: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetWheelX(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelX";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->mouseWheelX);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseGetWheelX(this));
	}
	{
		//
		class MethodInputMouseGetWheelY: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetWheelY(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelY";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->mouseWheelY);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseGetWheelY(this));
	}
	{
		//
		class MethodInputMouseGetWheelZ: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetWheelZ(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelZ";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->mouseWheelZ);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodInputMouseGetWheelZ(this));
	}
	// gui
	{
		//
		class MethodGUIScreenSetEnabled: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIScreenSetEnabled(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "screenId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_BOOLEAN, .name = "enabled", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.screen.setEnabled";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string screenId;
				bool enabled;
				if (minitScript->getStringValue(arguments, 0, screenId, false) == false ||
					minitScript->getBooleanValue(arguments, 1, enabled, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto screen = minitScript->screenNode->getGUI()->getScreen(screenId);
					if (screen != nullptr) {
						screen->setEnabled(enabled);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no screen with given id: " + screenId);
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIScreenSetEnabled(this));
	}
	{
		//
		class MethodGUIScreenIsEnabled: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIScreenIsEnabled(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "screenId", .optional = false, .reference = false, .nullable = false },
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.screen.isEnabled";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string screenId;
				if (minitScript->getStringValue(arguments, 0, screenId, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto screen = minitScript->screenNode->getGUI()->getScreen(screenId);
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
		registerMethod(new MethodGUIScreenIsEnabled(this));
	}
	{
		//
		class MethodGUIScreenGoto: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIScreenGoto(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_MAP, .name = "variables", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_PSEUDO_MIXED, .name = "arguments", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.screen.goto";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string fileName;
				if (arguments.size() > 3 ||
					EngineMinitScript::getStringValue(arguments, 0, fileName, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					// delete next screen node if given
					minitScript->nextScreenNode = nullptr;
					// variables
					unordered_map<string, string> variables;
					if (arguments.size() >= 2) {
						auto mapPtr = arguments[1].getMapPointer();
						if (mapPtr != nullptr) {
							for (const auto& [mapEntryKey, mapEntryValue]: *mapPtr) {
								variables[mapEntryKey] = mapEntryValue->getValueAsString();
							}
						}
					}
					// setup next screen node
					try {
						string screenPathName;
						string screenFileName;
						minitScript->screenNode->getProjectFilePathNameAndFileName(fileName, screenPathName, screenFileName);
						//
						minitScript->nextScreenNode = unique_ptr<GUIScreenNode>(
							GUIParser::parse(
								screenPathName,
								screenFileName,
								variables,
								minitScript->getLibrary(),
								arguments.size() == 3?arguments[2]:EngineMinitScript::Variable(),
								minitScript->screenNode->getContext()
							)
						);
					} catch (Exception& exception) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": an error occurred with goto screen to '" + fileName + "': " + string(exception.what()));
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIScreenGoto(this));
	}
	{
		//
		class MethodGUIScreenPush: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIScreenPush(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_MAP, .name = "variables", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_PSEUDO_MIXED, .name = "arguments", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.screen.push";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string fileName;
				if (arguments.size() > 3 ||
					EngineMinitScript::getStringValue(arguments, 0, fileName, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					// variables
					unordered_map<string, string> variables;
					if (arguments.size() >= 2) {
						auto mapPtr = arguments[1].getMapPointer();
						if (mapPtr != nullptr) {
							for (const auto& [mapEntryKey, mapEntryValue]: *mapPtr) {
								variables[mapEntryKey] = mapEntryValue->getValueAsString();
							}
						}
					}
					// push screen node
					try {
						string screenPathName;
						string screenFileName;
						minitScript->screenNode->getProjectFilePathNameAndFileName(fileName, screenPathName, screenFileName);
						//
						auto screenNode = GUIParser::parse(
							screenPathName,
							screenFileName,
							variables,
							minitScript->getLibrary(),
							arguments.size() == 3?arguments[2]:EngineMinitScript::Variable(),
							minitScript->screenNode->getContext()
						);
						minitScript->screenNode->getGUI()->addScreen(screenNode->getId(), screenNode);
						minitScript->screenNode->getGUI()->addRenderScreen(screenNode->getId());
					} catch (Exception& exception) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": an error occurred with pushing screen '" + fileName + "': " + string(exception.what()));
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIScreenPush(this));
	}
	{
		//
		class MethodGUIScreenPop: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIScreenPop(GUIMinitScript* minitScript):
				Method(
					{},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				// mark as popped
				return "gui.screen.pop";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->popped = true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIScreenPop(this));
	}
	{
		//
		class MethodGUIScreenCall: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIScreenCall(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "screenId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "function", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.screen.call";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string screenId;
				string function;
				if (minitScript->getStringValue(arguments, 0, screenId) == false ||
					minitScript->getStringValue(arguments, 1, function) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto screen = minitScript->screenNode->getGUI()->getScreen(screenId);
					auto screenMinitScript = screen != nullptr?screen->getMinitScript():nullptr;
					auto scriptIdx = screenMinitScript != nullptr?screenMinitScript->getFunctionScriptIdx(function):SCRIPTIDX_NONE;
					if (screen == nullptr) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": screen not found: " + screenId);
						minitScript->startErrorScript();
					} else
					if (screenMinitScript == nullptr) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": screen mini script not found for given screen: " + screenId);
						minitScript->startErrorScript();
					} else
					if (scriptIdx == SCRIPTIDX_NONE) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": screen: " + screenId + ", function not found: " + function);
						minitScript->startErrorScript();
					} else {
						#if defined (__clang__)
							// MACOSX currently does not support initializing span using begin and end iterators,
							// so we need to make a copy of arguments beginning from second element
							vector<Variable> callArguments;
							for (auto i = 2; i < arguments.size(); i++) callArguments.push_back(arguments[i]);
							// call
							span callArgumentsSpan(callArguments);
							screenMinitScript->call(scriptIdx, callArgumentsSpan, returnValue);
						#else
							span callArgumentsSpan(arguments.begin() + 2, arguments.end());
							screenMinitScript->call(scriptIdx, callArgumentsSpan, returnValue);
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
		registerMethod(new MethodGUIScreenCall(this));
	}
	{
		//
		class MethodScreenNodeGetId: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodScreenNodeGetId(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_STRING),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.screennode.getId";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				returnValue.setValue(minitScript->screenNode->getId());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodScreenNodeGetId(this));
	}
	{
		//
		class MethodGUIEventACTIONTYPE_PERFORMING: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIEventACTIONTYPE_PERFORMING(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.event.ACTIONTYPE_PERFORMING";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				returnValue.setValue(static_cast<int64_t>(GUIActionListenerType::PERFORMING));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIEventACTIONTYPE_PERFORMING(this));
	}
	{
		//
		class MethodGUIEventACTIONTYPE_PERFORMED: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIEventACTIONTYPE_PERFORMED(GUIMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.event.ACTIONTYPE_PERFORMED";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				returnValue.setValue(static_cast<int64_t>(GUIActionListenerType::PERFORMED));
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIEventACTIONTYPE_PERFORMED(this));
	}
	{
		//
		class MethodGUINodeControllerGetValue: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUINodeControllerGetValue(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.node.controller.getValue";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string nodeId;
				if (EngineMinitScript::getStringValue(arguments, 0, nodeId, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto node = minitScript->screenNode->getNodeById(nodeId);
					auto controller = node != nullptr?node->getController():nullptr;
					if (controller != nullptr) {
						returnValue.setValue(controller->getValue().getString());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no node controller found for given node id '" + nodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUINodeControllerGetValue(this));
	}
	{
		//
		class MethodGUINodeControllerSetValue: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUINodeControllerSetValue(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.node.controller.setValue";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string nodeId;
				string value;
				if (EngineMinitScript::getStringValue(arguments, 0, nodeId, false) == false ||
					EngineMinitScript::getStringValue(arguments, 1, value, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto node = minitScript->screenNode->getNodeById(nodeId);
					auto controller = node != nullptr?node->getController():nullptr;
					if (controller != nullptr) {
						controller->setValue(MutableString(value));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no node controller found for given node id '" + nodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUINodeControllerSetValue(this));
	}
	{
		//
		class MethodGUITextNodeGetText: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUITextNodeGetText(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "textNodeId", .optional = false, .reference = false, .nullable = false },
					},
					VariableType::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.textnode.getText";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string textNodeId;
				if (EngineMinitScript::getStringValue(arguments, 0, textNodeId, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto textNode = dynamic_cast<GUITextNode*>(minitScript->screenNode->getNodeById(textNodeId));
					auto styledTextNode = textNode == nullptr?dynamic_cast<GUIStyledTextNode*>(minitScript->screenNode->getNodeById(textNodeId)):nullptr;
					if (textNode != nullptr) {
						returnValue.setValue(textNode->getText().getString());
					} else
					if (styledTextNode != nullptr) {
						returnValue.setValue(styledTextNode->getText().getString());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no text or styled text node found for given node id '" + textNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUITextNodeGetText(this));
	}
	{
		//
		class MethodGUITextNodeSetText: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUITextNodeSetText(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "textNodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "text", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.textnode.setText";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string textNodeId;
				string text;
				if (EngineMinitScript::getStringValue(arguments, 0, textNodeId, false) == false ||
					EngineMinitScript::getStringValue(arguments, 1, text, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto textNode = dynamic_cast<GUITextNode*>(minitScript->screenNode->getNodeById(textNodeId));
					auto styledTextNode = textNode == nullptr?dynamic_cast<GUIStyledTextNode*>(minitScript->screenNode->getNodeById(textNodeId)):nullptr;
					if (textNode != nullptr) {
						textNode->setText(MutableString(text));
					} else
					if (styledTextNode != nullptr) {
						styledTextNode->setText(MutableString(text));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no text or styled text node found for given node id '" + textNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUITextNodeSetText(this));
	}
	{
		//
		class MethodGUIElementNodeConditionsHas: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIElementNodeConditionsHas(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "condition", .optional = false, .reference = false, .nullable = false },
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.has";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string elementNodeId;
				string condition;
				if (EngineMinitScript::getStringValue(arguments, 0, elementNodeId, false) == false ||
					EngineMinitScript::getStringValue(arguments, 1, condition, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(minitScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						returnValue.setValue(elementNode->getActiveConditions().has(condition));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no element node found for given node id '" + elementNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIElementNodeConditionsHas(this));
	}
	{
		//
		class MethodGUIElementNodeConditionsGet: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIElementNodeConditionsGet(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_ARRAY
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.get";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string elementNodeId;
				if (EngineMinitScript::getStringValue(arguments, 0, elementNodeId, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(minitScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						auto conditions = elementNode->getActiveConditions().getConditions();
						returnValue.setType(TYPE_ARRAY);
						for (const auto& condition: conditions) {
							returnValue.pushArrayEntry(condition);
						}
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no element node found for given node id '" + elementNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIElementNodeConditionsGet(this));
	}
	{
		//
		class MethodGUIElementNodeConditionsSet: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIElementNodeConditionsSet(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "condition", .optional = false, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.set";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string elementNodeId;
				string condition;
				if (EngineMinitScript::getStringValue(arguments, 0, elementNodeId, false) == false ||
					EngineMinitScript::getStringValue(arguments, 1, condition, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(minitScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().set(condition);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no element node found for given node id '" + elementNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIElementNodeConditionsSet(this));
	}
	{
		//
		class MethodGUIElementNodeConditionsAdd: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIElementNodeConditionsAdd(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "condition", .optional = false, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.add";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string elementNodeId;
				string condition;
				if (EngineMinitScript::getStringValue(arguments, 0, elementNodeId, false) == false ||
					EngineMinitScript::getStringValue(arguments, 1, condition, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(minitScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().add(condition);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no element node found for given node id '" + elementNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIElementNodeConditionsAdd(this));
	}
	{
		//
		class MethodGUIElementNodeConditionsSetAll: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIElementNodeConditionsSetAll(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_ARRAY, .name = "conditions", .optional = false, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.setAll";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string elementNodeId;
				if (EngineMinitScript::getStringValue(arguments, 0, elementNodeId, false) == false ||
					arguments.size() <= 1 || arguments[1].getType() != VariableType::TYPE_ARRAY) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(minitScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						vector<string> conditions;
						for (auto i = 0; i < arguments[1].getArraySize(); i++) {
							string condition;
							if (arguments[1].getArrayEntry(i).getStringValue(condition, false) == false) {
								Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
							} else {
								conditions.push_back(condition);
							}
						}
						elementNode->getActiveConditions().set(conditions);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no element node found for given node id '" + elementNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIElementNodeConditionsSetAll(this));
	}
	{
		//
		class MethodGUIElementNodeConditionsRemove: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIElementNodeConditionsRemove(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "condition", .optional = false, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.remove";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string elementNodeId;
				string condition;
				if (EngineMinitScript::getStringValue(arguments, 0, elementNodeId, false) == false ||
					EngineMinitScript::getStringValue(arguments, 1, condition, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(minitScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().remove(condition);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no element node found for given node id '" + elementNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIElementNodeConditionsRemove(this));
	}
	{
		//
		class MethodGUIElementNodeConditionsRemoveAll: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIElementNodeConditionsRemoveAll(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "elementNodeId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.elementnode.conditions.removeAll";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string elementNodeId;
				if (EngineMinitScript::getStringValue(arguments, 0, elementNodeId, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto elementNode = dynamic_cast<GUIElementNode*>(minitScript->screenNode->getNodeById(elementNodeId));
					if (elementNode != nullptr) {
						elementNode->getActiveConditions().removeAll();
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no element node found for given node id '" + elementNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIElementNodeConditionsRemoveAll(this));
	}
	{
		//
		class MethodGUIImageNodeGetSource: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIImageNodeGetSource(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "imageNodeId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.imagenode.getSource";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string imageNodeId;
				if (EngineMinitScript::getStringValue(arguments, 0, imageNodeId, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto imageNode = dynamic_cast<GUIImageNode*>(minitScript->screenNode->getNodeById(imageNodeId));
					if (imageNode != nullptr) {
						returnValue.setValue(imageNode->getSource());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no image node found for given image node id '" + imageNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIImageNodeGetSource(this));
	}
	{
		//
		class MethodGUIImageNodeSetSource: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIImageNodeSetSource(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "imageNodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "source", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.imagenode.setSource";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string imageNodeId;
				string source;
				if (EngineMinitScript::getStringValue(arguments, 0, imageNodeId, false) == false ||
					EngineMinitScript::getStringValue(arguments, 1, source, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto imageNode = dynamic_cast<GUIImageNode*>(minitScript->screenNode->getNodeById(imageNodeId));
					if (imageNode != nullptr) {
						imageNode->setSource(source);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no image node found for given image node id '" + imageNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIImageNodeSetSource(this));
	}
	{
		//
		class MethodGUIVideoNodeGetSource: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIVideoNodeGetSource(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "videoNodeId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.videonode.getSource";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string videoNodeId;
				if (EngineMinitScript::getStringValue(arguments, 0, videoNodeId, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto videoNode = dynamic_cast<GUIVideoNode*>(minitScript->screenNode->getNodeById(videoNodeId));
					if (videoNode != nullptr) {
						returnValue.setValue(videoNode->getSource());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no video node found for given video node id '" + videoNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIVideoNodeGetSource(this));
	}
	{
		//
		class MethodGUIVideoNodeSetSource: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIVideoNodeSetSource(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "videoNodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "source", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.videonode.setSource";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string videoNodeId;
				string source;
				if (EngineMinitScript::getStringValue(arguments, 0, videoNodeId, false) == false ||
					EngineMinitScript::getStringValue(arguments, 1, source, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto videoNode = dynamic_cast<GUIVideoNode*>(minitScript->screenNode->getNodeById(videoNodeId));
					if (videoNode != nullptr) {
						videoNode->setSource(source);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no video node found for given video node id '" + videoNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIVideoNodeSetSource(this));
	}
	{
		//
		class MethodGUIParentNodeClearSubNodes: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIParentNodeClearSubNodes(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "parentNodeId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.parentnode.clearSubNodes";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string parentNodeId;
				if (EngineMinitScript::getStringValue(arguments, 0, parentNodeId, false) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto parentNode = dynamic_cast<GUIParentNode*>(minitScript->screenNode->getNodeById(parentNodeId));
					if (parentNode != nullptr) {
						parentNode->clearSubNodes();
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no parent node found for given parent node id '" + parentNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIParentNodeClearSubNodes(this));
	}
	{
		//
		class MethodGUIParentNodeAddSubNodes: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIParentNodeAddSubNodes(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "parentNodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "xml", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_BOOLEAN, .name = "resetScrollOffsets", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.parentnode.addSubNodes";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string parentNodeId;
				string xml;
				bool resetScrollOffsets = true;
				if (EngineMinitScript::getStringValue(arguments, 0, parentNodeId, false) == false ||
					EngineMinitScript::getStringValue(arguments, 1, xml, false) == false ||
					EngineMinitScript::getBooleanValue(arguments, 2, resetScrollOffsets, true) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto parentNode = dynamic_cast<GUIParentNode*>(minitScript->screenNode->getNodeById(parentNodeId));
					if (parentNode != nullptr) {
						parentNode->addSubNodes(xml, resetScrollOffsets);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no parent node found for given parent node id '" + parentNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIParentNodeAddSubNodes(this));
	}
	{
		//
		class MethodGUIParentNodeReplaceSubNodes: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodGUIParentNodeReplaceSubNodes(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "parentNodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "xml", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_BOOLEAN, .name = "resetScrollOffsets", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "gui.parentnode.replaceSubNodes";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string parentNodeId;
				string xml;
				bool resetScrollOffsets = true;
				if (EngineMinitScript::getStringValue(arguments, 0, parentNodeId, false) == false ||
					EngineMinitScript::getStringValue(arguments, 1, xml, false) == false ||
					EngineMinitScript::getBooleanValue(arguments, 2, resetScrollOffsets, true) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto parentNode = dynamic_cast<GUIParentNode*>(minitScript->screenNode->getNodeById(parentNodeId));
					if (parentNode != nullptr) {
						parentNode->replaceSubNodes(xml, resetScrollOffsets);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no parent node found for given parent node id '" + parentNodeId + "'");
						minitScript->startErrorScript();
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodGUIParentNodeReplaceSubNodes(this));
	}
	{
		//
		class MethodLogicSignalSend: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodLogicSignalSend(GUIMinitScript* minitScript):
				Method({
					{ .type = VariableType::TYPE_STRING, .name = "logicId", .optional = false, .reference = false, .nullable = false },
					{ .type = VariableType::TYPE_STRING, .name = "signal", .optional = false, .reference = false, .nullable = false }
				}),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.signal.send";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				auto context = minitScript->screenNode->getContext();
				if (context != nullptr) {
					string logicId;
					string signal;
					if (EngineMinitScript::getStringValue(arguments, 0, logicId) == true &&
						EngineMinitScript::getStringValue(arguments, 1, signal) == true) {
						context->getLogicsMutex()->lock();
						auto logic = static_cast<Logic*>(context->getLogic(logicId));
						if (logic == nullptr) {
							Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no logic with given id: " + logicId);
							minitScript->startErrorScript();
						} else {
							vector<Variable> arguments(arguments.size() - 2);
							for (auto i = 2; i < arguments.size(); i++) arguments.push_back(arguments[i]);
							logic->addSignal(signal, arguments);
						}
						context->getLogicsMutex()->unlock();
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
						minitScript->startErrorScript();
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no application logic context available");
					minitScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodLogicSignalSend(this));
	}
	{
		//
		class MethodLogicHas: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodLogicHas(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "logicId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "callable", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.has";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				auto context = minitScript->screenNode->getContext();
				if (context != nullptr) {
					string logicId;
					string callable;
					if (EngineMinitScript::getStringValue(arguments, 0, logicId) == false ||
						EngineMinitScript::getStringValue(arguments, 1, callable) == false) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
						minitScript->startErrorScript();
					} else {
						context->getLogicsMutex()->lock();
						auto logic = dynamic_cast<MinitScriptLogic*>(context->getLogic(logicId));
						if (logic == nullptr || logic->getMinitScript() == nullptr) {
							returnValue.setValue(false);
						} else {
							auto logicMinitScript = logic->getMinitScript();
							auto scriptIdx = logicMinitScript->getFunctionScriptIdx(callable);
							if (scriptIdx == SCRIPTIDX_NONE || logicMinitScript->getScripts()[scriptIdx].callable == false) {
								returnValue.setValue(false);
							} else {
								returnValue.setValue(true);
							}
						}
						context->getLogicsMutex()->unlock();
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no application logic context available");
					minitScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodLogicHas(this));
	}
	{
		//
		class MethodLogicCall: public Method {
		private:
			GUIMinitScript* minitScript { nullptr };
		public:
			MethodLogicCall(GUIMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "logicId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "callable", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.call";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				auto context = minitScript->screenNode->getContext();
				if (context != nullptr) {
					string logicId;
					string callable;
					if (EngineMinitScript::getStringValue(arguments, 0, logicId) == false ||
						EngineMinitScript::getStringValue(arguments, 1, callable) == false) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
						minitScript->startErrorScript();
					} else {
						context->getLogicsMutex()->lock();
						auto logic = dynamic_cast<MinitScriptLogic*>(context->getLogic(logicId));
						if (logic == nullptr || logic->getMinitScript() == nullptr) {
							Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no mini script logic with given id: " + logicId);
							minitScript->startErrorScript();
						} else {
							auto logicMinitScript = logic->getMinitScript();
							auto scriptIdx = logicMinitScript->getFunctionScriptIdx(callable);
							if (scriptIdx == SCRIPTIDX_NONE || logicMinitScript->getScripts()[scriptIdx].callable == false) {
								Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": callable not found: " + callable);
								minitScript->startErrorScript();
							} else {
								#if defined (__clang__)
									// MACOSX currently does not support initializing span using begin and end iterators,
									// so we need to make a copy of arguments beginning from second element
									vector<Variable> callArguments;
									for (auto i = 2; i < arguments.size(); i++) callArguments.push_back(arguments[i]);
									// call
									span callArgumentsSpan(callArguments);
									logicMinitScript->call(scriptIdx, callArgumentsSpan, returnValue);
								#else
									span callArgumentsSpan(arguments.begin() + 2, arguments.end());
									logicMinitScript->call(scriptIdx, callArgumentsSpan, returnValue);
								#endif
							}
						}
						context->getLogicsMutex()->unlock();
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no application logic context available");
					minitScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTION_GUI;
			}
		};
		registerMethod(new MethodLogicCall(this));
	}
}

void GUIMinitScript::registerVariables() {
}

void GUIMinitScript::collectHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents) {
	// keyboard events
	keyboardTypedChars.clear();
	keyboardControlDown = false;
	keyboardMetaDown = false;
	keyboardAltDown = false;
	keyboardShiftDown = false;
	for (const auto& event: keyEvents) {
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
	for (const auto& event: mouseEvents) {
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
