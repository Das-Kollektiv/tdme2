#pragma once

#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>

#include <tdme/tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

#include <ext/tinyxml/tinyxml.h>

using std::string;
using std::vector;

/**
 * Markdown
 * @author Andreas Drewke
 */
class tdme::tools::editor::misc::Markdown final
{
public:
	struct TOCEntry {
		string id;
		string level;
		string title;
	};

	/**
	 * Create mark down GUI XML
	 * @param pathName markdown path name
	 * @param pathName markdown file name
	 * @param xml resulting xml
	 * @param toc resulting table of contents
	 * @returns GUI XML
	 */
	static const string createGUIXML(const string& pathName, const string& fileName, vector<TOCEntry>& toc);

};
