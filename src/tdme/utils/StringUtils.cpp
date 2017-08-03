#include <tdme/utils/StringUtils.h>

using std::string;
using std::wstring;

using tdme::utils::StringUtils;

const bool StringUtils::startsWith(const wstring& src, const wstring& prefix) {
    return src.find(prefix) == 0;
}