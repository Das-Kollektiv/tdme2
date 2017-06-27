// Generated from /tdme/src/tdme/audio/Sound.java
#include <tdme/audio/Sound.h>

#include <com/jogamp/openal/AL.h>
#include <java/io/File.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/nio/ByteBuffer.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/AudioBufferManager_AudioBufferManaged.h>
#include <tdme/audio/AudioBufferManager.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>
#include <Array.h>

using tdme::audio::Sound;
using com::jogamp::openal::AL;
using java::io::File;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::nio::ByteBuffer;
using tdme::audio::Audio;
using tdme::audio::AudioBufferManager_AudioBufferManaged;
using tdme::audio::AudioBufferManager;
using tdme::math::Vector3;
using tdme::utils::_Console;

Sound::Sound(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Sound::Sound(String* id, String* pathName, String* fileName) 
	: Sound(*static_cast< ::default_init_tag* >(0))
{
	ctor(id,pathName,fileName);
}

void Sound::init()
{
	initiated = false;
}

void Sound::ctor(String* id, String* pathName, String* fileName)
{
	super::ctor(id);
	init();
	this->bufferId = ::java::lang::StringBuilder().append(pathName)->append(File::separator)
		->append(fileName)->toString();
	this->pathName = pathName;
	this->fileName = fileName;
	alBufferId = Audio::ALBUFFERID_NONE;
	alSourceId = Audio::ALSOURCEID_NONE;
}

bool Sound::isPlaying()
{
	auto state = new int32_tArray(1);
	Audio::al->alGetSourcei(alSourceId, AL::AL_SOURCE_STATE, state, 0);
	return ((*state)[0] == AL::AL_PLAYING);
}

void Sound::rewind()
{
	if (initiated == false)
		return;

	Audio::al->alSourceRewind(alSourceId);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
			->append(u"': Could not rewind"_j)->toString()));
	}
}

void Sound::play()
{
	if (initiated == false)
		return;

	update();
	Audio::al->alSourcePlay(alSourceId);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
			->append(u"': Could not play"_j)->toString()));
	}
}

void Sound::pause()
{
	if (initiated == false)
		return;

	Audio::al->alSourcePause(alSourceId);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
			->append(u"': Could not pause"_j)->toString()));
	}
}

void Sound::stop()
{
	if (initiated == false)
		return;

	Audio::al->alSourceStop(alSourceId);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
			->append(u"': Could not stop"_j)->toString()));
	}
}

bool Sound::initialize()
{
	auto audioBufferManaged = Audio::instance->audioBufferManager->addAudioBuffer(bufferId);
	if (audioBufferManaged->alId == Audio::ALBUFFERID_NONE) {
		auto bufferIdArray = new int32_tArray(1);
		Audio::al->alGenBuffers(1, bufferIdArray, 0);
		if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
				->append(u"': Could not generate buffer"_j)->toString()));
			return false;
		}
		alBufferId = (*bufferIdArray)[0];
		audioBufferManaged->setAlId(alBufferId);
		auto format = -1;
		auto frequency = -1;
		auto data = ByteBuffer::allocate(2 * 2 * 10* 60* 44100);
		if (true == true)
			return false;

		if (format == -1 || frequency == -1) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
				->append(u"': Format or frequency invalid"_j)->toString()));
			dispose();
			return false;
		}
		Audio::al->alBufferData(alBufferId, format, data, data->remaining(), frequency);
		if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
				->append(u"': Could not upload buffer data"_j)->toString()));
			dispose();
			return false;
		}
	} else {
		alBufferId = audioBufferManaged->alId;
	}
	auto sourceIds = new int32_tArray(1);
	Audio::al->alGenSources(1, sourceIds, 0);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
			->append(u"': Could not generate source"_j)->toString()));
		dispose();
		return false;
	}
	alSourceId = (*sourceIds)[0];
	Audio::al->alSourcei(alSourceId, AL::AL_BUFFER, alBufferId);
	update();
	initiated = true;
	return true;
}

void Sound::update()
{
	Audio::al->alSourcef(alSourceId, AL::AL_PITCH, pitch);
	Audio::al->alSourcef(alSourceId, AL::AL_GAIN, gain);
	Audio::al->alSourcefv(alSourceId, AL::AL_POSITION, sourcePosition->getArray(), 0);
	Audio::al->alSourcefv(alSourceId, AL::AL_DIRECTION, sourceDirection->getArray(), 0);
	Audio::al->alSourcefv(alSourceId, AL::AL_VELOCITY, sourceVelocity->getArray(), 0);
	Audio::al->alSourcei(alSourceId, AL::AL_LOOPING, looping ? AL::AL_TRUE : AL::AL_FALSE);
	if (fixed == true) {
		Audio::al->alSourcef(alSourceId, AL::AL_ROLLOFF_FACTOR, 0.0f);
		Audio::al->alSourcei(alSourceId, AL::AL_SOURCE_RELATIVE, AL::AL_TRUE);
	} else {
		Audio::al->alSourcef(alSourceId, AL::AL_ROLLOFF_FACTOR, 1.0f);
		Audio::al->alSourcei(alSourceId, AL::AL_SOURCE_RELATIVE, AL::AL_FALSE);
	}
}

void Sound::dispose()
{
	if (alSourceId != Audio::ALSOURCEID_NONE) {
		Audio::al->alDeleteSources(1, new int32_tArray({alSourceId}), 0);
		if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
				->append(u"': Could not delete source"_j)->toString()));
		}
		alSourceId = Audio::ALSOURCEID_NONE;
	}
	if (alBufferId != Audio::ALBUFFERID_NONE && Audio::instance->audioBufferManager->removeAudioBuffer(bufferId) == true) {
		Audio::al->alDeleteBuffers(1, new int32_tArray({alBufferId}), 0);
		if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
				->append(u"': Could not delete buffers"_j)->toString()));
		}
		alBufferId = Audio::ALBUFFERID_NONE;
	}
	initiated = false;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Sound::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.audio.Sound", 16);
    return c;
}

java::lang::Class* Sound::getClass0()
{
	return class_();
}

