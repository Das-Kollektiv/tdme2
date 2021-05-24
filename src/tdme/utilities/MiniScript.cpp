#include <tdme/utilities/MiniScript.h>

#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/Transformations.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::map;
using std::sort;
using std::stack;
using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::scene::SceneEntity;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Integer;
using tdme::utilities::MiniScript;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

MiniScript::MiniScript(const string& pathName, const string& fileName) {
	//
	registerStateMachineStates();
	registerMethods();
	registerVariables();

	//
	loadScript(pathName, fileName);

	//
	Console::println("DUMPINFO:\n\n" + dumpInfo() + "\n\n");
}

MiniScript::~MiniScript() {
	for (auto& scriptMethodIt: scriptMethods) delete scriptMethodIt.second;
	for (auto& scriptStateMachineStateIt: scriptStateMachineStates) delete scriptStateMachineStateIt.second;
}

void MiniScript::executeStateMachine() {
	if (scriptState.state == STATE_NONE) return;
	// execute state machine
	auto scriptStateMachineStateIt = scriptStateMachineStates.find(scriptState.state);
	if (scriptStateMachineStateIt != scriptStateMachineStates.end()) {
		scriptStateMachineStateIt->second->execute();
	} else {
		Console::println("MiniScript::doLogic(): unknown state with id: " + to_string(scriptState.state));
	}
}

bool MiniScript::isRunning() {
	return scriptState.running;
}

void MiniScript::registerStateMachineState(ScriptStateMachineState* state) {
	auto scriptStateMachineStateIt = scriptStateMachineStates.find(state->getId());
	if (scriptStateMachineStateIt != scriptStateMachineStates.end()) {
		Console::println("MiniScript::registerStateMachineState(): state with id + " + to_string(state->getId()) + ", name '" + state->getName() + "' already registered.");
		return;
	}
	scriptStateMachineStates[state->getId()] = state;
}

void MiniScript::registerMethod(ScriptMethod* method) {
	auto scriptMethodsIt = scriptMethods.find(method->getMethodName());
	if (scriptMethodsIt != scriptMethods.end()) {
		Console::println("MiniScript::registerMethod(): method with name '" + method->getMethodName() + "' already registered.");
		return;
	}
	scriptMethods[method->getMethodName()] = method;
}

void MiniScript::executeScriptLine() {
	if (scriptState.idx == -1 || scriptState.statementIdx == -1 || scriptState.running == false) return;
	auto& script = scripts[scriptState.idx];
	auto& statement = script.statements[scriptState.statementIdx];
	if (VERBOSE == true) Console::println("MiniScript::executeScriptLine(): @" + to_string(statement.line) + ": " + statement.statement);

	scriptState.statementIdx++;
	if (scriptState.statementIdx >= script.statements.size()) {
		scriptState.idx = -1;
		scriptState.statementIdx = -1;
		scriptState.state = STATE_WAIT_FOR_CONDITION;
	}

	string variable;
	string method;
	vector<string> arguments;
	parseScriptStatement(statement.statement, variable, method, arguments);
	auto returnValue = executeScriptStatement(method, arguments, statement);
	if (variable.empty() == false) scriptState.variables[variable] = returnValue;
}

void MiniScript::parseScriptStatement(const string& statement, string& variable, string& method, vector<string>& arguments) {
	if (VERBOSE == true) Console::println("MiniScript::parseScriptStatement(): " + statement);
	auto rightStatement = statement;
	auto assigmentPosIdx = statement.find_first_of('=');
	if (assigmentPosIdx != string::npos) {
		variable = StringTools::trim(StringTools::substring(statement, 0, assigmentPosIdx));
		rightStatement = StringTools::trim(StringTools::substring(statement, assigmentPosIdx + 1));
		if (StringTools::startsWith(variable, "$") == false) {
			Console::println("MiniScript::parseScriptStatement(): variable '" + variable + "' needs to start with a $. Ignoring this variable!");
			variable.clear();
		} 
	}
	auto argumentStartIdx = string::npos;
	auto argumentEndIdx = string::npos;
	auto bracketCount = 0;
	string argument;
	for (auto i = 0; i < rightStatement.size(); i++) {
		auto c = rightStatement[i];
		if (c == '(') {
			bracketCount++;
			if (bracketCount > 1) {
				argument+= c;
			}	
		} else
		if (c == ')') {
			bracketCount--;
			if (bracketCount == 0) {
				if (argument.empty() == false) {
					arguments.push_back(StringTools::trim(argument));
					argument.clear();
				}	
			} else {
				argument+= c;
			}
		} else
		if (c == ',') {
			if (bracketCount == 1) {
				if (argument.empty() == false) {
					arguments.push_back(StringTools::trim(argument));
					argument.clear();
				}
			} else {
				argument+= c;
			} 		
		} else
		if (bracketCount == 0) {
			method+= c;
		} else {
			argument+= c;
		}
	}
}

