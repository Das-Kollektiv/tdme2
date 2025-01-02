#include <regex>
#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/math/Math.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/StringMethods.h>
#include <minitscript/utilities/Character.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Float.h>
#include <minitscript/utilities/Integer.h>
#include <minitscript/utilities/UTF8StringTokenizer.h>
#include <minitscript/utilities/UTF8StringTools.h>
#include <minitscript/utilities/UTF8CharacterIterator.h>

using std::smatch;
using std::span;

using minitscript::minitscript::StringMethods;

using minitscript::minitscript::MinitScript;

using _Math = minitscript::math::Math;
using _Character = minitscript::utilities::Character;
using _Console = minitscript::utilities::Console;
using _Float = minitscript::utilities::Float;
using _Integer = minitscript::utilities::Integer;
using _UTF8StringTools = minitscript::utilities::UTF8StringTools;
using _UTF8CharacterIterator = minitscript::utilities::UTF8CharacterIterator;

void StringMethods::registerConstants(MinitScript* minitScript) {
}

void StringMethods::registerMethods(MinitScript* minitScript) {
	// string functions
	{
		//
		class MethodString: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodString(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true) {
					returnValue.setValue(stringValue);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodString(minitScript));
	}
	{
		//
		class MethodStringGetSize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringGetSize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::getSize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true) {
					returnValue.setValue(static_cast<int64_t>(_UTF8StringTools::getLength(stringValue, arguments[0].getStringValueCache())));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringGetSize(minitScript));
	}
	{
		//
		class MethodStringCharAt: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringCharAt(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::charAt";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				int64_t index;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getIntegerValue(arguments, 1, index) == true) {
					returnValue.setValue(_UTF8StringTools::getCharAt(stringValue, index, arguments[0].getStringValueCache()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringCharAt(minitScript));
	}
	{
		//
		class MethodStringCodePointAt: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringCodePointAt(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::codePointAt";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				int64_t index;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getIntegerValue(arguments, 1, index) == true) {
					returnValue.setValue(static_cast<int64_t>(_UTF8StringTools::getCodePointAt(stringValue, index, arguments[0].getStringValueCache())));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringCodePointAt(minitScript));
	}
	{
		//
		class MethodStringStartsWith: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringStartsWith(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "prefix", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::startsWith";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string prefix;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, prefix) == true) {
					returnValue.setValue(_UTF8StringTools::startsWith(stringValue, prefix));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringStartsWith(minitScript));
	}
	{
		//
		class MethodStringEndsWith: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringEndsWith(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "suffix", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::endsWith";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string suffix;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, suffix) == true) {
					returnValue.setValue(_UTF8StringTools::endsWith(stringValue, suffix));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringEndsWith(minitScript));
	}
	{
		//
		class MethodStringReplace: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringReplace(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::replace";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string what;
				string by;
				int64_t beginIndex = 0;
				if ((arguments.size() == 3 || arguments.size() == 4) &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, what) == true &&
					MinitScript::getStringValue(arguments, 2, by) == true &&
					MinitScript::getIntegerValue(arguments, 3, beginIndex, true) == true) {
					returnValue.setValue(_UTF8StringTools::replace(stringValue, what, by, beginIndex, arguments[0].getStringValueCache()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringReplace(minitScript));
	}
	{
		//
		class MethodStringIndexOf: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringIndexOf(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::indexOf";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, what) == true &&
					MinitScript::getIntegerValue(arguments, 2, beginIndex, true) == true) {
					returnValue.setValue(_UTF8StringTools::indexOf(stringValue, what, beginIndex, arguments[0].getStringValueCache()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringIndexOf(minitScript));
	}
	{
		//
		class MethodStringFirstIndexOf: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringFirstIndexOf(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::firstIndexOf";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, what) == true &&
					MinitScript::getIntegerValue(arguments, 2, beginIndex, true) == true) {
					returnValue.setValue(_UTF8StringTools::firstIndexOf(stringValue, what, beginIndex, arguments[0].getStringValueCache()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringFirstIndexOf(minitScript));
	}
	{
		//
		class MethodStringLastIndexOf: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringLastIndexOf(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::lastIndexOf";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, what) == true &&
					MinitScript::getIntegerValue(arguments, 2, beginIndex, true) == true) {
					returnValue.setValue(_UTF8StringTools::lastIndexOf(stringValue, what, beginIndex, arguments[0].getStringValueCache()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringLastIndexOf(minitScript));
	}
	{
		//
		class MethodStringFirstIndexOfChars: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringFirstIndexOfChars(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::firstIndexOfChars";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, what) == true &&
					MinitScript::getIntegerValue(arguments, 2, beginIndex, true) == true) {
					returnValue.setValue(
						static_cast<int64_t>(
							_UTF8StringTools::firstIndexOfChars(
								stringValue,
								what,
								beginIndex,
								arguments[0].getStringValueCache(),
								arguments[1].getStringValueCache()
							)
						)
					);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringFirstIndexOfChars(minitScript));
	}
	{
		//
		class MethodStringLastIndexOfChars: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringLastIndexOfChars(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "endIndex", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::lastIndexOfChars";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string what;
				int64_t endIndex = string::npos;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, what) == true &&
					MinitScript::getIntegerValue(arguments, 2, endIndex, true) == true) {
					returnValue.setValue(
						static_cast<int64_t>(
							_UTF8StringTools::lastIndexOfChars(
								stringValue,
								what,
								endIndex,
								arguments[0].getStringValueCache(),
								arguments[1].getStringValueCache()
							)
						)
					);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringLastIndexOfChars(minitScript));
	}
	{
		//
		class MethodStringSubString: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringSubString(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "beginIndex", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "endIndex", .optional = true, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::substring";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				int64_t beginIndex;
				int64_t endIndex = string::npos;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getIntegerValue(arguments, 1, beginIndex) == true &&
					MinitScript::getIntegerValue(arguments, 2, endIndex, true) == true) {
					// utf8 character iterator
					returnValue.setValue(_UTF8StringTools::substring(stringValue, beginIndex, endIndex));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringSubString(minitScript));
	}
	{
		//
		class MethodStringEqualsIgnoreCase: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringEqualsIgnoreCase(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "other", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::equalsIgnoreCase";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string other;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, other) == true) {
					returnValue.setValue(_UTF8StringTools::equalsIgnoreCase(stringValue, other, arguments[0].getStringValueCache(), arguments[1].getStringValueCache()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringEqualsIgnoreCase(minitScript));
	}
	{
		//
		class MethodStringTrim: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringTrim(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::trim";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true) {
					returnValue.setValue(_UTF8StringTools::trim(stringValue, arguments[0].getStringValueCache()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringTrim(minitScript));
	}
	{
		//
		class MethodStringRegexMatch: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringRegexMatch(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "pattern", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_ARRAY, .name = "matches", .optional = true, .reference = true, .nullable = true },
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::regexMatch";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string pattern;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, pattern) == true) {
					if (arguments.size() == 3) {
						smatch matches;
						returnValue.setValue(_UTF8StringTools::regexMatch(stringValue, pattern, &matches));
						arguments[2].setType(MinitScript::TYPE_ARRAY);
						arguments[2].clearArray();
						for (const auto& match: matches) {
							arguments[2].pushArrayEntry(MinitScript::Variable(string(match.str())));
						}
					} else {
						returnValue.setValue(_UTF8StringTools::regexMatch(stringValue, pattern));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringRegexMatch(minitScript));
	}
	{
		//
		class MethodStringRegexSearch: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringRegexSearch(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "pattern", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_ARRAY, .name = "matches", .optional = true, .reference = true, .nullable = true },
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::regexSearch";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string pattern;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, pattern) == true) {
					if (arguments.size() == 3) {
						smatch matches;
						returnValue.setValue(_UTF8StringTools::regexSearch(stringValue, pattern, &matches));
						arguments[2].setType(MinitScript::TYPE_ARRAY);
						arguments[2].clearArray();
						for (const auto& match: matches) {
							arguments[2].pushArrayEntry(MinitScript::Variable(string(match.str())));
						}
					} else {
						returnValue.setValue(_UTF8StringTools::regexSearch(stringValue, pattern));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringRegexSearch(minitScript));
	}
	{
		//
		class MethodStringRegexReplace: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringRegexReplace(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "pattern", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::regexReplace";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string pattern;
				string by;
				if (arguments.size() == 3 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, pattern) == true &&
					MinitScript::getStringValue(arguments, 2, by) == true) {
					returnValue.setValue(_UTF8StringTools::regexReplace(stringValue, pattern, by));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringRegexReplace(minitScript));
	}
	{
		//
		class MethodStringTokenize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringTokenize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "delimiters", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_ARRAY
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::tokenize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string delimiters;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, delimiters) == true) {
					auto tokenizedStringVector = _UTF8StringTools::tokenize(stringValue, delimiters);
					returnValue.setType(MinitScript::TYPE_ARRAY);
					for (const auto& tokenizedString: tokenizedStringVector) {
						returnValue.pushArrayEntry(tokenizedString);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringTokenize(minitScript));
	}
	{
		//
		class MethodStringGenerate: public MinitScript::Method {
		private:
			MinitScript *minitScript { nullptr };
		public:
			MethodStringGenerate(MinitScript *minitScript) :
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "count", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "String::generate";
			}
			void executeMethod(span<MinitScript::Variable> &arguments, MinitScript::Variable &returnValue, const MinitScript::SubStatement& subStatement) override {
				string what;
				int64_t count = 1;
				if ((arguments.size() == 1 || arguments.size() == 2) &&
					MinitScript::getStringValue(arguments, 0, what) == true &&
					MinitScript::getIntegerValue(arguments, 1, count, true) == true) {
					returnValue.setValue(_UTF8StringTools::generate(what, count));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringGenerate(minitScript));
	}
	{
		//
		class MethodStringIndent: public MinitScript::Method {
		private:
			MinitScript *minitScript { nullptr };
		public:
			MethodStringIndent(MinitScript *minitScript) :
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "with", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "count", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "String::indent";
			}
			void executeMethod(span<MinitScript::Variable> &arguments, MinitScript::Variable &returnValue, const MinitScript::SubStatement& subStatement) override {
				string src;
				string with;
				int64_t count = 1;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, src) == true &&
					MinitScript::getStringValue(arguments, 1, with) == true &&
					MinitScript::getIntegerValue(arguments, 2, count, true) == true) {
					returnValue.setValue(_UTF8StringTools::indent(src, with, count));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringIndent(minitScript));
	}
	{
		//
		class MethodStringConcatenate: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringConcatenate(MinitScript* minitScript): MinitScript::Method({}, MinitScript::TYPE_STRING), minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::concatenate";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
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
		minitScript->registerMethod(new MethodStringConcatenate(minitScript));
	}
	{
		//
		class MethodToStringUpperCase: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodToStringUpperCase(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::toUpperCase";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true) {
					returnValue.setValue(_UTF8StringTools::toUpperCase(stringValue, arguments[0].getStringValueCache()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodToStringUpperCase(minitScript));
	}
	{
		//
		class MethodToStringLowerCase: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodToStringLowerCase(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::toLowerCase";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true) {
					returnValue.setValue(_UTF8StringTools::toLowerCase(stringValue, arguments[0].getStringValueCache()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodToStringLowerCase(minitScript));
	}
	{
		//
		class MethodStringIsEmpty: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringIsEmpty(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::isEmpty";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true) {
					returnValue.setValue(stringValue.empty());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringIsEmpty(minitScript));
	}
	{
		//
		class MethodStringIsFloat: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringIsFloat(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::isFloat";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true) {
					returnValue.setValue(_Float::is(stringValue));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringIsFloat(minitScript));
	}
	{
		//
		class MethodStringIsInteger: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringIsInteger(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::isInteger";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true) {
					returnValue.setValue(_Integer::is(stringValue));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringIsInteger(minitScript));
	}
	{
		//
		class MethodStringPadLeft: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringPadLeft(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "toLength", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::padLeft";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string by;
				int64_t toLength;
				if (arguments.size() == 3 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, by) == true &&
					MinitScript::getIntegerValue(arguments, 2, toLength) == true) {
					returnValue.setValue(_UTF8StringTools::padLeft(stringValue, by, toLength, arguments[0].getStringValueCache()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringPadLeft(minitScript));
	}
	{
		//
		class MethodStringPadRight: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringPadRight(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "toLength", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::padRight";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				string by;
				int64_t toLength;
				if (arguments.size() == 3 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true &&
					MinitScript::getStringValue(arguments, 1, by) == true &&
					MinitScript::getIntegerValue(arguments, 2, toLength) == true) {
					returnValue.setValue(_UTF8StringTools::padRight(stringValue, by, toLength, arguments[0].getStringValueCache()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringPadRight(minitScript));
	}
	{
		//
		class MethodStringToByteArray: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringToByteArray(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_BYTEARRAY
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::toByteArray";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, stringValue) == true) {
					returnValue.setType(MinitScript::TYPE_BYTEARRAY);
					for (auto i = 0; i < stringValue.size(); i++) returnValue.pushByteArrayEntry(stringValue[i]);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringToByteArray(minitScript));
	}
	{
		//
		class MethodStringFromByteArray: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringFromByteArray(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BYTEARRAY, .name = "byteArray", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::fromByteArray";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_BYTEARRAY) {
					auto byteArrayPointer = arguments[0].getByteArrayPointer();
					if (byteArrayPointer != nullptr) {
						returnValue.setValue(string((const char*)(byteArrayPointer->data()), byteArrayPointer->size()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringFromByteArray(minitScript));
	}
	{
		//
		class MethodStringFromCodePoint: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodStringFromCodePoint(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "codePoint", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "String::fromCodePoint";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t codePoint;
				if (arguments.size() == 1 &&
					MinitScript::getIntegerValue(arguments, 0, codePoint) == true) {
					returnValue.setValue(_Character::toString(codePoint));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodStringFromCodePoint(minitScript));
	}
}
