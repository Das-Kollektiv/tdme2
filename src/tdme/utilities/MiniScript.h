#pragma once

#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/engine/Transformations.h>
#include <tdme/math/Vector3.h>

using std::map;
using std::stack;
using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::engine::Transformations;
using tdme::math::Vector3;

/**
 * Miniscript
 */
class tdme::utilities::MiniScript {
private:
	static constexpr bool VERBOSE { false };

	struct ScriptStatement {
		int line;
		int statementIdx;
		string statement;
		int gotoStatementIdx;
	};
	struct Script {
		int line;
		vector<string> conditions;
		vector<ScriptStatement> statements;
	};

	enum ScriptVariableType {
		TYPE_VOID,
		TYPE_BOOLEAN,
		TYPE_INTEGER,
		TYPE_STRING,
		TYPE_TRANSFORMATIONS
	};

	struct ScriptVariable {
		ScriptVariableType type { TYPE_VOID };
		string stringValue;
		Transformations transformationsValue;
		bool booleanValue { false };
		int64_t integerValue { -1 };
	};

	struct ScriptState {
		enum ConditionType {
			SCRIPT,
			CONDITIONTYPE_FORTIME
		};
		bool running { false };
		int idx { -1 };
		int statementIdx { -1 };
		int64_t waitStarted { -1LL };
		int64_t waitTime { -1LL };
		string id;
		map<string, ScriptVariable> variables;
		map<int, int64_t> forTimeStarted;
		stack<ConditionType> conditionTypeStack;
		int state { -1 };
	};

	/**
	 * @return string representation of script variable type
	 */
	inline static const string getScriptVariableTypeAsString(ScriptVariableType type) {
		switch(type) {
			case TYPE_VOID: return "Void";
			case TYPE_BOOLEAN: return "Boolean";
			case TYPE_INTEGER: return "Integer";
			case TYPE_STRING: return "String";
			case TYPE_TRANSFORMATIONS: return "Transformations";
		}
		return string();
	}

	/**
	 * @return string representation of script variable type
	 */
	inline static const string getScriptVariableAsString(const ScriptVariable& variable) {
		string result;
		result+= getScriptVariableTypeAsString(variable.type);
		result+= "(";
		result+= getScriptVariableValueString(variable);
		result+= ")";
		return result;
	}

	/**
	 * @return string representation of script variable type
	 */
	inline static const string getScriptVariableValueString(const ScriptVariable& variable) {
		string result;
		switch (variable.type) {
			case TYPE_VOID:
				break;
			case TYPE_BOOLEAN:
				result+= variable.booleanValue == true?"1":"0";
				break;
			case TYPE_INTEGER:
				result+= to_string(variable.integerValue);
				break;
			case TYPE_STRING:
				result+= variable.stringValue;
				break;
			case TYPE_TRANSFORMATIONS:
				result+=
					"translation = Vector3(" +
					to_string(variable.transformationsValue.getTranslation().getX()) + ", " +
					to_string(variable.transformationsValue.getTranslation().getY()) + ", " +
					to_string(variable.transformationsValue.getTranslation().getZ()) + ")";
				for (auto i = 0; i < variable.transformationsValue.getRotationCount(); i++) {
					", rotation = (axis = Vector3(" +
					to_string(variable.transformationsValue.getRotationAxis(i).getX()) + ", " +
					to_string(variable.transformationsValue.getRotationAxis(i).getY()) + ", " +
					to_string(variable.transformationsValue.getRotationAxis(i).getZ()) + "), angle = " +
					to_string(variable.transformationsValue.getRotationAngle(i)) + ")";
				}
		}
		return result;
	}

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

	private:
		vector<ArgumentType> argumentTypes;
		ScriptVariableType returnValueType;
	};

	enum StateMachineState {
		STATE_NONE = -1,
		STATE_NEXT_STATEMENT,
		STATE_WAIT,
		STATE_WAIT_FOR_CONDITION
	};

	vector<Script> scripts;
	ScriptState scriptState;
	unordered_map<string, ScriptMethod*> scriptMethods;
	unordered_map<int, ScriptStateMachineState*> scriptStateMachineStates;

	/**
	 * Execute a single script line
	 */
	void executeScriptLine();

	/**
	 * Parse a script statement
	 * @param statement statement 
	 * @param variable variable
	 * @param method method
	 * @param arguments arguments
	 */
	void parseScriptStatement(const string& statement, string& variable, string& method, vector<string>& arguments);

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

protected:
	/**
	 * Start error script
	 */
	void startErrorScript();

	/**
	 * Register state machine states
	 */
	void registerStateMachineStates();

	/**
	 * Register methods
	 */
	void registerMethods();

	/**
	 * Register variables
	 */
	void registerVariables();

public:
	/**
	 * Public constructor
	 * @param pathName path name
	 * @param fileName file name
	 */
	MiniScript(const string& pathName, const string& fileName);

	/**
	 * Destructor
	 */
	~MiniScript();

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
	 * Load script
	 * @param pathName path name
	 * @param fileName file name
	 */
	void loadScript(const string& pathName, const string& fileName);

	/**
	 * Start script
	 * @param delay delay
	 */
	void startScript(int64_t delay = 0LL);

	/**
	 * Emit
	 * @param condition condition
	 */
	void emit(const string& condition);

	/**
	 * Execute state machine
	 * @return quit requested
	 */
	void executeStateMachine();

	/**
	 * @return is running
	 */
	bool isRunning();

	/**
	 * Get string value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static bool getStringValue(const vector<ScriptVariable>& arguments, int idx, string& value, bool optional = false);

	/**
	 * Get transformations value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static bool getTransformationsValue(const vector<ScriptVariable>& arguments, int idx, Transformations& value, bool optional = false);

	/**
	 * Get boolean value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optionalfalse
	 * @return success
	 */
	static bool getBooleanValue(const vector<ScriptVariable>& arguments, int idx, bool& value, bool optional = false);

	/**
	 * Get integer value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	static bool getIntegerValue(const vector<ScriptVariable>& arguments, int idx, int64_t& value, bool optional = false);

	/**
	 * Set string value from given value into variable
	 * @param argument argument
	 * @param value value
	 */
	static void setStringValue(ScriptVariable& variable, const string& value);

	/**
	 * Set transformations value from given value into variable
	 * @param argument argument
	 * @param value value
	 */
	static void setTransformationsValue(ScriptVariable& variable, const Transformations& value);

	/**
	 * Set boolean value from given value into variable
	 * @param argument argument
	 * @param value value
	 */
	static void setBooleanValue(ScriptVariable& variable, bool value);

	/**
	 * Set integer value from given value into variable
	 * @param argument argument
	 * @param value value
	 */
	static void setIntegerValue(ScriptVariable& variable, int64_t value);

	/**
	 * Dump info
	 */
	const string dumpInfo();

};
