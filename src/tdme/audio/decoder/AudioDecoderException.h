#pragma once

#include <tdme/audio/decoder/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/_ExceptionBase.h>

using tdme::utils::_ExceptionBase;

/**
 * Audio decoder exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::decoder::AudioDecoderException: public _ExceptionBase
{
public:

	/**
	 * @brief Public constructor
	 * @param message exception message
	 */
	AudioDecoderException(const string& message) throw();

};
