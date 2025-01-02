#include <string>
#include <vector>

#include <yannet/yannet.h>
#include <yannet/utilities/Base64.h>

using std::string;
using std::vector;

using yannet::utilities::Base64;

void Base64::encode(const string& decodedString, string& encodedString) {
	// see: https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c/34571089#34571089
	string dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int val = 0, valb = -6;
	for (uint8_t c: decodedString) {
		val = (val << 8) + c;
		valb+= 8;
		while (valb >= 0) {
			encodedString.push_back(dictionary[(val >> valb) & 0x3F]);
			valb-= 6;
		}
	}
	if (valb > -6) encodedString.push_back(dictionary[((val << 8) >> (valb + 8)) & 0x3F]);
	while (encodedString.size() % 4) encodedString.push_back('=');
}

void Base64::encode(const vector<uint8_t>& decodedData, string& encodedString) {
	// see: https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c/34571089#34571089
	string dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int val = 0, valb = -6;
	for (uint8_t c: decodedData) {
		val = (val << 8) + c;
		valb+= 8;
		while (valb >= 0) {
			encodedString.push_back(dictionary[(val >> valb) & 0x3F]);
			valb-= 6;
		}
	}
	if (valb > -6) encodedString.push_back(dictionary[((val << 8) >> (valb + 8)) & 0x3F]);
	while (encodedString.size() % 4) encodedString.push_back('=');
}

void Base64::decode(const string& encodedString, string& decodedString) {
	// see: https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c/34571089#34571089
	string dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	std::vector<int> T(256, -1);
	for (int i = 0; i < 64; i++) T[dictionary[i]] = i;
	int val = 0, valb = -8;
	for (uint8_t c: encodedString) {
		if (T[c] == -1) break;
		val = (val << 6) + T[c];
		valb+= 6;
		if (valb >= 0) {
			decodedString.push_back(char((val >> valb) & 0xFF));
			valb-= 8;
		}
	}
}

void Base64::decode(const string& encodedString, vector<uint8_t>& decodedData) {
	// see: https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c/34571089#34571089
	string dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	std::vector<int> T(256, -1);
	for (int i = 0; i < 64; i++) T[dictionary[i]] = i;
		int val = 0, valb = -8;
		for (uint8_t c: encodedString) {
			if (T[c] == -1) break;
			val = (val << 6) + T[c];
			valb+= 6;
			if (valb >= 0) {
				decodedData.push_back(char((val >> valb) & 0xFF));
			valb-= 8;
		}
	}
}
