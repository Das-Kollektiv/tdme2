#pragma once

#include <array>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTools.h>

using std::array;
using std::stack;
using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::engine::Transformations;
using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::StringTools;

/**
 * Miniscript
 */
class tdme::utilities::MiniScript {
public:
	enum ScriptOperator {
		OPERATOR_NONE,
		// priority 3
		OPERATOR_NOT,
		// priority 5
		OPERATOR_DIVISION,
		OPERATOR_MULTIPLICATION,
		OPERATOR_REMAINDER, // TODO: not yet
		// priority 6
		OPERATOR_ADDITION,
		OPERATOR_SUBTRACTION,
		// priority 9
		OPERATOR_LESSER,
		OPERATOR_LESSEREQUALS,
		OPERATOR_GREATER,
		OPERATOR_GREATEREQUALS,
		// priority 10
		OPERATOR_EQUALS,
		OPERATOR_NOTEQUAL,
		// priority 14
		OPERATOR_AND,
		// priority 15
		OPERATOR_OR,
		// priority 16
		OPERATOR_SET,
		//
		OPERATOR_MAX
	};

	enum StateMachineState {
		STATE_NONE = -1,
		STATE_NEXT_STATEMENT,
		STATE_WAIT,
		STATE_WAIT_FOR_CONDITION
	};

	struct ScriptStatement {
		int line;
		int statementIdx;
		string statement;
		int gotoStatementIdx;
	};

	enum ScriptVariableType {
		TYPE_VOID,
		TYPE_BOOLEAN,
		TYPE_INTEGER,
		TYPE_FLOAT,
		TYPE_STRING,
		TYPE_VECTOR3,
		TYPE_TRANSFORMATIONS
	};

	class ScriptVariable {
	private:
		ScriptVariableType type { TYPE_VOID };
		string stringValue;
		Transformations transformationsValue;
		bool booleanValue { false };
		int64_t integerValue { 0 };
		float floatValue { 0.0f };
		Vector3 vector3Value;

