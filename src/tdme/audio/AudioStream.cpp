#include <tdme/audio/AudioStream.h>

#if defined(__APPLE__)
	#include <OpenAL/al.h>
#elif defined(__FreeBSD__) or defined(__linux__) or defined(_WIN32) or defined(__HAIKU__)
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
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/utils/Console.h>

using std::array;
using std::string;
using std::vector;
using std::to_string;
using std::string;

using tdme::audio::AudioStream;
using tdme::utils::ByteBuffer;
using tdme::audio::Audio;
using tdme::audio::decoder::AudioDecoder;
using tdme::audio::decoder::AudioDecoderException;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystemException;
using tdme::utils::Console;

constexpr int32_t AudioStream::BUFFER_COUNT;

constexpr int32_t AudioStream::BUFFER_SIZE;

AudioStream::AudioStream(const string& id, const string& pathName, const string& fileName) : AudioEntity(id)
{
	initiated = false;
	this->pathName = pathName;
	this->fileName = fileName;
	alSourceId = Audio::ALSOURCEID_NONE;
	format = -1;
	frequency = -1;
	data = nullptr;
}

AudioStream::~AudioStream() {
}

bool AudioStream::isPlaying()
{
	ALint state;
	alGetSourcei(alSourceId, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}

void AudioStream::rewind()
{
	try {
		decoder.reset();
	} catch (FileSystemException &fse) {
		Console::println(string("Audio stream: '"+ (id) + "': " + fse.what()));
	} catch (AudioDecoderException &ade) {
		Console::println(string("Audio stream: '" + (id) + "': " + ade.what()));
	}
}

void AudioStream::play()
{
	if (initiated == false)
		return;

	if (isPlaying() == true)
		stop();

	// update AL properties
	updateProperties();
	ALsizei buffersToPlay = 0;
	for (auto i = 0; i < alBufferIds.size(); i++) {
		data->clear();
		try {
			auto bytesDecoded = decoder.readFromStream(data);
			// skip if no more data is available
			if (bytesDecoded == 0) break;
		} catch (FileSystemException &fse) {
			Console::println(string("Audio stream: '" + (id) + "': " + fse.what()));
		} catch (AudioDecoderException& ade) {
			Console::println(string("Audio stream: '" + (id) + "': " + ade.what()));
		}
		alBufferData(alBufferIds[i], format, data->getBuffer(), data->getPosition(), frequency);
		if (alGetError() != AL_NO_ERROR) {
			Console::println(string("Audio stream: '"+ id + "': Could not upload buffer"));
		}
		buffersToPlay++;
	}

	alSourceQueueBuffers(alSourceId, buffersToPlay, alBufferIds.data());
	if (alGetError() != AL_NO_ERROR) {
		Console::println(string("Audio stream: '" + id + "': Could not queue buffers"));
	}
	alSourcePlay(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::println(string("Audio stream: '"+ id + "': Could not play source"));
	}
}

void AudioStream::pause()
{
	if (initiated == false)
		return;

	alSourcePause(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::println(string("Audio sound: '" + id + "': Could not pause"));
	}
}

void AudioStream::stop()
{
	if (initiated == false)
		return;

	alSourceStop(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::println(string("Audio sound: '" + id + "': Could not stop"));
	}
	// determine queued buffers
	ALint queuedBuffers;
	alGetSourcei(alSourceId, AL_BUFFERS_QUEUED, &queuedBuffers);
	if (alGetError() != AL_NO_ERROR) {
		Console::println(string("Audio stream: '" + id + "': Could not determine queued buffers"));
	}
	// unqueue buffers
	if (queuedBuffers > 0) {
		vector<uint32_t> removedBuffers;
		removedBuffers.resize(queuedBuffers);
		alSourceUnqueueBuffers(alSourceId, queuedBuffers, removedBuffers.data());
		if (alGetError() != AL_NO_ERROR) {
			Console::println(string("Audio stream: '" + id + "': Could not unqueue buffers"));
		}
	}
}

bool AudioStream::initialize()
{
	// decode audio stream
	try {
		// decode ogg vorbis
		decoder.openFile(pathName, fileName);
		Console::println(
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
				Console::println(string("Audio sound: '" + id + "': Unsupported number of channels"));
		}
	} catch (FileSystemException& fse) {
		Console::println(string("Audio sound: '" + (id) + "': " + fse.what()));
		decoder.close();
		dispose();
		return false;
	} catch (AudioDecoderException& ade) {
		Console::println(string("Audio sound: '" + (id) + "': " + ade.what()));
		decoder.close();
		dispose();
		return false;
	}

	alGenBuffers(alBufferIds.size(), alBufferIds.data());
	if (alGetError() != AL_NO_ERROR) {
		Console::println(string("Audio stream: '" + id + "': Could not generate buffer"));
		return false;
	}
	// create source
	alGenSources(1, &alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::println(string("Audio stream: '" + id + "': Could not generate source"));
		dispose();
		return false;
	}
	// initiate sound properties
	updateProperties();
	data = ByteBuffer::allocate(BUFFER_SIZE);
	initiated = true;
	return true;
}

void AudioStream::update()
{
	if (initiated == false)
		return;

	// determine processed buffers
	int32_t processedBuffers;
	alGetSourcei(alSourceId, AL_BUFFERS_PROCESSED, &processedBuffers);
	if (alGetError() != AL_NO_ERROR) {
		Console::println(string("Audio stream: '" + id + "': Could not determine processed buffers"));
	}
	if (processedBuffers > 0) {
		while (processedBuffers > 0) {
			// get a processed buffer id and unqueue it
			uint32_t processedBufferId;
			alSourceUnqueueBuffers(alSourceId, 1, &processedBufferId);
			if (alGetError() != AL_NO_ERROR) {
				Console::println(string("Audio stream: '" + id + "': Could not unqueue buffers"));
			}
			// fill processed buffer again
			data->clear();
			auto bytesDecoded = 0;
			try {
				bytesDecoded = decoder.readFromStream(data);
				if (looping == true && bytesDecoded < BUFFER_SIZE) {
					decoder.reset();
					bytesDecoded += decoder.readFromStream(data);
				}
			} catch (FileSystemException& fse) {
				Console::println(string("Audio stream: '" + (id) + "': " + fse.what()));
			} catch (AudioDecoderException& ade) {
				Console::println(string("Audio stream: '" + (id) + "': " + ade.what()));
			}
			// new buffer if we have any data left
			if (bytesDecoded > 0) {
				// upload buffer data
				alBufferData(processedBufferId, format, data->getBuffer(), data->getPosition(), frequency);
				if (alGetError() != AL_NO_ERROR) {
					Console::println(string("Audio stream: '" + id + "': Could not upload buffer"));
				}
				// queue it
				alSourceQueueBuffers(alSourceId, 1, &processedBufferId);
				if (alGetError() != AL_NO_ERROR) {
					Console::println(string("Audio stream: '" + id + "': Could not queue buffer"));
				}
			}
			// processed it
			processedBuffers--;
		}
	}
	// update AL properties
	updateProperties();
}

void AudioStream::updateProperties()
{
	// update sound properties
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
	if (initiated == false)
		return;

	if (alSourceId != Audio::ALSOURCEID_NONE) {
		alDeleteSources(1, &alSourceId);
		if (alGetError() != AL_NO_ERROR) {
			Console::println(string("Audio sound: '" + id + "': Could not delete source"));
		}
		alSourceId = Audio::ALSOURCEID_NONE;
	}
	// if (alBufferIds != nullptr) {
		alDeleteBuffers(alBufferIds.size(), alBufferIds.data());
		if (alGetError() != AL_NO_ERROR) {
			Console::println(string("Audio sound: '" + id + "': Could not delete buffers"));
		}
	//	alBufferIds = nullptr;
	// }

	decoder.close();
	if (data != nullptr) {
		delete data;
		data = nullptr;
	}
	initiated = false;
}