MiniScript::ScriptVariable MiniScript::executeScriptStatement(const string& method, const vector<string>& arguments, const ScriptStatement& statement) {
	string argumentsString;
	for (auto& argument: arguments) argumentsString+= (argumentsString.empty() == false?",":"") + argument;
	if (VERBOSE == true) Console::println("MiniScript::executeScriptStatement(): " + method + "(" + argumentsString + ")");
	vector<ScriptVariable> argumentValues;
	ScriptVariable returnValue;
	// check if argument is a method calls return value
	for (auto& argument: arguments) {
		if (argument.empty() == false && argument.find('(') != string::npos && argument.find(')') != string::npos) {
			// method call, call method and put its return value into argument value
			string subVariable;
			string subMethod;
			vector<string> subArguments;
			parseScriptStatement(argument, subVariable, subMethod, subArguments);
			auto argumentValue = executeScriptStatement(subMethod, subArguments, statement);
			if (subVariable.empty() == false) scriptState.variables[subVariable] = argumentValue;
			argumentValues.push_back(argumentValue);
		} else
		// variable
		if (StringTools::startsWith(argument, "$") == true) {
			auto variableIt = scriptState.variables.find(argument);
			if (variableIt == scriptState.variables.end()) {
				Console::println("MiniScript::executeScriptStatement(): " + method + "(" + argument + "): variable: '" + argument + "' does not exist");
				argumentValues.push_back(ScriptVariable());
			} else {
				auto argumentValue = variableIt->second;
				argumentValues.push_back(argumentValue);
			}
		} else {
			// literal
			ScriptVariable argumentValue;
			setStringValue(argumentValue, argument);
			argumentValues.push_back(argumentValue);
		}
	}
	auto scriptMethodsIt = scriptMethods.find(method);
	if (scriptMethodsIt != scriptMethods.end()) {
		auto scriptMethod = scriptMethodsIt->second;
		auto argumentIdx = 0;
		if (scriptMethod->isVariadic() == false) {
			for (auto& argumentType: scriptMethod->getArgumentTypes()) {
				auto argumentOk = true;
				switch(argumentType.type) {
					case TYPE_VOID:
						break;
					case TYPE_BOOLEAN:
						{
							bool booleanValue;
							argumentOk = getBooleanValue(argumentValues, argumentIdx, booleanValue, argumentType.optional);
						}
						break;
					case TYPE_INTEGER:
						{
							int64_t integerValue;
							argumentOk = getIntegerValue(argumentValues, argumentIdx, integerValue, argumentType.optional);
						}
						break;
					case TYPE_STRING:
						{
							string stringValue;
							argumentOk = getStringValue(argumentValues, argumentIdx, stringValue, argumentType.optional);
						}
						break;
					case TYPE_TRANSFORMATIONS:
						Transformations transformationsValue;
						argumentOk = getTransformationsValue(argumentValues, argumentIdx, transformationsValue, argumentType.optional);
						break;
				}
				if (argumentOk == false) {
					Console::println(
						string("MiniScript::executeScriptStatement(): ") +
						"@" + to_string(statement.line) +
						": method '" + method + "'" +
						": argument value @ " + to_string(argumentIdx + 1) + ": expected " + getScriptVariableTypeAsString(argumentType.type) + ", but got: " + getScriptVariableAsString(argumentValues[argumentIdx]));
				}
				argumentIdx++;
			}
			if (argumentValues.size() > scriptMethod->getArgumentTypes().size()) {
				Console::println(
					string("MiniScript::executeScriptStatement(): ") +
					"@" + to_string(statement.line) +
					": method '" + method + "'" +
					": too many arguments: expected: " + to_string(scriptMethod->getArgumentTypes().size()) + ", got " + to_string(argumentValues.size()));
			}
		}
		scriptMethod->executeMethod(argumentValues, returnValue, statement);
		if (returnValue.type != scriptMethod->getReturnValueType()) {
			Console::println(
				string("MiniScript::executeScriptStatement(): ") +
				"@" + to_string(statement.line) +
				": method '" + method + "'" +
				": return value: expected " + getScriptVariableTypeAsString(scriptMethod->getReturnValueType()) + ", but got: " + getScriptVariableTypeAsString(returnValue.type));
		}
		return returnValue;
	} else {
		Console::println("MiniScript::executeScriptStatement(): unknown method: " + method + "(" + argumentsString + ")");
		startErrorScript();
	}
	return returnValue;
}

