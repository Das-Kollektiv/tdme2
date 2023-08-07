#include <tdme/engine/Camera.h>

#include <memory>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Frustum.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::make_unique;
using std::unique_ptr;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Camera;
using tdme::engine::Frustum;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;

Camera::Camera(Renderer* renderer)
{
	this->renderer = renderer;
	width = 0;
	height = 0;
	fovX = 45.0f;
	zNear = 0.1f;
	zFar = 150.0f;
	cameraMode = CAMERAMODE_LOOKAT;
	frustumMode = FRUSTUMMODE_PERSPECTIVE;
	orthographicFrustumScale = 1.0f;
	upVector.set(0.0f, 1.0f, 0.0f);
	forwardVector.set(0.0f, 0.0f, -1.0f);
	sideVector.set(1.0f, 0.0f, 0.0f);
	lookFrom.set(0.0f, 50.0f, 400.0f);
	lookAt.set(0.0f, 50.0f, 0.0f);
	frustum = make_unique<Frustum>(renderer);
}

Camera::~Camera() {
}

Vector3 Camera::defaultUp(0.0f, 1.0f, 0.0f);

Vector3 Camera::computeUpVector(const Vector3& lookFrom, const Vector3& lookAt)
{
	Vector3 tmpForward;
	Vector3 tmpUpVector;
	tmpForward.set(lookAt).sub(lookFrom).normalize();
	if (Math::abs(tmpForward.getX()) < Math::EPSILON && Math::abs(tmpForward.getZ()) < Math::EPSILON) {
		tmpUpVector.set(0.0f, 0.0f, tmpForward.getY()).normalize();
		return tmpUpVector;
	}
	auto tmpSide = Vector3::computeCrossProduct(tmpForward, defaultUp).normalize();
	tmpUpVector = Vector3::computeCrossProduct(tmpSide, tmpForward).normalize();
	return tmpUpVector;
}

Matrix4x4& Camera::computeProjectionMatrix()
{
	// see: see http://www.songho.ca/opengl/gl_transform.html
	switch(frustumMode) {
		case FRUSTUMMODE_ORTHOGRAPHIC:
			{
				auto leftPlane = (-width / 2.0f) * orthographicFrustumScale;
				auto rightPlane = (width / 2.0f) * orthographicFrustumScale;
				auto topPlane = (height / 2.0f) * orthographicFrustumScale;
				auto bottomPlane = (-height / 2.0f) * orthographicFrustumScale;
				auto nearPlane = zNear;
				auto farPlane = zFar;
				return projectionMatrix.set(
					2.0f / (rightPlane - leftPlane),
					0.0f,
					0.0f,
					0.0f,
					0.0f,
					2.0f / (topPlane - bottomPlane),
					0.0f,
					0.0f,
					0.0f,
					0.0f,
					-2.0f / (farPlane - nearPlane),
					0.0f,
					-(rightPlane + leftPlane) / (rightPlane - leftPlane),
					-(topPlane + bottomPlane) / (topPlane - bottomPlane),
					-(farPlane + nearPlane) / (farPlane - nearPlane),
					1.0f
				);
			}
		default:
			{
				// see: https://github.com/g-truc/glm
				auto aspect = static_cast<float>(this->height) / static_cast<float>(this->width);
				auto rad = fovX * 3.1415927f / 180.0f;
				auto _height = Math::cos(0.5f * rad) / Math::sin(0.5 * rad);
				auto _width = _height * aspect;
				return projectionMatrix.set(
					_width,
					0.0f,
					0.0f,
					0.0f,
					0.0f,
					_height,
					0.0f,
					0.0f,
					0.0f,
					0.0f,
					-(zFar + zNear) / (zFar - zNear),
					-1.0f,
					0.0f,
					0.0f,
					-(2.0f * zFar * zNear) / (zFar - zNear),
					1.0f
				);
			}
	}
}

Matrix4x4& Camera::computeModelViewMatrix()
{
	Vector3 tmpUp = upVector;
	if (cameraMode == CAMERAMODE_LOOKAT) {
		forwardVector.set(lookAt).sub(lookFrom).normalize();
		sideVector = Vector3::computeCrossProduct(forwardVector, upVector).normalize();
		tmpUp = Vector3::computeCrossProduct(sideVector, forwardVector);
	}
	cameraMatrix.
		identity().
		translate(
			lookFrom.clone().scale(-1.0f)
		).
		multiply(
			Matrix4x4(
				sideVector[0],
				tmpUp[0],
				-forwardVector[0],
				0.0f,
				sideVector[1],
				tmpUp[1],
				-forwardVector[1],
				0.0f,
				sideVector[2],
				tmpUp[2],
				-forwardVector[2],
				0.0f,
				0.0f,
				0.0f,
				0.0f,
				1.0f
			)
		);
	return cameraMatrix;
}

void Camera::update(int contextIdx, int32_t width, int32_t height)
{
	auto reshaped = false;
	auto _width = width;
	auto _height = height;
	if (this->width != _width || this->height != _height) {
		reshaped = true;
		if (_height <= 0)
			_height = 1;

		this->width = _width;
		this->height = _height;
		renderer->getViewportMatrix().set(
			_width / 2.0f,
			0.0f,
			0.0f,
			0.0f,
			0.0f,
			_height / 2.0f,
			0.0f,
			0.0f,
			0.0f,
			0.0f,
			1.0f,
			0.0f,
			0 + (_width / 2.0f),
			0 + (_height / 2.0f),
			0.0f,
			1.0f
		);
	}

	// setup projection and model view matrices and such
	renderer->getCameraPosition().set(lookFrom);
	renderer->getProjectionMatrix().set(computeProjectionMatrix());
	renderer->onUpdateProjectionMatrix(contextIdx);
	renderer->getModelViewMatrix().set(computeModelViewMatrix());
	renderer->onUpdateModelViewMatrix(contextIdx);
	renderer->getCameraMatrix().set(renderer->getModelViewMatrix());
	renderer->onUpdateCameraMatrix(contextIdx);

	//
	mvpInvertedMatrix.set(cameraMatrix).multiply(projectionMatrix).invert();
	mvpMatrix.set(cameraMatrix).multiply(projectionMatrix);

	// viewport
	renderer->setViewPort(width, height);
	renderer->updateViewPort();
}
