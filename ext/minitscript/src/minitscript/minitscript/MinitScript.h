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

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/fwd-minitscript.h>
#include <minitscript/minitscript/Context.h>
#include <minitscript/minitscript/Library.h>
#include <minitscript/utilities/Character.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Exception.h>
#include <minitscript/utilities/Float.h>
#include <minitscript/utilities/Hex.h>
#include <minitscript/utilities/Integer.h>
#include <minitscript/utilities/StringTools.h>
#include <minitscript/utilities/Time.h>
#include <minitscript/utilities/UTF8CharacterIterator.h>

using std::array;
using std::exchange;
using std::find;
using std::make_unique;
using std::move;
using std::pair;
using std::remove;
using std::sort;
using std::span;
using std::stack;
using std::string;
using std::string_view;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

// namespaces
namespace minitscript {
namespace minitscript {
	using ::minitscript::utilities::Character;
	using ::minitscript::utilities::Console;
	using ::minitscript::utilities::Float;
	using ::minitscript::utilities::Hex;
	using ::minitscript::utilities::Integer;
	using ::minitscript::utilities::StringTools;
	using ::minitscript::utilities::Time;
	using ::minitscript::utilities::UTF8CharacterIterator;
}
}

#define MINITSCRIPT_METHODUSAGE_COMPLAIN(methodName) { minitScript->complain(methodName, subStatement); minitScript->startErrorScript(); }
#define MINITSCRIPT_METHODUSAGE_COMPLAINM(methodName, message) { minitScript->complain(methodName, subStatement, message); minitScript->startErrorScript(); }
#define MINITSCRIPT_METHODUSAGE_COMPLAINO(methodName, operatorString) { minitScript->complainOperator(methodName, operatorString, subStatement); minitScript->startErrorScript(); }
#define MINITSCRIPT_METHODUSAGE_COMPLAINOM(methodName, operatorString, message) { minitScript->complainOperator(methodName, operatorString, subStatement, message); minitScript->startErrorScript(); }

/**
 * MinitScript
 * @author Andreas Drewke
 */
class minitscript::minitscript::MinitScript {
	friend class ApplicationMethods;
	friend class ArrayMethods;
	friend class BaseMethods;
	friend class JSONMethods;
	friend class MathMethods;
	friend class ScriptMethods;
	friend class Setup;
	friend class Transpiler;
	friend class Validations;

public:
	enum Operator {
		// see: https://en.cppreference.com/w/cpp/language/operator_precedence
		OPERATOR_NONE,
		// priority 2
		OPERATOR_MEMBERACCESS_PROPERTY,
		OPERATOR_MEMBERACCESS_EXECUTE,
		OPERATOR_SUBSCRIPT,
		OPERATOR_POSTFIX_INCREMENT,
		OPERATOR_POSTFIX_DECREMENT,
		// priority 3
		OPERATOR_PREFIX_INCREMENT,
		OPERATOR_PREFIX_DECREMENT,
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

	/**
	 * Statement
	 */
	struct Statement {
		/**
		 * Constructor
		 * @param fileName fileName
		 * @param line line
		 * @param statementIdx statement index
		 * @param statement statement
		 * @param executableStatement executable statement
		 * @param gotoStatementIdx goto statement index
		 */
		inline Statement(
			const string& fileName,
			int line,
			int statementIdx,
			const string& statement,
			const string& executableStatement,
			int gotoStatementIdx
		):
			fileName(fileName),
			line(line),
			statementIdx(statementIdx),
			statement(statement),
			executableStatement(executableStatement),
			gotoStatementIdx(gotoStatementIdx)
		{}
		//
		string fileName;
		int line;
		int statementIdx;
		string statement;
		string executableStatement;
		int gotoStatementIdx;
	};

	/**
	 * Sub statement
	 */
	struct SubStatement {
		/**
		 * Sub statement
		 */
		SubStatement():
			statement(nullptr),
			subLineIdx(SUBLINEIDX_NONE)
		{}
		/**
		 * Sub statement
		 * @param statement statement
		 * @param subLineIdx sub line index
		 */
		SubStatement(const Statement& statement, int subLineIdx):
			statement(&statement),
			subLineIdx(subLineIdx)
		{}
		//
		const Statement* statement;
		int subLineIdx;
	};

	enum VariableType {
		// primitives
		TYPE_NULL = 0,
		TYPE_BOOLEAN = 1,
		TYPE_INTEGER = 2,
		TYPE_FLOAT = 3,
		// special
		TYPE_FUNCTION_CALL = 4,
		TYPE_FUNCTION_ASSIGNMENT = 5,
		TYPE_STACKLET_ASSIGNMENT = 6,
		// pseudo
		TYPE_PSEUDO_NUMBER = 7,
		TYPE_PSEUDO_MIXED = 8,
		// classes
		TYPE_STRING = 9,
		TYPE_BYTEARRAY = 10,
		TYPE_ARRAY = 11,
		TYPE_MAP = 12,
		TYPE_SET = 13,
		TYPE_PSEUDO_DATATYPES = 14,
		TYPE_HTTPDOWNLOADCLIENT = 14,
		TYPE_PSEUDO_CUSTOM_DATATYPES = 15
	};

	//
	class SyntaxTreeNode;
	class Variable;

	/**
	 * Data type
	 */
	class DataType {
		friend class MinitScript;
		friend class MathMethods;

	protected:
		/**
		 * Script context
		 */
		class ScriptContext {
			friend class MinitScript;
			public:
				/**
				 * Constructor
				 */
				inline ScriptContext() {}

				/**
				 * Destructor
				 */
				virtual ~ScriptContext() {}

				/**
				 * Set MinitScript instance
				 * @param minitScript MinitScript instance
				 */
				inline void setMinitScript(MinitScript* minitScript) {
					this->minitScript = minitScript;
				}

				/**
				 * Set garbage collection type index
				 * @param index garbage collection type index
				 */
				inline void setIndex(int index) {
					this->index = index;
				}

				/**
				 * Set requires garbage collection
				 */
				inline void setRequiresGarbageCollection() {
					minitScript->garbageCollectionDataTypesIndices.insert(index);
				}

				/**
				 * Unset requires garbage collection
				 */
				inline void unsetRequiresGarbageCollection() {
					minitScript->garbageCollectionDataTypesIndices.erase(index);
				}

			private:
				int index { -1 };
				MinitScript* minitScript { nullptr };
		};

		//
		bool mathDataType { false };
		bool requiresGarbageCollection { false };
		//
		MinitScript::VariableType type { TYPE_NULL };

		/**
		 * Set type
		 * @param type type
		 */
		inline void setType(MinitScript::VariableType type) {
			this->type = type;
		}

		/**
		 * @return is math data type
		 */
		inline bool isMathDataType() {
			return mathDataType;
		}

		/**
		 * @return is requiring garbage collection
		 */
		inline bool isRequiringGarbageCollection() {
			return requiresGarbageCollection;
		}

		/**
		 * Register constants
		 * @param minitScript MinitScript instance
		 */
		virtual void registerConstants(MinitScript* minitScript) const = 0;

