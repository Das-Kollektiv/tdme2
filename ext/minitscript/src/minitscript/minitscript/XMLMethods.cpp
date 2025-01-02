#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/XMLMethods.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/StringTools.h>

using std::span;

using minitscript::minitscript::XMLMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;
using _StringTools = minitscript::utilities::StringTools;

void XMLMethods::registerConstants(MinitScript* minitScript) {
}

void XMLMethods::registerMethods(MinitScript* minitScript) {
	// xml
	{
		//
		class MethodXMLCreateTag: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodXMLCreateTag(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_MAP, .name = "attributes", .optional = true, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "innerXML", .optional = true, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "xml.createTag";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string name;
				string innerXML;
				if ((arguments.size() == 1 || arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, name) == true &&
					(arguments.size() == 1 || arguments[1].getType() == MinitScript::TYPE_MAP) &&
					MinitScript::getStringValue(arguments, 2, innerXML, true) == true) {
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
					returnValue.setValue(xml);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodXMLCreateTag(minitScript));
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
