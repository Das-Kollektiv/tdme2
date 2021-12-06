#include <tdme/engine/EntityShaderParameters.h>

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTools.h>

using tdme::engine::EntityShaderParameters;

using std::map;
using std::string;

using tdme::engine::Engine;
using tdme::engine::ShaderParameter;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::StringTools;

const ShaderParameter EntityShaderParameters::getShaderParameter(const string& parameterName) const {
	auto shaderParameterIt = parameters.find(parameterName);
	if (shaderParameterIt == parameters.end()) {
		return Engine::getDefaultShaderParameter(shaderId, parameterName);
	}
	auto& shaderParameter = shaderParameterIt->second;
	return shaderParameter;
}

void EntityShaderParameters::setShaderParameter(const string& parameterName, const ShaderParameter& parameterValue) {
	auto currentShaderParameter = getShaderParameter(parameterName);
	if (currentShaderParameter.getType() == ShaderParameter::TYPE_NONE) {
		Console::println("EntityShaderParameters::setShaderParameter(): no parameter for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
		return;
	}
	if (currentShaderParameter.getType() != parameterValue.getType()) {
		Console::println("EntityShaderParameters::setShaderParameter(): parameter type mismatch for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
	}
	parameters[parameterName] = parameterValue;
	changed = true;
}

void EntityShaderParameters::setShaderParameter(const string& parameterName, const string& parameterValueString) {
	auto currentShaderParameter = getShaderParameter(parameterName);
	if (currentShaderParameter.getType() == ShaderParameter::TYPE_NONE) {
		Console::println("EntityShaderParameters::setShaderParameter(): no parameter for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
		return;
	}
	ShaderParameter parameterValue;
	switch(currentShaderParameter.getType()) {
		case ShaderParameter::TYPE_NONE:
			break;
		case ShaderParameter::TYPE_BOOLEAN:
			parameterValue = ShaderParameter(StringTools::toLowerCase(StringTools::trim(parameterValueString)) == "true");
			break;
		case ShaderParameter::TYPE_INTEGER:
			parameterValue = ShaderParameter(Integer::parseInt(StringTools::trim(parameterValueString)));
			break;
		case ShaderParameter::TYPE_FLOAT:
			parameterValue = ShaderParameter(Float::parseFloat(StringTools::trim(parameterValueString)));
			break;
		case ShaderParameter::TYPE_VECTOR2:
			{
				auto parameterValueStringArray = StringTools::tokenize(parameterValueString, ",");
				if (parameterValueStringArray.size() != 2) break;
				parameterValue = ShaderParameter(
					Vector2(
						Float::parseFloat(StringTools::trim(parameterValueStringArray[0])),
						Float::parseFloat(StringTools::trim(parameterValueStringArray[1]))
					)
				);
			}
			break;
		case ShaderParameter::TYPE_VECTOR3:
			{
				auto parameterValueStringArray = StringTools::tokenize(parameterValueString, ",");
				if (parameterValueStringArray.size() != 3) break;
				parameterValue = ShaderParameter(
					Vector3(
						Float::parseFloat(StringTools::trim(parameterValueStringArray[0])),
						Float::parseFloat(StringTools::trim(parameterValueStringArray[1])),
						Float::parseFloat(StringTools::trim(parameterValueStringArray[2]))
					)
				);
			}
			break;
		default:
			break;
	}
	if (currentShaderParameter.getType() != parameterValue.getType()) {
		Console::println("EntityShaderParameters::setShaderParameter(): parameter type mismatch for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
	}
	parameters[parameterName] = parameterValue;
	changed = true;
}
