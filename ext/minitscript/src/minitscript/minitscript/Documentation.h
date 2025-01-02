#pragma once

#include <string>
#include <set>
#include <unordered_set>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/fwd-minitscript.h>
#include <minitscript/utilities/Properties.h>

using std::string;
using std::set;
using std::unordered_set;

// namespaces
namespace minitscript {
namespace minitscript {
	using ::minitscript::utilities::Properties;
}
}

/**
 * MinitScript documentation
 * @author Andreas Drewke
 */
class minitscript::minitscript::Documentation {
public:
	/**
	 * Get all class method names
	 * @param minitScript MinitScript script instance
	 * @return all class method names
	 */
	static const set<string> getAllClassMethods(MinitScript* minitScript);

	/**
	 * Generate methods categories
	 * @param minitScript MinitScript script instance
	 * @param allClassMethods all class methods
	 * @param excludeMinitScript exclude MinitScript script instance
	 * @return methods categories
	 */
	static const set<string> getMethodsCategories(
		MinitScript* minitScript,
		const set<string>& allClassMethods,
		MinitScript* excludeMinitScript = nullptr);

	/**
	 * Generate classes documentation
	 * @param heading heading
	 * @param mainHeadingIdx main heading index
	 * @param minitScript MinitScript script instance
	 * @param descriptions descriptions
	 * @param descriptionPrefix description prefix
	 * @param allClassMethods all class methods
	 * @return documentation
	 */
	static const string generateClassesDocumentation(
		const string& heading,
		int mainHeadingIdx,
		MinitScript* minitScript,
		Properties& descriptions,
		const string& descriptionPrefix,
		const set<string>& allClassMethods
	);

	/**
	 * Generate functions documentation
	 * @param heading heading
	 * @param mainHeadingIdx main heading index
	 * @param minitScript MinitScript script instance
	 * @param descriptions descriptions
	 * @param descriptionPrefix desscription prefix
	 * @param allClassMethods all class methods
	 * @param excludeMinitScript exclude MinitScript script instance
	 * @return documentation
	 */
	static const string generateFunctionsDocumentation(
		const string& heading,
		int mainHeadingIdx,
		MinitScript* minitScript,
		Properties& descriptions,
		const string& descriptionPrefix,
		const set<string>& allClassMethods,
		MinitScript* excludeMinitScript = nullptr
	);

	/**
	 * Generate operators documentation
	 * @param heading heading
	 * @param mainHeadingIdx main heading index
	 * @param minitScript MinitScript script instance
	 * @return documentation
	 */
	static const string generateOperatorsDocumentation(
		const string& heading,
		int mainHeadingIdx,
		MinitScript* minitScript
	);

	/**
	 * Generate variables documentation
	 * @param heading heading
	 * @param mainHeadingIdx main heading index
	 * @param minitScript MinitScript script instance
	 * @return documentation
	 */
	static const string generateVariablesDocumentation(
		const string& heading,
		int mainHeadingIdx,
		MinitScript* minitScript
	);

};
