#pragma once

#include <algorithm>
#include <array>
#include <memory>
#include <span>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>
#include <miniscript/utilities/Character.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>
#include <miniscript/utilities/Float.h>
#include <miniscript/utilities/Integer.h>
#include <miniscript/utilities/StringTools.h>
#include <miniscript/utilities/Time.h>

using std::array;
using std::exchange;
using std::make_unique;
using std::move;
using std::remove;
using std::sort;
using std::span;
using std::stack;
using std::string;
using std::string_view;
using std::swap;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using _Character = miniscript::utilities::Character;
using _Console = miniscript::utilities::Console;
using _Exception = miniscript::utilities::Exception;
using _Float = miniscript::utilities::Float;
using _Integer = miniscript::utilities::Integer;
using _StringTools = miniscript::utilities::StringTools;
using _Time = miniscript::utilities::Time;

namespace miniscript {
namespace tools {
	class TranspilerTool;
}
}

/**
 * Miniscript
 * @author Andreas Drewke
 */
class miniscript::miniscript::MiniScript {
	friend class ::miniscript::tools::TranspilerTool;
	friend class BaseMethods;
	friend class JSONMethods;
	friend class ScriptMethods;
	friend class Transpiler;

public:
	enum ScriptOperator {
		// see: https://en.cppreference.com/w/cpp/language/operator_precedence
		OPERATOR_NONE,
		// priority 2
		OPERATOR_INCREMENT,
		OPERATOR_DECREMENT,
		// priority 3
		OPERATOR_NOT,
		OPERATOR_BITWISENOT,
		// priority 5
		OPERATOR_DIVISION,
		OPERATOR_MULTIPLICATION,
		OPERATOR_MODULO,
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
		// priority 11
		OPERATOR_BITWISEAND,
		// priority 12
		OPERATOR_BITWISEXOR,
		// priority 12
		OPERATOR_BITWISEOR,
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
		STATEMACHINESTATE_NONE = -1,
		STATEMACHINESTATE_NEXT_STATEMENT,
		STATEMACHINESTATE_WAIT,
		STATEMACHINESTATE_WAIT_FOR_CONDITION
	};

	struct ScriptStatement {
		ScriptStatement(
			int line,
			int statementIdx,
			const string& statement,
			const string& executableStatement,
			int gotoStatementIdx
		):
			line(line),
			statementIdx(statementIdx),
			statement(statement),
			executableStatement(executableStatement),
			gotoStatementIdx(gotoStatementIdx)
		{}
		int line;
		int statementIdx;
		string statement;
		string executableStatement;
		int gotoStatementIdx;
	};

	enum ScriptVariableType {
		// primitives
		TYPE_NULL,
		TYPE_BOOLEAN,
		TYPE_INTEGER,
		TYPE_FLOAT,
		// special
		TYPE_FUNCTION_CALL,
		TYPE_FUNCTION_ASSIGNMENT,
		// pseudo
		TYPE_PSEUDO_NUMBER,
		TYPE_PSEUDO_MIXED,
		// classes
		TYPE_STRING,
		TYPE_ARRAY,
		TYPE_MAP,
		TYPE_SET,
		TYPE_PSEUDO_CUSTOM_DATATYPES,
	};

	//
	class ScriptSyntaxTreeNode;
	class ScriptVariable;

	/**
	 * Script data type
	 */
	class ScriptDataType {
		friend class MiniScript;
		friend class MathMethods;

	protected:
		bool mathDataType { false };
		int type { TYPE_NULL };

		/**
		 * Set type
		 * @param type type
		 */
		inline void setType(int type) {
			this->type = type;
		}

		/**
		 * @return is math data type
		 */
		inline bool isMathDataType() {
			return mathDataType;
		}

		/**
		 * Register methods
		 * @param miniScript mini script instance
		 */
		virtual void registerMethods(MiniScript* miniScript) const = 0;

		/**
		 * Unset script variable value
		 * @param variable variable
		 */
		virtual void unsetScriptVariableValue(ScriptVariable& variable) const = 0;

		/**
		 * Set script variable value
		 * @param variable variable
		 * @param value value
		 */
		virtual void setScriptVariableValue(ScriptVariable& variable, const void* value) const = 0;

		/**
		 * Copy script variable
		 * @param to to
		 * @param from from
		 */
		virtual void copyScriptVariable(ScriptVariable& to, const ScriptVariable& from) const = 0;

