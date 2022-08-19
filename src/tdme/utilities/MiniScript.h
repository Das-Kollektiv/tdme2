#pragma once

#include <algorithm>
#include <array>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::array;
using std::remove;
using std::stack;
using std::string;
using std::string_view;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::engine::Transform;
using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

/**
 * Miniscript
 * @author Andreas Drewke
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
		TYPE_TRANSFORM,
		TYPE_ARRAY
	};

	/**
	 * MiniScript script variable
	 */
	class ScriptVariable {
		friend class MiniScript;

	private:
		ScriptVariableType type { TYPE_VOID };
		void* valuePtr { nullptr };

		/**
		 * @return boolean value reference
		 */
		inline bool& getBooleanValueReference() {
			return *static_cast<bool*>(valuePtr);
		}

		/**
		 * @return const boolean value reference
		 */
		inline const bool& getBooleanValueReference() const {
			return *static_cast<bool*>(valuePtr);
		}

		/**
		 * @return integer value reference
		 */
		inline int64_t& getIntegerValueReference() {
			return *static_cast<int64_t*>(valuePtr);
		}

		/**
		 * @return const integer value reference
		 */
		inline const int64_t& getIntegerValueReference() const {
			return *static_cast<int64_t*>(valuePtr);
		}

		/**
		 * @return float value reference
		 */
		inline float& getFloatValueReference() {
			return *static_cast<float*>(valuePtr);
		}

		/**
		 * @return const float value reference
		 */
		inline const float& getFloatValueReference() const {
			return *static_cast<float*>(valuePtr);
		}

		/**
		 * @return string value reference
		 */
		inline string& getStringValueReference() {
			return *static_cast<string*>(valuePtr);
		}

		/**
		 * @return const string value reference
		 */
		inline const string& getStringValueReference() const {
			return *static_cast<string*>(valuePtr);
		}

		/**
		 * @return vector3 value reference
		 */
		inline Vector3& getVector3ValueReference() {
			return *static_cast<Vector3*>(valuePtr);
		}

		/**
		 * @return const vector3 value reference
		 */
		inline const Vector3& getVector3ValueReference() const {
			return *static_cast<Vector3*>(valuePtr);
		}

		/**
		 * @return transform value reference
		 */
		inline Transform& getTransformValueReference() {
			return *static_cast<Transform*>(valuePtr);
		}

		/**
		 * @return const transform value reference
		 */
		inline const Transform& getTransformValueReference() const {
			return *static_cast<Transform*>(valuePtr);
		}

		/**
		 * @return array value reference
		 */
		inline vector<ScriptVariable>& getArrayValueReference() {
			return *static_cast<vector<ScriptVariable>*>(valuePtr);
		}

		/**
		 * @return const array value reference
		 */
		inline const vector<ScriptVariable>& getArrayValueReference() const {
			return *static_cast<vector<ScriptVariable>*>(valuePtr);
		}

	public:
		/**
		 * Assignment operator
		 * @param scriptVariable script variable to copy
		 * @return this script variable
		 */
		inline ScriptVariable& operator=(const ScriptVariable& scriptVariable) {
			switch(scriptVariable.type) {
				case TYPE_VOID:
					break;
				case TYPE_BOOLEAN:
					setValue(scriptVariable.getBooleanValueReference());
					break;
				case TYPE_INTEGER:
					setValue(scriptVariable.getIntegerValueReference());
					break;
				case TYPE_FLOAT:
					setValue(scriptVariable.getFloatValueReference());
					break;
				case TYPE_STRING:
					setValue(scriptVariable.getStringValueReference());
					break;
				case TYPE_VECTOR3:
					setValue(scriptVariable.getVector3ValueReference());
					break;
				case TYPE_TRANSFORM:
					setValue(scriptVariable.getTransformValueReference());
					break;
				case TYPE_ARRAY:
					setValue(scriptVariable.getArrayValueReference());
					break;
			}
			return *this;
		}

		/**
		 * Copy constructor
		 * @param scriptVariable script variable to copy
		 */
		inline ScriptVariable(const ScriptVariable& scriptVariable) {
			switch(scriptVariable.type) {
				case TYPE_VOID:
					break;
				case TYPE_BOOLEAN:
					setValue(scriptVariable.getBooleanValueReference());
					break;
				case TYPE_INTEGER:
					setValue(scriptVariable.getIntegerValueReference());
					break;
				case TYPE_FLOAT:
					setValue(scriptVariable.getFloatValueReference());
					break;
				case TYPE_STRING:
					setValue(scriptVariable.getStringValueReference());
					break;
				case TYPE_VECTOR3:
					setValue(scriptVariable.getVector3ValueReference());
					break;
				case TYPE_TRANSFORM:
					setValue(scriptVariable.getTransformValueReference());
					break;
				case TYPE_ARRAY:
					setValue(scriptVariable.getArrayValueReference());
					break;
			}
		}

		/**
		 * Constructor
		 */
		inline ScriptVariable() {
		}

		/**
		 * Destructor
		 */
		inline ~ScriptVariable() {
			setType(TYPE_VOID);
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
		inline ScriptVariable(const Transform& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const vector<ScriptVariable>& value) {
			setValue(value);
		}

		/**
		 * @return type
		 */
		inline ScriptVariableType getType() const {
			return type;
		}

		/**
		 * Set type
		 * @param newType new type
		 */
		inline void setType(ScriptVariableType newType) {
			if (type == newType) return;
			switch(type) {
				case TYPE_VOID:
					break;
				case TYPE_BOOLEAN:
					delete static_cast<bool*>(valuePtr);
					break;
				case TYPE_INTEGER:
					delete static_cast<int64_t*>(valuePtr);
					break;
				case TYPE_FLOAT:
					delete static_cast<float*>(valuePtr);
					break;
				case TYPE_STRING:
					delete static_cast<string*>(valuePtr);
					break;
				case TYPE_VECTOR3:
					delete static_cast<Vector3*>(valuePtr);
					break;
				case TYPE_TRANSFORM:
					delete static_cast<Transform*>(valuePtr);
					break;
				case TYPE_ARRAY:
					delete static_cast<vector<ScriptVariable>*>(valuePtr);
					break;
			}
			this->valuePtr = nullptr;
			this->type = newType;
			switch(type) {
				case TYPE_VOID:
					break;
				case TYPE_BOOLEAN:
					valuePtr = new bool();
					break;
				case TYPE_INTEGER:
					valuePtr = new int64_t();
					break;
				case TYPE_FLOAT:
					valuePtr = new float();
					break;
				case TYPE_STRING:
					valuePtr = new string();
					break;
				case TYPE_VECTOR3:
					valuePtr = new Vector3();
					break;
				case TYPE_TRANSFORM:
					valuePtr = new Transform();
					break;
				case TYPE_ARRAY:
					valuePtr = new vector<ScriptVariable>();
					break;
			}
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
					value = getBooleanValueReference();
					return true;
					break;
				case TYPE_INTEGER:
					value = getIntegerValueReference() != 0;
					return true;
				case TYPE_FLOAT:
					value = getFloatValueReference() != 0.0f;
					return true;
				case TYPE_STRING:
					{
						auto& stringValue = getStringValueReference();
						auto lowerCaseString = StringTools::toLowerCase(stringValue);
						if (lowerCaseString != "false" && lowerCaseString != "true" && lowerCaseString != "1" && lowerCaseString != "0") return optional;
						value = lowerCaseString == "true" || lowerCaseString == "1";
						return true;
					}
				case TYPE_VECTOR3:
					return false;
				case TYPE_TRANSFORM:
					return false;
					break;
				case TYPE_ARRAY:
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
					value = getBooleanValueReference() == true?1:0;
					return true;
					break;
				case TYPE_INTEGER:
					value = getIntegerValueReference();
					return true;
				case TYPE_FLOAT:
					Console::println("MiniScript::getIntegerValue(): converting float to integer: precision loss");
					value = getFloatValueReference();
					return true;
				case TYPE_STRING:
					{
						auto& stringValue = getStringValueReference();
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
					}
				case TYPE_VECTOR3:
					return optional;
				case TYPE_TRANSFORM:
					return optional;
				case TYPE_ARRAY:
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
					value = getBooleanValueReference() == true?1.0f:0.0f;
					return true;
					break;
				case TYPE_INTEGER:
					value = getIntegerValueReference();
					return true;
				case TYPE_FLOAT:
					value = getFloatValueReference();
					return true;
				case TYPE_STRING:
					{
						auto& stringValue = getStringValueReference();
						if (Float::is(stringValue) == false) return optional;
						value = Float::parse(stringValue);
					}
					return true;
				case TYPE_VECTOR3:
					return optional;
				case TYPE_TRANSFORM:
					return optional;
				case TYPE_ARRAY:
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
					value = getBooleanValueReference() == true?"true":"false";
					return true;
				case TYPE_INTEGER:
					value = to_string(getIntegerValueReference());
					return true;
				case TYPE_FLOAT:
					value = to_string(getFloatValueReference());
					return true;
				case TYPE_STRING:
					value = getStringValueReference();
					return true;
				case TYPE_VECTOR3:
					return false;
				case TYPE_TRANSFORM:
					return false;
				case TYPE_ARRAY:
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
					value = getVector3ValueReference();
					return true;
				case TYPE_TRANSFORM:
					return optional;
				case TYPE_ARRAY:
					return optional;
			}
			return false;
		}

		/**
		 * Get transform value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getTransformValue(Transform& value, bool optional = false) const {
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
				case TYPE_TRANSFORM:
					value = getTransformValueReference();
					return true;
				case TYPE_ARRAY:
					return optional;
			}
			return false;
		}

		/**
		 * Get array value from given variable
		 * @param value value
		 * @param optional optional
		 * @return success
		 */
		inline bool getArrayValue(vector<ScriptVariable>& value, bool optional = false) const {
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
				case TYPE_TRANSFORM:
					return optional;
				case TYPE_ARRAY:
					value = getArrayValueReference();
					return true;
			}
			return false;
		}

		/**
		 * Set boolean value from given value into variable
		 * @param value value
		 */
		inline void setValue(bool value) {
			setType(TYPE_BOOLEAN);
			getBooleanValueReference() = value;
		}

		/**
		 * Set integer value from given value into variable
		 * @param value value
		 */
		inline void setValue(int64_t value) {
			setType(TYPE_INTEGER);
			getIntegerValueReference() = value;
		}

		/**
		 * Set float value from given value into variable
		 * @param value value
		 */
		inline void setValue(float value) {
			setType(TYPE_FLOAT);
			getFloatValueReference() = value;
		}

		/**
		 * Set string value from given value into variable
		 * @param value value
		 */
		inline void setValue(const string& value) {
			setType(TYPE_STRING);
			getStringValueReference() = value;
		}

		/**
		 * Set vector3 value from given value into variable
		 * @param value value
		 */
		inline void setValue(const Vector3& value) {
			setType(TYPE_VECTOR3);
			getVector3ValueReference() = value;
		}

		/**
		 * Set transform value from given value into variable
		 * @param value value
		 */
		inline void setValue(const Transform& value) {
			setType(TYPE_TRANSFORM);
			getTransformValueReference() = value;
		}

		/**
		 * Set array value from given value into variable
		 * @param value value
		 */
		inline void setValue(const vector<ScriptVariable>& value) {
			// TODO: be verbose about misuse
			setType(TYPE_ARRAY);
			getArrayValueReference() = value;
		}

		/**
		 * Get value from array with given index
		 * @param idx index
		 */
		inline const ScriptVariable getArrayValue(int idx) const {
			// TODO: be verbose about misuse
			if (type != TYPE_ARRAY) return ScriptVariable();
			auto& arrayValue = getArrayValueReference();
			if (idx >= 0 && idx < arrayValue.size()) return arrayValue[idx];
			return ScriptVariable();
		}

		/**
		 * Set value to array with given index
		 * @param idx index
		 */
		inline void setArrayValue(int idx, const ScriptVariable& value) {
			// TODO: be verbose about misuse
			setType(TYPE_ARRAY);
			if (idx < 0) return;
			auto& arrayValue = getArrayValueReference();
			while (arrayValue.size() <= idx) pushArrayValue(ScriptVariable());
			arrayValue[idx] = value;
		}

		/**
		 * Push value to array
		 * @param value value
		 */
		inline void pushArrayValue(const ScriptVariable& value) {
			// TODO: be verbose about misuse
			setType(TYPE_ARRAY);
			getArrayValueReference().push_back(value);
		}

		/**
		 * Get array length
		 */
		inline int64_t getArraySize() const {
			// TODO: be verbose about misuse
			if (getType() != TYPE_ARRAY) return 0;
			return getArrayValueReference().size();
		}

		/**
		 * Set implicit typed value given by value string
		 * @param value value
		 */
		inline void setImplicitTypedValue(const string& value) {
			if (value == "true") {
				setValue(true);
			} else
			if (value == "false") {
				setValue(false);
			} else
			if (Integer::is(value) == true) {
				setValue(static_cast<int64_t>(Integer::parse(value)));
			} else
			if (Float::is(value) == true) {
				setValue(Float::parse(value));
			} else {
				setValue(value);
			}
		}

		/**
		 * Set implicit typed value given by value string
		 * @param value value
		 */
		inline void setImplicitTypedValueFromStringView(const string_view& value) {
			if (value == "true") {
				setValue(true);
			} else
			if (value == "false") {
				setValue(false);
			} else
			if (Integer::viewIs(value) == true) {
				setValue(static_cast<int64_t>(Integer::viewParse(value)));
			} else
			if (Float::viewIs(value) == true) {
				setValue(Float::viewParse(value));
			} else {
				setValue(string(value));
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
				case TYPE_TRANSFORM: return "Transform";
				case TYPE_ARRAY: return "Array";
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
					result+= "<VOID>";
					break;
				case TYPE_BOOLEAN:
					result+= getBooleanValueReference() == true?"1":"0";
					break;
				case TYPE_INTEGER:
					result+= to_string(getIntegerValueReference());
					break;
				case TYPE_FLOAT:
					result+= to_string(getFloatValueReference());
					break;
				case TYPE_STRING:
					result+= getStringValueReference();
					break;
				case TYPE_VECTOR3:
					{
						auto& vector3Value = getVector3ValueReference();
						result+=
							"Vector3(" +
							to_string(vector3Value.getX()) + ", " +
							to_string(vector3Value.getY()) + ", " +
							to_string(vector3Value.getZ()) + ")";
					}
					break;
				case TYPE_TRANSFORM:
					{
						auto& transformValue = getTransformValueReference();
						result+=
							"Transform(translation = Vector3(" +
							to_string(transformValue.getTranslation().getX()) + ", " +
							to_string(transformValue.getTranslation().getY()) + ", " +
							to_string(transformValue.getTranslation().getZ()) + "), " +
							"scale = Vector3(" +
							to_string(transformValue.getScale().getX()) + ", " +
							to_string(transformValue.getScale().getY()) + ", " +
							to_string(transformValue.getScale().getZ()) + ")";
						for (auto i = 0; i < transformValue.getRotationCount(); i++) {
							result+= ", rotations = (axis = Vector3(" +
									to_string(transformValue.getRotationAxis(i).getX()) + ", " +
									to_string(transformValue.getRotationAxis(i).getY()) + ", " +
									to_string(transformValue.getRotationAxis(i).getZ()) + "), angle = " +
									to_string(transformValue.getRotationAngle(i)) + ")";
						}
						result+= ")";
					}
					break;
				case TYPE_ARRAY:
					{
						auto& arrayValue = getArrayValueReference();
						result+="[";
						string valuesString;
						for (auto& value: arrayValue) {
							if (valuesString.empty() == false) valuesString+= ", ";
							valuesString+= value.getValueString();
						}
						result+= valuesString;
						result+="]";
					}
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
	 * Script
	 */
	struct Script {
		enum ConditionType { CONDITIONTYPE_ON, CONDITIONTYPE_ONENABLED };
		ConditionType conditionType;
		int line;
		string condition;
		string name;
		bool emitCondition;
		vector<ScriptStatement> statements;
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

protected:
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
		unordered_map<string, ScriptVariable*> variables;
		unordered_map<int, int64_t> forTimeStarted;
		stack<bool> conditionStack;
		stack<EndType> endTypeStack;
		stack<StateMachineState> stateStack;
		vector<string> enabledNamedConditions;
		int64_t timeEnabledConditionsCheckLast { -1LL };
	};

	//
	string hash;
	bool native;
	vector<Script> scripts;
	vector<Script> nativeScripts;
	ScriptState scriptState;

	/**
	 * Initialize native mini script
	 */
	virtual void initializeNative();

	/**
	 * @return if this script was compiled to C++ and is executed nativly
	 */
	inline bool getNative() {
		return native;
	}

	/**
	 * Set native
	 * @param native native
	 */
	inline void setNative(bool native) {
		this->native = native;
	}

	/**
	 * Set hash
	 * @param hash hash
	 */
	inline void setHash(const string& hash) {
		this->hash = hash;
	}

	/**
	 * Goto statement from given statements goto statement
	 * @param statement statement
	 */
	void gotoStatementGoto(const ScriptStatement& statement) {
		scriptState.statementIdx = statement.gotoStatementIdx;
	}

	/**
	 * @return native script
	 */
	inline vector<Script> getNativeScripts() {
		return nativeScripts;
	}

	/**
	 * Set native scripts
	 * @param native native scripts
	 */
	inline void setNativeScripts(const vector<Script>& nativeScripts) {
		this->nativeScripts = nativeScripts;
	}

	/**
	 * Execute state machine
	 */
	void executeStateMachine();

	/**
	 * Reset script execution state
	 * @param scriptIdx script index
	 * @param stateMachineState state machine state
	 */
	inline void resetScriptExecutationState(int scriptIdx, StateMachineState stateMachineState) {
		scriptState.enabledNamedConditions.clear();
		scriptState.forTimeStarted.clear();
		while (scriptState.conditionStack.empty() == false) scriptState.conditionStack.pop();
		while (scriptState.endTypeStack.empty() == false) scriptState.endTypeStack.pop();
		scriptState.id.clear();
		scriptState.scriptIdx = scriptIdx;
		scriptState.statementIdx = 0;
		scriptState.timeWaitStarted = Time::getCurrentMillis();
		scriptState.timeWaitTime = 0LL;
		setScriptState(stateMachineState);
	}

	/**
	 * Stop script execution
	 */
	inline void stopScriptExecutation() {
		//
		scriptState.running = false;
		for (auto& scriptVariableIt: scriptState.variables) delete scriptVariableIt.second;
		scriptState.variables.clear();
		scriptState.timeEnabledConditionsCheckLast = -1LL;
		resetScriptExecutationState(-1, STATE_NONE);
	}

	/**
	 * Set script state machine state
	 * @param state state
	 */
	inline void setScriptState(int state) {
		auto& stateStackTop = scriptState.stateStack.top();
		stateStackTop.state = state;
		stateStackTop.lastState = -1;
		stateStackTop.lastStateMachineState = nullptr;
	}

	/**
	 * Determine script index to start
	 * @return script index or -1 if no script to start
	 */
	virtual int determineScriptIdxToStart();

	/**
	 * Determine named script index to start
	 * @return script index or -1 if no script to start
	 */
	virtual int determineNamedScriptIdxToStart();

	/**
	 * Returns pointer of variable with given name or nullptr
	 * @param name name
	 * @param callerMethod caller method
	 * @param parentVariable parent variable
	 * @param statement optional statement the variable is read in
	 * @return pointer to variable
	 */
	inline ScriptVariable* getVariableIntern(const string& name, const string& callerMethod, ScriptVariable** parentVariable = nullptr, const ScriptStatement* statement = nullptr) {
		// TODO: this is WIP still
		if (StringTools::startsWith(name, "$") == false) {
			if (statement != nullptr) {
				Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': variable names must start with an $");
			} else {
				Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': variable names must start with an $");
			}
			return nullptr;
		}
		// determine left and right access operator position if there are any
		auto arrayAccessOperatorLeftIdx = string::npos;
		auto arrayAccessOperatorRightIdx = string::npos;
		for (auto i = 0; i < name.length(); i++) {
			auto c = name[i];
			if (c == '[') {
				if (arrayAccessOperatorLeftIdx != string::npos) {
					if (statement != nullptr) {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': unexpected char: '['");
					} else {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': variable: '" + name + "': unexpected char: '['");
					}
					return nullptr;
				}
				arrayAccessOperatorLeftIdx = i;
			} else
			if (c == ']') {
				if (arrayAccessOperatorLeftIdx == string::npos || arrayAccessOperatorRightIdx != string::npos) {
					if (statement != nullptr) {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': unexpected char: ']'");
					} else {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': variable: '" + name + "': unexpected char: ']'");
					}
					return nullptr;
				}
				arrayAccessOperatorRightIdx = i;
			}
		}
		// array access, if we have any, evaluate the array index
		auto haveArrayAccess = arrayAccessOperatorLeftIdx != string::npos && arrayAccessOperatorRightIdx != string::npos;
		auto extractedVariableName = haveArrayAccess == true?StringTools::substring(name, 0, arrayAccessOperatorLeftIdx):string();
		int64_t arrayIdx = -1;
		if (haveArrayAccess == true) {
			auto arrayIdxExpressionString = string(&name.data()[arrayAccessOperatorLeftIdx + 1], arrayAccessOperatorRightIdx - arrayAccessOperatorLeftIdx - 1);
			ScriptVariable statementReturnValue;
			if (evaluate(string(arrayIdxExpressionString), statementReturnValue) == false || statementReturnValue.getIntegerValue(arrayIdx, false) == false) {
				if (statement != nullptr) {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': failed to evaluate expression: '" + arrayIdxExpressionString + "'");
				} else {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': failed to evaluate expression: '" + arrayIdxExpressionString + "'");
				}
				return nullptr;
			}
		}
		// retrieve variable from variable map
		auto scriptVariableIt = scriptState.variables.find(extractedVariableName.empty() == false?extractedVariableName:name);
		if (scriptVariableIt == scriptState.variables.end()) {
			if (statement != nullptr) {
				Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "' does not exist");
			} else {
				Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "' does not exist");
			}
			return nullptr;
		}
		// get pointer to final variable
		auto variablePtr = scriptVariableIt->second;
		if (haveArrayAccess == true) {
			if (variablePtr->getType() == MiniScript::TYPE_ARRAY) {
				if (parentVariable != nullptr) *parentVariable = variablePtr;
				auto& arrayValueReference = variablePtr->getArrayValueReference();
				if (arrayIdx >= 0 && arrayIdx < arrayValueReference.size()) {
					return &arrayValueReference[arrayIdx];
				} else {
					if (statement != nullptr) {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': index out of bounds: 0 <= " + to_string(arrayIdx) + " < " + to_string(arrayValueReference.size()));
					} else {
						Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': index out of bounds: 0 <= " + to_string(arrayIdx) + " <= " + to_string(arrayValueReference.size()));
					}
					return nullptr;
				}
			} else {
				if (statement != nullptr) {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': @" + to_string(statement->line) + ": '" + statement->statement + "': variable: '" + name + "': array access operator, but variable is not of type array or string");
				} else {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': array access operator, but variable is not of type array or string");
				}
				return nullptr;
			}
		} else {
			return variablePtr;
		}
	}

