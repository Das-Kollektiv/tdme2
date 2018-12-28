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

#include <tdme/audio/decoder/VorbisDecoder.h>

#include <vorbis/vorbisfile.h>

#include <string>

#include <tdme/audio/decoder/fwd-tdme.h>
#include <tdme/audio/decoder/AudioDecoderException.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/ByteBuffer.h>

using std::string;

using tdme::audio::decoder::AudioDecoderException;
using tdme::audio::decoder::VorbisDecoder;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::filesystem::FileSystemException;
using tdme::utils::ByteBuffer;

static size_t oggfiledata_read(void* buffer, size_t size, size_t count, VorbisDecoder::OGGFileData* oggFileData) {
	size_t bytesRead = 0;
	for (size_t i = 0; i < size * count; i++) {
		if (oggFileData->position == oggFileData->data.size()) break;
		((uint8_t*)buffer)[i] = oggFileData->data[oggFileData->position];
		bytesRead++;
		oggFileData->position++;
	}
	return bytesRead;
}

static int oggfiledata_seek(VorbisDecoder::OGGFileData* oggFileData, ogg_int64_t offset, int whence) {
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

static int oggfiledata_close(VorbisDecoder::OGGFileData* oggFileData) {
	delete oggFileData;
	return 0;
}

static long oggfiledata_tell(VorbisDecoder::OGGFileData* oggFileData) {
	return oggFileData->position;
}

VorbisDecoder::VorbisDecoder() : AudioDecoder()
{
}

void VorbisDecoder::openFile(const string& pathName, const string& fileName) throw (FileSystemException, AudioDecoderException) {
	// read from file system
	auto oggFileData = new OGGFileData();
	FileSystem::getInstance()->getContent(pathName, fileName, oggFileData->data);

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
	if (ov_open_callbacks(oggFileData, &vf, NULL, 0, oggFileCallbacks) < 0) {
		throw AudioDecoderException("Input does not appear to be an OGG bitstream");
	}

	// fetch audio stream properties
	char **ptr = ov_comment(&vf, -1)->user_comments;
	vorbis_info *vi = ov_info(&vf, -1);

	/*
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

void VorbisDecoder::reset() throw (FileSystemException, AudioDecoderException) {
	close();
	openFile(pathName, fileName);
}

int32_t VorbisDecoder::readFromStream(ByteBuffer* data) throw (FileSystemException, AudioDecoderException) {
	int32_t read = 0;
	while (read < data->getCapacity()) {
		long len = ov_read(
			&vf,
			(char*)(data->getBuffer() + read),
			data->getCapacity() - read,
			0,
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

/**
 * Closes the audio file
 */
void VorbisDecoder::close() throw (FileSystemException, AudioDecoderException) {
	ov_clear(&vf);
}
