// This source code is based on
/*
PL_MPEG Example - Video player using SDL2/OpenGL for rendering

Dominic Szablewski - https://phoboslab.org


-- LICENSE: The MIT License(MIT)

Copyright(c) 2019 Dominic Szablewski

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files(the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions :
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define PL_MPEG_IMPLEMENTATION
#include <ext/pl_mpeg/pl_mpeg.h>

#include <tdme/tdme.h>
#include <tdme/video/decoder/MPEG1Decoder.h>
#include <tdme/video/decoder/VideoDecoderException.h>

#include <memory>
#include <string>

#include <tdme/math/Math.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>

using tdme::video::decoder::MPEG1Decoder;

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;

using tdme::math::Math;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::video::decoder::VideoDecoderException;

void MPEG1Decoder::openFile(const string& pathName, const string& fileName) {
	// close old stream
	close();

	// open new stream
	plm = plm_create_with_filename((pathName + "/" + fileName).c_str());
	if (plm == nullptr) {
		Console::printLine("MPEG1Decoder::openFile(): Failed to open: " + pathName + "/" + fileName);
		throw VideoDecoderException("Failed to open file");
	}

	plm_set_video_decode_callback(plm, plmOnVideo, this);
	plm_set_audio_decode_callback(plm, plmOnAudio, this);

	//
	audioSampleRate = plm_get_samplerate(plm);
	audioChannels = 2;
	videoFrameRate = plm_get_framerate(plm);
	videoDuration = plm_get_duration(plm);
	videoWidth = plm_get_width(plm);
	videoHeight = plm_get_height(plm);
	videoBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(static_cast<int>(videoWidth) * static_cast<int>(videoHeight) * 4));
	audioBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(32768));

	// request looping, enable audio, use stream 0
	plm_set_loop(plm, TRUE);
	plm_set_audio_enabled(plm, TRUE);
	plm_set_audio_stream(plm, 0);

	// audio lead time
	if (plm_get_num_audio_streams(plm) > 0) {
		auto samplesPerBuffer = 4096;
		plm_set_audio_lead_time(plm, (float)samplesPerBuffer / (float)audioSampleRate);
	}
}

void MPEG1Decoder::reset() {
	if (plm == nullptr) return;
	plm_seek(plm, 0.0f, FALSE);
}

void MPEG1Decoder::update(float deltaTime) {
	if (plm == nullptr) return;
	plm_decode(plm, deltaTime);
}

void MPEG1Decoder::seek(float time) {
	if (plm == nullptr) return;
	plm_seek(plm, time, FALSE);
}

int64_t MPEG1Decoder::readAudioFromStream(ByteBuffer* data) {
	if (plm == nullptr) return 0LL;
	auto read = Math::min(audioBuffer->getPosition(), data->getCapacity() - data->getPosition());
	data->put(audioBuffer->getBuffer(), read);
	audioBuffer->clear();
	return read;
}

int64_t MPEG1Decoder::readVideoFromStream(ByteBuffer* data) {
	if (plm == nullptr) return 0LL;
	auto read = Math::min(videoBuffer->getCapacity(), data->getCapacity() - data->getPosition());
	data->put(videoBuffer->getBuffer(), read);
	return read;
}

void MPEG1Decoder::close() {
	if (plm == nullptr) return;
	plm_destroy(plm);
	plm = nullptr;
	videoBuffer = nullptr;
	audioBuffer = nullptr;
}

void MPEG1Decoder::plmOnVideo(plm_t* plm, plm_frame_t *frame, void *user) {
	auto mpeg1Decoder = static_cast<MPEG1Decoder*>(user);
	auto frameBuffer = mpeg1Decoder->videoBuffer->getBuffer();
	plm_frame_to_rgba(frame, frameBuffer, frame->width * 4);
	for (auto y = 0; y < mpeg1Decoder->videoHeight; y++) {
		for (auto x = 0; x < mpeg1Decoder->videoWidth; x++) {
			frameBuffer[y * mpeg1Decoder->videoWidth * 4 + x * 4 + 3] = 0xff;
		}
	}
}

void MPEG1Decoder::plmOnAudio(plm_t* plm, plm_samples_t *samples, void *user) {
	auto mpeg1Decoder = static_cast<MPEG1Decoder*>(user);
	int samplesToProcess = samples->count * 2;
	for (auto i = 0LL; i < samplesToProcess; i++) {
		auto sample = static_cast<int16_t>(samples->interleaved[i] * 32767);
		mpeg1Decoder->audioBuffer->put((uint8_t*)&sample, sizeof(int16_t));
	}
}
