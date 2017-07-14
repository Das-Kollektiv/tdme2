// Generated from /tdme/src/tdme/gui/GUIParserException.java

#pragma once

#include <string>

#include <tdme/gui/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/_ExceptionBase.h>

using std::wstring;

using tdme::utils::_ExceptionBase;

/** 
 * GUI parser exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::GUIParserException final
	: public _ExceptionBase
{
public:
	GUIParserException(const string& message);
};
