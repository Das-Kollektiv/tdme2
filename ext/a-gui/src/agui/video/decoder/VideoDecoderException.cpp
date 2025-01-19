#include <agui/video/decoder/VideoDecoderException.h>

#include <agui/agui.h>
#include <agui/utilities/ExceptionBase.h>

using agui::video::decoder::VideoDecoderException;

using agui::utilities::ExceptionBase;

VideoDecoderException::VideoDecoderException(const string& message) throw() : ExceptionBase(message) {
}