		/**
		 * Multiply
		 * @param miniScript mini script instance
		 * @param argumentValues argument values
		 * @param returnValue return value
		 * @param statement statement
		 * @return mul was executed
		 */
		virtual bool mul(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const = 0;

		/**
		 * Division
		 * @param miniScript mini script instance
		 * @param argumentValues argument values
		 * @param returnValue return value
		 * @param statement statement
		 * @return div was executed
		 */
		virtual bool div(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const = 0;

		/**
		 * Addition
		 * @param miniScript mini script instance
		 * @param argumentValues argument values
		 * @param returnValue return value
		 * @param statement statement
		 * @return add was executed
		 */
		virtual bool add(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const = 0;

		/**
		 * Subtraction
		 * @param miniScript mini script instance
		 * @param argumentValues argument values
		 * @param returnValue return value
		 * @param statement statement
		 * @return sub was executed
		 */
		virtual bool sub(MiniScript* miniScript, const span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) const = 0;

	public:
		// forbid class copy
		FORBID_CLASS_COPY(ScriptDataType)

		/**
		 * Script data type
		 * @param mathDataType is math data type and provides math methods
		 */
		ScriptDataType(bool mathDataType): mathDataType(mathDataType) {
			//
		}

		virtual ~ScriptDataType() {
			//
		}

		/**
		 * @return type
		 */
		inline int getType() const {
			return type;
		}

		/**
		 * @return class name
		 */
		virtual const string& getClassName() const = 0;

		/**
		 * @return type as string
		 */
		virtual const string& getTypeAsString() const = 0;

		/**
		 * Returns value as string
		 * @param variable variable
		 * @return value as string
		 */
		virtual const string getValueAsString(const ScriptVariable& variable) const = 0;

	};

	/**
	 * MiniScript script variable
	 */
	class ScriptVariable {
		friend class MiniScript;

	private:
		/**
		 * MiniScript variable initializer
		 */
		class Initializer {
			public:
				/**
				 * Constructor
				 */
				Initializer():
					statement(
						MiniScript::ScriptStatement(
							MiniScript::LINE_NONE,
							MiniScript::STATEMENTIDX_NONE,
							string(),
							string(),
							MiniScript::STATEMENTIDX_NONE
						)
					),
					syntaxTree(new ScriptSyntaxTreeNode()) {
					//
				}

				/**
				 * Constructor
				 * @param initializerString initializer string
				 * @param statement statement
				 * @param syntaxTree syntax tree
				 */
				Initializer(const string& initializerString, const ScriptStatement& statement, ScriptSyntaxTreeNode* syntaxTree): initializerString(initializerString), statement(statement), syntaxTree(syntaxTree) {}

				/**
				 * Destructor
				 */
				~Initializer() { delete syntaxTree; }

				/**
				 * Copy from initializer
				 * @param initializer initializer
				 */
				void copy(Initializer* initializer) {
					this->initializerString = initializer->initializerString;
					this->statement = initializer->statement;
					if (syntaxTree != nullptr && initializer->syntaxTree != nullptr) {
						*syntaxTree = *initializer->syntaxTree;
					}
				}

				/**
				 * @return initializer string
				 */
				const string& getInitializerString() const {
					return initializerString;
				}

				/**
				 * @return statement
				 */
				const ScriptStatement& getStatement() const {
					return statement;
				}

				/**
				 * @return syntax tree node
				 */
				const ScriptSyntaxTreeNode* getSyntaxTree() const {
					return syntaxTree;
				}

			private:
				string initializerString;
				ScriptStatement statement;
				ScriptSyntaxTreeNode* syntaxTree;
		};

		//
		ScriptVariableType type { TYPE_NULL };	// 4, maybe use a int16_t here
		uint64_t valuePtr { 0LL };				// 8
		// TODO: union initializer/reference
		Initializer* initializer { nullptr };	// 8
		ScriptVariable* reference { nullptr };	// 8
		int referenceCounter { 1 };				// 4, maybe use a int16_t here

		/**
		 * Acquire reference
		 */
		inline void acquireReference() {
			referenceCounter++;
		}

		/**
		 * Release reference
		 */
		inline void releaseReference() {
			if (reference != nullptr) {
				reference->releaseReference();
			}
			if (--referenceCounter == 0) {
				reference = nullptr;
				setType(TYPE_NULL);
				delete this;
			}
		}

		/**
		 * Return initializer
		 * @return initializer
		 */
		inline Initializer*& getInitializerReference() {
			return reference != nullptr?reference->initializer:initializer;
		}

		/**
		 * Return const value pointer
		 * @return value ptr
		 */
		inline const uint64_t& getValuePtrReference() const {
			return reference != nullptr?reference->valuePtr:valuePtr;
		}

		/**
		 * Return value pointer
		 * @return value ptr
		 */
		inline uint64_t& getValuePtrReference() {
			return reference != nullptr?reference->valuePtr:valuePtr;
		}

		/**
		 * @return boolean value reference
		 */
		inline bool& getBooleanValueReference() {
			return *(bool*)(&getValuePtrReference());
		}

		/**
		 * @return const boolean value reference
		 */
		inline const bool& getBooleanValueReference() const {
			return *(bool*)(&getValuePtrReference());
		}

		/**
		 * @return integer value reference
		 */
		inline int64_t& getIntegerValueReference() {
			return *(int64_t*)(&getValuePtrReference());
		}

		/**
		 * @return const integer value reference
		 */
		inline const int64_t& getIntegerValueReference() const {
			return *(int64_t*)(&getValuePtrReference());
		}

		/**
		 * @return float value reference
		 */
		inline float& getFloatValueReference() {
			return *(float*)(&getValuePtrReference());
		}

		/**
		 * @return const float value reference
		 */
		inline const float& getFloatValueReference() const {
			return *(float*)(&getValuePtrReference());
		}

		/**
		 * @return string value reference
		 */
		inline string& getStringValueReference() {
			return *static_cast<string*>((void*)getValuePtrReference());
		}

		/**
		 * @return const string value reference
		 */
		inline const string& getStringValueReference() const {
			return *static_cast<string*>((void*)getValuePtrReference());
		}

		/**
		 * @return array value reference
		 */
		inline vector<ScriptVariable*>& getArrayValueReference() {
			return *static_cast<vector<ScriptVariable*>*>((void*)getValuePtrReference());
		}

		/**
		 * @return const array value reference
		 */
		inline const vector<ScriptVariable*>& getArrayValueReference() const {
			return *static_cast<vector<ScriptVariable*>*>((void*)getValuePtrReference());
		}

		/**
		 * @return map value reference
		 */
		inline unordered_map<string, ScriptVariable*>& getMapValueReference() {
			return *static_cast<unordered_map<string, ScriptVariable*>*>((void*)getValuePtrReference());
		}

		/**
		 * @return const map value reference
		 */
		inline const unordered_map<string, ScriptVariable*>& getMapValueReference() const {
			return *static_cast<unordered_map<string, ScriptVariable*>*>((void*)getValuePtrReference());
		}

		/**
		 * @return set value reference
		 */
		inline unordered_set<string>& getSetValueReference() {
			return *static_cast<unordered_set<string>*>((void*)getValuePtrReference());
		}

		/**
		 * @return const set value reference
		 */
		inline const unordered_set<string>& getSetValueReference() const {
			return *static_cast<unordered_set<string>*>((void*)getValuePtrReference());
		}

	public:
		// class names
		STATIC_DLL_IMPEXT static const string CLASSNAME_NONE;
		STATIC_DLL_IMPEXT static const string CLASSNAME_STRING;
		STATIC_DLL_IMPEXT static const string CLASSNAME_ARRAY;
		STATIC_DLL_IMPEXT static const string CLASSNAME_MAP;
		STATIC_DLL_IMPEXT static const string CLASSNAME_SET;

		/**
		 * Create reference variable
		 * @param variable variable
		 * @returns reference variable
		 */
		inline static ScriptVariable createReferenceVariable(const ScriptVariable* variable) {
			// copy a reference variable is cheap
			if (variable->reference != nullptr) return *variable;
			//
			ScriptVariable referenceVariable;
			referenceVariable.reference = (ScriptVariable*)variable; // TODO: improve me!
			referenceVariable.reference->acquireReference();
			return referenceVariable;
		}

		/**
		 * Create reference variable pointer
		 * @param variable variable
		 * @returns reference variable
		 */
		inline static ScriptVariable* createReferenceVariablePointer(const ScriptVariable* variable) {
			// copy a reference variable is cheap
			if (variable->reference != nullptr) return new ScriptVariable(*variable);
			//
			ScriptVariable* referenceVariable = new ScriptVariable();
			referenceVariable->reference = (ScriptVariable*)variable; // TODO: improve me!
			referenceVariable->reference->acquireReference();
			return referenceVariable;
		}

		/**
		 * Copy script variable
		 * @param from from
		 * @param to to
		 */
		inline static void copyScriptVariable(ScriptVariable& to, const ScriptVariable& from) {
			// initial setup
			to.setNullValue();
			// do the copy
			switch(from.getType()) {
				case TYPE_NULL:
					// no op
					break;
				case TYPE_BOOLEAN:
					to.setValue(from.getBooleanValueReference());
					break;
				case TYPE_INTEGER:
					to.setValue(from.getIntegerValueReference());
					break;
				case TYPE_FLOAT:
					to.setValue(from.getFloatValueReference());
					break;
				case TYPE_FUNCTION_CALL:
					to.setType(TYPE_FUNCTION_CALL);
					to.getStringValueReference() = from.getStringValueReference();
					// copy initializer if we have any
					to.getInitializer()->copy(from.initializer);
					//
					break;
				case TYPE_FUNCTION_ASSIGNMENT:
					to.setFunctionAssignment(from.getStringValueReference());
					break;
				case TYPE_PSEUDO_NUMBER: break;
				case TYPE_PSEUDO_MIXED: break;
				case TYPE_STRING:
					to.setValue(from.getStringValueReference());
					break;
				case TYPE_ARRAY:
					to.setValue(from.getArrayValueReference());
					// copy initializer if we have any
					to.getInitializer()->copy(from.initializer);
					//
					break;
				case TYPE_MAP:
					to.setValue(from.getMapValueReference());
					// copy initializer if we have any
					to.getInitializer()->copy(from.initializer);
					//
					break;
				case TYPE_SET:
					to.setValue(from.getSetValueReference());
					// copy initializer if we have any
					to.getInitializer()->copy(from.initializer);
					//
					break;
				default:
					// custom data type
					auto dataTypeIdx = static_cast<int>(from.getType()) - TYPE_PSEUDO_CUSTOM_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::scriptDataTypes.size()) {
						_Console::println("ScriptVariable::copyScriptVariable(): unknown custom data type with id " + to_string(dataTypeIdx));
						return;
					}
					MiniScript::scriptDataTypes[dataTypeIdx]->copyScriptVariable(to, from);
			}

		}

		/**
		 * Create none reference variable
		 * @param variable variable
		 * @returns reference variable
		 */
		inline static ScriptVariable createNonReferenceVariable(const ScriptVariable* variable) {
			// copy a non reference variable is cheap
			if (variable->reference == nullptr) return *variable;
			// otherwise do the copy
			ScriptVariable nonReferenceVariable;
			//
			copyScriptVariable(nonReferenceVariable, *variable);
			//
			return nonReferenceVariable;
		}

		/**
		 * Create none reference variable pointer
		 * @param variable variable
		 * @returns reference variable
		 */
		inline static ScriptVariable* createNonReferenceVariablePointer(const ScriptVariable* variable) {
			// copy a non reference variable is cheap
			if (variable->reference == nullptr) return new ScriptVariable(*variable);
			// otherwise do the copy
			ScriptVariable* nonReferenceVariable = new ScriptVariable();
			//
			copyScriptVariable(*nonReferenceVariable, *variable);
			//
			return nonReferenceVariable;
		}

		/**
		 * Copy constructor
		 * @param variable variable to copy
		 */
		inline ScriptVariable(const ScriptVariable& variable) {
			if (variable.reference != nullptr) {
				reference = variable.reference;
				variable.reference->acquireReference();
			} else {
				copyScriptVariable(*this, variable);
			}
		}

		/**
		 * Move constructor
		 * @param variable variable to move from
		 */
		inline ScriptVariable(ScriptVariable&& variable):
			type(exchange(variable.type, MiniScript::TYPE_NULL)),
			valuePtr(exchange(variable.valuePtr, 0ll)),
			initializer(exchange(variable.initializer, nullptr)),
			reference(exchange(variable.reference, nullptr)),
			referenceCounter(exchange(variable.referenceCounter, 1)) {
			//
		}

		/**
		 * Assignment operator
		 * @param variable variable to copy
		 * @return this variable
		 */
		inline ScriptVariable& operator=(const ScriptVariable& variable) {
			if (variable.reference != nullptr) {
				reference = variable.reference;
				variable.reference->acquireReference();
			} else {
				copyScriptVariable(*this, variable);
			}
			//
			return *this;
		}

		/**
		 * Move operator
		 * @param variable variable to move from
		 * @return this script variable
		 */
		inline ScriptVariable& operator=(ScriptVariable&& variable) {
			swap(type, variable.type);
			swap(valuePtr, variable.valuePtr);
			swap(initializer, variable.initializer);
			swap(reference, variable.reference);
			swap(referenceCounter, variable.referenceCounter);
			//
			return *this;
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
			if (reference != nullptr) {
				reference->releaseReference();
			}
			if (--referenceCounter == 0) {
				reference = nullptr;
				setType(TYPE_NULL);
			}
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
		inline ScriptVariable(const vector<ScriptVariable*>& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline ScriptVariable(const unordered_map<string, ScriptVariable*>& value) {
			setValue(value);
		}

		/**
		 * @return type
		 */
		inline ScriptVariableType getType() const {
			return reference != nullptr?reference->type:type;
		}

		/**
		 * Set type
		 * @param newType new type
		 */
		inline void setType(ScriptVariableType newType) {
			if (getType() == newType) return;
			switch(getType()) {
				case TYPE_NULL:
					break;
				case TYPE_BOOLEAN:
					break;
				case TYPE_INTEGER:
					break;
				case TYPE_FLOAT:
					break;
				case TYPE_FUNCTION_CALL:
					delete static_cast<string*>((void*)getValuePtrReference());
					delete getInitializerReference();
					getInitializerReference() = nullptr;
					break;
				case TYPE_PSEUDO_NUMBER: break;
				case TYPE_PSEUDO_MIXED: break;
				case TYPE_STRING:
				case TYPE_FUNCTION_ASSIGNMENT:
					delete static_cast<string*>((void*)getValuePtrReference());
					break;
				case TYPE_ARRAY:
					for (auto arrayValue: getArrayValueReference()) arrayValue->releaseReference();
					delete static_cast<vector<ScriptVariable*>*>((void*)getValuePtrReference());
					delete getInitializerReference();
					getInitializerReference() = nullptr;
					break;
				case TYPE_MAP:
					for (const auto& [mapEntryName, mapEntryValue]: getMapValueReference()) mapEntryValue->releaseReference();
					delete static_cast<unordered_map<string, ScriptVariable*>*>((void*)getValuePtrReference());
					delete getInitializerReference();
					getInitializerReference() = nullptr;
					break;
				case TYPE_SET:
					delete static_cast<unordered_set<string>*>((void*)getValuePtrReference());
					delete getInitializerReference();
					getInitializerReference() = nullptr;
					break;
				default:
					// custom data type
					auto dataTypeIdx = static_cast<int>(this->getType()) - TYPE_PSEUDO_CUSTOM_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::scriptDataTypes.size()) {
						_Console::println("ScriptVariable::setType(): unknown custom data type with id " + to_string(dataTypeIdx));
						return;
					}
					MiniScript::scriptDataTypes[dataTypeIdx]->unsetScriptVariableValue(*this);

			}
			this->getValuePtrReference() = 0LL;
			//
			if (reference != nullptr) {
				reference->type = newType;
			} else {
				type = newType;
			}
			//
			switch(getType()) {
				case TYPE_NULL:
					break;
				case TYPE_BOOLEAN:
					break;
				case TYPE_INTEGER:
					break;
				case TYPE_FLOAT:
					break;
				case TYPE_PSEUDO_NUMBER: break;
				case TYPE_PSEUDO_MIXED: break;
				case TYPE_STRING:
				case TYPE_FUNCTION_ASSIGNMENT:
					getValuePtrReference() = (uint64_t)(new string());
					break;
				case TYPE_ARRAY:
					getValuePtrReference() = (uint64_t)(new vector<ScriptVariable*>());
					getInitializerReference() = new Initializer();
					break;
				case TYPE_MAP:
					getValuePtrReference() = (uint64_t)(new unordered_map<string, ScriptVariable*>());
					getInitializerReference() = new Initializer();
					break;
				case TYPE_SET:
					getValuePtrReference() = (uint64_t)(new unordered_set<string>());
					getInitializerReference() = new Initializer();
					break;
				case TYPE_FUNCTION_CALL:
					getValuePtrReference() = (uint64_t)(new string());
					getInitializerReference() = new Initializer();
					break;
				default:
					// custom data type
					auto dataTypeIdx = static_cast<int>(this->getType()) - TYPE_PSEUDO_CUSTOM_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::scriptDataTypes.size()) {
						_Console::println("ScriptVariable::setType(): unknown custom data type with id " + to_string(dataTypeIdx));
						return;
					}
					MiniScript::scriptDataTypes[dataTypeIdx]->setScriptVariableValue(*this, nullptr);
			}
		}

		/**
		 * Return initializer
		 * @return initializer
		 */
		inline Initializer* getInitializer() const {
			return reference != nullptr?reference->initializer:initializer;
		}

		/**
		 * @return value pointer
		 */
		inline const uint64_t getValuePtr() const {
			return reference != nullptr?reference->valuePtr:valuePtr;
		}

		/**
		 * Set value pointer
		 * @param valuePtr value pointer
		 */
		inline void setValuePtr(uint64_t valuePtr) {
			if (reference != nullptr) {
				reference->valuePtr = valuePtr;
			} else {
				this->valuePtr = valuePtr;
			}
		}

		/**
		 * Get boolean value from given variable
		 * @param value value
		 * @param optional optionalfalse
		 * @return success
		 */
		inline bool getBooleanValue(bool& value, bool optional = false) const {
			switch(getType()) {
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
						const auto& stringValue = getStringValueReference();
						auto lowerCaseString = _StringTools::toLowerCase(stringValue);
						if (lowerCaseString != "false" && lowerCaseString != "true" && lowerCaseString != "1" && lowerCaseString != "0") return optional;
						value = lowerCaseString == "true" || lowerCaseString == "1";
						return true;
					}
				default:
					return optional;
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
			switch(getType()) {
				case TYPE_BOOLEAN:
					value = getBooleanValueReference() == true?1:0;
					return true;
					break;
				case TYPE_INTEGER:
					value = getIntegerValueReference();
					return true;
				case TYPE_FLOAT:
					_Console::println("MiniScript::getIntegerValue(): converting float to integer: precision loss");
					value = getFloatValueReference();
					return true;
				case TYPE_STRING:
					{
						const auto& stringValue = getStringValueReference();
						if (_Integer::is(stringValue) == true) {
							value = _Integer::parse(stringValue);
							return true;
						} else
						if (_Float::is(stringValue) == true) {
							_Console::println("MiniScript::getIntegerValue(): converting float to integer: precision loss");
							value = static_cast<int64_t>(_Float::parse(stringValue));
							return true;
						} else {
							return optional;
						}
					}
				default:
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
			switch(getType()) {
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
						const auto& stringValue = getStringValueReference();
						if (_Float::is(stringValue) == false) return optional;
						value = _Float::parse(stringValue);
					}
					return true;
				default:
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
			switch(getType()) {
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
				case TYPE_FUNCTION_ASSIGNMENT:
					value = getStringValueReference();
					return true;
				default:
					return false;
			}
			return false;
		}

		/**
		 * Set boolean value from given value into variable
		 * @param value value
		 */
		inline void setNullValue() {
			setType(TYPE_NULL);
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
		 * Set array value from given value into variable
		 * @param value value
		 */
		inline void setValue(const vector<ScriptVariable*>& value) {
			setType(TYPE_ARRAY);
			auto& arrayValue = getArrayValueReference();
			for (const auto arrayEntry: value) {
				arrayValue.push_back(new ScriptVariable(*arrayEntry));
			}
		}

		/**
		 * Set map value from given value into variable
		 * @param value value
		 */
		inline void setValue(const unordered_map<string, ScriptVariable*>& value) {
			setType(TYPE_MAP);
			auto& mapValue = getMapValueReference();
			for (const auto& [mapEntryName, mapEntryValue]: value) {
				mapValue[mapEntryName] = new ScriptVariable(*mapEntryValue);
			}
		}

		/**
		 * Set set value from given value into variable
		 * @param value value
		 */
		inline void setValue(const unordered_set<string>& value) {
			setType(TYPE_SET);
			getSetValueReference() = value;
		}

		/**
		 * Set value for custom data types
		 * @param value value
		 */
		inline void setValue(const void* value) {
			// custom data type
			auto dataTypeIdx = static_cast<int>(this->getType()) - TYPE_PSEUDO_CUSTOM_DATATYPES;
			if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::scriptDataTypes.size()) {
				_Console::println("ScriptVariable::setValue(): unknown custom data type with id " + to_string(dataTypeIdx));
				return;
			}
			MiniScript::scriptDataTypes[dataTypeIdx]->setScriptVariableValue(*this, value);
		}

		/**
		 * @return return const pointer to underlying vector or nullptr
		 */
		inline const vector<ScriptVariable*>* getArrayPointer() const {
			if (getType() != TYPE_ARRAY) return nullptr;
			auto& arrayValue = getArrayValueReference();
			return &arrayValue;
		}

		/**
		 * @return pointer to underlying vector or nullptr
		 */
		inline vector<ScriptVariable*>* getArrayPointer() {
			if (getType() != TYPE_ARRAY) return nullptr;
			auto& arrayValue = getArrayValueReference();
			return &arrayValue;
		}

		/**
		 * Get array size
		 * @return array size
		 */
		inline int64_t getArraySize() const {
			if (getType() != TYPE_ARRAY) return 0;
			return getArrayValueReference().size();
		}

		/**
		 * Get entry from array with given index
		 * @param idx index
		 * @return entry from array with given index
		 */
		inline const ScriptVariable getArrayEntry(int idx) const {
			if (getType() != TYPE_ARRAY) return ScriptVariable();
			const auto& arrayValue = getArrayValueReference();
			if (idx >= 0 && idx < arrayValue.size()) return *arrayValue[idx];
			return ScriptVariable();
		}

		/**
		 * Set entry in array with given index
		 * @param idx index
		 */
		inline void setArrayEntry(int idx, const ScriptVariable& value) {
			setType(TYPE_ARRAY);
			if (idx < 0) return;
			auto& arrayValue = getArrayValueReference();
			while (arrayValue.size() <= idx) pushArrayEntry(ScriptVariable());
			arrayValue[idx]->releaseReference();
			arrayValue[idx] = new ScriptVariable(value);
		}

		/**
		 * Push entry to array
		 * @param value value
		 */
		inline void pushArrayEntry(const ScriptVariable& value) {
			setType(TYPE_ARRAY);
			getArrayValueReference().push_back(new ScriptVariable(value));
		}

		/**
		 * Remove array entry at given index
		 * @param idx index
		 */
		inline void removeArrayEntry(int idx) {
			if (getType() != TYPE_ARRAY) return;
			auto& arrayValue = getArrayValueReference();
			if (idx >= 0 && idx < arrayValue.size()) {
				arrayValue[idx]->releaseReference();
				arrayValue.erase(arrayValue.begin() + idx);
			}
			return;
		}

		/**
		 * @return return const pointer to underlying unordered_map or nullptr
		 */
		inline const unordered_map<string, ScriptVariable*>* getMapPointer() const {
			if (getType() != TYPE_MAP) return nullptr;
			auto& mapValue = getMapValueReference();
			return &mapValue;
		}

		/**
		 * @return pointer to underlying unordered_map or nullptr
		 */
		inline unordered_map<string, ScriptVariable*>* getMapPointer() {
			if (getType() != TYPE_MAP) return nullptr;
			auto& mapValue = getMapValueReference();
			return &mapValue;
		}

		/**
		 * Get map size
		 */
		inline int64_t getMapSize() const {
			if (getType() != TYPE_MAP) return 0;
			return getMapValueReference().size();
		}

		/**
		 * Map has entry with given key
		 * @param key key
		 * @return key exists
		 */
		inline bool hasMapEntry(const string& key) const {
			if (getType() != TYPE_MAP) return false;
			const auto& mapValue = getMapValueReference();
			auto it = mapValue.find(key);
			if (it != mapValue.end()) return true;
			return false;
		}

		/**
		 * Get entry from map with given key
		 * @param key key
		 * @return map entry from given key
		 */
		inline const ScriptVariable getMapEntry(const string& key) const {
			if (getType() != TYPE_MAP) return ScriptVariable();
			const auto& mapValue = getMapValueReference();
			auto it = mapValue.find(key);
			if (it != mapValue.end()) return *it->second;
			return ScriptVariable();
		}

		/**
		 * Set entry in map with given key
		 * @param key key
		 * @param value value
		 */
		inline void setMapEntry(const string& key, const ScriptVariable& value) {
			setType(TYPE_MAP);
			auto mapValueIt = getMapValueReference().find(key);
			if (mapValueIt != getMapValueReference().end()) mapValueIt->second->releaseReference();
			getMapValueReference()[key] = new ScriptVariable(value);
		}

		/**
		 * Remove entry in map with given key
		 * @param key key
		 */
		inline void removeMapEntry(const string& key) {
			if (getType() != TYPE_MAP) return;
			auto& mapValue = getMapValueReference();
			auto mapValueIt = mapValue.find(key);
			if (mapValueIt != mapValue.end()) {
				mapValueIt->second->releaseReference();
				mapValue.erase(mapValueIt);
			}
		}

		/**
		 * Get map keys
		 * @return keys
		 */
		inline const vector<string> getMapKeys() const {
			vector<string> keys;
			if (getType() != TYPE_MAP) return keys;
			const auto& mapValue = getMapValueReference();
			for (const auto& [mapEntryName, mapEntryValue]: mapValue) {
				keys.push_back(mapEntryName);
			}
			return keys;
		}

		/**
		 * Get map values
		 * @return values
		 */
		inline const vector<ScriptVariable*> getMapValues() const {
			vector<ScriptVariable*> values;
			if (getType() != TYPE_MAP) return values;
			const auto& mapValue = getMapValueReference();
			for (const auto& [mapEntryKey, mapEntryValue]: mapValue) {
				values.push_back(mapEntryValue);
			}
			return values;
		}

		/**
		 * @return const pointer to underlying unordered_set or nullptr
		 */
		inline const unordered_set<string>* getSetPointer() const {
			if (getType() != TYPE_SET) return nullptr;
			auto& setValue = getSetValueReference();
			return &setValue;
		}

		/**
		 * @return pointer to underlying unordered_set or nullptr
		 */
		inline unordered_set<string>* getSetPointer() {
			if (getType() != TYPE_SET) return nullptr;
			auto& setValue = getSetValueReference();
			return &setValue;
		}

		/**
		 * Get set size
		 */
		inline int64_t getSetSize() const {
			if (getType() != TYPE_SET) return 0;
			return getSetValueReference().size();
		}

		/**
		 * Set has given key
		 * @param key key
		 * @return key exists
		 */
		inline bool hasSetKey(const string& key) const {
			if (getType() != TYPE_SET) return false;
			const auto& setValue = getSetValueReference();
			auto it = setValue.find(key);
			if (it != setValue.end()) return true;
			return false;
		}

		/**
		 * Insert given key in set
		 * @param key key
		 */
		inline void insertSetKey(const string& key) {
			setType(TYPE_SET);
			getSetValueReference().insert(key);
		}

		/**
		 * Remove key in set with given key
		 * @param key key
		 */
		inline void removeSetKey(const string& key) {
			if (getType() != TYPE_SET) return;
			auto& setValue = getSetValueReference();
			auto it = setValue.find(key);
			if (it != setValue.end()) {
				setValue.erase(it);
			}
		}

		/**
		 * Get set keys
		 * @return keys
		 */
		inline const vector<string> getSetKeys() const {
			vector<string> keys;
			if (getType() != TYPE_SET) return keys;
			const auto& setValue = getSetValueReference();
			for (const auto& key: setValue) {
				keys.push_back(key);
			}
			return keys;
		}

		/**
		 * Set array/map values initializer function call statement
		 * @param miniScript miniscript instance
		 * @param statement statement
		 * @param initializerStatement initializer statement
		 */
		void setFunctionCallStatement(const string& initializerStatement, MiniScript* miniScript, const ScriptStatement& statement);

		/**
		 * Set function assignment from given value into variable
		 * @param value value
		 */
		inline void setFunctionAssignment(const string& value) {
			setType(TYPE_FUNCTION_ASSIGNMENT);
			getStringValueReference() = value;
		}

		/**
		 * Set implicit typed value given by value string
		 * @param value value
		 * @param miniScript mini script
		 * @param statement statement
		 */
		inline void setImplicitTypedValue(const string& value, MiniScript* miniScript, const ScriptStatement& statement) {
			setImplicitTypedValueFromStringView(string_view(value), miniScript, statement);
		}

		/**
		 * Set implicit typed value given by value string
		 * @param value value
		 * @param miniScript mini script
		 * @param statement statement
		 */
		inline void setImplicitTypedValueFromStringView(const string_view& value, MiniScript* miniScript, const ScriptStatement& statement) {
			string_view function;
			//
			if (value == "null") {
				setNullValue();
			} else
			if (value == "true") {
				setValue(true);
			} else
			if (value == "false") {
				setValue(false);
			} else
			if (_Integer::viewIs(value) == true) {
				setValue(static_cast<int64_t>(_Integer::viewParse(value)));
			} else
			if (_Float::viewIs(value) == true) {
				setValue(_Float::viewParse(value));
			} else
			if (_StringTools::viewStartsWith(value, "{") == true &&
				_StringTools::viewEndsWith(value, "}") == true) {
				*this = initializeMapSet(value, miniScript, statement);
			} else
			if (_StringTools::viewStartsWith(value, "[") == true &&
				_StringTools::viewEndsWith(value, "]") == true) {
				*this = initializeArray(value, miniScript, statement);
			} else
			if (viewIsFunctionAssignment(value, function) == true) {
				setFunctionAssignment(string(function));
			} else
			// function call
			//	TODO: improve me
			if (value.find('(') != string::npos &&
				value.find(')') != string::npos) {
				setFunctionCallStatement(miniScript->doStatementPreProcessing(string(value), statement), miniScript, statement);
				_Console::println("Function Call Statement: " + miniScript->doStatementPreProcessing(string(value), statement));
			} else
			// variable
			if (viewIsVariableAccess(value) == true) {
				setFunctionCallStatement("getVariable(\"" + string(value) + "\")", miniScript, statement);
				_Console::println("Variable Access: " + string(value));
			} else {
				setValue(string(value));
			}
		}

		/**
		 * Check if given variable type does match expected variable type
		 * @param type type
		 * @param expectedType expected type
		 * @return given variable type does match expected variable type
		 */
		inline static bool isExpectedType(ScriptVariableType type, ScriptVariableType expectedType) {
			if (type == expectedType) return true;
			switch(expectedType) {
				case TYPE_PSEUDO_NUMBER:
					return type == TYPE_INTEGER || type == TYPE_FLOAT || type == TYPE_BOOLEAN;
				case TYPE_PSEUDO_MIXED:
					return true;
				default:
					return false;
			}
		}

		/**
		 * @return class name of given script variable type
		 */
		inline const string& getClassName() {
			return getClassName(getType());
		}

		/**
		 * Return class name of given script variable type
		 * @param type type
		 * @return class name of given script variable type
		 */
		inline static const string& getClassName(ScriptVariableType type) {
			switch (type) {
				case TYPE_NULL: return CLASSNAME_NONE;
				case TYPE_BOOLEAN: return CLASSNAME_NONE;
				case TYPE_INTEGER: return CLASSNAME_NONE;
				case TYPE_FLOAT: return CLASSNAME_NONE;
				case TYPE_FUNCTION_CALL: return CLASSNAME_NONE;
				case TYPE_FUNCTION_ASSIGNMENT: return CLASSNAME_NONE;
				case TYPE_PSEUDO_NUMBER: return CLASSNAME_NONE;
				case TYPE_PSEUDO_MIXED: return CLASSNAME_NONE;
				case TYPE_STRING: return CLASSNAME_STRING;
				case TYPE_ARRAY: return CLASSNAME_ARRAY;
				case TYPE_MAP: return CLASSNAME_MAP;
				case TYPE_SET: return CLASSNAME_SET;
				default:
					// custom data types
					auto dataTypeIdx = static_cast<int>(type) - TYPE_PSEUDO_CUSTOM_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::scriptDataTypes.size()) {
						_Console::println("ScriptVariable::getClassName(): unknown custom data type with id " + to_string(dataTypeIdx));
						return CLASSNAME_NONE;
					}
					return MiniScript::scriptDataTypes[dataTypeIdx]->getClassName();
			}
		}

		/**
		 * Returns given script variable type as string
		 * @param type type
		 * @return script variable type as string
		 */
		inline static const string getTypeAsString(ScriptVariableType type) {
			switch(type) {
				case TYPE_NULL: return "Null";
				case TYPE_BOOLEAN: return "Boolean";
				case TYPE_INTEGER: return "Integer";
				case TYPE_FLOAT: return "Float";
				case TYPE_FUNCTION_CALL: return string();
				case TYPE_FUNCTION_ASSIGNMENT: return string();
				case TYPE_PSEUDO_NUMBER: return "Number";
				case TYPE_PSEUDO_MIXED: return "Mixed";
				case TYPE_STRING: return "String";
				case TYPE_ARRAY: return "Array";
				case TYPE_MAP: return "Map";
				case TYPE_SET: return "Set";
				default:
					// custom data types
					auto dataTypeIdx = static_cast<int>(type) - TYPE_PSEUDO_CUSTOM_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::scriptDataTypes.size()) {
						_Console::println("ScriptVariable::getTypeAsString(): unknown custom data type with id " + to_string(dataTypeIdx));
						return CLASSNAME_NONE;
					}
					return MiniScript::scriptDataTypes[dataTypeIdx]->getTypeAsString();
			}
			return string();
		}

		/**
		 * @return this script variable type as string
		 */
		inline const string getTypeAsString() const {
			return getTypeAsString(getType());
		}

		/**
		 * Returns given return value variable type string representation
		 * @param type type
		 * @param nullable nullable
		 * @return return value variable type string representation
		 */
		inline static const string getReturnTypeAsString(ScriptVariableType type, bool nullable) {
			switch(type) {
				case TYPE_NULL: return "Null";
				default: return string(nullable?"?":"") + getTypeAsString(type);
			}
			return string();
		}

		/**
		 * Returns given return value variable type string representation
		 * @param nullable nullable
		 * @return return value variable type string representation
		 */
		inline const string getReturnTypeAsString(bool nullable) const {
			return getReturnTypeAsString(getType(), nullable);
		}

		/**
		 * @return string representation of script variable type
		 */
		inline const string getAsString() const {
			string result;
			result+= getTypeAsString();
			result+= "(";
			if (getType() == TYPE_STRING) result+= "\"";
			result+= getValueAsString();
			if (getType() == TYPE_STRING) result+= "\"";
			result+= ")";
			return result;
		}

		/**
		 * Print string representation of script variable
		 * @param formatted formatted
		 * @param jsonCompatible json compatible
		 * @param depth recursion depth
		 * @return string representation of script variable type
		 */
		inline const string getValueAsString(bool formatted = false, bool jsonCompatible = false, int depth = 0) const {
			string result;
			switch (getType()) {
				case TYPE_NULL:
					result+= "<Null>";
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
				case TYPE_FUNCTION_CALL:
					result+= "{" + getStringValueReference() + "}";
					break;
				case TYPE_FUNCTION_ASSIGNMENT:
					result+= "() -> " + getStringValueReference();
					break;
				case TYPE_PSEUDO_NUMBER:
					result+= "Number";
					break;
				case TYPE_PSEUDO_MIXED:
					result+= "Mixed";
					break;
				case TYPE_STRING:
					result+= getStringValueReference();
					break;
				case TYPE_ARRAY:
					{
						const auto& arrayValue = getArrayValueReference();
						vector<string> values;
						for (const auto arrayEntry: arrayValue) {
							if (arrayEntry->getType() == TYPE_STRING) {
								values.push_back("\"" + _StringTools::replace(_StringTools::replace(arrayEntry->getValueAsString(formatted, jsonCompatible, depth + 1), "\\", "\\\\"), "\"", "\\\"") + "\"" );
							} else {
								values.push_back(arrayEntry->getValueAsString(formatted, jsonCompatible, depth + 1));
							}
						}
						if (formatted == true) {
							auto i = 0;
							for (auto& value: values) {
								if (i != values.size() - 1) value+= ",";
								i++;
							}
							for (const auto& valueString: values) {
								result+= _StringTools::indent(valueString, "\t" , depth + 1);
								result+= "\n";
							}
							result = (depth == 0?_StringTools::indent("[", "\t", depth):"[") + "\n" + result;
							result+= _StringTools::indent("]", "\t", depth) + (depth == 0?"\n":"");
						} else {
							auto i = 0;
							for (const auto& valueString: values) {
								result+= valueString;
								if (i != values.size() - 1) result+= ", ";
								i++;
							}
							result = "[" + result + "]";
						}
						break;
					}
				case TYPE_MAP:
					{
						const auto& mapValue = getMapValueReference();
						vector<string> values;
						for (const auto& [mapEntryName, mapEntryValue]: mapValue) {
							string value;
							value+= "\"" + _StringTools::replace(_StringTools::replace(mapEntryName, "\\", "\\\\"), "\"", "\\\"") +  "\": ";
							if (mapEntryValue->getType() == TYPE_STRING) {
								value+= "\"";
								value+= _StringTools::replace(_StringTools::replace(mapEntryValue->getValueAsString(formatted, jsonCompatible, depth + 1), "\\", "\\\\"), "\"", "\\\"");
								value+= "\"";
							} else {
								value+= mapEntryValue->getValueAsString(formatted, jsonCompatible, depth + 1);
							}
							values.push_back(value);
						}
						sort(values.begin(), values.end());
						if (formatted == true) {
							auto i = 0;
							for (auto& value: values) {
								if (i != values.size() - 1) value+= ",";
								i++;
							}
							for (const auto& valueString: values) {
								result+= _StringTools::indent(valueString, "\t" , depth + 1);
								result+= "\n";
							}
							result = (depth == 0?_StringTools::indent("{", "\t", depth):"{") + "\n" + result;
							result+= _StringTools::indent("}", "\t", depth) + (depth == 0?"\n":"");
						} else {
							auto i = 0;
							for (const auto& valueString: values) {
								result+= valueString;
								if (i != values.size() - 1) result+= ", ";
								i++;
							}
							result = "{" + result + "}";
						}
						break;
					}
				case TYPE_SET:
					{
						const auto& setValue = getSetValueReference();
						vector<string> values;
						for (const auto& key: setValue) {
							values.push_back(
								"\"" + _StringTools::replace(_StringTools::replace(key, "\\", "\\\\"), "\"", "\\\"") + "\""
							);
							if (jsonCompatible == true) {
								values.back() += ": true";
							}
						}
						sort(values.begin(), values.end());
						if (formatted == true) {
							auto i = 0;
							for (auto& value: values) {
								if (i != values.size() - 1) value+= ",";
								i++;
							}
							for (const auto& valueString: values) {
								result+= _StringTools::indent(valueString, "\t" , depth + 1);
								result+= "\n";
							}
							result = (depth == 0?_StringTools::indent("{", "\t", depth):"{") + "\n" + result;
							result+= _StringTools::indent("}", "\t", depth) + (depth == 0?"\n":"");
						} else {
							auto i = 0;
							for (const auto& valueString: values) {
								result+= valueString;
								if (i != values.size() - 1) result+= ", ";
								i++;
							}
							result = "{" + result + "}";
						}
						break;
					}
				default:
					// custom data types
					auto dataTypeIdx = static_cast<int>(type) - TYPE_PSEUDO_CUSTOM_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::scriptDataTypes.size()) {
						_Console::println("ScriptVariable::getValueAsString(): unknown custom data type with id " + to_string(dataTypeIdx));
						return result;
					}
					return MiniScript::scriptDataTypes[dataTypeIdx]->getValueAsString(*this);

			}
			return result;
		}
	};

