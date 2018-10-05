#include <string.h>

#include <tdme/utils/HexEncDec.h>

using std::string;

using tdme::utils::HexEncDec;

void HexEncDec::encodeInt(const uint64_t decodedInt, string& encodedString) {
	encodedString = "";
	char encodingCharSet[] = "0123456789abcdef";
	auto _decodedInt = decodedInt;
	for (int i = 0; i < 32; i++) {
		unsigned int charIdx = _decodedInt & 15;
		encodedString = encodingCharSet[charIdx] + encodedString;
		_decodedInt>>= 4;
		if (_decodedInt == 0) break;
	}
}
