#include <tdme/utilities/MiniScript.h>

#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
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
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::map;
using std::remove;
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
using tdme::utilities::MiniScript;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

string MiniScript::OPERATOR_CHARS = "!*/%+-<>&|=";

MiniScript::MiniScript() {
}

MiniScript::~MiniScript() {
	for (auto& scriptMethodIt: scriptMethods) delete scriptMethodIt.second;
	for (auto& scriptStateMachineStateIt: scriptStateMachineStates) delete scriptStateMachineStateIt.second;
}

void MiniScript::registerStateMachineState(ScriptStateMachineState* state) {
	auto scriptStateMachineStateIt = scriptStateMachineStates.find(state->getId());
	if (scriptStateMachineStateIt != scriptStateMachineStates.end()) {
		Console::println("MiniScript::registerStateMachineState(): '" + scriptFileName + "': state with id + " + to_string(state->getId()) + ", name '" + state->getName() + "' already registered.");
		return;
	}
	scriptStateMachineStates[state->getId()] = state;
}

void MiniScript::registerMethod(ScriptMethod* method) {
	auto scriptMethodsIt = scriptMethods.find(method->getMethodName());
	if (scriptMethodsIt != scriptMethods.end()) {
		Console::println("MiniScript::registerMethod(): '" + scriptFileName + "': method with name '" + method->getMethodName() + "' already registered.");
		return;
	}
	scriptMethods[method->getMethodName()] = method;
}

void MiniScript::executeScriptLine() {
	if (scriptState.scriptIdx == -1 || scriptState.statementIdx == -1 || scriptState.running == false) return;
	auto& script = scripts[scriptState.scriptIdx];
	if (script.statements.empty() == true) return;
	auto& statement = script.statements[scriptState.statementIdx];
	if (VERBOSE == true) Console::println("MiniScript::executeScriptLine(): '" + scriptFileName + "': @" + to_string(statement.line) + ": '" + statement.statement + "'");

	scriptState.statementIdx++;
	if (scriptState.statementIdx >= script.statements.size()) {
		scriptState.scriptIdx = -1;
		scriptState.statementIdx = -1;
		setScriptState(STATE_WAIT_FOR_CONDITION);
	}

	string method;
	vector<string> arguments;
	if (parseScriptStatement(statement.statement, method, arguments) == true) {
		auto returnValue = executeScriptStatement(method, arguments, statement);
	} else {
		Console::println("MiniScript::executeScriptLine(): '" + scriptFileName + "': @" + to_string(statement.line) + ": '" + statement.statement + "': parse error");
		startErrorScript();
	}
}

bool MiniScript::parseScriptStatement(const string& statement, string& method, vector<string>& arguments) {
	if (VERBOSE == true) Console::println("MiniScript::parseScriptStatement(): '" + scriptFileName + "': '" + statement + "'");
	auto argumentStartIdx = string::npos;
	auto argumentEndIdx = string::npos;
	auto bracketCount = 0;
	auto quote = false;
	string argument;
	string quotedArgument;
	for (auto i = 0; i < statement.size(); i++) {
		auto c = statement[i];
		if (c == '"' && bracketCount == 1) {
			quote = quote == false?true:false;
			quotedArgument+= c;
		} else
		if (quote == false) {
			if (c == '(') {
				bracketCount++;
				if (bracketCount > 1) {
					argument+= c;
				}
			} else
			if (c == ')') {
				bracketCount--;
				if (bracketCount == 0) {
					if (quotedArgument.empty() == false || argument.empty() == false) {
						arguments.push_back(quotedArgument.empty() == false?quotedArgument:StringTools::trim(argument));
						argument.clear();
						quotedArgument.clear();
					}
				} else {
					argument+= c;
				}
			} else
			if (c == ',') {
				if (bracketCount == 1) {
					if (quotedArgument.empty() == false || argument.empty() == false) {
						arguments.push_back(quotedArgument.empty() == false?quotedArgument:StringTools::trim(argument));
						argument.clear();
						quotedArgument.clear();
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
		} else {
			quotedArgument+= c;
		}
	}
	method = StringTools::trim(method);
	if (VERBOSE == true) {
		Console::print("MiniScript::parseScriptStatement(): '" + scriptFileName + "': method: '" + method + "', arguments: ");
		int variableIdx = 0;
		for (auto& argument: arguments) {
			if (variableIdx > 0) Console::print(", ");
			Console::print("'" + argument + "'");
			variableIdx++;
		}
		Console::println();
	}
	if (bracketCount > 0) {
		Console::println("MiniScript::parseScriptStatement(): '" + scriptFileName + "': '" + statement + "': unbalanced bracket count: " + to_string(bracketCount) + " still open");
		return false;
	}
	return true;
}

MiniScript::ScriptVariable MiniScript::executeScriptStatement(const string& method, const vector<string>& arguments, const ScriptStatement& statement) {
	string argumentsString;
	for (auto& argument: arguments) argumentsString+= (argumentsString.empty() == false?",":"") + argument;
	if (VERBOSE == true) Console::println("MiniScript::executeScriptStatement(): '" + scriptFileName + "': @" + to_string(statement.line) + ": '" + statement.statement + "': string arguments: " + method + "(" + argumentsString + ")");
	vector<ScriptVariable> argumentValues;
	ScriptVariable returnValue;
	// check if argument is a method calls return value
	for (auto& argument: arguments) {
		if (argument.empty() == false &&
			StringTools::startsWith(argument, "\"") == false &&
			StringTools::endsWith(argument, "\"") == false &&
			argument.find('(') != string::npos &&
			argument.find(')') != string::npos) {
			// method call, call method and put its return value into argument value
			string subMethod;
			vector<string> subArguments;
			if (parseScriptStatement(argument, subMethod, subArguments) == true) {
				auto argumentValue = executeScriptStatement(subMethod, subArguments, statement);
				argumentValues.push_back(argumentValue);
			} else {
				Console::println("MiniScript::executeScriptStatement(): parseScriptStatement(): '" + scriptFileName + "': @" + to_string(statement.line) +  ": '" + statement.statement + "': '" + argument + "': parse error");
				startErrorScript();
			}
		} else
		// variable
		if (StringTools::startsWith(argument, "$") == true) {
			auto variableIt = scriptState.variables.find(argument);
			if (variableIt == scriptState.variables.end()) {
				Console::println("MiniScript::executeScriptStatement(): '" + scriptFileName + "': @" + to_string(statement.line) + ": '" + statement.statement + "': " + method + "(" + argument + "): variable: '" + argument + "' does not exist");
				argumentValues.push_back(ScriptVariable());
			} else {
				auto argumentValue = variableIt->second;
				argumentValues.push_back(argumentValue);
			}
		} else {
			// literal
			ScriptVariable argumentValue;
			if (StringTools::startsWith(argument, "\"") == true &&
				StringTools::endsWith(argument, "\"") == true) {
				argumentValue.setValue(StringTools::substring(argument, 1, argument.size() - 1));
			} else {
				argumentValue.setImplicitTypedValue(argument);
			}
			argumentValues.push_back(argumentValue);
		}
	}
	if (VERBOSE == true) {
		string argumentValuesString;
		for (auto& argumentValue: argumentValues) argumentValuesString+= (argumentValuesString.empty() == false?",":"") + argumentValue.getAsString();
		Console::println("MiniScript::executeScriptStatement(): '" + scriptFileName + "': @" + to_string(statement.line) + ": '" + statement.statement + "': " + method + "(" + argumentValuesString + ")");
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
					case TYPE_FLOAT:
						{
							float floatValue;
							argumentOk = getFloatValue(argumentValues, argumentIdx, floatValue, argumentType.optional);
						}
						break;
					case TYPE_STRING:
						{
							string stringValue;
							argumentOk = getStringValue(argumentValues, argumentIdx, stringValue, argumentType.optional);
						}
						break;
					case TYPE_VECTOR3:
						{
							Vector3 vector3Value;
							argumentOk = getVector3Value(argumentValues, argumentIdx, vector3Value, argumentType.optional);
							break;
						}
					case TYPE_TRANSFORMATIONS:
						{
							Transformations transformationsValue;
							argumentOk = getTransformationsValue(argumentValues, argumentIdx, transformationsValue, argumentType.optional);
							break;
						}
				}
				if (argumentOk == false) {
					Console::println(
						string("MiniScript::executeScriptStatement(): ") +
						"'" + scriptFileName + "': " +
						"@" + to_string(statement.line) +
						": '" + statement.statement + "'" +
						": method '" + method + "'" +
						": argument value @ " + to_string(argumentIdx) + ": expected " + ScriptVariable::getTypeAsString(argumentType.type) + ", but got: " + (argumentIdx < argumentValues.size()?argumentValues[argumentIdx].getAsString():"nothing"));
				}
				argumentIdx++;
			}
			if (argumentValues.size() > scriptMethod->getArgumentTypes().size()) {
				Console::println(
					string("MiniScript::executeScriptStatement(): ") +
					"'" + scriptFileName + "': " +
					"@" + to_string(statement.line) +
					": '" + statement.statement + "'" +
					": method '" + method + "'" +
					": too many arguments: expected: " + to_string(scriptMethod->getArgumentTypes().size()) + ", got " + to_string(argumentValues.size()));
			}
		}
		scriptMethod->executeMethod(argumentValues, returnValue, statement);
		if (scriptMethod->isMixedReturnValue() == false && returnValue.getType() != scriptMethod->getReturnValueType()) {
			Console::println(
				string("MiniScript::executeScriptStatement(): ") +
				"'" + scriptFileName + "': " +
				"@" + to_string(statement.line) +
				": '" + statement.statement + "'" +
				": method '" + method + "'" +
				": return value: expected " + ScriptVariable::getTypeAsString(scriptMethod->getReturnValueType()) + ", but got: " + ScriptVariable::getTypeAsString(returnValue.getType()));
		}
		return returnValue;
	} else {
		Console::println("MiniScript::executeScriptStatement(): '" + scriptFileName + "': unknown method @" + to_string(statement.line) + ": '" + statement.statement + "': " + method + "(" + argumentsString + ")");
		startErrorScript();
	}
	return returnValue;
}

