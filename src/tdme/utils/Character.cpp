#include <tdme/utils/Character.h>

#include <cwctype>

using tdme::utils::Character;

wchar_t Character::toLowerCase(wchar_t character) {
	return towlower(character);
}

wchar_t Character::toUpperCase(wchar_t character) {
	return towupper(character);
}
