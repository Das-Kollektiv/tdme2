/**
 * @version $Id: dd68ad5359d025ce4319f9a5652e8fc4c74d0656 $
 */

#include "JsonException.h"

#include <tdme/utils/ExceptionBase.h>

using tdme::ext::jsonbox::JsonException;
using tdme::utils::ExceptionBase;

using std::wstring;

JsonException::JsonException(const string& message) throw() : ExceptionBase(message) {
}
