#include <string>
#include <vector>

#include <cstring>

#include <miniscript/miniscript.h>
#include <ext/sha256/sha256.h>
#include <miniscript/utilities/SHA256.h>

using std::string;
using std::vector;

void miniscript::utilities::SHA256::encode(const string& decodedString, string& encodedString) {
	unsigned char digest[::SHA256::DIGEST_SIZE];
	memset(digest, 0, ::SHA256::DIGEST_SIZE);

	auto ctx = ::SHA256();
	ctx.init();
	ctx.update((const uint8_t*)decodedString.c_str(), decodedString.size());
	ctx.final(digest);

	char buf[2 * ::SHA256::DIGEST_SIZE + 1];
	buf[2 * ::SHA256::DIGEST_SIZE] = 0;
	for (int i = 0; i < ::SHA256::DIGEST_SIZE; i++) sprintf(buf + i * 2, "%02x", digest[i]);
	encodedString = string(buf);
}

void miniscript::utilities::SHA256::encode(const vector<uint8_t>& decodedData, string& encodedString) {
	unsigned char digest[::SHA256::DIGEST_SIZE];
	memset(digest, 0, ::SHA256::DIGEST_SIZE);

	auto ctx = ::SHA256();
	ctx.init();
	ctx.update((const uint8_t*)decodedData.data(), decodedData.size());
	ctx.final(digest);

	char buf[2 * ::SHA256::DIGEST_SIZE + 1];
	buf[2 * ::SHA256::DIGEST_SIZE] = 0;
	for (int i = 0; i < ::SHA256::DIGEST_SIZE; i++) sprintf(buf + i * 2, "%02x", digest[i]);
	encodedString = string(buf);
}
