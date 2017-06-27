// Generated from /tdme/src/tdme/engine/Camera.java
#include <tdme/engine/Camera.h>

#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/Frustum.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::engine::Camera;
using java::lang::Math;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::Frustum;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::MathTools;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Camera::Camera(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Camera::Camera(GLRenderer* renderer) 
	: Camera(*static_cast< ::default_init_tag* >(0))
{
	ctor(renderer);
}

Vector3* Camera::defaultUp;

void Camera::ctor(GLRenderer* renderer)
{
	super::ctor();
	this->renderer = renderer;
	width = 0;
	height = 0;
	aspect = 1;
	fovY = 45.0f;
	zNear = 10.0f;
	zFar = 4000.0f;
	upVector = new Vector3(0.0f, 1.0f, 0.0f);
	lookFrom = new Vector3(0.0f, 50.0f, 400.0f);
	lookAt = new Vector3(0.0f, 50.0f, 0.0f);
	projectionMatrix = new Matrix4x4();
	modelViewMatrix = new Matrix4x4();
	tmpAxesMatrix = new Matrix4x4();
	tmpLookFromInverted = new Vector3();
	tmpForward = new Vector3();
	tmpSide = new Vector3();
	tmpUp = new Vector3();
	frustum = new Frustum(renderer);
}

float Camera::getFovY()
{
	return fovY;
}

void Camera::setFovY(float fovY)
{
	this->fovY = fovY;
}

float Camera::getZNear()
{
	return zNear;
}

void Camera::setZNear(float zNear)
{
	this->zNear = zNear;
}

float Camera::getZFar()
{
	return zFar;
}

void Camera::setZFar(float zFar)
{
	this->zFar = zFar;
}

Vector3* Camera::getUpVector()
{
	return upVector;
}

Vector3* Camera::getLookFrom()
{
	return lookFrom;
}

Vector3* Camera::getLookAt()
{
	return lookAt;
}

Frustum* Camera::getFrustum()
{
	return frustum;
}

void Camera::computeUpVector(Vector3* lookFrom, Vector3* lookAt, Vector3* upVector)
{
	tmpForward->set(lookAt)->sub(lookFrom)->normalize();
	if (Math::abs(tmpForward->getX()) < MathTools::EPSILON && Math::abs(tmpForward->getZ()) < MathTools::EPSILON) {
		upVector->set(0.0f, 0.0f, tmpForward->getY())->normalize();
		return;
	}
	Vector3::computeCrossProduct(tmpForward, defaultUp, tmpSide)->normalize();
	Vector3::computeCrossProduct(tmpSide, tmpForward, upVector)->normalize();
}

Matrix4x4* Camera::computeProjectionMatrix(float yfieldOfView, float aspect, float zNear, float zFar)
{
	auto tangent = static_cast< float >(Math::tan(yfieldOfView / 2.0f * 3.1415927f / 180.0f));
	auto height = zNear * tangent;
	auto width = height * aspect;
	return computeFrustumMatrix(-width, width, -height, height, zNear, zFar);
}

Matrix4x4* Camera::computeFrustumMatrix(float left, float right, float bottom, float top, float near, float far)
{
	return projectionMatrix->set(2.0f * near / (right - left), 0.0f, 0.0f, 0.0f, 0.0f, 2.0f * near / (top - bottom), 0.0f, 0.0f, (right + left) / (right - left), (top + bottom) / (top - bottom), -(far + near) / (far - near), -1.0f, 0.0f, 0.0f, -(2.0f * far * near) / (far - near), 1.0f);
}

Matrix4x4* Camera::computeModelViewMatrix(Vector3* lookFrom, Vector3* lookAt, Vector3* upVector)
{
	tmpForward->set(lookAt)->sub(lookFrom)->normalize();
	Vector3::computeCrossProduct(tmpForward, upVector, tmpSide)->normalize();
	Vector3::computeCrossProduct(tmpSide, tmpForward, tmpUp);
	auto sideXYZ = tmpSide->getArray();
	auto forwardXYZ = tmpForward->getArray();
	auto upXYZ = tmpUp->getArray();
	modelViewMatrix->identity()->translate(tmpLookFromInverted->set(lookFrom)->scale(-1.0f))->multiply(tmpAxesMatrix->set((*sideXYZ)[0], (*upXYZ)[0], -(*forwardXYZ)[0], 0.0f, (*sideXYZ)[1], (*upXYZ)[1], -(*forwardXYZ)[1], 0.0f, (*sideXYZ)[2], (*upXYZ)[2], -(*forwardXYZ)[2], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	return modelViewMatrix;
}

void Camera::update(int32_t width, int32_t height)
{
	if (this->width != width || this->height != height) {
		if (height <= 0)
			height = 1;

		aspect = static_cast< float >(width) / static_cast< float >(height);
		this->width = width;
		this->height = height;
		renderer->getViewportMatrix()->set(width / 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, height / 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0 + (width / 2.0f), 0 + (height / 2.0f), 0.0f, 1.0f);
	} else {
		aspect = static_cast< float >(width) / static_cast< float >(height);
	}
	renderer->getProjectionMatrix()->set(computeProjectionMatrix(fovY, aspect, zNear, zFar));
	renderer->onUpdateProjectionMatrix();
	renderer->getModelViewMatrix()->set(computeModelViewMatrix(lookFrom, lookAt, upVector));
	renderer->onUpdateModelViewMatrix();
	renderer->getCameraMatrix()->set(renderer->getModelViewMatrix());
	renderer->onUpdateCameraMatrix();
	frustum->updateFrustum();
}

String* Camera::toString()
{
	return ::java::lang::StringBuilder().append(u"Camera [width="_j)->append(width)
		->append(u", height="_j)
		->append(height)
		->append(u", aspect="_j)
		->append(aspect)
		->append(u", zNear="_j)
		->append(zNear)
		->append(u", zFar="_j)
		->append(zFar)
		->append(u", upVector="_j)
		->append(static_cast< Object* >(upVector))
		->append(u", lookFrom="_j)
		->append(static_cast< Object* >(lookFrom))
		->append(u", lookAt="_j)
		->append(static_cast< Object* >(lookAt))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Camera::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.Camera", 18);
    return c;
}

void Camera::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		defaultUp = new Vector3(0.0f, 1.0f, 0.0f);
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* Camera::getClass0()
{
	return class_();
}

