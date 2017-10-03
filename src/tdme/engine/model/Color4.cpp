#include <tdme/engine/model/Color4.h>

#include <array>

#include <tdme/engine/model/Color4Base.h>

using std::array;

using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;

Color4::Color4() : Color4Base()
{
	Color4Base();
}

Color4::Color4(const Color4& color) : Color4Base(color)
{
}

Color4::Color4(float r, float g, float b, float a) : Color4Base(r,g,b,a)
{
}

Color4::Color4(const array<float, 4>& color) : Color4Base(color)
{
}

