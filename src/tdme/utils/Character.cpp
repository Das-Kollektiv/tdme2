#include <tdme/utils/Character.h>

#include <cwctype>
#include <cctype>

using tdme::utils::Character;

char Character::toLowerCase(char character) {
	return towlower(character);
}

char Character::toUpperCase(char character) {
	return towupper(character);
}

bool Character::isAlphaNumeric(char character) {
	return isalnum(character) != 0;
}
