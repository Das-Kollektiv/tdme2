// Generated from /tdme/src/tdme/audio/AudioStream.java
#include <tdme/audio/AudioStream.h>

#include <java/io/IOException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/nio/ByteBuffer.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/decoder/AudioDecoder.h>
#include <tdme/audio/decoder/AudioDecoderException.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>
#include <Array.h>

using tdme::audio::AudioStream;
using java::io::IOException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::nio::ByteBuffer;
using tdme::audio::Audio;
using tdme::audio::decoder::AudioDecoder;
using tdme::audio::decoder::AudioDecoderException;
using tdme::math::Vector3;
using tdme::utils::_Console;

AudioStream::AudioStream(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

AudioStream::AudioStream(String* id, String* pathName, String* fileName) 
	: AudioStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(id,pathName,fileName);
}

void AudioStream::init()
{
	initiated = false;
}

constexpr int32_t AudioStream::BUFFER_COUNT;

constexpr int32_t AudioStream::BUFFER_SIZE;

void AudioStream::ctor(String* id, String* pathName, String* fileName)
{
	super::ctor(id);
	init();
	this->pathName = pathName;
	this->fileName = fileName;
	alBufferIds = nullptr;
	alSourceId = Audio::ALSOURCEID_NONE;
	decoder = nullptr;
	format = -1;
	frequency = -1;
	data = nullptr;
}

bool AudioStream::isPlaying()
{
	/*
	auto state = new int32_tArray(1);
	Audio::al->alGetSourcei(alSourceId, AL::AL_SOURCE_STATE, state, 0);
	return ((*state)[0] == AL::AL_PLAYING);
	*/
	return false;
}

void AudioStream::rewind()
{
	if (initiated == false)
		return;

	try {
		decoder->reset();
	} catch (IOException* ioe) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
			->append(u"': "_j)
			->append(ioe->getMessage())->toString()));
	} catch (AudioDecoderException* ade) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
			->append(u"': "_j)
			->append(ade->getMessage())->toString()));
	}
}

void AudioStream::play()
{
	if (initiated == false)
		return;

	if (isPlaying() == true)
		stop();

	updateProperties();
	auto buffersToPlay = 0;
	for (auto i = 0; i < alBufferIds->length; i++) {
		data->clear();
		try {
			auto bytesDecoded = decoder->readFromStream(data);
			if (bytesDecoded == 0)
				break;

		} catch (IOException* ioe) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
				->append(u"': "_j)
				->append(ioe->getMessage())->toString()));
		} catch (AudioDecoderException* ade) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
				->append(u"': "_j)
				->append(ade->getMessage())->toString()));
		}
		/*
		Audio::al->alBufferData((*alBufferIds)[i], format, data, data->remaining(), frequency);
		if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
				->append(u"': Could not upload buffer"_j)->toString()));
		}
		buffersToPlay++;
		*/
	}
	/*
	Audio::al->alSourceQueueBuffers(alSourceId, buffersToPlay, alBufferIds, 0);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
			->append(u"': Could not queue buffers"_j)->toString()));
	}
	Audio::al->alSourcePlay(alSourceId);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
			->append(u"': Could not play source"_j)->toString()));
	}
	*/
}

void AudioStream::pause()
{
	if (initiated == false)
		return;

	/*
	Audio::al->alSourcePause(alSourceId);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
			->append(u"': Could not pause"_j)->toString()));
	}
	*/
}

void AudioStream::stop()
{
	if (initiated == false)
		return;

	/*
	Audio::al->alSourceStop(alSourceId);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
			->append(u"': Could not stop"_j)->toString()));
	}
	auto queuedBuffersArray = new int32_tArray(1);
	Audio::al->alGetSourcei(alSourceId, AL::AL_BUFFERS_QUEUED, queuedBuffersArray, 0);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
			->append(u"': Could not determine queued buffers"_j)->toString()));
	}
	auto queuedBuffers = (*queuedBuffersArray)[0];
	if (queuedBuffers > 0) {
		auto removedBuffers = new int32_tArray(queuedBuffers);
		Audio::al->alSourceUnqueueBuffers(alSourceId, queuedBuffers, removedBuffers, 0);
		if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
				->append(u"': Could not unqueue buffers"_j)->toString()));
		}
	}
	*/
}