void MiniScript::startErrorScript() {
	emit("error");
}

void MiniScript::emit(const string& condition) {
	if (VERBOSE == true) Console::println("MiniScript::emit(): " + condition);
	auto scriptIdx = 0;
	for (auto& script: scripts) {
		auto conditionMet = true;
		if (script.conditions.size() == 1 && script.conditions[0] == condition) {
			break;
		} else {
			scriptIdx++;
		}
	}
	if (scriptIdx == scripts.size()) {
		scriptIdx = -1;
		startErrorScript();
		return;
	}
	if (scriptState.idx == scriptIdx) {
		Console::println("MiniScript::emit(): script already running: " + condition);
		return;
	}
	//
	scriptState.forTimeStarted.clear();
	scriptState.id.clear();
	scriptState.idx = scriptIdx;
	scriptState.statementIdx = 0;
	scriptState.waitStarted = Time::getCurrentMillis();
	scriptState.waitTime = 0LL;
	scriptState.state = STATE_NEXT_STATEMENT;
}

void MiniScript::loadScript(const string& pathName, const string& fileName) {
	vector<string> scriptLines;
	try {
		FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, scriptLines);
	} catch (FileSystemException& fse)	{
		Console::println("MiniScript::MiniScript(): " + pathName + "/" + fileName + ": an error occurred: " + fse.what());
	}
	auto haveCondition = false;
	auto line = 1;
	auto statementIdx = 1;
	stack<int> gotoStatementIdxStack;
	for (auto scriptLine: scriptLines) {
		scriptLine = StringTools::trim(scriptLine);
		if (StringTools::startsWith(scriptLine, "#") == true) {
			line++;
			continue;
		}
		if (haveCondition == false) {
			if (StringTools::startsWith(scriptLine, "on:") == true) {
				haveCondition = true;
				scriptLine = StringTools::trim(StringTools::substring(scriptLine, string("on:").size()));
				vector<string> conditions;
				StringTokenizer t;
				t.tokenize(scriptLine, ";");
				while (t.hasMoreTokens()) conditions.push_back(StringTools::trim(t.nextToken()));
				scripts.push_back({ .line = line, .conditions = conditions, .statements = {} });
				statementIdx = 0;
			} else {
				Console::println("MiniScript::MiniScript(): " + pathName + "/" + fileName + ": expecting 'on:' script condition");
			}
		} else {
			if (scriptLine == "end") {
				if (gotoStatementIdxStack.empty() == false) {
					auto gotoStatementIdx = gotoStatementIdxStack.top();
					gotoStatementIdxStack.pop();
					scripts.at(scripts.size() - 1).statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = scriptLine, .gotoStatementIdx = gotoStatementIdx });
					scripts.at(scripts.size() - 1).statements.at(gotoStatementIdx).gotoStatementIdx = scripts.at(scripts.size() - 1).statements.size();
				} else{
					haveCondition = false;
				}
			} else {
				if (StringTools::startsWith(scriptLine, "forTime") == true) gotoStatementIdxStack.push(statementIdx);
				scripts.at(scripts.size() - 1).statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = scriptLine, .gotoStatementIdx = -1 });
			}
			statementIdx++;
		}
		line++;
	}
	Console::println("MiniScript::MiniScript(): " + pathName + "/" + fileName);
	for (auto& script: scripts) {
		for (auto& condition: script.conditions)
			Console::print(condition + "; ");
		Console::println();
		for (auto& scriptStatement: script.statements) {
			Console::println("\t" + to_string(scriptStatement.statementIdx) + ": " + scriptStatement.statement + (scriptStatement.gotoStatementIdx != -1?" (gotoStatement " + to_string(scriptStatement.gotoStatementIdx) + ")":""));
		}
	}

	//
	startScript();
}

