#include <tdme/engine/EntityShaderParameters.h>

#include <map>
#include <string>

#include <tdme/engine/Engine.h>

using tdme::engine::EntityShaderParameters;

using std::map;
using std::string;

using tdme::engine::Engine;

void EntityShaderParameters::computeHash() {
	// TODO: md5 or something
	shaderParametersHash.clear();
	shaderParametersHash+= shaderId + ";";
	for (auto& it: shaderParameters) {
		shaderParametersHash+= it.first;
		shaderParametersHash+= "=";
		auto& parameterValue = it.second;
		switch(parameterValue.getType()) {
			case ShaderParameter::TYPE_NONE:
				break;
			case ShaderParameter::TYPE_FLOAT:
				shaderParametersHash+= to_string(static_cast<int>(parameterValue.getFloatValue() * 100.0f));
				break;
			case ShaderParameter::TYPE_VECTOR3:
				{
					auto& shaderParameterArray = parameterValue.getVector3Value().getArray();
					for (auto i = 0; i < shaderParameterArray.size(); i++) {
						if (i != 0) shaderParametersHash+= ",";
						shaderParametersHash+= to_string(static_cast<int>(shaderParameterArray[i] * 100.0f));
					}
				}
				break;
			default:
				break;
		}
		shaderParametersHash+= ";";
	}
}

const ShaderParameter EntityShaderParameters::getShaderParameter(const string& parameterName) {
	auto shaderParameterIt = shaderParameters.find(parameterName);
	if (shaderParameterIt == shaderParameters.end()) {
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
	shaderParameters[parameterName] = parameterValue;

	// compute new hash
	computeHash();
}
