#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/ByteArrayMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/Console.h>

using std::span;

using minitscript::minitscript::ByteArrayMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;

void ByteArrayMethods::registerConstants(MinitScript* minitScript) {
}

void ByteArrayMethods::registerMethods(MinitScript* minitScript) {
	// byte array methods
	{
		//
		class MethodByteArray: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArray(MinitScript* minitScript):
				MinitScript::Method(
					{},
					MinitScript::TYPE_BYTEARRAY
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					returnValue.setType(MinitScript::TYPE_BYTEARRAY);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArray(minitScript));
	}
	//
	{
		//
		class MethodByteArrayGetSize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayGetSize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::getSize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					returnValue.setValue(static_cast<int64_t>(arguments[0].getByteArraySize()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayGetSize(minitScript));
	}
	//
	{
		//
		class MethodByteArrayGetReadPosition: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayGetReadPosition(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::getReadPosition";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					returnValue.setValue(*arguments[0].getByteArrayReadPointer());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayGetReadPosition(minitScript));
	}
	//
	{
		//
		class MethodByteArraySetReadPosition: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArraySetReadPosition(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "position", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::setReadPosition";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t position;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY &&
					MinitScript::getIntegerValue(arguments, 1, position) == true) {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if (position < 0ll) {
						minitScript->complain(getMethodName(), subStatement, "Byte array read position must not be lesser than 0");
					} else
					if (position >= arguments[0].getByteArraySize()) {
						minitScript->complain(getMethodName(), subStatement, "Byte array read position exceeding byte array size: " + to_string(*byteArrayReadPtr) + " >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						*byteArrayReadPtr = position;
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArraySetReadPosition(minitScript));
	}
	//
	{
		//
		class MethodByteArrayGetWritePosition: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayGetWritePosition(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::getWritePosition";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					returnValue.setValue(*arguments[0].getByteArrayWritePointer());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayGetWritePosition(minitScript));
	}
	//
	{
		//
		class MethodByteArraySetWritePosition: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArraySetWritePosition(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "position", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::setWritePosition";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t position;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY &&
					MinitScript::getIntegerValue(arguments, 1, position) == true) {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					if (position < 0ll) {
						minitScript->complain(getMethodName(), subStatement, "Byte array write position must not be lesser than 0");
					} else
					if (position > arguments[0].getByteArraySize()) {
						minitScript->complain(getMethodName(), subStatement, "Byte array write position exceeding byte array size: " + to_string(*byteArrayWritePtr) + " >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						*byteArrayWritePtr = position;
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArraySetWritePosition(minitScript));
	}
	//
	{
		//
		class MethodByteArrayReadBool: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayReadBool(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MinitScript::TYPE_BOOLEAN,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::readBool";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 1 > arguments[0].getByteArraySize()) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading boolean value, because of read position " + to_string(*byteArrayReadPtr) + " + 1 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						returnValue.setValue(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++) != 0);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayReadBool(minitScript));
	}
	//
	{
		//
		class MethodByteArrayReadInt8: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayReadInt8(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_INTEGER,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::readInt8";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 1 > arguments[0].getByteArraySize()) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading 8 bit integer value, because of read position " + to_string(*byteArrayReadPtr) + " + 1 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						returnValue.setValue(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayReadInt8(minitScript));
	}
	//
	{
		//
		class MethodByteArrayReadInt16: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayReadInt16(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MinitScript::TYPE_INTEGER,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::readInt16";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 2 > arguments[0].getByteArraySize()) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading 16 bit integer value, because of read position " + to_string(*byteArrayReadPtr) + " + 2 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						returnValue.setValue(
							static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 8)
						);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayReadInt16(minitScript));
	}
	//
	{
		//
		class MethodByteArrayReadInt32: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayReadInt32(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MinitScript::TYPE_INTEGER,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::readInt32";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 4 > arguments[0].getByteArraySize()) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading 32 bit integer value, because of read position " + to_string(*byteArrayReadPtr) + " + 4 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						returnValue.setValue(
							static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 8) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 16) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 24)
						);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayReadInt32(minitScript));
	}
	//
	{
		//
		class MethodByteArrayReadInt64: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayReadInt64(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MinitScript::TYPE_INTEGER,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::readInt64";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 8 > arguments[0].getByteArraySize()) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading 64 bit integer value, because of read position " + to_string(*byteArrayReadPtr) + " + 8 >= " + to_string(arguments[0].getByteArraySize()));
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
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayReadInt64(minitScript));
	}
	//
	{
		//
		class MethodByteArrayReadFloat: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayReadFloat(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MinitScript::TYPE_FLOAT,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::readFloat";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 4 > arguments[0].getByteArraySize()) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading 32 bit float value, because of read position " + to_string(*byteArrayReadPtr) + " + 4 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						uint32_t floatAsInt =
							static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 8) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 16) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 24);
						returnValue.setValue(*((float*)&floatAsInt));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayReadFloat(minitScript));
	}
	//
	{
		//
		class MethodByteArrayReadSmallString: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayReadSmallString(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MinitScript::TYPE_STRING,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::readSmallString";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 1 > arguments[0].getByteArraySize()) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading 8 bit string size, because of read position " + to_string(*byteArrayReadPtr) + " + 1 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						string value;
						auto size = static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++));
						if ((*byteArrayReadPtr) + size > arguments[0].getByteArraySize()) {
							minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading string bytes, because of read position " + to_string(*byteArrayReadPtr) + " + " + to_string(size) + " >= " + to_string(arguments[0].getByteArraySize()));
						} else {
							value.resize(size);
							for (auto i = 0; i < size; i++) value.data()[i] = arguments[0].getByteArrayEntry((*byteArrayReadPtr)++);
							returnValue.setValue(value);
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayReadSmallString(minitScript));
	}
	//
	{
		//
		class MethodByteArrayReadMediumString: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayReadMediumString(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MinitScript::TYPE_STRING,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::readMediumString";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 2 > arguments[0].getByteArraySize()) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading 16 bit string size, because of read position " + to_string(*byteArrayReadPtr) + " + 2 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						string value;
						auto size =
							static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 8);
						if ((*byteArrayReadPtr) + size > arguments[0].getByteArraySize()) {
							minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading string bytes, because of read position " + to_string(*byteArrayReadPtr) + " + " + to_string(size) + " >= " + to_string(arguments[0].getByteArraySize()));
						} else {
							value.resize(size);
							for (auto i = 0; i < size; i++) value.data()[i] = arguments[0].getByteArrayEntry((*byteArrayReadPtr)++);
							returnValue.setValue(value);
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayReadMediumString(minitScript));
	}
	//
	{
		//
		class MethodByteArrayReadLargeString: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayReadLargeString(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
					},
					MinitScript::TYPE_STRING,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::readLargeString";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					const auto byteArrayReadPtr = arguments[0].getByteArrayReadPointer();
					if ((*byteArrayReadPtr) + 4 > arguments[0].getByteArraySize()) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading 32 bit string size, because of read position " + to_string(*byteArrayReadPtr) + " + 4 >= " + to_string(arguments[0].getByteArraySize()));
					} else {
						string value;
						auto size =
							static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 8) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 16) +
							(static_cast<int64_t>(arguments[0].getByteArrayEntry((*byteArrayReadPtr)++)) << 24);
						if ((*byteArrayReadPtr) + size > arguments[0].getByteArraySize()) {
							minitScript->complain(getMethodName(), subStatement, "Exceeding byte array size while reading string bytes, because of read position " + to_string(*byteArrayReadPtr) + " + " + to_string(size) + " >= " + to_string(arguments[0].getByteArraySize()));
						} else {
							value.resize(size);
							for (auto i = 0; i < size; i++) value.data()[i] = arguments[0].getByteArrayEntry((*byteArrayReadPtr)++);
							returnValue.setValue(value);
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayReadLargeString(minitScript));
	}
	//
	{
		//
		class MethodByteArrayWriteBool: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayWriteBool(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::writeBool";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				bool value;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY &&
					MinitScript::getBooleanValue(arguments, 1, value) == true) {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayWriteBool(minitScript));
	}
	//
	{
		//
		class MethodByteArrayWriteInt8: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayWriteInt8(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::writeInt8";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t value;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY &&
					MinitScript::getIntegerValue(arguments, 1, value) == true) {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayWriteInt8(minitScript));
	}
	//
	{
		//
		class MethodByteArrayWriteInt16: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayWriteInt16(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::writeInt16";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t value;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY &&
					MinitScript::getIntegerValue(arguments, 1, value) == true) {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 8) & 0xff);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayWriteInt16(minitScript));
	}
	//
	{
		//
		class MethodByteArrayWriteInt32: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayWriteInt32(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::writeInt32";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t value;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY &&
					MinitScript::getIntegerValue(arguments, 1, value) == true) {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 8) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 16) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 24) & 0xff);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayWriteInt32(minitScript));
	}
	//
	{
		//
		class MethodByteArrayWriteInt64: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayWriteInt64(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::writeInt64";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t value;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY &&
					MinitScript::getIntegerValue(arguments, 1, value) == true) {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 8) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 16) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 24) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 32) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 40) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 48) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value >> 56) & 0xff);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayWriteInt64(minitScript));
	}
	//
	{
		//
		class MethodByteArrayWriteFloat: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayWriteFloat(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::writeFloat";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float value;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY &&
					MinitScript::getFloatValue(arguments, 1, value) == true) {
					const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
					uint32_t intValue = *((uint32_t*)&value);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, intValue & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (intValue >> 8) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (intValue >> 16) & 0xff);
					arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (intValue >> 24) & 0xff);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayWriteFloat(minitScript));
	}
	//
	{
		//
		class MethodByteArrayWriteSmallString: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayWriteSmallString(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::writeSmallString";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string value;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY &&
					MinitScript::getStringValue(arguments, 1, value) == true) {
					if (value.size() > 255) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding small string size of 255 bytes: " + to_string(value.size()) + " > 255");
					} else {
						const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
						arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value.size());
						for (auto i = 0; i < value.size(); i++) {
							arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value[i]);
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayWriteSmallString(minitScript));
	}
	//
	{
		//
		class MethodByteArrayWriteMediumString: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayWriteMediumString(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::writeMediumString";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string value;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY &&
					MinitScript::getStringValue(arguments, 1, value) == true) {
					if (value.size() > 65535) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding medium string size of 65535 bytes: " + to_string(value.size()) + " > 65535");
					} else {
						const auto byteArrayWritePtr = arguments[0].getByteArrayWritePointer();
						arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value.size() & 0xff);
						arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, (value.size() >> 8) & 0xff);
						for (auto i = 0; i < value.size(); i++) {
							arguments[0].setByteArrayEntry((*byteArrayWritePtr)++, value[i]);
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayWriteMediumString(minitScript));
	}
	//
	{
		//
		class MethodByteArrayWriteLargeString: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayWriteLargeString(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::writeLargeString";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string value;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY &&
					MinitScript::getStringValue(arguments, 1, value) == true) {
					if (value.size() > 4294967295) {
						minitScript->complain(getMethodName(), subStatement, "Exceeding medium string size of 4294967295 bytes: " + to_string(value.size()) + " > 4294967295");
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
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayWriteLargeString(minitScript));
	}
	//
	{
		//
		class MethodByteArrayRemove: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayRemove(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "size", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::remove";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t index;
				int64_t size;
				if ((arguments.size() == 3 && arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) &&
					MinitScript::getIntegerValue(arguments, 1, index) == true &&
					MinitScript::getIntegerValue(arguments, 2, size) == true) {
					arguments[0].removeByteArray(index, size);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayRemove(minitScript));
	}
	{
		//
		class MethodByteArrayClear: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodByteArrayClear(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "bytearray", .optional = false, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "ByteArray::clear";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 && arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					arguments[0].clearByteArray();
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodByteArrayClear(minitScript));
	}
}
