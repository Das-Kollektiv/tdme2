#include <tdme/utilities/Enum.h>

using tdme::utilities::Enum;

Enum::Enum(const string& name, int32_t ordinal)
{
	this->name = name;
	this->ordinal = ordinal;
}
