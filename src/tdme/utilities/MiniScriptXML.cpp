#include <span>

#include <tdme/tdme.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptXML.h>

using std::span;

using tdme::utilities::MiniScriptXML;

using tdme::gui::GUIParser;
using tdme::utilities::MiniScript;

void MiniScriptXML::registerMethods(MiniScript* miniScript) {
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
						{ .type = MiniScript::ScriptVariableType::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_MAP, .name = "attributes", .optional = true, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_STRING, .name = "innerXML", .optional = true, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_STRING
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
					(argumentValues.size() >= 2 && argumentValues[1].getType() != MiniScript::ScriptVariableType::TYPE_MAP) ||
					MiniScript::getStringValue(argumentValues, 2, innerXML, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto mapPtr = argumentValues[1].getMapPointer();
					string xml;
					xml+= "<" + name;
					if (mapPtr != nullptr && mapPtr->empty() == false) {
						for(const auto& [mapEntryName, mapEntryValue]: *mapPtr) {
							xml+= " " + mapEntryName + "=\"" + GUIParser::escape(mapEntryValue->getValueAsString()) + "\"";
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
