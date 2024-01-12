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
	// byte array methods
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
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setType(MiniScript::TYPE_BYTEARRAY);
			}
		};
		miniScript->registerMethod(new MethodByteArray(miniScript));
	}
	//
	{
		//
		class MethodByteArraySize: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArraySize(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::size";
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
		miniScript->registerMethod(new MethodByteArraySize(miniScript));
	}
	//
	{
		//
		class MethodByteArrayGetReadPosition: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayGetReadPosition(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::getReadPosition";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(*arguments[0].getByteArrayReadPointer());
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayGetReadPosition(miniScript));
	}
	//
	{
		//
		class MethodByteArraySetReadPosition: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArraySetReadPosition(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "position", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::setReadPosition";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t position;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getIntegerValue(arguments, 1, position, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if (position < 0ll) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Byte array read position must not be lesser than 0");
					} else
					if (position >= arguments[0].getByteArraySize()) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Byte array read position exceeding byte array size: " + to_string(*byteArrayReadPtr) + " >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						*byteArrayReadPtr = position;
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArraySetReadPosition(miniScript));
	}
	//
	{
		//
		class MethodByteArrayGetWritePosition: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayGetWritePosition(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::getWritePosition";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(*arguments[0].getByteArrayWritePointer());
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayGetWritePosition(miniScript));
	}
	//
	{
		//
		class MethodByteArraySetWritePosition: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArraySetWritePosition(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "position", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::setWritePosition";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t position;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getIntegerValue(arguments, 1, position, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					if (position < 0ll) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Byte array write position must not be lesser than 0");
					} else
					if (position > arguments[0].getByteArraySize()) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Byte array write position exceeding byte array size: " + to_string(*byteArrayWritePtr) + " >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						*byteArrayWritePtr = position;
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArraySetWritePosition(miniScript));
	}
	//
	{
		//
		class MethodByteArrayReadBool: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayReadBool(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::readBool";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 1 > arguments[0].getByteArraySize()) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading boolean value, because of read position " + to_string(*byteArrayReadPtr) + " + 1 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						returnValue.setValue(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++) != 0);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayReadBool(miniScript));
	}
	//
	{
		//
		class MethodByteArrayReadInt8: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayReadInt8(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_INTEGER,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::readInt8";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 1 > arguments[0].getByteArraySize()) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading 8 bit integer value, because of read position " + to_string(*byteArrayReadPtr) + " + 1 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						returnValue.setValue(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)));
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayReadInt8(miniScript));
	}
	//
	{
		//
		class MethodByteArrayReadInt16: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayReadInt16(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_INTEGER,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::readInt16";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 2 > arguments[0].getByteArraySize()) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading 16 bit integer value, because of read position " + to_string(*byteArrayReadPtr) + " + 2 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						returnValue.setValue(
							static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 8)
						);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayReadInt16(miniScript));
	}
	//
	{
		//
		class MethodByteArrayReadInt32: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayReadInt32(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_INTEGER,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::readInt32";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 4 > arguments[0].getByteArraySize()) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading 32 bit integer value, because of read position " + to_string(*byteArrayReadPtr) + " + 4 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						returnValue.setValue(
							static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 8) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 16) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 24)
						);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayReadInt32(miniScript));
	}
	//
	{
		//
		class MethodByteArrayReadInt64: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayReadInt64(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_INTEGER,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::readInt64";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 8 > arguments[0].getByteArraySize()) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading 64 bit integer value, because of read position " + to_string(*byteArrayReadPtr) + " + 8 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						returnValue.setValue(
							static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 8) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 16) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 24) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 32) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 40) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 48) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 56)

						);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayReadInt64(miniScript));
	}
	//
	{
		//
		class MethodByteArrayReadFloat: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayReadFloat(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_FLOAT,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::readFloat";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 4 > arguments[0].getByteArraySize()) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading 32 bit float value, because of read position " + to_string(*byteArrayReadPtr) + " + 4 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						uint32_t floatAsInt =
							static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 8) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 16) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 24);
						returnValue.setValue(*((float*)&floatAsInt));
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayReadFloat(miniScript));
	}
	//
	{
		//
		class MethodByteArrayReadSmallString: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayReadSmallString(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_STRING,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::readSmallString";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 1 > arguments[0].getByteArraySize()) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading 8 bit string size, because of read position " + to_string(*byteArrayReadPtr) + " + 1 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						string value;
						auto size = static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++));
						if ((*byteArrayReadPtr) + size > arguments[0].getByteArraySize()) {
							_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading string bytes, because of read position " + to_string(*byteArrayReadPtr) + " + " + to_string(size) + " >= " + to_string(arguments[0].getByteArraySize()));
						} else {
							value.resize(size);
							for (auto i = 0; i < size; i++) value.data()[i] = arguments[0].getByteArrayEntry((*byteArrayReadPtr)++);
							returnValue.setValue(value);
						}
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayReadSmallString(miniScript));
	}
	//
	{
		//
		class MethodByteArrayReadMediumString: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayReadMediumString(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_STRING,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::readMediumString";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 2 > arguments[0].getByteArraySize()) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading 16 bit string size, because of read position " + to_string(*byteArrayReadPtr) + " + 2 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						string value;
						auto size =
							static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 8);
						if ((*byteArrayReadPtr) + size > arguments[0].getByteArraySize()) {
							_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading string bytes, because of read position " + to_string(*byteArrayReadPtr) + " + " + to_string(size) + " >= " + to_string(arguments[0].getByteArraySize()));
						} else {
							value.resize(size);
							for (auto i = 0; i < size; i++) value.data()[i] = arguments[0].getByteArrayEntry((*byteArrayReadPtr)++);
							returnValue.setValue(value);
						}
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayReadMediumString(miniScript));
	}
	//
	{
		//
		class MethodByteArrayReadLargeString: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayReadLargeString(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_STRING,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::readLargeString";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 4 > arguments[0].getByteArraySize()) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading 32 bit string size, because of read position " + to_string(*byteArrayReadPtr) + " + 4 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						string value;
						auto size =
							static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 8) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 16) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 24);
						if ((*byteArrayReadPtr) + size > arguments[0].getByteArraySize()) {
							_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding byte array size while reading string bytes, because of read position " + to_string(*byteArrayReadPtr) + " + " + to_string(size) + " >= " + to_string(arguments[0].getByteArraySize()));
						} else {
							value.resize(size);
							for (auto i = 0; i < size; i++) value.data()[i] = arguments[0].getByteArrayEntry((*byteArrayReadPtr)++);
							returnValue.setValue(value);
						}
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayReadLargeString(miniScript));
	}
	//
	{
		//
		class MethodByteArrayWriteBool: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayWriteBool(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_BOOLEAN, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::writeBool";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				// TODO: value bounds check
				bool value;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getBooleanValue(arguments, 1, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value);
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayWriteBool(miniScript));
	}
	//
	{
		//
		class MethodByteArrayWriteInt8: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayWriteInt8(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::writeInt8";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				// TODO: value bounds check
				int64_t value;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getIntegerValue(arguments, 1, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value);
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayWriteInt8(miniScript));
	}
	//
	{
		//
		class MethodByteArrayWriteInt16: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayWriteInt16(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::writeInt16";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				// TODO: value bounds check
				int64_t value;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getIntegerValue(arguments, 1, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 8) & 0xff);
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayWriteInt16(miniScript));
	}
	//
	{
		//
		class MethodByteArrayWriteInt32: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayWriteInt32(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::writeInt32";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				// TODO: value bounds check
				int64_t value;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getIntegerValue(arguments, 1, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 8) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 16) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 24) & 0xff);
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayWriteInt32(miniScript));
	}
	//
	{
		//
		class MethodByteArrayWriteInt64: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayWriteInt64(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::writeInt64";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				// TODO: value bounds check
				int64_t value;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getIntegerValue(arguments, 1, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 8) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 16) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 24) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 32) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 40) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 48) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 56) & 0xff);
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayWriteInt64(miniScript));
	}
	//
	{
		//
		class MethodByteArrayWriteFloat: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayWriteFloat(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::writeFloat";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				// TODO: value bounds check
				float value;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getFloatValue(arguments, 1, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					uint32_t intValue = *((uint32_t*)&value);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, intValue & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (intValue >> 8) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (intValue >> 16) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (intValue >> 24) & 0xff);
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayWriteFloat(miniScript));
	}
	//
	{
		//
		class MethodByteArrayWriteSmallString: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayWriteSmallString(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::writeSmallString";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string value;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getStringValue(arguments, 1, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					if (value.size() > 255) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding small string size of 255 bytes: " + to_string(value.size()) + " > 255");
					} else {
						const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
						arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value.size());
						for (auto i = 0; i < value.size(); i++) {
							arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value[i]);
						}
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayWriteSmallString(miniScript));
	}
	//
	{
		//
		class MethodByteArrayWriteMediumString: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayWriteMediumString(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::writeMediumString";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string value;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getStringValue(arguments, 1, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					if (value.size() > 65535) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding medium string size of 65535 bytes: " + to_string(value.size()) + " > 65535");
					} else {
						const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
						arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value.size() & 0xff);
						arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value.size() >> 8) & 0xff);
						for (auto i = 0; i < value.size(); i++) {
							arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value[i]);
						}
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayWriteMediumString(miniScript));
	}
	//
	{
		//
		class MethodByteArrayWriteLargeString: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodByteArrayWriteLargeString(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::writeLargeString";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string value;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_BYTEARRAY ||
					MiniScript::getStringValue(arguments, 1, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					if (value.size() > 4294967295) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": Exceeding medium string size of 4294967295 bytes: " + to_string(value.size()) + " > 4294967295");
					} else {
						const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
						arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value.size() & 0xff);
						arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value.size() >> 8) & 0xff);
						arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value.size() >> 16) & 0xff);
						arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value.size() >> 24) & 0xff);
						for (auto i = 0; i < value.size(); i++) {
							arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value[i]);
						}
					}
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayWriteLargeString(miniScript));
	}
	//
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
						{ .type = MiniScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "size", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "ByteArray::remove";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t index;
				int64_t size;
				if ((arguments.size() != 3 || arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) ||
					MiniScript::getIntegerValue(arguments, 1, index, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, size, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					// TODO: bounds check
					arguments[0].removeByteArray(index, size);
				}
			}
		};
		miniScript->registerMethod(new MethodByteArrayRemove(miniScript));
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