		/**
		 * Register methods
		 * @param minitScript MinitScript instance
		 */
		virtual void registerMethods(MinitScript* minitScript) const = 0;

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
		 * @param minitScript MinitScript instance
		 * @param arguments argument values
		 * @param returnValue return value
		 * @param subStatement sub statement
		 * @return mul was executed
		 */
		virtual bool mul(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const = 0;

		/**
		 * Division
		 * @param minitScript MinitScript instance
		 * @param arguments argument values
		 * @param returnValue return value
		 * @param subStatement sub statement
		 * @return div was executed
		 */
		virtual bool div(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const = 0;

		/**
		 * Addition
		 * @param minitScript MinitScript instance
		 * @param arguments argument values
		 * @param returnValue return value
		 * @param subStatement sub statement
		 * @return add was executed
		 */
		virtual bool add(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const = 0;

		/**
		 * Subtraction
		 * @param minitScript MinitScript instance
		 * @param arguments argument values
		 * @param returnValue return value
		 * @param subStatement sub statement
		 * @return sub was executed
		 */
		virtual bool sub(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const = 0;

		/**
		 * Create script context
		 * @return script context
		 */
		virtual ScriptContext* createScriptContext() const = 0;

		/**
		 * Delete script context
		 * @param context script context
		 */
		virtual void deleteScriptContext(ScriptContext* context) const = 0;

		/**
		 * Issue garbage collection
		 * @param context script context
		 */
		virtual void garbageCollection(ScriptContext* context) const = 0;

	public:
		// forbid class copy
		_FORBID_CLASS_COPY(DataType)

		/**
		 * Data type
		 * @param mathDataType is math data type and provides math methods
		 * @param requiresGarbageCollection requires garbage collection
		 */
		inline DataType(bool mathDataType, bool requiresGarbageCollection): mathDataType(mathDataType), requiresGarbageCollection(requiresGarbageCollection) {
			//
		}

		virtual ~DataType() {
			//
		}

		/**
		 * @return type
		 */
		inline MinitScript::VariableType getType() const {
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
		friend class ArrayMethods;
		friend class BaseMethods;
		friend class MinitScript;
	private:
		/**
		 * Variable initializer
		 */
		class Initializer {
			public:
				/**
				 * Constructor
				 */
				inline Initializer():
					statement(
						MinitScript::Statement(
							string(),
							MinitScript::LINE_NONE,
							MinitScript::STATEMENTIDX_NONE,
							string(),
							string(),
							MinitScript::STATEMENTIDX_NONE
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
				inline Initializer(const string& initializerString, const Statement& statement, SyntaxTreeNode* syntaxTree): initializerString(initializerString), statement(statement), syntaxTree(syntaxTree) {}

				/**
				 * Destructor
				 */
				inline ~Initializer() { delete syntaxTree; }

				/**
				 * Copy from initializer
				 * @param initializer initializer
				 */
				inline void copy(Initializer* initializer) {
					this->initializerString = initializer->initializerString;
					this->statement = initializer->statement;
					if (syntaxTree != nullptr && initializer->syntaxTree != nullptr) {
						*syntaxTree = *initializer->syntaxTree;
					}
				}

				/**
				 * @return initializer string
				 */
				inline const string& getInitializerString() const {
					return initializerString;
				}

				/**
				 * @return statement
				 */
				inline const Statement& getStatement() const {
					return statement;
				}

				/**
				 * @return syntax tree node
				 */
				inline const SyntaxTreeNode* getSyntaxTree() const {
					return syntaxTree;
				}

			private:
				string initializerString;
				Statement statement;
				SyntaxTreeNode* syntaxTree;
		};

		//
		static constexpr uint32_t TYPE_BITS_VALUE { 67108863 }; // 2 ^ 26 - 1
		static constexpr uint32_t ARRAY_SUBTYPE_BITS_VALUE { 67108864 | 134217728 }; // 2 ^ 26 | 2 ^ 27
		static constexpr uint32_t CONSTANT_BIT_VALUE { 268435456 }; // 2 ^ 28
		static constexpr uint32_t REFERENCE_BIT_VALUE { 536870912 }; // 2 ^ 29
		static constexpr uint32_t PRIVATE_BIT_VALUE { 1073741824 }; // 2 ^ 30
		static constexpr uint32_t PRIVATESCOPE_BIT_VALUE { 2147483648 }; // 2 ^ 31

		//
		static constexpr uint32_t ARRAY_SUBTYPE_MIXED { 0 };
		static constexpr uint32_t ARRAY_SUBTYPE_BOOLEAN { 1 };
		static constexpr uint32_t ARRAY_SUBTYPE_INTEGER { 2 };
		static constexpr uint32_t ARRAY_SUBTYPE_FLOAT { 3 };

		//
		union InitializerReferenceUnion {
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
			inline StringValue(): cache(UTF8CharacterIterator::UTF8PositionCache()) {}

			/**
			 * Constructor
			 * @param value value
			 */
			inline StringValue(const string& value): value(value) {}

			/**
			 * @return value
			 */
			inline const string& getValue() const {
				return value;
			}

			/**
			 * Set value
			 * @param value value
			 */
			inline void setValue(const string& value) {
				this->value = value;
				cache.removeCache();
			}

			/**
			 * @return const cache
			 */
			inline const UTF8CharacterIterator::UTF8PositionCache& getCache() const {
				return cache;
			}

			/**
			 * @return cache
			 */
			inline UTF8CharacterIterator::UTF8PositionCache& getCache() {
				return cache;
			}

			/**
			 * Set cache
			 * @param cache cache
			 */
			inline void setCache(const UTF8CharacterIterator::UTF8PositionCache& cache) {
				this->cache = cache;
			}

		private:
			string value;
			UTF8CharacterIterator::UTF8PositionCache cache;
		};

		/**
		 * Function value
		 */
		struct FunctionValue {
			string name;
			int scriptIdx;
		};

		/**
		 * ByteArray value
		 */
		struct ByteArrayValue {
			int64_t readPtr { 0ll };
			int64_t writePtr { 0ll };
			vector<uint8_t> value;
		};

		// 24 bytes
		uint32_t typeBits { TYPE_NULL };							// 4 bytes
		int32_t referenceCounter { 1 };								// 4 bytes
		uint64_t valuePtr { 0LL };									// 8 bytes
		InitializerReferenceUnion initializerReferenceUnion {};		// 8 bytes

		/**
		 * Set constant
		 */
		inline void setConstant() {
			typeBits|= CONSTANT_BIT_VALUE;
		}

		/**
		 * Unset constant
		 */
		inline void unsetConstant() {
			typeBits&= TYPE_BITS_VALUE | ARRAY_SUBTYPE_BITS_VALUE | REFERENCE_BIT_VALUE | PRIVATE_BIT_VALUE | PRIVATESCOPE_BIT_VALUE;
		}

		/**
		 * @return unset reference
		 */
		inline void unsetReference() {
			typeBits&= TYPE_BITS_VALUE | ARRAY_SUBTYPE_BITS_VALUE | CONSTANT_BIT_VALUE | PRIVATE_BIT_VALUE | PRIVATESCOPE_BIT_VALUE;
			initializerReferenceUnion.reference = nullptr;
		}

		/**
		 * Set private
		 */
		inline void setPrivate() {
			typeBits|= PRIVATE_BIT_VALUE;
		}

		/**
		 * Set private scope
		 */
		inline void setPrivateScope() {
			typeBits|= PRIVATESCOPE_BIT_VALUE;
		}

		/**
		 * Unset private scope
		 */
		inline void unsetPrivateScope() {
			typeBits&= TYPE_BITS_VALUE | ARRAY_SUBTYPE_BITS_VALUE | CONSTANT_BIT_VALUE | REFERENCE_BIT_VALUE | PRIVATE_BIT_VALUE;
		}

		/**
		 * Set array sub type, see ARRAY_SUBTYPE_*
		 * @param value value
		 */
		inline void setArraySubType(int value) {
			if (isReference() == false) {
				typeBits&= TYPE_BITS_VALUE | CONSTANT_BIT_VALUE | REFERENCE_BIT_VALUE | PRIVATE_BIT_VALUE | PRIVATESCOPE_BIT_VALUE;
				typeBits|= (value & 0x3) << 26;
			} else {
				initializerReferenceUnion.reference->typeBits&= TYPE_BITS_VALUE | CONSTANT_BIT_VALUE | REFERENCE_BIT_VALUE | PRIVATE_BIT_VALUE | PRIVATESCOPE_BIT_VALUE;
				initializerReferenceUnion.reference->typeBits|= (value & 0x3) << 26;
			}
		}

		/**
		 * Get array sub type, see ARRAY_SUBTYPE_*
		 * @return array sub type
		 */
		inline int getArraySubType() {
			if (isReference() == false) {
				return (typeBits & ARRAY_SUBTYPE_BITS_VALUE) >> 26;
			} else {
				return (initializerReferenceUnion.reference->typeBits & ARRAY_SUBTYPE_BITS_VALUE) >> 26;
			}
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
			if (--referenceCounter == 0) {
				if (isReference() == true) {
					initializerReferenceUnion.reference->releaseReference();
					unsetReference();
				}
				setType(TYPE_NULL);
				delete this;
			}
		}

		/**
		 * Return initializer
		 * @return initializer
		 */
		inline Initializer*& getInitializerReference() {
			return isReference() == false?initializerReferenceUnion.initializer:initializerReferenceUnion.reference->initializerReferenceUnion.initializer;
		}

		/**
		 * Return const value pointer
		 * @return value ptr
		 */
		inline const uint64_t& getValuePtrReference() const {
			return isReference() == false?valuePtr:initializerReferenceUnion.reference->valuePtr;
		}

		/**
		 * Return value pointer
		 * @return value ptr
		 */
		inline uint64_t& getValuePtrReference() {
			return isReference() == false?valuePtr:initializerReferenceUnion.reference->valuePtr;
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
		 * @return function value reference
		 */
		inline FunctionValue& getFunctionValueReference() {
			return *static_cast<FunctionValue*>((void*)getValuePtrReference());
		}

		/**
		 * @return const function value reference
		 */
		inline const FunctionValue& getFunctionValueReference() const {
			return *static_cast<FunctionValue*>((void*)getValuePtrReference());
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
		inline ByteArrayValue& getByteArrayValueReference() {
			return *static_cast<ByteArrayValue*>((void*)getValuePtrReference());
		}

		/**
		 * @return const byte array value reference
		 */
		inline const ByteArrayValue& getByteArrayValueReference() const {
			return *static_cast<ByteArrayValue*>((void*)getValuePtrReference());
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
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_NONE;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_NULL;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_BOOLEAN;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_INTEGER;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_FLOAT;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_FUNCTION;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_STACKLET;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_NUMBER;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_MIXED;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_STRING;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_BYTEARRAY;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_ARRAY;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_MAP;
		MINITSCRIPT_STATIC_DLL_IMPEXT static const string TYPENAME_SET;

		/**
		 * @return is constant
		 */
		inline bool isConstant() const {
			return
				(typeBits & CONSTANT_BIT_VALUE) == CONSTANT_BIT_VALUE ||
				(isReference() == true && (initializerReferenceUnion.reference->typeBits & CONSTANT_BIT_VALUE) == CONSTANT_BIT_VALUE);
		}

		/**
		 * @return is reference
		 */
		inline bool isReference() const {
			return (typeBits & REFERENCE_BIT_VALUE) == REFERENCE_BIT_VALUE;
		}

		/**
		 * @return is private
		 */
		inline bool isPrivate() const {
			return
				(typeBits & PRIVATE_BIT_VALUE) == PRIVATE_BIT_VALUE ||
				(isReference() == true && (initializerReferenceUnion.reference->typeBits & PRIVATE_BIT_VALUE) == PRIVATE_BIT_VALUE);
		}

		/**
		 * @return is private scope
		 */
		inline bool isPrivateScope() const {
			return
				(typeBits & PRIVATESCOPE_BIT_VALUE) == PRIVATESCOPE_BIT_VALUE ||
				(isReference() == true && (initializerReferenceUnion.reference->typeBits & PRIVATESCOPE_BIT_VALUE) == PRIVATESCOPE_BIT_VALUE);
		}

		/**
		 * Unset variable
		 */
		inline void unset() {
			if (isReference() == true) {
				initializerReferenceUnion.reference->releaseReference();
				unsetReference();
			}
			setType(TYPE_NULL);
		}

		/**
		 * Set reference
		 * @param variable variable
		 */
		inline void setReference(const Variable* variable) {
			unset();
			typeBits|= REFERENCE_BIT_VALUE;
			if (variable->isReference() == true) {
				initializerReferenceUnion.reference = variable->initializerReferenceUnion.reference;
				initializerReferenceUnion.reference->acquireReference();
			} else {
				initializerReferenceUnion.reference = (Variable*)variable;
				initializerReferenceUnion.reference->acquireReference();
			}
			// we need to copy those properties
			//	as we can tag a reference variable instance (which points to the original)
			//	as private, private scope and constant itself too
			//	no matter which properties the original variable has
			if (variable->isConstant() == true) setConstant();
			if (variable->isPrivate() == true) setPrivate();
			if (variable->isPrivateScope() == true) setPrivateScope();
		}

		/**
		 * Create variable optimized for method argument usage
		 * @param variable variable
		 * @return reference/non reference variable based on data type
		 */
		inline static Variable createMethodArgumentVariable(const Variable* variable) {
			auto createReference = false;
			switch(variable->getType()) {
				case(TYPE_FUNCTION_CALL):
				case(TYPE_FUNCTION_ASSIGNMENT):
				case(TYPE_STACKLET_ASSIGNMENT):
				case(TYPE_STRING):
				case(TYPE_BYTEARRAY):
				case(TYPE_ARRAY):
				case(TYPE_MAP):
				case(TYPE_SET):
					createReference = true;
					break;
				default:
					createReference = variable->getType() >= TYPE_PSEUDO_DATATYPES;
					break;
			}
			//
			return createReference == true?createReferenceVariable(variable):createNonReferenceVariable(variable);
		}

		/**
		 * Create non const/reference variable
		 * @param variable variable
		 * @return non const/reference variable
		 */
		inline static Variable createNonConstVariable(const Variable* variable) {
			auto nonConstVariable = createNonReferenceVariable(variable);
			MinitScript::unsetConstant(nonConstVariable);
			return nonConstVariable;
		}

		/**
		 * Create reference variable
		 * @param variable variable
		 * @return reference variable
		 */
		inline static Variable createReferenceVariable(const Variable* variable) {
			Variable referenceVariable;
			referenceVariable.setReference((Variable*)variable);
			return referenceVariable;
		}

		/**
		 * Create reference variable pointer
		 * @param variable variable
		 * @return reference variable
		 */
		inline static Variable* createReferenceVariablePointer(const Variable* variable) {
			auto referenceVariable = new Variable();
			referenceVariable->setReference((Variable*)variable);
			return referenceVariable;
		}

		/**
		 * Create none reference variable
		 * @param variable variable
		 * @return reference variable
		 */
		inline static Variable createNonReferenceVariable(const Variable* variable) {
			Variable nonReferenceVariable;
			//
			copyVariable(nonReferenceVariable, *variable, true);
			//
			return nonReferenceVariable;
		}

		/**
		 * Create none reference variable pointer
		 * @param variable variable
		 * @return reference variable
		 */
		inline static Variable* createNonReferenceVariablePointer(const Variable* variable) {
			auto nonReferenceVariable = new Variable();
			//
			copyVariable(*nonReferenceVariable, *variable, true);
			//
			return nonReferenceVariable;
		}

		/**
		 * Copy variable
		 * @param from from
		 * @param to to
		 * @param properties copy also properties
		 */
		inline static void copyVariable(Variable& to, const Variable& from, bool properties) {
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
					{
						const auto& functionValue = from.getFunctionValueReference();
						to.setFunctionAssignment(functionValue.name, functionValue.scriptIdx);
						break;
					}
				case TYPE_STACKLET_ASSIGNMENT:
					{
						const auto& functionValue = from.getFunctionValueReference();
						to.setStackletAssignment(functionValue.name, functionValue.scriptIdx);
						break;
					}
				case TYPE_PSEUDO_NUMBER: break;
				case TYPE_PSEUDO_MIXED: break;
				case TYPE_STRING:
					{
						const auto& stringValue = from.getStringValueReference();
						to.getStringValueReference().setValue(stringValue.getValue());
						to.getStringValueReference().setCache(stringValue.getCache());
						break;
					}
				case TYPE_BYTEARRAY:
					to.getByteArrayValueReference() = from.getByteArrayValueReference();
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
					auto dataTypeIdx = static_cast<int>(from.getType()) - TYPE_PSEUDO_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MinitScript::dataTypes.size()) {
						Console::printLine("ScriptVariable::copyScriptVariable(): unknown data type with id " + to_string(dataTypeIdx));
						return;
					}
					MinitScript::dataTypes[dataTypeIdx]->copyVariable(to, from);
			}
			//
			if (properties == true) {
				if (from.isConstant() == true) to.setConstant();
				if (from.isPrivate() == true) to.setPrivate();
				if (from.isPrivateScope() == true) to.setPrivateScope();
			}
		}

		/**
		 * Swap variables
		 * @param a a
		 * @param b b
		 */
		inline static void swap(Variable& a, Variable& b) {
			auto& _a = a.isReference() == true?*a.initializerReferenceUnion.reference:a;
			auto& _b = b.isReference() == true?*b.initializerReferenceUnion.reference:b;
			std::swap(_a.typeBits, _b.typeBits);
			std::swap(_a.valuePtr, _b.valuePtr);
			std::swap(_a.initializerReferenceUnion, _b.initializerReferenceUnion);
			std::swap(_a.referenceCounter, _b.referenceCounter);
		}

		/**
		 * Copy constructor
		 * @param variable variable to copy
		 */
		inline Variable(const Variable& variable) {
			if (variable.isReference() == true) {
				setReference(&variable);
			} else {
				copyVariable(*this, variable, true);
			}
		}

		/**
		 * Move constructor
		 * @param variable variable to move from
		 */
		inline Variable(Variable&& variable):
			typeBits(exchange(variable.typeBits, static_cast<int>(MinitScript::TYPE_NULL))),
			valuePtr(exchange(variable.valuePtr, 0ll)),
			referenceCounter(exchange(variable.referenceCounter, 1)) {
			// TODO: improve me
			initializerReferenceUnion.initializer = variable.initializerReferenceUnion.initializer;
			variable.initializerReferenceUnion.initializer = nullptr;
		}

		/**
		 * Assignment operator
		 * @param variable variable to copy
		 * @return this variable
		 */
		inline Variable& operator=(const Variable& variable) {
			// set up new variable
			unset();
			//
			if (variable.isReference() == true) {
				setReference(&variable);
			} else {
				copyVariable(*this, variable, true);
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
			std::swap(typeBits, variable.typeBits);
			std::swap(valuePtr, variable.valuePtr);
			std::swap(initializerReferenceUnion, variable.initializerReferenceUnion);
			std::swap(referenceCounter, variable.referenceCounter);
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
				initializerReferenceUnion.reference->releaseReference();
				unsetReference();
			}
			setType(TYPE_NULL);
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
		 * @param type type
		 * @param value value
		 * @param scriptIdx script index
		 */
		inline Variable(VariableType type, const string& value, int scriptIdx = SCRIPTIDX_NONE) {
			switch (type) {
				case MinitScript::TYPE_FUNCTION_ASSIGNMENT:
					setFunctionAssignment(value, scriptIdx);
					break;
				case MinitScript::TYPE_STACKLET_ASSIGNMENT:
					setStackletAssignment(value, scriptIdx);
					break;
				case MinitScript::TYPE_STRING:
					setValue(value);
					break;
				default:
					Console::printLine("Variable::Variable(VariableType, const string&): invalid type: " + getTypeAsString(type));
			}
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
			return static_cast<VariableType>((isReference() == false?typeBits:initializerReferenceUnion.reference->typeBits) & TYPE_BITS_VALUE);
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
					delete static_cast<StringValue*>((void*)getValuePtrReference());
					break;
				case TYPE_FUNCTION_ASSIGNMENT:
				case TYPE_STACKLET_ASSIGNMENT:
					delete static_cast<FunctionValue*>((void*)getValuePtrReference());
					break;
				case TYPE_BYTEARRAY:
					delete static_cast<ByteArrayValue*>((void*)getValuePtrReference());
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
					auto dataTypeIdx = static_cast<int>(this->getType()) - TYPE_PSEUDO_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MinitScript::dataTypes.size()) {
						Console::printLine("ScriptVariable::setType(): unknown data type with id " + to_string(dataTypeIdx));
						return;
					}
					MinitScript::dataTypes[dataTypeIdx]->unsetVariableValue(*this);

			}
			this->getValuePtrReference() = 0LL;
			//
			if (isReference() == true) {
				initializerReferenceUnion.reference->typeBits =
					static_cast<uint32_t>(newType) |
					((initializerReferenceUnion.reference->typeBits & CONSTANT_BIT_VALUE) == CONSTANT_BIT_VALUE?CONSTANT_BIT_VALUE:0) |
					((initializerReferenceUnion.reference->typeBits & PRIVATE_BIT_VALUE) == PRIVATE_BIT_VALUE?PRIVATE_BIT_VALUE:0) |
					((initializerReferenceUnion.reference->typeBits & PRIVATESCOPE_BIT_VALUE) == PRIVATESCOPE_BIT_VALUE?PRIVATESCOPE_BIT_VALUE:0);
			} else {
				typeBits =
					static_cast<uint32_t>(newType) |
					((typeBits & CONSTANT_BIT_VALUE) == CONSTANT_BIT_VALUE?CONSTANT_BIT_VALUE:0) |
					((typeBits & PRIVATE_BIT_VALUE) == PRIVATE_BIT_VALUE?PRIVATE_BIT_VALUE:0) |
					((typeBits & PRIVATESCOPE_BIT_VALUE) == PRIVATESCOPE_BIT_VALUE?PRIVATESCOPE_BIT_VALUE:0);
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
				case TYPE_FUNCTION_ASSIGNMENT:
				case TYPE_STACKLET_ASSIGNMENT:
					getValuePtrReference() = (uint64_t)(new FunctionValue());
					break;
				case TYPE_STRING:
					getValuePtrReference() = (uint64_t)(new StringValue());
					break;
				case TYPE_BYTEARRAY:
					getValuePtrReference() = (uint64_t)(new ByteArrayValue());
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
					auto dataTypeIdx = static_cast<int>(this->getType()) - TYPE_PSEUDO_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MinitScript::dataTypes.size()) {
						Console::printLine("ScriptVariable::setType(): unknown data type with id " + to_string(dataTypeIdx));
						return;
					}
					MinitScript::dataTypes[dataTypeIdx]->setVariableValue(*this);
			}
		}

		/**
		 * Return initializer
		 * @return initializer
		 */
		inline Initializer* getInitializer() const {
			return isReference() == true?initializerReferenceUnion.reference->initializerReferenceUnion.initializer:initializerReferenceUnion.initializer;
		}

		/**
		 * @return value pointer
		 */
		inline void* getValuePtr() const {
			return (void*)(isReference() == true?initializerReferenceUnion.reference->valuePtr:valuePtr);
		}

		/**
		 * Set value pointer
		 * @param valuePtr value pointer
		 */
		inline void setValuePtr(void* valuePtr) {
			if (isReference() == true) {
				initializerReferenceUnion.reference->valuePtr = (uint64_t)valuePtr;
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
						auto lowerCaseString = StringTools::toLowerCase(getStringValueReference().getValue());
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
					value = getFloatValueReference();
					return true;
				case TYPE_STRING:
					{
						const auto& stringValue = getStringValueReference().getValue();
						if (Integer::is(stringValue) == true) {
							value = Integer::parse(stringValue);
							return true;
						} else
						if (Float::is(stringValue) == true) {
							value = static_cast<int64_t>(Float::parse(stringValue));
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
						if (Float::is(stringValue) == false) return optional;
						value = Float::parse(stringValue);
					}
					return true;
				default:
					return optional;
			}
			return false;
		}

		/**
		 * Get function values from given variable
		 * @param function function
		 * @param scriptIdx script index
		 * @param optional optional
		 * @return success
		 */
		inline bool getFunctionValue(string& function, int& scriptIdx, bool optional = false) const {
			switch(getType()) {
				case TYPE_FUNCTION_ASSIGNMENT:
					{
						const auto& functionValue = getFunctionValueReference();
						function = functionValue.name;
						scriptIdx = functionValue.scriptIdx;
						return true;
					}
				default:
					return false;
			}
			return false;
		}

		/**
		 * Get stacklet values from given variable
		 * @param stacklet stacklet
		 * @param scriptIdx script index
		 * @param optional optional
		 * @return success
		 */
		inline bool getStackletValue(string& stacklet, int& scriptIdx, bool optional = false) const {
			switch(getType()) {
				case TYPE_STACKLET_ASSIGNMENT:
					{
						const auto& functionValue = getFunctionValueReference();
						stacklet = functionValue.name;
						scriptIdx = functionValue.scriptIdx;
						return true;
					}
				default:
					return false;
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
					value = getStringValueReference().getValue();
					return true;
				default:
					return false;
			}
			return false;
		}

		/**
		 * Get byte value from given variable
		 * @param minitScript mini script
		 * @param value value
		 * @param statement statement
		 * @return success
		 */
		inline bool getByteValue(MinitScript* minitScript, uint8_t& value, const Statement* statement = nullptr) const {
			int64_t intValue;
			if (getIntegerValue(intValue, false) == true && value >= 0 && value <= 255) {
				value = intValue;
				return true;
			} else {
				if (statement != nullptr) {
					Console::printLine(minitScript->getStatementInformation(*statement) + ": Expected byte integer value (0 <= value <= 255), but got " + getValueAsString());
				} else {
					Console::printLine(minitScript->getScriptFileName() + ": Expected byte integer value (0 <= value <= 255), but got " + getValueAsString());
				}
			}
			return false;
		}

		/**
		 * Get string value UTF8 position cache from given variable
		 * @return UTF8 position cache or nullptr if not available
		 */
		inline UTF8CharacterIterator::UTF8PositionCache* getStringValueCache() {
			switch(getType()) {
				case TYPE_STRING:
				case TYPE_FUNCTION_ASSIGNMENT:
				case TYPE_STACKLET_ASSIGNMENT:
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
		 * Set value from given variable into variable
		 * @param variable variable
		 */
		inline void setValue(const Variable& variable) {
			setType(TYPE_NULL);
			copyVariable(*this, variable, false);
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
			for (const auto arrayEntry: value) {
				 pushByteArrayEntry(arrayEntry);
			}
		}

		/**
		 * Set array value from given value into variable
		 * @param value value
		 */
		inline void setValue(const vector<Variable*>& value) {
			setType(TYPE_ARRAY);
			setArraySubType(ARRAY_SUBTYPE_MIXED);
			for (const auto arrayEntry: value) {
				pushArrayEntry(*arrayEntry);
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
			auto dataTypeIdx = static_cast<int>(this->getType()) - TYPE_PSEUDO_DATATYPES;
			if (dataTypeIdx < 0 || dataTypeIdx >= MinitScript::dataTypes.size()) {
				Console::printLine("ScriptVariable::setValue(): unknown data type with id " + to_string(dataTypeIdx));
				return;
			}
			MinitScript::dataTypes[dataTypeIdx]->setVariableValue(*this, value);
		}

		/**
		 * @return return const pointer to underlying byte vector or nullptr
		 */
		inline const vector<uint8_t>* getByteArrayPointer() const {
			if (getType() != TYPE_BYTEARRAY) return nullptr;
			auto& byteArrayValue = getByteArrayValueReference().value;
			return &byteArrayValue;
		}

		/**
		 * @return pointer to underlying byte vector or nullptr
		 */
		inline vector<uint8_t>* getByteArrayPointer() {
			if (getType() != TYPE_BYTEARRAY) return nullptr;
			auto& byteArrayValue = getByteArrayValueReference().value;
			return &byteArrayValue;
		}

		/**
		 * Get byte array size
		 * @return byte array size
		 */
		inline int64_t getByteArraySize() const {
			if (getType() != TYPE_BYTEARRAY) return 0;
			return getByteArrayValueReference().value.size();
		}

		/**
		 * Get const byte array read pointer
		 * @return const pointer to byte array read pointer
		 */
		inline const int64_t* getByteArrayReadPointer() const {
			if (getType() != TYPE_BYTEARRAY) return nullptr;
			return &getByteArrayValueReference().readPtr;
		}

		/**
		 * Get byte array read pointer
		 * @return pointer to byte array read pointer
		 */
		inline int64_t* getByteArrayReadPointer() {
			if (getType() != TYPE_BYTEARRAY) return nullptr;
			return &getByteArrayValueReference().readPtr;
		}

		/**
		 * Get const byte array write pointer
		 * @return const pointer to byte array write pointer
		 */
		inline const int64_t* getByteArrayWritePointer() const {
			if (getType() != TYPE_BYTEARRAY) return nullptr;
			return &getByteArrayValueReference().writePtr;
		}

		/**
		 * Get byte array write pointer
		 * @return pointer to byte array write pointer
		 */
		inline int64_t* getByteArrayWritePointer() {
			if (getType() != TYPE_BYTEARRAY) return nullptr;
			return &getByteArrayValueReference().writePtr;
		}

		/**
		 * Get entry from byte array with given index
		 * @param idx index
		 * @return entry from byte array with given index
		 */
		inline const uint8_t getByteArrayEntry(int64_t idx) const {
			if (getType() != TYPE_BYTEARRAY) return 0;
			const auto& byteArrayValue = getByteArrayValueReference().value;
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
			auto& byteArrayValue = getByteArrayValueReference().value;
			while (byteArrayValue.size() <= idx) pushByteArrayEntry(0);
			byteArrayValue[idx] = value;
		}

		/**
		 * Push entry to byte array
		 * @param value value
		 */
		inline void pushByteArrayEntry(uint8_t value) {
			setType(TYPE_BYTEARRAY);
			getByteArrayValueReference().value.push_back(value);
		}

		/**
		 * Remove byte array entries at given index and size
		 * @param idx index
		 * @param size size
		 */
		inline void removeByteArray(int64_t idx, int64_t size) {
			if (getType() != TYPE_BYTEARRAY) return;
			auto& byteArrayValue = getByteArrayValueReference().value;
			if (idx >= 0 && idx < byteArrayValue.size()) {
				byteArrayValue.erase(byteArrayValue.begin() + idx, byteArrayValue.begin() + idx + size);
			}
		}

		/**
		 * Clear byte array
		 */
		inline void clearByteArray() {
			if (getType() != TYPE_BYTEARRAY) return;
			auto& byteArrayValue = getByteArrayValueReference().value;
			byteArrayValue.clear();
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
		 * Set initial array sub type by adding first value
		 * @param value value
		 */
		inline void setInitialArraySubType(const Variable& value) {
			switch(value.getType()) {
				case(TYPE_NULL): setArraySubType(ARRAY_SUBTYPE_INTEGER); break;
				case(TYPE_BOOLEAN): setArraySubType(ARRAY_SUBTYPE_BOOLEAN); break;
				case(TYPE_INTEGER): setArraySubType(ARRAY_SUBTYPE_INTEGER); break;
				case(TYPE_FLOAT): setArraySubType(ARRAY_SUBTYPE_FLOAT); break;
				default: setArraySubType(ARRAY_SUBTYPE_MIXED); break;
			}
		}

		/**
		 * Determine array sub type after adding another value
		 * @param value value
		 */
		inline void determineArraySubType(const Variable& value) {
			switch (getArraySubType()) {
				case ARRAY_SUBTYPE_BOOLEAN:
					{
						switch(value.getType()) {
							case(TYPE_NULL): setArraySubType(ARRAY_SUBTYPE_INTEGER); break;
							case(TYPE_BOOLEAN): break;
							case(TYPE_INTEGER): setArraySubType(ARRAY_SUBTYPE_INTEGER); break;
							case(TYPE_FLOAT): setArraySubType(ARRAY_SUBTYPE_FLOAT); break;
							default: setArraySubType(ARRAY_SUBTYPE_MIXED); break;
						}
						break;
					}
				case ARRAY_SUBTYPE_INTEGER:
					{
						switch(value.getType()) {
							case(TYPE_NULL): break;
							case(TYPE_BOOLEAN): break;
							case(TYPE_INTEGER): break;
							case(TYPE_FLOAT): setArraySubType(ARRAY_SUBTYPE_FLOAT); break;
							default: setArraySubType(ARRAY_SUBTYPE_MIXED); break;
						}
						break;
					}
				case ARRAY_SUBTYPE_FLOAT:
					{
						switch(value.getType()) {
							case(TYPE_NULL): break;
							case(TYPE_BOOLEAN): break;
							case(TYPE_INTEGER): break;
							case(TYPE_FLOAT): break;
							default: setArraySubType(ARRAY_SUBTYPE_MIXED); break;
						}
						break;
					}
				case ARRAY_SUBTYPE_MIXED:
					{
						break;
					}
			}
		}

		/**
		 * Compute array sub type
		 */
		inline void computeArraySubType() {
			if (getType() != TYPE_ARRAY) return;
			setArraySubType(ARRAY_SUBTYPE_MIXED);
			const auto& arrayValue = getArrayValueReference();
			if (arrayValue.empty() == true) return;
			setInitialArraySubType(*arrayValue[0]);
			for (auto i = 1; i < arrayValue.size(); i++) determineArraySubType(*arrayValue[i]);
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
		 * Get entry pointer from array with given index
		 * @param idx index
		 * @return entry from array with given index
		 */
		inline const Variable* getArrayEntryPtr(int64_t idx) const {
			if (getType() != TYPE_ARRAY) return nullptr;
			const auto& arrayValue = getArrayValueReference();
			if (idx >= 0 && idx < arrayValue.size()) return arrayValue[idx];
			return nullptr;
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
			if (arrayValue.size() == 1) {
				setInitialArraySubType(value);
			} else {
				determineArraySubType(value);
			}
		}

		/**
		 * Push entry to array
		 * @param value value
		 */
		inline void pushArrayEntry(const Variable& value) {
			setType(TYPE_ARRAY);
			auto& arrayValue = getArrayValueReference();
			arrayValue.push_back(new Variable(value));
			if (arrayValue.size() == 1) {
				setInitialArraySubType(value);
			} else {
				determineArraySubType(value);
			}
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
			if (arrayValue.empty() == true) {
				setArraySubType(ARRAY_SUBTYPE_MIXED);
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
			setArraySubType(ARRAY_SUBTYPE_MIXED);
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
		 * Get entry pointer from map with given key
		 * @param key key
		 * @return map entry from given key
		 */
		inline const Variable* getMapEntryPtr(const string& key) const {
			if (getType() != TYPE_MAP) return nullptr;
			const auto& mapValue = getMapValueReference();
			auto it = mapValue.find(key);
			if (it != mapValue.end()) return it->second;
			return nullptr;
		}

		/**
		 * Set entry in map with given key
		 * @param key key
		 * @param value value
		 * @param _private private entry
		 *
		 */
		inline void setMapEntry(const string& key, const Variable& value, bool _private = false) {
			setType(TYPE_MAP);
			auto mapValueIt = getMapValueReference().find(key);
			if (mapValueIt != getMapValueReference().end()) mapValueIt->second->releaseReference();
			auto variablePtr = new Variable(value);
			if (_private == true) variablePtr->setPrivate();
			getMapValueReference()[key] = variablePtr;
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
		 * @param scriptFileName script file name
		 * @param initializerStatement initializer statement
		 * @param minitScript minitscript instance
		 * @param scriptIdx script index
		 * @param statement statement
		 */
		void setFunctionCallStatement(const string& scriptFileName, const string& initializerStatement, MinitScript* minitScript, int scriptIdx, const Statement& statement);

		/**
		 * Set function assignment from given value into variable
		 * @param function function
		 * @param scriptIdx script index
		 */
		inline void setFunctionAssignment(const string& function, int scriptIdx = MinitScript::SCRIPTIDX_NONE) {
			setType(TYPE_FUNCTION_ASSIGNMENT);
			auto& functionValue = getFunctionValueReference();
			functionValue.name = function;
			functionValue.scriptIdx = scriptIdx;
		}

		/**
		 * Set stacklet assignment from given value into variable
		 * @param stacklet stacklet
		 * @param scriptIdx script index
		 */
		inline void setStackletAssignment(const string& stacklet, int scriptIdx = MinitScript::SCRIPTIDX_NONE) {
			setType(TYPE_STACKLET_ASSIGNMENT);
			auto& functionValue = getFunctionValueReference();
			functionValue.name = stacklet;
			functionValue.scriptIdx = scriptIdx;
		}

		/**
		 * Set implicit typed value given by value string
		 * @param scriptFileName script file name
		 * @param value value
		 * @param minitScript mini script
		 * @param scriptIdx script index
		 * @param statement statement
		 */
		inline void setImplicitTypedValue(const string& scriptFileName, const string& value, MinitScript* minitScript, int scriptIdx, const Statement& statement) {
			setImplicitTypedValueFromStringView(scriptFileName, string_view(value), minitScript, scriptIdx, statement);
		}

		/**
		 * Set implicit typed value given by value string
		 * @param scriptFileName script file name
		 * @param value value
		 * @param minitScript mini script
		 * @param scriptIdx script index
		 * @param statement statement
		 */
		inline void setImplicitTypedValueFromStringView(const string& scriptFileName, const string_view& value, MinitScript* minitScript, int scriptIdx, const Statement& statement) {
			//
			auto viewIsFunctionAssignment = [](const string_view& candidate, string_view& function) -> bool {
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
				for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
				if (i >= candidate.size()) return false;
				// -
				if (candidate[i++] != '-') return false;
				//
				if (i >= candidate.size()) return false;
				// >
				if (candidate[i++] != '>') return false;
				// spaces
				for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
				if (i >= candidate.size()) return false;
				//
				auto functionStartIdx = i;
				for (; i < candidate.size(); i++) {
					auto c = candidate[i];
					if (Character::isAlphaNumeric(c) == false && c != '_') {
						return false;
					}
				}
				//
				function = string_view(&candidate[functionStartIdx], i - functionStartIdx);
				//
				return true;
			};
			//
			auto viewIsStackletAssignment = [](const string_view& candidate, string_view& stacklet) -> bool {
				if (candidate.size() == 0) return false;
				//
				auto i = 0;
				// spaces
				for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
				if (i >= candidate.size()) return false;
				// -
				if (candidate[i++] != '-') return false;
				//
				if (i >= candidate.size()) return false;
				// >
				if (candidate[i++] != '>') return false;
				// spaces
				for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
				if (i >= candidate.size()) return false;
				//
				auto stackletStartIdx = i;
				for (; i < candidate.size(); i++) {
					auto c = candidate[i];
					if (Character::isAlphaNumeric(c) == false && c != '_') {
						return false;
					}
				}
				//
				stacklet = string_view(&candidate[stackletStartIdx], i - stackletStartIdx);
				//
				return true;
			};
			//
			string_view functionOrStacklet;
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
			if (Integer::viewIs(value) == true) {
				setValue(static_cast<int64_t>(Integer::viewParse(value)));
			} else
			if (Float::viewIs(value) == true) {
				setValue(Float::viewParse(value));
			} else
			if (viewIsStringLiteral(value) == true) {
				setValue(minitScript->deescape(dequote(value), statement));
			} else
			if (StringTools::viewStartsWith(value, "{") == true &&
				StringTools::viewEndsWith(value, "}") == true) {
				setValue(initializeMapSet(scriptFileName, value, minitScript, scriptIdx, statement));
			} else
			if (StringTools::viewStartsWith(value, "[") == true &&
				StringTools::viewEndsWith(value, "]") == true) {
				setValue(initializeArray(scriptFileName, value, minitScript, scriptIdx, statement));
			} else
			if (viewIsFunctionAssignment(value, functionOrStacklet) == true) {
				setFunctionAssignment(string(functionOrStacklet));
			} else
			if (viewIsStackletAssignment(value, functionOrStacklet) == true) {
				setStackletAssignment(string(functionOrStacklet));
			} else
			if (viewIsCall(value) == true) {
				setFunctionCallStatement(scriptFileName, minitScript->doStatementPreProcessing(string(value), statement), minitScript, scriptIdx, statement);
			} else
			if (viewIsVariableAccess(value) == true) {
				setFunctionCallStatement(scriptFileName, "getVariable(\"" + string(value) + "\")", minitScript, scriptIdx, statement);
			} else {
				setValue(minitScript->deescape(value, statement));
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
				case TYPE_STACKLET_ASSIGNMENT: return TYPENAME_STACKLET;
				case TYPE_PSEUDO_NUMBER: return TYPENAME_NUMBER;
				case TYPE_PSEUDO_MIXED: return TYPENAME_MIXED;
				case TYPE_STRING: return TYPENAME_STRING;
				case TYPE_BYTEARRAY: return TYPENAME_BYTEARRAY;
				case TYPE_ARRAY: return TYPENAME_ARRAY;
				case TYPE_MAP: return TYPENAME_MAP;
				case TYPE_SET: return TYPENAME_SET;
				default:
					// custom data types
					auto dataTypeIdx = static_cast<int>(type) - TYPE_PSEUDO_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MinitScript::dataTypes.size()) {
						return TYPENAME_NONE;
					}
					return MinitScript::dataTypes[dataTypeIdx]->getTypeAsString();
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
			auto escapeString = [](const string& str) -> const string {
				const array<char, 11> escapeSequences = {'0', 'a', 'b', 'f', 'n', 'r', 't', 'v', 'U', '"'};
				//
				auto result = str;
				//
				result = StringTools::replace(result, "\0", "\\0");
				result = StringTools::replace(result, "\a", "\\a");
				result = StringTools::replace(result, "\b", "\\b");
				result = StringTools::replace(result, "\f", "\\f");
				result = StringTools::replace(result, "\n", "\\n");
				result = StringTools::replace(result, "\r", "\\r");
				result = StringTools::replace(result, "\t", "\\t");
				result = StringTools::replace(result, "\v", "\\v");
				result = StringTools::replace(result, "\"", "\\\"");
				//
				string result2;
				auto lc = '\0';
				auto llc = '\0';
				for (auto i = 0; i < result.size(); i++) {
					//
					auto c = result[i];
					auto nc = i < result.size() - 1?result[i + 1]:'\0';
					if (c == '\\' && lc != '\\' && nc != '\\' && find(escapeSequences.begin(), escapeSequences.end(), nc) == escapeSequences.end()) {
						result2+= "\\\\";
					} else {
						result2+= c;
					}
					//
					auto lc = c;
					auto llc = lc;
				}
				//
				return result2;
			};
			//
			string result;
			switch (getType()) {
				case TYPE_NULL:
					result+= "<Null>";
					break;
				case TYPE_BOOLEAN:
					result+= getBooleanValueReference() == true?"true":"false";
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
					{
						const auto& functionValue = getFunctionValueReference();
						result+= "() -> " + functionValue.name + "(" + to_string(functionValue.scriptIdx) + ")";
						break;
					}
				case TYPE_STACKLET_ASSIGNMENT:
					{
						const auto& functionValue = getFunctionValueReference();
						result+= "-> " + functionValue.name + "(" + to_string(functionValue.scriptIdx) + ")";
						break;
					}
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
						const auto& byteArrayValue = getByteArrayValueReference().value;
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
						result =
							"ByteArray([" + result + "], " +
								"size: " + to_string(byteArrayValue.size()) +
								", capacity: " + to_string(byteArrayValue.capacity()) +
								", read position: " + to_string(getByteArrayValueReference().readPtr) +
								", write position: " + to_string(getByteArrayValueReference().writePtr) +
								")";
						break;
					}
				case TYPE_ARRAY:
					{
						const auto& arrayValue = getArrayValueReference();
						vector<string> values;
						for (const auto arrayEntry: arrayValue) {
							if (arrayEntry->getType() == TYPE_STRING) {
								values.push_back("\"" + escapeString(arrayEntry->getValueAsString(formatted, jsonCompatible, depth + 1)) + "\"");
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
								result+= StringTools::indent(valueString, "\t" , depth + 1);
								result+= "\n";
							}
							result = (depth == 0?StringTools::indent("[", "\t", depth):"[") + "\n" + result;
							result+= StringTools::indent("]", "\t", depth) + (depth == 0?"\n":"");
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
							value+= "\"" + escapeString(mapEntryName) +  "\": ";
							if (mapEntryValue->getType() == TYPE_STRING) {
								value+= "\"";
								value+= escapeString(mapEntryValue->getValueAsString(formatted, jsonCompatible, depth + 1));
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
								result+= StringTools::indent(valueString, "\t" , depth + 1);
								result+= "\n";
							}
							result = (depth == 0?StringTools::indent("{", "\t", depth):"{") + "\n" + result;
							result+= StringTools::indent("}", "\t", depth) + (depth == 0?"\n":"");
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
								"\"" + escapeString(key) + "\""
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
								result+= StringTools::indent(valueString, "\t" , depth + 1);
								result+= "\n";
							}
							result = (depth == 0?StringTools::indent("{", "\t", depth):"{") + "\n" + result;
							result+= StringTools::indent("}", "\t", depth) + (depth == 0?"\n":"");
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
					auto dataTypeIdx = static_cast<int>(getType()) - TYPE_PSEUDO_DATATYPES;
					if (dataTypeIdx < 0 || dataTypeIdx >= MinitScript::dataTypes.size()) {
						Console::printLine("ScriptVariable::getValueAsString(): unknown data type with id " + to_string(dataTypeIdx));
						return result;
					}
					return MinitScript::dataTypes[dataTypeIdx]->getValueAsString(*this);

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
		_FORBID_CLASS_COPY(StateMachineState)

		/**
		 * Constructor
		 */
		inline StateMachineState() {}

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
		_FORBID_CLASS_COPY(Method)

		/**
		 * Constructor
		 * @param argumentTypes argument types
		 * @param returnValueType return value type
		 * @param returnValueNullable true if return value can also be a null value
		 * @param throwsException throws exception
		 */
		inline Method(
			const vector<ArgumentType>& argumentTypes = {},
			VariableType returnValueType = VariableType::TYPE_NULL,
			bool returnValueNullable = false,
			bool throwsException = false
		):
			argumentTypes(argumentTypes),
			returnValueType(returnValueType),
			returnValueNullable(returnValueNullable),
			throwsException(throwsException) {
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
		 * @param subStatement sub statement
		 */
		virtual void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) = 0;

		/**
		 * @return arguments
		 */
		inline const vector<ArgumentType>& getArgumentTypes() const {
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
			return result;
		}

		/**
		 * Returns given return value variable type string representation
		 * @return return value variable type string representation
		 */
		inline const string getReturnTypeAsString() const {
			return MinitScript::Variable::getReturnTypeAsString(returnValueType, returnValueNullable);
		}

		/**
		 * @return return value type
		 */
		inline const VariableType& getReturnValueType() const {
			return returnValueType;
		}

		/**
		 * @return if return value can be null
		 */
		inline bool isReturnValueNullable() const {
			return returnValueNullable;
		}

		/**
		 * Returns if method throws an exception
		 * @return method throws an exception
		 */
		inline const string getThrowsAsString() const {
			return throwsException == true?" - throws exception":"";
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
		MINITSCRIPT_STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTIONS_ALL;

	private:
		vector<ArgumentType> argumentTypes;
		VariableType returnValueType;
		bool returnValueNullable;
		bool throwsException;
	};

	/**
	 * Syntax Tree Node
	 */
	struct SyntaxTreeNode {
		enum Type {
			SCRIPTSYNTAXTREENODE_NONE,
			SCRIPTSYNTAXTREENODE_LITERAL,
			SCRIPTSYNTAXTREENODE_EXECUTE_METHOD,
			SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION,
			SCRIPTSYNTAXTREENODE_EXECUTE_STACKLET
		};
		/**
		 * Constructor
		 */
		inline SyntaxTreeNode():
			type(SCRIPTSYNTAXTREENODE_NONE),
			value(Variable()),
			pointer(0ll),
			arguments({}),
			subLineIdx(LINE_NONE)
		{}
		/**
		 * Constructor
		 * @param type type
		 * @param value value
		 * @param pointer pointer to method
		 * @param arguments arguments
		 * @param subLineIdx sub line index
		 */
		inline SyntaxTreeNode(
			Type type,
			const Variable& value,
			Method* method,
			const vector<SyntaxTreeNode>& arguments,
			int subLineIdx
		):
			type(type),
			value(value),
			pointer((uint64_t)method),
			arguments(arguments),
			subLineIdx(subLineIdx)
		{}
		/**
		 * Constructor
		 * @param type type
		 * @param value value
		 * @param scriptIdx script index
		 * @param arguments arguments
		 * @param subLineIdx sub line index
		 */
		inline SyntaxTreeNode(
			Type type,
			const Variable& value,
			uint64_t scriptIdx,
			const vector<SyntaxTreeNode>& arguments,
			int subLineIdx
		):
			type(type),
			value(value),
			pointer(scriptIdx),
			arguments(arguments),
			subLineIdx(subLineIdx)
		{}
		/**
		 * @return method
		 */
		inline Method* getMethod() const {
			return (Method*)pointer;
		}
		/**
		 * Set method
		 * @param method method
		 */
		inline void setMethod(Method* method) {
			pointer = (uint64_t)method;
		}
		/**
		 * @return function/stacklet script index
		 */
		inline int64_t getScriptIdx() const {
			return pointer;
		}
		/**
		 * Set function/stacklet script index
		 * @param scriptIdx script index
		 */
		inline void setScriptIdx(uint64_t scriptIdx) {
			pointer = scriptIdx;
		}
		//
		Type type;
		Variable value;
		uint64_t pointer;
		vector<SyntaxTreeNode> arguments;
		int subLineIdx;
	};

	/**
	 * Script
	 */
	struct Script {
		/**
		 * Argument
		 */
		struct Argument {
			/**
			 * Constructor
			 * @param name name
			 * @param reference reference
			 * @param privateScope private scope
			 */
			Argument(
				const string& name,
				bool reference,
				bool privateScope
			):
				name(name),
				reference(reference),
				privateScope(privateScope)
			{}
			//
			string name;
			bool reference;
			bool privateScope;
		};
		//
		enum Type {
			TYPE_NONE,
			TYPE_FUNCTION,
			TYPE_STACKLET
			#if defined(MINITSCRIPT_EVENTS)
				// events
				,
				TYPE_ON,
				TYPE_ONENABLED
			#endif
		};
		/**
		 * Constructor
		 * @param _module module name
		 * @param type type
		 * @param line line
		 * @param condition condition
		 * @param executableCondition executable condition
		 * @param conditionStatement condition statement
		 * @param conditionSyntaxTree condition syntax tree
		 * @param name name
		 * @param emitCondition emit condition
		 * @param statements statements
		 * @param syntaxTree syntax tree
		 * @param callableFunction callable function
		 * @param functionArguments function arguments
		 * @param rootScriptIdx root script index
		 */
		inline Script(
			const string& _module,
			Type type,
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
			// applies only for functions/stacklets
			bool callable,
			const vector<Argument>& arguments,
			int rootScriptIdx
		):
			_module(_module),
			type(type),
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
			arguments(arguments),
			rootScriptIdx(rootScriptIdx)
		{}

		/**
		 * @return statements
		 */
		inline const vector<Statement>& getStatements() const {
			return moduleStatements != nullptr?*moduleStatements:statements;
		}

		//
		string _module;
		Type type;
		int line;
		// condition, condition name or function/stacklet/callable name
		string condition;
		string executableCondition;
		Statement conditionStatement;
		SyntaxTreeNode conditionSyntaxTree;
		// if condition holds a condition, name is the additional condition name if given
		string name;
		bool emitCondition;
		vector<Statement> statements;
		vector<SyntaxTreeNode> syntaxTree;
		bool callable;
		vector<Argument> arguments;
		// modules
		int rootScriptIdx;
		// safe to use, also with modules
		vector<Statement> const * moduleStatements { nullptr };
	};

	static constexpr int SCRIPTIDX_NONE { -1 };
	static constexpr int LINE_NONE { -1 };
	static constexpr int STATEMENTIDX_NONE { -1 };
	static constexpr int STATEMENTIDX_FIRST { 0 };
	static constexpr int ARGUMENTIDX_NONE { -1 };
	static constexpr int SUBLINEIDX_NONE { -1 };

	MINITSCRIPT_STATIC_DLL_IMPEXT static const string METHOD_SCRIPTCALL;
	MINITSCRIPT_STATIC_DLL_IMPEXT static const string METHOD_SCRIPTCALLSTACKLET;
	MINITSCRIPT_STATIC_DLL_IMPEXT static const string METHOD_SCRIPTCALLBYINDEX;
	MINITSCRIPT_STATIC_DLL_IMPEXT static const string METHOD_SCRIPTCALLSTACKLETBYINDEX;
	MINITSCRIPT_STATIC_DLL_IMPEXT static const string METHOD_ENABLENAMEDCONDITION;
	MINITSCRIPT_STATIC_DLL_IMPEXT static const string METHOD_DISABLENAMEDCONDITION;

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
								argumentsString+= (argumentsString.empty() == false?", ":"") + string("\"") + escapeString(argument.value.getValueAsString()) + string("\"");
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

	/**
	 * Script state
	 */
	struct ScriptState {
		/**
		 * Block
		 */
		struct Block {
			enum Type { TYPE_NONE, TYPE_GLOBAL, TYPE_STACKLET, TYPE_FUNCTION, TYPE_FOR, TYPE_FORTIME, TYPE_IF, TYPE_SWITCH, TYPE_CASE, TYPE_TRY, TYPE_CATCH };
			/**
			 * Constructor
			 * @param type block type
			 * @param match match
			 * @param continueStatement continue statement
			 * @param breakStatement break statement
			 * @param catchStatement catch statement
			 * @param parameter switch variable / iteration function
			 */
			inline Block(
				Type type,
				bool match,
				const Statement* continueStatement,
				const Statement* breakStatement,
				const Statement* catchStatement,
				const Variable& parameter
			):
				type(type),
				match(match),
				continueStatement(continueStatement),
				breakStatement(breakStatement),
				catchStatement(catchStatement),
				parameter(parameter)
			{}
			//
			Type type;
			bool match;
			const Statement* continueStatement;
			const Statement* breakStatement;
			const Statement* catchStatement;
			Variable parameter;
		};
		enum ConditionType {
			SCRIPT,
			CONDITIONTYPE_FORTIME
		};
		inline ScriptState(int idx): idx(idx) {
		}
		int idx;
		int state { STATE_NONE };
		int lastState { STATE_NONE };
		StateMachineState* lastStateMachineState { nullptr };
		bool running { false };
		int scriptIdx { SCRIPTIDX_NONE };
		int statementIdx { STATEMENTIDX_NONE };
		int gotoStatementIdx { STATEMENTIDX_NONE };
		int64_t timeWaitStarted { TIME_NONE };
		int64_t timeWaitTime { TIME_NONE };
		unordered_map<string, Variable*> variables;
		unordered_map<int, int64_t> forTimeStarted;
		vector<Block> blockStack;
		// applies for functions only
		Variable returnValue;
	};

	//
	string scriptPathName;
	string scriptFileName;

	// modules
	bool _module { false };
	vector<string> modules;
	MinitScript* rootScript { this };
	MinitScript* parentScript { nullptr };

	//
	bool native { false };
	Context* context { nullptr };
	Library* library { nullptr };
	vector<Script> scripts;
	string nativeHash;
	vector<string> nativeModuleHashes;
	vector<Script> nativeScripts;
	unordered_map<string, int> nativeFunctions;
	vector<unique_ptr<ScriptState>> scriptStateStack;

	vector<string> parseErrors;
	vector<pair<int, string>> deferredInlineScriptCodes;

	int inlineFunctionIdx { 0 };
	int inlineStackletIdx { 0 };

	unique_ptr<MathMethods> minitScriptMath;

	SubStatement errorSubStatement;
	string errorMessage;

	#if defined(MINITSCRIPT_EVENTS)
		// events
		// root context variables
		vector<string> enabledNamedConditions;
		int64_t timeEnabledConditionsCheckLast { TIME_NONE };
		// deferred emit
		string deferredEmit;
		bool emitted { false };
	#endif

	int exceptionScriptIdx { STATEMENTIDX_NONE };
	SubStatement exceptionSubStatement;
	Variable exceptionThrowArgument;

	//
	int64_t dataTypesGCTime { -1ll };

	// functions/stacklets/callables defined by script itself
	unordered_map<string, int> functions;
	// registered methods
	unordered_map<string, Method*> methods;
	// registered state machine states
	unordered_map<int, StateMachineState*> stateMachineStates;
	// operators
	unordered_map<uint8_t, Method*> operators;
	//
	bool scriptValid { false };

	/**
	 * Escape string variable
	 * @param str string
	 * @return escaped string
	 */
	inline static const string escapeString(const string& str) {
		//
		auto result = str;
		const array<char, 11> escapeSequences = {'0', 'a', 'b', 'f', 'n', 'r', 't', 'v', 'U', '"'};
		for (const auto c: escapeSequences) {
			result = StringTools::replace(result, string("\\") + c, string("\\\\") + c);
		}
		//
		result = StringTools::replace(result, "\0", "\\0");
		result = StringTools::replace(result, "\a", "\\a");
		result = StringTools::replace(result, "\b", "\\b");
		result = StringTools::replace(result, "\f", "\\f");
		result = StringTools::replace(result, "\n", "\\n");
		result = StringTools::replace(result, "\r", "\\r");
		result = StringTools::replace(result, "\t", "\\t");
		result = StringTools::replace(result, "\v", "\\v");
		result = StringTools::replace(result, "\"", "\\\"");
		//
		string result2;
		auto lc = '\0';
		auto llc = '\0';
		for (auto i = 0; i < result.size(); i++) {
			//
			auto c = result[i];
			auto nc = i < result.size() - 1?result[i + 1]:'\0';
			if (c == '\\' && lc != '\\' && nc != '\\' && find(escapeSequences.begin(), escapeSequences.end(), nc) == escapeSequences.end()) {
				result2+= "\\\\";
			} else {
				result2+= c;
			}
			//
			auto lc = c;
			auto llc = lc;
		}
		//
		return result2;
	}

	/**
	 * Initialize native mini script
	 */
	virtual void initializeNative();

	/**
	 * Go to statement
	 * @param statement statement
	 */
	inline void gotoStatement(const Statement& statement) {
		setScriptStateState(MinitScript::STATEMACHINESTATE_NEXT_STATEMENT);
		getScriptState().gotoStatementIdx = statement.statementIdx;
	}

	/**
	 * Go to statement goto from given statement
	 * @param statement statement
	 */
	inline void gotoStatementGoto(const Statement& statement) {
		setScriptStateState(MinitScript::STATEMACHINESTATE_NEXT_STATEMENT);
		getScriptState().gotoStatementIdx = statement.gotoStatementIdx;
	}

	/**
	 * Execute state machine
	 */
	void executeStateMachine();

	/**
	 * Dump script state
	 * @param scriptState script state
	 * @param message message
	 */
	void dumpScriptState(ScriptState& scriptState, const string& message = string());

	/**
	 * @return has script state
	 */
	inline bool hasScriptState() {
		return rootScript->scriptStateStack.empty() == false;
	}

	/**
	 * @return get script state stack size
	 */
	inline int getScriptStateStackSize() {
		return rootScript->scriptStateStack.size();
	}

	/**
	 * Push a new script state
	 */
	inline void pushScriptState() {
		rootScript->scriptStateStack.push_back(make_unique<ScriptState>(rootScript->scriptStateStack.size()));
	}

	/**
	 * Pop script state
	 */
	inline void popScriptState() {
		if (hasScriptState() == false) return;
		auto& scriptState = getScriptState();
		// we need to delete references first
		unordered_set<string> deletedVariables;
		for (const auto& [variableName, variable]: scriptState.variables) {
			if (variable->isReference() == false) continue;
			deletedVariables.insert(variableName);
			delete variable;
		}
		// next ordinary variables
		for (const auto& [variableName, variable]: scriptState.variables) {
			if (deletedVariables.contains(variableName) == true) continue;
			delete variable;
		}
		scriptState.variables.clear();
		rootScript->scriptStateStack.erase(rootScript->scriptStateStack.begin() + rootScript->scriptStateStack.size() - 1);
	}

	/**
	 * @return is function/stacklet running
	 */
	inline bool isFunctionRunning() {
		// function?
		if (rootScript->scriptStateStack.size() > 1) return true;
		// stacklet?
		for (const auto& block: getRootScriptState().blockStack) {
			if (block.type == ScriptState::Block::TYPE_STACKLET) return true;
		}
		// nope
		return false;
	}

	/**
	 * Reset script execution state
	 * @param scriptIdx script index
	 * @param stateMachineState state machine state
	 */
	inline void resetScriptExecutationState(int scriptIdx, StateMachineStateId stateMachineState) {
		auto& scriptState = getScriptState();
		//
		#if defined(MINITSCRIPT_EVENTS)
			// events
			if (isFunctionRunning() == false) enabledNamedConditions.clear();
		#endif
		//
		scriptState.forTimeStarted.clear();
		scriptState.blockStack.clear();
		if (scriptIdx != SCRIPTIDX_NONE) {
			scriptState.blockStack.emplace_back(
				scripts[scriptIdx].type == Script::TYPE_FUNCTION?
					ScriptState::Block::TYPE_FUNCTION:
					ScriptState::Block::TYPE_GLOBAL,
				false,
				nullptr,
				nullptr,
				nullptr,
				Variable()
			);
		} else {
			scriptState.blockStack.emplace_back(
				ScriptState::Block::TYPE_NONE,
				false,
				nullptr,
				nullptr,
				nullptr,
				Variable()
			);
		}
		scriptState.scriptIdx = scriptIdx;
		scriptState.statementIdx = STATEMENTIDX_FIRST;
		scriptState.gotoStatementIdx = STATEMENTIDX_NONE;
		scriptState.timeWaitStarted = Time::getCurrentMillis();
		scriptState.timeWaitTime = 0LL;
		scriptState.returnValue.setNullValue();
		setScriptStateState(stateMachineState);
	}

	/**
	 * Reset stacklet script execution state
	 * @param scriptIdx script index
	 * @param stateMachineState state machine state
	 */
	inline void resetStackletScriptExecutationState(int scriptIdx, StateMachineStateId stateMachineState) {
		auto& scriptState = getScriptState();
		scriptState.blockStack.emplace_back(
			ScriptState::Block::TYPE_STACKLET,
			false,
			nullptr,
			nullptr,
			nullptr,
			Variable()
		);
		scriptState.scriptIdx = scriptIdx;
		scriptState.statementIdx = STATEMENTIDX_FIRST;
		scriptState.gotoStatementIdx = STATEMENTIDX_NONE;
		scriptState.returnValue.setNullValue();
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
		//
		garbageCollection();
		//
		auto& scriptState = getScriptState();
		for (auto& scriptState: rootScript->scriptStateStack) {
			scriptState->running = false;
		}
		//
		#if defined(MINITSCRIPT_EVENTS)
			// events
			if (isFunctionRunning() == false) timeEnabledConditionsCheckLast = TIME_NONE;
		#endif
		//
		resetScriptExecutationState(SCRIPTIDX_NONE, STATEMACHINESTATE_NONE);
	}

	/**
	 * @return has exception
	 */
	inline bool hasException() {
		return rootScript->exceptionSubStatement.statement != nullptr;
	}

	/**
	 * Set exception
	 * @param scriptIdx script index
	 * @param subStatement sub statement
	 * @param throwArgument throwArgument
	 */
	inline void setException(int scriptIdx, const MinitScript::SubStatement& subStatement, const Variable& throwArgument) {
		this->rootScript->exceptionScriptIdx = scriptIdx;
		this->rootScript->exceptionSubStatement = subStatement;
		this->rootScript->exceptionThrowArgument = throwArgument;
	}

	/**
	 * Unset exception
	 */
	inline void unsetException() {
		this->rootScript->exceptionScriptIdx = STATEMENTIDX_NONE;
		this->rootScript->exceptionSubStatement = SubStatement();
		this->rootScript->exceptionThrowArgument.unset();
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

	#if defined(MINITSCRIPT_EVENTS)
		/**
		 * @return if script has emitted a condition like error
		 */
		inline bool hasEmitted() {
			return emitted;
		}

		// events
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
	#endif

	/***
	 * Create lamda function for given variable
	 * @param variable variable
	 * @param arguments arguments
	 * @param functionScriptCode function script code
	 * @param lineIdx start line index of lamda function
	 * @param populateThis populate this variable, which applies to lamda member function of maps/objects
	 * @param statement statement
	 * @param nameHint name hint
	 */
	void createLamdaFunction(Variable& variable, const vector<string_view>& arguments, const string_view& functionScriptCode, int lineIdx, bool populateThis, const Statement& statement, const string& nameHint = string());

	/***
	 * Create stacklet for given variable
	 * @param variable variable
	 * @param scopeName scope name
	 * @param arguments arguments
	 * @param stackletScriptCode stacklet script code
	 * @param lineIdx start line index of lamda function
	 * @param statement statement
	 */
	void createStacklet(Variable& variable, const string& scopeName, const vector<string_view>& arguments, const string_view& stackletScriptCode, int lineIdx, const Statement& statement);

	/**
	 * Initialize array by initializer string
	 * @param scriptFileName script file name
	 * @param initializerString initializer string
	 * @param minitScript mini script
	 * @param scriptIdx script index
	 * @param statement statement
	 * @return initialized variable
	 */
	static const Variable initializeArray(const string& scriptFileName, const string_view& initializerString, MinitScript* minitScript, int scriptIdx, const Statement& statement);

	/**
	 * Initialize map/set by initializer string
	 * @param scriptFileName script file name
	 * @param initializerString initializer string
	 * @param minitScript mini script
	 * @param scriptIdx script index
	 * @param statement statement
	 * @return initialized variable
	 */
	static const Variable initializeMapSet(const string& scriptFileName, const string_view& initializerString, MinitScript* minitScript, int scriptIdx, const Statement& statement);

	/**
	 * Try garbage collection
	 */
	inline void tryGarbageCollection() {
		auto now = Time::getCurrentMillis();
		if (dataTypesGCTime == -1ll || now - dataTypesGCTime >= GARBAGE_COLLECTION_INTERVAL) {
			garbageCollection();
			dataTypesGCTime = now;
		}
	}

	/**
	 * Issue garbage collection
	 */
	void garbageCollection();

private:
	static constexpr bool VERBOSE { false };
	static constexpr bool VALIDATION { true };
	static constexpr int64_t GARBAGE_COLLECTION_INTERVAL { 1000ll };

	/**
	 * Shutdown RAII
	 */
	class ShutdownRAII {
		public:
			/**
			 * Constructor
			 * @param dataTypes data types
			 */
			inline ShutdownRAII(vector<DataType*>& dataTypes): dataTypes(dataTypes) {}

			/**
			 * Destructor
			 */
			inline ~ShutdownRAII() {
				for (const auto dataType: dataTypes) delete dataType;
				dataTypes.clear();
			}
		private:
			vector<DataType*>& dataTypes;
	};

	//
	MINITSCRIPT_STATIC_DLL_IMPEXT static const string OPERATOR_CHARS;
	MINITSCRIPT_STATIC_DLL_IMPEXT static vector<DataType*> dataTypes;
	MINITSCRIPT_STATIC_DLL_IMPEXT static ShutdownRAII shutdownRAII;

	/**
	 * Garbage collection data type
	 */
	struct GarbageCollectionDataType {
		/**
		 * Constructor
		 * @param dataType data type
		 * @param context script context
		 */
		inline GarbageCollectionDataType(
			DataType* dataType,
			DataType::ScriptContext* context):
			dataType(dataType),
			context(context) {
			//
		}
		//
		DataType* dataType;
		DataType::ScriptContext* context;
	};

	//
	vector<GarbageCollectionDataType> garbageCollectionDataTypes;
	unordered_map<VariableType, DataType::ScriptContext*> garbageCollectionScriptContextsByDataType;
	unordered_set<int> garbageCollectionDataTypesIndices;

	/**
	 * Parser argument
	 */
	struct ParserArgument {
		/**
		 * Constructor
		 * @param argument argument
		 * @param subLineIdx sub line index
		 */
		inline ParserArgument(
			const string_view& argument,
			int subLineIdx
		):
			argument(argument),
			subLineIdx(subLineIdx)
		{}
		//
		string_view argument;
		int subLineIdx;
	};

	/**
	 * Parse script code into this MinitScript instance
	 * @param scriptCode script code
	 * @param _module module name
	 * @param lineIdxOffset line index offset
	 * @return success
	 */
	bool parseScriptInternal(const string& scriptCode, const string& _module = string(), int lineIdxOffset = 0);


	/**
	 * Execute next statement
	 */
	void executeNextStatement();

	/**
	 * Get next statement from script code
	 * @param scriptFileName script file name
	 * @param scriptCode script code
	 * @param i character index
	 * @param line line
	 * @param statement statement
	 * @return success
	 */
	bool getNextStatement(const string& scriptFileName, const string& scriptCode, int& i, int& line, string& statement);

	/**
	 * Parse a statement
	 * @param executableStatement executable statement
	 * @param methodName method name
	 * @param arguments arguments
	 * @param statement statment
	 * @return success
	 */
	bool parseStatement(const string_view& executableStatement, string_view& methodName, vector<ParserArgument>& arguments, const Statement& statement);

	/**
	 * Execute a statement
	 * @param syntaxTree syntax tree
	 * @param statement statement
	 * @return return value as variable
	 */
	Variable executeStatement(const SyntaxTreeNode& syntaxTree, const Statement& statement);

	/**
	 * Create statement syntax tree
	 * @param scriptFileName script file name
	 * @param scriptIdx script index
	 * @param methodName method name
	 * @param arguments arguments
	 * @param statement statement
	 * @param syntaxTree syntax tree
	 * @param subLineIdx sub line index
	 * @return success
	 */
	bool createStatementSyntaxTree(const string& scriptFileName, int scriptIdx, const string_view& methodName, const vector<ParserArgument>& arguments, const Statement& statement, SyntaxTreeNode& syntaxTree, int subLineIdx = 0);

	/**
	 * Return stacklet scope script index
	 * @param scriptIdx stacklet script index
	 * @return stacklet scope script index
	 */
	int getStackletScopeScriptIdx(int scriptIdx);

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
	 * @param setVariableStatement set variable statement, where we disable subscript and property operators
	 * @param memberAccessPropertyStatement member access property statement
	 */
	const string doStatementPreProcessing(const string& processedStatement, const Statement& statement, bool setVariableStatement = false, bool memberAccessPropertyStatement = false);

	/**
	 * Get access operator left and right indices
	 * @param variableStatement variable statement
	 * @param callerMethod caller method
	 * @param accessOperatorLeftIdx access operator left idx
	 * @param accessOperatorRightIdx access operator right idx
	 * @param subStatement sub statement
	 * @param startIdx startIdx
	 */
	bool getVariableAccessOperatorLeftRightIndices(const string& variableStatement, const string& callerMethod, string::size_type& accessOperatorLeftIdx, string::size_type& accessOperatorRightIdx, const SubStatement* subStatement = nullptr, int startIdx = 0);

	/**
	 * Evaluate access
	 * @param variableStatement variable statement
	 * @param callerMethod caller method
	 * @param arrayAccessOperatorLeftIdx array access operator left idx
	 * @param arrayAccessOperatorRightIdx array access operator right idx
	 * @param arrayIdx array index
	 * @param key map key
	 * @param subStatement sub statement
	 */
	bool evaluateAccess(const string& variableStatement, const string& callerMethod, string::size_type& arrayAccessOperatorLeftIdx, string::size_type& arrayAccessOperatorRightIdx, int64_t& arrayIdx, string& key, const SubStatement* subStatement = nullptr);

	/**
	 * Returns pointer of variable with given name or nullptr
	 * @param variablePtr pointer to variable
	 * @param variableStatement variable statement
	 * @param callerMethod caller method
	 * @param parentVariable parent variable
	 * @param arrayIdx array index whereas there is ARRAYIDX_ADD for [] or ARRAYIDX_NONE for no array access
	 * @param key key
	 * @param setAccessBool set access bool which returns one of SETACCESSBOOL_NONE, *_TRUE, *_FALSE
	 * @param subStatement optional sub statement the variable is read in
	 * @param expectVariable expect variable which controls verbosity
	 * @return pointer to variable
	 */
	Variable* evaluateVariableAccessIntern(Variable* variablePtr, const string& variableStatement, const string& callerMethod, Variable*& parentVariable, int64_t& arrayIdx, string& key, int& setAccessBool, const SubStatement* subStatement = nullptr, bool expectVariable = true);

	/**
	 * Returns pointer of variable with given name or nullptr
	 * @param variableStatement variable statement
	 * @param callerMethod caller method
	 * @param variableName variable name
	 * @param parentVariable parent variable
	 * @param arrayIdx array index whereas there is ARRAYIDX_ADD for [] or ARRAYIDX_NONE for no array access
	 * @param key key
	 * @param setAccessBool set access bool which returns one of SETACCESSBOOL_NONE, *_TRUE, *_FALSE
	 * @param subStatement optional sub statement the variable is read in
	 * @param expectVariable expect variable which controls verbosity
	 * @param global use global context instead of current context
	 * @return pointer to variable
	 */
	inline Variable* getVariableIntern(const string& variableStatement, const string& callerMethod, string& variableName, Variable*& parentVariable, int64_t& arrayIdx, string& key, int& setAccessBool, const SubStatement* subStatement = nullptr, bool expectVariable = true, bool global = false) {
		// determine variable name
		{
			auto dotIdx = string::npos;
			auto squareBracketIdx = string::npos;
			auto lc = '\0';
			for (auto i = 0; i < variableStatement.size(); i++) {
				auto c = variableStatement[i];
				if (c == '.') {
					if (dotIdx == string::npos) dotIdx = i;
				} else
				if (c == '[') {
					if (squareBracketIdx == string::npos) squareBracketIdx = i;
				} else
				if (lc == ':' && c == ':') {
					dotIdx = string::npos;
					squareBracketIdx = string::npos;
				}
				//
				lc = c;
			}
			if (dotIdx == string::npos) dotIdx = variableStatement.size();
			if (squareBracketIdx == string::npos) squareBracketIdx = variableStatement.size();
			variableName = StringTools::substring(
				variableStatement,
				0,
				dotIdx < squareBracketIdx?
					dotIdx:
					squareBracketIdx
			);
		}
		// retrieve variable from script state
		Variable* variablePtr = nullptr;
		const auto& scriptState = global == false?getScriptState():getRootScriptState();
		auto variableIt = scriptState.variables.find(variableName);
		if (variableIt == scriptState.variables.end()) {
			if (expectVariable == true) {
				Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + " does not exist");
			}
			return nullptr;
		} else {
			variablePtr = variableIt->second;
		}
		//
		return evaluateVariableAccessIntern(variablePtr, variableStatement, callerMethod, parentVariable, arrayIdx, key, setAccessBool, subStatement, expectVariable);
	}

	/**
	 * Set variable internal
	 * @param variableStatement variable statement
	 * @param parentVariable parent variable
	 * @param variablePtr variable pointer
	 * @param arrayIdx array index
	 * @param key key
	 * @param variable variable
	 * @param subStatement optional sub statement the variable is written in
	 * @param createReference optional flag for creating variable references
	 */
	void setVariableInternal(const string& variableStatement, Variable* parentVariable, Variable* variablePtr, int64_t arrayIdx, const string& key, const Variable& variable, const SubStatement* subStatement = nullptr, bool createReference = false);

	/**
	 * Evaluate given statement without executing preprocessor run
	 * @param statement statement
	 * @param executableStatement executable statement
	 * @param returnValue return value
	 * @param pushScriptState push script state
	 * @return success
	 */
	bool evaluateInternal(const string& statement, const string& executableStatement, Variable& returnValue, bool pushScriptState = true);

	/**
	 * Call function
	 * @param scriptIdx script index
	 * @param arguments argument values
	 * @param returnValue return value
	 * @param pushScriptState push script state
	 * @return success
	 */
	bool call(int scriptIdx, span<Variable>& arguments, Variable& returnValue, bool pushScriptState);

	/**
	 * Call function
	 * @param function function
	 * @param arguments argument values
	 * @param returnValue return value
	 * @param pushScriptState push script state
	 * @return success
	 */
	inline bool call(const string& function, span<Variable>& arguments, Variable& returnValue, bool pushScriptState) {
		// lookup function
		auto functionIt = functions.find(function);
		if (functionIt == functions.end()) {
			return false;
		}
		//
		auto scriptIdx = functionIt->second;
		// call it
		return call(scriptIdx, arguments, returnValue, pushScriptState);
	}

	/**
	  * Initialize variable
	  * @param variable variable
	  * @return initialized variable
	  */
	const Variable initializeVariable(const Variable& variable);

	/**
	 * Deescape string
	 * @param str string
	 * @param statement statement
	 * @return deescaped string
	 */
	inline const string deescape(const string_view& str, const Statement& statement) {
		string deescapedStr;
		auto lc = '\0';
		for (auto i = 0; i < str.size(); i++) {
			auto c = str[i];
			if (c != '\\' || lc == '\\') {
				// escape sequences
				//	see: https://en.cppreference.com/w/cpp/language/escape
				// \0 null character
				if (lc == '\\' && c == '0') deescapedStr+= '\0'; else
				// \a audible bell
				if (lc == '\\' && c == 'a') deescapedStr+= '\a'; else
				// \b backspace
				if (lc == '\\' && c == 'b') deescapedStr+= '\b'; else
				// \f form feed - new page
				if (lc == '\\' && c == 'f') deescapedStr+= '\f'; else
				// \n line feed - new line
				if (lc == '\\' && c == 'n') deescapedStr+= '\n'; else
				// \r carriage return
				if (lc == '\\' && c == 'r') deescapedStr+= '\r'; else
				// \t horizontal tab
				if (lc == '\\' && c == 't') deescapedStr+= '\t'; else
				// \v vertical tab
				if (lc == '\\' && c == 'v') deescapedStr+= '\v'; else
				// unicode \Unnnnnnnn
				if (lc == '\\' && c == 'U') {
					string unicodeHexadecimalSequence;
					auto j = 0;
					auto valid = true;
					for (i++; i < str.size() && j < 8; i++ && j++) {
						c = str[i];
						unicodeHexadecimalSequence+= c;
						if (((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) == false) break;
					}
					i--;
					if (valid == false || j != 8) {
						Console::printLine(getStatementInformation(statement) + ": Invalid hexadecimal unicode character sequence: " + unicodeHexadecimalSequence);
					} else {
						Character::appendToString(deescapedStr, Hex::decodeInt(unicodeHexadecimalSequence));
					}
				} else
					deescapedStr+= c;
				//
				lc = '\0';
				continue;
			}
			lc = c;
		}
		return deescapedStr;
	}

	/**
	 * Returns if a given string is a lambda function
	 * @param candidate candidate
	 * @param arguments arguments
	 * @param functionScriptCode function script code
	 * @param lineIdx start line index
	 * @return if candidate is a lambda function
	 */
	inline static bool viewIsLamdaFunction(const string_view& candidate, vector<string_view>& arguments, string_view& functionScriptCode, int& lineIdx) {
		if (candidate.size() == 0) return false;
		//
		auto i = 0;
		// (
		if (candidate[i++] != '(') return false;
		// spaces
		for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
		if (i >= candidate.size()) return false;
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
			if (argumentStartIdx != string::npos && Character::isAlphaNumeric(candidate[i]) == false && c != '_') {
				return false;
			}
		}
		//
		if (i >= candidate.size()) return false;
		// spaces
		for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
		if (i >= candidate.size()) return false;
		// -
		if (candidate[i++] != '-') return false;
		//
		if (i >= candidate.size()) return false;
		// >
		if (candidate[i++] != '>') return false;
		// spaces
		for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
		if (i >= candidate.size()) return false;
		//
		if (candidate[i++] != '{') return false;
		//
		for (auto j = 0; j < i - 1; j++) {
			if (candidate[j] == '\n') lineIdx++;
		}
		//
		auto scriptCodeStartIdx = i;
		auto scriptCodeEndIdx = string::npos;
		//
		for (auto j = candidate.size() - 1; j > i; j--) {
			if (candidate[j] == '}') {
				scriptCodeEndIdx = j;
				break;
			} else
			if (Character::isSpace(candidate[j]) == false) {
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
	 * Returns if a given string is a stacklet
	 * @param candidate candidate
	 * @param arguments arguments
	 * @param stackletScriptCode stacklet script code
	 * @param lineIdx start line index
	 * @return if candidate is a stacklet function
	 */
	inline static bool viewIsStacklet(const string_view& candidate, vector<string_view>& arguments, string_view& stackletScriptCode, int& lineIdx) {
		if (candidate.size() == 0) return false;
		//
		auto i = 0;
		// spaces
		for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
		if (i >= candidate.size()) return false;
		// -
		if (candidate[i++] != '-') return false;
		//
		if (i >= candidate.size()) return false;
		// >
		if (candidate[i++] != '>') return false;
		// spaces
		for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
		if (i >= candidate.size()) return false;
		//
		if (candidate[i++] != '{') return false;
		//
		for (auto j = 0; j < i - 1; j++) {
			if (candidate[j] == '\n') lineIdx++;
		}
		//
		auto scriptCodeStartIdx = i;
		auto scriptCodeEndIdx = string::npos;
		//
		for (auto j = candidate.size() - 1; j > i; j--) {
			if (candidate[j] == '}') {
				scriptCodeEndIdx = j;
				break;
			} else
			if (Character::isSpace(candidate[j]) == false) {
				return false;
			}
		}
		//
		if (scriptCodeEndIdx == string::npos) return false;
		//
		stackletScriptCode = string_view(&candidate[scriptCodeStartIdx], scriptCodeEndIdx - scriptCodeStartIdx);
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
			if (squareBracketCount == 0 && Character::isAlphaNumeric(c) == false && c != '_' && c != '.' && c != ':') {
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

	/**
	 * Returns if a given key candidate is marked as private by head '-'
	 * @param candidate candidate
	 * @return if key candidate is marked as private
	 */
	static bool viewIsKeyPrivate(const string_view& candidate);

	/**
	 * Returns private key
	 * @param candidate candidate
	 * @return private key
	 */
	static const string_view viewGetPrivateKey(const string_view& candidate);

	/**
	 * Returns if a given string is a string literal
	 * @param candidate candidate
	 * @return if string is a string literal
	 */
	inline static bool viewIsStringLiteral(const string_view& candidate) {
		// we need a " or ' and a " or ' :DDD
		if (candidate.size() < 2) return false;
		auto i = 0;
		// check for head quote
		if (candidate[i] != '"' && candidate[i] != '\'') return false;
		// detect quote
		auto quote = candidate[i++];
		// check for tail quote
		if (candidate[candidate.size() - 1] != quote) return false;
		//
		auto lc = '\0';
		for (; i < candidate.size() - 1; i++) {
			auto c = candidate[i];
			if (c == quote && lc != '\\') return false;
			lc = c;
		}
		//
		return true;
	}

	/**
	 * Dequote a string
	 * @param str string
	 * @return dequoted string
	 */
	inline static string_view dequote(const string_view& str) {
		return StringTools::viewSubstring(str, 1, str.size() - 1);
	}

	/**
	 * Returns if a given string is a array/map/set initializer
	 * @param candidate candidate
	 * @return if string is a array/map/set initializer
	 */
	inline static bool viewIsInitializer(const string_view& candidate) {
		return
			(StringTools::viewStartsWith(candidate, "[") == true && StringTools::viewEndsWith(candidate, "]") == true) ||
			(StringTools::viewStartsWith(candidate, "{") == true && StringTools::viewEndsWith(candidate, "}") == true);

	}

	/**
	 * Returns if a given string is a method/function call
	 * @param candidate candidate
	 * @return if string is a method/function call
	 */
	inline static bool viewIsCall(const string_view& candidate) {
		// TODO: improve me!
		auto leftBracketIdx = candidate.find('(');
		auto rightBracketIdx = candidate.rfind(')');
		return leftBracketIdx > 0 && rightBracketIdx > leftBracketIdx;
	}

	/**
	 * Set variable recursively to be a constant
	 * @param variable variable
	 */
	static void setConstantInternal(Variable& variable);

	/**
	 * Set variable recursively to be a non constant
	 * @param variable variable
	 */
	static void unsetConstantInternal(Variable& variable);

public:
	/**
	 * Initialize
	 */
	static void initialize();

	/**
	 * Set variable recursively to be a constant
	 * @param variable variable
	 */
	inline static void setConstant(Variable& variable) {
		if (variable.isConstant() == true) return;
		setConstantInternal(variable);
	}

	/**
	 * Set variable recursively to be a non constant
	 * @param variable variable
	 */
	inline static void unsetConstant(Variable& variable) {
		if (variable.isConstant() == false) return;
		unsetConstantInternal(variable);
	}

	/**
	 * Return data type script context
	 * @param type data type
	 * @return data type script context
	 */
	inline DataType::ScriptContext* getDataTypeScriptContext(VariableType type) {
		auto garbageCollectionScriptContextsByDataTypeIt = garbageCollectionScriptContextsByDataType.find(type);
		if (garbageCollectionScriptContextsByDataTypeIt != garbageCollectionScriptContextsByDataType.end()) {
			return garbageCollectionScriptContextsByDataTypeIt->second;
		}
		return nullptr;
	}

	/**
	 * @return context
	 */
	inline Context* getContext() {
		return context;
	}

	/**
	 * Set context
	 * @param context context
	 */
	inline void setContext(Context* context) {
		this->context = context;
	}

	/**
	 * @return library
	 */
	inline Library* getLibrary() {
		return library;
	}

	/**
	 * Set library
	 * @param library library
	 */
	inline void setLibrary(Library* library) {
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
	 * Decode operator
	 * @param arguments arguments
	 * @param operatorValueIdx operator value index
	 * @param defaultOperatorString default operator string
	 * @return operator string
	 */
	inline static const string decodeOperator(const span<MinitScript::Variable>& arguments, int operatorValueIdx, const string& defaultOperatorString) {
		//
		int64_t operatorValue;
		if (MinitScript::getIntegerValue(arguments, operatorValueIdx, operatorValue) == false) return defaultOperatorString;
		//
		string result;
		auto c1 = (operatorValue & 255);
		auto c2 = ((operatorValue >> 8) & 255);
		if (c1 != 0ll) result+= (char)c1;
		if (c2 != 0ll) result+= (char)c2;
		//
		return result;
	}

	/**
	 * @return error message
	 */
	const string& getErrorMessage() {
		return errorMessage;
	}

	/**
	 * @return error sub statement
	 */
	const SubStatement& getErrorSubStatement() {
		return errorSubStatement;
	}

	/**
	 * Complain about method usage
	 * @param methodName method mame
	 * @param subStatement sub statement
	 */
	void complain(const string& methodName, const SubStatement& subStatement);

	/**
	 * Complain about method usage
	 * @param methodName method mame
	 * @param subStatement sub statement
	 * @param message message
	 */
	void complain(const string& methodName, const SubStatement& subStatement, const string& message);

	/**
	 * Complain about operator usage
	 * @param methodName method mame
	 * @param operatorString operator string
	 * @param subStatement sub statement
	 */
	void complainOperator(const string& methodName, const string& operatorString, const SubStatement& subStatement);

	/**
	 * Complain about operator usage
	 * @param methodName method mame
	 * @param operatorString operator string
	 * @param subStatement sub statement
	 * @param message message
	 */
	void complainOperator(const string& methodName, const string& operatorString, const SubStatement& subStatement, const string& message);

	/**
	 * @return data types
	 */
	inline static const vector<DataType*>& getDataTypes() {
		return MinitScript::dataTypes;
	}

	/**
	 * Returns data type by class name or nullptr
	 * @param className class name
	 * @return data type
	 */
	inline static DataType* getDataTypeByClassName(const string& className) {
		for (const auto dataType: MinitScript::dataTypes) {
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
	_FORBID_CLASS_COPY(MinitScript)

	/**
	 * Default constructor
	 */
	MinitScript();

	/**
	 * Destructor
	 */
	virtual ~MinitScript();

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
	 * @return if this MinitScript instance is a module
	 */
	inline bool isModule() {
		return _module;
	}

	/**
	 * @return modules in use
	 */
	inline const vector<string>& getModules() {
		return modules;
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
	 * @return native module script hashes
	 */
	inline const vector<string>& getNativeModuleHashes() {
		return nativeModuleHashes;
	}
	/**
	 * Initialize native module
	 * @param parentScript parent Minit Script instance
	 */
	virtual void initializeNativeModule(MinitScript* parentScript);

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
	inline const vector<Script>& getScripts() {
		return scripts;
	}

	/**
	 * @return root script state
	 */
	inline ScriptState& getRootScriptState() {
		return *(rootScript->scriptStateStack[0].get());
	}

	/**
	 * @return script state
	 */
	inline ScriptState& getScriptState() {
		return *(rootScript->scriptStateStack[rootScript->scriptStateStack.size() - 1].get());
	}

	/**
	 * @return math methods
	 */
	inline MathMethods* getMathMethods() {
		return rootScript->minitScriptMath.get();
	}

	/**
	 * Start error script
	 */
	inline void startErrorScript() {
		#if defined(MINITSCRIPT_EVENTS)
			if (hasCondition("error") == true) {
				// events
				emit("error");
			} else {
				//
				_throw("An error occurred");
			}
		#else
			//
			_throw("An error occurred");
		#endif
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
	 * Unregister variables
	 */
	virtual void unregisterVariables();

	/**
	 * Get statement sub line index
	 * @param statement statement
	 * @param idx index
	 * @return sub line index
	 */
	inline int getStatementSubLineIdx(const string& statement, int idx) {
		auto subLineIdx = 0;
		for (auto i = 0; i < statement.size() && i <= idx; i++) {
			if (statement[i] == '\n') subLineIdx++;
		}
		return subLineIdx;
	}

	/**
	 * Return statement information
	 * @param statement statement
	 * @param subLineIdx sub line index
	 * @return statement information
	 */
	inline const string getStatementInformation(const Statement& statement, int subLineIdx = -1) {
		//
		auto statementCode = statement.statement;
		auto statementLine = statement.line;
		if (subLineIdx != -1) {
			auto statementCodeLines = StringTools::tokenize(statementCode, "\n", true);
			if (subLineIdx >= 0 && subLineIdx < statementCodeLines.size()) {
				statementCode = statementCodeLines[subLineIdx];
				statementLine+= subLineIdx;
			}
		}
		//
		return statement.fileName + ":" + to_string(statementLine) +  ": " + statementCode;
	}

	/**
	 * Return sub statement information
	 * @param subStatement sub statement
	 * @return sub statement information
	 */
	inline const string getSubStatementInformation(const SubStatement& subStatement) {
		return getStatementInformation(*subStatement.statement, subStatement.subLineIdx);
	}

	/**
	 * Get arguments information
	 * @param methodName method name
	 * @return arguments information
	 */
	inline const string getArgumentsInformation(const string& methodName) {
		auto scriptMethod = rootScript->getMethod(methodName);
		if (scriptMethod == nullptr) {
			Console::printLine("MinitScript::getArgumentInformation(): method not found: " + methodName);
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
			case(OPERATOR_SUBSCRIPT): return "[]";
			case(OPERATOR_MEMBERACCESS_PROPERTY): return ".";
			case(OPERATOR_MEMBERACCESS_EXECUTE): return "->";
			case(OPERATOR_POSTFIX_INCREMENT): return "++";
			case(OPERATOR_POSTFIX_DECREMENT): return "--";
			case(OPERATOR_PREFIX_INCREMENT): return "++";
			case(OPERATOR_PREFIX_DECREMENT): return "--";
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
	 * Is given candidate a operator string
	 * @param candidate candidate
	 * @return operator
	 */
	inline static bool isOperator(const string& candidate) {
		for (int i = OPERATOR_NONE + 1; i < OPERATOR_MAX; i++) {
			if (candidate == getOperatorAsString(static_cast<Operator>(i))) return true;
		}
		return false;
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
	 * Checks if left and right operator arguments have given type
	 * @param arguments arguments
	 * @param type type
	 * @return has type
	 */
	inline static bool hasTypeForOperatorArguments(const span<Variable>& arguments, VariableType type) {
		for (auto i = 0; i < arguments.size() - (arguments.size() == 3?1:0); i++) {
			if (arguments[i].getType() == type) return true;
		}
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
	 * Get function value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param function function
	 * @param scriptIdx script index
	 * @param optional optional
	 * @return success
	 */
	inline static bool getFunctionValue(const span<Variable>& arguments, int idx, string& function, int& scriptIdx, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		return argument.getFunctionValue(function, scriptIdx, optional);
	}

	/**
	 * Get stacklet value from given variable
	 * @param arguments arguments
	 * @param idx argument index
	 * @param stacklet stacklet
	 * @param scriptIdx script index
	 * @param optional optional
	 * @return success
	 */
	inline static bool getStackletValue(const span<Variable>& arguments, int idx, string& stacklet, int& scriptIdx, bool optional = false) {
		if (idx >= arguments.size()) return optional;
		const auto& argument = arguments[idx];
		return argument.getStackletValue(stacklet, scriptIdx, optional);
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
	inline bool isVariableAccess(const string& candidate, const SubStatement* subStatement = nullptr) {
		if (candidate.size() < 2) {
			Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + candidate + ": empty variable statement");
			return false;
		}
		auto i = 0;
		if (candidate[i++] != '$') {
			Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + candidate + ": variable statement must begin with an $");
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
			if (squareBracketCount == 0 && Character::isAlphaNumeric(c) == false && c != '_' && c != '.' && c != ':') {
				Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + candidate + ": invalid character in variable statement: '" + c + "'");
				return false;
			}
		}
		if (candidate.size() == 2 && string_view(candidate) == string_view("$$", 2)) {
			Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + candidate + ": variable statement must not be $$");
			return false;
		}
		if (candidate.size() == 7 && string_view(candidate) == string_view("$GLOBAL", 7)) {
			Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + candidate + ": variable statement must not be $GLOBAL");
			return false;
		}
		return true;
	}

	/**
	 * Returns if variable determined by given variable statement exists
	 * @param variableStatement variable statement
	 * @param subStatement optional sub statement the variable is read in
	 * @return variable exists
	 */
	inline bool hasVariable(const string& variableStatement, const SubStatement* subStatement = nullptr) {
		//
		string variableName;
		// global accessor
		string globalVariableStatement;
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$$.", 3)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 3);
		} else
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$GLOBAL.", 8)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 8);
		}
		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		auto variablePtr = getVariableIntern(globalVariableStatement.empty() == true?variableStatement:globalVariableStatement, __FUNCTION__, variableName, parentVariable, arrayIdx, key, setAccessBool, subStatement, false, globalVariableStatement.empty() == false);
		// set '.' operator
		if (setAccessBool != SETACCESSBOOL_NONE) {
			return true;
		} else
		// we have a pointer to a ordinary variable
		if (variablePtr != nullptr) {
			return true;
		}
		//
		return false;
	}

	/**
	 * Returns variable determined by given variable statement optimized for method argument usage
	 * @param variableStatement variable statement
	 * @param subStatement optional sub statement the variable is read in
	 * @return variable
	 */
	inline const Variable getMethodArgumentVariable(const string& variableStatement, const SubStatement* subStatement = nullptr) {
		//
		if (isVariableAccess(variableStatement, subStatement) == false) return Variable();
		//
		string variableName;
		// global accessor
		string globalVariableStatement;
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$$.", 3)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 3);
		} else
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$GLOBAL.", 8)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 8);
		}

		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		auto variablePtr = getVariableIntern(globalVariableStatement.empty() == true?variableStatement:globalVariableStatement, __FUNCTION__, variableName, parentVariable, arrayIdx, key, setAccessBool, subStatement, true, globalVariableStatement.empty() == false);
		// set '.' operator
		if (setAccessBool != SETACCESSBOOL_NONE) {
			return Variable(setAccessBool == SETACCESSBOOL_TRUE);
		} else
		// we have a pointer to a ordinary variable
		if (variablePtr != nullptr) {
			// if we return any variable we can safely remove the constness, a reference can of course keep its constness
			auto variable = Variable::createMethodArgumentVariable(variablePtr);
			if (variable.isReference() == false) variable.unsetConstant();
			return variable;
		} else {
			// nothing to return
			return Variable();
		}
	}

	/**
	 * Returns variable determined by given variable statement and variable pointer optimized for method argument usage
	 * @param variablePtr variable pointer
	 * @param variableStatement variable statement
	 * @param subStatement optional sub statement the variable is read in
	 * @return variable
	 */
	inline const Variable getMethodArgumentVariable(Variable* variablePtr, const string& variableStatement, const SubStatement* subStatement = nullptr) {
		//
		if (isVariableAccess(variableStatement, subStatement) == false) return Variable();
		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		variablePtr = evaluateVariableAccessIntern(variablePtr, variableStatement, __FUNCTION__, parentVariable, arrayIdx, key, setAccessBool, subStatement, true);
		// set '.' operator
		if (setAccessBool != SETACCESSBOOL_NONE) {
			return Variable(setAccessBool == SETACCESSBOOL_TRUE);
		} else
		// we have a pointer to a ordinary variable
		if (variablePtr != nullptr) {
			// if we return any variable we can safely remove the constness, a reference can of course keep its constness
			auto variable = Variable::createMethodArgumentVariable(variablePtr);
			if (variable.isReference() == false) variable.unsetConstant();
			return variable;
		} else {
			// nothing to return
			return Variable();
		}
	}

	/**
	 * Returns variable determined by given variable statement
	 * @param variableStatement variable statement
	 * @param subStatement optional sub statement the variable is read in
	 * @param createReference optional flag for creating variable references
	 * @return variable
	 */
	inline const Variable getVariable(const string& variableStatement, const SubStatement* subStatement = nullptr, bool createReference = false) {
		//
		if (isVariableAccess(variableStatement, subStatement) == false) return Variable();
		//
		string variableName;
		// global accessor
		string globalVariableStatement;
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$$.", 3)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 3);
		} else
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$GLOBAL.", 8)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 8);
		}

		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		auto variablePtr = getVariableIntern(globalVariableStatement.empty() == true?variableStatement:globalVariableStatement, __FUNCTION__, variableName, parentVariable, arrayIdx, key, setAccessBool, subStatement, true, globalVariableStatement.empty() == false);
		// set '.' operator
		if (setAccessBool != SETACCESSBOOL_NONE) {
			return Variable(setAccessBool == SETACCESSBOOL_TRUE);
		} else
		// we have a pointer to a ordinary variable
		if (variablePtr != nullptr) {
			// if we return any variable we can safely remove the constness, a reference can of course keep its constness
			auto variable = createReference == false?Variable::createNonReferenceVariable(variablePtr):Variable::createReferenceVariable(variablePtr);
			if (createReference == false) variable.unsetConstant();
			return variable;
		} else {
			// nothing to return
			return Variable();
		}
	}

	/**
	 * Returns variable determined by given variable statement and variable pointer
	 * @param variablePtr variable pointer
	 * @param variableStatement variable statement
	 * @param subStatement optional sub statement the variable is read in
	 * @param createReference optional flag for creating variable references
	 * @return variable
	 */
	inline const Variable getVariable(Variable* variablePtr, const string& variableStatement, const SubStatement* subStatement = nullptr, bool createReference = false) {
		//
		if (isVariableAccess(variableStatement, subStatement) == false) return Variable();
		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		variablePtr = evaluateVariableAccessIntern(variablePtr, variableStatement, __FUNCTION__, parentVariable, arrayIdx, key, setAccessBool, subStatement, true);
		// set '.' operator
		if (setAccessBool != SETACCESSBOOL_NONE) {
			return Variable(setAccessBool == SETACCESSBOOL_TRUE);
		} else
		// we have a pointer to a ordinary variable
		if (variablePtr != nullptr) {
			// if we return any variable we can safely remove the constness, a reference can of course keep its constness
			auto variable = createReference == false?Variable::createNonReferenceVariable(variablePtr):Variable::createReferenceVariable(variablePtr);
			if (createReference == false) variable.unsetConstant();
			return variable;
		} else {
			// nothing to return
			return Variable();
		}
	}

	/**
	 * Unsets variable determined by given variable statement and variable pointer
	 * @param variablePtr variable pointer
	 * @param variableStatement variable statement
	 * @param subStatement optional sub statement the variable is read in
	 * @param createReference optional flag for creating variable references
	 * @return variable
	 */
	inline void unsetVariable(Variable* variablePtr, const string& variableStatement, const SubStatement* subStatement = nullptr) {
		//
		if (isVariableAccess(variableStatement, subStatement) == false) return;
		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		variablePtr = evaluateVariableAccessIntern(variablePtr, variableStatement, __FUNCTION__, parentVariable, arrayIdx, key, setAccessBool, subStatement, true);
		// set '.' operator
		if (setAccessBool != SETACCESSBOOL_NONE) {
			return;
		} else
		// we have a pointer to a ordinary variable
		if (variablePtr != nullptr) {
			//
			variablePtr->unset();
		}
	}

	/**
	 * Unsets variable determined by given variable statement
	 * @param variableStatement variable statement
	 * @param subStatement optional sub statement the variable is read in
	 */
	inline void unsetVariable(const string& variableStatement, const SubStatement* subStatement = nullptr) {
		//
		if (isVariableAccess(variableStatement, subStatement) == false) return;
		//
		string variableName;
		// global accessor
		string globalVariableStatement;
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$$.", 3)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 3);
		} else
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$GLOBAL.", 8)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 8);
		}

		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		auto variablePtr = getVariableIntern(globalVariableStatement.empty() == true?variableStatement:globalVariableStatement, __FUNCTION__, variableName, parentVariable, arrayIdx, key, setAccessBool, subStatement, true, globalVariableStatement.empty() == false);
		// set '.' operator
		if (setAccessBool != SETACCESSBOOL_NONE) {
			// no op
		} else
		// we have a pointer to a ordinary variable
		if (variablePtr != nullptr) {
			variablePtr->unset();
		}
	}

	/**
	 * Set constant by given variable statement and variable
	 * @param variableStatement variable statement
	 * @param variable variable
	 */
	inline void setConstant(const string& variableStatement, const Variable& variable) {
		auto constVariable = variable;
		setConstant(constVariable);
		setVariable(variableStatement, constVariable);
	}

	/**
	 * Set variable by given variable statement and variable
	 * @param variableStatement variable statement
	 * @param variable variable
	 * @param subStatement optional sub statement the variable is written in
	 * @param createReference optional flag for creating variable references
	 */
	inline void setVariable(const string& variableStatement, const Variable& variable, const SubStatement* subStatement = nullptr, bool createReference = false) {
		//
		if (isVariableAccess(variableStatement, subStatement) == false) return;
		//
		string variableName;
		// global accessor
		string globalVariableStatement;
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$$.", 3)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 3);
		} else
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$GLOBAL.", 8)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 8);
		}

		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		auto variablePtr = getVariableIntern(globalVariableStatement.empty() == true?variableStatement:globalVariableStatement, __FUNCTION__, variableName, parentVariable, arrayIdx, key, setAccessBool, subStatement, false, globalVariableStatement.empty() == false);

		// set variable if not yet done
		if (variablePtr == nullptr && parentVariable == nullptr) {
			// default
			auto& scriptState = globalVariableStatement.empty() == true?getScriptState():getRootScriptState();
			auto variableIt = scriptState.variables.find(globalVariableStatement.empty() == true?variableStatement:globalVariableStatement);
			if (variableIt != scriptState.variables.end()) {
				auto& existingVariable = variableIt->second;
				if (existingVariable->isConstant() == false) {
					// if we set a variable in variable scope that did exist before, we can safely remove the constness
					if (createReference == true) {
						existingVariable->setReference(&variable);
					} else {
						existingVariable->setValue(variable);
					}
				} else {
					Console::printLine(getSubStatementInformation(*subStatement) + ": Constant: " + variableStatement + ": assignment of constant is not allowed");
				}
				return;
			} else {
				// if we set a variable in variable scope that did not exist before, we keep things as they are regarding constness
				scriptState.variables[globalVariableStatement.empty() == true?variableStatement:globalVariableStatement] =
					createReference == false?Variable::createNonReferenceVariablePointer(&variable):Variable::createReferenceVariablePointer(&variable);
			}
		} else {
			setVariableInternal(variableStatement, parentVariable, variablePtr, arrayIdx, key, variable, subStatement, createReference);
		}
	}

	/**
	 * Set variable by given variable pointer, variable statement and variable
	 * @param variablePtr variable pointer
	 * @param variableStatement variable statement
	 * @param variable variable
	 * @param subStatement optional sub statement the variable is written in
	 * @param createReference optional flag for creating variable references
	 */
	inline void setVariable(Variable* variablePtr, const string& variableStatement, const Variable& variable, const SubStatement* subStatement = nullptr, bool createReference = false) {
		//
		if (isVariableAccess(variableStatement, subStatement) == false) return;
		//
		string variableName;
		// global accessor
		string globalVariableStatement;
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$$.", 3)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 3);
		} else
		if (StringTools::viewStartsWith(string_view(variableStatement), string_view("$GLOBAL.", 8)) == true) {
			globalVariableStatement = "$" + StringTools::substring(variableStatement, 8);
		}

		//
		Variable* parentVariable = nullptr;
		string key;
		int64_t arrayIdx = ARRAYIDX_NONE;
		int setAccessBool = SETACCESSBOOL_NONE;
		variablePtr = evaluateVariableAccessIntern(variablePtr, globalVariableStatement.empty() == true?variableStatement:globalVariableStatement, __FUNCTION__, parentVariable, arrayIdx, key, setAccessBool, subStatement, false);

		// set variable if not yet done
		setVariableInternal(variableStatement, parentVariable, variablePtr, arrayIdx, key, variable, subStatement, createReference);
	}

	/**
	 * Parse script
	 * @param pathName path name
	 * @param fileName file name
	 * @param nativeOnly native only
	 */
	void parseScript(const string& pathName, const string& fileName, bool nativeOnly = false);

	/**
	 * Initialize script
	 */
	virtual void initializeScript();

	/**
	 * Start script by calling "main" function
	 */
	virtual void startScript();

	#if defined(MINITSCRIPT_EVENTS)
		// events
		/**
		 * Check if condition with given name exists
		 * @param condition condition
		 * @return condition with given name exists
		 */
		inline bool hasCondition(const string& condition) {
			// iterate scripts to find out if condition exists
			for (const auto& script: scripts) {
				if (script.type != Script::TYPE_ON) {
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
	#endif

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
	inline bool call(int scriptIdx, span<Variable>& arguments, Variable& returnValue) {
		return call(scriptIdx, arguments, returnValue, true);
	}

	/**
	 * Call function
	 * @param function function
	 * @param arguments argument values
	 * @param returnValue return value
	 * @return success
	 */
	inline bool call(const string& function, span<Variable>& arguments, Variable& returnValue) {
		return call(function, arguments, returnValue, true);
	}

	/**
	 * Call stacklet
	 * @param scriptIdx script index
	 * @param arguments argument values
	 * @param returnValue return value
	 * @return success
	 */
	inline bool callStacklet(int scriptIdx, span<Variable>& arguments, Variable& returnValue) {
		return call(scriptIdx, arguments, returnValue, false);
	}

	/**
	 * Call stacklet
	 * @param stacklet stacklet
	 * @param arguments argument values
	 * @param returnValue return value
	 * @return success
	 */
	inline bool callStacklet(const string& stacklet, span<Variable>& arguments, Variable& returnValue) {
		return call(stacklet, arguments, returnValue, false);
	}

	/**
	 * Evaluate statement
	 * @param evaluateStatement evaluate statement
	 * @param returnValue return value
	 * @return success
	 */
	inline bool evaluate(const string& evaluateStatement, Variable& returnValue) {
		Statement evaluateScriptStatement(
			"evaluate",
			LINE_NONE,
			STATEMENTIDX_FIRST,
			"internal.script.evaluate(" + StringTools::replace(StringTools::replace(evaluateStatement, "\\", "\\\\"), "\"", "\\\"") + ")",
			"internal.script.evaluate(" + StringTools::replace(StringTools::replace(evaluateStatement, "\\", "\\\\"), "\"", "\\\"") + ")",
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
		auto methodIt = rootScript->methods.find(methodName);
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
	 * Get method by operator
	 * @param operator_ operator
	 * @return method or nullptr
	 */
	inline Method* getOperatorMethod(Operator operator_) {
		auto methodIt = operators.find(operator_);
		if (methodIt != operators.end()) {
			return methodIt->second;
		} else {
			return nullptr;
		}
	}

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
	 * Get MinitScript instance information
	 * @return information as string
	 */
	const string getInformation();

	/**
	 * Stack trace
	 * @param arguments arguments
	 * @param subStatement sub statement
	 */
	const string stackTrace(const span<Variable>& arguments, const SubStatement& subStatement);

	/**
	 * Throw
	 * @param throwArgument throw argument
	 * @return if exception has been handled
	 */
	bool _throw(const MinitScript::Variable& throwArgument);

};
