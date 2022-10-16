#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/Vector2.h>
#include <tdme/utilities/ByteBuffer.h>

using std::vector;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::ColorTexture;
using tdme::math::Vector2;
using tdme::utilities::ByteBuffer;

/**
 * Color texture canvas
 * @author Andreas Drewke
 */
class tdme::engine::ColorTextureCanvas final
{
public:
	/**
	 * Public constructor
	 * @param texture texture
	 */
	inline ColorTextureCanvas(Texture* texture) {
		this->texture = texture;
		this->texture->acquireReference();
	}

	/**
	 * Destructor
	 */
	inline virtual ~ColorTextureCanvas() {
		this->texture->releaseReference();
	}

	/**
	 * @return underlying texture, the format is currently RGBA
	 */
	inline Texture* getTexture() {
		return texture;
	}

	/**
	 * Draw pixel
	 * @param x x
	 * @param y y
	 * @param red red
	 * @param green green
	 * @param blue blue
	 * @param alpha alpha
	 */
	inline void drawPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
		auto buffer = texture->getTextureData()->getBuffer();
		auto textureWidth = texture->getTextureWidth();
		auto textureHeight = texture->getTextureHeight();
		if (x < 0 || x >= textureWidth) return;
		if (y < 0 || y >= textureHeight) return;
		buffer[y * textureWidth * 4 + x * 4 + 0] = red;
		buffer[y * textureWidth * 4 + x * 4 + 1] = green;
		buffer[y * textureWidth * 4 + x * 4 + 2] = blue;
		buffer[y * textureWidth * 4 + x * 4 + 3] = alpha;
	}

	/**
	 * Draw line
	 * @param x1 x1
	 * @param y1 y1
	 * @param x2 x2
	 * @param y2 y2
	 * @param red red
	 * @param green green
	 * @param blue blue
	 * @param alpha alpha
	 */
	inline void drawLine(int x1, int y1, int x2, int y2, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
		auto buffer = texture->getTextureData()->getBuffer();
		auto imageWidth = texture->getTextureWidth();
		auto imageHeight = texture->getTextureHeight();

		//
		auto xDelta = x2 - x1;
		auto yDelta = y2 - y1;

		//
		if (Math::abs(xDelta) > Math::abs(yDelta)) {
			auto yAdv = Math::abs(static_cast<float>(yDelta) / static_cast<float>(xDelta));
			if (yDelta < 0) yAdv*= -1.0f;
			auto _y = 0.0f;
			for (int _x = 0; Math::abs(_x) < Math::abs(xDelta); _x+= Math::sign(xDelta)) {
				drawPixel(x1 + _x, static_cast<int>(Math::round(static_cast<float>(y1) + _y)), red, green, blue, alpha);
				_y+= yAdv;
			}
		} else {
			auto xAdv = Math::abs(static_cast<float>(xDelta) / static_cast<float>(yDelta));
			if (xDelta < 0) xAdv*= -1.0f;
			auto _x = 0.0f;
			for (int _y = 0; Math::abs(_y) < Math::abs(yDelta); _y+= Math::sign(yDelta)) {
				drawPixel(static_cast<int>(Math::round(static_cast<float>(x1) + _x)), y1 + _y, red, green, blue, alpha);
				_x+= xAdv;
			}
		}
	}

	/**
	 * Draw bezier curve
	 * @param controlPoints control points
	 * @param red red
	 * @param green green
	 * @param blue blue
	 * @param alpha alpha
	 */
	void drawBezier(const vector<Vector2>& controlPoints, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

private:
	Texture* texture { nullptr };

};
