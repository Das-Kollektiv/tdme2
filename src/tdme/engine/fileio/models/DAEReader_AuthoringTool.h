
#pragma once

#include <string>

#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::string;

using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::DAEReader_AuthoringTool;

using tdme::utils::Enum;

class tdme::engine::fileio::models::DAEReader_AuthoringTool final
	: public Enum
{
public: /* package */
	static DAEReader_AuthoringTool *UNKNOWN;
	static DAEReader_AuthoringTool *BLENDER;

public:
	DAEReader_AuthoringTool(const string& name, int ordinal);

public:
	static DAEReader_AuthoringTool* valueOf(const string& a0);
};
