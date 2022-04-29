#pragma once

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/video/decoder/fwd-tdme.h>

using tdme::utilities::ExceptionBase;

/**
 * Audio decoder exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::video::decoder::VideoDecoderException: public ExceptionBase
{
public:

	/**
	 * @brief Public constructor
	 * @param message message exception message
	 */
	VideoDecoderException(const string& message) throw();

};