void MiniScript::emit(const string& condition) {
	if (VERBOSE == true) Console::println("MiniScript::emit(): '" + scriptFileName + "': " + condition);
	auto scriptIdx = 0;
	for (auto& script: scripts) {
		auto conditionMet = true;
		if (script.name.empty() == false && script.name == condition) {
			break;
		} else
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
	if (scriptState.scriptIdx == scriptIdx) {
		Console::println("MiniScript::emit(): '" + scriptFileName + "': script already running: " + condition);
		return;
	}
	//
	scriptState.forTimeStarted.clear();
	while (scriptState.conditionStack.empty() == false) scriptState.conditionStack.pop();
	while (scriptState.endTypeStack.empty() == false) scriptState.endTypeStack.pop();
	scriptState.enabledConditionNames.clear();
	scriptState.id.clear();
	scriptState.scriptIdx = scriptIdx;
	scriptState.statementIdx = 0;
	scriptState.timeWaitStarted = Time::getCurrentMillis();
	scriptState.timeWaitTime = 0LL;
	setScriptState(STATE_NEXT_STATEMENT);
}

void MiniScript::execute() {
	if (scriptState.state.state == STATE_NONE) return;

	// check named conditions
	auto now = Time::getCurrentMillis();
	if (scriptState.enabledConditionNames.empty() == false &&
		(scriptState.timeEnabledConditionsCheckLast == -1LL || now >= scriptState.timeEnabledConditionsCheckLast + 100LL)) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			scriptState.scriptIdx = scriptIdxToStart;
			scriptState.statementIdx = 0;
			scriptState.timeWaitStarted = Time::getCurrentMillis();
			scriptState.timeWaitTime = 0LL;
			scriptState.id.clear();
			scriptState.forTimeStarted.clear();
			while (scriptState.conditionStack.empty() == false) scriptState.conditionStack.pop();
			while (scriptState.endTypeStack.empty() == false) scriptState.endTypeStack.pop();
			scriptState.enabledConditionNames.clear();
			setScriptState(STATE_NEXT_STATEMENT);
		}
		scriptState.timeEnabledConditionsCheckLast = now;
	}

	// execute while having statements to be processed
	while (true == true) {
		// determine state machine state if it did change
		if (scriptState.state.lastStateMachineState == nullptr || scriptState.state.state != scriptState.state.lastState) {
			scriptState.state.lastState = scriptState.state.state;
			scriptState.state.lastStateMachineState = nullptr;
			auto scriptStateMachineStateIt = scriptStateMachineStates.find(scriptState.state.state);
			if (scriptStateMachineStateIt != scriptStateMachineStates.end()) {
				scriptState.state.lastStateMachineState = scriptStateMachineStateIt->second;
			}
		}

		// execute state machine
		if (scriptState.state.lastStateMachineState != nullptr) {
			scriptState.state.lastStateMachineState->execute();
		} else {
			Console::println("MiniScript::executeStateMachine(): '" + scriptFileName + "': unknown state with id: " + to_string(scriptState.state.state));
			break;
		}

		// break if no next statement but other state machine state or not running
		if (scriptState.state.state != STATE_NEXT_STATEMENT || scriptState.running == true) break;
	}
}

