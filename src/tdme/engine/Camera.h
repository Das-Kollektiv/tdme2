#pragma once

#include <memory>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Frustum.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::unique_ptr;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Frustum;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Camera
 * @author Andreas Drewke
 */
class tdme::engine::Camera final
{
public:
	enum FrustumMode { FRUSTUMMODE_PERSPECTIVE, FRUSTUMMODE_ORTHOGRAPHIC };
	enum CameraMode { CAMERAMODE_LOOKAT, CAMERAMODE_NONE };

private:
	STATIC_DLL_IMPEXT static Vector3 defaultUp;
	RendererBackend* rendererBackend { nullptr };
	int32_t width;
	int32_t height;
	float fovX;
	float zNear;
	float zFar;
	CameraMode cameraMode;
	FrustumMode frustumMode;
	float orthographicFrustumScale;
	Vector3 lookFrom;
	Vector3 lookAt;
	Vector3 upVector;
	Vector3 forwardVector;
	Vector3 sideVector;
	Matrix4x4 projectionMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 mvpMatrix;
	Matrix4x4 mvpInvertedMatrix;
	unique_ptr<Frustum> frustum;

public:
	// forbid class copy
	FORBID_CLASS_COPY(Camera)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	Camera(RendererBackend* rendererBackend);

	/**
	 * Destructor
	 */
	~Camera();

	/**
	 * @returns width
	 */
	inline int getWidth() {
		return width;
	}

	/**
	 * @returns height
	 */
	inline int getHeight() {
		return height;
	}

	/**
	 * @returns camera mode
	 */
	inline CameraMode getCameraMode() const {
		return cameraMode;
	}

	/**
	 * Set camera mode
	 * @param camera mode
	 */
	inline void setCameraMode(CameraMode cameraMode) {
		this->cameraMode = cameraMode;
	}

	/**
	 * @returns frustum mode
	 */
	inline FrustumMode getFrustumMode() const {
		return frustumMode;
	}

	/**
	 * Set frustum mode
	 * @param frustum mode
	 */
	inline void setFrustumMode(FrustumMode frustumMode) {
		this->frustumMode = frustumMode;
	}

	/**
	 * @returns orthographic frustum scale
	 */
	inline float getOrthographicFrustumScale() const {
		return orthographicFrustumScale;
	}

	/**
	 * Set orthographic frustum scale
	 * @param orthographicFrustumScale orthographic frustum scale
	 */
	inline void setOrthographicFrustumScale(float orthographicFrustumScale) {
		this->orthographicFrustumScale = orthographicFrustumScale;
	}

	/**
	 * @returns field of view X
	 */
	inline float getFovX() const {
		return fovX;
	}

	/**
	 * Set field of view X
	 * @param fovX field of view X
	 */
	inline void setFovX(float fovX) {
		this->fovX = fovX;
	}

	/**
	 * @returns float
	 */
	inline float getZNear() const {
		return zNear;
	}

	/**
	 * Set z near
	 * @param zNear zNear
	 */
	inline void setZNear(float zNear) {
		this->zNear = zNear;
	}

	/**
	 * @returns float
	 */
	inline float getZFar() const {
		return zFar;
	}

	/**
	 * Set z far
	 * @param zFar zFar
	 */
	inline void setZFar(float zFar) {
		this->zFar = zFar;
	}

	/**
	 * @returns up vector
	 */
	inline const Vector3& getUpVector() const {
		return upVector;
	}

	/**
	 * Set up vector
	 * @param upVector up vector
	 */
	inline void setUpVector(const Vector3& upVector) {
		this->upVector = upVector;
	}

	/**
	 * @returns forward vector
	 */
	inline const Vector3& getForwardVector() const {
		return forwardVector;
	}

	/**
	 * Set forward vector
	 * @param forwardVector forward vector
	 */
	inline void setForwardVector(const Vector3& forwardVector) {
		this->forwardVector = forwardVector;
	}

	/**
	 * @returns side vector
	 */
	inline const Vector3& getSideVector() const {
		return sideVector;
	}

	/**
	 * Set side vector
	 * @param sideVector side vector
	 */
	inline void setSideVector(const Vector3& sideVector) {
		this->sideVector = sideVector;
	}

	/**
	 * @returns look from vector
	 */
	inline const Vector3& getLookFrom() const {
		return lookFrom;
	}

	/**
	 * Set look from
	 * @param lookFrom look from
	 */
	inline void setLookFrom(const Vector3& lookFrom) {
		this->lookFrom = lookFrom;
	}

	/**
	 * @returns look at vector
	 */
	inline const Vector3& getLookAt() const {
		return lookAt;
	}

	/**
	 * Set look at
	 * @param lookAt look at
	 */
	inline void setLookAt(const Vector3& lookAt) {
		this->lookAt = lookAt;
	}

	/**
	 * @returns camera matrix
	 */
	inline const Matrix4x4& getCameraMatrix() const {
		return cameraMatrix;
	}

	/**
	 * @returns projection matrix
	 */
	inline const Matrix4x4& getProjectionMatrix() const {
		return projectionMatrix;
	}

	/**
	 * @returns model view projection matrix
	 */
	inline const Matrix4x4& getModelViewProjectionMatrix() const {
		return mvpMatrix;
	}

	/**
	 * @returns inverted model view porjection matrix
	 */
	inline const Matrix4x4& getModelViewProjectionInvertedMatrix() const {
		return mvpInvertedMatrix;
	}

	/**
	 * @returns frustum
	 */
	inline Frustum* getFrustum() {
		return frustum.get();
	}

	/**
	 * Computes the up vector for given look from and look at vectors
	 * @param lookFrom look from
	 * @param lookAt look at
	 * @returns up vector
	 */
	static Vector3 computeUpVector(const Vector3& lookFrom, const Vector3& lookAt);

	/**
	 * Sets up camera while resizing the view port
	 * @param contextIdx context index
	 * @param width width
	 * @param height height
	 */
	void update(int contextIdx, int32_t width, int32_t height);

private:

	/**
	 * Computes the projection matrix
	 * @returns projection matrix
	 */
	Matrix4x4& computeProjectionMatrix();

	/**
	 * Computes projection matrix for given look from, look at and up vector
	 * @returns model view matrix
	 */
	Matrix4x4& computeModelViewMatrix();

};
