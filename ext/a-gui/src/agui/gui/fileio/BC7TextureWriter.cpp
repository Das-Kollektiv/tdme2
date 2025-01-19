#include <agui/gui/fileio/BC7TextureWriter.h>

#include <ext/bc7enc_rdo/bc7enc.h>

#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/math/Math.h>
#include <agui/utilities/ByteBuffer.h>
#include <agui/utilities/Console.h>

using std::string;
using std::to_string;
using std::vector;

using agui::gui::fileio::BC7TextureWriter;

using agui::math::Math;
using agui::utilities::ByteBuffer;
using agui::utilities::Console;

bool BC7TextureWriter::write(int width, int height, int bytesPerPixel, const ByteBuffer& textureByteBuffer, vector<uint8_t>& bc7Data) {
	//
	bc7enc_compress_block_params bc7encParameters;
	bc7encParameters.m_uber_level = BC7ENC_MAX_UBER_LEVEL;
	bc7enc_compress_block_params_init(&bc7encParameters);
	bc7enc_compress_block_params_init_linear_weights(&bc7encParameters);

	//
	auto xBlocks = static_cast<int>(Math::ceil(width / 4.0f));
	auto yBlocks = static_cast<int>(Math::ceil(height / 4.0f));
	bc7Data.resize(xBlocks * yBlocks * 16);

	//
	for (auto yBlock = 0; yBlock < yBlocks; yBlock++) {
		for (auto xBlock = 0; xBlock < xBlocks; xBlock++) {
			//
			array<uint8_t, 4 * 4 * 4> rgbaBlockPixels { 0 };
			auto blockPixelIdx = 0;
			auto xBlockOffset = xBlock * 4;
			auto yBlockOffset = yBlock * 4;
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					auto offset = (yBlockOffset + y) * width * bytesPerPixel + (xBlockOffset + x) * bytesPerPixel;
					auto red = 0xff;
					auto green = 0;
					auto blue = 0;
					auto alpha = 0;
					if (offset < textureByteBuffer.getCapacity()) {
						red = textureByteBuffer.get(offset + 0);
						green = textureByteBuffer.get(offset + 1);
						blue = textureByteBuffer.get(offset + 2);
						alpha = bytesPerPixel == 4?textureByteBuffer.get(offset + 3):0xff;
					}
					rgbaBlockPixels[blockPixelIdx * 4 + 0] = red;
					rgbaBlockPixels[blockPixelIdx * 4 + 1] = green;
					rgbaBlockPixels[blockPixelIdx * 4 + 2] = blue;
					rgbaBlockPixels[blockPixelIdx * 4 + 3] = alpha;
					blockPixelIdx++;
				}
			}
			//
			bc7enc_compress_block_init();
			bc7enc_compress_block(&bc7Data.data()[yBlock * xBlocks * 16 + xBlock * 16], rgbaBlockPixels.data(), &bc7encParameters);
		}
	}

	//
	return true;
}
