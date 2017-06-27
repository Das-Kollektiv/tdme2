// Generated from /tdme/src/tdme/audio/AudioBufferManager.java
#include <tdme/audio/AudioBufferManager_AudioBufferManaged.h>

#include <java/lang/String.h>
#include <tdme/audio/AudioBufferManager.h>

using tdme::audio::AudioBufferManager_AudioBufferManaged;
using java::lang::String;
using tdme::audio::AudioBufferManager;

AudioBufferManager_AudioBufferManaged::AudioBufferManager_AudioBufferManaged(AudioBufferManager *AudioBufferManager_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, AudioBufferManager_this(AudioBufferManager_this)
{
	clinit();
}

AudioBufferManager_AudioBufferManaged::AudioBufferManager_AudioBufferManaged(AudioBufferManager *AudioBufferManager_this, String* id, int32_t alId) 
	: AudioBufferManager_AudioBufferManaged(AudioBufferManager_this, *static_cast< ::default_init_tag* >(0))
{
	ctor(id,alId);
}

void AudioBufferManager_AudioBufferManaged::ctor(String* id, int32_t alId)
{
	super::ctor();
	this->id = id;
	this->alId = alId;
	this->referenceCounter = 0;
}

String* AudioBufferManager_AudioBufferManaged::getId()
{
	return id;
}

int32_t AudioBufferManager_AudioBufferManaged::getAlId()
{
	return alId;
}

void AudioBufferManager_AudioBufferManaged::setAlId(int32_t alId)
{
	this->alId = alId;
}

int32_t AudioBufferManager_AudioBufferManaged::getReferenceCounter()
{
	return referenceCounter;
}

bool AudioBufferManager_AudioBufferManaged::decrementReferenceCounter()
{
	referenceCounter--;
	return referenceCounter == 0;
}

void AudioBufferManager_AudioBufferManaged::incrementReferenceCounter()
{
	referenceCounter++;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AudioBufferManager_AudioBufferManaged::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.audio.AudioBufferManager.AudioBufferManaged", 48);
    return c;
}

java::lang::Class* AudioBufferManager_AudioBufferManaged::getClass0()
{
	return class_();
}

