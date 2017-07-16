// Generated from /tdme/src/tdme/audio/Audio.java
#include <tdme/audio/Audio.h>

#include <vector>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <tdme/audio/AudioBufferManager.h>
#include <tdme/audio/AudioEntity.h>
#include <tdme/audio/AudioStream.h>
#include <tdme/audio/Sound.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_HashMap_KeysIterator.h>
#include <tdme/utils/_HashMap_ValuesIterator.h>
#include <tdme/utils/_HashMap.h>
#include <Array.h>

using std::vector;

using tdme::audio::Audio;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using tdme::audio::AudioBufferManager;
using tdme::audio::AudioEntity;
using tdme::audio::AudioStream;
using tdme::audio::Sound;
using tdme::math::Vector3;
using tdme::utils::_Console;
using tdme::utils::_HashMap_KeysIterator;
using tdme::utils::_HashMap_ValuesIterator;
using tdme::utils::_HashMap;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

Audio::Audio(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Audio::Audio() 
	: Audio(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Audio::init()
{
	audioBufferManager = new AudioBufferManager();
	listenerPosition = new Vector3();
	listenerVelocity = new Vector3();
	listenerOrientationAt = new Vector3(0.0f, 0.0f, -1.0f);
	listenerOrientationUp = new Vector3(0.0f, 1.0f, 0.0f);
}

constexpr int32_t Audio::ALBUFFERID_NONE;

constexpr int32_t Audio::ALSOURCEID_NONE;

Audio* Audio::instance;

_HashMap* Audio::audioEntities;

// AL* Audio::al;

Audio* Audio::getInstance()
{
	clinit();
	if (Audio::instance == nullptr) {
		Audio::instance = new Audio();
	}
	return Audio::instance;
}

void Audio::ctor()
{
	super::ctor();
	init();
	/*
	ALut::alutInit();
	al = ALFactory::getAL();
	*/
	update();
}

Vector3* Audio::getListenerPosition()
{
	return listenerPosition;
}

Vector3* Audio::getListenerVelocity()
{
	return listenerVelocity;
}

Vector3* Audio::getListenerOrientationAt()
{
	return listenerOrientationAt;
}

Vector3* Audio::getListenerOrientationUp()
{
	return listenerOrientationUp;
}

AudioEntity* Audio::getEntity(String* id)
{
	return java_cast< AudioEntity* >(audioEntities->get(id));
}

AudioEntity* Audio::addStream(String* id, String* pathName, String* fileName)
{
	AudioEntity* stream = new AudioStream(id, pathName, fileName);
	if (stream->initialize() == true) {
		removeEntity(id);
		audioEntities->put(id, stream);
		return stream;
	} else {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
			->append(u"' failed"_j)->toString()));
		return nullptr;
	}
}

AudioEntity* Audio::addSound(String* id, String* pathName, String* fileName)
{
	AudioEntity* sound = new Sound(id, pathName, fileName);
	if (sound->initialize() == true) {
		removeEntity(id);
		audioEntities->put(id, sound);
		return sound;
	} else {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
			->append(u"' failed"_j)->toString()));
		return nullptr;
	}
}

void Audio::removeEntity(String* id)
{
	auto audioEntity = java_cast< AudioEntity* >(audioEntities->get(id));
	if (audioEntity != nullptr) {
		audioEntity->stop();
		audioEntity->dispose();
		audioEntities->remove(audioEntity->getId());
	}
}

void Audio::reset()
{
	vector<String*> keys;
	for (auto _i = audioEntities->getKeysIterator()->iterator(); _i->hasNext(); ) {
		String* key = java_cast< String* >(_i->next());
		{
			keys.push_back(key);
		}
	}
	for (String* key: keys) {
		removeEntity(key);
	}
}

void Audio::shutdown()
{
	reset();
	// ALut::alutExit();
}

void Audio::update()
{
	for (auto _i = audioEntities->getValuesIterator()->iterator(); _i->hasNext(); ) {
		AudioEntity* audioEntity = java_cast< AudioEntity* >(_i->next());
		{
			audioEntity->update();
		}
	}
	/*
	al->alListenerfv(AL::AL_POSITION, listenerPosition->getArray(), 0);
	al->alListenerfv(AL::AL_VELOCITY, listenerVelocity->getArray(), 0);
	*/
	auto listenerOrientationAtArray = listenerOrientationAt->getArray();
	auto listenerOrientationUpArray = listenerOrientationUp->getArray();
	auto listenerOrientation = new floatArray({
		(*listenerOrientationAtArray)[0],
		(*listenerOrientationAtArray)[1],
		(*listenerOrientationAtArray)[2],
		(*listenerOrientationUpArray)[0],
		(*listenerOrientationUpArray)[1],
		(*listenerOrientationUpArray)[2]
	});
	/*
	al->alListenerfv(AL::AL_ORIENTATION, listenerOrientation, 0);
	*/
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Audio::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.audio.Audio", 16);
    return c;
}

void Audio::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
			instance = nullptr;
			audioEntities = new _HashMap();
		//al = nullptr;
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* Audio::getClass0()
{
	return class_();
}