	/**
	 * Script State Machine State
	 */
	class ScriptStateMachineState {
	public:
		// forbid class copy
		FORBID_CLASS_COPY(ScriptStateMachineState)

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
			bool reference;
			bool nullable;
		};

		// forbid class copy
		FORBID_CLASS_COPY(ScriptMethod)

		/**
		 * Constructor
		 * @param argumentTypes argument types
		 * @param returnValueType return value type
		 * @param returnValueNullable true if return value can also be a null value
		 */
		ScriptMethod(
			const vector<ArgumentType>& argumentTypes = {},
			ScriptVariableType returnValueType = ScriptVariableType::TYPE_NULL,
			bool returnValueNullable = false
		):
			argumentTypes(argumentTypes),
			returnValueType(returnValueType),
			returnValueNullable(returnValueNullable) {
			//
		}

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
		virtual void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) = 0;

		/**
		 * @return arguments
		 */
		const vector<ArgumentType>& getArgumentTypes() const {
			return argumentTypes;
		}

		/**
		 * Get arguments information
		 * @param beginIdx begin index
		 * @return arguments information
		 */
		inline const string getArgumentsInformation(int beginIdx = 0) const {
			string result;
			auto optionalArgumentCount = 0;
			auto argumentIdx = 0;
			for (const auto& argumentType: argumentTypes) {
				string argumentResult;
				if (argumentType.optional == true) {
					result+= "[";
					optionalArgumentCount++;
				}
				if (argumentIdx > beginIdx) result+= ", ";
				if (optionalArgumentCount > 0 || argumentIdx >= beginIdx) {
					if (argumentType.reference == true) {
						result+= "&";
					}
					result+= "$" + argumentType.name + ": " + (argumentType.nullable == true?"?":"") + ScriptVariable::getTypeAsString(argumentType.type);
				}
				argumentIdx++;
			}
			if (isVariadic() == true) {
				if (argumentIdx > beginIdx) result+= ", ";
				result+="...";
			}
			for (auto i = 0; i < optionalArgumentCount; i++) result+= "]";
			//
			return result;
		}

		/**
		 * @return return value type
		 */
		const ScriptVariableType& getReturnValueType() const {
			return returnValueType;
		}

		/**
		 * @return if return value can be null
		 */
		bool isReturnValueNullable() const {
			return returnValueNullable;
		}

		/**
		 * @return if variadic method
		 */
		virtual bool isVariadic() const {
			return false;
		}

		/**
		 * @return if private
		 */
		virtual bool isPrivate() const {
			return false;
		}

		/**
		 * @return operator
		 */
		virtual ScriptOperator getOperator() const {
			return OPERATOR_NONE;
		}

		/**
		 * @return context function
		 */
		virtual const vector<string>& getContextFunctions() {
			return CONTEXTFUNCTIONS_ALL;
		}

	protected:
		STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTIONS_ALL;
		STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTIONS_ENGINE;
		STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTIONS_LOGIC;
		STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTIONS_ENGINELOGIC;
		STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTION_GUI;

	private:
		vector<ArgumentType> argumentTypes;
		ScriptVariableType returnValueType;
		bool returnValueNullable;
	};

	struct ScriptSyntaxTreeNode {
		enum Type {
			SCRIPTSYNTAXTREENODE_NONE,
			SCRIPTSYNTAXTREENODE_LITERAL,
			SCRIPTSYNTAXTREENODE_EXECUTE_METHOD,
			SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION
		};
		ScriptSyntaxTreeNode():
			type(SCRIPTSYNTAXTREENODE_NONE),
			value(ScriptVariable()),
			method(nullptr),
			arguments({})
		{}
		ScriptSyntaxTreeNode(
			Type type,
			const ScriptVariable& value,
			ScriptMethod* method,
			const vector<ScriptSyntaxTreeNode>& arguments
		):
			type(type),
			value(value),
			method(method),
			arguments(arguments)
		{}
		Type type;
		ScriptVariable value;
		ScriptMethod* method;
		vector<ScriptSyntaxTreeNode> arguments;
	};

	/**
	 * Script
	 */
	struct Script {
		struct ScriptArgument {
			ScriptArgument(
				const string& name,
				bool reference
			):
				name(name),
				reference(reference)
			{}
			string name;
			bool reference;
		};
		enum ScriptType { SCRIPTTYPE_NONE, SCRIPTTYPE_FUNCTION, SCRIPTTYPE_ON, SCRIPTTYPE_ONENABLED };
		Script(
			ScriptType scriptType,
			int line,
			// applies only for on and on-enabled
			const string& condition,
			const string& executableCondition,
			ScriptStatement conditionStatement,
			ScriptSyntaxTreeNode conditionSyntaxTree,
			// applies only for on-enabled
			const string& name,
			bool emitCondition,
			const vector<ScriptStatement>& statements,
			const vector<ScriptSyntaxTreeNode>& syntaxTree,
			// applies only for functions
			bool callable,
			const vector<ScriptArgument>& arguments
		):
			scriptType(scriptType),
			line(line),
			condition(condition),
			executableCondition(executableCondition),
			conditionStatement(conditionStatement),
			conditionSyntaxTree(conditionSyntaxTree),
			name(name),
			emitCondition(emitCondition),
			statements(statements),
			syntaxTree(syntaxTree),
			callable(callable),
			arguments(arguments)
		{}
		ScriptType scriptType;
		int line;
		string condition;
		string executableCondition;
		ScriptStatement conditionStatement;
		ScriptSyntaxTreeNode conditionSyntaxTree;
		string name;
		bool emitCondition;
		vector<ScriptStatement> statements;
		vector<ScriptSyntaxTreeNode> syntaxTree;
		bool callable;
		vector<ScriptArgument> arguments;
	};

	static constexpr int SCRIPTIDX_NONE { -1 };
	static constexpr int LINE_NONE { -1 };
	static constexpr int STATEMENTIDX_NONE { -1 };
	static constexpr int STATEMENTIDX_FIRST { 0 };
	static constexpr int ARGUMENTIDX_NONE { -1 };

	STATIC_DLL_IMPEXT static const string METHOD_SCRIPTCALL;
	STATIC_DLL_IMPEXT static const string METHOD_ENABLENAMEDCONDITION;
	STATIC_DLL_IMPEXT static const string METHOD_DISABLENAMEDCONDITION;

	/**
	 * Returns arguments as string placed in a vector of string_views
	 * @param arguments arguments
	 * @return arguments as string
	 */
	inline const string getArgumentsAsString(const vector<string_view>& arguments) {
		string argumentsString;
		for (const auto& argument: arguments) argumentsString+= (argumentsString.empty() == false?", ":"") + string("'") + string(argument) + string("'");
		return argumentsString;
	}

	/**
	 * Returns arguments as string
	 * @param arguments arguments
	 * @return arguments as string
	 */
	inline const string getArgumentsAsString(const vector<ScriptSyntaxTreeNode>& arguments) {
		string argumentsString;
		for (const auto& argument: arguments) {
			switch (argument.type) {
				case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
					switch(argument.value.getType()) {
						case TYPE_NULL:
							{
								argumentsString+= (argumentsString.empty() == false?", ":"") + string("<Null>");
								break;
							}
						case TYPE_BOOLEAN:
						case TYPE_INTEGER:
						case TYPE_FLOAT:
							{
								argumentsString+= (argumentsString.empty() == false?", ":"") + argument.value.getValueAsString();
								break;
							}
						case TYPE_STRING:
							{
								argumentsString+= (argumentsString.empty() == false?", ":"") + string("\"") + argument.value.getValueAsString() + string("\"");
								break;
							}
						default:
							{
								argumentsString+= (argumentsString.empty() == false?", ":"") + string("<COMPLEX DATATYPE>");
								break;
							}
					}
					break;
				case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
				case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
					argumentsString+= (argumentsString.empty() == false?", ":"") + argument.value.getValueAsString() + string("(") + getArgumentsAsString(argument.arguments) + string(")");
					break;
				default:
					break;
			}
		}
		return argumentsString;
	}

