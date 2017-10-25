#include <tdme/audio/AudioEntity.h>

#include <string>

#include <tdme/math/Vector3.h>

using std::string;

using tdme::audio::AudioEntity;
using tdme::math::Vector3;

AudioEntity::AudioEntity(const string& id)
{
	this->id = id;
	looping = false;
	fixed = false;
	pitch = 1.0f;
	gain = 1.0f;
	sourcePosition.set(0.0f, 0.0f, 0.0f);
	sourceDirection.set(0.0f, 0.0f, 0.0f);
	sourceVelocity.set(0.0f, 0.0f, 0.0f);
}

AudioEntity::~AudioEntity() {
}

const string& AudioEntity::getId()
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

Vector3& AudioEntity::getSourcePosition()
{
	return sourcePosition;
}

Vector3& AudioEntity::getSourceDirection()
{
	return sourceDirection;
}

Vector3& AudioEntity::getSourceVelocity()
{
	return sourceVelocity;
}
