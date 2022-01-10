#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/utilities/Enum.h>

using std::string;

using tdme::engine::model::Model;
using tdme::engine::model::ShaderModel;
using tdme::utilities::Enum;

/**
 * Shader model
 */
class tdme::engine::model::ShaderModel final: public Enum
{
	friend class Model;

public:
	STATIC_DLL_IMPEXT static ShaderModel* SPECULAR;
	STATIC_DLL_IMPEXT static ShaderModel* PBR;

public:
	ShaderModel(const string& name, int ordinal);

public:
	static ShaderModel* valueOf(const string& a0);

};
