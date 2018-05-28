#include <tdme/utils/Enum.h>

using tdme::utils::Enum;

Enum::Enum(const string& name, int32_t ordinal)
{
	this->name = name;
	this->ordinal = ordinal;
}

bool Enum::equals(Enum* enumObject) const
{
	return this == enumObject;
}

const string& Enum::getName() const
{
	return name;
}

int32_t Enum::getOrdinal() const
{
	return ordinal;
}
