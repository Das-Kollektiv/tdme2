#include <tdme/tools/editor/misc/Markdown.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::tools::editor::misc::Markdown;

using tdme::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::StringTools;

const string Markdown::createGUIXML(const string& pathName, const string& fileName, vector<TOCEntry>& toc) {
	vector<string> markdownLines;
	FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, markdownLines);
	string xml;
	xml+= "<screen id='markdown' min-width='1024' min-height='768' max-width='3200' max-height='1800'>\n";
	xml+= "\t<scrollarea width='100%' height='100%'>\n";
	xml+= "\t\t<layout alignment='vertical' width='100%' height='auto'>\n";
	auto inTable = false;
	auto inTableIdx = 0;
	auto inCode = false;
	string inCodeString;
	int tocIdx = 1;
	auto tocLevel1 = 0;
	auto tocLevel2 = 0;
	auto tocLevel3 = 0;
	auto tocLevel4 = 0;
	for (auto markdownLine: markdownLines) {
		markdownLine = StringTools::replace(markdownLine, "&nbsp;", " ");
		//
		markdownLine = StringTools::replace(markdownLine, "\\<", "<");
		markdownLine = StringTools::replace(markdownLine, "\\>", ">");
		// TODO: support <sub> and </sub>
		markdownLine = StringTools::replace(markdownLine, "<sub>", "");
		markdownLine = StringTools::replace(markdownLine, "</sub>", "");
		// TODO: support <i> and </i>
		markdownLine = StringTools::replace(markdownLine, "<i>", "");
		markdownLine = StringTools::replace(markdownLine, "</i>", "");
		//
		auto markdownLineTrimmed = StringTools::trim(markdownLine);
		//
		if (inTable == true && StringTools::startsWith(markdownLine, "|") == false) {
			inTable = false;
			inTableIdx = 0;
			xml+= "</table>\n";
		}
		if (StringTools::startsWith(markdownLine, "```") == true) {
			if (inCode == false) {
				inCode = true;
			} else {
				xml+= "<space height='10'/>\n";
				xml+= "<styled-text font='{$font.default}' size='{$fontsize.default}' color='{$color.font_normal}' background-color='{$color.element_midground}' border-color='{$color.element_frame}' border='1' padding='5' width='*' height='auto' preformatted='true'>\n";
				xml+= "	<![CDATA[\n";
				xml+= StringTools::replace(StringTools::replace(inCodeString, "[", "\\["), "]", "\\]");
				xml+= "	]]>\n";
				xml+= "</styled-text>\n";
				xml+= "<space height='10'/>\n";
				inCodeString.clear();
				inCode = false;
			}
		} else
		if (inCode == true) {
			inCodeString+= markdownLine + "\n";
		} else
		if (inTable == false && markdownLineTrimmed.empty() == true) {
			xml+= "<space height='20'/>\n";
		} else
		if (inTable == false && StringTools::startsWith(markdownLineTrimmed, "-") == true) {
			string textSize = "{$fontsize.default}";
			auto bulletPointIdx = StringTools::firstIndexOf(markdownLine, '-');
			auto bulletPoint = StringTools::trim(StringTools::substring(markdownLine, bulletPointIdx + 1));
			auto indent = bulletPointIdx / 2;
			xml+= "<layout alignment='horizontal' width='100%' height='auto'>\n";
			xml+= "\t<space width='" + to_string((bulletPointIdx + 1) * 10) + "'/>\n";
			xml+= "\t<styled-text font='{$font.default}' size='" + textSize + "' color='{$color.font_normal}' width='*' height='auto'>• " + GUIParser::escape(bulletPoint) + "</styled-text>\n";
			xml+= "</layout>\n";
		} else
		// image
		if (StringTools::startsWith(markdownLine, "!") == true) {
			string tooltip;
			{
				auto tooltipStartPosition = StringTools::indexOf(markdownLine, '[');
				auto tooltipEndPosition = StringTools::indexOf(markdownLine, ']');
				if (tooltipStartPosition != string::npos &&
					tooltipEndPosition != string::npos &&
					tooltipEndPosition > tooltipStartPosition) {
					tooltip = StringTools::substring(markdownLine, tooltipStartPosition + 1, tooltipEndPosition);
				}
			}
			string source;
			{
				string url;
				auto urlStartPosition = StringTools::indexOf(markdownLine, '(');
				auto urlEndPosition = StringTools::indexOf(markdownLine, ')');
				if (urlStartPosition != string::npos &&
					urlEndPosition != string::npos &&
					urlEndPosition > urlStartPosition) {
					url = StringTools::substring(markdownLine, urlStartPosition + 1, urlEndPosition);
				}
				if (StringTools::startsWith(url, "https://raw.githubusercontent.com/andreasdr/tdme2/master/") == true) {
					source = StringTools::substring(url, string("https://raw.githubusercontent.com/andreasdr/tdme2/master/").size());
				}
			}
			//
			if (source.empty() == false) {
				xml+= "<image src='" + GUIParser::escape(FileSystem::getInstance()->getCurrentWorkingPathName() + "/" + source) + "' tooltip='" + GUIParser::escape(tooltip) + "' />\n";
			}
		} else
		if (StringTools::startsWith(markdownLine, "|") == true) {
			if (inTable == false) {
				inTable = true;
				xml+= "<table width='auto' height='auto'>\n";
			}
			markdownLine = StringTools::trim(markdownLine);
			vector<string> tableColumnStrings = { "" };
			auto separator = true;
			for (auto i = 1; i < markdownLine.size(); i++) {
				if (markdownLine[i - 1] != '\\' && markdownLine[i] == '|') {
					if (i != markdownLine.size() - 1) tableColumnStrings.push_back(string());
					continue;
				}
				tableColumnStrings[tableColumnStrings.size() - 1]+= markdownLine[i];
				if (markdownLine[i] != '-' && markdownLine[i] != ' ' && markdownLine[i] != '\t' && markdownLine[i] != '|') separator = false;
			}
			if (separator == false) {
				xml+= "<table-row>\n";
				for (auto tableColumnString: tableColumnStrings) {
					tableColumnString = StringTools::replace(tableColumnString, "\\<", "<");
					tableColumnString = StringTools::replace(tableColumnString, "\\>", ">");
					tableColumnString = StringTools::replace(tableColumnString, "\\|", "|");
					string textSize = "{$fontsize.default}";
					string backgroundColor = (inTableIdx % 2) == 0?"{$color.element_midground}":"{$color.element_background}";
					xml+= "<table-cell padding='5' background-color='" + backgroundColor + "' border='1' border-color='{$color.element_frame}'>\n";
					xml+= "\t<text font='{$font.default}' size='" + textSize + "' text='" + GUIParser::escape(StringTools::trim(tableColumnString)) + "' color='{$color.font_normal}' width='auto' height='auto' />\n";
					xml+= "</table-cell>\n";
				}
				xml+= "</table-row>\n";
				inTableIdx++;
			}
		} else {
			// text
			string tocId;
			string textSize = "{$fontsize.default}";
			if (StringTools::startsWith(markdownLine, "####") == true) {
				markdownLine = StringTools::trim(StringTools::substring(markdownLine, 4));
				textSize = "{$fontsize.h4}";
				tocId = to_string(tocIdx++);
				tocLevel4++;
				string tocLevel;
				tocLevel+= StringTools::padLeft(to_string(tocLevel1), "0", 3) + ".";
				tocLevel+= StringTools::padLeft(to_string(tocLevel2), "0", 3) + ".";
				tocLevel+= StringTools::padLeft(to_string(tocLevel3), "0", 3) + ".";
				tocLevel+= StringTools::padLeft(to_string(tocLevel4), "0", 3) + ".";
				toc.push_back(
					{
						.id = tocId,
						.level = tocLevel,
						.title = markdownLine
					}
				);
			} else
			if (StringTools::startsWith(markdownLine, "###") == true) {
				markdownLine = StringTools::trim(StringTools::substring(markdownLine, 3));
				textSize = "{$fontsize.h3}";
				tocId = to_string(tocIdx++);
				tocLevel3++;
				tocLevel4 = 0;
				string tocLevel;
				tocLevel+= StringTools::padLeft(to_string(tocLevel1), "0", 3) + ".";
				tocLevel+= StringTools::padLeft(to_string(tocLevel2), "0", 3) + ".";
				tocLevel+= StringTools::padLeft(to_string(tocLevel3), "0", 3) + ".";
				toc.push_back(
					{
						.id = tocId,
						.level = tocLevel,
						.title = markdownLine
					}
				);
			} else
			if (StringTools::startsWith(markdownLine, "##") == true) {
				markdownLine = StringTools::trim(StringTools::substring(markdownLine, 2));
				textSize = "{$fontsize.h2}";
				tocId = to_string(tocIdx++);
				tocLevel2++;
				tocLevel3 = 0;
				tocLevel4 = 0;
				string tocLevel;
				tocLevel+= StringTools::padLeft(to_string(tocLevel1), "0", 3) + ".";
				tocLevel+= StringTools::padLeft(to_string(tocLevel2), "0", 3) + ".";
				toc.push_back(
					{
						.id = tocId,
						.level = tocLevel,
						.title = markdownLine
					}
				);
			} else
			if (StringTools::startsWith(markdownLine, "#") == true) {
				markdownLine = StringTools::trim(StringTools::substring(markdownLine, 1));
				textSize = "{$fontsize.h1}";
				tocId = to_string(tocIdx++);
				tocLevel1++;
				tocLevel2 = 0;
				tocLevel3 = 0;
				tocLevel4 = 0;
				string tocLevel;
				tocLevel+= StringTools::padLeft(to_string(tocLevel1), "0", 3) + ".";
				toc.push_back(
					{
						.id = tocId,
						.level = tocLevel,
						.title = markdownLine
					}
				);
			}
			xml+= "<styled-text " + (tocId.empty() == false?"id = '" + tocId + "' ":"") + "font='{$font.default}' size='" + textSize + "' color='{$color.font_normal}' width='*' height='auto'>" + GUIParser::escape(markdownLine) + "</styled-text>\n";
		}
	}
	if (inCode == true) {
		xml+= "<space height='10'/>\n";
		xml+= "<styled-text font='{$font.default}' size='{$fontsize.default}' color='{$color.font_normal}' background-color='{$color.element_midground}' border-color='{$color.element_frame}' border='1' padding='5' width='*' height='auto' preformatted='true'>\n";
		xml+= "	<![CDATA[\n";
		xml+= StringTools::replace(StringTools::replace(inCodeString, "[", "\\["), "]", "\\]");
		xml+= "	]]>\n";
		xml+= "</styled-text>\n";
		xml+= "<space height='10'/>\n";
	}
	if (inTable == true) xml+= "</table>\n";
	//
	xml+= "\t\t</layout>\n";
	xml+= "\t</scrollarea>\n";
	xml+= "</screen>\n";
	// FileSystem::getStandardFileSystem()->setContentFromString(".", "xxx.xml", xml);
	return xml;
}
