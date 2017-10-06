#include <tdme/engine/model/ModelHelper_VertexOrder.h>

#include <tdme/utils/Enum.h>

using tdme::engine::model::ModelHelper_VertexOrder;
using tdme::utils::Enum;

ModelHelper_VertexOrder::ModelHelper_VertexOrder(const wstring& name, int ordinal): Enum(name, ordinal)
{
}

ModelHelper_VertexOrder* tdme::engine::model::ModelHelper_VertexOrder::CLOCKWISE = new ModelHelper_VertexOrder(L"CLOCKWISE", 0);
ModelHelper_VertexOrder* tdme::engine::model::ModelHelper_VertexOrder::COUNTERCLOCKWISE = new ModelHelper_VertexOrder(L"COUNTERCLOCKWISE", 1);

ModelHelper_VertexOrder* ModelHelper_VertexOrder::valueOf(const wstring& a0)
{
	if (CLOCKWISE->getName() == a0) return CLOCKWISE;
	if (COUNTERCLOCKWISE->getName() == a0) return COUNTERCLOCKWISE;
	// TODO: throw exception here maybe
	return nullptr;
}
