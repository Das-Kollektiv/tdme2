#pragma once

#include <ext/libpng/png.h>

#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/fileio/fwd-agui.h>
#include <agui/utilities/ByteBuffer.h>

using std::string;
using std::vector;

// namespaces
namespace agui {
namespace gui {
namespace fileio {
	using ::agui::utilities::ByteBuffer;
}
}
}

/**
 * BC7 texture writer class
 * @author Andreas Drewke
 */
class agui::gui::fileio::BC7TextureWriter final
{
public:

	/**
	 * Writes a texture to BC7 using a data vector
	 * @param width width
	 * @param height height
	 * @param bytesPerPixel bytes per pixel
	 * @param textureByteBuffer texture RGB byte buffer
	 * @param bc7Data BC7 data
	 * @return success
	 */
	static bool write(int width, int height, int bytesPerPixel, const ByteBuffer& textureByteBuffer, vector<uint8_t>& bc7Data);

};
