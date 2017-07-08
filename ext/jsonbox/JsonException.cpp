/**
 * @version $Id: dd68ad5359d025ce4319f9a5652e8fc4c74d0656 $
 */

#include "JsonException.h"

using namespace tdme::ext::jsonbox;

using std::wstring;

JsonException::JsonException(const wstring &message) throw() : tdme::utils::Exception(message) {
}
