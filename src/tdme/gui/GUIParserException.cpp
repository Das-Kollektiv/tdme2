#include <tdme/gui/GUIParserException.h>

#include <tdme/utils/_ExceptionBase.h>

using tdme::gui::GUIParserException;
using tdme::utils::_ExceptionBase;

GUIParserException::GUIParserException(const string& message) : _ExceptionBase(message)
{
}

