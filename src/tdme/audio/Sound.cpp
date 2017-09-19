// Generated from /tdme/src/tdme/audio/Sound.java
#include <tdme/audio/Sound.h>

#include <OpenAL/al.h>

#include <string>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/AudioBufferManager_AudioBufferManaged.h>
#include <tdme/audio/AudioBufferManager.h>
#include <tdme/audio/decoder/fwd-tdme.h>
#include <tdme/audio/decoder/VorbisDecoder.h>
#include <tdme/audio/decoder/AudioDecoderException.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/fwd-tdme.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>

using std::to_wstring;
using std::wstring;
using std::string;

using tdme::audio::Sound;
using tdme::utils::ByteBuffer;
using tdme::audio::Audio;
using tdme::audio::AudioBufferManager_AudioBufferManaged;
using tdme::audio::AudioBufferManager;
using tdme::audio::decoder::AudioDecoderException;
using tdme::audio::decoder::VorbisDecoder;
using tdme::math::Vector3;
using tdme::os::_FileSystemException;
using tdme::utils::StringConverter;
using tdme::utils::_Console;

Sound::Sound(const wstring& id, const wstring& pathName, const wstring& fileName) : AudioEntity(id)
{
	initiated = false;
	this->bufferId = pathName + L"/" + fileName;
	this->pathName = pathName;
	this->fileName = fileName;
	alBufferId = Audio::ALBUFFERID_NONE;
	alSourceId = Audio::ALSOURCEID_NONE;
}

bool Sound::isPlaying()
{
	ALint state;
	alGetSourcei(alSourceId, AL_SOURCE_STATE, &state);
	return (state == AL_PLAYING);
}

void Sound::rewind()
{
	if (initiated == false)
		return;

	alSourceRewind(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio sound: '" + id + L"': Could not rewind"));
	}
}

void Sound::play()
{
	if (initiated == false)
		return;

	update();
	alSourcePlay(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio sound: '" + id + L"': Could not play"));
	}
}

void Sound::pause()
{
	if (initiated == false)
		return;

	alSourcePause(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio sound: '" + id+ L"': Could not pause"));
	}
}

void Sound::stop()
{
	if (initiated == false)
		return;

	alSourceStop(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio sound: '" + id + L"': Could not stop"));
	}
}

bool Sound::initialize()
{
	auto audioBufferManaged = Audio::instance->audioBufferManager.addAudioBuffer(bufferId);
	if (audioBufferManaged->alId == Audio::ALBUFFERID_NONE) {
		int alError;
		alGenBuffers(1, &alBufferId);
		if (alGetError() != AL_NO_ERROR) {
			_Console::println(wstring(L"Audio sound: '" + id + L"': Could not generate buffer"));
			return false;
		}
		audioBufferManaged->setAlId(alBufferId);
		auto format = -1;
		auto frequency = -1;
		auto data = ByteBuffer::allocate(2 * 2 * 10 * 60 * 44100);

		VorbisDecoder decoder;
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
			if (decoder.readFromStream(data) == 0) throw new AudioDecoderException("no audio data was decoded");
			_Console::println(
				wstring(
					L"Audio sound: '" +
					id +
					L"' with length " +
					to_wstring((float)data->getPosition() / 2.0f / (float)decoder.getChannels() / (float)decoder.getSampleRate()) +
					L" seconds" +
					L"(" +
					to_wstring(data->getPosition()) +
					L" bytes)"
				)
			);
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
		decoder.close();
		if (format == -1 || frequency == -1) {
			_Console::println(wstring(L"Audio sound: '" + id + L"': Format or frequency invalid"));
			dispose();
			return false;
		}
		alBufferData(alBufferId, format, data->getBuffer(), data->getPosition(), frequency);
		if (alGetError() != AL_NO_ERROR) {
			_Console::println(wstring(L"Audio sound: '" + id + L"': Could not upload buffer data"));
			dispose();
			return false;
		}
	} else {
		alBufferId = audioBufferManaged->alId;
	}
	alGenSources(1, &alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		_Console::println(wstring(L"Audio sound: '" + id + L"': Could not generate source"));
		dispose();
		return false;
	}
	alSourcei(alSourceId, AL_BUFFER, alBufferId);
	update();
	initiated = true;
	return true;
}

void Sound::update()
{
	alSourcef(alSourceId, AL_PITCH, pitch);
	alSourcef(alSourceId, AL_GAIN, gain);
	alSourcefv(alSourceId, AL_POSITION, sourcePosition.getArray()->data());
	alSourcefv(alSourceId, AL_DIRECTION, sourceDirection.getArray()->data());
	alSourcefv(alSourceId, AL_VELOCITY, sourceVelocity.getArray()->data());
	alSourcei(alSourceId, AL_LOOPING, looping ? AL_TRUE : AL_FALSE);
	if (fixed == true) {
		alSourcef(alSourceId, AL_ROLLOFF_FACTOR, 0.0f);
		alSourcei(alSourceId, AL_SOURCE_RELATIVE, AL_TRUE);
	} else {
		alSourcef(alSourceId, AL_ROLLOFF_FACTOR, 1.0f);
		alSourcei(alSourceId, AL_SOURCE_RELATIVE, AL_FALSE);
	}
}

void Sound::dispose()
{
	if (alSourceId != Audio::ALSOURCEID_NONE) {
		alDeleteSources(1, &alSourceId);
		if (alGetError() != AL_NO_ERROR) {
			_Console::println(wstring(L"Audio sound: '" + id + L"': Could not delete source"));
		}
		alSourceId = Audio::ALSOURCEID_NONE;
	}
	if (alBufferId != Audio::ALBUFFERID_NONE && Audio::instance->audioBufferManager.removeAudioBuffer(bufferId) == true) {
		alDeleteBuffers(1, &alBufferId);
		if (alGetError() != AL_NO_ERROR) {
			_Console::println(wstring(L"Audio sound: '" + id + L"': Could not delete buffers"));
		}
		alBufferId = Audio::ALBUFFERID_NONE;
	}
	initiated = false;
}
