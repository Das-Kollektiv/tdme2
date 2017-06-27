// Generated from /tdme/src/tdme/audio/decoder/AudioDecoder.java
#include <tdme/audio/decoder/AudioDecoder.h>

using tdme::audio::decoder::AudioDecoder;
AudioDecoder::AudioDecoder(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

AudioDecoder::AudioDecoder()
	: AudioDecoder(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void AudioDecoder::ctor()
{
	super::ctor();
	init();
}

void AudioDecoder::init()
{
	channels = AudioDecoder::CHANNELS_NONE;
	sampleRate = AudioDecoder::SAMPLERATE_NONE;
	bitsPerSample = AudioDecoder::BITSPERSAMPLES_NONE;
}

constexpr int32_t AudioDecoder::CHANNELS_NONE;

constexpr int32_t AudioDecoder::SAMPLERATE_NONE;

constexpr int32_t AudioDecoder::BITSPERSAMPLES_NONE;

int32_t AudioDecoder::getChannels()
{
	return channels;
}

int32_t AudioDecoder::getSampleRate()
{
	return sampleRate;
}

int32_t AudioDecoder::getBitsPerSample()
{
	return bitsPerSample;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AudioDecoder::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.audio.decoder.AudioDecoder", 31);
    return c;
}

java::lang::Class* AudioDecoder::getClass0()
{
	return class_();
}

