#include <tdme/engine/Camera.h>

#include <tdme/engine/Frustum.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::Camera;
using tdme::math::Math;
using tdme::engine::Frustum;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Camera::Camera(GLRenderer* renderer)
{
	this->renderer = renderer;
	width = 0;
	height = 0;
	aspect = 1;
	fovY = 45.0f;
	zNear = 10.0f;
	zFar = 4000.0f;
	upVector.set(0.0f, 1.0f, 0.0f);
	lookFrom.set(0.0f, 50.0f, 400.0f);
	lookAt.set(0.0f, 50.0f, 0.0f);
	frustum = new Frustum(renderer);
}

Camera::~Camera() {
	delete frustum;
}

Vector3 Camera::defaultUp(0.0f, 1.0f, 0.0f);

Vector3 Camera::computeUpVector(const Vector3& lookFrom, const Vector3& lookAt)
{
	Vector3 tmpForward;
	Vector3 tmpSide;
	Vector3 tmpUpVector;
	tmpForward.set(lookAt).sub(lookFrom).normalize();
	if (Math::abs(tmpForward.getX()) < Math::EPSILON && Math::abs(tmpForward.getZ()) < Math::EPSILON) {
		tmpUpVector.set(0.0f, 0.0f, tmpForward.getY()).normalize();
		return tmpUpVector;
	}
	Vector3::computeCrossProduct(tmpForward, defaultUp, tmpSide).normalize();
	Vector3::computeCrossProduct(tmpSide, tmpForward, tmpUpVector).normalize();
	return tmpUpVector;
}

Matrix4x4& Camera::computeProjectionMatrix(float yfieldOfView, float aspect, float zNear, float zFar)
{
	auto tangent = static_cast< float >(Math::tan(yfieldOfView / 2.0f * 3.1415927f / 180.0f));
	auto height = zNear * tangent;
	auto width = height * aspect;
	return computeFrustumMatrix(-width, width, -height, height, zNear, zFar);
}

Matrix4x4& Camera::computeFrustumMatrix(float left, float right, float bottom, float top, float near, float far)
{
	return projectionMatrix.set(
		2.0f * near / (right - left),
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		2.0f * near / (top - bottom),
		0.0f,
		0.0f,
		(right + left) / (right - left),
		(top + bottom) / (top - bottom),
		-(far + near) / (far - near),
		-1.0f,
		0.0f,
		0.0f,
		-(2.0f * far * near) / (far - near),
		1.0f
	);
}

Matrix4x4& Camera::computeModelViewMatrix(const Vector3& lookFrom, const Vector3& lookAt, const Vector3& upVector)
{
	Matrix4x4 tmpAxesMatrix;
	Vector3 tmpForward;
	Vector3 tmpSide;
	Vector3 tmpUp;
	Vector3 tmpLookFromInverted;
	tmpForward.set(lookAt).sub(lookFrom).normalize();
	Vector3::computeCrossProduct(tmpForward, upVector, tmpSide).normalize();
	Vector3::computeCrossProduct(tmpSide, tmpForward, tmpUp);
	auto& sideXYZ = tmpSide.getArray();
	auto& forwardXYZ = tmpForward.getArray();
	auto& upXYZ = tmpUp.getArray();
	modelViewMatrix.
		identity().
		translate(
			tmpLookFromInverted.set(lookFrom).scale(-1.0f)
		).
		multiply(
			tmpAxesMatrix.set(
				sideXYZ[0],
				upXYZ[0],
				-forwardXYZ[0],
				0.0f,
				sideXYZ[1],
				upXYZ[1],
				-forwardXYZ[1],
				0.0f,
				sideXYZ[2],
				upXYZ[2],
				-forwardXYZ[2],
				0.0f,
				0.0f,
				0.0f,
				0.0f,
				1.0f
			)
		);
	return modelViewMatrix;
}

void Camera::update(int32_t width, int32_t height)
{
	// setup new view port if required
	if (this->width != width || this->height != height) {
		if (height <= 0)
			height = 1;

		aspect = static_cast< float >(width) / static_cast< float >(height);
		this->width = width;
		this->height = height;
		renderer->getViewportMatrix().set(width / 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, height / 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0 + (width / 2.0f), 0 + (height / 2.0f), 0.0f, 1.0f);
	} else {
		aspect = static_cast< float >(width) / static_cast< float >(height);
	}

	// setup projection and model view and such
	renderer->getProjectionMatrix().set(computeProjectionMatrix(fovY, aspect, zNear, zFar));
	renderer->onUpdateProjectionMatrix();
	renderer->getModelViewMatrix().set(computeModelViewMatrix(lookFrom, lookAt, upVector));
	renderer->onUpdateModelViewMatrix();
	renderer->getCameraMatrix().set(renderer->getModelViewMatrix());
	renderer->onUpdateCameraMatrix();

	frustumChanged =
		lastZNear != zNear ||
		lastZFar != zFar ||
		lastUpVector.equals(upVector) == false ||
		lastLookFrom.equals(lookFrom) == false ||
		lastLookAt.equals(lookAt) == false;

	if (frustumChanged == true) {
		// update frustum
		frustum->updateFrustum();
	}

	lastZNear = zNear;
	lastZFar = zFar;
	lastUpVector.set(upVector);
	lastLookFrom.set(lookFrom);
	lastLookAt.set(lookAt);
}


