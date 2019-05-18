#pragma once

#include <tdme/tdme.h>
#include <tdme/audio/decoder/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/ExceptionBase.h>

using tdme::utils::ExceptionBase;

/**
 * Audio decoder exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::decoder::AudioDecoderException: public ExceptionBase
{
public:

	/**
	 * @brief Public constructor
	 * @param message message exception message
	 */
	AudioDecoderException(const string& message) throw();

};
