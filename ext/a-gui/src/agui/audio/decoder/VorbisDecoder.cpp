// This source code is based on
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2007             *
 * by the Xiph.Org Foundation http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************/

#include <stdio.h>

#include <agui/audio/decoder/VorbisDecoder.h>

#include <vorbis/vorbisfile.h>

#include <string>
#include <memory>

#include <agui/agui.h>
#include <agui/audio/decoder/fwd-agui.h>
#include <agui/audio/decoder/AudioDecoderException.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/ByteBuffer.h>

using std::make_unique;
using std::string;
using std::vector;

using agui::audio::decoder::AudioDecoderException;
using agui::audio::decoder::VorbisDecoder;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;
using agui::utilities::ByteBuffer;

size_t VorbisDecoder::oggfiledata_read(void* buffer, size_t size, size_t count, VorbisDecoder::OGGFileData* oggFileData) {
	size_t bytesRead = 0;
	for (size_t i = 0; i < size * count; i++) {
		if (oggFileData->position == oggFileData->data.size()) break;
		((uint8_t*)buffer)[i] = oggFileData->data[oggFileData->position];
		bytesRead++;
		oggFileData->position++;
	}
	return bytesRead;
}

int VorbisDecoder::oggfiledata_seek(VorbisDecoder::OGGFileData* oggFileData, ogg_int64_t offset, int whence) {
	switch (whence) {
		case SEEK_SET:
			oggFileData->position = offset;
			return 0;
		case SEEK_CUR:
			oggFileData->position+= offset;
			return 0;
		case SEEK_END:
			oggFileData->position = oggFileData->data.size() + offset;
			return 0;
		default:
			return 1;
	}
}

int VorbisDecoder::oggfiledata_close(VorbisDecoder::OGGFileData* oggFileData) {
	return 0;
}

long VorbisDecoder::oggfiledata_tell(VorbisDecoder::OGGFileData* oggFileData) {
	return oggFileData->position;
}

void VorbisDecoder::openFile(const string& pathName, const string& fileName) {
	// read from file system
	oggFileData = make_unique<OGGFileData>();
	FileSystem::getInstance()->getContent(pathName, fileName, oggFileData->data);
	if (oggFileData->data.size() == 0) {
		throw AudioDecoderException("No input");
	}

	// set up ogg file callbacks
	static ov_callbacks oggFileCallbacks = {
	  (size_t (*)(void *, size_t, size_t, void *))  oggfiledata_read,
	  (int (*)(void *, ogg_int64_t, int))           oggfiledata_seek,
	  (int (*)(void *))                             oggfiledata_close,
	  (long (*)(void *))                            oggfiledata_tell
	};

	//
	this->pathName = pathName;
	this->fileName = fileName;
	if (ov_open_callbacks(oggFileData.get(), &vf, NULL, 0, oggFileCallbacks) < 0) {
		throw AudioDecoderException("Input does not appear to be an OGG bitstream");
	}

	// vorbis info
	vorbis_info *vi = ov_info(&vf, -1);

	/*
	// fetch audio stream properties
	char **ptr = ov_comment(&vf, -1)->user_comments;
	// Throw the comments plus a few lines about the bitstream we're decoding
	while (*ptr) {
		fprintf(stderr, "%s\n", *ptr);
		++ptr;
	}
	fprintf(stderr, "\nBitstream is %d channel, %ldHz\n", vi->channels, vi->rate);
	fprintf(stderr, "\nDecoded length: %ld samples\n",(long) ov_pcm_total(&vf, -1));
	fprintf(stderr, "Encoded by: %s\n\n", ov_comment(&vf, -1)->vendor);
	*/

	// set audio stream properties
	channels = vi->channels;
	sampleRate = vi->rate;
	bitsPerSample = 16;
	samples = ov_pcm_total(&vf, -1);
	section = 0;
}

void VorbisDecoder::reset() {
	close();
	openFile(pathName, fileName);
}

int64_t VorbisDecoder::readFromStream(ByteBuffer* data) {
	auto read = 0LL;
	while (read < data->getCapacity()) {
		long len = ov_read(
			&vf,
			(char*)(data->getBuffer() + read),
			data->getCapacity() - read,
			// powerpc and powerpc64 are considered to use big endianess for now
			#if defined(__powerpc__) || defined(__powerpc64__)
				1,
			#else
				0,
			#endif
			2,
			1,
			&section
		);
		if (len <= 0) break;
		read+= len;
	}
	data->setPosition(read);
	return read;
}

void VorbisDecoder::close() {
	if (oggFileData == nullptr) return;
	if (oggFileData->data.size() > 0) ov_clear(&vf);
	oggFileData = nullptr;
}