void MiniScript::startScript(int64_t delay) {
	if (VERBOSE == true) Console::println("MiniScript::startScript(): waiting " + to_string(delay) + "ms; starting script.");
	scriptState.variables.clear();
	scriptState.forTimeStarted.clear();
	scriptState.id.clear();
	registerVariables();
	scriptState.statementIdx = 0;
	scriptState.waitStarted = Time::getCurrentMillis();
	scriptState.waitTime = delay;
	scriptState.state = delay > 0LL?STATE_WAIT:STATE_WAIT_FOR_CONDITION;
	scriptState.running = true;
}

int MiniScript::determineScriptIdxToStart() {
	if (VERBOSE == true) Console::println("MiniScript::determineScriptIdxToStart()");
	auto currentScriptStateScript = scriptState.state;
	auto nothingScriptIdx = -1;
	auto scriptIdx = 0;
	for (auto& script: scripts) {
		auto conditionMet = true;
		if (script.conditions.size() == 1 && script.conditions[0] == "nothing") {
			nothingScriptIdx = scriptIdx;
		} else
		if (script.conditions.size() == 1 &&
			script.conditions[0].find('(') == string::npos &&
			script.conditions[0].rfind(')') == string::npos) {
			// user emit condition
		} else {
			for (auto condition: script.conditions) {
				string variable;
				string method;
				vector<string> arguments;
				parseScriptStatement(condition, variable, method, arguments);
				auto returnValue = executeScriptStatement(
					method,
					arguments,
					{
						.line = 0,
						.statementIdx = 0,
						.statement = condition,
						.gotoStatementIdx = -0
					}
				);
				if (returnValue.type != ScriptVariableType::TYPE_BOOLEAN) {
					Console::println("MiniScript::determineScriptIdxToStart(): " + condition + ": expecting boolean return value");
					conditionMet = false;
					break;
				} else
				if (returnValue.booleanValue == false) {
					conditionMet = false;
					break;
				}
			}
			if (conditionMet == false) {
				if (VERBOSE == true) {
					Console::print("MiniScript::determineScriptIdxToStart(): ");
					for (auto condition: script.conditions) Console::print(condition + "; ");
					Console::println(": FAILED");
				}	
				scriptIdx++;
				continue;
			}
			if (VERBOSE == true) {
				Console::print("MiniScript::determineScriptIdxToStart(): ");
				for (auto condition: script.conditions) Console::print(condition + "; ");
				Console::println(": OK");
			}
			scriptState.state = currentScriptStateScript;
			return scriptIdx;
		}	
		scriptIdx++;
	}
	scriptState.state = currentScriptStateScript;
	return nothingScriptIdx;
}

inline bool MiniScript::getStringValue(const vector<ScriptVariable>& arguments, int idx, string& value, bool optional) {
	if (idx >= arguments.size()) return optional;
	auto& argument = arguments[idx];
	switch(argument.type) {
		case TYPE_VOID:
			return optional;
		case TYPE_BOOLEAN:
			value = argument.booleanValue == true?"true":"false";
			return true;
		case TYPE_INTEGER:
			value = to_string(argument.integerValue);
			return true;
		case TYPE_STRING:
			value = argument.stringValue;
			return true;
		case TYPE_TRANSFORMATIONS:
			return false;
	} 
	return false;
}

inline bool MiniScript::getTransformationsValue(const vector<ScriptVariable>& arguments, int idx, Transformations& value, bool optional) {
	if (idx >= arguments.size()) return optional;
	auto& argument = arguments[idx];
	switch(argument.type) {
		case TYPE_VOID:
			return optional;
		case TYPE_BOOLEAN:
			return optional;
		case TYPE_INTEGER:
			return optional;
		case TYPE_STRING:
			return optional;
		case TYPE_TRANSFORMATIONS:
			value = argument.transformationsValue;
			return true;
	} 
	return false;
}

