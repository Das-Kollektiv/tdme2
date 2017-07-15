#include <tdme/audio/decoder/AudioDecoderException.h>

#include <tdme/utils/_ExceptionBase.h>

using tdme::audio::decoder::AudioDecoderException;

using tdme::utils::_ExceptionBase;

AudioDecoderException::AudioDecoderException(const string& message) throw() : _ExceptionBase(message) {
}