protected:
	static constexpr int SETACCESSBOOL_NONE { -1 };
	static constexpr int SETACCESSBOOL_TRUE { 0 };
	static constexpr int SETACCESSBOOL_FALSE { 1 };
	static constexpr int ARRAYIDX_NONE { -1 };
	static constexpr int ARRAYIDX_ADD { -2 };
	static constexpr int STATE_NONE { -1 };
	static constexpr int OPERATORIDX_NONE { -1 };
	static constexpr int LINE_FIRST { 1 };
	static constexpr int64_t TIME_NONE { -1LL };

	struct ScriptState {
		enum EndType { ENDTYPE_BLOCK, ENDTYPE_FOR, ENDTYPE_IF };
		enum ConditionType {
			SCRIPT,
			CONDITIONTYPE_FORTIME
		};
		int state { STATE_NONE };
		int lastState { STATE_NONE };
		ScriptStateMachineState* lastStateMachineState { nullptr };
		bool running { false };
		int scriptIdx { SCRIPTIDX_NONE };
		int statementIdx { STATEMENTIDX_NONE };
		int gotoStatementIdx { STATEMENTIDX_NONE };
		int64_t timeWaitStarted { TIME_NONE };
		int64_t timeWaitTime { TIME_NONE };
		string id;
		unordered_map<string, ScriptVariable*> variables;
		unordered_map<int, int64_t> forTimeStarted;
		stack<bool> conditionStack;
		stack<EndType> endTypeStack;
		// applies for functions only
		ScriptVariable returnValue;
	};

	bool native;
	vector<Script> scripts;
	string nativeHash;
	vector<Script> nativeScripts;
	vector<unique_ptr<ScriptState>> scriptStateStack;

	// root context variables
	vector<string> enabledNamedConditions;
	int64_t timeEnabledConditionsCheckLast { TIME_NONE };

	vector<string> parseErrors;
	vector<string> deferredFunctionScriptCodes;

	int inlineFunctionIdx { 0 };

	unique_ptr<MathMethods> miniScriptMath;

	/**
	 * Initialize native mini script
	 */
	virtual void initializeNative();

	/**
	 * Set native
	 * @param native native
	 */
	inline void setNative(bool native) {
		this->native = native;
	}

	/**
	 * Set native hash
	 * @param nativeHash native hash
	 */
	inline void setNativeHash(const string& nativeHash) {
		this->nativeHash = nativeHash;
	}

	/**
	 * Go to statement goto from given statement
	 * @param statement statement
	 */
	void gotoStatementGoto(const ScriptStatement& statement) {
		getScriptState().gotoStatementIdx = statement.gotoStatementIdx;
	}

	/**
	 * @return native script
	 */
	inline vector<Script> getNativeScripts() {
		return nativeScripts;
	}

	/**
	 * Set native scripts
	 * @param nativeScripts native scripts
	 */
	inline void setNativeScripts(const vector<Script>& nativeScripts) {
		this->nativeScripts = nativeScripts;
	}

	/**
	 * Set native user script functions
	 * @param nativeScriptFunctions native user script functions
	 */
	inline void setNativeScriptFunctions(const unordered_map<string, int>& nativeScriptFunctions) {
		this->scriptFunctions = nativeScriptFunctions;
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
		auto& scriptState = getScriptState();
		if (isFunctionRunning() == false) enabledNamedConditions.clear();
		scriptState.forTimeStarted.clear();
		while (scriptState.conditionStack.empty() == false) scriptState.conditionStack.pop();
		while (scriptState.endTypeStack.empty() == false) scriptState.endTypeStack.pop();
		if (scriptIdx != SCRIPTIDX_NONE) scriptState.endTypeStack.push(ScriptState::ENDTYPE_BLOCK);
		scriptState.id.clear();
		scriptState.scriptIdx = scriptIdx;
		scriptState.statementIdx = STATEMENTIDX_FIRST;
		scriptState.gotoStatementIdx = STATEMENTIDX_NONE;
		scriptState.timeWaitStarted = _Time::getCurrentMillis();
		scriptState.timeWaitTime = 0LL;
		setScriptStateState(stateMachineState);
	}

	/**
	 * Set running flag to false
	 */
	inline void stopRunning() {
		getScriptState().running = false;
	}

	/**
	 * Stop script execution
	 */
	inline void stopScriptExecution() {
		while (scriptStateStack.size() > 1) popScriptState();
		//
		auto& scriptState = getScriptState();
		//
		scriptState.running = false;
		//
		if (isFunctionRunning() == false) timeEnabledConditionsCheckLast = TIME_NONE;
		resetScriptExecutationState(SCRIPTIDX_NONE, STATEMACHINESTATE_NONE);
	}

	/**
	 * Set script state machine state
	 * @param state state
	 */
	inline void setScriptStateState(int state) {
		auto& scriptState = getScriptState();
		scriptState.state = state;
		scriptState.lastState = STATE_NONE;
		scriptState.lastStateMachineState = nullptr;
	}

	/**
	 * @return is function running
	 */
	inline bool isFunctionRunning() {
		return scriptStateStack.size() > 1;
	}

	/**
	 * Push a new script state
	 */
	inline void pushScriptState() {
		scriptStateStack.push_back(make_unique<ScriptState>());
	}

	/**
	 * Pop script state
	 */
	inline void popScriptState() {
		if (scriptStateStack.empty() == true) return;
		const auto& scriptState = getScriptState();
		for (const auto& [variableName, variable]: scriptState.variables) delete variable;
		scriptStateStack.erase(scriptStateStack.begin() + scriptStateStack.size() - 1);
	}

	/**
	 * Determine script index to start
	 * @return script index or SCRIPTIDX_NONE if no script to start
	 */
	virtual int determineScriptIdxToStart();

	/**
	 * Determine named script index to start
	 * @return script index or SCRIPTIDX_NONE if no script to start
	 */
	virtual int determineNamedScriptIdxToStart();

	/**
	 * Initialize array by initializer string
	 * @param initializerString initializer string
	 * @param miniScript mini script
	 * @param statement statement
	 * @return initialized variable
	 */
	static const ScriptVariable initializeArray(const string_view& initializerString, MiniScript* miniScript, const ScriptStatement& statement);

	/**
	 * Initialize map/set by initializer string
	 * @param initializerString initializer string
	 * @param miniScript mini script
	 * @param statement statement
	 * @return initialized variable
	 */
	static const ScriptVariable initializeMapSet(const string_view& initializerString, MiniScript* miniScript, const ScriptStatement& statement);

