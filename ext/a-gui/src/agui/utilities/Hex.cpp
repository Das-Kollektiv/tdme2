#include <string.h>

#include <agui/agui.h>
#include <agui/utilities/Hex.h>

using std::string;

using agui::utilities::Hex;

void Hex::encodeInt(const uint64_t decodedInt, string& encodedString) {
	encodedString = "";
	char encodingCharSet[] = "0123456789abcdef";
	auto _decodedInt = decodedInt;
	for (auto i = 0; i < 32; i++) {
		auto charIdx = _decodedInt & 15;
		encodedString = encodingCharSet[charIdx] + encodedString;
		_decodedInt>>= 4;
		if (_decodedInt == 0) break;
	}
}

bool Hex::decodeInt(const string& encodedString, uint64_t& decodedInt) {
	char encodingCharSet[] = "0123456789abcdef";
	decodedInt = 0;
	for (auto i = 0; i < encodedString.length(); i++) {
		auto codeIdx = -1;
		char c = encodedString[encodedString.length() - i - 1];
		char* codePtr = strchr(encodingCharSet, c);
		if (codePtr == NULL) {
			return false;
		} else {
			codeIdx = codePtr - encodingCharSet;
		}
		decodedInt+= codeIdx << (i * 4);
	}
	return true;
}
