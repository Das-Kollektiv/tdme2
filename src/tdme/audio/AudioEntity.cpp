// Generated from /tdme/src/tdme/audio/AudioEntity.java
#include <tdme/audio/AudioEntity.h>

#include <java/lang/String.h>
#include <tdme/math/Vector3.h>

using tdme::audio::AudioEntity;
using java::lang::String;
using tdme::math::Vector3;

AudioEntity::AudioEntity(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

AudioEntity::AudioEntity(String* id) 
	: AudioEntity(*static_cast< ::default_init_tag* >(0))
{
	ctor(id);
}

void AudioEntity::init()
{
	looping = false;
	fixed = false;
	pitch = 1.0f;
	gain = 1.0f;
	sourcePosition = new Vector3();
	sourceDirection = new Vector3();
	sourceVelocity = new Vector3();
}

void AudioEntity::ctor(String* id)
{
	super::ctor();
	init();
	this->id = id;
}

String* AudioEntity::getId()
{
	return id;
}

bool AudioEntity::isLooping()
{
	return looping;
}

void AudioEntity::setLooping(bool looping)
{
	this->looping = looping;
}

bool AudioEntity::isFixed()
{
	return fixed;
}

void AudioEntity::setFixed(bool fixed)
{
	this->fixed = fixed;
}

float AudioEntity::getPitch()
{
	return pitch;
}

void AudioEntity::setPitch(float pitch)
{
	this->pitch = pitch;
}

float AudioEntity::getGain()
{
	return gain;
}

void AudioEntity::setGain(float gain)
{
	this->gain = gain;
}

Vector3* AudioEntity::getSourcePosition()
{
	return sourcePosition;
}

Vector3* AudioEntity::getSourceDirection()
{
	return sourceDirection;
}

Vector3* AudioEntity::getSourceVelocity()
{
	return sourceVelocity;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AudioEntity::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.audio.AudioEntity", 22);
    return c;
}

java::lang::Class* AudioEntity::getClass0()
{
	return class_();
}