inline bool MiniScript::getBooleanValue(const vector<ScriptVariable>& arguments, int idx, bool& value, bool optional) {
	if (idx >= arguments.size()) return optional;
	auto& argument = arguments[idx];
	switch(argument.type) {
		case TYPE_VOID:
			return optional;
		case TYPE_BOOLEAN:
			value = argument.booleanValue;
			return true;
			break;
		case TYPE_INTEGER:
			value = argument.integerValue != 0;
			return true;
		case TYPE_STRING:
			{
				auto lowerCaseString = StringTools::toLowerCase(argument.stringValue);
				if (lowerCaseString != "false" && lowerCaseString != "true" && lowerCaseString != "1" && lowerCaseString != "0") return optional;
				value = lowerCaseString == "true" || lowerCaseString == "1";
				return true;
			}	
		case TYPE_TRANSFORMATIONS:
			return false;
			break;
	}
	return false;
}

inline bool MiniScript::getIntegerValue(const vector<ScriptVariable>& arguments, int idx, int64_t& value, bool optional) {
	if (idx >= arguments.size()) return optional;
	auto& argument = arguments[idx];
	switch(argument.type) {
		case TYPE_VOID:
			return optional;
		case TYPE_BOOLEAN:
			value = argument.booleanValue == true?1:0;
			return true;
			break;
		case TYPE_INTEGER:
			value = argument.integerValue;
			return true;
		case TYPE_STRING:
			if (Integer::isInt(argument.stringValue) == false) return optional;
			value = Integer::parseInt(argument.stringValue);
			return true;
		case TYPE_TRANSFORMATIONS:
			return optional;
			break;
	} 
	return false;
}

void MiniScript::setStringValue(ScriptVariable& variable, const string& value) {
	variable.type = TYPE_STRING;
	variable.stringValue = value;
}

void MiniScript::setTransformationsValue(ScriptVariable& variable, const Transformations& value) {
	variable.type = TYPE_TRANSFORMATIONS;
	variable.transformationsValue = value;
}

void MiniScript::setBooleanValue(ScriptVariable& variable, bool value) {
	variable.type = TYPE_BOOLEAN;
	variable.booleanValue = value;
}

void MiniScript::setIntegerValue(ScriptVariable& variable, int64_t value) {
	variable.type = TYPE_INTEGER;
	variable.integerValue = value;
}

const string MiniScript::dumpInfo() {
	string result;
	result+="State Machine States:\n";
	{
		vector<string> states;
		for (auto& scriptStateMachineStateIt: scriptStateMachineStates) {
			string state;
			state = scriptStateMachineStateIt.second->getName() + "(" + to_string(scriptStateMachineStateIt.second->getId()) + ")";
			states.push_back(state);
		}
		sort(states.begin(), states.end());
		for (auto& state: states) result+= state+ "\n";
	}
	result+= "\n";
	result+= "Methods:\n";
	{
		vector<string> methods;
		for (auto& scriptMethodIt: scriptMethods) {
			auto scriptMethod = scriptMethodIt.second;
			string method;
			method+= scriptMethod->getMethodName();
			method+= "(";
			auto argumentIdx = 0;
			if (scriptMethod->isVariadic() == true) {
				method+="...";
			} else {
				for (auto& argumentType: scriptMethod->getArgumentTypes()) {
					if (argumentIdx > 0) method+= ", ";
					method+= argumentType.name + ": " + getScriptVariableTypeAsString(argumentType.type);
					if (argumentType.optional == true) {
						method+= "(OPTIONAL)";
					}
					argumentIdx++;
				}
			}
			method+= "): ";
			method+= getScriptVariableTypeAsString(scriptMethod->getReturnValueType());
			methods.push_back(method);
		}
		sort(methods.begin(), methods.end());
		for (auto& method: methods) result+= method + "\n";
	}
	result+= "\n";
	result+= "Variables:\n";
	{
		vector<string> variables;
		for (auto& scriptVariableIt: scriptState.variables) {
			string variable;
			auto& scriptVariable = scriptVariableIt.second;
			variable+= scriptVariableIt.first + " = " + getScriptVariableAsString(scriptVariable);
			variables.push_back(variable);
		}
		sort(variables.begin(), variables.end());
		for (auto& variable: variables) result+= variable + "\n";
	}
	return result;
}

