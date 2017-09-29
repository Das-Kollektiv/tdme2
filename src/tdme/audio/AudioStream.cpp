// Generated from /tdme/src/tdme/audio/AudioStream.java
#include <tdme/audio/AudioStream.h>

#if defined(__APPLE__)
	#include <OpenAL/al.h>
#elif defined(__linux__)
	#include <AL/al.h>
#endif

#include <array>
#include <string>
#include <vector>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/decoder/AudioDecoder.h>
#include <tdme/audio/decoder/AudioDecoderException.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <Array.h>

using std::array;
using std::string;
using std::vector;
using std::to_wstring;
using std::wstring;

using tdme::audio::AudioStream;
using tdme::utils::ByteBuffer;
using tdme::audio::Audio;
using tdme::audio::decoder::AudioDecoder;
using tdme::audio::decoder::AudioDecoderException;
using tdme::math::Vector3;
using tdme::os::_FileSystemException;
using tdme::utils::StringConverter;
using tdme::utils::_Console;

constexpr int32_t AudioStream::BUFFER_COUNT;

constexpr int32_t AudioStream::BUFFER_SIZE;

AudioStream::AudioStream(const wstring& id, const wstring& pathName, const wstring& fileName) : AudioEntity(id)
{
	initiated = false;
	this->pathName = pathName;
	this->fileName = fileName;
	alSourceId = Audio::ALSOURCEID_NONE;
	format = -1;
	frequency = -1;
	data = nullptr;
}

bool AudioStream::isPlaying()
{
	ALint state;
	alGetSourcei(alSourceId, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}

void AudioStream::rewind()
{
	if (initiated == false)
		return;

	try {
		decoder.reset();
	} catch (_FileSystemException &fse) {
		_Console::println(string("Audio stream: '"+ StringConverter::toString(id) + "': " + fse.what()));
	} catch (AudioDecoderException &ade) {
		_Console::println(string("Audio stream: '" + StringConverter::toString(id) + "': " + ade.what()));
	}
}

void AudioStream::play()
{
	if (initiated == false)
		return;

	if (isPlaying() == true)
		stop();

	updateProperties();
	ALsizei buffersToPlay = 0;
	for (auto i = 0; i < alBufferIds.size(); i++) {
		data->clear();
		try {
			auto bytesDecoded = decoder.readFromStream(data);
			if (bytesDecoded == 0) break;
		} catch (_FileSystemException &fse) {
			_Console::println(string("Audio stream: '" + StringConverter::toString(id) + "': " + fse.what()));
		} catch (AudioDecoderException& ade) {
			_Console::println(string("Audio stream: '" + StringConverter::toString(id) + "': " + ade.what()));
		}
		alBufferData(alBufferIds[i], format, data->getBuffer(), data->getPosition(), frequency);
		if (alGetError() != AL_NO_ERROR) {
			_Console::println(wstring(L"Audio stream: '"+ id + L"': Could not upload buffer"));
		}
		buffersToPlay++;
	}

	alSourceQueueBuffers(alSourceId, buffersToPlay, alBufferIds.data());
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio stream: '" + id + L"': Could not queue buffers"));
	}
	alSourcePlay(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio stream: '"+ id + L"': Could not play source"));
	}
}

void AudioStream::pause()
{
	if (initiated == false)
		return;

	alSourcePause(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio sound: '" + id + L"': Could not pause"));
	}
}

void AudioStream::stop()
{
	if (initiated == false)
		return;

	alSourceStop(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio sound: '" + id + L"': Could not stop"));
	}
	ALint queuedBuffers;
	alGetSourcei(alSourceId, AL_BUFFERS_QUEUED, &queuedBuffers);
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio stream: '" + id + L"': Could not determine queued buffers"));
	}
	if (queuedBuffers > 0) {
		vector<uint32_t> removedBuffers;
		removedBuffers.resize(queuedBuffers);
		alSourceUnqueueBuffers(alSourceId, queuedBuffers, removedBuffers.data());
		if (alGetError() != AL_NO_ERROR) {
			_Console::println(wstring(L"Audio stream: '" + id + L"': Could not unqueue buffers"));
		}
	}
}

