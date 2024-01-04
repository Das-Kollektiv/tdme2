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
#include <miniscript/miniscript/Context.h>
#include <miniscript/miniscript/Library.h>
#include <miniscript/utilities/Character.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>
#include <miniscript/utilities/Float.h>
#include <miniscript/utilities/Integer.h>
#include <miniscript/utilities/StringTools.h>
#include <miniscript/utilities/Time.h>
#include <miniscript/utilities/UTF8CharacterIterator.h>

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
using _UTF8CharacterIterator = miniscript::utilities::UTF8CharacterIterator;
using _Context = miniscript::miniscript::Context;
using _Library = miniscript::miniscript::Library;

/**
 * Miniscript
 * @author Andreas Drewke
 */
class miniscript::miniscript::MiniScript {
	friend class BaseMethods;
	friend class JSONMethods;
	friend class ScriptMethods;
	friend class Transpiler;

public:
	enum Operator {
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

	enum StateMachineStateId {
		STATEMACHINESTATE_NONE = -1,
		STATEMACHINESTATE_NEXT_STATEMENT,
		STATEMACHINESTATE_WAIT,
		STATEMACHINESTATE_WAIT_FOR_CONDITION
	};

	struct Statement {
		Statement(
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

	enum VariableType {
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
		TYPE_BYTEARRAY,
		TYPE_ARRAY,
		TYPE_MAP,
		TYPE_SET,
		TYPE_PSEUDO_CUSTOM_DATATYPES,
	};

	//
	class SyntaxTreeNode;
	class Variable;

	/**
	 * Data type
	 */
	class DataType {
		friend class MiniScript;
		friend class MathMethods;

	protected:
		bool mathDataType { false };
		MiniScript::VariableType type { TYPE_NULL };

		/**
		 * Set type
		 * @param type type
		 */
		inline void setType(MiniScript::VariableType type) {
			this->type = type;
		}

		/**
		 * @return is math data type
		 */
		inline bool isMathDataType() {
			return mathDataType;
		}

		/**
		 * Register constants
		 * @param miniScript MiniScript instance
		 */
		virtual void registerConstants(MiniScript* miniScript) const = 0;

		/**
		 * Register methods
		 * @param miniScript MiniScript instance
		 */
		virtual void registerMethods(MiniScript* miniScript) const = 0;

		/**
		 * Unset variable value
		 * @param variable variable
		 */
		virtual void unsetVariableValue(Variable& variable) const = 0;

		/**
		 * Set variable value
		 * @param variable variable
		 */
		virtual void setVariableValue(Variable& variable) const = 0;

		/**
		 * Set variable value
		 * @param variable variable
		 * @param value value
		 */
		virtual void setVariableValue(Variable& variable, const void* value) const = 0;

		/**
		 * Copy variable
		 * @param to to
		 * @param from from
		 */
		virtual void copyVariable(Variable& to, const Variable& from) const = 0;

		/**
		 * Multiply
		 * @param miniScript MiniScript instance
		 * @param arguments argument values
		 * @param returnValue return value
		 * @param statement statement
		 * @return mul was executed
		 */
		virtual bool mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const = 0;

		/**
		 * Division
		 * @param miniScript MiniScript instance
		 * @param arguments argument values
		 * @param returnValue return value
		 * @param statement statement
		 * @return div was executed
		 */
		virtual bool div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const = 0;

		/**
		 * Addition
		 * @param miniScript MiniScript instance
		 * @param arguments argument values
		 * @param returnValue return value
		 * @param statement statement
		 * @return add was executed
		 */
		virtual bool add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const = 0;

		/**
		 * Subtraction
		 * @param miniScript MiniScript instance
		 * @param arguments argument values
		 * @param returnValue return value
		 * @param statement statement
		 * @return sub was executed
		 */
		virtual bool sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const = 0;

	public:
		// forbid class copy
		FORBID_CLASS_COPY(DataType)

		/**
		 * Data type
		 * @param mathDataType is math data type and provides math methods
		 */
		DataType(bool mathDataType): mathDataType(mathDataType) {
			//
		}

		virtual ~DataType() {
			//
		}

		/**
		 * @return type
		 */
		inline MiniScript::VariableType getType() const {
			return type;
		}

		/**
		 * @return type as string
		 */
		virtual const string& getTypeAsString() const = 0;

		/**
		 * Returns value as string
		 * @param variable variable
		 * @return value as string
		 */
		virtual const string getValueAsString(const Variable& variable) const = 0;

	};

	/**
	 * Variable
	 */
	class Variable {
		friend class MiniScript;

	private:
		/**
		 * Variable initializer
		 */
		class Initializer {
			public:
				/**
				 * Constructor
				 */
				Initializer():
					statement(
						MiniScript::Statement(
							MiniScript::LINE_NONE,
							MiniScript::STATEMENTIDX_NONE,
							string(),
							string(),
							MiniScript::STATEMENTIDX_NONE
						)
					),
					syntaxTree(new SyntaxTreeNode()) {
					//
				}

				/**
				 * Constructor
				 * @param initializerString initializer string
				 * @param statement statement
				 * @param syntaxTree syntax tree
				 */
				Initializer(const string& initializerString, const Statement& statement, SyntaxTreeNode* syntaxTree): initializerString(initializerString), statement(statement), syntaxTree(syntaxTree) {}

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
				const Statement& getStatement() const {
					return statement;
				}

				/**
				 * @return syntax tree node
				 */
				const SyntaxTreeNode* getSyntaxTree() const {
					return syntaxTree;
				}

			private:
				string initializerString;
				Statement statement;
				SyntaxTreeNode* syntaxTree;
		};

		//
		static constexpr uint32_t TYPE_BITS_VALUE { 1073741823 }; // 2 ^ 30 - 1
		static constexpr uint32_t CONSTANT_BIT_VALUE { 1073741824 }; // 2 ^ 30
		static constexpr uint32_t REFERENCE_BIT_VALUE { 2147483648 }; // 2 ^ 31

		//
		union ir {
			Initializer* initializer;
			Variable* reference;
		};

		/**
		 * String value
		 */
		class StringValue {
			friend class Variable;
		public:
			/**
			 * Constructor
			 */
			StringValue(): cache(_UTF8CharacterIterator::UTF8PositionCache()) {}

			/**
			 * Constructor
			 * @param value value
			 */
			StringValue(const string& value): value(value) {}

			/**
			 * @return value
			 */
			const string& getValue() const {
				return value;
			}

			/**
			 * Set value
			 * @param value value
			 */
			void setValue(const string& value) {
				this->value = value;
				cache.removeCache();
			}

			/**
			 * @return const cache
			 */
			const _UTF8CharacterIterator::UTF8PositionCache& getCache() const {
				return cache;
			}

			/**
			 * @return cache
			 */
			_UTF8CharacterIterator::UTF8PositionCache& getCache() {
				return cache;
			}

			/**
			 * Set cache
			 * @param cache cache
			 */
			void setCache(const _UTF8CharacterIterator::UTF8PositionCache& cache) {
				this->cache = cache;
			}

		private:
			string value;
			_UTF8CharacterIterator::UTF8PositionCache cache;
		};

		// 24 bytes
		uint32_t typeReferenceConstantBits { TYPE_NULL };	// 4 bytes
		int32_t referenceCounter { 1 };				// 4 bytes
		uint64_t valuePtr { 0LL };					// 8 bytes
		ir ir {};									// 8 bytes

		/**
		 * @return is constant
		 */
		inline bool isConstant() const {
			return
				(typeReferenceConstantBits & CONSTANT_BIT_VALUE) == CONSTANT_BIT_VALUE ||
				(isReference() == true && (ir.reference->typeReferenceConstantBits & CONSTANT_BIT_VALUE) == CONSTANT_BIT_VALUE);
		}

		/**
		 * Set constant
		 */
		inline void setConstant() {
			typeReferenceConstantBits|= CONSTANT_BIT_VALUE;
		}

		/**
		 * Unset constant
		 */
		inline void unsetConstant() {
			typeReferenceConstantBits&= TYPE_BITS_VALUE | REFERENCE_BIT_VALUE;
		}

		/**
		 * @return is reference
		 */
		inline bool isReference() const {
			return (typeReferenceConstantBits & REFERENCE_BIT_VALUE) == REFERENCE_BIT_VALUE;
		}

		/**
		 * @return unset reference
		 */
		inline void unsetReference() {
			typeReferenceConstantBits&= TYPE_BITS_VALUE | CONSTANT_BIT_VALUE;
			ir.reference = nullptr;
		}

		/**
		 * Set reference
		 * @param variable variable
		 */
		inline void setReference(Variable* variable) {
			typeReferenceConstantBits|= REFERENCE_BIT_VALUE;
			ir.reference = (Variable*)variable;
			ir.reference->acquireReference();
		}

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
			if (isReference() == true) {
				ir.reference->releaseReference();
			}
			if (--referenceCounter == 0) {
				if (isReference() == true) unsetReference();
				setType(TYPE_NULL);
				delete this;
			}
		}

		/**
		 * Return initializer
		 * @return initializer
		 */
		inline Initializer*& getInitializerReference() {
			return isReference() == false?ir.initializer:ir.reference->ir.initializer;
		}

		/**
		 * Return const value pointer
		 * @return value ptr
		 */
		inline const uint64_t& getValuePtrReference() const {
			return isReference() == false?valuePtr:ir.reference->valuePtr;
		}

		/**
		 * Return value pointer
		 * @return value ptr
		 */
		inline uint64_t& getValuePtrReference() {
			return isReference() == false?valuePtr:ir.reference->valuePtr;
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
		inline StringValue& getStringValueReference() {
			return *static_cast<StringValue*>((void*)getValuePtrReference());
		}

		/**
		 * @return const string value reference
		 */
		inline const StringValue& getStringValueReference() const {
			return *static_cast<StringValue*>((void*)getValuePtrReference());
		}

		/**
		 * @return byte array value reference
		 */
		inline vector<uint8_t>& getByteArrayValueReference() {
			return *static_cast<vector<uint8_t>*>((void*)getValuePtrReference());
		}

		/**
		 * @return const byte array value reference
		 */
		inline const vector<uint8_t>& getByteArrayValueReference() const {
			return *static_cast<vector<uint8_t>*>((void*)getValuePtrReference());
		}

		/**
		 * @return array value reference
		 */
		inline vector<Variable*>& getArrayValueReference() {
			return *static_cast<vector<Variable*>*>((void*)getValuePtrReference());
		}

		/**
		 * @return const array value reference
		 */
		inline const vector<Variable*>& getArrayValueReference() const {
			return *static_cast<vector<Variable*>*>((void*)getValuePtrReference());
		}

		/**
		 * @return map value reference
		 */
		inline unordered_map<string, Variable*>& getMapValueReference() {
			return *static_cast<unordered_map<string, Variable*>*>((void*)getValuePtrReference());
		}

		/**
		 * @return const map value reference
		 */
		inline const unordered_map<string, Variable*>& getMapValueReference() const {
			return *static_cast<unordered_map<string, Variable*>*>((void*)getValuePtrReference());
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
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_NONE;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_NULL;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_BOOLEAN;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_INTEGER;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_FLOAT;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_FUNCTION;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_NUMBER;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_MIXED;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_STRING;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_BYTEARRAY;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_ARRAY;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_MAP;
		MINISCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_SET;

		/**
		 * Unset variable
		 */
		inline void unset() {
			if (isReference() == true) {
				ir.reference->releaseReference();
				unsetReference();
			}
			setType(TYPE_NULL);
		}

		/**
		 * Create reference variable
		 * @param variable variable
		 * @returns reference variable
		 */
		inline static Variable createReferenceVariable(const Variable* variable) {
			// copy a reference variable is cheap
			if (variable->isReference() == true) return *variable;
			//
			Variable referenceVariable;
			referenceVariable.setReference((Variable*)variable);
			return referenceVariable;
		}

		/**
		 * Create reference variable pointer
		 * @param variable variable
		 * @returns reference variable
		 */
		inline static Variable* createReferenceVariablePointer(const Variable* variable) {
			// copy a reference variable is cheap
			if (variable->isReference() == true) return new Variable(*variable);
			//
			Variable* referenceVariable = new Variable();
			referenceVariable->setReference((Variable*)variable);
			return referenceVariable;
		}

		/**
		 * Create none reference variable
		 * @param variable variable
		 * @returns reference variable
		 */
		inline static Variable createNonReferenceVariable(const Variable* variable) {
			// copy a non reference variable is cheap
			if (variable->isReference() == false) return *variable;
			// otherwise do the copy
			Variable nonReferenceVariable;
			//
			copyVariable(nonReferenceVariable, *variable);
			//
			return nonReferenceVariable;
		}

		/**
		 * Create none reference variable pointer
		 * @param variable variable
		 * @returns reference variable
		 */
		inline static Variable* createNonReferenceVariablePointer(const Variable* variable) {
			// copy a non reference variable is cheap
			if (variable->isReference() == false) return new Variable(*variable);
			// otherwise do the copy
			Variable* nonReferenceVariable = new Variable();
			//
			copyVariable(*nonReferenceVariable, *variable);
			//
			return nonReferenceVariable;
		}

		/**
		 * Copy variable
		 * @param from from
		 * @param to to
		 */
		inline static void copyVariable(Variable& to, const Variable& from) {
			// initial setup
			to.setType(from.getType());
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
					to.getStringValueReference().setValue(from.getStringValueReference().getValue());
					// copy initializer if we have any
					to.getInitializer()->copy(from.getInitializer());
					//
					break;
				case TYPE_FUNCTION_ASSIGNMENT:
					to.setFunctionAssignment(from.getStringValueReference().getValue());
					break;
				case TYPE_PSEUDO_NUMBER: break;
				case TYPE_PSEUDO_MIXED: break;
				case TYPE_STRING:
					to.getStringValueReference().setValue(from.getStringValueReference().getValue());
					to.getStringValueReference().setCache(from.getStringValueReference().getCache());
					break;
				case TYPE_BYTEARRAY:
					to.setValue(from.getByteArrayValueReference());
					break;
				case TYPE_ARRAY:
					to.setValue(from.getArrayValueReference());
					// copy initializer if we have any
					to.getInitializer()->copy(from.getInitializer());
					//
					break;
				case TYPE_MAP:
					to.setValue(from.getMapValueReference());
					// copy initializer if we have any
					to.getInitializer()->copy(from.getInitializer());
					//
					break;
				case TYPE_SET:
					to.setValue(from.getSetValueReference());
					// copy initializer if we have any
					to.getInitializer()->copy(from.getInitializer());
					//
					break;
				default:
					// custom data type
					auto dataTypeIdx = static_cast<int>(from.getType()) - TYPE_PSEUDO_CUSTOM_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::dataTypes.size()) {
						_Console::println("ScriptVariable::copyScriptVariable(): unknown custom data type with id " + to_string(dataTypeIdx));
						return;
					}
					MiniScript::dataTypes[dataTypeIdx]->copyVariable(to, from);
			}
			//
			if (from.isConstant() == true) to.setConstant();
		}

		/**
		 * Copy constructor
		 * @param variable variable to copy
		 */
		inline Variable(const Variable& variable) {
			if (variable.isReference() == true) {
				setReference(variable.ir.reference);
			} else {
				copyVariable(*this, variable);
			}
		}

		/**
		 * Move constructor
		 * @param variable variable to move from
		 */
		inline Variable(Variable&& variable):
			typeReferenceConstantBits(exchange(variable.typeReferenceConstantBits, static_cast<int>(MiniScript::TYPE_NULL))),
			valuePtr(exchange(variable.valuePtr, 0ll)),
			referenceCounter(exchange(variable.referenceCounter, 1)) {
			// TODO: improve me
			ir.initializer = variable.ir.initializer;
			variable.ir.initializer = nullptr;
		}

		/**
		 * Assignment operator
		 * @param variable variable to copy
		 * @return this variable
		 */
		inline Variable& operator=(const Variable& variable) {
			// set up new variable
			if (variable.isReference() == true) {
				// release current reference
				if (isReference() == true) {
					ir.reference->releaseReference();
					unsetReference();
				}
				//
				setType(TYPE_NULL);
				//
				setReference(variable.ir.reference);
			} else {
				setType(TYPE_NULL);
				//
				copyVariable(*this, variable);
			}
			//
			return *this;
		}

		/**
		 * Move operator
		 * @param variable variable to move from
		 * @return this variable
		 */
		inline Variable& operator=(Variable&& variable) {
			swap(typeReferenceConstantBits, variable.typeReferenceConstantBits);
			swap(valuePtr, variable.valuePtr);
			swap(ir, variable.ir);
			swap(referenceCounter, variable.referenceCounter);
			//
			return *this;
		}

		/**
		 * Constructor
		 */
		inline Variable() {
		}

		/**
		 * Destructor
		 */
		inline ~Variable() {
			if (isReference() == true) {
				ir.reference->releaseReference();
			}
			if (--referenceCounter == 0) {
				if (isReference() == true) unsetReference();
				setType(TYPE_NULL);
			}
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline Variable(bool value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline Variable(int64_t value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline Variable(float value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline Variable(const string& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline Variable(const vector<Variable*>& value) {
			setValue(value);
		}

		/**
		 * Constructor
		 * @param value value
		 */
		inline Variable(const unordered_map<string, Variable*>& value) {
			setValue(value);
		}

		/**
		 * @return type
		 */
		inline VariableType getType() const {
			return static_cast<VariableType>((isReference() == false?typeReferenceConstantBits:ir.reference->typeReferenceConstantBits) & TYPE_BITS_VALUE);
		}

		/**
		 * Set type
		 * @param newType new type
		 */
		inline void setType(VariableType newType) {
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
					delete static_cast<StringValue*>((void*)getValuePtrReference());
					delete getInitializerReference();
					getInitializerReference() = nullptr;
					break;
				case TYPE_PSEUDO_NUMBER: break;
				case TYPE_PSEUDO_MIXED: break;
				case TYPE_STRING:
				case TYPE_FUNCTION_ASSIGNMENT:
					delete static_cast<StringValue*>((void*)getValuePtrReference());
					break;
				case TYPE_BYTEARRAY:
					delete static_cast<vector<uint8_t>*>((void*)getValuePtrReference());
					break;
				case TYPE_ARRAY:
					for (auto arrayValue: getArrayValueReference()) arrayValue->releaseReference();
					delete static_cast<vector<Variable*>*>((void*)getValuePtrReference());
					delete getInitializerReference();
					getInitializerReference() = nullptr;
					break;
				case TYPE_MAP:
					for (const auto& [mapEntryName, mapEntryValue]: getMapValueReference()) mapEntryValue->releaseReference();
					delete static_cast<unordered_map<string, Variable*>*>((void*)getValuePtrReference());
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
					if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::dataTypes.size()) {
						_Console::println("ScriptVariable::setType(): unknown custom data type with id " + to_string(dataTypeIdx));
						return;
					}
					MiniScript::dataTypes[dataTypeIdx]->unsetVariableValue(*this);

			}
			this->getValuePtrReference() = 0LL;
			//
			if (isReference() == true) {
				ir.reference->typeReferenceConstantBits =
					static_cast<uint32_t>(newType) |
					((ir.reference->typeReferenceConstantBits & CONSTANT_BIT_VALUE) == CONSTANT_BIT_VALUE?CONSTANT_BIT_VALUE:0);
			} else {
				typeReferenceConstantBits =
					static_cast<uint32_t>(newType) |
					((typeReferenceConstantBits & CONSTANT_BIT_VALUE) == CONSTANT_BIT_VALUE?CONSTANT_BIT_VALUE:0);
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
					getValuePtrReference() = (uint64_t)(new StringValue());
					break;
				case TYPE_BYTEARRAY:
					getValuePtrReference() = (uint64_t)(new vector<uint8_t>());
					break;
				case TYPE_ARRAY:
					getValuePtrReference() = (uint64_t)(new vector<Variable*>());
					getInitializerReference() = new Initializer();
					break;
				case TYPE_MAP:
					getValuePtrReference() = (uint64_t)(new unordered_map<string, Variable*>());
					getInitializerReference() = new Initializer();
					break;
				case TYPE_SET:
					getValuePtrReference() = (uint64_t)(new unordered_set<string>());
					getInitializerReference() = new Initializer();
					break;
				case TYPE_FUNCTION_CALL:
					getValuePtrReference() = (uint64_t)(new StringValue());
					getInitializerReference() = new Initializer();
					break;
				default:
					// custom data type
					auto dataTypeIdx = static_cast<int>(this->getType()) - TYPE_PSEUDO_CUSTOM_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::dataTypes.size()) {
						_Console::println("ScriptVariable::setType(): unknown custom data type with id " + to_string(dataTypeIdx));
						return;
					}
					MiniScript::dataTypes[dataTypeIdx]->setVariableValue(*this);
			}
		}

		/**
		 * Return initializer
		 * @return initializer
		 */
		inline Initializer* getInitializer() const {
			return isReference() == true?ir.reference->ir.initializer:ir.initializer;
		}

		/**
		 * @return value pointer
		 */
		inline void* getValuePtr() const {
			return (void*)(isReference() == true?ir.reference->valuePtr:valuePtr);
		}

		/**
		 * Set value pointer
		 * @param valuePtr value pointer
		 */
		inline void setValuePtr(void* valuePtr) {
			if (isReference() == true) {
				ir.reference->valuePtr = (uint64_t)valuePtr;
			} else {
				this->valuePtr = (uint64_t)valuePtr;
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
						auto lowerCaseString = _StringTools::toLowerCase(getStringValueReference().getValue());
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
						const auto& stringValue = getStringValueReference().getValue();
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
						const auto& stringValue = getStringValueReference().getValue();
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
					value = getStringValueReference().getValue();
					return true;
				default:
					return false;
			}
			return false;
		}

		/**
		 * Get byte value from given variable
		 * @param miniScript mini script
		 * @param value value
		 * @param statement statement
		 * @return success
		 */
		inline bool getByteValue(MiniScript* miniScript, uint8_t& value, const Statement* statement = nullptr) const {
			int64_t intValue;
			if (getIntegerValue(intValue, false) == true && value >= 0 && value <= 255) {
				value = intValue;
				return true;
			} else {
				if (statement != nullptr) {
					_Console::println(miniScript->getStatementInformation(*statement) + ": expected byte integer value (0 <= value <= 255), but got " + getValueAsString());
				} else {
					_Console::println(miniScript->getScriptFileName() + ": expected byte integer value (0 <= value <= 255), but got " + getValueAsString());
				}
			}
			return false;
		}

		/**
		 * Get string value UTF8 position cache from given variable
		 * @return UTF8 position cache or nullptr if not available
		 */
		inline _UTF8CharacterIterator::UTF8PositionCache* getStringValueCache() {
			switch(getType()) {
				case TYPE_STRING:
				case TYPE_FUNCTION_ASSIGNMENT:
					return &getStringValueReference().getCache();
				default:
					return nullptr;
			}
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
			getStringValueReference().setValue(value);
		}

		/**
		 * Set array value from given value into variable
		 * @param value value
		 */
		inline void setValue(const vector<uint8_t>& value) {
			setType(TYPE_BYTEARRAY);
			auto& byteArrayValue = getByteArrayValueReference();
			for (const auto arrayEntry: value) {
				 byteArrayValue.push_back(arrayEntry);
			}
		}

		/**
		 * Set array value from given value into variable
		 * @param value value
		 */
		inline void setValue(const vector<Variable*>& value) {
			setType(TYPE_ARRAY);
			auto& arrayValue = getArrayValueReference();
			for (const auto arrayEntry: value) {
				arrayValue.push_back(new Variable(*arrayEntry));
			}
		}

		/**
		 * Set map value from given value into variable
		 * @param value value
		 */
		inline void setValue(const unordered_map<string, Variable*>& value) {
			setType(TYPE_MAP);
			auto& mapValue = getMapValueReference();
			for (const auto& [mapEntryName, mapEntryValue]: value) {
				mapValue[mapEntryName] = new Variable(*mapEntryValue);
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
			if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::dataTypes.size()) {
				_Console::println("ScriptVariable::setValue(): unknown custom data type with id " + to_string(dataTypeIdx));
				return;
			}
			MiniScript::dataTypes[dataTypeIdx]->setVariableValue(*this, value);
		}

		/**
		 * @return return const pointer to underlying byte vector or nullptr
		 */
		inline const vector<uint8_t>* getByteArrayPointer() const {
			if (getType() != TYPE_BYTEARRAY) return nullptr;
			auto& byteArrayValue = getByteArrayValueReference();
			return &byteArrayValue;
		}

		/**
		 * @return pointer to underlying byte vector or nullptr
		 */
		inline vector<uint8_t>* getByteArrayPointer() {
			if (getType() != TYPE_BYTEARRAY) return nullptr;
			auto& byteArrayValue = getByteArrayValueReference();
			return &byteArrayValue;
		}

		/**
		 * Get byte array size
		 * @return byte array size
		 */
		inline int64_t getByteArraySize() const {
			if (getType() != TYPE_BYTEARRAY) return 0;
			return getByteArrayValueReference().size();
		}

		/**
		 * Get entry from byte array with given index
		 * @param idx index
		 * @return entry from byte array with given index
		 */
		inline const uint8_t getByteArrayEntry(int64_t idx) const {
			if (getType() != TYPE_BYTEARRAY) return 0;
			const auto& byteArrayValue = getByteArrayValueReference();
			if (idx >= 0 && idx < byteArrayValue.size()) return byteArrayValue[idx];
			return 0;
		}

		/**
		 * Set entry in byte array with given index
		 * @param idx index
		 */
		inline void setByteArrayEntry(int64_t idx, uint8_t value) {
			setType(TYPE_BYTEARRAY);
			if (idx < 0) return;
			auto& byteArrayValue = getByteArrayValueReference();
			while (byteArrayValue.size() <= idx) pushByteArrayEntry(0);
			byteArrayValue[idx] = value;
		}

		/**
		 * Push entry to byte array
		 * @param value value
		 */
		inline void pushByteArrayEntry(uint8_t value) {
			setType(TYPE_BYTEARRAY);
			getByteArrayValueReference().push_back(value);
		}

		/**
		 * Remove byte array entry at given index
		 * @param idx index
		 */
		inline void removeByteArrayEntry(int64_t idx) {
			if (getType() != TYPE_BYTEARRAY) return;
			auto& byteArrayValue = getByteArrayValueReference();
			if (idx >= 0 && idx < byteArrayValue.size()) {
				byteArrayValue.erase(byteArrayValue.begin() + idx);
			}
			return;
		}

		/**
		 * Clear byte array
		 */
		inline void clearByteArray() {
			if (getType() != TYPE_BYTEARRAY) return;
			auto& byteArrayValue = getByteArrayValueReference();
			byteArrayValue.clear();
			return;
		}

		/**
		 * @return return const pointer to underlying vector or nullptr
		 */
		inline const vector<Variable*>* getArrayPointer() const {
			if (getType() != TYPE_ARRAY) return nullptr;
			auto& arrayValue = getArrayValueReference();
			return &arrayValue;
		}

		/**
		 * @return pointer to underlying vector or nullptr
		 */
		inline vector<Variable*>* getArrayPointer() {
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
		inline const Variable getArrayEntry(int64_t idx) const {
			if (getType() != TYPE_ARRAY) return Variable();
			const auto& arrayValue = getArrayValueReference();
			if (idx >= 0 && idx < arrayValue.size()) return *arrayValue[idx];
			return Variable();
		}

		/**
		 * Set entry in array with given index
		 * @param idx index
		 */
		inline void setArrayEntry(int64_t idx, const Variable& value) {
			setType(TYPE_ARRAY);
			if (idx < 0) return;
			auto& arrayValue = getArrayValueReference();
			while (arrayValue.size() <= idx) pushArrayEntry(Variable());
			arrayValue[idx]->releaseReference();
			arrayValue[idx] = new Variable(value);
		}

		/**
		 * Push entry to array
		 * @param value value
		 */
		inline void pushArrayEntry(const Variable& value) {
			setType(TYPE_ARRAY);
			getArrayValueReference().push_back(new Variable(value));
		}

		/**
		 * Remove array entry at given index
		 * @param idx index
		 */
		inline void removeArrayEntry(int64_t idx) {
			if (getType() != TYPE_ARRAY) return;
			auto& arrayValue = getArrayValueReference();
			if (idx >= 0 && idx < arrayValue.size()) {
				arrayValue[idx]->releaseReference();
				arrayValue.erase(arrayValue.begin() + idx);
			}
			return;
		}

		/**
		 * Clear array
		 */
		inline void clearArray() {
			if (getType() != TYPE_ARRAY) return;
			auto& arrayValue = getArrayValueReference();
			for (auto i = 0; i < arrayValue.size(); i++) arrayValue[i]->releaseReference();
			arrayValue.clear();
		}

		/**
		 * @return return const pointer to underlying unordered_map or nullptr
		 */
		inline const unordered_map<string, Variable*>* getMapPointer() const {
			if (getType() != TYPE_MAP) return nullptr;
			auto& mapValue = getMapValueReference();
			return &mapValue;
		}

		/**
		 * @return pointer to underlying unordered_map or nullptr
		 */
		inline unordered_map<string, Variable*>* getMapPointer() {
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
		inline const Variable getMapEntry(const string& key) const {
			if (getType() != TYPE_MAP) return Variable();
			const auto& mapValue = getMapValueReference();
			auto it = mapValue.find(key);
			if (it != mapValue.end()) return *it->second;
			return Variable();
		}

		/**
		 * Set entry in map with given key
		 * @param key key
		 * @param value value
		 */
		inline void setMapEntry(const string& key, const Variable& value) {
			setType(TYPE_MAP);
			auto mapValueIt = getMapValueReference().find(key);
			if (mapValueIt != getMapValueReference().end()) mapValueIt->second->releaseReference();
			getMapValueReference()[key] = new Variable(value);
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
		inline const vector<Variable*> getMapValues() const {
			vector<Variable*> values;
			if (getType() != TYPE_MAP) return values;
			const auto& mapValue = getMapValueReference();
			for (const auto& [mapEntryKey, mapEntryValue]: mapValue) {
				values.push_back(mapEntryValue);
			}
			return values;
		}

		/**
		 * Clear array
		 */
		inline void clearMap() {
			if (getType() != TYPE_MAP) return;
			auto& mapValue = getMapValueReference();
			for (const auto& [mapEntryName, mapEntryValue]: mapValue) {
				mapEntryValue->releaseReference();
			}
			mapValue.clear();
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
		 * Clear set
		 */
		inline void clearSet() {
			if (getType() != TYPE_SET) return;
			auto& setValue = getSetValueReference();
			setValue.clear();
		}

		/**
		 * Set array/map values initializer function call statement
		 * @param miniScript miniscript instance
		 * @param statement statement
		 * @param initializerStatement initializer statement
		 */
		void setFunctionCallStatement(const string& initializerStatement, MiniScript* miniScript, const Statement& statement);

		/**
		 * Set function assignment from given value into variable
		 * @param value value
		 */
		inline void setFunctionAssignment(const string& value) {
			setType(TYPE_FUNCTION_ASSIGNMENT);
			getStringValueReference().setValue(value);
		}

		/**
		 * Set implicit typed value given by value string
		 * @param value value
		 * @param miniScript mini script
		 * @param statement statement
		 */
		inline void setImplicitTypedValue(const string& value, MiniScript* miniScript, const Statement& statement) {
			setImplicitTypedValueFromStringView(string_view(value), miniScript, statement);
		}

		/**
		 * Set implicit typed value given by value string
		 * @param value value
		 * @param miniScript mini script
		 * @param statement statement
		 */
		inline void setImplicitTypedValueFromStringView(const string_view& value, MiniScript* miniScript, const Statement& statement) {
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
			} else
			// variable
			if (viewIsVariableAccess(value) == true) {
				setFunctionCallStatement("getVariable(\"" + string(value) + "\")", miniScript, statement);
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
		inline static bool isExpectedType(VariableType type, VariableType expectedType) {
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
		 * Returns given variable type as string
		 * @param type type
		 * @return variable type as string
		 */
		inline static const string& getTypeAsString(VariableType type) {
			switch(type) {
				case TYPE_NULL: return TYPENAME_NULL;
				case TYPE_BOOLEAN: return TYPENAME_BOOLEAN;
				case TYPE_INTEGER: return TYPENAME_INTEGER;
				case TYPE_FLOAT: return TYPENAME_FLOAT;
				case TYPE_FUNCTION_CALL: return TYPENAME_NONE;
				case TYPE_FUNCTION_ASSIGNMENT: return TYPENAME_FUNCTION;
				case TYPE_PSEUDO_NUMBER: return TYPENAME_NUMBER;
				case TYPE_PSEUDO_MIXED: return TYPENAME_MIXED;
				case TYPE_STRING: return TYPENAME_STRING;
				case TYPE_BYTEARRAY: return TYPENAME_BYTEARRAY;
				case TYPE_ARRAY: return TYPENAME_ARRAY;
				case TYPE_MAP: return TYPENAME_MAP;
				case TYPE_SET: return TYPENAME_SET;
				default:
					// custom data types
					auto dataTypeIdx = static_cast<int>(type) - TYPE_PSEUDO_CUSTOM_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::dataTypes.size()) {
						return TYPENAME_NONE;
					}
					return MiniScript::dataTypes[dataTypeIdx]->getTypeAsString();
			}
			return TYPENAME_NONE;
		}

		/**
		 * @return this variable type as string
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
		inline static const string getReturnTypeAsString(VariableType type, bool nullable) {
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
		 * @return string representation of variable type
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
		 * Print string representation of variable
		 * @param formatted formatted
		 * @param jsonCompatible json compatible
		 * @param depth recursion depth
		 * @return string representation of variable type
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
					result+= "{" + getStringValueReference().getValue() + "}";
					break;
				case TYPE_FUNCTION_ASSIGNMENT:
					result+= "() -> " + getStringValueReference().getValue();
					break;
				case TYPE_PSEUDO_NUMBER:
					result+= "Number";
					break;
				case TYPE_PSEUDO_MIXED:
					result+= "Mixed";
					break;
				case TYPE_STRING:
					result+= getStringValueReference().getValue();
					break;
				case TYPE_BYTEARRAY:
					{
						const auto& byteArrayValue = getByteArrayValueReference();
						vector<string> values;
						for (const auto arrayEntry: byteArrayValue) {
							values.push_back(to_string(arrayEntry));
						}
						auto i = 0;
						for (const auto& valueString: values) {
							result+= valueString;
							if (i != values.size() - 1) result+= ", ";
							i++;
						}
						result = "ByteArray([" + result + "], size: " + to_string(byteArrayValue.size()) + ", capacity: " + to_string(byteArrayValue.capacity()) + ")";
						break;
					}
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
					auto dataTypeIdx = static_cast<int>(getType()) - TYPE_PSEUDO_CUSTOM_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MiniScript::dataTypes.size()) {
						_Console::println("ScriptVariable::getValueAsString(): unknown custom data type with id " + to_string(dataTypeIdx));
						return result;
					}
					return MiniScript::dataTypes[dataTypeIdx]->getValueAsString(*this);

			}
			return result;
		}
	};

	/**
	 * State Machine State
	 */
	class StateMachineState {
	public:
		// forbid class copy
		FORBID_CLASS_COPY(StateMachineState)

		/**
		 * Constructor
		 */
		StateMachineState() {}

		/**
		 * Destructor
		 */
		virtual ~StateMachineState() {}

		/**
		 * @return name
		 */
		virtual const string getName() = 0;

		/**
		 * @return id
		 */
		virtual int getId() = 0;

		/**
		 * Execute state machine state
		 */
		virtual void execute() = 0;
	};

	/**
	 * Method
	 */
	class Method {
	public:
		struct ArgumentType {
			VariableType type;
			string name;
			bool optional;
			bool reference;
			bool nullable;
		};

		// forbid class copy
		FORBID_CLASS_COPY(Method)

		/**
		 * Constructor
		 * @param argumentTypes argument types
		 * @param returnValueType return value type
		 * @param returnValueNullable true if return value can also be a null value
		 */
		Method(
			const vector<ArgumentType>& argumentTypes = {},
			VariableType returnValueType = VariableType::TYPE_NULL,
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
		virtual ~Method() {}

		/**
		 * @return method name
		 */
		virtual const string getMethodName() = 0;

		/**
		 * Execute method
		 * @param arguments argument values
		 * @param returnValue return value
		 * @param statement statement
		 */
		virtual void executeMethod(span<Variable>& arguments, Variable& returnValue, const Statement& statement) = 0;

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
					result+= "$" + argumentType.name + ": " + (argumentType.nullable == true?"?":"") + Variable::getTypeAsString(argumentType.type);
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
		const VariableType& getReturnValueType() const {
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
		virtual Operator getOperator() const {
			return OPERATOR_NONE;
		}

		/**
		 * @return context function
		 */
		virtual const vector<string>& getContextFunctions() {
			return CONTEXTFUNCTIONS_ALL;
		}

	protected:
		MINISCRIPT_STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTIONS_ALL;

	private:
		vector<ArgumentType> argumentTypes;
		VariableType returnValueType;
		bool returnValueNullable;
	};

	struct SyntaxTreeNode {
		enum Type {
			SCRIPTSYNTAXTREENODE_NONE,
			SCRIPTSYNTAXTREENODE_LITERAL,
			SCRIPTSYNTAXTREENODE_EXECUTE_METHOD,
			SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION
		};
		SyntaxTreeNode():
			type(SCRIPTSYNTAXTREENODE_NONE),
			value(Variable()),
			pointer(0ll),
			arguments({})
		{}
		SyntaxTreeNode(
			Type type,
			const Variable& value,
			Method* method,
			const vector<SyntaxTreeNode>& arguments
		):
			type(type),
			value(value),
			pointer((uint64_t)method),
			arguments(arguments)
		{}
		SyntaxTreeNode(
			Type type,
			const Variable& value,
			uint64_t functionIdx,
			const vector<SyntaxTreeNode>& arguments
		):
			type(type),
			value(value),
			pointer(functionIdx),
			arguments(arguments)
		{}
		inline Method* getMethod() const {
			return (Method*)pointer;
		}
		inline void setMethod(Method* method) {
			pointer = (uint64_t)method;
		}
		inline uint64_t getFunctionScriptIdx() const {
			return pointer;
		}
		inline void setFunctionScriptIdx(uint64_t scriptIdx) {
			pointer = scriptIdx;
		}
		Type type;
		Variable value;
		uint64_t pointer;
		vector<SyntaxTreeNode> arguments;
	};

	/**
	 * Script
	 */
	struct Script {
		struct FunctionArgument {
			FunctionArgument(
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
			Statement conditionStatement,
			SyntaxTreeNode conditionSyntaxTree,
			// applies only for on-enabled
			const string& name,
			bool emitCondition,
			const vector<Statement>& statements,
			const vector<SyntaxTreeNode>& syntaxTree,
			// applies only for functions
			bool callableFunction,
			const vector<FunctionArgument>& functionArguments
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
			callableFunction(callableFunction),
			functionArguments(functionArguments)
		{}
		ScriptType scriptType;
		int line;
		string condition;
		string executableCondition;
		Statement conditionStatement;
		SyntaxTreeNode conditionSyntaxTree;
		string name;
		bool emitCondition;
		vector<Statement> statements;
		vector<SyntaxTreeNode> syntaxTree;
		bool callableFunction;
		vector<FunctionArgument> functionArguments;
	};

	static constexpr int SCRIPTIDX_NONE { -1 };
	static constexpr int LINE_NONE { -1 };
	static constexpr int STATEMENTIDX_NONE { -1 };
	static constexpr int STATEMENTIDX_FIRST { 0 };
	static constexpr int ARGUMENTIDX_NONE { -1 };

	MINISCRIPT_STATIC_DLL_IMPEXT static const string METHOD_SCRIPTCALL;
	MINISCRIPT_STATIC_DLL_IMPEXT static const string METHOD_ENABLENAMEDCONDITION;
	MINISCRIPT_STATIC_DLL_IMPEXT static const string METHOD_DISABLENAMEDCONDITION;

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
	inline const string getArgumentsAsString(const vector<SyntaxTreeNode>& arguments) {
		string argumentsString;
		for (const auto& argument: arguments) {
			switch (argument.type) {
				case SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
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
				case SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
				case SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
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
	static constexpr int ARRAYIDX_FIRST { 0 };
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
		StateMachineState* lastStateMachineState { nullptr };
		bool running { false };
		int scriptIdx { SCRIPTIDX_NONE };
		int statementIdx { STATEMENTIDX_NONE };
		int gotoStatementIdx { STATEMENTIDX_NONE };
		int64_t timeWaitStarted { TIME_NONE };
		int64_t timeWaitTime { TIME_NONE };
		string id;
		unordered_map<string, Variable*> variables;
		unordered_map<int, int64_t> forTimeStarted;
		stack<bool> conditionStack;
		stack<EndType> endTypeStack;
		// applies for functions only
		Variable returnValue;
	};

	bool native;
	_Context* context { nullptr };
	_Library* library { nullptr };
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
	void gotoStatementGoto(const Statement& statement) {
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
	 * Set native functions
	 * @param nativeFunctions native functions
	 */
	inline void setNativeFunctions(const unordered_map<string, int>& nativeFunctions) {
		this->functions = nativeFunctions;
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
	inline void resetScriptExecutationState(int scriptIdx, StateMachineStateId stateMachineState) {
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
		auto& scriptState = getScriptState();
		for (const auto& [variableName, variable]: scriptState.variables) delete variable;
		scriptState.variables.clear();
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

	/***
	 * Create inline/lamda function for given variable
	 * @param variable variable
	 * @param arguments arguments
	 * @param functionScriptCode function script code
	 * @param populateThis populate this variable, which applies to inline member function of maps/objects
	 * @param statement statement
	 */
	void createLamdaFunction(Variable& variable, const vector<string_view>& arguments, const string_view& functionScriptCode, bool populateThis, const Statement& statement);

	/**
	 * Initialize array by initializer string
	 * @param initializerString initializer string
	 * @param miniScript mini script
	 * @param statement statement
	 * @return initialized variable
	 */
	static const Variable initializeArray(const string_view& initializerString, MiniScript* miniScript, const Statement& statement);

	/**
	 * Initialize map/set by initializer string
	 * @param initializerString initializer string
	 * @param miniScript mini script
	 * @param statement statement
	 * @return initialized variable
	 */
	static const Variable initializeMapSet(const string_view& initializerString, MiniScript* miniScript, const Statement& statement);

private:
	static constexpr bool VERBOSE { false };

	//
	MINISCRIPT_STATIC_DLL_IMPEXT static const string OPERATOR_CHARS;
	MINISCRIPT_STATIC_DLL_IMPEXT static vector<DataType*> dataTypes;

	// TODO: maybe we need a better naming for this
	// functions defined by script itself
	unordered_map<string, int> functions;
	// registered methods
	unordered_map<string, Method*> methods;
	// registered state machine states
	unordered_map<int, StateMachineState*> stateMachineStates;
	// operators
	unordered_map<uint8_t, Method*> operators;
	//
	string scriptPathName;
	string scriptFileName;
	//
	bool scriptValid { false };

	/**
	 * Parse script code into this MiniScript instance
	 * @param scriptCode script code
	 * @return success
	 */
	bool parseScriptInternal(const string& scriptCode);


	/**
	 * Execute next statement
	 */
	void executeNextStatement();

	/**
	 * Get next statement from script code
	 * @param scriptCode script code
	 * @param i character index
	 * @param line line
	 * @return next statement
	 */
	const string getNextStatement(const string& scriptCode, int& i, int& line);

	/**
	 * Parse a statement
	 * @param executableStatement executable statement
	 * @param methodName method name
	 * @param arguments arguments
	 * @param statement statment
	 * @param accessObjectMember generated access object member statement
	 * @return success
	 */
	bool parseStatement(const string_view& executableStatement, string_view& methodName, vector<string_view>& arguments, const Statement& statement, string& accessObjectMemberStatement);

	/**
	 * Execute a statement
	 * @param syntaxTree syntax tree
	 * @param statement statement
	 * @return return value as variable
	 */
	Variable executeStatement(const SyntaxTreeNode& syntaxTree, const Statement& statement);

	/**
	 * Create statement syntax tree
	 * @param methodName method name
	 * @param arguments arguments
	 * @param statement statement
	 * @param syntaxTree syntax tree
	 * @return success
	 */
	bool createStatementSyntaxTree(const string_view& methodName, const vector<string_view>& arguments, const Statement& statement, SyntaxTreeNode& syntaxTree);

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
	bool validateCallable(const SyntaxTreeNode& syntaxTreeNode, const Statement& statement);

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
	bool validateContextFunctions(const SyntaxTreeNode& syntaxTreeNode, vector<string>& functionStack, const Statement& statement);

	/**
	 * Returns if char is operator char
	 * @param c char to test
	 * @return if char is operator char
	 */
	static inline const bool isOperatorChar(char c) {
		return OPERATOR_CHARS.find(c) != string::npos;
	}

	/**
	 * Do statement pre processing, 1) replace operators with corresponding methods
	 * @param processedStatement statement that is currently being processed
	 * @param statement statement
	 */
	const string doStatementPreProcessing(const string& processedStatement, const Statement& statement);

	/**
	 * Returns if statement has a object member access
	 * @param executableStatement executable statement
	 * @param object object
	 * @param method method
	 * @param statement statement
	 * @return statement has a object member access
	 */
	bool getObjectMemberAccess(const string_view& executableStatement, string_view& object, string_view& method, const Statement& statement);

	/**
	 * Get access operator left and right indices
	 * @param variableStatement variable statement
	 * @param callerMethod caller method
	 * @param accessOperatorLeftIdx access operator left idx
	 * @param accessOperatorRightIdx access operator right idx
	 * @param statement statement
	 * @param startIdx startIdx
	 */
	bool getVariableAccessOperatorLeftRightIndices(const string& variableStatement, const string& callerMethod, string::size_type& accessOperatorLeftIdx, string::size_type& accessOperatorRightIdx, const Statement* statement = nullptr, int startIdx = 0);

	/**
	 * Evaluate access
	 * @param variableStatement variable statement
	 * @param callerMethod caller method
	 * @param arrayAccessOperatorLeftIdx array access operator left idx
	 * @param arrayAccessOperatorRightIdx array access operator right idx
	 * @param arrayIdx array index
	 * @param key map key
	 * @param statement statement
	 */
	bool evaluateAccess(const string& variableStatement, const string& callerMethod, string::size_type& arrayAccessOperatorLeftIdx, string::size_type& arrayAccessOperatorRightIdx, int64_t& arrayIdx, string& key, const Statement* statement = nullptr);

	/**
	 * Returns pointer of variable with given name or nullptr
	 * @param variablePtr pointer to variable
	 * @param variableStatement variable statement
	 * @param callerMethod caller method
	 * @param parentVariable parent variable
	 * @param arrayIdx array index whereas there is ARRAYIDX_ADD for [] or ARRAYIDX_NONE for no array access
	 * @param key key
	 * @param setAccessBool set access bool which returns one of SETACCESSBOOL_NONE, *_TRUE, *_FALSE
	 * @param statement optional statement the variable is read in
	 * @param expectVariable expect variable which controls verbosity
	 * @return pointer to variable
	 */
	Variable* evaluateVariableAccessIntern(Variable* variablePtr, const string& variableStatement, const string& callerMethod, Variable*& parentVariable, int64_t& arrayIdx, string& key, int& setAccessBool, const Statement* statement = nullptr, bool expectVariable = true);

	/**
	 * Returns pointer of variable with given name or nullptr
	 * @param variableStatement variable statement
	 * @param callerMethod caller method
	 * @param variableName variable name
	 * @param parentVariable parent variable
	 * @param arrayIdx array index whereas there is ARRAYIDX_ADD for [] or ARRAYIDX_NONE for no array access
	 * @param key key
	 * @param setAccessBool set access bool which returns one of SETACCESSBOOL_NONE, *_TRUE, *_FALSE
	 * @param statement optional statement the variable is read in
	 * @param expectVariable expect variable which controls verbosity
	 * @param global use global context instead of current context
	 * @return pointer to variable
	 */
	Variable* getVariableIntern(const string& variableStatement, const string& callerMethod, string& variableName, Variable*& parentVariable, int64_t& arrayIdx, string& key, int& setAccessBool, const Statement* statement = nullptr, bool expectVariable = true, bool global = false);

	/**
	 * Set variable internal
	 * @param variableStatement variable statement
	 * @param parentVariable parent variable
	 * @param variablePtr variable pointer
	 * @param arrayIdx array index
	 * @param key key
	 * @param variable variable
	 * @param statement optional statement the variable is written in
	 * @param createReference optional flag for creating variable references
	 */
	void setVariableInternal(const string& variableStatement, Variable* parentVariable, Variable* variablePtr, int64_t arrayIdx, const string& key, const Variable& variable, const Statement* statement = nullptr, bool createReference = false);

	/**
	 * Evaluate given statement without executing preprocessor run
	 * @param statement statement
	 * @param executableStatement executable statement
	 * @param returnValue return value
	 * @param pushOwnScriptState push own script state
	 * @return success
	 */
	bool evaluateInternal(const string& statement, const string& executableStatement, Variable& returnValue, bool pushOwnScriptState = true);

	/**
	  * Initialize variable
	  * @param variable variable
	  * @return initialized variable
	  */
	const Variable initializeVariable(const Variable& variable);

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
	 * Returns if a given string is a inline/lambda function
	 * @param candidate candidate
	 * @return if candidate is a inline/lambda function
	 */
	inline static bool viewIsLamdaFunction(const string_view& candidate) {
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
		return true;
	}

	/**
	 * Returns if a given string is a inline/lambda function
	 * @param candidate candidate
	 * @param arguments arguments
	 * @param functionScriptCode function script code
	 * @return if candidate is a inline/lambda function
	 */
	inline static bool viewIsLamdaFunction(const string_view& candidate, vector<string_view>& arguments, string_view& functionScriptCode) {
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
		if (candidate.size() < 2) return false;
		auto i = 0;
		if (candidate[i++] != '$') return false;
		if (candidate[i] == '$') i++;
		auto squareBracketCount = 0;
		for (; i < candidate.size(); i++) {
			auto c = candidate[i];
			if (c == '[') {
				squareBracketCount++;
			} else
			if (c == ']') {
				squareBracketCount--;
			} else
			if (squareBracketCount == 0 && _Character::isAlphaNumeric(c) == false && c != '_' && c != '.' && c != ':') {
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
	 * Set variable recursively to be a constant
	 * @param variable variable
	 */
	static void setConstant(Variable& variable);

	/**
	 * @return context
	 */
	inline _Context* getContext() {
		return context;
	}

	/**
	 * Set context
	 * @param context context
	 */
	inline void setContext(_Context* context) {
		this->context = context;
	}

	/**
	 * @return library
	 */
	inline _Library* getLibrary() {
		return library;
	}

	/**
	 * Set library
	 * @param library library
	 */
	inline void setLibrary(_Library* library) {
		this->library = library;
	}

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
	inline static const vector<DataType*>& getDataTypes() {
		return dataTypes;
	}

	/**
	 * Returns data type by class name or nullptr
	 * @param className class name
	 * @return data type
	 */
	inline static DataType* getDataTypeByClassName(const string& className) {
		for (const auto dataType: dataTypes) {
			if (dataType->getTypeAsString() == className) return dataType;
		}
		return nullptr;
	}

	/**
	 * Register data type
	 * @param dataType data type
	 */
	static void registerDataType(DataType* dataType);

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
	 * @return base class header
	 */
	virtual const string getBaseClassHeader();

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
	 * @return if this script was compiled to C++ and is executed natively
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
	 * @return script path name
	 */
	inline const string& getScriptPathName() {
		return scriptPathName;
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
	 * @return root script state
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
	 * @return math methods
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
		return methods.find(methodName) != methods.end();
	}

	/**
	 * Returns if function with given name does exist
	 * @param functionName function name
	 * @return function exists
	 */
	inline bool hasFunction(const string& functionName) {
		return functions.find(functionName) != functions.end();
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
	 * Return statement information
	 * @param statement statement
	 * @return statement information
	 */
	inline const string getStatementInformation(const Statement& statement) {
		return scriptFileName + ":" + to_string(statement.line) +  ": " + statement.statement;
	}

	/**
	 * Get argument information
	 * @param methodName method name
	 * @return argument information
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
	 * @param operator_ operator
	 * @return operator as string
	 */
	inline static string getOperatorAsString(Operator operator_) {
		switch(operator_) {
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
	inline static bool hasType(const span<Variable>& arguments, VariableType type) {
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
	inline static bool getBooleanValue(const span<Variable>& arguments, int idx, bool& value, bool optional = false) {
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
	inline static bool getIntegerValue(const span<Variable>& arguments, int idx, int64_t& value, bool optional = false) {
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
	inline static bool getFloatValue(const span<Variable>& arguments, int idx, float& value, bool optional = false) {
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
	inline static bool getStringValue(const span<Variable>& arguments, int idx, string& value, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		return argument.getStringValue(value, optional);
	}

	/**
	 * Register state machine state
	 * @param state state
	 */
	void registerStateMachineState(StateMachineState* state);

	/**
	 * Register method
	 * @param method method
	 */
	void registerMethod(Method* method);

	/**
	 * Returns if a given string is a variable name
	 * @param candidate candidate
	 * @param statement statement
	 * @return if string is a variable name
	 */
	inline bool isVariableAccess(const string& candidate, const Statement* statement = nullptr) {
		if (candidate.size() < 2) {
			_Console::println((statement != nullptr?getStatementInformation(*statement):scriptFileName) + ": variable: " + candidate + ": empty variable statement");
			return false;
		}
		auto i = 0;
		if (candidate[i++] != '$') {
			_Console::println((statement != nullptr?getStatementInformation(*statement):scriptFileName) + ": variable: " + candidate + ": variable statement must begin with an $");
			return false;
		}
		if (candidate[i] == '$') i++;
		//
		auto squareBracketCount = 0;
		for (; i < candidate.size(); i++) {
			auto c = candidate[i];
			if (c == '[') {
				squareBracketCount++;
			} else
			if (c == ']') {
				squareBracketCount--;
			} else
			if (squareBracketCount == 0 && _Character::isAlphaNumeric(c) == false && c != '_' && c != '.' && c != ':') {
				_Console::println((statement != nullptr?getStatementInformation(*statement):scriptFileName) + ": variable: " + candidate + ": invalid character in variable statement: '" + c + "'");
				return false;
			}
		}
		if (candidate.size() == 2 && string_view(candidate) == string_view("$$", 2)) {
			_Console::println((statement != nullptr?getStatementInformation(*statement):scriptFileName) + ": variable: " + candidate + ": variable statement must not be $$");
			return false;
		}
		if (candidate.size() == 7 && string_view(candidate) == string_view("$GLOBAL", 7)) {
			_Console::println((statement != nullptr?getStatementInformation(*statement):scriptFileName) + ": variable: " + candidate + ": variable statement must not be $GLOBAL");
			return false;
		}
		return true;
	}

	/**
	 * Returns if variable with given name exists
	 * @param variableStatement variable statement
	 * @param statement optional statement the variable is read in
	 * @return variable exists
	 */
	inline bool hasVariable(const string& variableStatement, const Statement* statement = nullptr) {
		//
		string variableName;
		// global accessor
		string globalVariableStatement;
		if (_StringTools::viewStartsWith(string_view(variableStatement), string_view("$$.", 3)) == true) {
			globalVariableStatement = "$" + _StringTools::substring(variableStatement, 3);
		} else
		if (_StringTools::viewStartsWith(string_view(variableStatement), string_view("$GLOBAL.", 8)) == true) {
			globalVariableStatement = "$" + _StringTools::substring(variableStatement, 8);
		}
		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		auto variablePtr = getVariableIntern(globalVariableStatement.empty() == true?variableStatement:globalVariableStatement, __FUNCTION__, variableName, parentVariable, arrayIdx, key, setAccessBool, statement, false, globalVariableStatement.empty() == false);
		// set '.' operator
		if (setAccessBool != SETACCESSBOOL_NONE) {
			return true;
		} else
		// we have a pointer to a ordinary variable
		if (variablePtr != nullptr) {
			return true;
		} else {
			// special case for accessing byte array entries at given array index
			if (parentVariable != nullptr && parentVariable->getType() == TYPE_BYTEARRAY && arrayIdx >= ARRAYIDX_FIRST) {
				return true;
			} else {
				// nothing to return
				return false;
			}
		}
	}

	/**
	 * Returns variable with given name
	 * @param variableStatement variable statement
	 * @param statement optional statement the variable is read in
	 * @param createReference optional flag for creating variable references
	 * @return variable
	 */
	inline const Variable getVariable(const string& variableStatement, const Statement* statement = nullptr, bool createReference = false) {
		//
		if (isVariableAccess(variableStatement, statement) == false) return Variable();
		//
		string variableName;
		// global accessor
		string globalVariableStatement;
		if (_StringTools::viewStartsWith(string_view(variableStatement), string_view("$$.", 3)) == true) {
			globalVariableStatement = "$" + _StringTools::substring(variableStatement, 3);
		} else
		if (_StringTools::viewStartsWith(string_view(variableStatement), string_view("$GLOBAL.", 8)) == true) {
			globalVariableStatement = "$" + _StringTools::substring(variableStatement, 8);
		}

		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		auto variablePtr = getVariableIntern(globalVariableStatement.empty() == true?variableStatement:globalVariableStatement, __FUNCTION__, variableName, parentVariable, arrayIdx, key, setAccessBool, statement, true, globalVariableStatement.empty() == false);
		// set '.' operator
		if (setAccessBool != SETACCESSBOOL_NONE) {
			return Variable(setAccessBool == SETACCESSBOOL_TRUE);
		} else
		// we have a pointer to a ordinary variable
		if (variablePtr != nullptr) {
			// if we return any variable we can safely remove the constness, a reference can of course keep its constness
			auto variable = createReference == false?*variablePtr:Variable::createReferenceVariable(variablePtr);
			variable.unsetConstant();
			return variable;
		} else {
			// special case for accessing byte array entries at given array index
			if (parentVariable != nullptr && parentVariable->getType() == TYPE_BYTEARRAY && arrayIdx >= ARRAYIDX_FIRST) {
				return Variable(static_cast<int64_t>(parentVariable->getByteArrayEntry(arrayIdx)));
			} else {
				// nothing to return
				return Variable();
			}
		}
	}

	/**
	 * Returns variable with given name
	 * @param variablePtr variable pointer
	 * @param variableStatement variable statement
	 * @param statement optional statement the variable is read in
	 * @param createReference optional flag for creating variable references
	 * @return variable
	 */
	inline const Variable getVariable(Variable* variablePtr, const string& variableStatement, const Statement* statement = nullptr, bool createReference = false) {
		//
		if (isVariableAccess(variableStatement, statement) == false) return Variable();
		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		variablePtr = evaluateVariableAccessIntern(variablePtr, variableStatement, __FUNCTION__, parentVariable, arrayIdx, key, setAccessBool, statement, true);
		// set '.' operator
		if (setAccessBool != SETACCESSBOOL_NONE) {
			return Variable(setAccessBool == SETACCESSBOOL_TRUE);
		} else
		// we have a pointer to a ordinary variable
		if (variablePtr != nullptr) {
			// if we return any variable we can safely remove the constness, a reference can of course keep its constness
			auto variable = createReference == false?*variablePtr:Variable::createReferenceVariable(variablePtr);
			variable.unsetConstant();
			return variable;
		} else {
			// special case for accessing byte array entries at given array index
			if (parentVariable != nullptr && parentVariable->getType() == TYPE_BYTEARRAY && arrayIdx >= ARRAYIDX_FIRST) {
				return Variable(static_cast<int64_t>(parentVariable->getByteArrayEntry(arrayIdx)));
			} else {
				// nothing to return
				return Variable();
			}
		}
	}

	/**
	 * Set constant
	 * @param variableStatement variable statement
	 * @param variable variable
	 */
	inline void setConstant(const string& variableStatement, const Variable& variable) {
		auto constVariable = variable;
		setConstant(constVariable);
		setVariable(variableStatement, constVariable);
	}

	/**
	 * Set variable
	 * @param variableStatement variable statement
	 * @param variable variable
	 * @param statement optional statement the variable is written in
	 * @param createReference optional flag for creating variable references
	 */
	inline void setVariable(const string& variableStatement, const Variable& variable, const Statement* statement = nullptr, bool createReference = false) {
		//
		if (isVariableAccess(variableStatement, statement) == false) return;
		//
		string variableName;
		// global accessor
		string globalVariableStatement;
		if (_StringTools::viewStartsWith(string_view(variableStatement), string_view("$$.", 3)) == true) {
			globalVariableStatement = "$" + _StringTools::substring(variableStatement, 3);
		} else
		if (_StringTools::viewStartsWith(string_view(variableStatement), string_view("$GLOBAL.", 8)) == true) {
			globalVariableStatement = "$" + _StringTools::substring(variableStatement, 8);
		}

		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		auto variablePtr = getVariableIntern(globalVariableStatement.empty() == true?variableStatement:globalVariableStatement, __FUNCTION__, variableName, parentVariable, arrayIdx, key, setAccessBool, statement, false, globalVariableStatement.empty() == false);

		// set variable if not yet done
		if (variablePtr == nullptr && parentVariable == nullptr) {
			// default
			auto& scriptState = globalVariableStatement.empty() == true?getScriptState():getRootScriptState();
			auto variableIt = scriptState.variables.find(globalVariableStatement.empty() == true?variableStatement:globalVariableStatement);
			if (variableIt != scriptState.variables.end()) {
				auto& existingVariable = variableIt->second;
				if (existingVariable->isConstant() == false) {
					// if we set a variable in variable scope that did exist before, we can safely remove the constness
					*existingVariable = variable;
				} else {
					_Console::println(getStatementInformation(*statement) + ": constant: " + variableStatement + ": Assignment of constant is not allowed");
				}
				return;
			} else {
				// if we set a variable in variable scope that did not exist before, we keep things as they are regarding constness
				scriptState.variables[globalVariableStatement.empty() == true?variableStatement:globalVariableStatement] =
					createReference == false?Variable::createNonReferenceVariablePointer(&variable):Variable::createReferenceVariablePointer(&variable);
			}
		} else {
			setVariableInternal(variableStatement, parentVariable, variablePtr, arrayIdx, key, variable, statement, createReference);
		}
	}

	/**
	 * Set variable
	 * @param variablePtr variable pointer
	 * @param variableStatement variable statement
	 * @param variable variable
	 * @param statement optional statement the variable is written in
	 * @param createReference optional flag for creating variable references
	 */
	inline void setVariable(Variable* variablePtr, const string& variableStatement, const Variable& variable, const Statement* statement = nullptr, bool createReference = false) {
		//
		if (isVariableAccess(variableStatement, statement) == false) return;
		//
		string variableName;
		// global accessor
		string globalVariableStatement;
		if (_StringTools::viewStartsWith(string_view(variableStatement), string_view("$$.", 3)) == true) {
			globalVariableStatement = "$" + _StringTools::substring(variableStatement, 3);
		} else
		if (_StringTools::viewStartsWith(string_view(variableStatement), string_view("$GLOBAL.", 8)) == true) {
			globalVariableStatement = "$" + _StringTools::substring(variableStatement, 8);
		}

		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		variablePtr = evaluateVariableAccessIntern(variablePtr, globalVariableStatement.empty() == true?variableStatement:globalVariableStatement, __FUNCTION__, parentVariable, arrayIdx, key, setAccessBool, statement, false);

		// set variable if not yet done
		setVariableInternal(variableStatement, parentVariable, variablePtr, arrayIdx, key, variable, statement, createReference);
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
	 * Return function script index by function name
	 * @param function function
	 * @return function script index
	 */
	inline int getFunctionScriptIdx(const string& function) {
		// lookup function
		auto functionIt = functions.find(function);
		if (functionIt == functions.end()) {
			return SCRIPTIDX_NONE;
		}
		//
		auto scriptIdx = functionIt->second;
		//
		return scriptIdx;
	}

	/**
	 * Call function
	 * @param scriptIdx script index
	 * @param arguments argument values
	 * @param returnValue return value
	 * @return success
	 */
	virtual bool call(int scriptIdx, span<Variable>& arguments, Variable& returnValue);

	/**
	 * Call function
	 * @param function function
	 * @param arguments argument values
	 * @param returnValue return value
	 * @return success
	 */
	inline bool call(const string& function, span<Variable>& arguments, Variable& returnValue) {
		// lookup function
		auto functionIt = functions.find(function);
		if (functionIt == functions.end()) {
			return false;
		}
		//
		auto scriptIdx = functionIt->second;
		// call it
		return call(scriptIdx, arguments, returnValue);
	}

	/**
	 * Evaluate statement
	 * @param evaluateStatement evaluate statement
	 * @param returnValue return value
	 * @return success
	 */
	inline bool evaluate(const string& evaluateStatement, Variable& returnValue) {
		Statement evaluateScriptStatement(
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
	 * @return method or nullptr
	 */
	inline Method* getMethod(const string& methodName) {
		auto methodIt = methods.find(methodName);
		if (methodIt != methods.end()) {
			return methodIt->second;
		} else {
			return nullptr;
		}
	}

	/**
	 * @return methods
	 */
	const vector<Method*> getMethods();

	/**
	 * @return operator methods
	 */
	const vector<Method*> getOperatorMethods();

	/**
	 * Get script information for a specific script index
	 * @param scriptIdx script index
	 * @param includeStatements include statements
	 * @return information as string
	 */
	const string getScriptInformation(int scriptIdx, bool includeStatements = true);

	/**
	 * Get MiniScript instance information
	 * @return information as string
	 */
	const string getInformation();

};
