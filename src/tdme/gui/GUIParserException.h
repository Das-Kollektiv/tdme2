#pragma once

#include <string>

#include <tdme/gui/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/ExceptionBase.h>

using std::string;

using tdme::utils::ExceptionBase;

/** 
 * GUI parser exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::GUIParserException final
	: public ExceptionBase
{
public:
	GUIParserException(const string& message);
};