private:
	static constexpr bool VERBOSE { false };

	//
	STATIC_DLL_IMPEXT static const string OPERATOR_CHARS;
	STATIC_DLL_IMPEXT static vector<ScriptDataType*> scriptDataTypes;

	// TODO: maybe we need a better naming for this
	// script functions defined by script itself
	unordered_map<string, int> scriptFunctions;
	// script methods defined by using ScriptMethod
	unordered_map<string, ScriptMethod*> scriptMethods;
	unordered_map<int, ScriptStateMachineState*> scriptStateMachineStates;
	unordered_map<uint8_t, ScriptMethod*> scriptOperators;
	string scriptPathName;
	string scriptFileName;
	bool scriptValid { false };

	//
	struct ScriptStatementOperator {
		int idx { OPERATORIDX_NONE };
		ScriptOperator scriptOperator;
	};

	/**
	 * Parse additional script code into this MiniScript instance
	 * @param scriptCode script code
	 * @return success
	 */
	bool parseScriptInternal(const string& scriptCode);


	/**
	 * Execute a single script line
	 */
	void executeScriptLine();

	/**
	 * Get next statement from script code
	 * @param scriptCode script code
	 * @param i character index
	 * @param line script line
	 * @return next statement
	 */
	const string getNextStatement(const string& scriptCode, int& i, int& line);

	/**
	 * Parse a script statement
	 * @param executableStatement executable statement
	 * @param methodName method name
	 * @param arguments arguments
	 * @param statement statment
	 * @param accessObjectMember generated access object member statement
	 * @return success
	 */
	bool parseScriptStatement(const string_view& executableStatement, string_view& methodName, vector<string_view>& arguments, const ScriptStatement& statement, string& accessObjectMemberStatement);

	/**
	 * Execute a script statement
	 * @param syntaxTree syntax tree
	 * @param statement statement
	 * @return return value as script variable
	 */
	ScriptVariable executeScriptStatement(const ScriptSyntaxTreeNode& syntaxTree, const ScriptStatement& statement);

	/**
	 * Create script statement syntax tree
	 * @param methodName method name
	 * @param arguments arguments
	 * @param statement statement
	 * @param syntaxTree syntax tree
	 * @return success
	 */
	bool createScriptStatementSyntaxTree(const string_view& methodName, const vector<string_view>& arguments, const ScriptStatement& statement, ScriptSyntaxTreeNode& syntaxTree);

	/**
	 * Validate callabe
	 * @param function function
	 */
	bool validateCallable(const string& function);

	/**
	 * Validate callable
	 * @param syntaxTreeNode syntax tree node
	 * @param statement statement
	 */
	bool validateCallable(const ScriptSyntaxTreeNode& syntaxTreeNode, const ScriptStatement& statement);

	/**
	 * Validate context functions
	 * @param function function
	 * @param functionStack function stack
	 */
	bool validateContextFunctions(const string& function, vector<string>& functionStack);

	/**
	 * Validate context functions
	 * @param syntaxTreeNode syntax tree node
	 * @param functionStack function stack
	 * @param statement statement
	 */
	bool validateContextFunctions(const ScriptSyntaxTreeNode& syntaxTreeNode, vector<string>& functionStack, const ScriptStatement& statement);

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
	 * @param processedStatement statement that is currently being processed
	 * @param nextOperator next operator
	 * @param statement statement
	 */
	bool getNextStatementOperator(const string& processedStatement, ScriptStatementOperator& nextOperator, const ScriptStatement& statement);

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
	 * @param brackets barrier brackets
	 */
	const string findRightArgument(const string& statement, int position, int& length, string& brackets);

	/**
	 * Find left argument in statement beginning from position
	 * @param statement statement
	 * @param position position
	 * @param length argument length
	 * @param brackets barrier brackets
	 */
	const string findLeftArgument(const string& statement, int position, int& length, string& brackets);

	/**
	 * Do statement pre processing, 1) replace operators with corresponding methods
	 * @param processedStatement statement that is currently being processed
	 * @param statement statement
	 */
	const string doStatementPreProcessing(const string& processedStatement, const ScriptStatement& statement);

	/**
	 * Returns if statement has a object member access
	 * @param executableStatement executable statement
	 * @param object object
	 * @param method method
	 * @param statement statement
	 * @return statement has a object member access
	 */
	bool getObjectMemberAccess(const string_view& executableStatement, string_view& object, string_view& method, const ScriptStatement& statement);

	/**
	 * Get access operator left and right indices
	 * @param name name
	 * @param callerMethod caller method
	 * @param accessOperatorLeftIdx access operator left idx
	 * @param accessOperatorRightIdx access operator right idx
	 * @param statement statement
	 * @param startIdx startIdx
	 */
	bool getVariableAccessOperatorLeftRightIndices(const string& name, const string& callerMethod, string::size_type& accessOperatorLeftIdx, string::size_type& accessOperatorRightIdx, const ScriptStatement* statement = nullptr, int startIdx = 0);

	/**
	 * Evaluate access
	 * @param name name
	 * @param callerMethod caller method
	 * @param arrayAccessOperatorLeftIdx array access operator left idx
	 * @param arrayAccessOperatorRightIdx array access operator right idx
	 * @param arrayIdx array index
	 * @param key map key
	 * @param statement statement
	 */
	bool evaluateAccess(const string& name, const string& callerMethod, string::size_type& arrayAccessOperatorLeftIdx, string::size_type& arrayAccessOperatorRightIdx, int64_t& arrayIdx, string& key, const ScriptStatement* statement = nullptr);

	/**
	 * Returns pointer of variable with given name or nullptr
	 * @param name name
	 * @param callerMethod caller method
	 * @param parentVariable parent variable
	 * @param arrayIdx array index whereas there is ARRAYIDX_ADD for [] or ARRAYIDX_NONE for no array access
	 * @param key key
	 * @param setAccessBool set access bool which returns one of SETACCESSBOOL_NONE, *_TRUE, *_FALSE
	 * @param statement optional statement the variable is read in
	 * @param expectVariable expect variable which controls verbosity
	 * @param global use global context instead of current context
	 * @return pointer to variable
	 */
	ScriptVariable* getVariableIntern(const string& name, const string& callerMethod, ScriptVariable*& parentVariable, int64_t& arrayIdx, string& key, int& setAccessBool, const ScriptStatement* statement = nullptr, bool expectVariable = true, bool global = false);

	/**
	 * Evaluate given statement without executing preprocessor run
	 * @param statement script statement
	 * @param executableStatement executable script statement
	 * @param returnValue script return value
	 * @param pushOwnScriptState push own script state
	 * @return success
	 */
	bool evaluateInternal(const string& statement, const string& executableStatement, ScriptVariable& returnValue, bool pushOwnScriptState = true);

	/**
	  * Initialize variable
	  * @param variable variable
	  * @return initialized variable
	  */
	const ScriptVariable initializeVariable(const ScriptVariable& variable);

	/**
	 * Returns if a given string is a function assignment
	 * @param candidate candidate
	 * @param function function
	 * @return if candidate is a function assignment
	 */
	inline static bool viewIsFunctionAssignment(const string_view& candidate, string_view& function) {
		if (candidate.size() == 0) return false;
		//
		auto i = 0;
		// (
		if (candidate[i++] != '(') return false;
		//
		if (i >= candidate.size()) return false;
		// )
		if (candidate[i++] != ')') return false;
		// spaces
		for (; i < candidate.size() && _Character::isSpace(candidate[i]) == true; i++); if (i >= candidate.size()) return false;
		// -
		if (candidate[i++] != '-') return false;
		//
		if (i >= candidate.size()) return false;
		// >
		if (candidate[i++] != '>') return false;
		// spaces
		for (; i < candidate.size() && _Character::isSpace(candidate[i]) == true; i++); if (i >= candidate.size()) return false;
		//
		auto functionStartIdx = i;
		for (; i < candidate.size(); i++) {
			auto c = candidate[i];
			if (_Character::isAlphaNumeric(c) == false && c != '_') {
				return false;
			}
		}
		//
		function = string_view(&candidate[functionStartIdx], i - functionStartIdx);
		//
		return true;
	}

	/**
	 * Returns if a given string is a inline function
	 * @param candidate candidate
	 * @param arguments arguments
	 * @param functionScriptCode function script code
	 * @return if candidate is a inline function
	 */
	inline static bool viewIsInlineFunction(const string_view& candidate, vector<string_view>& arguments, string_view& functionScriptCode) {
		if (candidate.size() == 0) return false;
		//
		auto i = 0;
		// (
		if (candidate[i++] != '(') return false;
		// spaces
		for (; i < candidate.size() && _Character::isSpace(candidate[i]) == true; i++); if (i >= candidate.size()) return false;
		//
		auto argumentStartIdx = string::npos;
		auto argumentEndIdx = string::npos;
		//
		for (; i < candidate.size(); i++) {
			auto c = candidate[i];
			if (c == '&') {
				if (argumentStartIdx == string::npos) {
					argumentStartIdx = i;
				} else {
					return false;
				}
			} else
			if (c == '$') {
				if (argumentStartIdx == string::npos) {
					argumentStartIdx = i;
				} else
				if (argumentStartIdx == i - 1 && candidate[argumentStartIdx] == '&') {
					// no op
				} else {
					return false;
				}
			} else
			if (c == ',' || c == ')') {
				if (argumentEndIdx == string::npos) {
					if (argumentStartIdx != string::npos) {
						argumentEndIdx = i;
						arguments.push_back(string_view(&candidate[argumentStartIdx], argumentEndIdx - argumentStartIdx));
					}
					//
					argumentStartIdx = string::npos;
					argumentEndIdx = string::npos;
				} else {
					return false;
				}
				if (c == ')') {
					i++;
					break;
				}
			} else
			if (argumentStartIdx != string::npos && _Character::isAlphaNumeric(candidate[i]) == false && c != '_') {
				return false;
			}
		}
		//
		if (i >= candidate.size()) return false;
		// spaces
		for (; i < candidate.size() && _Character::isSpace(candidate[i]) == true; i++); if (i >= candidate.size()) return false;
		// -
		if (candidate[i++] != '-') return false;
		//
		if (i >= candidate.size()) return false;
		// >
		if (candidate[i++] != '>') return false;
		// spaces
		for (; i < candidate.size() && _Character::isSpace(candidate[i]) == true; i++); if (i >= candidate.size()) return false;
		//
		if (candidate[i++] != '{') return false;
		//
		auto scriptCodeStartIdx = i;
		auto scriptCodeEndIdx = string::npos;
		//
		for (auto j = candidate.size() - 1; j > i; j--) {
			if (candidate[j] == '}') {
				scriptCodeEndIdx = j;
				break;
			} else
			if (_Character::isSpace(candidate[j]) == false) {
				return false;
			}
		}
		//
		if (scriptCodeEndIdx == string::npos) return false;
		//
		functionScriptCode = string_view(&candidate[scriptCodeStartIdx], scriptCodeEndIdx - scriptCodeStartIdx);
		//
		return true;
	}

	/**
	 * Returns if a given string is a variable name
	 * @param candidate candidate
	 * @return if string is a variable name
	 */
	inline static bool viewIsVariableAccess(const string_view& candidate) {
		if (candidate.size() == 0) return false;
		if (candidate[0] != '$') return false;
		auto squareBracketCount = 0;
		for (auto i = 1; i < candidate.size(); i++) {
			auto c = candidate[i];
			if (c == '[') {
				squareBracketCount++;
			} else
			if (c == ']') {
				squareBracketCount--;
			} else
			if (squareBracketCount == 0 && _Character::isAlphaNumeric(c) == false && c != '_' && c != '.') {
				return false;
			}
		}
		return true;
	}

	/**
	 * Returns if a given string is a valid map key name
	 * @param candidate candidate
	 * @return if string is a valid map key name
	 */
	static bool viewIsKey(const string_view& candidate);