bool AudioStream::initialize()
{
	try {
		// decode ogg vorbis
		decoder.openFile(pathName, fileName);
		_Console::println(
			wstring(
				L"Audio sound: '" +
				id +
				L"' with " +
				to_wstring(decoder.getBitsPerSample()) +
				L" bits per sample, " +
				to_wstring(decoder.getChannels()) +
				L" channels, " +
				to_wstring(decoder.getSampleRate()) +
				L" samplerate"
			)
		);
		frequency = decoder.getSampleRate();
		switch (decoder.getChannels()) {
			case(1): format = AL_FORMAT_MONO16; break;
			case(2): format = AL_FORMAT_STEREO16; break;
			default:
				_Console::println(wstring(L"Audio sound: '" + id + L"': Unsupported number of channels"));
		}
	} catch (_FileSystemException& fse) {
		_Console::println(string("Audio sound: '" + StringConverter::toString(id) + "': " + fse.what()));
		decoder.close();
		dispose();
		return false;
	} catch (AudioDecoderException& ade) {
		_Console::println(string("Audio sound: '" + StringConverter::toString(id) + "': " + ade.what()));
		decoder.close();
		dispose();
		return false;
	}

	alGenBuffers(alBufferIds.size(), alBufferIds.data());
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio stream: '" + id + L"': Could not generate buffer"));
		return false;
	}
	alGenSources(1, &alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio stream: '" + id + L"': Could not generate source"));
		dispose();
		return false;
	}
	updateProperties();
	data = ByteBuffer::allocate(BUFFER_SIZE);
	initiated = true;
	return true;
}

void AudioStream::update()
{
	if (initiated == false)
		return;

	int32_t processedBuffers;
	alGetSourcei(alSourceId, AL_BUFFERS_PROCESSED, &processedBuffers);
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio stream: '" + id + L"': Could not determine processed buffers"));
	}
	if (processedBuffers > 0) {
		while (processedBuffers > 0) {
			uint32_t processedBufferId;
			alSourceUnqueueBuffers(alSourceId, 1, &processedBufferId);
			if (alGetError() != AL_NO_ERROR) {
				_Console::println(wstring(L"Audio stream: '" + id + L"': Could not unqueue buffers"));
			}
			data->clear();
			auto bytesDecoded = 0;
			try {
				bytesDecoded = decoder.readFromStream(data);
				if (looping == true && bytesDecoded < BUFFER_SIZE) {
					decoder.reset();
					bytesDecoded += decoder.readFromStream(data);
				}
			} catch (_FileSystemException& fse) {
				_Console::println(string("Audio stream: '" + StringConverter::toString(id) + "': " + fse.what()));
			} catch (AudioDecoderException& ade) {
				_Console::println(string("Audio stream: '" + StringConverter::toString(id) + "': " + ade.what()));
			}
			if (bytesDecoded > 0) {
				alBufferData(processedBufferId, format, data->getBuffer(), data->getPosition(), frequency);
				if (alGetError() != AL_NO_ERROR) {
					_Console::println(wstring(L"Audio stream: '" + id + L"': Could not upload buffer"));
				}
				alSourceQueueBuffers(alSourceId, 1, &processedBufferId);
				if (alGetError() != AL_NO_ERROR) {
					_Console::println(wstring(L"Audio stream: '" + id + L"': Could not queue buffer"));
				}
			}
			processedBuffers--;
		}
	}
	updateProperties();
}

void AudioStream::updateProperties()
{
	alSourcef(alSourceId, AL_PITCH, pitch);
	alSourcef(alSourceId, AL_GAIN, gain);
	alSourcefv(alSourceId, AL_POSITION, sourcePosition.getArray().data());
	alSourcefv(alSourceId, AL_DIRECTION, sourceDirection.getArray().data());
	alSourcefv(alSourceId, AL_VELOCITY, sourceVelocity.getArray().data());
	if (fixed == true) {
		alSourcef(alSourceId, AL_ROLLOFF_FACTOR, 0.0f);
		alSourcei(alSourceId, AL_SOURCE_RELATIVE, AL_TRUE);
	} else {
		alSourcef(alSourceId, AL_ROLLOFF_FACTOR, 1.0f);
		alSourcei(alSourceId, AL_SOURCE_RELATIVE, AL_FALSE);
	}
}

void AudioStream::dispose()
{
	if (alSourceId != Audio::ALSOURCEID_NONE) {
		alDeleteSources(1, &alSourceId);
		if (alGetError() != AL_NO_ERROR) {
			_Console::println(wstring(L"Audio sound: '" + id + L"': Could not delete source"));
		}
		alSourceId = Audio::ALSOURCEID_NONE;
	}
	// if (alBufferIds != nullptr) {
		alDeleteBuffers(alBufferIds.size(), alBufferIds.data());
		if (alGetError() != AL_NO_ERROR) {
			_Console::println(wstring(L"Audio sound: '" + id + L"': Could not delete buffers"));
		}
	//	alBufferIds = nullptr;
	// }

	decoder.close();

	initiated = false;
}
