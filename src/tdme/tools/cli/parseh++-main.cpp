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

void processFile(const string& hppFileName) {
	Console::println("Processing file: " + hppFileName);

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
	enum TokenType { TOKENTYPE_NONE, TOKENTYPE_INLINECOMMENT, TOKENTYPE_PREPROCESSOR, TOKENTYPE_USING, TOKENTYPE_CLASS, TOKENTYPE_CLASS_DECLARATION, TOKENTYPE_CLASS_DECLARATION_FRIEND_CLASS };

	struct ClassDeclaration {
		enum ModifierType { MODIFIERTYPE_PRIVATE, MODIFIERTYPE_PROTECTED, MODIFIERTYPE_PUBLIC };
		string description;
		string fullQualifiedName;
		string namespaceName;
		string name;
		set<string> friendClasses;
		ModifierType currentModifier { MODIFIERTYPE_PUBLIC };
		int curlyBracketCount { 0 };
	};

	//
	map<string, string> usings;
	map<string, ClassDeclaration> classes;

	//
	auto hppCode = FileSystem::getInstance()->getContentAsString(".", hppFileName);
	stack<TokenType> tokenTypeStack;
	tokenTypeStack.push(TOKENTYPE_NONE);
	string token;
	stack<ClassDeclaration> classDeclarationStack;
	int classDeclarationCurlyBrackets = 0;
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
					if (tokenType == TOKENTYPE_CLASS_DECLARATION) {
						if (c == '{') {
							// TODO:
							auto& classDeclaration = classDeclarationStack.top();
							classDeclaration.curlyBracketCount++;
							continue;
						} else
						if (c == '}') {
							// TODO:
							auto& classDeclaration = classDeclarationStack.top();
							classDeclaration.curlyBracketCount--;
							if (classDeclaration.curlyBracketCount == 0) {
								classes[classDeclaration.name] = classDeclaration;
								classDeclarationStack.top();
							}
							continue;
						} else
						if (c == ';') {
							// TODO:
							Console::println("TOKENTYPE_CLASS_DECLARATION: '" + token + "'");
							token.clear();
							continue;
						}
					}
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
								auto& classDeclaration = classDeclarationStack.top();
								classDeclaration.currentModifier = ClassDeclaration::MODIFIERTYPE_PRIVATE;
								token.clear();
							} else
							if (tokenTrimmed == "protected:") {
								auto& classDeclaration = classDeclarationStack.top();
								classDeclaration.currentModifier = ClassDeclaration::MODIFIERTYPE_PROTECTED;
								token.clear();
							} else
							if (tokenTrimmed == "public:") {
								auto& classDeclaration = classDeclarationStack.top();
								classDeclaration.currentModifier = ClassDeclaration::MODIFIERTYPE_PUBLIC;
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
	for (auto& usingIt: usings) {
		Console::println("\t" + usingIt.first + " --> " + usingIt.second);
	}
	Console::println("Classes: ");
	for (auto& classIt: classes) {
		auto& classDeclaration = classIt.second;
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
	processFile(argv[1]);
}
