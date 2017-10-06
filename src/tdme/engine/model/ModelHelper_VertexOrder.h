
#pragma once

#include <string>

#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::utils::Enum;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::ModelHelper_VertexOrder;

class tdme::engine::model::ModelHelper_VertexOrder final
	: public Enum
{
	friend class ModelHelper;
public:
	static ModelHelper_VertexOrder *CLOCKWISE;
	static ModelHelper_VertexOrder *COUNTERCLOCKWISE;

	ModelHelper_VertexOrder(const wstring& name, int ordinal);

public:
	static ModelHelper_VertexOrder* valueOf(const wstring& a0);
};
