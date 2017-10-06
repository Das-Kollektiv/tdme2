#include <tdme/engine/fileio/models/DAEReader_AuthoringTool.h>

#include <tdme/utils/Enum.h>

using tdme::engine::fileio::models::DAEReader_AuthoringTool;
using tdme::utils::Enum;

DAEReader_AuthoringTool::DAEReader_AuthoringTool(const wstring& name, int ordinal): Enum(name, ordinal)
{
}

DAEReader_AuthoringTool* tdme::engine::fileio::models::DAEReader_AuthoringTool::UNKNOWN = new DAEReader_AuthoringTool(L"UNKNOWN", 0);
DAEReader_AuthoringTool* tdme::engine::fileio::models::DAEReader_AuthoringTool::BLENDER = new DAEReader_AuthoringTool(L"BLENDER", 1);

DAEReader_AuthoringTool* DAEReader_AuthoringTool::valueOf(const wstring& a0)
{
	if (BLENDER->getName() == a0) return BLENDER;
	if (UNKNOWN->getName() == a0) return UNKNOWN;
	// TODO: throw exception here maybe
	return nullptr;
}
