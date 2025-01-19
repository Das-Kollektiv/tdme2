#pragma once

#include <agui/agui.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/ExceptionBase.h>
#include <agui/video/decoder/fwd-agui.h>

/**
 * Audio decoder exception
 * @author Andreas Drewke
 */
class agui::video::decoder::VideoDecoderException: public agui::utilities::ExceptionBase
{
public:

	/**
	 * @brief Public constructor
	 * @param message message exception message
	 */
	VideoDecoderException(const string& message) throw();

};