void MiniScript::loadScript(const string& pathName, const string& fileName) {
	scriptValid = true;
	scriptPathName = pathName;
	scriptFileName = fileName;

	// shutdown methods and machine states
	for (auto& scriptMethodIt: scriptMethods) delete scriptMethodIt.second;
	for (auto& scriptStateMachineStateIt: scriptStateMachineStates) delete scriptStateMachineStateIt.second;
	scriptMethods.clear();
	scriptStateMachineStates.clear();

	// shutdown script state
	scriptState.variables.clear();
	scriptState.forTimeStarted.clear();
	while (scriptState.conditionStack.empty() == false) scriptState.conditionStack.pop();
	while (scriptState.endTypeStack.empty() == false) scriptState.endTypeStack.pop();
	scriptState.enabledConditionNames.clear();
	scriptState.id.clear();
	scriptState.statementIdx = 0;
	scriptState.timeWaitStarted = Time::getCurrentMillis();
	scriptState.timeWaitTime = 0LL;
	scriptState.running = false;
	setScriptState(STATE_WAIT_FOR_CONDITION);

	//
	registerStateMachineStates();
	registerMethods();
	registerVariables();

	//
	vector<string> scriptLines;
	try {
		FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, scriptLines);
	} catch (FileSystemException& fse)	{
		Console::println("MiniScript::loadScript(): " + pathName + "/" + fileName + ": an error occurred: " + fse.what());
	}
	auto haveCondition = false;
	auto line = 1;
	auto statementIdx = 1;
	enum GotoStatementType { GOTOSTATEMENTTYPE_FOR, GOTOSTATEMENTTYPE_IF, GOTOSTATEMENTTYPE_ELSE, GOTOSTATEMENTTYPE_ELSEIF };
	struct GotoStatementStruct {
		GotoStatementType type;
		int statementIdx;
	};
	stack<GotoStatementStruct> gotoStatementStack;
	for (auto scriptLine: scriptLines) {
		scriptLine = StringTools::trim(scriptLine);
		if (StringTools::startsWith(scriptLine, "#") == true || scriptLine.empty() == true) {
			line++;
			continue;
		}
		if (haveCondition == false) {
			if (StringTools::startsWith(scriptLine, "on:") == true || StringTools::startsWith(scriptLine, "on-enabled:") == true) {
				haveCondition = true;
				Script::ConditionType conditionType = StringTools::startsWith(scriptLine, "on-enabled:")?Script::CONDITIONTYPE_ONENABLED:Script::CONDITIONTYPE_ON;
				scriptLine =
					conditionType == Script::CONDITIONTYPE_ONENABLED?
						StringTools::trim(StringTools::substring(scriptLine, string("on-enabled:").size())):
						StringTools::trim(StringTools::substring(scriptLine, string("on:").size()));
				string name;
				auto scriptLineNameSeparatorIdx = scriptLine.rfind(":=");
				if (scriptLineNameSeparatorIdx != string::npos) {
					name = StringTools::trim(StringTools::substring(scriptLine, scriptLineNameSeparatorIdx + 2));
					scriptLine = StringTools::trim(StringTools::substring(scriptLine, 0, scriptLineNameSeparatorIdx));
				}
				vector<string> conditions;
				StringTokenizer t1;
				t1.tokenize(scriptLine, ";");
				while (t1.hasMoreTokens()) conditions.push_back(doStatementPreProcessing(StringTools::trim(t1.nextToken())));
				statementIdx = 0;
				scripts.push_back(
					{
						.conditionType = conditionType,
						.line = line,
						.conditions = conditions,
						.name = name,
						.statements = {}
					}
				);
			} else {
				Console::println("MiniScript::MiniScript(): '" + scriptFileName + "': @" + to_string(line) + ": expecting 'on:' or 'on-enabled:' script condition");
				scriptValid = false;
			}
		} else {
			if (StringTools::startsWith(scriptLine, "on:") == true) {
				Console::println("MiniScript::loadScript(): '" + scriptFileName + ": unbalanced forXXX/if/elseif/else/end");
				scriptValid = false;
			} else
			if (scriptLine == "end") {
				if (gotoStatementStack.empty() == false) {
					auto gotoStatementStackElement = gotoStatementStack.top();
					gotoStatementStack.pop();
					switch(gotoStatementStackElement.type) {
						case GOTOSTATEMENTTYPE_FOR:
							{
								scripts[scripts.size() - 1].statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = scriptLine, .gotoStatementIdx = gotoStatementStackElement.statementIdx });
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
							}
							break;
						case GOTOSTATEMENTTYPE_IF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = scriptLine, .gotoStatementIdx = -1 });
							}
							break;
						case GOTOSTATEMENTTYPE_ELSE:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = scriptLine, .gotoStatementIdx = -1 });
							}
							break;
						case GOTOSTATEMENTTYPE_ELSEIF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = scriptLine, .gotoStatementIdx = -1 });
							}
							break;
					}
				} else{
					scripts[scripts.size() - 1].statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = "end", .gotoStatementIdx = -1 });
					haveCondition = false;
				}
			} else
			if (scriptLine == "else") {
				if (gotoStatementStack.empty() == false) {
					auto gotoStatementStackElement = gotoStatementStack.top();
					gotoStatementStack.pop();
					switch(gotoStatementStackElement.type) {
						case GOTOSTATEMENTTYPE_IF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = scriptLine, .gotoStatementIdx = -1 });
							}
							break;
						case GOTOSTATEMENTTYPE_ELSEIF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = scriptLine, .gotoStatementIdx = -1 });
							}
							break;
						default:
							Console::println("MiniScript::MiniScript(): '" + scriptFileName + ": @" + to_string(line) + ": else without if/elseif");
							scriptValid = false;
							break;
					}
					gotoStatementStack.push(
						{
							.type = GOTOSTATEMENTTYPE_ELSE,
							.statementIdx = statementIdx
						}
					);
				} else {
					Console::println("MiniScript::MiniScript(): '" + scriptFileName + ": @" + to_string(line) + ": else without if");
					scriptValid = false;
				}
			} else
			if (StringTools::regexMatch(scriptLine, "^elseif[\\s]*\\(.*\\)$") == true) {
				scriptLine = doStatementPreProcessing(scriptLine);
				if (gotoStatementStack.empty() == false) {
					auto gotoStatementStackElement = gotoStatementStack.top();
					gotoStatementStack.pop();
					switch(gotoStatementStackElement.type) {
						case GOTOSTATEMENTTYPE_IF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = scriptLine, .gotoStatementIdx = -1 });
							}
							break;
						case GOTOSTATEMENTTYPE_ELSEIF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = scriptLine, .gotoStatementIdx = -1 });
							}
							break;
						default:
							Console::println("MiniScript::MiniScript(): '" + scriptFileName + ": @" + to_string(line) + ": elseif without if");
							scriptValid = false;
							break;
					}
					gotoStatementStack.push(
						{
							.type = GOTOSTATEMENTTYPE_ELSEIF,
							.statementIdx = statementIdx
						}
					);
				} else {
					Console::println("MiniScript::MiniScript(): '" + scriptFileName + ": @" + to_string(line) + ": elseif without if");
				}
			} else {
				scriptLine = doStatementPreProcessing(scriptLine);
				if (StringTools::regexMatch(scriptLine, "^forTime[\\s]*\\(.*\\)$") == true ||
					StringTools::regexMatch(scriptLine, "^forCondition[\\s]*\\(.*\\)$") == true) {
					gotoStatementStack.push(
						{
							.type = GOTOSTATEMENTTYPE_FOR,
							.statementIdx = statementIdx
						}
					);
				} else
				if (StringTools::regexMatch(scriptLine, "^if[\\s]*\\(.*\\)$") == true) {
					gotoStatementStack.push(
						{
							.type = GOTOSTATEMENTTYPE_IF,
							.statementIdx = statementIdx
						}
					);
				}
				scripts[scripts.size() - 1].statements.push_back({ .line = line, .statementIdx = statementIdx, .statement = scriptLine, .gotoStatementIdx = -1 });
			}
			statementIdx++;
		}
		line++;
	}

	// check for unbalanced forXXX/if/elseif/else/end
	if (scriptValid == true && gotoStatementStack.empty() == false) {
		scriptValid = false;
		// TODO: give some more info about line and statement of not closed condition
		Console::println("MiniScript::loadScript(): '" + scriptFileName + ": unbalanced forXXX/if/elseif/else/end");
		return;
	}

	// check for initialize and error condition
	auto haveInitializeScript = false;
	auto haveErrorScript = false;
	for (auto& script: scripts) {
		if (script.conditionType == Script::CONDITIONTYPE_ONENABLED) {
			// no op
		} else
		if (script.conditions.size() == 1 && script.conditions[0] == "initialize") {
			haveInitializeScript = true;
		} else
		if (script.conditions.size() == 1 && script.conditions[0] == "error") {
			haveErrorScript = true;
		}
	}
	if (haveInitializeScript == false || haveErrorScript == false) {
		scriptValid = false;
		Console::println("MiniScript::loadScript(): '" + scriptFileName + ": script needs to define a initialize and error condition");
		return;

	}

	//
	startScript();
}

void MiniScript::startScript() {
	if (VERBOSE == true) Console::println("MiniScript::startScript(): '" + scriptFileName + ": starting script.");
	if (scriptValid == false) {
		Console::println("MiniScript::startScript(): '" + scriptFileName + "': script not valid: not starting");
		return;
	}
	scriptState.variables.clear();
	scriptState.running = true;
	registerVariables();
	emit("initialize");
}

int MiniScript::determineScriptIdxToStart() {
	if (VERBOSE == true) Console::println("MiniScript::determineScriptIdxToStart()");
	auto currentScriptStateScript = scriptState.state;
	auto nothingScriptIdx = -1;
	auto scriptIdx = 0;
	for (auto& script: scripts) {
		if (script.conditionType == Script::CONDITIONTYPE_ONENABLED) {
			// no op
		} else
		if (script.conditions.size() == 1 && script.conditions[0] == "nothing") {
			nothingScriptIdx = scriptIdx;
			// no op
		} else
		if (script.conditions.size() == 1 &&
			script.conditions[0].find('(') == string::npos &&
			script.conditions[0].rfind(')') == string::npos) {
			// user emit condition
		} else {
			auto conditionMet = true;
			for (auto& condition: script.conditions) {
				string method;
				vector<string> arguments;
				if (parseScriptStatement(condition, method, arguments) == true) {
					auto returnValue = executeScriptStatement(
						method,
						arguments,
						{
							.line = script.line,
							.statementIdx = 0,
							.statement = condition,
							.gotoStatementIdx = -1
						}
					);
					auto returnValueBoolValue = false;
					if (returnValue.getBooleanValue(returnValueBoolValue, false) == false) {
						Console::println("MiniScript::determineScriptIdxToStart(): '" + condition + "': expecting boolean return value, but got: " + returnValue.getAsString());
						conditionMet = false;
						break;
					} else
					if (returnValueBoolValue == false) {
						conditionMet = false;
						break;
					}
				} else {
					Console::println("MiniScript::determineScriptIdxToStart(): '" + scriptFileName + "': @" + to_string(script.line) + ": '" + condition + "': parse error");
				}
			}
			if (conditionMet == false) {
				if (VERBOSE == true) {
					Console::print("MiniScript::determineScriptIdxToStart(): ");
					for (auto& condition: script.conditions) Console::print(condition + "; ");
					Console::println(": FAILED");
				}	
			} else {
				if (VERBOSE == true) {
					Console::print("MiniScript::determineScriptIdxToStart(): ");
					for (auto& condition: script.conditions) Console::print(condition + "; ");
					Console::println(": OK");
				}
				scriptState.state = currentScriptStateScript;
				return scriptIdx;
			}
		}
		scriptIdx++;
	}
	scriptState.state = currentScriptStateScript;
	return nothingScriptIdx;
}

