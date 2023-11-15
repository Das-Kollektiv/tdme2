#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/miniscript/XMLMethods.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/StringTools.h>

using std::span;

using miniscript::miniscript::XMLMethods;

using miniscript::miniscript::MiniScript;
using miniscript::utilities::Console;
using miniscript::utilities::StringTools;

void XMLMethods::registerMethods(MiniScript* miniScript) {
	// xml
	{
		//
		class ScriptMethodXMLCreateTag: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodXMLCreateTag(MiniScript* miniScript):
				MiniScript::ScriptMethod(
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
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				string name;
				string innerXML;
				if (MiniScript::getStringValue(argumentValues, 0, name, false) == false ||
					(argumentValues.size() >= 2 && argumentValues[1].getType() != MiniScript::TYPE_MAP) ||
					MiniScript::getStringValue(argumentValues, 2, innerXML, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto mapPtr = argumentValues[1].getMapPointer();
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
		miniScript->registerMethod(new ScriptMethodXMLCreateTag(miniScript));
	}
}

inline const string XMLMethods::escape(const string& str) {
	string result;
	result = StringTools::replace(str, "&", "&amp;");
	result = StringTools::replace(result, "\"", "&quot;");
	result = StringTools::replace(result, "'", "&#39;");
	result = StringTools::replace(result, "<", "&lt;");
	result = StringTools::replace(result, ">", "&gt;");
	return result;
}