public:

	/**
	 * Returns string representation of given argument indices
	 * @param argumentIndices argument indices
	 * @param delimiter delimiter
	 * @return string representation of given argument indices
	 */
	inline static const string getArgumentIndicesAsString(const vector<int>& argumentIndices, const string& delimiter) {
		string result;
		for (const auto argumentIdx: argumentIndices) {
			if (result.empty() == false) result+= delimiter;
			result+= to_string(argumentIdx);
		}
		return result;
	}

	/**
	 * @return data types
	 */
	inline static const vector<ScriptDataType*>& getDataTypes() {
		return scriptDataTypes;
	}

	/**
	 * Returns data type by class name or nullptr
	 * @param className class name
	 * @return script data type
	 */
	inline static ScriptDataType* getDataTypeByClassName(const string& className) {
		for (const auto scriptDataType: scriptDataTypes) {
			if (scriptDataType->getClassName() == className) return scriptDataType;
		}
		return nullptr;
	}

	/**
	 * Register script data type
	 * @param scriptDataType script data type
	 */
	static void registerDataType(ScriptDataType* scriptDataType);

	// forbid class copy
	FORBID_CLASS_COPY(MiniScript)

	/**
	 * Default constructor
	 */
	MiniScript();

	/**
	 * Destructor
	 */
	virtual ~MiniScript();

	/**
	 * @return base class
	 */
	virtual const string getBaseClass();

	/**
	 * @return transpilation units
	 */
	virtual const vector<string> getTranspilationUnits();

	/**
	 * @return parse errors
	 */
	inline const vector<string>& getParseErrors() {
		return parseErrors;
	}

	/**
	 * @return if this script is valid to be executed
	 */
	inline bool isValid() {
		return scriptValid;
	}

	/**
	 * @return if this script was compiled to C++ and is executed nativly
	 */
	inline bool isNative() {
		return native;
	}

	/**
	 * @return native script hash
	 */
	inline const string& getNativeHash() {
		return nativeHash;
	}

	/**
	 * @return script file name
	 */
	inline const string& getScriptFileName() {
		return scriptFileName;
	}

	/**
	 * @return scripts
	 */
	const vector<Script>& getScripts() {
		return scripts;
	}

	/**
	 * @return script state
	 */
	inline ScriptState& getRootScriptState() {
		return *(scriptStateStack[0].get());
	}

	/**
	 * @return script state
	 */
	inline ScriptState& getScriptState() {
		return *(scriptStateStack[scriptStateStack.size() - 1].get());
	}

	/**
	 * @return mini script math
	 */
	inline MathMethods* getMathMethods() {
		return miniScriptMath.get();
	}

	/**
	 * Start error script
	 */
	inline void startErrorScript() {
		emit("error");
	}

	/**
	 * Returns if method with given name does exist
	 * @param methodName method name
	 * @return method exists
	 */
	inline bool hasMethod(const string& methodName) {
		return scriptMethods.find(methodName) != scriptMethods.end();
	}

	/**
	 * Returns if function with given name does exist
	 * @param functionName function name
	 * @return function exists
	 */
	inline bool hasFunction(const string& functionName) {
		return scriptFunctions.find(functionName) != scriptFunctions.end();
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
	 * Return script statement information
	 * @param statement statement
	 * @return script statement information
	 */
	inline const string getStatementInformation(const ScriptStatement& statement) {
		return scriptFileName + ":" + to_string(statement.line) +  ": " + statement.statement;
	}

	/**
	 * Get script argument information
	 * @param methodName method name
	 * @return script argument information
	 */
	inline const string getArgumentInformation(const string& methodName) {
		auto scriptMethod = getMethod(methodName);
		if (scriptMethod == nullptr) {
			_Console::println("MiniScript::getArgumentInformation(): method not found: " + methodName);
			return "No information available";
		}
		return scriptMethod->getArgumentsInformation();
	}

	/**
	 * Get operator as string
	 * @param scriptOperator script operator
	 * @return script operator as string
	 */
	inline static string getOperatorAsString(ScriptOperator scriptOperator) {
		switch(scriptOperator) {
			case(OPERATOR_NONE): return "NONE";
			case(OPERATOR_INCREMENT): return "++";
			case(OPERATOR_DECREMENT): return "--";
			case(OPERATOR_NOT): return "!";
			case(OPERATOR_BITWISENOT): return "~";
			case(OPERATOR_MULTIPLICATION): return "*";
			case(OPERATOR_DIVISION): return "/";
			case(OPERATOR_MODULO): return "%";
			case(OPERATOR_ADDITION): return "+";
			case(OPERATOR_SUBTRACTION): return "-";
			case(OPERATOR_LESSER): return "<";
			case(OPERATOR_LESSEREQUALS): return "<=";
			case(OPERATOR_GREATER): return ">";
			case(OPERATOR_GREATEREQUALS): return ">=";
			case(OPERATOR_EQUALS): return "==";
			case(OPERATOR_NOTEQUAL): return "!=";
			case(OPERATOR_BITWISEAND): return "&";
			case(OPERATOR_BITWISEXOR): return "^";
			case(OPERATOR_BITWISEOR): return "|";
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
	inline static bool hasType(const span<ScriptVariable>& arguments, ScriptVariableType type) {
		for (const auto& argument: arguments) if (argument.getType() == type) return true;
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
	inline static bool getBooleanValue(const span<ScriptVariable>& arguments, int idx, bool& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
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
	inline static bool getIntegerValue(const span<ScriptVariable>& arguments, int idx, int64_t& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
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
	inline static bool getFloatValue(const span<ScriptVariable>& arguments, int idx, float& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
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
	inline static bool getStringValue(const span<ScriptVariable>& arguments, int idx, string& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		return argument.getStringValue(value, optional);
	}

	/**
	 * Register script state machine state
	 * @param state state
	 */
	void registerStateMachineState(ScriptStateMachineState* state);

	/**
	 * Register script method
	 * @param scriptMethod script method
	 */
	void registerMethod(ScriptMethod* scriptMethod);

	/**
	 * Returns if a given string is a variable name
	 * @param candidate candidate
	 * @return if string is a variable name
	 */
	inline static bool isVariableAccess(const string& candidate) {
		if (candidate.size() == 0) return false;
		if (candidate[0] != '$') return false;
		auto squareBracketCount = 0;
		for (auto i = 1; i < candidate.size(); i++) {
			auto c = candidate[i];
			if (c == '[') {
				squareBracketCount++;
			} else
			if (c == ']') {
				squareBracketCount--;
			} else
			if (squareBracketCount == 0 && _Character::isAlphaNumeric(c) == false && c != '_' && c != '.') {
				return false;
			}
		}
		return true;
	}

	/**
	 * Returns variable with given name
	 * @param name name
	 * @param statement optional statement the variable is read in
	 * @param createReference optional flag for creating variable references
	 * @return variable
	 */
	inline const ScriptVariable getVariable(const string& name, const ScriptStatement* statement = nullptr, bool createReference = false) {
		// global accessor
		string globalVariableName;
		if (_StringTools::startsWith(name, "$GLOBAL.") == true) {
			globalVariableName = "$" + _StringTools::trim(_StringTools::substring(name, 8));
		}

		//
		ScriptVariable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		auto variablePtr = getVariableIntern(globalVariableName.empty() == true?name:globalVariableName, __FUNCTION__, parentVariable, arrayIdx, key, setAccessBool, statement, true, globalVariableName.empty() == false);
		if (setAccessBool != SETACCESSBOOL_NONE) {
			return ScriptVariable(setAccessBool == SETACCESSBOOL_TRUE);
		} else
		if (variablePtr != nullptr) {
			return createReference == false?*variablePtr:ScriptVariable::createReferenceVariable(variablePtr);
		} else {
			return ScriptVariable();
		}
	}

	/**
	 * Set script variable
	 * @param name name
	 * @param variable variable
	 * @param statement optional statement the variable is written in
	 * @param createReference optional flag for creating variable references
	 */
	inline void setVariable(const string& name, const ScriptVariable& variable, const ScriptStatement* statement = nullptr, bool createReference = false) {
		// global accessor
		string globalVariableName;
		if (_StringTools::startsWith(name, "$GLOBAL.") == true) {
			globalVariableName = "$" + _StringTools::trim(_StringTools::substring(name, 8));
		}

		//
		ScriptVariable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		auto variablePtr = getVariableIntern(globalVariableName.empty() == true?name:globalVariableName, __FUNCTION__, parentVariable, arrayIdx, key, setAccessBool, statement, false, globalVariableName.empty() == false);
		// common case
		if (variablePtr != nullptr) {
			*variablePtr = variable;
			return;
		} else
		// array add operator
		if (key.empty() == false) {
			if (parentVariable == nullptr) {
				string callerMethod = __FUNCTION__;
				if (statement != nullptr) {
					_Console::println("MiniScript::" + callerMethod + "(): " + getStatementInformation(*statement) + ": variable: '" + name + "': map access operator without map: '" + key + "'");
				} else {
					_Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': map access operator without map: '" + key + "'");
				}
			} else
			// all checks passed, push to map
			if (parentVariable->getType() == MiniScript::TYPE_MAP) {
				parentVariable->setMapEntry(key, createReference == false?ScriptVariable::createNonReferenceVariable(&variable):ScriptVariable::createReferenceVariable(&variable));
			} else
			if (parentVariable->getType() == MiniScript::TYPE_SET) {
				bool booleanValue;
				if (variable.getBooleanValue(booleanValue, false) == true) {
					if (booleanValue == true) {
						parentVariable->insertSetKey(key);
					} else {
						parentVariable->removeSetKey(key);
					}
				} else {
					string callerMethod = __FUNCTION__;
					_Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': set access operator: expected boolean variable to remove/insert key in set, but got " + variable.getTypeAsString());
				}
			} else {
				string callerMethod = __FUNCTION__;
				if (statement != nullptr) {
					_Console::println("MiniScript::" + callerMethod + "(): " + getStatementInformation(*statement) + ": variable: '" + name + "': map/set access operator: expected map/set, but got " + parentVariable->getTypeAsString() + ": '" + key + "'");
				} else {
					_Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': map/set access operator: expected map/set, but got " + parentVariable->getTypeAsString() + ": '" + key + "'");
				}
			}
			//
			return;
		} else
		if (arrayIdx == ARRAYIDX_ADD) {
			if (parentVariable == nullptr) {
				string callerMethod = __FUNCTION__;
				if (statement != nullptr) {
					_Console::println("MiniScript::" + callerMethod + "(): " + getStatementInformation(*statement) + ": variable: '" + name + "': [] array push operator without array");
				} else {
					_Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': [] array push operator without array");
				}
			} else
			if (parentVariable->getType() != MiniScript::TYPE_ARRAY) {
				string callerMethod = __FUNCTION__;
				if (statement != nullptr) {
					_Console::println("MiniScript::" + callerMethod + "(): " + getStatementInformation(*statement) + ": variable: '" + name + "': [] array push operator: expected array , but got " + parentVariable->getTypeAsString());
				} else {
					_Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': [] array push operator: expected array, but got " + parentVariable->getTypeAsString());
				}
			} else {
				// all checks passed, push variable to array
				auto& arrayValueReference = parentVariable->getArrayValueReference();
				arrayValueReference.push_back(createReference == false?ScriptVariable::createNonReferenceVariablePointer(&variable):ScriptVariable::createReferenceVariablePointer(&variable));
			}
			//
			return;
		}

		// default
		auto& scriptState = globalVariableName.empty() == true?getScriptState():getRootScriptState();
		auto scriptVariableIt = scriptState.variables.find(globalVariableName.empty() == true?name:globalVariableName);
		if (scriptVariableIt != scriptState.variables.end()) {
			*scriptVariableIt->second = variable;
			return;
		} else {
			scriptState.variables[globalVariableName.empty() == true?name:globalVariableName] =
				createReference == false?ScriptVariable::createNonReferenceVariablePointer(&variable):ScriptVariable::createReferenceVariablePointer(&variable);
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
	 * Parse script
	 * @param pathName path name
	 * @param fileName file name
	 */
	void parseScript(const string& pathName, const string& fileName);

	/**
	 * Start script
	 */
	virtual void startScript();

	/**
	 * Check if condition with given name exists
	 * @param condition condition
	 * @return condition with given name exists
	 */
	inline bool hasCondition(const string& condition) {
		// iterate scripts to find out if condition exists
		for (const auto& script: scripts) {
			if (script.scriptType != Script::SCRIPTTYPE_ON) {
				// no op
			} else
			if (script.emitCondition == true && script.condition == condition) {
				// no op
				return true;
			}
		}
		//
		return false;
	}

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
	 * Call (script user) function
	 * @param function (script user) function
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @return success
	 */
	inline int getFunctionScriptIdx(const string& function) {
		// lookup function
		auto scriptFunctionsIt = scriptFunctions.find(function);
		if (scriptFunctionsIt == scriptFunctions.end()) {
			return SCRIPTIDX_NONE;
		}
		//
		auto scriptIdx = scriptFunctionsIt->second;
		//
		return scriptIdx;
	}

	/**
	 * Call (script user) function
	 * @param scriptIdx script index
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @return success
	 */
	virtual bool call(int scriptIdx, span<ScriptVariable>& argumentValues, ScriptVariable& returnValue);

	/**
	 * Call (script user) function
	 * @param function (script user) function
	 * @param argumentValues argument values
	 * @param returnValue return value
	 * @return success
	 */
	inline bool call(const string& function, span<ScriptVariable>& argumentValues, ScriptVariable& returnValue) {
		// lookup function
		auto scriptFunctionsIt = scriptFunctions.find(function);
		if (scriptFunctionsIt == scriptFunctions.end()) {
			// _Console::println("MiniScript::call(): Script user function not found: " + function);
			return false;
		}
		//
		auto scriptIdx = scriptFunctionsIt->second;
		// call it
		return call(scriptIdx, argumentValues, returnValue);
	}

	/**
	 * Evaluate given statement
	 * @param statement script statement
	 * @param returnValue script return value
	 * @return success
	 */
	inline bool evaluate(const string& evaluateStatement, ScriptVariable& returnValue) {
		ScriptStatement evaluateScriptStatement(
			LINE_NONE,
			STATEMENTIDX_FIRST,
			"internal.script.evaluate(" + _StringTools::replace(_StringTools::replace(evaluateStatement, "\\", "\\\\"), "\"", "\\\"") + ")",
			"internal.script.evaluate(" + _StringTools::replace(_StringTools::replace(evaluateStatement, "\\", "\\\\"), "\"", "\\\"") + ")",
			STATEMENTIDX_NONE
		);
		return evaluateInternal(evaluateStatement, doStatementPreProcessing(evaluateStatement, evaluateScriptStatement), returnValue);
	}

	/**
	 * @return is running
	 */
	inline bool isRunning() {
		return getScriptState().running;
	}

	/**
	 * Get method by method name
	 * @param methodName method name
	 * @return script method or nullptr
	 */
	inline ScriptMethod* getMethod(const string& methodName) {
		auto scriptMethodIt = scriptMethods.find(methodName);
		if (scriptMethodIt != scriptMethods.end()) {
			return scriptMethodIt->second;
		} else {
			return nullptr;
		}
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
	 * Get miniscript script information
	 * @param scriptIdx script index
	 * @param includeStatements include statements
	 * @return information as string
	 */
	const string getScriptInformation(int scriptIdx, bool includeStatements = true);

	/**
	 * Get miniscript instance information
	 * @return information as string
	 */
	const string getInformation();

};
