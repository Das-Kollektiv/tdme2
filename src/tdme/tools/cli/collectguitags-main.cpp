#include <map>
#include <set>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileNameFilter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>

#include <ext/tinyxml/tinyxml.h>

using std::map;
using std::set;
using std::string;
using std::to_string;
using std::vector;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

void scanDir(const string& folder, vector<string>& totalFiles) {
	class ListFilter : public virtual FileNameFilter {
		public:
			virtual ~ListFilter() {}

			bool accept(const string& pathName, const string& fileName) override {
				if (fileName == ".") return false;
				if (fileName == "..") return false;
				if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) return true;
				if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".xml") == true) return true;
				return false;
			}
	};

	ListFilter listFilter;
	vector<string> files;

	FileSystem::getInstance()->list(folder, files, &listFilter);

	for (const auto& fileName: files) {
		if (StringTools::endsWith(fileName, ".xml") == true) {
			totalFiles.push_back(folder + "/" + fileName);
		} else {
			scanDir(folder + "/" + fileName, totalFiles);
		}
	}
}

void parseXMLNode(TiXmlElement* xmlParentNode, map<string, set<string>>& elementAttributeMap) {
	for (auto* node = xmlParentNode->FirstChildElement(); node != nullptr; node = node->NextSiblingElement()) {
		string nodeTagName = string(node->Value());
		auto definitionFileName = "resources/engine/gui/definitions/" + nodeTagName + ".xml";
		try {
			auto xml =
				FileSystem::getInstance()->getContentAsString(
					FileSystem::getInstance()->getPathName(definitionFileName),
					FileSystem::getInstance()->getFileName(definitionFileName)
				);
			Console::println("parseXMLNode(): Opened compound definition: " + definitionFileName);
			auto i = 0;
			while (i < xml.size()) {
				auto attributeStartIdx = xml.find("{", i);
				if (attributeStartIdx == string::npos) break;
				auto attributeEndIdx = xml.find("}", attributeStartIdx);
				if (attributeEndIdx == string::npos) break;
				auto attributeKey = StringTools::substring(xml, attributeStartIdx + 2, attributeEndIdx);
				if (StringTools::startsWith(attributeKey, "color.") == false &&  StringTools::startsWith(attributeKey, "font.") == false && StringTools::startsWith(attributeKey, "_TreeDepth__") == false) {
					if (attributeKey == "_InnerXML__") attributeKey = "* accepts XML within tag";
					elementAttributeMap[nodeTagName].insert(attributeKey);
				}
				i = attributeEndIdx + 1;
			}
		} catch (Exception& exception) {
			// ignore silently
		}
		if (StringTools::endsWith(nodeTagName, "-internal") == true) continue;
		if (elementAttributeMap.find(nodeTagName) == elementAttributeMap.end()) elementAttributeMap[nodeTagName] = {};
		for (TiXmlAttribute* attribute = node->FirstAttribute(); attribute != nullptr; attribute = attribute->Next()) {
			auto attributeKey = string(attribute->Name());
			auto attributeValue = string(attribute->Value());
			elementAttributeMap[nodeTagName].insert(attributeKey);
		}
		parseXMLNode(node, elementAttributeMap);
	}
}

void processFile(const string& fileName, map<string, set<string>>& elementAttributeMap) {
	Console::println("processFile(): " + fileName);
	auto xml =
		FileSystem::getInstance()->getContentAsString(
			FileSystem::getInstance()->getPathName(fileName),
			FileSystem::getInstance()->getFileName(fileName)
		);
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(xml.c_str());
	if (xmlDocument.Error() == true) {
		string message = string("processFile(): Could not parse XML. Error='") + string(xmlDocument.ErrorDesc()) + "':\n\n" + xml;
		Console::println(message);
		return;
	}
	parseXMLNode(xmlDocument.RootElement(), elementAttributeMap);
}

int main(int argc, char** argv)
{
	Console::println(string("collectguitags ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	if (argc < 2) {
		Console::println("Usage: collectguitags path_to_xmls [path_to_xmls]");
		Application::exit(Application::EXITCODE_FAILURE);
	}

	vector<string> files;
	for (auto i = 1; i < argc; i++) {
		auto pathToHeaders = string(argv[i]);
		Console::println("Scanning files: " + pathToHeaders);
		scanDir(pathToHeaders, files);
	}

	Console::println("Processing files");
	map<string, set<string>> elementAttributeMap;
	for (const auto& fileName: files) {
		processFile(fileName, elementAttributeMap);
	}

	//
	for (const auto& [elementName, elementAttributeVector]: elementAttributeMap) {
		Console::println(elementName);
		for (const auto& attribute: elementAttributeVector) {
			Console::println("\t" + attribute);
		}
		Console::println();
	}

	//
	Application::exit(Application::EXITCODE_SUCCESS);
}
