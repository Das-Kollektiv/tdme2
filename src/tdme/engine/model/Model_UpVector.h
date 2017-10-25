
#pragma once

#include <string>

#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::string;

using tdme::utils::Enum;
using tdme::engine::model::Model;
using tdme::engine::model::Model_UpVector;

class tdme::engine::model::Model_UpVector final
	: public Enum
{
	friend class Model;

public:
	static Model_UpVector *Y_UP;
	static Model_UpVector *Z_UP;

public:
	Model_UpVector(const string& name, int ordinal);

public:
	static Model_UpVector* valueOf(const string& a0);

};