void MiniScript::registerStateMachineStates() {
	// base
	{
		//
		class ScriptStateNextStatement: public ScriptStateMachineState {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptStateNextStatement(MiniScript* miniScript): ScriptStateMachineState(), miniScript(miniScript) {}
			virtual const string getName() override {
				return "STATE_NEXT_STATEMENT";
			}
			virtual int getId() override {
				return STATE_NEXT_STATEMENT;
			}
			virtual void execute() override {
				if (miniScript->scriptState.statementIdx == -1) {
					miniScript->scriptState.state = STATE_WAIT_FOR_CONDITION;
					return;
				}
				miniScript->executeScriptLine();
			}
		};
		registerStateMachineState(new ScriptStateNextStatement(this));
	}
	{
		//
		class ScriptStateWait: public ScriptStateMachineState {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptStateWait(MiniScript* miniScript): ScriptStateMachineState(), miniScript(miniScript) {}
			virtual const string getName() override {
				return "STATE_WAIT";
			}
			virtual int getId() override {
				return STATE_WAIT;
			}
			virtual void execute() override {
				auto now = Time::getCurrentMillis();
				if (now > miniScript->scriptState.waitStarted + miniScript->scriptState.waitTime) {
					miniScript->scriptState.state = STATE_NEXT_STATEMENT;
				}
			}
		};
		registerStateMachineState(new ScriptStateWait(this));
	}
	{
		//
		class ScriptStateWaitForCondition: public ScriptStateMachineState {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptStateWaitForCondition(MiniScript* miniScript): ScriptStateMachineState(), miniScript(miniScript) {}
			virtual const string getName() override {
				return "STATE_WAIT_FOR_CONDITION";
			}
			virtual int getId() override {
				return STATE_WAIT_FOR_CONDITION;
			}
			virtual void execute() override {
				auto now = Time::getCurrentMillis();
				if (now < miniScript->scriptState.waitStarted + miniScript->scriptState.waitTime) {
					return;
				}
				auto scriptIdxToStart = miniScript->determineScriptIdxToStart();
				if (scriptIdxToStart == -1) {
					miniScript->scriptState.waitStarted = now;
					miniScript->scriptState.waitTime = 1000LL;
					return;
				}
				miniScript->scriptState.forTimeStarted.clear();
				miniScript->scriptState.id.clear();
				miniScript->scriptState.idx = scriptIdxToStart;
				miniScript->scriptState.statementIdx = 0;
				miniScript->scriptState.waitStarted = Time::getCurrentMillis();
				miniScript->scriptState.waitTime = 0LL;
				miniScript->scriptState.state = STATE_NEXT_STATEMENT;

			}
		};
		registerStateMachineState(new ScriptStateWaitForCondition(this));
	}
}

