#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/engine/ColorTextureCanvas.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector2.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Time.h>

using std::string;
using std::to_string;

using tdme::application::Application;
using tdme::engine::ColorTextureCanvas;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::fileio::textures::PNGTextureWriter;
using tdme::math::Math;
using tdme::math::Vector2;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::Time;


int main(int argc, char** argv) {
	Console::println("SplineTest");

	//
	auto beginTime = Time::getCurrentMillis();

	// create png
	auto imageWidth = 1024;
	auto imageHeight = 1024;
	auto imageScale = 1024.0f / 7.0f;
	auto textureByteBuffer = ByteBuffer::allocate(imageWidth * imageHeight * 4);
	auto texture = new Texture(
		"bezier-test",
		32,
		imageWidth,
		imageHeight,
		imageWidth,
		imageHeight,
		textureByteBuffer
	);
	texture->acquireReference();


	ColorTextureCanvas canvas(texture);
	canvas.drawBezier(
		{
			Vector2(0.0f, 0.0f),
			Vector2(0.0f, imageHeight - 1),
			Vector2(imageWidth - 1, imageHeight - 1),
			Vector2(imageWidth - 1, 0.0f)
		},
		0xff,
		0x00,
		0x00,
		0xff
	);

	//
	auto endTime = Time::getCurrentMillis();

	//
	Console::println("Time to generate spline+texture: " + to_string(endTime - beginTime) + "ms");

	//
	auto smoothedTexture = TextureReader::smooth(texture, ":smoothed", 0.5f);
	PNGTextureWriter::write(smoothedTexture, ".", "bezier-test.png", true, false);

	//
	texture->releaseReference();
	smoothedTexture->releaseReference();
}
