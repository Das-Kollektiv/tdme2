#include <openssl/sha.h>

#include <string>
#include <vector>
#include <cstring>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/SHA256.h>

using miniscript::utilities::SHA256;

using std::string;
using std::vector;

void SHA256::encode(const string& decodedString, string& encodedString) {
	hash((const uint8_t*)decodedString.data(), decodedString.size(), encodedString);
}

void SHA256::encode(const vector<uint8_t>& decodedData, string& encodedString) {
	hash(decodedData.data(), decodedData.size(), encodedString);
}

inline void SHA256::hash(const uint8_t* data, size_t size, string& encodedString) {
	// see: https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c
	// check this later: https://stackoverflow.com/questions/34289094/alternative-for-calculating-sha256-to-using-deprecated-openssl-code
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, data, size);
	SHA256_Final(hash, &sha256);
	char outputBuffer[SHA256_DIGEST_LENGTH * 2];
	for (int64_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
	}
	encodedString = string(outputBuffer, SHA256_DIGEST_LENGTH * 2);
}