private:
	static constexpr bool VERBOSE { false };

	//
	STATIC_DLL_IMPEXT static string OPERATOR_CHARS;

	//
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
	 * Returns arguments as string placed in a vector of string_views
	 * @param arguments arguments
	 * @return arguments as string
	 */
	inline const string getArgumentsAsString(const vector<string_view>& arguments) {
		string argumentsString;
		for (auto& argument: arguments) argumentsString+= (argumentsString.empty() == false?", ":"") + string("'") + string(argument) + string("'");
		return argumentsString;
	}

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
	bool parseScriptStatement(const string_view& statement, string_view& method, vector<string_view>& arguments);

	/**
	 * Execute a script statement
	 * @param method method 
	 * @param arguments arguments
	 * @param statement statement
	 * @return return value as script variablle
	 */
	ScriptVariable executeScriptStatement(const string_view& method, const vector<string_view>& arguments, const ScriptStatement& statement);

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

	/**
	 * Transpile script statement
	 * @param generatedCode generated code
	 * @param method method
	 * @param arguments arguments
	 * @param statement script statement
	 * @param scriptIdx script index
	 * @param statementIdx statement index
	 * @param methodCodeMap method code map
	 * @param scriptStateChanged script could have state changed
	 * @param scriptStopped script could have been stopped
	 * @param enabledNamedConditions enabled named conditions
	 * @param depth depth
	 * @param argumentIdx argument index
	 * @param parentArgumentIdx parent argument index
	 * @param returnValue return value
	 * @param injectCode code to additionally inject
	 * @param additionalIndent additional indent
	 */
	bool transpileScriptStatement(string& generatedCode, const string_view& method, const vector<string_view>& arguments, const ScriptStatement& statement, int scriptIdx, int& statementIdx, const unordered_map<string, vector<string>>& methodCodeMap, bool& scriptStateChanged, bool& scriptStopped, vector<string>& enabledNamedConditions, int depth = 0, int argumentIdx = -1, int parentArgumentIdx = -1, const string& returnValue = string(), const string& injectCode = string(), int additionalIndent = 0);

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
	 * @return script hash
	 */
	inline const string& getHash() {
		return hash;
	}

	/**
	 * @return scripts
	 */
	const vector<Script>& getScripts() {
		return scripts;
	}

	/**
	 * Push script state
	 */
	inline void pushScriptState() {
		scriptState.stateStack.push(MiniScript::ScriptState::StateMachineState());
	}

	/**
	 * Pop script state
	 */
	inline void popScriptState() {
		scriptState.stateStack.pop();
	}

	/**
	 * @return script state machine state
	 */
	inline int getScriptState() {
		return scriptState.stateStack.top().state;
	}

	/**
	 * Start error script
	 */
	inline void startErrorScript() {
		emit("error");
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
	 * Check if arguments contain argument with given type
	 * @param arguments arguments
	 * @param type type
	 * @return has type
	 */
	template<std::size_t SIZE>
	inline static bool hasType(const array<ScriptVariable, SIZE>& arguments, ScriptVariableType type) {
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
	 * Get boolean value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optionalfalse
	 * @return success
	 */
	template<std::size_t SIZE>
	inline static bool getBooleanValue(const array<ScriptVariable, SIZE>& arguments, int idx, bool& value, bool optional = false) {
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
	 * Get integer value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	template<std::size_t SIZE>
	inline static bool getIntegerValue(const array<ScriptVariable, SIZE>& arguments, int idx, int64_t& value, bool optional = false) {
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
	 * Get float value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	template<std::size_t SIZE>
	inline static bool getFloatValue(const array<ScriptVariable, SIZE>& arguments, int idx, float& value, bool optional = false) {
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
	 * Get string value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	template<std::size_t SIZE>
	inline static bool getStringValue(const array<ScriptVariable, SIZE>& arguments, int idx, string& value, bool optional = false) {
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
	 * Get vector3 value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	template<std::size_t SIZE>
	inline static bool getVector3Value(const array<ScriptVariable, SIZE>& arguments, int idx, Vector3& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getVector3Value(value, optional);
	}

	/**
	 * Get transform value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getTransformValue(const vector<ScriptVariable>& arguments, int idx, Transform& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getTransformValue(value, optional);
	}

	/**
	 * Get transform value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	template<std::size_t SIZE>
	inline static bool getTransformValue(const array<ScriptVariable, SIZE>& arguments, int idx, Transform& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getTransformValue(value, optional);
	}

	/**
	 * Get array value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	inline static bool getArrayValue(const vector<ScriptVariable>& arguments, int idx, vector<ScriptVariable>& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getArrayValue(value, optional);
	}

	/**
	 * Get array value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param value value
	 * @param optional optional
	 * @return success
	 */
	template<std::size_t SIZE>
	inline static bool getArrayValue(const array<ScriptVariable, SIZE>& arguments, int idx, vector<ScriptVariable>& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		auto& argument = arguments[idx];
		return argument.getArrayValue(value, optional);
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
	 * @param statement optional statement the variable is read in
	 * @return variable
	 */
	inline const ScriptVariable getVariable(const string& name, const ScriptStatement* statement = nullptr) {
		auto variablePtr = getVariableIntern(name, __FUNCTION__, nullptr, statement);
		if (variablePtr != nullptr) {
			return *variablePtr;
		} else {
			return ScriptVariable();
		}
	}

	/**
	 * Set script variable
	 * @param name name
	 * @param variable variable
	 * @param statement optional statement the variable is written in
	 */
	inline void setVariable(const string& name, const ScriptVariable& variable, const ScriptStatement* statement = nullptr) {
		ScriptVariable* parentVariable = nullptr;
		auto variablePtr = getVariableIntern(name, __FUNCTION__, &parentVariable, statement);
		if (variablePtr != nullptr) {
			*variablePtr = variable;
			return;
		}
		//
		auto scriptVariableIt = scriptState.variables.find(name);
		if (scriptVariableIt != scriptState.variables.end()) {
			*scriptVariableIt->second = variable;
			return;
		} else {
			auto scriptVariable = new ScriptVariable();
			*scriptVariable = variable;
			scriptState.variables[name] = scriptVariable;
		}
	}

	/**
	 * Unset script variable
	 * @param name name
	 * @param statement optional statement the variable is unset in
	 */
	inline void unsetVariable(const string& name, const ScriptStatement* statement = nullptr) {
		// TODO:
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
	virtual void startScript();

	/**
	 * Emit
	 * @param condition condition
	 */
	virtual void emit(const string& condition);

	/**
	 * Execute
	 */
	virtual void execute();

	/**
	 * @return is running
	 */
	inline bool isRunning() {
		return scriptState.running;
	}

	/**
	 * @return script methods
	 */
	const vector<ScriptMethod*> getMethods();

	/**
	 * @return script operator methods
	 */
	const vector<ScriptMethod*> getOperatorMethods();

	/**
	 * Get miniscript instance information
	 */
	const string getInformation();

	/**
	 * Transpile a script statement
	 * @param generatedCode generated code
	 * @param scriptIdx script index
	 * @param methodCodeMap method code map
	 * @return success
	 */
	bool transpile(string& generatedCode, int scriptIdx, const unordered_map<string, vector<string>>& methodCodeMap);

	/**
	 * Transpile a script condition
	 * @param generatedCode generated code
	 * @param scriptIdx script index
	 * @param methodCodeMap method code map
	 * @param returnValue return value
	 * @param injectCode inject code
	 * @return success
	 */
	bool transpileScriptCondition(string& generatedCode, int scriptIdx, const unordered_map<string, vector<string>>& methodCodeMap, const string& returnValue, const string& injectCode, int depth = 0);

	/**
	 * Evaluate given statement
	 * @param statement
	 * @return return value
	 */
	inline bool evaluate(const string& statement, ScriptVariable& returnValue) {
		auto scriptEvaluateStatement = "script.evaluate(" + statement + ")";
		string_view method;
		vector<string_view> arguments;
		pushScriptState();
		if (parseScriptStatement(scriptEvaluateStatement, method, arguments) == true) {
			returnValue = executeScriptStatement(
				method,
				arguments,
				{
					.line = -1,
					.statementIdx = 0,
					.statement = "Evaluate: " + statement,
					.gotoStatementIdx = -1
				}
			);
			popScriptState();
			return true;
		} else {
			popScriptState();
			return false;
		}
	}

};
