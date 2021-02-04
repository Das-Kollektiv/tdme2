#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/ShaderParameter.h>

using std::map;
using std::string;

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
	void computeHash();

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
	const ShaderParameter getShaderParameter(const string& parameterName);

	/**
	 * Set shader parameter for given parameter name
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @param paraemterValue parameter value
	 */
	void setShaderParameter(const string& parameterName, const ShaderParameter& parameterValue);

	/**
	 * @return shader parameters hash
	 */
	const string& getShaderParametersHash() {
		return shaderParametersHash;
	}
};
