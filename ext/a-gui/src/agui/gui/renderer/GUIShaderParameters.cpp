#include <agui/gui/renderer/GUIShaderParameters.h>

#include <map>
#include <string>

#include <agui/agui.h>
#include <agui/gui/misc/GUIColor4.h>
#include <agui/gui/renderer/GUIShaderParameter.h>
#include <agui/math/Vector2.h>
#include <agui/math/Vector3.h>
#include <agui/math/Vector4.h>
#include <agui/utilities/Float.h>
#include <agui/utilities/Integer.h>
#include <agui/utilities/StringTools.h>

using agui::gui::renderer::GUIShaderParameters;

using std::map;
using std::string;

using agui::gui::misc::GUIColor4;
using agui::gui::renderer::GUIShaderParameter;
using agui::math::Vector2;
using agui::math::Vector3;
using agui::math::Vector4;
using agui::utilities::Float;
using agui::utilities::Integer;
using agui::utilities::StringTools;

const GUIShaderParameter GUIShaderParameters::getShaderParameter(const string& parameterName) const {
	auto shaderParameterIt = parameters.find(parameterName);
	if (shaderParameterIt == parameters.end()) {
		/*
		// TODO: implement me!
		auto defaultShaderParameter = Engine::getDefaultShaderParameter(shaderId, parameterName);
		if (defaultShaderParameter == nullptr) return GUIShaderParameter();
		return defaultShaderParameter->value;
		*/
		return GUIShaderParameter();
	}
	return shaderParameterIt->second;
}

void GUIShaderParameters::setShaderParameter(const string& parameterName, const GUIShaderParameter& parameterValue) {
	auto currentShaderParameter = getShaderParameter(parameterName);
	if (currentShaderParameter.getType() == GUIShaderParameter::TYPE_NONE) {
		Console::printLine("GUIShaderParameters::setShaderParameter(): no parameter for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
		return;
	}
	if (currentShaderParameter.getType() != parameterValue.getType()) {
		Console::printLine("GUIShaderParameters::setShaderParameter(): parameter type mismatch for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
	}
	parameters[parameterName] = parameterValue;
	changed = true;
}

void GUIShaderParameters::setShaderParameter(const string& parameterName, const string& parameterValueString) {
	auto currentShaderParameter = getShaderParameter(parameterName);
	if (currentShaderParameter.getType() == GUIShaderParameter::TYPE_NONE) {
		Console::printLine("GUIShaderParameters::setShaderParameter(): no parameter for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
		return;
	}
	GUIShaderParameter parameterValue;
	switch(currentShaderParameter.getType()) {
		case GUIShaderParameter::TYPE_NONE:
			break;
		case GUIShaderParameter::TYPE_BOOLEAN:
			parameterValue = GUIShaderParameter(StringTools::toLowerCase(StringTools::trim(parameterValueString)) == "true");
			break;
		case GUIShaderParameter::TYPE_INTEGER:
			parameterValue = GUIShaderParameter(Integer::parse(StringTools::trim(parameterValueString)));
			break;
		case GUIShaderParameter::TYPE_FLOAT:
			parameterValue = GUIShaderParameter(Float::parse(StringTools::trim(parameterValueString)));
			break;
		case GUIShaderParameter::TYPE_VECTOR2:
			{
				auto parameterValueStringArray = StringTools::tokenize(parameterValueString, ",");
				if (parameterValueStringArray.size() != 2) break;
				parameterValue = GUIShaderParameter(
					Vector2(
						Float::parse(StringTools::trim(parameterValueStringArray[0])),
						Float::parse(StringTools::trim(parameterValueStringArray[1]))
					)
				);
			}
			break;
		case GUIShaderParameter::TYPE_VECTOR3:
			{
				auto parameterValueStringArray = StringTools::tokenize(parameterValueString, ",");
				if (parameterValueStringArray.size() != 3) break;
				parameterValue = GUIShaderParameter(
					Vector3(
						Float::parse(StringTools::trim(parameterValueStringArray[0])),
						Float::parse(StringTools::trim(parameterValueStringArray[1])),
						Float::parse(StringTools::trim(parameterValueStringArray[2]))
					)
				);
			}
			break;
		case GUIShaderParameter::TYPE_VECTOR4:
			{
				auto parameterValueStringArray = StringTools::tokenize(parameterValueString, ",");
				if (parameterValueStringArray.size() != 4) break;
				parameterValue = GUIShaderParameter(
					Vector4(
						Float::parse(StringTools::trim(parameterValueStringArray[0])),
						Float::parse(StringTools::trim(parameterValueStringArray[1])),
						Float::parse(StringTools::trim(parameterValueStringArray[2])),
						Float::parse(StringTools::trim(parameterValueStringArray[3]))
					)
				);
			}
			break;
		case GUIShaderParameter::TYPE_COLOR4:
			{
				auto parameterValueStringArray = StringTools::tokenize(parameterValueString, ",");
				if (parameterValueStringArray.size() != 3 && parameterValueStringArray.size() != 4) break;
				parameterValue = GUIShaderParameter(
					GUIColor4(
						Float::parse(StringTools::trim(parameterValueStringArray[0])),
						Float::parse(StringTools::trim(parameterValueStringArray[1])),
						Float::parse(StringTools::trim(parameterValueStringArray[2])),
						parameterValueStringArray.size() == 4?Float::parse(StringTools::trim(parameterValueStringArray[3])):1.0f
					)
				);
			}
			break;
		default:
			break;
	}
	if (currentShaderParameter.getType() != parameterValue.getType()) {
		Console::printLine("GUIShaderParameters::setShaderParameter(): parameter type mismatch for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
	}
	parameters[parameterName] = parameterValue;
	changed = true;
}
