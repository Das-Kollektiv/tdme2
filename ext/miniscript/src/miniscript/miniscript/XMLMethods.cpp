#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/miniscript/XMLMethods.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/StringTools.h>

using std::span;

using miniscript::miniscript::XMLMethods;

using miniscript::miniscript::MiniScript;

using _Console = miniscript::utilities::Console;
using _StringTools = miniscript::utilities::StringTools;

void XMLMethods::registerConstants(MiniScript* miniScript) {
}

void XMLMethods::registerMethods(MiniScript* miniScript) {
	// xml
	{
		//
		class MethodXMLCreateTag: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodXMLCreateTag(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_MAP, .name = "attributes", .optional = true, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "innerXML", .optional = true, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "xml.createTag";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				string name;
				string innerXML;
				if (MiniScript::getStringValue(arguments, 0, name, false) == false ||
					(arguments.size() >= 2 && arguments[1].getType() != MiniScript::TYPE_MAP) ||
					MiniScript::getStringValue(arguments, 2, innerXML, true) == false) {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto mapPtr = arguments[1].getMapPointer();
					string xml;
					xml+= "<" + name;
					if (mapPtr != nullptr && mapPtr->empty() == false) {
						for(const auto& [mapEntryName, mapEntryValue]: *mapPtr) {
							xml+= " " + mapEntryName + "=\"" + escape(mapEntryValue->getValueAsString()) + "\"";
						}
					}
					if (innerXML.empty() == true) {
						xml+= "/>";
					} else {
						xml+= ">" + innerXML + "</" + name + ">";
					}
					//
					returnValue.setValue(xml);
				}
			}
		};
		miniScript->registerMethod(new MethodXMLCreateTag(miniScript));
	}
}

inline const string XMLMethods::escape(const string& str) {
	string result;
	result = _StringTools::replace(str, "&", "&amp;");
	result = _StringTools::replace(result, "\"", "&quot;");
	result = _StringTools::replace(result, "'", "&#39;");
	result = _StringTools::replace(result, "<", "&lt;");
	result = _StringTools::replace(result, ">", "&gt;");
	return result;
}