int MiniScript::determineNamedScriptIdxToStart() {
	if (VERBOSE == true) Console::println("MiniScript::determineNamedScriptIdxToStart()");
	auto currentScriptStateState = scriptState.state;
	// TODO: we could have a hash map here to speed up enabledConditionName -> script lookup
	for (auto& enabledConditionName: scriptState.enabledConditionNames) {
		auto scriptIdx = 0;
		for (auto& script: scripts) {
			if (script.conditionType != Script::CONDITIONTYPE_ONENABLED ||
				script.name != enabledConditionName) {
				// no op
			} else {
				auto conditionMet = true;
				for (auto& condition: script.conditions) {
					string method;
					vector<string> arguments;
					if (parseScriptStatement(condition, method, arguments) == true) {
						auto returnValue = executeScriptStatement(
							method,
							arguments,
							{
								.line = script.line,
								.statementIdx = 0,
								.statement = condition,
								.gotoStatementIdx = -1
							}
						);
						auto returnValueBoolValue = false;
						if (returnValue.getBooleanValue(returnValueBoolValue, false) == false) {
							Console::println("MiniScript::determineNamedScriptIdxToStart(): '" + condition + "': expecting boolean return value, but got: " + returnValue.getAsString());
							conditionMet = false;
							break;
						} else
						if (returnValueBoolValue == false) {
							conditionMet = false;
							break;
						}
					} else {
						Console::println("MiniScript::determineNamedScriptIdxToStart(): '" + scriptFileName + "': @" + to_string(script.line) + ": '" + condition + "': parse error");
					}
				}
				if (conditionMet == false) {
					if (VERBOSE == true) {
						Console::print("MiniScript::determineNamedScriptIdxToStart(): ");
						for (auto& condition: script.conditions) Console::print(condition + "; ");
						Console::println(": FAILED");
					}
				} else {
					if (VERBOSE == true) {
						Console::print("MiniScript::determineNamedScriptIdxToStart(): ");
						for (auto& condition: script.conditions) Console::print(condition + "; ");
						Console::println(": OK");
					}
					scriptState.state = currentScriptStateState;
					return scriptIdx;
				}
			}
			scriptIdx++;
		}
	}
	scriptState.state = currentScriptStateState;
	return -1;
}

bool MiniScript::getNextStatementOperator(const string& statement, MiniScript::ScriptStatementOperator& nextOperator) {
	//
	auto bracketCount = 0;
	auto quote = false;
	for (auto i = 0; i < statement.size(); i++) {
		auto c = statement[i];
		if (c == '"') {
			quote = quote == false?true:false;
		} else
		if (quote == false) {
			if (c == '(') {
				bracketCount++;
			} else
			if (c == ')') {
				bracketCount--;
			} else {
				for (int j = OPERATOR_NONE + 1; j < OPERATOR_MAX; j++) {
					auto priorizedOperator = static_cast<ScriptOperator>(j);
					string operatorCandidate;
					auto operatorString = getOperatorAsString(priorizedOperator);
					if (operatorString.size() == 1) operatorCandidate+= statement[i];
					if (operatorString.size() == 2 && i + 1 < statement.size()) {
						operatorCandidate+= statement[i];
						operatorCandidate+= statement[i + 1];
					}
					if (operatorString == operatorCandidate && (nextOperator.idx == -1 || priorizedOperator > nextOperator.scriptOperator)) {
						if (i > 0 && isOperatorChar(statement[i - 1]) == true) {
							continue;
						}
						if (operatorString.size() == 2 && i + 2 < statement.size() && isOperatorChar(statement[i + 2]) == true) {
							continue;
						} else
						if (operatorString.size() == 1 && i + 1 < statement.size() && isOperatorChar(statement[i + 1]) == true) {
							continue;
						}
						if (priorizedOperator == OPERATOR_SUBTRACTION) {
							auto leftArgumentLeft = 0;
							auto leftArgument = findLeftArgument(statement, i - 1, leftArgumentLeft);
							if (leftArgument.length() == 0) continue;
						}
						nextOperator.idx = i;
						nextOperator.scriptOperator = priorizedOperator;
					}
				}
			}
		}
	}

	//
	if (bracketCount > 0) {
		Console::println("MiniScript::getNextStatementOperator(): '" + scriptFileName + "': '" + statement + "': unbalanced bracket count: " + to_string(bracketCount) + " still open");
		return false;
	}
	//
	return nextOperator.idx != -1;
}

const string MiniScript::trimArgument(const string& argument) {
	auto processedArgument = StringTools::trim(argument);
	if (StringTools::startsWith(processedArgument, "(") == true && StringTools::endsWith(processedArgument, ")") == true) {
		processedArgument = StringTools::substring(processedArgument, 1, processedArgument.size() - 1);
	}
	return processedArgument;
}

const string MiniScript::findRightArgument(const string statement, int position, int& length) {
	//
	auto bracketCount = 0;
	auto quote = false;
	string argument;
	length = 0;
	for (auto i = position; i < statement.size(); i++) {
		auto c = statement[i];
		if (c == '"' && bracketCount == 1) {
			quote = quote == false?true:false;
			argument+= c;
		} else
		if (quote == false) {
			if (c == '(') {
				bracketCount++;
				argument+= c;
			} else
			if (c == ')') {
				bracketCount--;
				if (bracketCount < 0) return trimArgument(argument);
				argument+= c;
			} else
			if (c == ',') {
				if (bracketCount == 0) return trimArgument(argument);
				argument+= c;
			} else {
				argument+= c;
			}
		} else
		if (quote == true) {
			argument+= c;
		}
		length++;
	}
	return trimArgument(argument);
}

const string MiniScript::findLeftArgument(const string statement, int position, int& length) {
	//
	auto bracketCount = 0;
	auto quote = false;
	string argument;
	length = 0;
	for (int i = position; i >= 0; i--) {
		auto c = statement[i];
		if (c == '"' && bracketCount == 1) {
			quote = quote == false?true:false;
			argument = c + argument;
		} else
		if (quote == false) {
			if (c == ')') {
				bracketCount++;
				argument = c + argument;
			} else
			if (c == '(') {
				bracketCount--;
				if (bracketCount < 0) return trimArgument(argument);
				argument = c + argument;
			} else
			if (c == ',') {
				if (bracketCount == 0) return trimArgument(argument);
				argument = c + argument;
			} else {
				argument = c + argument;
			}
		} else
		if (quote == true) {
			argument = c + argument;
		}
		length++;
	}
	return trimArgument(argument);
}

const string MiniScript::doStatementPreProcessing(const string& statement) {
	auto preprocessedStatement = statement;
	ScriptStatementOperator nextOperators;
	while (getNextStatementOperator(preprocessedStatement, nextOperators) == true) {
		auto methodIt = scriptOperators.find(nextOperators.scriptOperator);
		if (methodIt == scriptOperators.end()) {
			Console::println("MiniScript::doStatementPreProcessing(): operator found in: '" + preprocessedStatement + "'@" + to_string(nextOperators.idx) + ": no method found");
			// TODO: error handling
			return preprocessedStatement;
		}
		auto method = methodIt->second;
		if (method->getArgumentTypes().size() == 1) {
			// find the single argument right
			auto operatorString = getOperatorAsString(nextOperators.scriptOperator);
			int rightArgumentLength = 0;
			auto rightArgument = findRightArgument(preprocessedStatement, nextOperators.idx + operatorString.size(), rightArgumentLength);
			// substitute with method call
			preprocessedStatement =
				StringTools::substring(preprocessedStatement, 0, nextOperators.idx) +
				method->getMethodName() + "(" + rightArgument + ")" +
				StringTools::substring(preprocessedStatement, nextOperators.idx + operatorString.size() + rightArgumentLength, preprocessedStatement.size());
		} else
		if (method->isVariadic() == true ||
			method->getArgumentTypes().size() == 2) {
			auto operatorString = getOperatorAsString(nextOperators.scriptOperator);
			// find the first argument left
			int leftArgumentLength = 0;
			auto leftArgument = findLeftArgument(preprocessedStatement, nextOperators.idx - 1, leftArgumentLength);
			// find the first argument right
			int rightArgumentLength = 0;
			auto rightArgument = findRightArgument(preprocessedStatement, nextOperators.idx + operatorString.size(), rightArgumentLength);
			//
			if (nextOperators.scriptOperator == OPERATOR_SET) {
				leftArgument = "\"" + leftArgument + "\"";
			}
			// substitute with method call
			preprocessedStatement =
				StringTools::substring(preprocessedStatement, 0, nextOperators.idx - leftArgumentLength) +
				method->getMethodName() + "(" + leftArgument + ", " + rightArgument + ")" +
				StringTools::substring(preprocessedStatement, nextOperators.idx + operatorString.size() + rightArgumentLength, preprocessedStatement.size());
		}
		nextOperators = ScriptStatementOperator();
	}
	return preprocessedStatement;
}