	public:
		/**
		 * Constructor
		 */
		inline ScriptVariable() {
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(bool value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(int64_t value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(float value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const string& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const Vector3& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const Transformations& value) {
			setValue(value);
		}

		/**
		 * @return type
		 */
		inline ScriptVariableType getType() const {
			return type;
		}

		/**
		 * Get boolean value from given variable
		 * @param value value
		 * @param optional optionalfalse
		 * @return success
		 */
		inline bool getBooleanValue(bool& value, bool optional = false) const {
			switch(type) {
				case TYPE_VOID:
					return optional;
				case TYPE_BOOLEAN:
					value = booleanValue;
					return true;
					break;
				case TYPE_INTEGER:
					value = integerValue != 0;
					return true;
				case TYPE_FLOAT:
					value = floatValue != 0.0f;
					return true;
				case TYPE_STRING:
					{
						auto lowerCaseString = StringTools::toLowerCase(stringValue);
						if (lowerCaseString != "false" && lowerCaseString != "true" && lowerCaseString != "1" && lowerCaseString != "0") return optional;
						value = lowerCaseString == "true" || lowerCaseString == "1";
						return true;
					}
				case TYPE_VECTOR3:
					return false;
				case TYPE_TRANSFORMATIONS:
					return false;
					break;
			}
			return false;
		}

		/**
		 * Get integer value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getIntegerValue(int64_t& value, bool optional = false) const {
			switch(type) {
				case TYPE_VOID:
					return optional;
				case TYPE_BOOLEAN:
					value = booleanValue == true?1:0;
					return true;
					break;
				case TYPE_INTEGER:
					value = integerValue;
					return true;
				case TYPE_FLOAT:
					Console::println("MiniScript::getIntegerValue(): converting float to integer: precision loss");
					value = floatValue;
					return true;
				case TYPE_STRING:
					if (Integer::is(stringValue) == true) {
						value = Integer::parse(stringValue);
						return true;
					} else
					if (Float::is(stringValue) == true) {
						Console::println("MiniScript::getIntegerValue(): converting float to integer: precision loss");
						value = static_cast<int64_t>(Float::parse(stringValue));
						return true;
					} else {
						return optional;
					}
				case TYPE_VECTOR3:
					return optional;
				case TYPE_TRANSFORMATIONS:
					return optional;
			}
			return false;
		}

		/**
		 * Get float value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getFloatValue(float& value, bool optional = false) const {
			switch(type) {
				case TYPE_VOID:
					return optional;
				case TYPE_BOOLEAN:
					value = booleanValue == true?1.0f:0.0f;
					return true;
					break;
				case TYPE_INTEGER:
					value = integerValue;
					return true;
				case TYPE_FLOAT:
					value = floatValue;
					return true;
				case TYPE_STRING:
					if (Float::is(stringValue) == false) return optional;
					value = Float::parse(stringValue);
					return true;
				case TYPE_VECTOR3:
					return optional;
				case TYPE_TRANSFORMATIONS:
					return optional;
			}
			return false;
		}

		/**
		 * Get string value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getStringValue(string& value, bool optional = false) const {
			switch(type) {
				case TYPE_VOID:
					return optional;
				case TYPE_BOOLEAN:
					value = booleanValue == true?"true":"false";
					return true;
				case TYPE_INTEGER:
					value = to_string(integerValue);
					return true;
				case TYPE_FLOAT:
					value = to_string(floatValue);
					return true;
				case TYPE_STRING:
					value = stringValue;
					return true;
				case TYPE_VECTOR3:
					return false;
				case TYPE_TRANSFORMATIONS:
					return false;
			}
			return false;
		}

		/**
		 * Get vector3 value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getVector3Value(Vector3& value, bool optional = false) const {
			switch(type) {
				case TYPE_VOID:
					return optional;
				case TYPE_BOOLEAN:
					return optional;
				case TYPE_INTEGER:
					return optional;
				case TYPE_FLOAT:
					return optional;
				case TYPE_STRING:
					return optional;
				case TYPE_VECTOR3:
					value = vector3Value;
					return true;
				case TYPE_TRANSFORMATIONS:
					return optional;
			}
			return false;
		}

		/**
		 * Get transformations value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getTransformationsValue(Transformations& value, bool optional = false) const {
			switch(type) {
				case TYPE_VOID:
					return optional;
				case TYPE_BOOLEAN:
					return optional;
				case TYPE_INTEGER:
					return optional;
				case TYPE_FLOAT:
					return optional;
				case TYPE_STRING:
					return optional;
				case TYPE_VECTOR3:
					return optional;
				case TYPE_TRANSFORMATIONS:
					value = transformationsValue;
					return true;
			}
			return false;
		}

		/**
		 * Set boolean value from given value into variable
		 * @param value value
		 */
		inline void setValue(bool value) {
			type = TYPE_BOOLEAN;
			booleanValue = value;
		}

		/**
		 * Set integer value from given value into variable
		 * @param value value
		 */
		inline void setValue(int64_t value) {
			type = TYPE_INTEGER;
			integerValue = value;
		}

		/**
		 * Set float value from given value into variable
		 * @param value value
		 */
		inline void setValue(float value) {
			type = TYPE_FLOAT;
			floatValue = value;
		}

		/**
		 * Set string value from given value into variable
		 * @param value value
		 */
		inline void setValue(const string& value) {
			type = TYPE_STRING;
			stringValue = value;
		}

		/**
		 * Set vector3 value from given value into variable
		 * @param value value
		 */
		inline void setValue(const Vector3& value) {
			type = TYPE_VECTOR3;
			vector3Value = value;
		}

		/**
		 * Set transformations value from given value into variable
		 * @param value value
		 */
		inline void setValue(const Transformations& value) {
			type = TYPE_TRANSFORMATIONS;
			transformationsValue = value;
		}

		/**
		 * Set implicit typed value as string
		 * @param value value
		 */
		inline void setImplicitTypedValue(const string& value) {
			if (Integer::is(value) == true) {
				type = TYPE_INTEGER;
				integerValue = Integer::parse(value);
			} else
			if (Float::is(value) == true) {
				type = TYPE_FLOAT;
				floatValue = Float::parse(value);
			} else {
				type = TYPE_STRING;
				stringValue = value;
			}
		}

		/**
		 * @return string representation of script variable type
		 */
		inline static const string getTypeAsString(ScriptVariableType type) {
			switch(type) {
				case TYPE_VOID: return "Void";
				case TYPE_BOOLEAN: return "Boolean";
				case TYPE_INTEGER: return "Integer";
				case TYPE_FLOAT: return "Float";
				case TYPE_STRING: return "String";
				case TYPE_VECTOR3: return "Vector3";
				case TYPE_TRANSFORMATIONS: return "Transformations";
			}
			return string();
		}

		/**
		 * @return string representation of script variable type
		 */
		inline const string getTypeAsString() {
			return getTypeAsString(type);
		}

		/**
		 * @return string representation of script variable type
		 */
		inline const string getAsString() {
			string result;
			result+= getTypeAsString();
			result+= "(";
			result+= getValueString();
			result+= ")";
			return result;
		}

		/**
		 * @return string representation of script variable type
		 */
		inline const string getValueString() const {
			string result;
			switch (type) {
				case TYPE_VOID:
					break;
				case TYPE_BOOLEAN:
					result+= booleanValue == true?"1":"0";
					break;
				case TYPE_INTEGER:
					result+= to_string(integerValue);
					break;
				case TYPE_FLOAT:
					result+= to_string(floatValue);
					break;
				case TYPE_STRING:
					result+= stringValue;
					break;
				case TYPE_VECTOR3:
					result+=
						"Vector3(" +
						to_string(vector3Value.getX()) + ", " +
						to_string(vector3Value.getY()) + ", " +
						to_string(vector3Value.getZ()) + ")";
					break;
				case TYPE_TRANSFORMATIONS:
					result+=
						"Transformations(translation = Vector3(" +
						to_string(transformationsValue.getTranslation().getX()) + ", " +
						to_string(transformationsValue.getTranslation().getY()) + ", " +
						to_string(transformationsValue.getTranslation().getZ()) + "), " +
						"scale = Vector3(" +
						to_string(transformationsValue.getScale().getX()) + ", " +
						to_string(transformationsValue.getScale().getY()) + ", " +
						to_string(transformationsValue.getScale().getZ()) + ")";
					for (auto i = 0; i < transformationsValue.getRotationCount(); i++) {
						result+= ", rotations = (axis = Vector3(" +
								to_string(transformationsValue.getRotationAxis(i).getX()) + ", " +
								to_string(transformationsValue.getRotationAxis(i).getY()) + ", " +
								to_string(transformationsValue.getRotationAxis(i).getZ()) + "), angle = " +
								to_string(transformationsValue.getRotationAngle(i)) + ")";
					}
					result+= ")";
			}
			return result;
		}
	};

	/**
	 * Script State Machine State
	 */
	class ScriptStateMachineState {
	public:
		/**
		 * Constructor
		 */
		ScriptStateMachineState() {}

		/**
		 * Destructor
		 */
		virtual ~ScriptStateMachineState() {}

		/**
		 * @return name
		 */
		virtual const string getName() = 0;

		/**
		 * @return id
		 */
		virtual int getId() = 0;

		/**
		 * Execute script state machine state
		 */
		virtual void execute() = 0;
	};

	/**
	 * Script method
	 */
	class ScriptMethod {
	public:
		struct ArgumentType {
			ScriptVariableType type;
			string name;
			bool optional;
		};

		/**
		 * Constructor
		 * @param argumentTypes argument types
		 * @param returnValueType return value type
		 */
		ScriptMethod(const vector<ArgumentType>& argumentTypes = {}, ScriptVariableType returnValueType = ScriptVariableType::TYPE_VOID): returnValueType(returnValueType), argumentTypes(argumentTypes) {}

		/**
		 * Destructor
		 */
		virtual ~ScriptMethod() {}

		/**
		 * @return script method name
		 */
		virtual const string getMethodName() = 0;

		/**
		 * Execute script method
		 * @param argumentValues argument values
		 * @param returnValue return value
		 * @param statement statement
		 */
		virtual void executeMethod(const vector<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) = 0;

		/**
		 * @return arguments
		 */
		const vector<ArgumentType>& getArgumentTypes() {
			return argumentTypes;
		}

		/**
		 * @return return value type
		 */
		const ScriptVariableType& getReturnValueType() {
			return returnValueType;
		}

		/**
		 * @return if variadic method
		 */
		virtual bool isVariadic() {
			return false;
		}

		/**
		 * @return if mixed return value
		 */
		virtual bool isMixedReturnValue() {
			return false;
		}

		/**
		 * @return operator
		 */
		virtual ScriptOperator getOperator() {
			return OPERATOR_NONE;
		}

		/**
		 * @return description
		 */
		virtual string getDescription() {
			return "No description.";
		}

	private:
		vector<ArgumentType> argumentTypes;
		ScriptVariableType returnValueType;
	};

private:
	static constexpr bool VERBOSE { false };

	struct ScriptState {
		enum EndType { ENDTYPE_FOR, ENDTYPE_IF };
		enum ConditionType {
			SCRIPT,
			CONDITIONTYPE_FORTIME
		};
		struct StateMachineState {
			int state { -1 };
			int lastState { -1 };
			ScriptStateMachineState* lastStateMachineState { nullptr };
		};
		bool running { false };
		int scriptIdx { -1 };
		int statementIdx { -1 };
		int64_t timeWaitStarted { -1LL };
		int64_t timeWaitTime { -1LL };
		string id;
		unordered_map<string, ScriptVariable> variables;
		unordered_map<int, int64_t> forTimeStarted;
		stack<bool> conditionStack;
		stack<EndType> endTypeStack;
		StateMachineState state;
		vector<string> enabledConditionNames;
		int64_t timeEnabledConditionsCheckLast { -1LL };
	};

	struct Script {
		enum ConditionType { CONDITIONTYPE_ON, CONDITIONTYPE_ONENABLED };
		ConditionType conditionType;
		int line;
		vector<string> conditions;
		string name;
		vector<ScriptStatement> statements;
	};

	//
	STATIC_DLL_IMPEXT static string OPERATOR_CHARS;

	//
	ScriptState scriptState;
	vector<Script> scripts;
	unordered_map<string, ScriptMethod*> scriptMethods;
	unordered_map<int, ScriptStateMachineState*> scriptStateMachineStates;
	unordered_map<uint8_t, ScriptMethod*> scriptOperators;
	string scriptPathName;
	string scriptFileName;
	bool scriptValid { false };

	//
	struct ScriptStatementOperator {
		int idx { -1 };
		ScriptOperator scriptOperator;
	};

	/**
	 * Execute a single script line
	 */
	void executeScriptLine();

	/**
	 * Parse a script statement
	 * @param statement statement 
	 * @param method method
	 * @param arguments arguments
	 * @return success
	 */
	bool parseScriptStatement(const string& statement, string& method, vector<string>& arguments);

	/**
	 * Execute a script statement
	 * @param method method 
	 * @param argument argument
	 * @param statement statement
	 * @return pointer to return value
	 */
	ScriptVariable executeScriptStatement(const string& method, const vector<string>& argument, const ScriptStatement& statement);

	/**
	 * Determine script index to start
	 * @return script index or -1 if no script to start
	 */
	int determineScriptIdxToStart();

	/**
	 * Determine named script index to start
	 * @return script index or -1 if no script to start
	 */
	int determineNamedScriptIdxToStart();

	/**
	 * Returns if char is operator char
	 * @param c char to test
	 * @return if char is operator char
	 */
	static inline const bool isOperatorChar(char c) {
		return OPERATOR_CHARS.find(c) != string::npos;
	}

	/**
	 * Determine next not substituted operator in statement
	 * @param statement statement
	 * @param nextOperator next operator
	 */
	bool getNextStatementOperator(const string& statement, ScriptStatementOperator& nextOperator);

	/**
	 * Trim argument and remove unnessessary parenthesis
	 * @param argument argument
	 * @return processed argument
	 */
	const string trimArgument(const string& argument);

	/**
	 * Find right argument in statement beginning from position
	 * @param statement statement
	 * @param position position
	 * @param length argument length
	 */
	const string findRightArgument(const string statement, int position, int& length);

	/**
	 * Find left argument in statement beginning from position
	 * @param statement statement
	 * @param position position
	 * @param length argument length
	 */
	const string findLeftArgument(const string statement, int position, int& length);

	/**
	 * Do statement pre processing, 1) replace operators with corresponding methods
	 * @param statement statement
	 */
	const string doStatementPreProcessing(const string& statement);

public:
	/**
	 * Default constructor
	 */
	MiniScript();

	/**
	 * Destructor
	 */
	virtual ~MiniScript();

	/**
	 * Start error script
	 */
	inline void startErrorScript() {
		emit("error");
	}

	/**
	 * Set script state machine state
	 * @param state state
	 */
	inline void setScriptState(int state) {
		if (scriptState.state.state == state) return;
		scriptState.state.state = state;
		scriptState.state.lastState = -1;
		scriptState.state.lastStateMachineState = nullptr;
	}

	/**
	 * Register state machine states
	 */
	virtual void registerStateMachineStates();

	/**
	 * Register methods
	 */
	virtual void registerMethods();

	/**
	 * Register variables
	 */
	virtual void registerVariables();

	/**
	 * Get operator as string
	 * @param scriptOperator script operator
	 * @return script operator as string
	 */
	inline static string getOperatorAsString(ScriptOperator scriptOperator) {
		switch(scriptOperator) {
			case(OPERATOR_NONE): return "NONE";
			case(OPERATOR_NOT): return "!";
			case(OPERATOR_MULTIPLICATION): return "*";
			case(OPERATOR_DIVISION): return "/";
			case(OPERATOR_REMAINDER): return "%";
			case(OPERATOR_ADDITION): return "+";
			case(OPERATOR_SUBTRACTION): return "-";
			case(OPERATOR_LESSER): return "<";
			case(OPERATOR_LESSEREQUALS): return "<=";
			case(OPERATOR_GREATER): return ">";
			case(OPERATOR_GREATEREQUALS): return ">=";
			case(OPERATOR_EQUALS): return "==";
			case(OPERATOR_NOTEQUAL): return "!=";
			case(OPERATOR_AND): return "&&";
			case(OPERATOR_OR): return "||";
			case(OPERATOR_SET): return "=";
			case(OPERATOR_MAX): return "MAX";
			default: return "INVALID";
		}
	}

	/**
	 * Check if arguments contain argument with given type
	 * @param arguments arguments
	 * @param type type
	 * @return has type
	 */
	inline static bool hasType(const vector<ScriptVariable>& arguments, ScriptVariableType type) {
		for (auto& argument: arguments) if (argument.getType() == type) return true;
		return false;
	}

	/**
	 * Get boolean value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optionalfalse
	 * @return success
	 */
	inline static bool getBooleanValue(const vector<ScriptVariable>& arguments, int idx, bool& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getBooleanValue(value, optional);
	}

	/**
	 * Get integer value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getIntegerValue(const vector<ScriptVariable>& arguments, int idx, int64_t& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getIntegerValue(value, optional);
	}

	/**
	 * Get float value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getFloatValue(const vector<ScriptVariable>& arguments, int idx, float& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getFloatValue(value, optional);
	}

	/**
	 * Get string value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getStringValue(const vector<ScriptVariable>& arguments, int idx, string& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getStringValue(value, optional);
	}

	/**
	 * Get vector3 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getVector3Value(const vector<ScriptVariable>& arguments, int idx, Vector3& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getVector3Value(value, optional);
	}
	/**
	 * Get transformations value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getTransformationsValue(const vector<ScriptVariable>& arguments, int idx, Transformations& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getTransformationsValue(value, optional);
	}

	/**
	 * Register script state machine state
	 * @param state state
	 */
	void registerStateMachineState(ScriptStateMachineState* state);

	/**
	 * Register script method
	 * @param method method
	 */
	void registerMethod(ScriptMethod* method);

	/**
	 * Returns variable with given name
	 * @param name name
	 * @return variable
	 */
	inline const ScriptVariable getVariable(const string& name) {
		auto scriptVariableIt = scriptState.variables.find(name);
		if (scriptVariableIt == scriptState.variables.end()) {
			Console::println("MiniScript::getVariable(): '" + scriptFileName + "': variable with name '" + name + "' does not exist.");
			return ScriptVariable();
		}
		return scriptVariableIt->second;
	}

	/**
	 * Set script variable
	 * @param name name
	 * @param variable variable
	 */
	inline void setVariable(const string& name, const ScriptVariable& variable) {
		scriptState.variables[name] = variable;
	}

	/**
	 * Unset script variable
	 * @param name name
	 */
	inline void unsetVariable(const string& name) {
		scriptState.variables.erase(name);
	}

	/**
	 * Load script
	 * @param pathName path name
	 * @param fileName file name
	 */
	void loadScript(const string& pathName, const string& fileName);

	/**
	 * Start script
	 */
	void startScript();

	/**
	 * Emit
	 * @param condition condition
	 */
	void emit(const string& condition);

	/**
	 * Execute
	 */
	void execute();

	/**
	 * @return is running
	 */
	inline bool isRunning() {
		return scriptState.running;
	}

	/**
	 * @return script state machine state
	 */
	inline int getScriptState() {
		return scriptState.state.state;
	}

	/**
	 * Get miniscript instance information
	 */
	const string getInformation();

};
