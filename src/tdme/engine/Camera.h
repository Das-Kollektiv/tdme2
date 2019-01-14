
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Frustum.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::Frustum;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Camera
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Camera final
{
private:
	static Vector3 defaultUp;
	GLRenderer* renderer {  };
	int32_t width {  };
	int32_t height {  };
	float aspect {  };
	float fovY {  };
	float zNear {  };
	float zFar {  };
	Vector3 upVector {  };
	Vector3 lookFrom {  };
	Vector3 lookAt {  };
	Matrix4x4 projectionMatrix {  };
	Matrix4x4 modelViewMatrix {  };
	Frustum* frustum {  };
	float lastZNear {  };
	float lastZFar {  };
	Vector3 lastUpVector {  };
	Vector3 lastLookFrom {  };
	Vector3 lastLookAt {  };
	bool frustumChanged {  };
public:

	/** 
	 * @return field of view Y
	 */
	inline float getFovY() const {
		return fovY;
	}

	/** 
	 * Set field of view Y
	 * @param fovY field of view y
	 */
	inline void setFovY(float fovY) {
		this->fovY = fovY;
	}

	/** 
	 * @return float
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
	 * @return float
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
	 * @return up vector
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
	 * @return look from vector
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
	 * @return look at vector
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
	 * @return frustum
	 */
	inline Frustum* getFrustum() {
		return frustum;
	}

	/** 
	 * Computes the up vector for given look from and look at vectors
	 * @param lookFrom look from
	 * @param lookAt look at
	 * @return up vector
	 */
	static Vector3 computeUpVector(const Vector3& lookFrom, const Vector3& lookAt);

private:

	/** 
	 * Computes the projection matrix
	 * @param yfieldOfView y field of view
	 * @param aspect aspect
	 * @param zNear z near
	 * @param zFar z far
	 * @return projection matrix
	 */
	Matrix4x4& computeProjectionMatrix(float yfieldOfView, float aspect, float zNear, float zFar);

	/** 
	 * Computes frustum matrix
	 * @param left left
	 * @param right right
	 * @param bottom top
	 * @param top bottom
	 * @param near near
	 * @param far far
	 * @return frustum matrix
	 */
	Matrix4x4& computeFrustumMatrix(float left, float right, float bottom, float top, float near, float far);

	/** 
	 * Computes projection matrix for given look from, look at and up vector
	 * @param lookFrom look from
	 * @param lookAt look at
	 * @param upVector up vector
	 * @return model view matrix
	 */
	Matrix4x4& computeModelViewMatrix(const Vector3& lookFrom, const Vector3& lookAt, const Vector3& upVector);

public:

	/** 
	 * Sets up camera while resizing the view port
	 * @param width width
	 * @param height height
	 */
	void update(int32_t width, int32_t height);

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	Camera(GLRenderer* renderer);

	/**
	 * Destructor
	 */
	~Camera();

	/**
	 * @return if frustum has changed
	 */
	inline bool hasFrustumChanged() {
		return frustumChanged;
	}

};
