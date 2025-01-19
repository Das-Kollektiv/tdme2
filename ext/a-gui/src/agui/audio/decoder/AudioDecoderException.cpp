#include <agui/audio/decoder/AudioDecoderException.h>

#include <agui/agui.h>
#include <agui/utilities/ExceptionBase.h>

using agui::audio::decoder::AudioDecoderException;

using agui::utilities::ExceptionBase;

AudioDecoderException::AudioDecoderException(const string& message) throw() : ExceptionBase(message) {
}
