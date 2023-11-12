#include <span>

#include <tdme/tdme.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptString.h>
#include <tdme/utilities/StringTools.h>

using std::span;

using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptString;
using tdme::utilities::StringTools;

void MiniScriptString::registerMethods(MiniScript* miniScript) {
	// string functions
	{
		//
		class ScriptMethodString: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodString(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(stringValue);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodString(miniScript));
	}
	{
		//
		class ScriptMethodStringLength: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringLength(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.length";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(static_cast<int64_t>(stringValue.size()));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringLength(miniScript));
	}
	{
		//
		class ScriptMethodStringCharAt: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringCharAt(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.charAt";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				int64_t index;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(index >= 0 && index < stringValue.size()?string(&stringValue[index], 1):string());
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringCharAt(miniScript));
	}
	{
		//
		class ScriptMethodStringStartsWith: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringStartsWith(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "prefix", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.startsWith";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string prefix;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, prefix, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::startsWith(stringValue, prefix));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringStartsWith(miniScript));
	}
	{
		//
		class ScriptMethodStringEndsWith: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringEndsWith(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "suffix", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.endsWith";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string suffix;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, suffix, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::endsWith(stringValue, suffix));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringEndsWith(miniScript));
	}
	{
		//
		class ScriptMethodStringReplace: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringReplace(MiniScript* miniScript):
				MiniScript::ScriptMethod(
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
				return "string.replace";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string what;
				string by;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getStringValue(argumentValues, 2, by, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 3, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::replace(stringValue, what, by, beginIndex));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringReplace(miniScript));
	}
	{
		//
		class ScriptMethodStringIndexOf: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringIndexOf(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.indexOf";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(static_cast<int64_t>(StringTools::indexOf(stringValue, what, beginIndex)));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringIndexOf(miniScript));
	}
	{
		//
		class ScriptMethodStringFirstIndexOf: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringFirstIndexOf(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.firstIndexOf";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(static_cast<int64_t>(StringTools::firstIndexOf(stringValue, what, beginIndex)));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringFirstIndexOf(miniScript));
	}
	{
		//
		class ScriptMethodStringLastIndexOf: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringLastIndexOf(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.lastIndexOf";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string what;
				int64_t beginIndex = -1;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(static_cast<int64_t>(StringTools::lastIndexOf(stringValue, what, beginIndex)));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringLastIndexOf(miniScript));
	}
	{
		//
		class ScriptMethodStringSubString: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringSubString(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "endIndex", .optional = true, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.substring";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				int64_t beginIndex;
				int64_t endIndex = -1;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, beginIndex, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, endIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					if (endIndex == -1) {
						returnValue.setValue(StringTools::substring(stringValue, beginIndex));
					} else {
						returnValue.setValue(StringTools::substring(stringValue, beginIndex, endIndex));
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringSubString(miniScript));
	}
	{
		//
		class ScriptMethodStringEqualsIgnoreCase: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringEqualsIgnoreCase(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "other", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.equalsIgnoreCase";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string other;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, other, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::equalsIgnoreCase(stringValue, other));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringEqualsIgnoreCase(miniScript));
	}
	{
		//
		class ScriptMethodStringTrim: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringTrim(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.trim";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::trim(stringValue));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringTrim(miniScript));
	}
	{
		//
		class ScriptMethodStringRegexMatch: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringRegexMatch(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "pattern", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.regexMatch";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string pattern;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, pattern, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::regexMatch(stringValue, pattern));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringRegexMatch(miniScript));
	}
	{
		//
		class ScriptMethodStringRegexReplace: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringRegexReplace(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "pattern", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.regexReplace";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string pattern;
				string by;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, pattern, false) == false ||
					MiniScript::getStringValue(argumentValues, 2, by, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::regexReplace(stringValue, pattern, by));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringRegexReplace(miniScript));
	}
	{
		//
		class ScriptMethodStringTokenize: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringTokenize(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "delimiters", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.tokenize";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string delimiters;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, delimiters, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto tokenizedStringVector = StringTools::tokenize(stringValue, delimiters);
					//
					returnValue.setType(MiniScript::TYPE_ARRAY);
					for (const auto& tokenizedString: tokenizedStringVector) {
						returnValue.pushArrayEntry(tokenizedString);
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringTokenize(miniScript));
	}
	{
		//
		class ScriptMethodStringSpace: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringSpace(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "spaces", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.space";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t spaces = 1;
				if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					string spacesString;
					for (auto i = 0; i < spaces; i++) spacesString+= " ";
					returnValue.setValue(spacesString);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringSpace(miniScript));
	}
	{
		//
		class ScriptMethodStringConcatenate: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringConcatenate(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::TYPE_STRING), miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.concatenate";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string result;
				for (const auto& argumentValue: argumentValues) {
					result+= argumentValue.getValueAsString();
				}
				returnValue.setValue(result);
			}
			bool isVariadic() const override {
				return true;
			}
		};
		miniScript->registerMethod(new ScriptMethodStringConcatenate(miniScript));
	}
	{
		//
		class ScriptMethodToStringUpperCase: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodToStringUpperCase(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.toUpperCase";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(StringTools::toUpperCase(stringValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodToStringUpperCase(miniScript));
	}
	{
		//
		class ScriptMethodToStringLowerCase: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodToStringLowerCase(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.toLowerCase";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(StringTools::toLowerCase(stringValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodToStringLowerCase(miniScript));
	}
	{
		//
		class ScriptMethodStringIsEmpty: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringIsEmpty(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.isEmpty";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(stringValue.empty());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringIsEmpty(miniScript));
	}
	{
		//
		class ScriptMethodStringIsFloat: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringIsFloat(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.isFloat";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(Float::is(stringValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringIsFloat(miniScript));
	}
	{
		//
		class ScriptMethodStringIsInteger: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringIsInteger(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.isInteger";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(Integer::is(stringValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringIsInteger(miniScript));
	}
	{
		//
		class ScriptMethodStringPadLeft: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringPadLeft(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "toSize", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.padLeft";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string by;
				int64_t toSize;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, by, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, toSize, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::padLeft(stringValue, by, toSize));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringPadLeft(miniScript));
	}
	{
		//
		class ScriptMethodStringPadRight: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringPadRight(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "toSize", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.padRight";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				string by;
				int64_t toSize;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, by, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, toSize, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::padRight(stringValue, by, toSize));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodStringPadRight(miniScript));
	}
}
