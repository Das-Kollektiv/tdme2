// Generated from /tdme/src/tdme/math/Matrix4x4Negative.java
#include <tdme/math/Matrix4x4Negative.h>

#include <java/lang/System.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::math::Matrix4x4Negative;
using java::lang::System;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Matrix4x4Negative::Matrix4x4Negative(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Matrix4x4Negative::Matrix4x4Negative() 
	: Matrix4x4Negative(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Matrix4x4Negative::ctor()
{
	super::ctor();
	xAxis = new Vector3();
	yAxis = new Vector3();
	zAxis = new Vector3();
	tmpAxis = new Vector3();
}

bool Matrix4x4Negative::isNegative(Matrix4x4* matrix)
{
	auto transformationsMatrixData = matrix->getArray();
	System::arraycopy(transformationsMatrixData, 0, xAxis->getArray(), 0, 3);
	System::arraycopy(transformationsMatrixData, 4, yAxis->getArray(), 0, 3);
	System::arraycopy(transformationsMatrixData, 8, zAxis->getArray(), 0, 3);
	return Vector3::computeDotProduct(Vector3::computeCrossProduct(xAxis, yAxis, tmpAxis), zAxis) < 0.0f;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Matrix4x4Negative::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.math.Matrix4x4Negative", 27);
    return c;
}

java::lang::Class* Matrix4x4Negative::getClass0()
{
	return class_();
}