const string MiniScript::getInformation() {
	string result;
	result+= "Script: " + scriptPathName + "/" + scriptFileName + "\n\n";
	for (auto& script: scripts) {
		switch(script.conditionType) {
			case Script::CONDITIONTYPE_ON: result+= "on: "; break;
			case Script::CONDITIONTYPE_ONENABLED: result+= "on-enabled: "; break;
		}
		for (auto& condition: script.conditions)
			result+= condition + "; ";
		if (script.name.empty() == false) {
			result+= "name = '" + script.name + "';\n";
		} else {
			result+= "\n";
		}
		for (auto& scriptStatement: script.statements) {
			result+= "\t" + to_string(scriptStatement.statementIdx) + ": " + scriptStatement.statement + (scriptStatement.gotoStatementIdx != -1?" (gotoStatement " + to_string(scriptStatement.gotoStatementIdx) + ")":"") + "\n";
		}
		result+= "\n";
	}

	//
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

	//
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
					method+= argumentType.name + ": " + ScriptVariable::getTypeAsString(argumentType.type);
					if (argumentType.optional == true) {
						method+= "(OPTIONAL)";
					}
					argumentIdx++;
				}
			}
			method+= "): ";
			method+= scriptMethod->isMixedReturnValue() == true?"Mixed":ScriptVariable::getTypeAsString(scriptMethod->getReturnValueType());
			methods.push_back(method);
		}
		sort(methods.begin(), methods.end());
		for (auto& method: methods) result+= method + "\n";
	}
	result+= "\n";

	//
	result+= "Operators:\n";
	{
		vector<string> operators;
		for (auto& scriptOperatorIt: scriptOperators) {
			auto method = scriptOperatorIt.second;
			string operatorString;
			operatorString+= getOperatorAsString(method->getOperator());
			operatorString+= " --> ";
			operatorString+= method->getMethodName();
			operatorString+= "(";
			auto argumentIdx = 0;
			if (method->isVariadic() == true) {
				operatorString+="...";
			} else {
				for (auto& argumentType: method->getArgumentTypes()) {
					if (argumentIdx > 0) operatorString+= ", ";
					operatorString+= argumentType.name + ": " + ScriptVariable::getTypeAsString(argumentType.type);
					if (argumentType.optional == true) {
						operatorString+= "(OPTIONAL)";
					}
					argumentIdx++;
				}
			}
			operatorString+= "): ";
			operatorString+= method->isMixedReturnValue() == true?"Mixed":ScriptVariable::getTypeAsString(method->getReturnValueType());
			operators.push_back(operatorString);
		}
		sort(operators.begin(), operators.end());
		for (auto& method: operators) result+= method + "\n";
	}
	result+= "\n";

	//
	result+= "Variables:\n";
	{
		vector<string> variables;
		for (auto& scriptVariableIt: scriptState.variables) {
			string variable;
			auto& scriptVariable = scriptVariableIt.second;
			variable+= scriptVariableIt.first + " = " + scriptVariable.getAsString();
			variables.push_back(variable);
		}
		sort(variables.begin(), variables.end());
		for (auto& variable: variables) result+= variable + "\n";
	}

	//
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
					miniScript->scriptState.enabledConditionNames.clear();
					miniScript->scriptState.timeEnabledConditionsCheckLast = -1LL;
					miniScript->setScriptState(STATE_WAIT_FOR_CONDITION);
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
				if (now > miniScript->scriptState.timeWaitStarted + miniScript->scriptState.timeWaitTime) {
					miniScript->setScriptState(STATE_NEXT_STATEMENT);
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
				if (now < miniScript->scriptState.timeWaitStarted + miniScript->scriptState.timeWaitTime) {
					return;
				}
				auto scriptIdxToStart = miniScript->determineScriptIdxToStart();
				if (scriptIdxToStart == -1) {
					miniScript->scriptState.timeWaitStarted = now;
					miniScript->scriptState.timeWaitTime = 100LL;
					return;
				}
				miniScript->scriptState.scriptIdx = scriptIdxToStart;
				miniScript->scriptState.statementIdx = 0;
				miniScript->scriptState.timeWaitStarted = Time::getCurrentMillis();
				miniScript->scriptState.timeWaitTime = 0LL;
				miniScript->scriptState.id.clear();
				miniScript->scriptState.forTimeStarted.clear();
				while (miniScript->scriptState.conditionStack.empty() == false) miniScript->scriptState.conditionStack.pop();
				while (miniScript->scriptState.endTypeStack.empty() == false) miniScript->scriptState.endTypeStack.pop();
				miniScript->scriptState.enabledConditionNames.clear();
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
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
				if (miniScript->scriptState.endTypeStack.empty() == true) {
					if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
						Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
						miniScript->startErrorScript();
					}
					return;
				}
				auto endType = miniScript->scriptState.endTypeStack.top();
				miniScript->scriptState.endTypeStack.pop();
				switch(endType) {
					case ScriptState::ENDTYPE_FOR:
						// no op
						break;
					case ScriptState::ENDTYPE_IF:
						miniScript->scriptState.conditionStack.pop();
						break;
				}
				if (statement.gotoStatementIdx != STATE_NONE) {
					miniScript->scriptState.statementIdx = statement.gotoStatementIdx;
					miniScript->setScriptState(STATE_NEXT_STATEMENT);
				}
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
					Console::println("ScriptMethodForTime::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: integer expected");
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
				//
				if (Time::getCurrentMillis() > timeWaitStarted + time) {
					miniScript->scriptState.forTimeStarted.erase(statement.line);
					miniScript->scriptState.statementIdx = statement.gotoStatementIdx;
					miniScript->setScriptState(STATE_NEXT_STATEMENT);
				} else {
					miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
				}
			}
		};
		registerMethod(new ScriptMethodForTime(this));
	}
	{
		//
		class ScriptMethodForCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodForCondition(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "forCondition";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
					Console::println("ScriptMethodForCondition::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: boolean expected");
					miniScript->startErrorScript();
					return;
				}
				//
				auto now = Time::getCurrentMillis();
				if (booleanValue == false) {
					miniScript->setScriptState(STATE_NEXT_STATEMENT);
					miniScript->scriptState.statementIdx = statement.gotoStatementIdx;
				} else {
					miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
				}
			}
		};
		registerMethod(new ScriptMethodForCondition(this));
	}
	{
		//
		class ScriptMethodIfCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodIfCondition(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "if";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
					Console::println("ScriptMethodIfCondition::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: boolean expected");
					miniScript->startErrorScript();
					return;
				}
				//
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_IF);
				//
				miniScript->scriptState.conditionStack.push(booleanValue);
				if (booleanValue == false) {
					miniScript->scriptState.statementIdx = statement.gotoStatementIdx;
					miniScript->setScriptState(STATE_NEXT_STATEMENT);
				}
			}
		};
		registerMethod(new ScriptMethodIfCondition(this));
	}
	{
		//
		class ScriptMethodElseIfCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodElseIfCondition(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "elseif";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
					Console::println("ScriptMethodElseIfCondition::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: boolean expected");
					miniScript->startErrorScript();
					return;
				}
				if (miniScript->scriptState.conditionStack.empty() == true) {
					Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
					miniScript->startErrorScript();
					return;
				}
				//
				auto conditionStackElement = miniScript->scriptState.conditionStack.top();
				if (conditionStackElement == false) {
					miniScript->scriptState.conditionStack.pop();
					miniScript->scriptState.conditionStack.push(booleanValue);
				}
				if (conditionStackElement == true || booleanValue == false) {
					miniScript->scriptState.statementIdx = statement.gotoStatementIdx;
					miniScript->setScriptState(STATE_NEXT_STATEMENT);
				}
			}
		};
		registerMethod(new ScriptMethodElseIfCondition(this));
	}
	{
		//
		class ScriptMethodElse: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodElse(MiniScript* miniScript): ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "else";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (miniScript->scriptState.conditionStack.empty() == true) {
					Console::println("ScriptMethodElse::executeMethod(): else without if");
					miniScript->startErrorScript();
					return;
				}
				auto conditionStackElement = miniScript->scriptState.conditionStack.top();
				if (conditionStackElement == true) {
					miniScript->scriptState.statementIdx = statement.gotoStatementIdx;
					miniScript->setScriptState(STATE_NEXT_STATEMENT);
				}
			}
		};
		registerMethod(new ScriptMethodElse(this));
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
				miniScript->scriptState.timeWaitStarted = Time::getCurrentMillis();
				miniScript->scriptState.timeWaitTime = 100LL;
				miniScript->setScriptState(STATE_WAIT_FOR_CONDITION);
			}
		};
		registerMethod(new ScriptMethodScriptWaitForCondition(this));
	}
	{
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
					miniScript->scriptState.timeWaitStarted = Time::getCurrentMillis();
					miniScript->scriptState.timeWaitTime = time;
					miniScript->setScriptState(STATE_WAIT);
				} else {
					Console::println("ScriptMethodScriptWait::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: integer expected");
				}
			}
		};
		registerMethod(new ScriptMethodScriptWait(this));
	}
	{
		//
		class ScriptMethodScriptEmit: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptEmit(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "condition", .optional = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.emit";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string condition;
				if (MiniScript::getStringValue(argumentValues, 0, condition, false) == true) {
					miniScript->emit(condition);
				} else {
					Console::println("ScriptMethodScriptWait::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
					return;
				}
			}
		};
		registerMethod(new ScriptMethodScriptEmit(this));
	}
	{
		//
		class ScriptMethodScriptEnableNamedCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptEnableNamedCondition(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "name", .optional = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.enableNamedCondition";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string name;
				if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
					miniScript->scriptState.enabledConditionNames.erase(
						remove(
							miniScript->scriptState.enabledConditionNames.begin(),
							miniScript->scriptState.enabledConditionNames.end(),
							name
						),
						miniScript->scriptState.enabledConditionNames.end()
					);
					miniScript->scriptState.enabledConditionNames.push_back(name);
				} else {
					Console::println("ScriptMethodScriptWait::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
					return;
				}
			}
		};
		registerMethod(new ScriptMethodScriptEnableNamedCondition(this));
	}
	{
		//
		class ScriptMethodScriptDisableNamedCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptDisableNamedCondition(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "name", .optional = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.disableNamedCondition";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string name;
				if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
					miniScript->scriptState.enabledConditionNames.erase(
						remove(
							miniScript->scriptState.enabledConditionNames.begin(),
							miniScript->scriptState.enabledConditionNames.end(),
							name
						),
						miniScript->scriptState.enabledConditionNames.end()
					);
				} else {
					Console::println("ScriptMethodScriptWait::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
					return;
				}
			}
		};
		registerMethod(new ScriptMethodScriptDisableNamedCondition(this));
	}
	{
		//
		class ScriptMethodScriptGetNamedConditions: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptGetNamedConditions(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.getNamedConditions";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string result;
				for (auto& namedCondition: miniScript->scriptState.enabledConditionNames) {
					result+= result.empty() == false?",":namedCondition;
				}
				returnValue.setValue(result);
			}
		};
		registerMethod(new ScriptMethodScriptGetNamedConditions(this));
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
					Console::print(argumentValue.getValueString());
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
		class ScriptMethodStringStop: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringStop(MiniScript* miniScript): ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.stop";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				miniScript->scriptState.running = false;
				miniScript->scriptState.scriptIdx = -1;
				miniScript->scriptState.statementIdx = 0;
				miniScript->scriptState.timeWaitStarted = -1LL;
				miniScript->scriptState.timeWaitTime = 0LL;
				miniScript->scriptState.id.clear();
				miniScript->scriptState.variables.clear();
				miniScript->scriptState.forTimeStarted.clear();
				while (miniScript->scriptState.conditionStack.empty() == false) miniScript->scriptState.conditionStack.pop();
				while (miniScript->scriptState.endTypeStack.empty() == false) miniScript->scriptState.endTypeStack.pop();
				miniScript->scriptState.enabledConditionNames.clear();
				miniScript->scriptState.timeEnabledConditionsCheckLast = -1LL;
				miniScript->setScriptState(STATE_NONE);
			}
		};
		registerMethod(new ScriptMethodStringStop(this));
	}
	// equality
	{
		//
		class ScriptMethodEquals: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEquals(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN), miniScript(miniScript) {}
			const string getMethodName() override {
				return "equals";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
						returnValue.setValue(false);
						return;
					}
				}
				returnValue.setValue(true);
			}
			bool isVariadic() override {
				return true;
			}
			ScriptOperator getOperator() override {
				return OPERATOR_EQUALS;
			}
		};
		registerMethod(new ScriptMethodEquals(this));
	}
	{
		//
		class ScriptMethodNotEqual: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodNotEqual(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN), miniScript(miniScript) {}
			const string getMethodName() override {
				return "notequal";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueString() == argumentValues[i].getValueString()) {
						returnValue.setValue(false);
						return;
					}
				}
				returnValue.setValue(true);
			}
			bool isVariadic() override {
				return true;
			}
			ScriptOperator getOperator() override {
				return OPERATOR_NOTEQUAL;
			}
		};
		registerMethod(new ScriptMethodNotEqual(this));
	}
	// int methods
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
				int64_t integerValue;
				if (MiniScript::getIntegerValue(argumentValues, 0, integerValue, false) == true) {
					returnValue.setValue(integerValue);
				} else {
					Console::println("ScriptMethodInt::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: integer expected");
					miniScript->startErrorScript();
					return;
				}
			}
		};
		registerMethod(new ScriptMethodInt(this));
	}
	// float methods
	{
		//
		class ScriptMethodFloat: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodFloat(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "float", .optional = false }
					},
					ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "float";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					returnValue.setValue(floatValue);
				} else {
					Console::println("ScriptMethodFloat::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript();
					return;
				}
			}
		};
		registerMethod(new ScriptMethodFloat(this));
	}
	//
	{
		//
		class ScriptMethodGreater: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGreater(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "a", .optional = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "b", .optional = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "greater";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA > floatValueB);
				} else {
					Console::println("ScriptMethodFGreater::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			ScriptOperator getOperator() override {
				return OPERATOR_GREATER;
			}
		};
		registerMethod(new ScriptMethodGreater(this));
	}
	{
		//
		class ScriptMethodGreaterEquals: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGreaterEquals(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "a", .optional = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "b", .optional = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "greaterequals";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA >= floatValueB);
				} else {
					Console::println("ScriptMethodFGreater::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			ScriptOperator getOperator() override {
				return OPERATOR_GREATEREQUALS;
			}
		};
		registerMethod(new ScriptMethodGreaterEquals(this));
	}
	{
		//
		class ScriptMethodLesser: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodLesser(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "a", .optional = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "b", .optional = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "lesser";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA < floatValueB);
				} else {
					Console::println("ScriptMethodFLesser::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			ScriptOperator getOperator() override {
				return OPERATOR_LESSER;
			}
		};
		registerMethod(new ScriptMethodLesser(this));
	}
	{
		//
		class ScriptMethodLesserEquals: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodLesserEquals(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "a", .optional = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "b", .optional = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "lesserequals";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA <= floatValueB);
				} else {
					Console::println("ScriptMethodFLesser::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript();
					return;
				}
			}
			ScriptOperator getOperator() override {
				return OPERATOR_LESSEREQUALS;
			}
		};
		registerMethod(new ScriptMethodLesserEquals(this));
	}
	{
		//
		class ScriptMethodAdd: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAdd(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_VOID), miniScript(miniScript) {}
			const string getMethodName() override {
				return "add";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
							result+= stringValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
							miniScript->startErrorScript();
							return;
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result+= vec3Value;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript();
								return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript();
								return;
							}
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					float result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= floatValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript();
							return;
						}
					}
					returnValue.setValue(result);
				} else {
					int64_t result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result+= intValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript();
							return;
						}
					}
					returnValue.setValue(result);
				}
			}
			bool isVariadic() override {
				return true;
			}
			bool isMixedReturnValue() override {
				return true;
			}
			ScriptOperator getOperator() override {
				return OPERATOR_ADDITION;
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
			ScriptMethodSub(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_VOID), miniScript(miniScript) {}
			const string getMethodName() override {
				return "sub";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
							result = vec3Value;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
							miniScript->startErrorScript();
							return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
							result = Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
							miniScript->startErrorScript();
							return;
						}
					}
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result-= vec3Value;
							} else {
								Console::println("ScriptMethodSub::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript();
								return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result-= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodSub::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript();
								return;
							}
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					float result = 0.0f;
					{
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
							result = floatValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
							miniScript->startErrorScript();
							return;
						}
					}
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= floatValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript();
							return;
						}
					}
					returnValue.setValue(result);
				} else {
					int64_t result = 0LL;
					{
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
							result = intValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
							miniScript->startErrorScript();
							return;
						}
					}
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result-= intValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript();
							return;
						}
					}
					returnValue.setValue(result);
				}
			}
			bool isVariadic() override {
				return true;
			}
			bool isMixedReturnValue() override {
				return true;
			}
			ScriptOperator getOperator() override {
				return OPERATOR_SUBTRACTION;
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
			ScriptMethodMul(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_VOID), miniScript(miniScript) {}
			const string getMethodName() override {
				return "mul";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
							result = vec3Value;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
							miniScript->startErrorScript();
							return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
							result = Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
							miniScript->startErrorScript();
							return;
						}
					}
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result*= vec3Value;
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript();
								return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result*= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript();
								return;
							}
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					float result = 0.0f;
					{
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
							result = floatValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
							miniScript->startErrorScript();
							return;
						}
					}
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result*= floatValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript();
							return;
						}
					}
					returnValue.setValue(result);
				} else {
					int64_t result = 0LL;
					{
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
							result = intValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
							miniScript->startErrorScript();
							return;
						}
					}
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result*= intValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript();
							return;
						}
					}
					returnValue.setValue(result);
				}
			}
			bool isVariadic() override {
				return true;
			}
			bool isMixedReturnValue() override {
				return true;
			}
			ScriptOperator getOperator() override {
				return OPERATOR_MULTIPLICATION;
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
			ScriptMethodDiv(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_VOID), miniScript(miniScript) {}
			const string getMethodName() override {
				return "div";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
							result = vec3Value;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
							miniScript->startErrorScript();
							return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
							result = Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
							miniScript->startErrorScript();
							return;
						}
					}
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result/= vec3Value;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript();
								return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result/= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript();
								return;
							}
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					float result = 0.0f;
					{
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
							result = floatValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
							miniScript->startErrorScript();
							return;
						}
					}
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result/= floatValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript();
							return;
						}
					}
					returnValue.setValue(result);
				} else {
					int64_t result = 0LL;
					{
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
							result = intValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
							miniScript->startErrorScript();
							return;
						}
					}
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result/= intValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript();
							return;
						}
					}
					returnValue.setValue(result);
				}
			}
			bool isVariadic() override {
				return true;
			}
			bool isMixedReturnValue() override {
				return true;
			}
			ScriptOperator getOperator() override {
				return OPERATOR_DIVISION;
			}
		};
		registerMethod(new ScriptMethodDiv(this));
	}
	// vector3 methods
	{
		//
		class ScriptMethodVec3: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "x", .optional = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "y", .optional = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "z", .optional = false }
					},
					ScriptVariableType::TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3(this));
	}
	{
		//
		class ScriptMethodVec3ComputeLength: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3ComputeLength(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.computeLength";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.computeLength());
				} else {
					Console::println("ScriptMethodVec3ComputeLength::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3ComputeLength(this));
	}
	{
		//
		class ScriptMethodVec3ComputeLengthSquared: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3ComputeLengthSquared(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.computeLengthSquared";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.computeLengthSquared());
				} else {
					Console::println("ScriptMethodVec3ComputeLengthSquared::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3ComputeLengthSquared(this));
	}
	{
		//
		class ScriptMethodVec3ComputeDotProduct: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3ComputeDotProduct(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "a", .optional = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "b", .optional = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.computeDotProduct";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 a;
				Vector3 b;
				if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
					returnValue.setValue(Vector3::computeDotProduct(a, b));
				} else {
					Console::println("ScriptMethodVec3ComputeDotProduct::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3ComputeDotProduct(this));
	}
	{
		//
		class ScriptMethodVec3ComputeCrossProduct: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3ComputeCrossProduct(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "a", .optional = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "b", .optional = false }
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.computeCrossProduct";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 a;
				Vector3 b;
				if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
					returnValue.setValue(Vector3::computeCrossProduct(a, b));
				} else {
					Console::println("ScriptMethodVec3ComputeCrossProduct::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3ComputeCrossProduct(this));
	}
	{
		//
		class ScriptMethodVec3Normalize: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3Normalize(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.normalize";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.normalize());
				} else {
					Console::println("ScriptMethodVec3Normalize::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3Normalize(this));
	}
	{
		//
		class ScriptMethodVec3ComputeAngle: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3ComputeAngle(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "a", .optional = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "b", .optional = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "n", .optional = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.computeAngle";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 a;
				Vector3 b;
				Vector3 n;
				if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, b, false) == true &&
					MiniScript::getVector3Value(argumentValues, 2, n, false) == true) {
					returnValue.setValue(Vector3::computeAngle(a, b, n));
				} else {
					Console::println("ScriptMethodVec3ComputeAngle::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected @ argument 2: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3ComputeAngle(this));
	}
	{
		//
		class ScriptMethodVec3GetX: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3GetX(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.getX";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getX());
				} else {
					Console::println("ScriptMethodVec3GetX::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3GetX(this));
	}
	{
		//
		class ScriptMethodVec3GetY: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3GetY(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.getY";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getY());
				} else {
					Console::println("ScriptMethodVec3GetY::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3GetY(this));
	}
	{
		//
		class ScriptMethodVec3GetZ: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3GetZ(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.getZ";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getZ());
				} else {
					Console::println("ScriptMethodVec3GetZ::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3GetZ(this));
	}
	// transformations
	{
		//
		class ScriptMethodTransformations: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformations(MiniScript* miniScript):
				ScriptMethod(
					{
					},
					ScriptVariableType::TYPE_TRANSFORMATIONS),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transformations";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transformations transformations;
				Vector3 vec3Value;
				if (argumentValues.size() >= 1) {
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, true) == true) {
						transformations.setTranslation(vec3Value);
					} else {
						Console::println("ScriptMethodTransformations::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: vector3 expected");
						miniScript->startErrorScript();
					}
				}
				if (argumentValues.size() >= 2) {
					if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, true) == true) {
						transformations.setScale(vec3Value);
					} else {
						Console::println("ScriptMethodTransformations::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 1: vector3 expected");
						miniScript->startErrorScript();
					}
				}
				for (auto i = 2; i < argumentValues.size(); i++) {
					if (MiniScript::getVector3Value(argumentValues, i, vec3Value, true) == true) {
						transformations.addRotation(vec3Value, 0.0f);
					} else {
						Console::println("ScriptMethodTransformations::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
						miniScript->startErrorScript();
					}
				}
				transformations.update();
				returnValue.setValue(transformations);
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodTransformations(this));
	}
	{
		//
		class ScriptMethodTransformationsGetTranslation: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformationsGetTranslation(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORMATIONS, .name = "transformations", .optional = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transformations.getTranslation";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transformations transformations;
				if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true) {
					returnValue.setValue(transformations.getTranslation());
				} else {
					Console::println("ScriptMethodTransformationsGetTranslation::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: transformations expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformationsGetTranslation(this));
	}
	{
		//
		class ScriptMethodTransformationsSetTranslation: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformationsSetTranslation(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORMATIONS, .name = "transformations", .optional = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "translation", .optional = false },
					},
					ScriptVariableType::TYPE_TRANSFORMATIONS),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transformations.setTranslation";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transformations transformations;
				Vector3 translation;
				if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, translation, false) == true) {
					transformations.setTranslation(translation);
					transformations.update();
					returnValue.setValue(transformations);
				} else {
					Console::println("ScriptMethodTransformationsSetTranslation::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformationsSetTranslation(this));
	}
	{
		//
		class ScriptMethodTransformationsGetScale: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformationsGetScale(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORMATIONS, .name = "transformations", .optional = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transformations.getScale";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transformations transformations;
				if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true) {
					returnValue.setValue(transformations.getScale());
				} else {
					Console::println("ScriptMethodTransformationsGetScale::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: transformations expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformationsGetScale(this));
	}
	{
		//
		class ScriptMethodTransformationsSetScale: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformationsSetScale(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORMATIONS, .name = "transformations", .optional = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "scale", .optional = false },
					},
					ScriptVariableType::TYPE_TRANSFORMATIONS),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transformations.setScale";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transformations transformations;
				Vector3 scale;
				if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, scale, false) == true) {
					transformations.setScale(scale);
					transformations.update();
					returnValue.setValue(transformations);
				} else {
					Console::println("ScriptMethodTransformationsSetScale::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformationsSetScale(this));
	}
	{
		//
		class ScriptMethodTransformationsGetRotationAxis: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformationsGetRotationAxis(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORMATIONS, .name = "transformations", .optional = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transformations.getRotationAxis";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t idx;
				Transformations transformations;
				if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
					if (idx < transformations.getRotationCount()) {
						returnValue.setValue(transformations.getRotationAxis(idx));
					} else {
						Console::println("ScriptMethodTransformationsGetRotationAxis::executeMethod(): " + getMethodName() + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transformations.getRotationCount()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println("ScriptMethodTransformationsGetRotationAxis::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: integer expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformationsGetRotationAxis(this));
	}
	{
		//
		class ScriptMethodTransformationsGetRotationAngle: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformationsGetRotationAngle(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORMATIONS, .name = "transformations", .optional = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transformations.getRotationAngle";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t idx;
				Transformations transformations;
				if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
					if (idx < transformations.getRotationCount()) {
						returnValue.setValue(transformations.getRotationAngle(idx));
					} else {
						Console::println("ScriptMethodTransformationsGetRotationAngle::executeMethod(): " + getMethodName() + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transformations.getRotationCount()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println("ScriptMethodTransformationsGetRotationAngle::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: integer expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformationsGetRotationAngle(this));
	}
	{
		//
		class ScriptMethodTransformationsSetRotationAngle: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformationsSetRotationAngle(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORMATIONS, .name = "transformations", .optional = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false },
					},
					ScriptVariableType::TYPE_TRANSFORMATIONS),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transformations.setRotationAngle";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t idx;
				Transformations transformations;
				float angle;
				if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, angle, false) == true) {
					if (idx < transformations.getRotationCount()) {
						transformations.setRotationAngle(idx, angle);
						transformations.update();
						returnValue.setValue(transformations);
					} else {
						Console::println("ScriptMethodTransformationsSetRotationAngle::executeMethod(): " + getMethodName() + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transformations.getRotationCount()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println("ScriptMethodTransformationsSetRotationAngle::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: integer expected, @ argument 2: float expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformationsSetRotationAngle(this));
	}
	{
		//
		class ScriptMethodTransformationsMultiply: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformationsMultiply(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORMATIONS, .name = "transformations", .optional = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transformations.multiply";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transformations transformations;
				Vector3 vec3;
				if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, vec3, false) == true) {
					returnValue.setValue(transformations.getTransformationsMatrix() * vec3);
				} else {
					Console::println("ScriptMethodTransformationsSetScale::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformationsMultiply(this));
	}
	{
		//
		class ScriptMethodTransformationsRotate: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformationsRotate(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORMATIONS, .name = "transformations", .optional = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transformations.rotate";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transformations transformations;
				Vector3 vec3;
				if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, vec3, false) == true) {
					returnValue.setValue(transformations.getRotationsQuaternion() * vec3);
				} else {
					Console::println("ScriptMethodTransformationsSetScale::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformationsRotate(this));
	}
	// bool methods
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
				bool boolValue;
				if (MiniScript::getBooleanValue(argumentValues, 0, boolValue, false) == true) {
					returnValue.setValue(boolValue);
				} else {
					Console::println("ScriptMethodBool::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: boolean expected");
					miniScript->startErrorScript();
					return;
				}
			}
		};
		registerMethod(new ScriptMethodBool(this));
	}
	{
		//
		class ScriptMethodNot: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodNot(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "bool", .optional = false }
					},
					ScriptVariableType::TYPE_BOOLEAN), miniScript(miniScript) {}
			const string getMethodName() override {
				return "not";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool booleanValue = false;
				if (MiniScript::getBooleanValue(argumentValues, 0, booleanValue, false) == true) {
					returnValue.setValue(!booleanValue);
				} else {
					Console::println("ScriptMethodNot::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: boolean expected");
					miniScript->startErrorScript();
					return;
				}
			}
			ScriptOperator getOperator() override {
				return OPERATOR_NOT;
			}
		};
		registerMethod(new ScriptMethodNot(this));
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
					bool booleanValue;
					if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
						Console::println("ScriptMethodAnd::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
						miniScript->startErrorScript();
						return;
					} else
					if (booleanValue == false) {
						returnValue.setValue(false);
						return;
					}
				}
				returnValue.setValue(true);
			}
			bool isVariadic() override {
				return true;
			}
			ScriptOperator getOperator() override {
				return OPERATOR_AND;
			}
		};
		registerMethod(new ScriptMethodAnd(this));
	}
	{
		//
		class ScriptMethodOr: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodOr(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN), miniScript(miniScript) {}
			const string getMethodName() override {
				return "or";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				for (auto i = 0; i < argumentValues.size(); i++) {
					bool booleanValue;
					if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
						Console::println("ScriptMethodOr::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
						miniScript->startErrorScript();
						return;
					} else
					if (booleanValue == true) {
						returnValue.setValue(true);
						return;
					}
				}
				returnValue.setValue(false);
			}
			bool isVariadic() override {
				return true;
			}
			ScriptOperator getOperator() override {
				return OPERATOR_OR;
			}
		};
		registerMethod(new ScriptMethodOr(this));
	}
	// string functions
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
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(stringValue);
				} else {
					Console::println("ScriptMethodString::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
					return;
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
				int64_t spaces = 1;
				if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
					Console::println("ScriptMethodSpace::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: integer expected");
					miniScript->startErrorScript();
					return;
				} else {
					string spacesString;
					for (auto i = 0; i < spaces; i++) spacesString+= " ";
					returnValue.setValue(spacesString);
				}
			}
		};
		registerMethod(new ScriptMethodSpace(this));
	}
	{
		//
		class ScriptMethodConcatenate: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodConcatenate(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_STRING), miniScript(miniScript) {}
			const string getMethodName() override {
				return "concatenate";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string result;
				for (auto& argumentValue: argumentValues) {
					result+= argumentValue.getValueString();
				}
				returnValue.setValue(result);
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodConcatenate(this));
	}
	{
		//
		class ScriptMethodToUpperCase: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodToUpperCase(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "toUpperCase";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(StringTools::toUpperCase(stringValue));
				} else {
					Console::println("ScriptMethodToUpperCase::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
					return;
				}
			}
		};
		registerMethod(new ScriptMethodToUpperCase(this));
	}
	{
		//
		class ScriptMethodToLowerCase: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodToLowerCase(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "toLowerCase";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(StringTools::toLowerCase(stringValue));
				} else {
					Console::println("ScriptMethodToLowerCase::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
					return;
				}
			}
		};
		registerMethod(new ScriptMethodToLowerCase(this));
	}
	{
		//
		class ScriptMethodGetVariable: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGetVariable(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false }
					},
					ScriptVariableType::TYPE_VOID
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "getVariable";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + getMethodName() + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript();
					return;
				}
			}
			bool isMixedReturnValue() override {
				return true;
			}

		};
		registerMethod(new ScriptMethodGetVariable(this));
	}
	// set
	{
		//
		class ScriptMethodSetVariable: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSetVariable(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_VOID), miniScript(miniScript) {}
			const string getMethodName() override {
				return "setVariable";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string variable;
				if (argumentValues.size() != 2 ||
					MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
					Console::println("ScriptMethodSetVariable::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
					miniScript->startErrorScript();
					return;
				}
				miniScript->setVariable(variable, argumentValues[1]);
				returnValue = argumentValues[1];
			}
			bool isVariadic() override {
				return true;
			}
			bool isMixedReturnValue() override {
				return true;
			}
			ScriptOperator getOperator() override {
				return OPERATOR_SET;
			}
		};
		registerMethod(new ScriptMethodSetVariable(this));
	}
	// time
	{
		//
		class ScriptMethodGetCurrentMillis: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGetCurrentMillis(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "time.getCurrentMillis";
			}
			void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(Time::getCurrentMillis());
			}
		};
		registerMethod(new ScriptMethodGetCurrentMillis(this));
	}
	// determine operators
	for (auto& methodIt: scriptMethods) {
		auto method = methodIt.second;
		auto methodOperator = method->getOperator();
		if (methodOperator != OPERATOR_NONE) {
			auto methodOperatorString = getOperatorAsString(methodOperator);
			auto scriptOperatorIt = scriptOperators.find(static_cast<uint8_t>(methodOperator));
			if (scriptOperatorIt != scriptOperators.end()) {
				Console::println("MiniScript::registerMethods(): operator '" + methodOperatorString + "' already registered for method '" + method->getMethodName() + "'");
				continue;
			}
			scriptOperators[static_cast<uint8_t>(methodOperator)] = method;
		}
	}
}

void MiniScript::registerVariables() {
}
