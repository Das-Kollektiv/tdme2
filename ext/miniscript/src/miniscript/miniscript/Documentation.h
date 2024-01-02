#pragma once

#include <string>
#include <set>
#include <unordered_set>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>
#include <miniscript/utilities/Properties.h>

using std::string;
using std::set;
using std::unordered_set;

using miniscript::utilities::Properties;

/**
 * MiniScript documentation
 * @author Andreas Drewke
 */
class miniscript::miniscript::Documentation {
public:
	/**
	 * Get all class method names
	 * @param miniScript MiniScript script instance
	 * @return all class method names
	 */
	static const set<string> getAllClassMethods(MiniScript* miniScript);

	/**
	 * Generate methods categories
	 * @param miniScript MiniScript script instance
	 * @param allClassMethods all class methods
	 * @param excludeMiniScript exclude MiniScript script instance
	 * @return methods categories
	 */
	static const set<string> getMethodsCategories(
		MiniScript* miniScript,
		const set<string>& allClassMethods,
		MiniScript* excludeMiniScript = nullptr);

	/**
	 * Generate classes documentation
	 * @param heading heading
	 * @param mainHeadingIdx main heading index
	 * @param miniScript MiniScript script instance
	 * @param descriptions descriptions
	 * @param descriptionPrefix description prefix
	 * @param allClassMethods all class methods
	 * @return documentation
	 */
	static const string generateClassesDocumentation(
		const string& heading,
		int mainHeadingIdx,
		MiniScript* miniScript,
		Properties& descriptions,
		const string& descriptionPrefix,
		const set<string>& allClassMethods
	);

	/**
	 * Generate methods documentation
	 * @param heading heading
	 * @param mainHeadingIdx main heading index
	 * @param miniScript MiniScript script instance
	 * @param descriptions descriptions
	 * @param descriptionPrefix desscription prefix
	 * @param allClassMethods all class methods
	 * @param excludeMiniScript exclude MiniScript script instance
	 * @return documentation
	 */
	static const string generateMethodsDocumentation(
		const string& heading,
		int mainHeadingIdx,
		MiniScript* miniScript,
		Properties& descriptions,
		const string& descriptionPrefix,
		const set<string>& allClassMethods,
		MiniScript* excludeMiniScript = nullptr
	);

	/**
	 * Generate operators documentation
	 * @param heading heading
	 * @param mainHeadingIdx main heading index
	 * @param miniScript MiniScript script instance
	 * @return documentation
	 */
	static const string generateOperatorsDocumentation(
		const string& heading,
		int mainHeadingIdx,
		MiniScript* miniScript
	);

	/**
	 * Generate variables documentation
	 * @param heading heading
	 * @param mainHeadingIdx main heading index
	 * @param miniScript MiniScript script instance
	 * @return documentation
	 */
	static const string generateVariablesDocumentation(
		const string& heading,
		int mainHeadingIdx,
		MiniScript* miniScript
	);

};
