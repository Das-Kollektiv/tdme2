#include <agui/audio/VorbisAudioStream.h>

#include <string>

#include <agui/agui.h>
#include <agui/audio/decoder/AudioDecoderException.h>
#include <agui/audio/decoder/VorbisDecoder.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/utilities/ByteBuffer.h>
#include <agui/utilities/Console.h>

using agui::audio::VorbisAudioStream;

using std::string;
using std::to_string;

using agui::audio::decoder::AudioDecoderException;
using agui::audio::decoder::VorbisDecoder;
using agui::os::filesystem::FileSystemException;
using agui::utilities::ByteBuffer;
using agui::utilities::Console;

void VorbisAudioStream::rewind()
{
	if (initiated == false) return;

	try {
		decoder.reset();
	} catch (FileSystemException &fse) {
		Console::printLine(string("VorbisAudioStream::rewind(): '"+ (id) + "': " + fse.what()));
	} catch (AudioDecoderException &ade) {
		Console::printLine(string("VorbisAudioStream::rewind(): '" + (id) + "': " + ade.what()));
	}
}

bool VorbisAudioStream::initialize()
{
	if (initiated == true) return true;

	uint32_t sampleRate = 0;
	uint8_t channels = 0;

	// decode audio stream
	try {
		// decode ogg vorbis
		decoder.openFile(pathName, fileName);
		Console::printLine(
			string(
				"VorbisAudioStream::initialize(): '" +
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
		sampleRate = decoder.getSampleRate();
		channels = decoder.getChannels();
	} catch (FileSystemException& fse) {
		Console::printLine(string("VorbisAudioStream::initialize(): '" + (id) + "': " + fse.what()));
		decoder.close();
		dispose();
		return false;
	} catch (AudioDecoderException& ade) {
		Console::printLine(string("VorbisAudioStream::initialize(): '" + (id) + "': " + ade.what()));
		decoder.close();
		dispose();
		return false;
	}

	// set stream parameters
	setParameters(sampleRate, channels, 32768);

	// check if underlying audio stream did initialize
	if (AudioStream::initialize() == false) {
		// nope, dispose and such
		decoder.close();
		dispose();
		return false;
	}

	// success
	initiated = true;
	return true;
}

void VorbisAudioStream::fillBuffer(ByteBuffer* data) {
	auto bytesDecoded = 0;
	try {
		bytesDecoded = decoder.readFromStream(data);
		if (looping == true && bytesDecoded < data->getCapacity()) {
			decoder.reset();
		}
	} catch (FileSystemException& fse) {
		Console::printLine(string("Audio stream: '" + (id) + "': " + fse.what()));
	} catch (AudioDecoderException& ade) {
		Console::printLine(string("Audio stream: '" + (id) + "': " + ade.what()));
	}
}

void VorbisAudioStream::dispose()
{
	if (initiated == false) return;

	// close decoder
	decoder.close();

	// dispose audio stream
	AudioStream::dispose();

	//
	initiated = false;
}
