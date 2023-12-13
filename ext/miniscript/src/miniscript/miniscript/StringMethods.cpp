#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/math/Math.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/miniscript/StringMethods.h>
#include <miniscript/utilities/Character.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Float.h>
#include <miniscript/utilities/Integer.h>
#include <miniscript/utilities/UTF8StringTokenizer.h>
#include <miniscript/utilities/UTF8StringTools.h>
#include <miniscript/utilities/UTF8CharacterIterator.h>

using std::span;

using miniscript::miniscript::StringMethods;

using miniscript::math::Math;
using miniscript::miniscript::MiniScript;
using miniscript::utilities::Character;
using miniscript::utilities::Console;
using miniscript::utilities::Float;
using miniscript::utilities::Integer;
using miniscript::utilities::UTF8StringTools;
using miniscript::utilities::UTF8CharacterIterator;

void StringMethods::registerMethods(MiniScript* miniScript) {
	// string functions
	{
		//
		class MethodString: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodString(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == true) {
					returnValue.setValue(stringValue);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodString(miniScript));
	}
	{
		//
		class MethodStringLength: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringLength(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::length";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == true) {
					returnValue.setValue(static_cast<int64_t>(UTF8StringTools::getLength(stringValue, arguments[0].getStringValueCache())));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodStringLength(miniScript));
	}
	{
		//
		class MethodStringCharAt: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringCharAt(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::charAt";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				int64_t index;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(arguments, 1, index, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::getCharAt(stringValue, index, arguments[0].getStringValueCache()));
				}
			}
		};
		miniScript->registerMethod(new MethodStringCharAt(miniScript));
	}
	{
		//
		class MethodStringStartsWith: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringStartsWith(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "prefix", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::startsWith";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string prefix;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, prefix, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::startsWith(stringValue, prefix));
				}
			}
		};
		miniScript->registerMethod(new MethodStringStartsWith(miniScript));
	}
	{
		//
		class MethodStringEndsWith: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringEndsWith(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "suffix", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::endsWith";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string suffix;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, suffix, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::endsWith(stringValue, suffix));
				}
			}
		};
		miniScript->registerMethod(new MethodStringEndsWith(miniScript));
	}
	{
		//
		class MethodStringReplace: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringReplace(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::replace";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string what;
				string by;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, what, false) == false ||
					MiniScript::getStringValue(arguments, 2, by, false) == false ||
					MiniScript::getIntegerValue(arguments, 3, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::replace(stringValue, what, by, beginIndex, arguments[0].getStringValueCache()));
				}
			}
		};
		miniScript->registerMethod(new MethodStringReplace(miniScript));
	}
	{
		//
		class MethodStringIndexOf: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringIndexOf(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::indexOf";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, what, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::indexOf(stringValue, what, beginIndex, arguments[0].getStringValueCache()));
				}
			}
		};
		miniScript->registerMethod(new MethodStringIndexOf(miniScript));
	}
	{
		//
		class MethodStringFirstIndexOf: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringFirstIndexOf(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::firstIndexOf";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, what, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::firstIndexOf(stringValue, what, beginIndex, arguments[0].getStringValueCache()));
				}
			}
		};
		miniScript->registerMethod(new MethodStringFirstIndexOf(miniScript));
	}
	{
		//
		class MethodStringLastIndexOf: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringLastIndexOf(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::lastIndexOf";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, what, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::lastIndexOf(stringValue, what, beginIndex, arguments[0].getStringValueCache()));
				}
			}
		};
		miniScript->registerMethod(new MethodStringLastIndexOf(miniScript));
	}
	{
		//
		class MethodStringFirstIndexOfChars: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringFirstIndexOfChars(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::firstIndexOfChars";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, what, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(
						static_cast<int64_t>(
							UTF8StringTools::firstIndexOfChars(
								stringValue,
								what,
								beginIndex,
								arguments[0].getStringValueCache(),
								arguments[1].getStringValueCache()
							)
						)
					);
				}
			}
		};
		miniScript->registerMethod(new MethodStringFirstIndexOfChars(miniScript));
	}
	{
		//
		class MethodStringLastIndexOfChars: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringLastIndexOfChars(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "endIndex", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::lastIndexOfChars";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string what;
				int64_t endIndex = -1;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, what, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, endIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(
						static_cast<int64_t>(
							UTF8StringTools::lastIndexOfChars(
								stringValue,
								what,
								endIndex,
								arguments[0].getStringValueCache(),
								arguments[1].getStringValueCache()
							)
						)
					);
				}
			}
		};
		miniScript->registerMethod(new MethodStringLastIndexOfChars(miniScript));
	}
	{
		//
		class MethodStringSubString: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringSubString(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "endIndex", .optional = true, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::substring";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				int64_t beginIndex;
				int64_t endIndex = string::npos;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(arguments, 1, beginIndex, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, endIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					// utf8 character iterator
					returnValue.setValue(UTF8StringTools::substring(stringValue, beginIndex, endIndex));
				}
			}
		};
		miniScript->registerMethod(new MethodStringSubString(miniScript));
	}
	{
		//
		class MethodStringEqualsIgnoreCase: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringEqualsIgnoreCase(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "other", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::equalsIgnoreCase";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string other;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, other, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::equalsIgnoreCase(stringValue, other, arguments[0].getStringValueCache(), arguments[1].getStringValueCache()));
				}
			}
		};
		miniScript->registerMethod(new MethodStringEqualsIgnoreCase(miniScript));
	}
	{
		//
		class MethodStringTrim: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringTrim(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::trim";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::trim(stringValue, arguments[0].getStringValueCache()));
				}
			}
		};
		miniScript->registerMethod(new MethodStringTrim(miniScript));
	}
	{
		//
		class MethodStringRegexMatch: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringRegexMatch(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "pattern", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::regexMatch";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string pattern;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, pattern, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::regexMatch(stringValue, pattern));
				}
			}
		};
		miniScript->registerMethod(new MethodStringRegexMatch(miniScript));
	}
	{
		//
		class MethodStringRegexReplace: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringRegexReplace(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "pattern", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::regexReplace";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string pattern;
				string by;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, pattern, false) == false ||
					MiniScript::getStringValue(arguments, 2, by, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::regexReplace(stringValue, pattern, by));
				}
			}
		};
		miniScript->registerMethod(new MethodStringRegexReplace(miniScript));
	}
	{
		//
		class MethodStringTokenize: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringTokenize(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "delimiters", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::tokenize";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string delimiters;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, delimiters, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto tokenizedStringVector = UTF8StringTools::tokenize(stringValue, delimiters);
					//
					returnValue.setType(MiniScript::TYPE_ARRAY);
					for (const auto& tokenizedString: tokenizedStringVector) {
						returnValue.pushArrayEntry(tokenizedString);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodStringTokenize(miniScript));
	}
	{
		//
		class MethodStringGenerate: public MiniScript::Method {
		private:
			MiniScript *miniScript { nullptr };
		public:
			MethodStringGenerate(MiniScript *miniScript) :
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "count", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "String::generate";
			}
			void executeMethod(span<MiniScript::Variable> &arguments, MiniScript::Variable &returnValue, const MiniScript::Statement &statement) override {
				string what;
				int64_t count = 1;
				if (MiniScript::getStringValue(arguments, 0, what, false) == false ||
					MiniScript::getIntegerValue(arguments, 1, count, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::generate(what, count));
				}
			}
		};
		miniScript->registerMethod(new MethodStringGenerate(miniScript));
	}
	{
		//
		class MethodStringIndent: public MiniScript::Method {
		private:
			MiniScript *miniScript { nullptr };
		public:
			MethodStringIndent(MiniScript *miniScript) :
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "src", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "with", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "count", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "String::indent";
			}
			void executeMethod(span<MiniScript::Variable> &arguments, MiniScript::Variable &returnValue, const MiniScript::Statement &statement) override {
				string src;
				string with;
				int64_t count = 1;
				if (MiniScript::getStringValue(arguments, 0, src, false) == false ||
					MiniScript::getStringValue(arguments, 1, with, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, count, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::indent(src, with, count));
				}
			}
		};
		miniScript->registerMethod(new MethodStringIndent(miniScript));
	}
	{
		//
		class MethodStringConcatenate: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringConcatenate(MiniScript* miniScript): MiniScript::Method({}, MiniScript::TYPE_STRING), miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::concatenate";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string result;
				for (const auto& argument: arguments) {
					result+= argument.getValueAsString();
				}
				returnValue.setValue(result);
			}
			bool isVariadic() const override {
				return true;
			}
		};
		miniScript->registerMethod(new MethodStringConcatenate(miniScript));
	}
	{
		//
		class MethodToStringUpperCase: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodToStringUpperCase(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::toUpperCase";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == true) {
					returnValue.setValue(UTF8StringTools::toUpperCase(stringValue, arguments[0].getStringValueCache()));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodToStringUpperCase(miniScript));
	}
	{
		//
		class MethodToStringLowerCase: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodToStringLowerCase(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::toLowerCase";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == true) {
					returnValue.setValue(UTF8StringTools::toLowerCase(stringValue, arguments[0].getStringValueCache()));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodToStringLowerCase(miniScript));
	}
	{
		//
		class MethodStringIsEmpty: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringIsEmpty(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::isEmpty";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == true) {
					returnValue.setValue(stringValue.empty());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodStringIsEmpty(miniScript));
	}
	{
		//
		class MethodStringIsFloat: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringIsFloat(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::isFloat";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == true) {
					returnValue.setValue(Float::is(stringValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodStringIsFloat(miniScript));
	}
	{
		//
		class MethodStringIsInteger: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringIsInteger(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::isInteger";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == true) {
					returnValue.setValue(Integer::is(stringValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodStringIsInteger(miniScript));
	}
	{
		//
		class MethodStringPadLeft: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringPadLeft(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "toLength", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::padLeft";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string by;
				int64_t toLength;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, by, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, toLength, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::padLeft(stringValue, by, toLength, arguments[0].getStringValueCache()));
				}
			}
		};
		miniScript->registerMethod(new MethodStringPadLeft(miniScript));
	}
	{
		//
		class MethodStringPadRight: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringPadRight(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "toLength", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::padRight";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				string by;
				int64_t toLength;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false ||
					MiniScript::getStringValue(arguments, 1, by, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, toLength, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(UTF8StringTools::padRight(stringValue, by, toLength, arguments[0].getStringValueCache()));
				}
			}
		};
		miniScript->registerMethod(new MethodStringPadRight(miniScript));
	}
	{
		//
		class MethodStringToByteArray: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringToByteArray(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BYTEARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::toByteArray";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(arguments, 0, stringValue, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setType(MiniScript::TYPE_BYTEARRAY);
					for (auto i = 0; i < stringValue.size(); i++) returnValue.pushByteArrayEntry(stringValue[i]);
				}
			}
		};
		miniScript->registerMethod(new MethodStringToByteArray(miniScript));
	}
	{
		//
		class MethodStringFromByteArray: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodStringFromByteArray(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BYTEARRAY, .name = "byteArray", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "String::fromByteArray";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				if (arguments.size() != 1 || arguments[0].getType() != MiniScript::TYPE_BYTEARRAY) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto byteArrayPointer = arguments[0].getByteArrayPointer();
					if (byteArrayPointer != nullptr) {
						returnValue.setValue(string((const char*)(byteArrayPointer->data()), byteArrayPointer->size()));
					}
				}
			}
		};
		miniScript->registerMethod(new MethodStringFromByteArray(miniScript));
	}
}
