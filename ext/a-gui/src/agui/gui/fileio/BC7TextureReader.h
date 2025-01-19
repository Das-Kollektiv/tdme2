#pragma once

#include <vector>

#include <agui/agui.h>
#include <agui/gui/fileio/fwd-agui.h>
#include <agui/utilities/ByteBuffer.h>

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
 * BC7 texture reader class
 * @author Andreas Drewke
 */
class agui::gui::fileio::BC7TextureReader final
{
public:
	/**
	 * Read BC7 from memory into texture byte buffer
	 * @param width width
	 * @param height height
	 * @param bytesPerPixel bytes per pixel
	 * @param bc7Data BC7 vector data to read BC7 from
	 * @param textureByteBuffer texture byte buffer
	 * @return success
	 */
	static bool read(int width, int height, int bytesPerPixel, const vector<uint8_t>& bc7Data, ByteBuffer& textureByteBuffer);

};
