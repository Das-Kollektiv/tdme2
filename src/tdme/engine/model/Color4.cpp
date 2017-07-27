// Generated from /tdme/src/tdme/engine/model/Color4.java
#include <tdme/engine/model/Color4.h>

#include <tdme/engine/model/Color4Base.h>

using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;

Color4::Color4() : Color4Base()
{
	Color4Base();
}

Color4::Color4(Color4* color) : Color4Base(static_cast<Color4Base*>(color))
{
}

Color4::Color4(float r, float g, float b, float a) : Color4Base(r,g,b,a)
{
}

Color4::Color4(floatArray* color) : Color4Base(color)
{
}

