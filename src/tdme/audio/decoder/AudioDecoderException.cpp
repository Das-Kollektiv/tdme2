#include <tdme/audio/decoder/AudioDecoderException.h>

#include <tdme/utils/ExceptionBase.h>

using tdme::audio::decoder::AudioDecoderException;

using tdme::utils::ExceptionBase;

AudioDecoderException::AudioDecoderException(const string& message) throw() : ExceptionBase(message) {
}
