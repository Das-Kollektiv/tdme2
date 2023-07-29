#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using std::map;
using std::set;
using std::stack;
using std::string;
using std::to_string;
using std::vector;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Integer;
using tdme::utilities::StringTools;

struct ClassDeclaration {
	struct ClassMemberDeclaration {
		enum DeclarationType { DECLARATIONTYPE_NONE, DECLARATIONTYPE_CONSTEXPR, DECLARATIONTYPE_ENUM, DECLARATIONTYPE_VARIABLE, DECLARATIONTYPE_METHOD };
		enum ModifierType { MODIFIERTYPE_PRIVATE, MODIFIERTYPE_PROTECTED, MODIFIERTYPE_PUBLIC };
		string description;
		string fullQualifiedName;
		string namespaceName;
		string name;
		DeclarationType declarationType;
		ModifierType modifierType { MODIFIERTYPE_PUBLIC };
		vector<string> additionalKeywords;
		// method only
		struct Argument {
			string type;
			string name;
		};
		vector<Argument> arguments;
		string returnValue;
	};
	string description;
	string fullQualifiedName;
	string namespaceName;
	string name;
	set<string> friendClasses;
	vector<ClassMemberDeclaration> members;
};

struct ClassDeclarationParserValues {
	enum ModifierType { MODIFIERTYPE_PRIVATE, MODIFIERTYPE_PROTECTED, MODIFIERTYPE_PUBLIC };
	ModifierType currentModifier { MODIFIERTYPE_PUBLIC };
	int curlyBracketCount { 0 };
};

static void parseDeclaration(const string& description, const string& token) {
	Console::println("parseDeclaration():");
	auto descriptionLines = StringTools::tokenize(description, "\n");
	Console::println("\tDescription");
	for (auto& descriptionLine: descriptionLines) Console::println("\t\t" + descriptionLine);
	Console::println("\tDeclaration");
	Console::println(token);
}

