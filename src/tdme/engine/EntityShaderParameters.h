#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/ShaderParameter.h>

using std::map;
using std::string;

using tdme::engine::Engine;
using tdme::engine::ShaderParameter;

/**
 * TDME2 engine entity shader parameters
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::EntityShaderParameters
{
private:
	map<string, ShaderParameter> shaderParameters;
	string shaderParametersHash;
	string shaderId;

	/**
	 * Compute shader parameters hash
	 */
	void computeHash() {
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

public:
	/**
	 * Public constructor
	 */
	EntityShaderParameters() {
	}

	/**
	 * Destructor
	 */
	~EntityShaderParameters() {
	}

	/**
	 * Set shader
	 * @param shaderId shader id
	 */
	void setShader(const string& shaderId) {
		shaderParameters.clear();
		shaderParametersHash.clear();
		this->shaderId = shaderId;
	}

	/**
	 * Returns shader parameter for given parameter name, if the value does not exist, the default will be returned
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @return shader parameter
	 */
	inline const ShaderParameter getShaderParameter(const string& parameterName) {
		auto shaderParameterIt = shaderParameters.find(parameterName);
		if (shaderParameterIt == shaderParameters.end()) {
			return Engine::getDefaultShaderParameter(shaderId, parameterName);
		}
		auto& shaderParameter = shaderParameterIt->second;
		return shaderParameter;
	}

	/**
	 * Set shader parameter for given parameter name
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @param paraemterValue parameter value
	 */
	inline void setShaderParameter(const string& parameterName, const ShaderParameter& parameterValue) {
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

	/**
	 * @return shader parameters hash
	 */
	const string& getShaderParametersHash() {
		return shaderParametersHash;
	}
};
