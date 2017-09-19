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
#include <tdme/os/fwd-tdme.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/StringConverter.h>

using std::wstring;

using tdme::audio::decoder::AudioDecoderException;
using tdme::audio::decoder::VorbisDecoder;
using tdme::os::_FileSystemException;
using tdme::utils::ByteBuffer;
using tdme::utils::StringConverter;

VorbisDecoder::VorbisDecoder() : AudioDecoder()
{
}

void VorbisDecoder::openFile(const wstring& pathName, const wstring& fileName) throw (_FileSystemException, AudioDecoderException) {
	this->pathName = pathName;
	this->fileName = fileName;
	if (ov_open_callbacks(fopen(StringConverter::toString(pathName + L"/" + fileName).c_str(), "r"), &vf, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0) {
		throw AudioDecoderException("Input does not appear to be an Ogg bitstream.");
	}
	/* Throw the comments plus a few lines about the bitstream we're decoding */
	char **ptr = ov_comment(&vf, -1)->user_comments;
	vorbis_info *vi = ov_info(&vf, -1);
	while (*ptr) {
		fprintf(stderr, "%s\n", *ptr);
		++ptr;
	}
	fprintf(stderr, "\nBitstream is %d channel, %ldHz\n", vi->channels, vi->rate);
	fprintf(stderr, "\nDecoded length: %ld samples\n",(long) ov_pcm_total(&vf, -1));
	fprintf(stderr, "Encoded by: %s\n\n", ov_comment(&vf, -1)->vendor);
	channels = vi->channels;
	sampleRate = vi->rate;
	bitsPerSample = 16;
	section = 0;
}

void VorbisDecoder::reset() throw (_FileSystemException, AudioDecoderException) {
	close();
	openFile(pathName, fileName);
}

int32_t VorbisDecoder::readFromStream(ByteBuffer* data) throw (_FileSystemException, AudioDecoderException) {
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
void VorbisDecoder::close() throw (_FileSystemException, AudioDecoderException) {
	ov_clear(&vf);
}
