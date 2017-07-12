/**
 * @version $Id: dd68ad5359d025ce4319f9a5652e8fc4c74d0656 $
 */

#include "JsonException.h"

using tdme::ext::jsonbox::JsonException;
using tdme::utils::_Exception;

using std::wstring;

JsonException::JsonException(const wstring &message) throw() : _Exception(message) {
}