bool AudioStream::initialize()
{
	if (true == true)
		return false;

	/*
	alBufferIds = new int32_tArray(BUFFER_COUNT);
	Audio::al->alGenBuffers(alBufferIds->length, alBufferIds, 0);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
			->append(u"': Could not generate buffer"_j)->toString()));
		return false;
	}
	auto sourceIds = new int32_tArray(1);
	Audio::al->alGenSources(1, sourceIds, 0);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
			->append(u"': Could not generate source"_j)->toString()));
		dispose();
		return false;
	}
	alSourceId = (*sourceIds)[0];
	*/
	updateProperties();
	data = ByteBuffer::allocateDirect(BUFFER_SIZE);
	initiated = true;
	return true;
}

void AudioStream::update()
{
	if (initiated == false)
		return;

	/*
	auto processedBuffersArray = new int32_tArray(1);
	Audio::al->alGetSourcei(alSourceId, AL::AL_BUFFERS_PROCESSED, processedBuffersArray, 0);
	if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
			->append(u"': Could not determine processed buffers"_j)->toString()));
	}
	auto processedBuffers = (*processedBuffersArray)[0];
	if (processedBuffers > 0) {
		while (processedBuffers > 0) {
			auto processedBufferIdArray = new int32_tArray(1);
			Audio::al->alSourceUnqueueBuffers(alSourceId, 1, processedBufferIdArray, 0);
			if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
					->append(u"': Could not unqueue buffers"_j)->toString()));
			}
			auto processedBufferId = (*processedBufferIdArray)[0];
			data->clear();
			auto bytesDecoded = 0;
			try {
				bytesDecoded = decoder->readFromStream(data);
				if (looping == true && bytesDecoded < BUFFER_SIZE) {
					decoder->reset();
					bytesDecoded += decoder->readFromStream(data);
				}
			} catch (IOException* ioe) {
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
					->append(u"': "_j)
					->append(ioe->getMessage())->toString()));
			} catch (AudioDecoderException* ade) {
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
					->append(u"': "_j)
					->append(ade->getMessage())->toString()));
			}
			if (bytesDecoded > 0) {
				Audio::al->alBufferData(processedBufferId, format, data, data->remaining(), frequency);
				if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
					_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
						->append(u"': Could not upload buffer"_j)->toString()));
				}
				Audio::al->alSourceQueueBuffers(alSourceId, 1, processedBufferIdArray, 0);
				if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
					_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio stream: '"_j)->append(id)
						->append(u"': Could not queue buffer"_j)->toString()));
				}
			}
			processedBuffers--;
		}
	}
	*/
	updateProperties();
}

void AudioStream::updateProperties()
{
	/*
	Audio::al->alSourcef(alSourceId, AL::AL_PITCH, pitch);
	Audio::al->alSourcef(alSourceId, AL::AL_GAIN, gain);
	Audio::al->alSourcefv(alSourceId, AL::AL_POSITION, sourcePosition->getArray(), 0);
	Audio::al->alSourcefv(alSourceId, AL::AL_DIRECTION, sourceDirection->getArray(), 0);
	Audio::al->alSourcefv(alSourceId, AL::AL_VELOCITY, sourceVelocity->getArray(), 0);
	if (fixed == true) {
		Audio::al->alSourcef(alSourceId, AL::AL_ROLLOFF_FACTOR, 0.0f);
		Audio::al->alSourcei(alSourceId, AL::AL_SOURCE_RELATIVE, AL::AL_TRUE);
	} else {
		Audio::al->alSourcef(alSourceId, AL::AL_ROLLOFF_FACTOR, 1.0f);
		Audio::al->alSourcei(alSourceId, AL::AL_SOURCE_RELATIVE, AL::AL_FALSE);
	}
	*/
}

void AudioStream::dispose()
{
	/*
	if (alSourceId != Audio::ALSOURCEID_NONE) {
		Audio::al->alDeleteSources(1, new int32_tArray({alSourceId}), 0);
		if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
				->append(u"': Could not delete source"_j)->toString()));
		}
		alSourceId = Audio::ALSOURCEID_NONE;
	}
	if (alBufferIds != nullptr) {
		Audio::al->alDeleteBuffers(alBufferIds->length, alBufferIds, 0);
		if (Audio::al->alGetError() != AL::AL_NO_ERROR) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Audio sound: '"_j)->append(id)
				->append(u"': Could not delete buffers"_j)->toString()));
		}
		alBufferIds = nullptr;
	}
	*/
	if (decoder != nullptr)
		decoder->close();

	initiated = false;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AudioStream::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.audio.AudioStream", 22);
    return c;
}

java::lang::Class* AudioStream::getClass0()
{
	return class_();
}

