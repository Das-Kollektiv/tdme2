// Generated from /tdme/src/tdme/audio/decoder/AudioDecoderException.java
#include <tdme/audio/decoder/AudioDecoderException.h>

using tdme::audio::decoder::AudioDecoderException;
AudioDecoderException::AudioDecoderException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

AudioDecoderException::AudioDecoderException(String* message) 
	: AudioDecoderException(*static_cast< ::default_init_tag* >(0))
{
	ctor(message);
}

void AudioDecoderException::ctor(String* message)
{
	super::ctor(message);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AudioDecoderException::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.audio.decoder.AudioDecoderException", 40);
    return c;
}

java::lang::Class* AudioDecoderException::getClass0()
{
	return class_();
}

