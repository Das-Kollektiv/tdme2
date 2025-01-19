#pragma once

#include <vorbis/vorbisfile.h>

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/audio/decoder/fwd-tdme.h>
#include <tdme/audio/decoder/AudioDecoder.h>
#include <tdme/audio/decoder/AudioDecoderException.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::vector;
using std::unique_ptr;

using tdme::audio::decoder::AudioDecoder;
using tdme::audio::decoder::AudioDecoderException;
using tdme::os::filesystem::FileSystemException;
using tdme::utilities::ByteBuffer;

/**
 * OGG/Vorbis audio decoder
 * @author Andreas Drewke
 */
class tdme::audio::decoder::VorbisDecoder final: public AudioDecoder
{
private:
	struct OGGFileData {
		vector<uint8_t> data;
		size_t position { 0 };
	};

public:
	/**
	 * Constructor
	 */
	inline VorbisDecoder() {}

	/**
	 * Destructor
	 */
	inline virtual ~VorbisDecoder() {
		close();
	}

	// overridden methods
	void openFile(const string& pathName, const string& fileName) override;
	void reset() override;
	int64_t readFromStream(ByteBuffer* data) override;
	void close() override;

private:
	/**
	 * Read from OGG file data
	 * @param buffer buffer to read into
	 * @param size chunk bytes to read
	 * @param count chunk count to read
	 * @param oggFileData pointer to OGG file data
	 */
	static size_t oggfiledata_read(void* buffer, size_t size, size_t count, VorbisDecoder::OGGFileData* oggFileData);

	/**
	 * Seek in OGG file data
	 * @param oggFileData OGG file data pointer
	 * @param offset offset (can be relative to position)
	 * @param whence whence see (SEEK_*)
	 */
	static int oggfiledata_seek(VorbisDecoder::OGGFileData* oggFileData, ogg_int64_t offset, int whence);

	/**
	 * Close OGG file data
	 * @param oggFileData pointer to OGG file data
	 */
	static int oggfiledata_close(VorbisDecoder::OGGFileData* oggFileData);

	/**
	 * Tell position of OGG file data
	 * @param oggFileData pointer to OGG file data
	 * @returns current read position
	 */
	static long oggfiledata_tell(VorbisDecoder::OGGFileData* oggFileData);

	//
	unique_ptr<OGGFileData> oggFileData;
	string pathName;
	string fileName;
	OggVorbis_File vf;
	int section { 0 };
};
