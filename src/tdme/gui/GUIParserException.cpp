#include <tdme/gui/GUIParserException.h>

#include <tdme/utils/ExceptionBase.h>

using tdme::gui::GUIParserException;
using tdme::utils::ExceptionBase;

GUIParserException::GUIParserException(const string& message) : ExceptionBase(message)
{
}

