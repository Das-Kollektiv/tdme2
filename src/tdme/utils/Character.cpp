#include <tdme/utils/Character.h>

#include <cwctype>

using tdme::utils::Character;

char Character::toLowerCase(char character) {
	return towlower(character);
}

char Character::toUpperCase(char character) {
	return towupper(character);
}
