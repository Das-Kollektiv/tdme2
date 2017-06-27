// Generated from /tdme/src/tdme/audio/AudioBufferManager.java
#include <tdme/audio/AudioBufferManager.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/AudioBufferManager_AudioBufferManaged.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_HashMap.h>

using tdme::audio::AudioBufferManager;
using java::lang::ClassCastException;
using java::lang::Object;
using java::lang::String;
using tdme::audio::Audio;
using tdme::audio::AudioBufferManager_AudioBufferManaged;
using tdme::utils::_Console;
using tdme::utils::_HashMap;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

AudioBufferManager::AudioBufferManager(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

AudioBufferManager::AudioBufferManager() 
	: AudioBufferManager(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void AudioBufferManager::ctor()
{
	super::ctor();
	audioBuffers = new _HashMap();
}

AudioBufferManager_AudioBufferManaged* AudioBufferManager::addAudioBuffer(String* id)
{
	auto audioBufferManaged = java_cast< AudioBufferManager_AudioBufferManaged* >(audioBuffers->get(id));
	if (audioBufferManaged != nullptr) {
		audioBufferManaged->incrementReferenceCounter();
		return audioBufferManaged;
	}
	audioBufferManaged = new AudioBufferManager_AudioBufferManaged(this, id, Audio::ALBUFFERID_NONE);
	audioBufferManaged->incrementReferenceCounter();
	audioBuffers->put(audioBufferManaged->getId(), audioBufferManaged);
	return audioBufferManaged;
}

bool AudioBufferManager::removeAudioBuffer(String* id)
{
	auto audioBufferManaged = java_cast< AudioBufferManager_AudioBufferManaged* >(audioBuffers->get(id));
	if (audioBufferManaged != nullptr) {
		if (audioBufferManaged->decrementReferenceCounter()) {
			audioBuffers->remove(id);
			return true;
		} else {
			return false;
		}
	}
	_Console::println(static_cast< Object* >(u"Warning: audio buffer not loaded by audio buffer manager"_j));
	return false;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AudioBufferManager::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.audio.AudioBufferManager", 29);
    return c;
}

java::lang::Class* AudioBufferManager::getClass0()
{
	return class_();
}

