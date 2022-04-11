#include <tdme/video/decoder/VideoDecoderException.h>

#include <tdme/tdme.h>
#include <tdme/utilities/ExceptionBase.h>

using tdme::video::decoder::VideoDecoderException;

using tdme::utilities::ExceptionBase;

VideoDecoderException::VideoDecoderException(const string& message) throw() : ExceptionBase(message) {
}
