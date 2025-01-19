#include <agui/gui/misc/GUIColorTextureCanvas.h>

#include <string>

#include <Bezier.h>
#include <Vector.h>

#include <agui/agui.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/math/Math.h>
#include <agui/utilities/ByteBuffer.h>
#include <agui/utilities/Console.h>

using agui::gui::misc::GUIColorTextureCanvas;

using agui::gui::textures::GUITexture;
using agui::math::Math;
using agui::utilities::ByteBuffer;
using agui::utilities::Console;

void GUIColorTextureCanvas::drawBezier(const vector<Vector2>& controlPoints, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	if (controlPoints.empty() == true) {
		Console::printLine("GUIColorTextureCanvas::drawBezier(): no control points given");
		return;
	}

	//
	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();
	auto buffer = texture->getTextureData()->getBuffer();

	//
	Bezier bezier;
	bezier.set_steps(static_cast<int>(Math::sqrt(static_cast<float>(textureWidth) * static_cast<float>(textureHeight)) / 2.0f));
	for (const auto& controlPoint: controlPoints) {
		bezier.add_way_point(Vector(controlPoint.getX(), controlPoint.getY(), 0.0));
	}
	while (bezier.node_count() < 4) {
		const auto& controlPoint = controlPoints[controlPoints.size() - 1];
		bezier.add_way_point(Vector(controlPoint.getX(), controlPoint.getY(), 0.0));
	}

	//
	auto previousX = static_cast<int>(Math::round(bezier.node(0).x));
	auto previousY = static_cast<int>(Math::round(bezier.node(0).y));
	for (auto i = 1; i < bezier.node_count(); ++i) {
		auto x = static_cast<int>(Math::round(bezier.node(i).x));
		auto y = static_cast<int>(Math::round(bezier.node(i).y));

		drawLine(previousX, previousY, x, y, red, green, blue, alpha);

		//
		previousX = x;
		previousY = y;
	}
}

void GUIColorTextureCanvas::debugBezier(const vector<Vector2>& controlPoints, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	if (controlPoints.empty() == true) {
		Console::printLine("GUIColorTextureCanvas::debugBezier(): no control points given");
		return;
	}

	//
	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();
	auto buffer = texture->getTextureData()->getBuffer();

	//
	auto previousX = static_cast<int>(Math::round(controlPoints[0].getX()));
	auto previousY = static_cast<int>(Math::round(controlPoints[0].getY()));
	for (auto i = 1; i < controlPoints.size(); ++i) {
		auto x = static_cast<int>(Math::round(controlPoints[i].getX()));
		auto y = static_cast<int>(Math::round(controlPoints[i].getY()));

		drawLine(previousX, previousY, x, y, red, green, blue, alpha);

		//
		previousX = x;
		previousY = y;
	}
}
