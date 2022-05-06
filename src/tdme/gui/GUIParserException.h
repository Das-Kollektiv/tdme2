#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/ExceptionBase.h>

using std::string;

using tdme::utilities::ExceptionBase;

/**
 * GUI parser exception
 * @author Andreas Drewke
 */
class tdme::gui::GUIParserException final: public ExceptionBase
{
public:
	/**
	 * Public constructor
	 */
	GUIParserException(const string& message);
};
