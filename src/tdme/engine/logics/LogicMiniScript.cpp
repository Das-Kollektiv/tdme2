#include <tdme/engine/logics/LogicMiniScript.h>

#include <span>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/Context.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using std::span;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::logics::LogicMiniScript;

using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::MiniScript;

LogicMiniScript::LogicMiniScript(): MiniScript() {
}

LogicMiniScript::~LogicMiniScript() {
}


void LogicMiniScript::registerStateMachineStates() {
	MiniScript::registerStateMachineStates();
}

void LogicMiniScript::registerMethods() {
	MiniScript::registerMethods();
	{
		//
		class ScriptMethodLogicGetId: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicGetId(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.getId";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->getId());
			}
		};
		registerMethod(new ScriptMethodLogicGetId(this));
	}
	{
		//
		class ScriptMethodLogicSignalSend: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalSend(LogicMiniScript* miniScript):
				ScriptMethod({
					{ .type = ScriptVariableType::TYPE_STRING, .name = "logicId", .optional = false },
					{ .type = ScriptVariableType::TYPE_STRING, .name = "signal", .optional = false }
				}),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.send";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string logicId;
				string signal;
				if (miniScript->getStringValue(argumentValues, 0, logicId) == true &&
					miniScript->getStringValue(argumentValues, 1, signal) == true) {
					auto logic = static_cast<Logic*>(miniScript->context->getLogic(logicId));
					if (logic == nullptr) {
						Console::println("ScriptMethodLogicSignalSend::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no logic with given id: " + logicId);
						return;
					} else {
						vector<ScriptVariable> arguments(argumentValues.size() - 2);
						for (auto i = 2; i < argumentValues.size(); i++) arguments.push_back(argumentValues[i]);
						logic->addSignal(signal, arguments);
					}
				} else {
					Console::println("ScriptMethodLogicSignalSend::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, argument 1: string expected");
					miniScript->startErrorScript();
				}
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodLogicSignalSend(this));
	}
	{
		//
		class ScriptMethodLogicSignalHas: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalHas(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.has";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->hasSignal());
			}
		};
		registerMethod(new ScriptMethodLogicSignalHas(this));
	}
	{
		//
		class ScriptMethodLogicSignalGetName: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalGetName(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.getName";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->getSignalName());
			}
		};
		registerMethod(new ScriptMethodLogicSignalGetName(this));
	}
	{
		//
		class ScriptMethodLogicSignalGetArgument: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalGetArgument(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "argumentIndex", .optional = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.getArgument";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t argumentIndex;
				if (miniScript->getIntegerValue(argumentValues, 0, argumentIndex) == true) {
					returnValue = miniScript->logic->getSignalArgument(argumentIndex);
				} else {
					Console::println("ScriptMethodLogicSignalGetArgument::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodLogicSignalGetArgument(this));
	}
	{
		//
		class ScriptMethodLogicSignalNext: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalNext(LogicMiniScript* miniScript):
				ScriptMethod(),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.next";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				miniScript->logic->removeSignal();
			}
		};
		registerMethod(new ScriptMethodLogicSignalNext(this));
	}
	// keyboard input
	{
		//
		class ScriptMethodInputKeyboardIsKeyDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsKeyDown(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "keyCode", .optional = false }
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
					Console::println("ScriptMethodInputKeyboardIsKeyDown::executeMethod(): " + getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsKeyDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardGetTypedString: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardGetTypedString(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.getTypedString";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardChars;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardGetTypedString(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsControlDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsControlDown(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isControlDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardControlDown == true;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsControlDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsMetaDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsMetaDown(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isMetaDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardControlDown == true;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsMetaDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsAltDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsAltDown(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isAltDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardAltDown == true;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsAltDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsShiftDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsShiftDown(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isShiftDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardShiftDown == true;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsShiftDown(this));
	}
}

void LogicMiniScript::registerVariables() {
}

void LogicMiniScript::collectHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents) {
	Console::println("LogicMiniScript::collectHIDEvents()");
	// keyboard events
	keyboardChars.clear();
	keyboardControlDown = false;
	keyboardMetaDown = false;
	keyboardAltDown = false;
	keyboardShiftDown = false;
	for (auto& event: keyEvents) {
		// key pressed
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
			keyboardKeys.insert(event.getKeyCode());
		} else
		// key released
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_RELEASED) {
			keyboardKeys.erase(event.getKeyCode());
		} else
		// key typed
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) {
			Character::appendToString(keyboardChars, event.getKeyChar());
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
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_MOVED) {
			mouseMoved = true;
		} else
		// on press and drag
		//	store button and mouse dragging properties
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
			if (event.getButton() != GUIMouseEvent::MOUSEEVENT_BUTTON_NONE) {
				mouseDragging[event.getButton() - 1] = true;
			}
		} else
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
			if (event.getButton() != GUIMouseEvent::MOUSEEVENT_BUTTON_NONE) {
				mouseDown[event.getButton() - 1] = true;
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
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_WHEEL_MOVED) {
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
