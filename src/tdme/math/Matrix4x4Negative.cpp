// Generated from /tdme/src/tdme/math/Matrix4x4Negative.java
#include <tdme/math/Matrix4x4Negative.h>

#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::math::Matrix4x4Negative;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Matrix4x4Negative::Matrix4x4Negative() 
{
}

bool Matrix4x4Negative::isNegative(Matrix4x4* matrix)
{
	auto transformationsMatrixData = matrix->getArray();
	xAxis.set((*transformationsMatrixData)[0], (*transformationsMatrixData)[1], (*transformationsMatrixData)[2]);
	yAxis.set((*transformationsMatrixData)[4], (*transformationsMatrixData)[5], (*transformationsMatrixData)[6]);
	zAxis.set((*transformationsMatrixData)[8], (*transformationsMatrixData)[9], (*transformationsMatrixData)[10]);
	return Vector3::computeDotProduct(Vector3::computeCrossProduct(&xAxis, &yAxis, &tmpAxis), &zAxis) < 0.0f;
}

