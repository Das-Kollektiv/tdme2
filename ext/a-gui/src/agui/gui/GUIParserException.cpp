#include <agui/gui/GUIParserException.h>

#include <agui/agui.h>
#include <agui/utilities/ExceptionBase.h>

using agui::gui::GUIParserException;
using agui::utilities::ExceptionBase;

GUIParserException::GUIParserException(const string& message) : ExceptionBase(message)
{
}

