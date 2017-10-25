#include <tdme/utils/Enum.h>

using tdme::utils::Enum;

Enum::Enum(const string& name, int32_t ordinal)
{
	this->name = name;
	this->ordinal = ordinal;
}

bool Enum::equals(Enum* enumObject)
{
	return this == enumObject;
}

const string& Enum::getName()
{
	return name;
}

int32_t Enum::getOrdinal()
{
	return ordinal;
}
