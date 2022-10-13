#include <string>

#include <Bezier.h>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Time.h>

using std::string;
using std::to_string;

using tdme::application::Application;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::fileio::textures::PNGTextureWriter;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::Time;


int main(int argc, char** argv) {
	Console::println("SplineTest");

	//
	auto beginTime = Time::getCurrentMillis();

	// generate 100 interpolate points between the last 4 way points
	Curve* curve = new Bezier();
	curve->set_steps(500);

	//
	curve->add_way_point(Vector(0, 0, 0));
	curve->add_way_point(Vector(0, 6, 0));
	curve->add_way_point(Vector(6, 6, 0));
	curve->add_way_point(Vector(6, 0, 0));

	//
	Console::println("Nodes: " + to_string(curve->node_count()));
	Console::println("Total Length: " + to_string(curve->total_length()));
	for (int i = 0; i < curve->node_count(); ++i) {
		Console::println("Node #" + to_string(i) + ": " + curve->node(i).toString() + + " (length so far: " + to_string(curve->length_from_starting_point(i)) + ")");
	}

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

	//
	auto buffer = textureByteBuffer->getBuffer();
	auto previousX = Math::clamp(static_cast<int>(curve->node(0).x * imageScale), 0, imageWidth - 1);
	auto previousY = Math::clamp(static_cast<int>(curve->node(0).y * imageScale), 0, imageHeight - 1);
	for (int i = 1; i < curve->node_count(); ++i) {
		auto x = Math::clamp(static_cast<int>(curve->node(i).x * imageScale), 0, imageWidth - 1);
		auto y = Math::clamp(static_cast<int>(curve->node(i).y * imageScale), 0, imageHeight - 1);

		//
		auto xDelta = x - previousX;
		auto yDelta = y - previousY;

		//
		if (Math::abs(xDelta) > Math::abs(yDelta)) {
			auto yAdv = Math::abs(static_cast<float>(yDelta) / static_cast<float>(xDelta));
			if (yDelta < 0) yAdv*= -1.0f;
			auto _y = 0.0f;
			for (int _x = 0; Math::abs(_x) < Math::abs(xDelta); _x+= Math::sign(xDelta)) {
				auto __x = Math::clamp(previousX + _x, 0, imageWidth - 1);
				auto __y = Math::clamp(static_cast<int>(Math::round(static_cast<float>(previousY) + _y)), 0, imageHeight - 1);
				buffer[__y * imageWidth * 4 + __x * 4 + 0] = 0xff;
				buffer[__y * imageWidth * 4 + __x * 4 + 1] = 0xff;
				buffer[__y * imageWidth * 4 + __x * 4 + 2] = 0xff;
				buffer[__y * imageWidth * 4 + __x * 4 + 3] = 0xff;
				_y+= yAdv;
			}
		} else {
			auto xAdv = Math::abs(static_cast<float>(xDelta) / static_cast<float>(yDelta));
			if (xDelta < 0) xAdv*= -1.0f;
			auto _x = 0.0f;
			for (int _y = 0; Math::abs(_y) < Math::abs(yDelta); _y+= Math::sign(yDelta)) {
				auto __x = Math::clamp(static_cast<int>(Math::round(static_cast<float>(previousX) + _x)), 0, imageWidth - 1);
				auto __y = Math::clamp(previousY + _y, 0, imageHeight - 1);
				buffer[__y * imageWidth * 4 + __x * 4 + 0] = 0xff;
				buffer[__y * imageWidth * 4 + __x * 4 + 1] = 0xff;
				buffer[__y * imageWidth * 4 + __x * 4 + 2] = 0xff;
				buffer[__y * imageWidth * 4 + __x * 4 + 3] = 0xff;
				_x+= xAdv;
			}
		}

		//
		previousX = x;
		previousY = y;
	}


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

	//
	delete curve;

}