static void parseHpp(const string& hppFileName) {
	Console::println("Processing file: " + hppFileName);

	//
	map<string, string> usings;
	map<string, ClassDeclaration> classes;

	//
	auto hppCode = FileSystem::getInstance()->getContentAsString(".", hppFileName);

	//
	enum TokenType { TOKENTYPE_NONE, TOKENTYPE_INLINECOMMENT, TOKENTYPE_PREPROCESSOR, TOKENTYPE_USING, TOKENTYPE_CLASS, TOKENTYPE_CLASS_DECLARATION, TOKENTYPE_CLASS_DECLARATION_FRIEND_CLASS };
	array<string, 7> TOKENTYPENAME =
		{
			"TOKENTYPE_NONE",
			"TOKENTYPE_INLINECOMMENT",
			"TOKENTYPE_PREPROCESSOR",
			"TOKENTYPE_USING",
			"TOKENTYPE_CLASS",
			"TOKENTYPE_CLASS_DECLARATION",
			"TOKENTYPE_CLASS_DECLARATION_FRIEND_CLASS"
		};

	stack<TokenType> tokenTypeStack;
	tokenTypeStack.push(TOKENTYPE_NONE);
	string token;
	stack<ClassDeclaration> classDeclarationStack;
	stack<ClassDeclarationParserValues> classDeclarationParserValuesStack;
	char quote = 0;
	char lc = 0;
	string lastInlineComment;
	for (auto i = 0; i < hppCode.size(); i++) {
		auto c = hppCode[i];
		auto tokenType = tokenTypeStack.top();
		switch (tokenType) {
			case (TOKENTYPE_NONE):
			case (TOKENTYPE_CLASS_DECLARATION):
				{
					// class declaration + class declaration only state machine state transitions
					if (c == '{') {
						// TODO:
						auto& classDeclarationParserValues = classDeclarationParserValuesStack.top();
						classDeclarationParserValues.curlyBracketCount++;
						token+= c;
					} else
					if (c == '}') {
						// TODO:
						auto& classDeclarationParserValues = classDeclarationParserValuesStack.top();
						classDeclarationParserValues.curlyBracketCount--;
						token+= c;
						if (classDeclarationParserValues.curlyBracketCount == -1) {
							tokenTypeStack.pop();
							classDeclarationStack.pop();
							classDeclarationParserValuesStack.pop();
						} else
						if (classDeclarationParserValues.curlyBracketCount == 0) {
							if (StringTools::trim(token).empty() == false) {
								parseDeclaration(lastInlineComment, token);
							}
							token.clear();
							lastInlineComment.clear();
						}
					} else
					if (c == ';' && classDeclarationParserValuesStack.top().curlyBracketCount == 0) {
						if (StringTools::trim(token).empty() == false) {
							parseDeclaration(lastInlineComment, token);
						}
						token.clear();
						lastInlineComment.clear();
					} else
					if (c == '#') {
						tokenTypeStack.push(TOKENTYPE_PREPROCESSOR);
					} else
					if (c == ' ' || c == '\t' || c == '\n') {
						// global + class declarations
						auto tokenTrimmed = StringTools::trim(token);
						if (tokenTrimmed == "/*" || tokenTrimmed == "/**") {
							token+= c;
							tokenTypeStack.push(TOKENTYPE_INLINECOMMENT);
						} else
						if (tokenTrimmed == "using") {
							tokenTypeStack.push(TOKENTYPE_USING);
							token.clear();
						} else
						if (tokenTrimmed == "class") {
							tokenTypeStack.push(TOKENTYPE_CLASS);
							token.clear();
						} else
						if (tokenType == TOKENTYPE_CLASS_DECLARATION) {
							// class declaration only
							if (tokenTrimmed == "friend") {
								tokenTypeStack.push(TOKENTYPE_CLASS_DECLARATION_FRIEND_CLASS);
								token.clear();
							} else
							if (tokenTrimmed == "private:") {
								auto& classDeclarationValuesStack = classDeclarationParserValuesStack.top();
								classDeclarationValuesStack.currentModifier = ClassDeclarationParserValues::MODIFIERTYPE_PRIVATE;
								token.clear();
							} else
							if (tokenTrimmed == "protected:") {
								auto& classDeclarationValuesStack = classDeclarationParserValuesStack.top();
								classDeclarationValuesStack.currentModifier = ClassDeclarationParserValues::MODIFIERTYPE_PROTECTED;
								token.clear();
							} else
							if (tokenTrimmed == "public:") {
								auto& classDeclarationValuesStack = classDeclarationParserValuesStack.top();
								classDeclarationValuesStack.currentModifier = ClassDeclarationParserValues::MODIFIERTYPE_PUBLIC;
								token.clear();
							} else {
								token+= c;
							}
						}
					} else {
						token+= c;
					}
					break;
				}
			case (TOKENTYPE_INLINECOMMENT):
				{
					if (lc == '*' && c == '/') {
						token+= c;
						lastInlineComment = token;
						tokenTypeStack.pop();
						token.clear();
					} else {
						token+= c;
					}
					break;
				}
			case (TOKENTYPE_PREPROCESSOR):
				{
					if (c == '\n') {
						token = StringTools::trim(token);
						tokenTypeStack.pop();
						token.clear();
					} else {
						token+= c;
					}
					break;
				}
			case (TOKENTYPE_USING):
				{
					if (c == ';') {
						token = StringTools::trim(token);
						auto tokenComponents = StringTools::tokenize(token, ":");
						if (tokenComponents.size() > 1) usings[tokenComponents[tokenComponents.size() - 1]] = token;
						tokenTypeStack.pop();
						token.clear();
					} else {
						token+= c;
					}
					break;
				}
			case (TOKENTYPE_CLASS):
				{
					if (c == '{') {
						token = StringTools::trim(token);
						Console::println(TOKENTYPENAME[tokenType] + "(" + to_string(tokenType) + "): '" + token + "'");
						tokenTypeStack.push(TOKENTYPE_CLASS_DECLARATION);
						ClassDeclaration classDeclaration;
						auto classDeclarationComponents = StringTools::tokenize(token, " \t\n");
						if (classDeclarationComponents.empty() == false) {
							classDeclaration.fullQualifiedName = classDeclarationComponents[0];
							auto classNameComponents = StringTools::tokenize(classDeclaration.fullQualifiedName, ":");
							for (auto j = 0; j < classNameComponents.size() - 1; j++) {
								if (classDeclaration.namespaceName.empty() == false) {
									classDeclaration.namespaceName+= "::";
								}
								classDeclaration.namespaceName+= classNameComponents[j];
							}
							classDeclaration.name = classNameComponents[classNameComponents.size() - 1];
							classDeclaration.description = lastInlineComment;
							lastInlineComment.clear();
						}
						classDeclarationStack.push(classDeclaration);
						classDeclarationParserValuesStack.push(ClassDeclarationParserValues());
						token.clear();
						break;
					} else {
						token+= c;
					}
					break;
				}
			case (TOKENTYPE_CLASS_DECLARATION_FRIEND_CLASS):
				{
					if (c == ';') {
						token = StringTools::trim(token);
						auto tokenComponents = StringTools::tokenize(token, " \t");
						if (tokenComponents.empty() == false) {
							if (tokenComponents[0] == "class") tokenComponents.erase(tokenComponents.begin());
							if (tokenComponents.empty() == false) {
								auto& classDeclaration = classDeclarationStack.top();
								auto friendClassTokens = StringTools::tokenize(tokenComponents[0], ":");
								if (friendClassTokens.size() > 1) {
									classDeclaration.friendClasses.insert(tokenComponents[0]);
								} else {
									classDeclaration.friendClasses.insert(classDeclaration.namespaceName + "::" + tokenComponents[0]);
								}
							}
						}
						tokenTypeStack.pop();
						token.clear();
					} else {
						token+= c;
					}
					break;
				}
			default:
			{
				Console::println("Unknown token type: " + TOKENTYPENAME[tokenType] + "(" + to_string(tokenType) + ")");
			}
		}
		lc = c;
	}

	Console::println("Summary: ");
	Console::println();
	Console::println("Usings: ");
	for (const auto& [usingShortClassName, usingFullClassName]: usings) {
		Console::println("\t" + usingShortClassName + " --> " + usingFullClassName);
	}
	Console::println("Classes: ");
	for (const auto& [className, classDeclaration]: classes) {
		Console::println("\t" + classDeclaration.name + "(" + classDeclaration.namespaceName + ")");
		Console::println("\t\tDescription:");
		auto descriptionLines = StringTools::tokenize(classDeclaration.description, "\n");
		for (auto& descriptionLine: descriptionLines) Console::println("\t\t\t" + descriptionLine);
		for (auto& friendClass: classDeclaration.friendClasses) {
			Console::println("\t\tFriend Class: " + friendClass);
		}
	}
}

int main(int argc, char** argv)
{
	Console::println(string("parsec++") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if (argc < 2) {
		Console::println("Usage: parseh++ path/to/file.h");
		Application::exit(1);
	}

	//
	parseHpp(argv[1]);
}
