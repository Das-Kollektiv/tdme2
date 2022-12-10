#include <tdme/engine/fileio/textures/BZ7TextureReader.h>

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/ByteBuffer.h>

#include <ext/bc7enc_rdo/bc7decomp.h>

using std::array;
using std::string;

using tdme::engine::fileio::textures::BZ7TextureReader;

using tdme::utilities::ByteBuffer;

bool BZ7TextureReader::read(int width, int height, int bytesPerPixel, const vector<uint8_t>& bz7Data, ByteBuffer& textureByteBuffer) {
	//
	auto xBlocks = static_cast<int>(Math::ceil(width / 4.0f));
	auto yBlocks = static_cast<int>(Math::ceil(height / 4.0f));

	//
	auto textureByteBufferBuffer = textureByteBuffer.getBuffer();

	//
	for (auto yBlock = 0; yBlock < yBlocks; yBlock++) {
		for (auto xBlock = 0; xBlock < xBlocks; xBlock++) {
			//
			array<bc7decomp::color_rgba, 4 * 4> rgbaBlockPixels { 0 };
			bc7decomp::unpack_bc7(&bz7Data.data()[yBlock * xBlocks * 16 + xBlock * 16], rgbaBlockPixels.data());
			//
			auto blockPixelIdx = 0;
			auto xBlockOffset = xBlock * 4;
			auto yBlockOffset = yBlock * 4;
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					auto offset = (yBlockOffset + y) * width * bytesPerPixel + (xBlockOffset + x) * bytesPerPixel;
					auto red = rgbaBlockPixels[blockPixelIdx].r;
					auto green = rgbaBlockPixels[blockPixelIdx].g;
					auto blue = rgbaBlockPixels[blockPixelIdx].b;
					auto alpha = rgbaBlockPixels[blockPixelIdx].a;
					if (offset < textureByteBuffer.getCapacity()) {
						textureByteBufferBuffer[offset + 0] = red;
						textureByteBufferBuffer[offset + 1] = green;
						textureByteBufferBuffer[offset + 2] = blue;
						if (bytesPerPixel == 4) textureByteBufferBuffer[offset + 3] = alpha;
					}
					blockPixelIdx++;
				}
			}
		}
	}
	//
	return false;
}

