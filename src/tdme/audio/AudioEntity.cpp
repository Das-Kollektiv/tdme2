#include <tdme/audio/AudioEntity.h>

#include <string>

#include <tdme/tdme.h>
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

