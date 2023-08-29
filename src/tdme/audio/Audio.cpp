#include <tdme/audio/Audio.h>

#if defined(__APPLE__)
	#define AL_SILENCE_DEPRECATION
	#include <OpenAL/al.h>
	#include <OpenAL/alc.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__linux__) || defined(_WIN32) || defined(_WIN64) || defined(__HAIKU__)
	#include <AL/al.h>
	#include <AL/alc.h>
#endif

#include <array>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/audio/AudioEntity.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::array;
using std::map;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::audio::Audio;
using tdme::audio::AudioEntity;
using tdme::math::Vector3;
using tdme::utilities::Console;

Audio* Audio::instance = nullptr;


void Audio::shutdown()
{
	if (Audio::instance == nullptr) return;
	delete Audio::instance;
	Audio::instance = nullptr;
}

Audio::Audio()
{
	// TODO: error handling
	device = alcOpenDevice(NULL);
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);

	//
	listenerPosition.set(0.0f, 0.0f, 0.0);
	listenerVelocity.set(0.0f, 0.0f, 0.0);
	listenerOrientationAt.set(0.0f, 0.0f, 1.0f);
	listenerOrientationUp.set(0.0f, 1.0f, 0.0f);

	// init listener position
	update();
}

Audio::~Audio()
{
	reset();
	alcCloseDevice(device);
}

void Audio::addEntity(AudioEntity* entity)
{
	if (entity->initialize() == true) {
		auto audioEntityIt = audioEntities.find(entity->getId());
		if (audioEntityIt != audioEntities.end()) {
			// check if we want to add this entity a second time
			if (entity == audioEntityIt->second) {
				Console::println("Audio::addEntity(): " + entity->getId() + ": entity already added!");
				return;
			}
			// remove old other entity
			removeEntity(entity->getId());
		}
		audioEntities[entity->getId()] = entity;
	} else {
		Console::println(string("Audio::addEntity(): adding '" + entity->getId() + "' failed"));
	}
}

void Audio::removeEntity(const string& id)
{
	auto audioEntityIt = audioEntities.find(id);
	if (audioEntityIt != audioEntities.end()) {
		auto audioEntity = audioEntityIt->second;
		audioEntity->stop();
		audioEntity->dispose();
		audioEntities.erase(audioEntityIt);
		delete audioEntity;
	}
}

void Audio::reset()
{
	// determine keys to remove
	vector<string> audioEntitiesToRemove;
	for (const auto& [audioEntityId, audioEntity]: audioEntities) {
		audioEntitiesToRemove.push_back(audioEntityId);
	}

	// remove entities
	for (const auto& key: audioEntitiesToRemove) {
		removeEntity(key);
	}
}
void Audio::update()
{
	// update audio entities
	for (const auto& [audioEntityId, audioEntity]: audioEntities) {
		audioEntity->update();
	}

	// update listener position
	alListenerfv(AL_POSITION, listenerPosition.getArray().data());
	alListenerfv(AL_VELOCITY, listenerVelocity.getArray().data());
	array<float, 6> listenerOrientation = {
		listenerOrientationAt[0],
		listenerOrientationAt[1],
		listenerOrientationAt[2],
		listenerOrientationUp[0],
		listenerOrientationUp[1],
		listenerOrientationUp[2]
	};
	alListenerfv(AL_ORIENTATION, listenerOrientation.data());
}
