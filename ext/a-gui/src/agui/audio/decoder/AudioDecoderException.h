#pragma once

#include <agui/agui.h>
#include <agui/audio/decoder/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/ExceptionBase.h>

/**
 * Audio decoder exception
 * @author Andreas Drewke
 */
class agui::audio::decoder::AudioDecoderException: public agui::utilities::ExceptionBase
{
public:

	/**
	 * @brief Public constructor
	 * @param message message exception message
	 */
	AudioDecoderException(const string& message) throw();

};
