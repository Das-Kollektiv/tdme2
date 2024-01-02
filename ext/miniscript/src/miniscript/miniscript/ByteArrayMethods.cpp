#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/ByteArrayMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>

using std::span;

using miniscript::miniscript::ByteArrayMethods;

using miniscript::miniscript::MiniScript;

using _Console = miniscript::utilities::Console;

void ByteArrayMethods::registerConstants(MiniScript* miniScript) {
}

void ByteArrayMethods::registerMethods(MiniScript* miniScript) {
	// array methods
	{
		//
		class MethodByteArray: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArray(MiniScript* miniScript):
				MiniScript::Method(
					{},
					MiniScript::TYPE_BYTEARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray";
			}
			bool isVariadic() const override {
				return true;
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setType(MiniScript::TYPE_BYTEARRAY);
				uint8_t value;
				for (const auto& argument: arguments) {
					if (argument.getByteValue(miniScript, value, &statement) == true) {
						returnValue.pushByteArrayEntry(value);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArray(miniScript));
	}
	{
		//
		class MethodByteArrayLength: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayLength(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::length";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 || arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(static_cast<int64_t>(arguments[0].getByteArraySize()));
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayLength(miniScript));
	}
	{
		//
		class MethodByteArrayPush: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayPush(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::push";
			}
			bool isVariadic() const override {
				return true;
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				if (arguments.size() < 1 || arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					uint8_t value;
					for (auto i = 1; i < arguments.size(); i++) {
						if (arguments[i].getByteValue(miniScript, value, &statement) == true) {
							arguments[0].pushByteArrayEntry(value);
						}
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayPush(miniScript));
	}
	{
		//
		class MethodByteArrayGet: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayGet(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::get";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t index;
				if ((arguments.size() <= 1 || arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) ||
					MiniScript::getIntegerValue(arguments, 1, index, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(static_cast<int64_t>(arguments[0].getByteArrayEntry(index)));
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayGet(miniScript));
	}
	{
		//
		class MethodByteArraySet: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArraySet(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::set";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t index;
				if ((arguments.size() <= 2 || arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) ||
					MiniScript::getIntegerValue(arguments, 1, index, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					uint8_t value;
					if (arguments[2].getByteValue(miniScript, value, &statement) == true) {
						arguments[0].setByteArrayEntry(index, value);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArraySet(miniScript));
	}
	{
		//
		class MethodByteArrayRemove: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayRemove(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::remove";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t index;
				if ((arguments.size() < 2 || arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) ||
					MiniScript::getIntegerValue(arguments, 1, index, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].removeByteArrayEntry(index);
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayRemove(miniScript));
	}
	{
		//
		class MethodByteArrayAppend: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayAppend(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "other", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::appendByteArray";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					arguments[1].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto byteArrayPtr = arguments[0].getByteArrayPointer();
					auto otherByteArrayPtr = arguments[1].getByteArrayPointer();
					if (byteArrayPtr != nullptr && otherByteArrayPtr != nullptr) {
						for (const auto value: *otherByteArrayPtr) byteArrayPtr->push_back(value);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayAppend(miniScript));
	}
	{
		//
		class MethodByteArrayExtract: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayExtract(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "length", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BYTEARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::extractByteArray";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t index;
				int64_t length;
				if (arguments.size() != 3 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getIntegerValue(arguments, 1, index, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, length, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto byteArrayPtr = arguments[0].getByteArrayPointer();
					if (byteArrayPtr != nullptr) {
						returnValue.setType(MiniScript::TYPE_BYTEARRAY);
						for (auto i = index; i >= 0 && i < byteArrayPtr->size() && i < index + length; i++) returnValue.pushByteArrayEntry((*byteArrayPtr)[i]);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayExtract(miniScript));
	}
	{
		//
		class MethodByteArrayClear: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayClear(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::clear";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t index;
				if (arguments.size() != 1 || arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].clearByteArray();
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayClear(miniScript));
	}
}
