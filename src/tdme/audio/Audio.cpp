// Generated from /tdme/src/tdme/audio/Audio.java
#include <tdme/audio/Audio.h>

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/audio/AudioBufferManager.h>
#include <tdme/audio/AudioEntity.h>
#include <tdme/audio/AudioStream.h>
#include <tdme/audio/Sound.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>

using std::array;
using std::map;
using std::vector;
using std::wstring;

using tdme::audio::Audio;
using tdme::audio::AudioBufferManager;
using tdme::audio::AudioEntity;
using tdme::audio::AudioStream;
using tdme::audio::Sound;
using tdme::math::Vector3;
using tdme::utils::_Console;

Audio::Audio() 
{
	listenerPosition.set(0.0f, 0.0f, 0.0);
	listenerVelocity.set(0.0f, 0.0f, 0.0);
	listenerOrientationAt.set(0.0f, 0.0f, -1.0f);
	listenerOrientationUp.set(0.0f, 1.0f, 0.0f);
	update();
}

constexpr int32_t Audio::ALBUFFERID_NONE;

constexpr int32_t Audio::ALSOURCEID_NONE;

Audio* Audio::instance = nullptr;

Audio* Audio::getInstance()
{
	if (Audio::instance == nullptr) {
		Audio::instance = new Audio();
	}
	return Audio::instance;
}

Vector3* Audio::getListenerPosition()
{
	return &listenerPosition;
}

Vector3* Audio::getListenerVelocity()
{
	return &listenerVelocity;
}

Vector3* Audio::getListenerOrientationAt()
{
	return &listenerOrientationAt;
}

Vector3* Audio::getListenerOrientationUp()
{
	return &listenerOrientationUp;
}

AudioEntity* Audio::getEntity(const wstring& id)
{
	auto audioEntityIt = audioEntities.find(id);
	if (audioEntityIt == audioEntities.end()) return nullptr;
	return audioEntityIt->second;
}

AudioEntity* Audio::addStream(const wstring& id, const wstring& pathName, const wstring& fileName)
{
	AudioEntity* stream = new AudioStream(id, pathName, fileName);
	if (stream->initialize() == true) {
		removeEntity(id);
		audioEntities[id] = stream;
		return stream;
	} else {
		_Console::println(wstring(L"Audio stream: '" + id + L"' failed"));
		return nullptr;
	}
}

AudioEntity* Audio::addSound(const wstring& id, const wstring& pathName, const wstring& fileName)
{
	AudioEntity* sound = new Sound(id, pathName, fileName);
	if (sound->initialize() == true) {
		removeEntity(id);
		audioEntities[id] = sound;
		return sound;
	} else {
		_Console::println(wstring(L"Audio sound: '" + id + L"' failed"));
		return nullptr;
	}
}

void Audio::removeEntity(const wstring& id)
{
	auto audioEntityIt = audioEntities.find(id);
	if (audioEntityIt != audioEntities.end()) {
		auto audioEntity = audioEntityIt->second;
		audioEntity->stop();
		audioEntity->dispose();
		audioEntities.erase(audioEntityIt);
	}
}

void Audio::reset()
{
	vector<wstring> keys;
	for (auto it = audioEntities.begin(); it != audioEntities.end(); ++it) {
		keys.push_back(it->first);
	}
	for (auto& key: keys) {
		removeEntity(key);
	}
}

void Audio::shutdown()
{
	reset();
}

void Audio::update()
{
	for (auto it = audioEntities.begin(); it != audioEntities.end(); ++it) {
		it->second->update();
	}
	/*
	al->alListenerfv(AL::AL_POSITION, listenerPosition->getArray(), 0);
	al->alListenerfv(AL::AL_VELOCITY, listenerVelocity->getArray(), 0);
	*/
	auto listenerOrientationAtArray = listenerOrientationAt.getArray();
	auto listenerOrientationUpArray = listenerOrientationUp.getArray();
	array<float, 6> listenerOrientation = {
		(*listenerOrientationAtArray)[0],
		(*listenerOrientationAtArray)[1],
		(*listenerOrientationAtArray)[2],
		(*listenerOrientationUpArray)[0],
		(*listenerOrientationUpArray)[1],
		(*listenerOrientationUpArray)[2]
	};
	/*
	al->alListenerfv(AL::AL_ORIENTATION, listenerOrientation, 0);
	*/
}
