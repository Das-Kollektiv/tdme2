
#pragma once

#include <tdme.h>
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
public:

	/** 
	 * @return field of view Y
	 */
	float getFovY();

	/** 
	 * Set field of view Y
	 * @param field of view y
	 */
	void setFovY(float fovY);

	/** 
	 * @return float
	 */
	float getZNear();

	/** 
	 * @param zNear
	 */
	void setZNear(float zNear);

	/** 
	 * @return float
	 */
	float getZFar();

	/** 
	 * @param zFar
	 */
	void setZFar(float zFar);

	/** 
	 * @return up vector
	 */
	Vector3& getUpVector();

	/** 
	 * @return look from vector
	 */
	Vector3& getLookFrom();

	/** 
	 * @return look at vector
	 */
	Vector3& getLookAt();

	/** 
	 * @return frustum
	 */
	Frustum* getFrustum();

	/** 
	 * Computes the up vector for given look from and look at vectors
	 * @param look from
	 * @param look at
	 * @param up vector
	 */
	void computeUpVector(const Vector3& lookFrom, const Vector3& lookAt, Vector3& upVector);

private:

	/** 
	 * Computes the projection matrix
	 * based on: http://www.songho.ca/opengl/gl_transform.html
	 * @param y field of view
	 * @param aspect
	 * @param z near
	 * @param z far
	 * @return projection matrix
	 */
	Matrix4x4& computeProjectionMatrix(float yfieldOfView, float aspect, float zNear, float zFar);

	/** 
	 * Computes frustum matrix
	 * based on: http://www.songho.ca/opengl/gl_transform.html
	 * @param left
	 * @param right
	 * @param top
	 * @param bottom
	 * @param near
	 * @param far
	 * @return frustum matrix
	 */
	Matrix4x4& computeFrustumMatrix(float left, float right, float bottom, float top, float near, float far);

	/** 
	 * Computes projection matrix for given look from, look at and up vector
	 * @param look from
	 * @param look at
	 * @param up vector
	 * @return model view matrix
	 */
	Matrix4x4& computeModelViewMatrix(const Vector3& lookFrom, const Vector3& lookAt, const Vector3& upVector);

public:

	/** 
	 * Sets up camera while resizing the view port
	 * @param gl
	 * @param width
	 * @param height
	 */
	void update(int32_t width, int32_t height);

	/**
	 * Public constructor
	 * @param renderer
	 */
	Camera(GLRenderer* renderer);

	/**
	 * Destructor
	 */
	~Camera();
};
