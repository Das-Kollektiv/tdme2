#include <tdme/utils/StringConverter.h>

#include <codecvt>
#include <locale>

using std::string;
using std::wstring;
using std::codecvt_utf8;
using std::wstring_convert;

using tdme::utils::StringConverter;

const string StringConverter::toString(const wstring& string)
{
	// https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
	using convert_type = codecvt_utf8<wchar_t>;
	wstring_convert<convert_type, wchar_t> converter;
	return converter.to_bytes(string);
}

const wstring StringConverter::toWideString(const string& string) {
	// https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
	using convert_type = codecvt_utf8<wchar_t>;
	wstring_convert<convert_type, wchar_t> converter;
	return converter.from_bytes(string);
}
