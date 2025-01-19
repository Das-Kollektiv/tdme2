#include <agui/audio/Sound.h>

#if defined(__APPLE__)
	#include <OpenAL/al.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__linux__) || defined(_WIN32) || defined(__HAIKU__)
	#include <AL/al.h>
#endif

#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/audio/decoder/fwd-agui.h>
#include <agui/audio/decoder/AudioDecoderException.h>
#include <agui/audio/decoder/VorbisDecoder.h>
#include <agui/audio/Audio.h>
#include <agui/audio/AudioBufferManager.h>
#include <agui/math/Vector3.h>
#include <agui/os/filesystem/fwd-agui.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/utilities/ByteBuffer.h>
#include <agui/utilities/Console.h>

using agui::audio::Sound;

using std::string;
using std::to_string;
using std::unique_ptr;

using agui::audio::decoder::AudioDecoderException;
using agui::audio::decoder::VorbisDecoder;
using agui::audio::Audio;
using agui::audio::AudioBufferManager;
using agui::math::Vector3;
using agui::os::filesystem::FileSystemException;
using agui::utilities::ByteBuffer;
using agui::utilities::Console;

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
		Console::printLine(string("Audio sound: '" + id + "': Could not rewind"));
	}
}

void Sound::play()
{
	if (initiated == false)
		return;
	// update
	update();
	// play
	alSourcePlay(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("Audio sound: '" + id + "': Could not play"));
	}
}

void Sound::pause()
{
	if (initiated == false)
		return;

	alSourcePause(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("Audio sound: '" + id+ "': Could not pause"));
	}
}

void Sound::stop()
{
	if (initiated == false)
		return;

	alSourceStop(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("Audio sound: '" + id + "': Could not stop"));
	}
}

bool Sound::initialize()
{
	// check if we already have this buffer
	auto managedAudioBuffer = Audio::instance->audioBufferManager.addAudioBuffer(bufferId);
	if (managedAudioBuffer->alId == Audio::ALBUFFERID_NONE) {
		// nope, generate al buffer
		int alError;
		alGenBuffers(1, &alBufferId);
		if (alGetError() != AL_NO_ERROR) {
			Console::printLine(string("Audio sound: '" + id + "': Could not generate buffer"));
			return false;
		}
		// set up al id in audio buffer managed
		managedAudioBuffer->setAlId(alBufferId);
		auto format = -1;
		auto frequency = -1;

		// decode audio sound
		VorbisDecoder decoder;
		unique_ptr<ByteBuffer> data;
		try {
			// decode ogg vorbis
			decoder.openFile(pathName, fileName);
			Console::printLine(
				string(
					"Audio sound: '" +
					id +
					"' with " +
					to_string(decoder.getBitsPerSample()) +
					" bits per sample, " +
					to_string(decoder.getChannels()) +
					" channels, " +
					to_string(decoder.getSampleRate()) +
					" samplerate"
				)
			);
			frequency = decoder.getSampleRate();
			switch (decoder.getChannels()) {
				case(1): format = AL_FORMAT_MONO16; break;
				case(2): format = AL_FORMAT_STEREO16; break;
				default:
					Console::printLine(string("Audio sound: '" + id + "': Unsupported number of channels"));
			}
			data = unique_ptr<ByteBuffer>(ByteBuffer::allocate(2 * 2 * decoder.getSamples()));
			if (decoder.readFromStream(data.get()) == 0) throw AudioDecoderException("no audio data was decoded");
			Console::printLine(
				string(
					"Audio sound: '" +
					id +
					"' with length " +
					to_string((float)data->getPosition() / 2.0f / (float)decoder.getChannels() / (float)decoder.getSampleRate()) +
					" seconds" +
					"(" +
					to_string(data->getPosition()) +
					" bytes)"
				)
			);
		} catch (FileSystemException& fse) {
			Console::printLine(string("Audio sound: '" + (id) + "': " + fse.what()));
			decoder.close();
			dispose();
			return false;
		} catch (AudioDecoderException& ade) {
			Console::printLine(string("Audio sound: '" + (id) + "': " + ade.what()));
			decoder.close();
			dispose();
			return false;
		}
		decoder.close();
		// check for valid format and frequency
		if (format == -1 || frequency == -1) {
			Console::printLine(string("Audio sound: '" + id + "': Format or frequency invalid"));
			dispose();
			return false;
		}
		// upload to al
		alBufferData(alBufferId, format, data->getBuffer(), data->getPosition(), frequency);
		if (alGetError() != AL_NO_ERROR) {
			Console::printLine(string("Audio sound: '" + id + "': Could not upload buffer data"));
			dispose();
			return false;
		}
	} else {
		alBufferId = managedAudioBuffer->alId;
	}

	// create source
	alGenSources(1, &alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("Audio sound: '" + id + "': Could not generate source"));
		dispose();
		return false;
	}

	// initiate sound properties
	alSourcei(alSourceId, AL_BUFFER, alBufferId);
	update();

	//
	initiated = true;
	return true;
}

void Sound::update()
{
	// update sound properties
	alSourcef(alSourceId, AL_PITCH, pitch);
	alSourcef(alSourceId, AL_GAIN, gain);
	alSourcefv(alSourceId, AL_POSITION, sourcePosition.getArray().data());
	alSourcefv(alSourceId, AL_DIRECTION, sourceDirection.getArray().data());
	alSourcefv(alSourceId, AL_VELOCITY, sourceVelocity.getArray().data());
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
			Console::printLine(string("Audio sound: '" + id + "': Could not delete source"));
		}
		alSourceId = Audio::ALSOURCEID_NONE;
	}
	if (alBufferId != Audio::ALBUFFERID_NONE && Audio::instance->audioBufferManager.removeAudioBuffer(bufferId) == true) {
		alDeleteBuffers(1, &alBufferId);
		if (alGetError() != AL_NO_ERROR) {
			Console::printLine(string("Audio sound: '" + id + "': Could not delete buffers"));
		}
		alBufferId = Audio::ALBUFFERID_NONE;
	}
	initiated = false;
}
