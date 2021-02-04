#include <tdme/engine/EntityShaderParameters.h>

#include <map>
#include <string>

#include <tdme/engine/Engine.h>

using tdme::engine::EntityShaderParameters;

using std::map;
using std::string;

using tdme::engine::Engine;


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
