/**
 * @version $Id: dd68ad5359d025ce4319f9a5652e8fc4c74d0656 $
 */

#include "JsonException.h"

#include <tdme/utils/_ExceptionBase.h>

using tdme::ext::jsonbox::JsonException;
using tdme::utils::_ExceptionBase;

using std::wstring;

JsonException::JsonException(const string& message) throw() : _ExceptionBase(message) {
}
