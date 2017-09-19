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

#include <tdme/audio/decoder/VorbisDecoder.h>

#include <vorbis/vorbisfile.h>

#include <string>

#include <tdme/audio/decoder/fwd-tdme.h>
#include <tdme/audio/decoder/AudioDecoderException.h>
#include <tdme/os/fwd-tdme.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/ByteBuffer.h>

using std::wstring;

using tdme::audio::decoder::VorbisDecoder;

VorbisDecoder::VorbisDecoder() : AudioDecoder()
{
}

void VorbisDecoder::openFile(const wstring& pathName, const wstring& fileName) throw (_FileSystemException, AudioDecoderException) {
	this->pathName = pathName;
	this->fileName = fileName;
	if (ov_open_callbacks(stdin, &vf, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0) {
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
}

void VorbisDecoder::reset() throw (_FileSystemException, AudioDecoderException) {
	close();
	openFile(pathName, fileName);
}

int32_t VorbisDecoder::readFromStream(ByteBuffer* data) throw (_FileSystemException, AudioDecoderException) {
	return ov_read(
		&vf,
		(char*)data->getBuffer(),
		data->getCapacity(),
		0,
		2,
		1,
		&section
	);
}

/**
 * Closes the audio file
 */
void VorbisDecoder::close() throw (_FileSystemException, AudioDecoderException) {
	ov_clear(&vf);
}
