#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using std::string;

using tdme::gui::nodes::GUIStyledTextNode;

/**
 * Text Tools
 * @author Andreas Drewke
 */
class tdme::tools::editor::misc::TextTools final
{
public:

	/**
	 * Find string
	 * @param textNode text node
	 * @param findString find string
	 * @param matchCase only find string that also matches case in find string
	 * @param wholeWord only find whole worlds
	 * @param selection only find in selection
	 * @param firstSearch first search
	 * @param index index
	 * @return success
	 */
	static bool find(GUIStyledTextNode* textNode, const string& findString, bool matchCase, bool wholeWord, bool selection, bool firstSearch, int& index);

	/**
	 * Count string
	 * @param textNode text node
	 * @param findString find string
	 * @param matchCase only find string that also matches case in find string
	 * @param wholeWord only find whole worlds
	 * @param selection only find in selection
	 */
	static int count(GUIStyledTextNode* textNode, const string& findString, bool matchCase, bool wholeWord, bool selection);

	/**
	 * Replace string
	 * @param textNode text node
	 * @param findString find string
	 * @param replaceString replace string
	 * @param matchCase only find string that also matches case in find string
	 * @param wholeWord only find whole worlds
	 * @param selection only find in selection
	 * @param index index
	 * @return success
	 */
	static bool replace(GUIStyledTextNode* textNode, const string& findString, const string& replaceString, bool matchCase, bool wholeWord, bool selection, int& index);

	/**
	 * Replace all string
	 * @param textNode text node
	 * @param findString find string
	 * @param replaceString replace string
	 * @param matchCase only find string that also matches case in find string
	 * @param wholeWord only find whole worlds
	 * @param selection only find in selection
	 * @return success
	 */
	static bool replaceAll(GUIStyledTextNode* textNode, const string& findString, const string& replaceString, bool matchCase, bool wholeWord, bool selection);

};