void MiniScript::registerMethods() {
	// script base methods
	{
		//
		class ScriptMethodEnd: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEnd(MiniScript* miniScript): ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "end";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				miniScript->scriptState.statementIdx = statement.gotoStatementIdx;
				miniScript->scriptState.state = STATE_NEXT_STATEMENT;
			}
		};
		registerMethod(new ScriptMethodEnd(this));
	}
	{
		//
		class ScriptMethodForTime: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodForTime(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "time", .optional = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "forTime";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t time;
				if (miniScript->getIntegerValue(argumentValues, 0, time) == false) {
					Console::println("ScriptMethodForTime::execute(): " + getMethodName() + "(): parameter type mismatch @ argument 0: integer expected");
					miniScript->startErrorScript();
					return;
				}
				//
				auto now = Time::getCurrentMillis();
				auto timeWaitStarted = now;
				auto forTimeStartedIt = miniScript->scriptState.forTimeStarted.find(statement.line);
				if (forTimeStartedIt == miniScript->scriptState.forTimeStarted.end()) {
					miniScript->scriptState.forTimeStarted[statement.line] = timeWaitStarted;
				} else {
					timeWaitStarted = forTimeStartedIt->second;
				}
				if (Time::getCurrentMillis() > timeWaitStarted + time) {
					miniScript->scriptState.forTimeStarted.erase(statement.line);
					miniScript->scriptState.state = STATE_NEXT_STATEMENT;
					miniScript->scriptState.statementIdx = statement.gotoStatementIdx;
				}
			}
		};
		registerMethod(new ScriptMethodForTime(this));
	}
	{
		//
		class ScriptMethodScriptWaitForCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptWaitForCondition(MiniScript* miniScript): miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.waitForCondition";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				// script bindings
				miniScript->scriptState.state = STATE_WAIT_FOR_CONDITION;
				miniScript->scriptState.waitStarted = Time::getCurrentMillis();
				miniScript->scriptState.waitTime = 1000LL;
			}
		};
		registerMethod(new ScriptMethodScriptWaitForCondition(this));
		//
		class ScriptMethodScriptWait: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptWait(MiniScript* miniScript):
				ScriptMethod({
					{.type = ScriptVariableType::TYPE_INTEGER, .name = "time", .optional = false }
				}),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.wait";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t time;
				if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
					miniScript->scriptState.state = STATE_WAIT;
					miniScript->scriptState.waitStarted = Time::getCurrentMillis();
					miniScript->scriptState.waitTime = time;
				} else {
					Console::println("ScriptMethodScriptWait::execute(): " + getMethodName() + "(): parameter type mismatch @ argument 0: integer expected");
				}
			}
		};
		registerMethod(new ScriptMethodScriptWait(this));
	}
	{
		//
		class ScriptMethodConsoleLog: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodConsoleLog(MiniScript* miniScript): ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "console.log";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				for (auto& argumentValue: argumentValues) {
					Console::print(MiniScript::getScriptVariableValueString(argumentValue));
				}
				Console::println();
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodConsoleLog(this));
	}
	{
		//
		class ScriptMethodStop: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStop(MiniScript* miniScript): ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "stop";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				miniScript->scriptState.running = false;
			}
		};
		registerMethod(new ScriptMethodStop(this));
	}
	{
		//
		class ScriptMethodStop: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStop(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN), miniScript(miniScript) {}
			const string getMethodName() override {
				return "equals";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (MiniScript::getScriptVariableValueString(argumentValues[0]) != MiniScript::getScriptVariableValueString(argumentValues[i])) {
						MiniScript::setBooleanValue(returnValue, false);
						return;
					}
				}
				MiniScript::setBooleanValue(returnValue, true);
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodStop(this));
	}
	{
		//
		class ScriptMethodAnd: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAnd(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN), miniScript(miniScript) {}
			const string getMethodName() override {
				return "and";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				for (auto i = 0; i < argumentValues.size(); i++) {
					bool success;
					bool booleanValue;
					if ((success = MiniScript::getBooleanValue(argumentValues, i, booleanValue, false)) == false || booleanValue == false) {
						MiniScript::setBooleanValue(returnValue, false);
						return;
					}
				}
				MiniScript::setBooleanValue(returnValue, true);
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodAnd(this));
	}
	{
		//
		class ScriptMethodAnd: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAnd(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN), miniScript(miniScript) {}
			const string getMethodName() override {
				return "or";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				for (auto i = 0; i < argumentValues.size(); i++) {
					bool success;
					bool booleanValue;
					if ((success = MiniScript::getBooleanValue(argumentValues, i, booleanValue, false)) == true && booleanValue == true) {
						MiniScript::setBooleanValue(returnValue, true);
						return;
					}
				}
				MiniScript::setBooleanValue(returnValue, false);
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodAnd(this));
	}
	{
		//
		class ScriptMethodAdd: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAdd(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_INTEGER), miniScript(miniScript) {}
			const string getMethodName() override {
				return "add";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t result = 0LL;
				for (auto i = 0; i < argumentValues.size(); i++) {
					bool success;
					int64_t integerValue;
					if ((success = MiniScript::getIntegerValue(argumentValues, i, integerValue, false)) == true) {
						result+= integerValue;
					}
				}
				MiniScript::setIntegerValue(returnValue, result);
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodAdd(this));
	}
	{
		//
		class ScriptMethodSub: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSub(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_INTEGER), miniScript(miniScript) {}
			const string getMethodName() override {
				return "sub";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t result = 0LL;
				{
					bool success;
					int64_t integerValue;
					if ((success = MiniScript::getIntegerValue(argumentValues, 0, integerValue, false)) == true) {
						result = integerValue;
					}
				}
				for (auto i = 1; i < argumentValues.size(); i++) {
					bool success;
					int64_t integerValue;
					if ((success = MiniScript::getIntegerValue(argumentValues, i, integerValue, false)) == true) {
						result-= integerValue;
					}
				}
				MiniScript::setIntegerValue(returnValue, result);
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodSub(this));
	}
	{
		//
		class ScriptMethodMul: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMul(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_INTEGER), miniScript(miniScript) {}
			const string getMethodName() override {
				return "mul";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t result = 0LL;
				{
					bool success;
					int64_t integerValue;
					if ((success = MiniScript::getIntegerValue(argumentValues, 0, integerValue, false)) == true) {
						result = integerValue;
					}
				}
				for (auto i = 1; i < argumentValues.size(); i++) {
					bool success;
					int64_t integerValue;
					if ((success = MiniScript::getIntegerValue(argumentValues, i, integerValue, false)) == true) {
						result*= integerValue;
					}
				}
				MiniScript::setIntegerValue(returnValue, result);
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodMul(this));
	}
	{
		//
		class ScriptMethodDiv: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodDiv(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_INTEGER), miniScript(miniScript) {}
			const string getMethodName() override {
				return "div";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t result = 0LL;
				{
					bool success;
					int64_t integerValue;
					if ((success = MiniScript::getIntegerValue(argumentValues, 0, integerValue, false)) == true) {
						result = integerValue;
					}
				}
				for (auto i = 1; i < argumentValues.size(); i++) {
					bool success;
					int64_t integerValue;
					if ((success = MiniScript::getIntegerValue(argumentValues, i, integerValue, false)) == true) {
						result/= integerValue;
					}
				}
				MiniScript::setIntegerValue(returnValue, result);
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodDiv(this));
	}
	{
		//
		class ScriptMethodEmit: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEmit(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "condition", .optional = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "emit";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string condition;
				if (MiniScript::getStringValue(argumentValues, 0, condition, false) == true) {
					miniScript->emit(condition);
				}
			}
		};
		registerMethod(new ScriptMethodEmit(this));
	}
	{
		//
		class ScriptMethodInt: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodInt(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "int", .optional = false }
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "int";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool success;
				int64_t integerValue;
				if ((success = MiniScript::getIntegerValue(argumentValues, 0, integerValue, false)) == true) {
					MiniScript::setIntegerValue(returnValue, integerValue);
				} else {
					MiniScript::setIntegerValue(returnValue, 0);
				}
			}
		};
		registerMethod(new ScriptMethodInt(this));
	}
	{
		//
		class ScriptMethodBool: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodBool(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "bool", .optional = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "bool";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool success;
				bool boolValue;
				if ((success = MiniScript::getBooleanValue(argumentValues, 0, boolValue, false)) == true) {
					MiniScript::setBooleanValue(returnValue, boolValue);
				} else {
					MiniScript::setBooleanValue(returnValue, false);
				}
			}
		};
		registerMethod(new ScriptMethodBool(this));
	}
	{
		//
		class ScriptMethodString: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodString(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool success;
				string stringValue;
				if ((success = MiniScript::getStringValue(argumentValues, 0, stringValue, false)) == true) {
					MiniScript::setStringValue(returnValue, stringValue);
				} else {
					MiniScript::setStringValue(returnValue, string());
				}
			}
		};
		registerMethod(new ScriptMethodString(this));
	}
	{
		//
		class ScriptMethodSpace: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSpace(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "spaces", .optional = true }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "space";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool success;
				int64_t spaces = 1;
				if ((success = MiniScript::getIntegerValue(argumentValues, 0, spaces, true)) == true) {
					string spacesString;
					for (auto i = 0; i < spaces; i++) spacesString+= " ";
					MiniScript::setStringValue(returnValue, spacesString);
				} else {
					MiniScript::setStringValue(returnValue, string(" "));
				}
			}
		};
		registerMethod(new ScriptMethodSpace(this));
	}
}

void MiniScript::registerVariables() {
}
