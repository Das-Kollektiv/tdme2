#pragma once

#include <vector>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/Rotation.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>

using std::vector;
using std::string;
using std::to_string;

using tdme::engine::model::RotationOrder;
using tdme::engine::Rotation;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;

/**
 * Transform which contain scale, rotations and translation
 * @author Andreas Drewke
 */
class tdme::engine::Transform {
private:
	Vector3 translation;
	Vector3 scale;
	Quaternion rotationsQuaternion;
	vector<Rotation> rotations;
	Matrix4x4 transformMatrix;

public:
	/**
	 * Public constructor
	 */
	inline Transform() {
		transformMatrix.identity();
		scale.set(1.0f, 1.0f, 1.0f);
		rotationsQuaternion.identity();
	}

	/**
	 * Destructor
	 */
	virtual inline ~Transform() {
	}

	/**
	 * @return object translation
	 */
	inline const Vector3& getTranslation() const {
		return translation;
	}

	/**
	 * Set translation
	 * @param translation translation
	 */
	inline void setTranslation(const Vector3& translation) {
		this->translation.set(translation);
	}

	/**
	 * @return object scale
	 */
	inline const Vector3& getScale() const {
		return scale;
	}

	/**
	 * Set scale
	 * @param scale scale
	 */
	inline void setScale(const Vector3& scale) {
		this->scale.set(scale);
	}

	/**
	 * @return rotation count
	 */
	inline const int getRotationCount() const {
		return rotations.size();
	}

	/**
	 * Get rotation at given index
	 * @param idx rotation index
	 * @return rotation
	 */
	inline Rotation& getRotation(const int idx) {
		return rotations[idx];
	}

	/**
	 * Add rotation
	 * @param axis axis
	 * @param angle angle
	 */
	inline void addRotation(const Vector3& axis, const float angle) {
		rotations.emplace_back(axis, angle);
	}

	/**
	 * Remove rotation
	 * @param idx index
	 */
	inline void removeRotation(const int idx) {
		rotations.erase(rotations.begin() + idx);
	}

	/**
	 * @param idx rotation index
	 * @return rotation axis for rotation with given index
	 */
	inline const Vector3& getRotationAxis(const int idx) const {
		return rotations[idx].getAxis();
	}

	/**
	 * Set rotation axis
	 * @param idx rotation index
	 * @param axis rotation axis
	 */
	inline void setRotationAxis(const int idx, const Vector3& axis) {
		return rotations[idx].setAxis(axis);
	}

	/**
	 * @param idx rotation index
	 * @return rotation angle for rotation with given index
	 */
	inline const float getRotationAngle(const int idx) const {
		return rotations[idx].getAngle();
	}

	/**
	 * @param idx rotation index
	 * @param angle rotation angle
	 * @return rotation angle for rotation with given index
	 */
	inline void setRotationAngle(const int idx, const float angle) {
		rotations[idx].setAngle(angle);
	}

	/**
	 * @return rotations quaternion
	 */
	inline const Quaternion& getRotationsQuaternion() const {
		return rotationsQuaternion;
	}

	/**
	 * @return this transform matrix
	 */
	inline const Matrix4x4& getTransformMatrix() const {
		return transformMatrix;
	}

	/**
	 * Set transform
	 * @param transform transform
	 */
	inline virtual void setTransform(const Transform& transform) {
		if (this == &transform) return;
		*this = transform;
	}

	/**
	 * Set up this transform from given matrix and rotation order
	 * @param matrix matrix
	 * @param rotationOrder rotation order
	 */
	virtual void fromMatrix(const Matrix4x4& matrix, RotationOrder* rotationOrder);

	/**
	 * Computes transform matrix
	 * @param parentTransform parent transform
	 */
	virtual void update();

	/**
	 * Invert this transform
	 */
	virtual Transform& invert();

	/**
	 * Clones the transform
	 * @return new cloned transform
	 */
	inline Transform clone() const {
		Transform clonedTransform;
		clonedTransform.translation = translation;
		clonedTransform.scale = scale;
		clonedTransform.rotationsQuaternion = rotationsQuaternion;
		clonedTransform.rotations = rotations;
		clonedTransform.transformMatrix = transformMatrix;
		return clonedTransform;

	}

	/**
	 * Multiplies this transform with another transform
	 * @param t transform
	 * @return this transform
	 */
	inline Transform& multiply(const Transform& t) {
		update();
		translation+= rotationsQuaternion * (t.translation * scale);
		scale*= t.scale;
		rotationsQuaternion*= t.rotationsQuaternion;
		auto eulerAngles = rotationsQuaternion.computeEulerAngles();
		rotations.clear();
		rotations.emplace_back(Vector3(0.0f, 0.0f, 1.0f), eulerAngles[2]);
		rotations.emplace_back(Vector3(0.0f, 1.0f, 0.0f), eulerAngles[1]);
		rotations.emplace_back(Vector3(1.0f, 0.0f, 0.0f), eulerAngles[0]);
		update();
		return *this;
	}

	/*
	 * Operator *=
	 * @param t transform to multiply by
	 * @return this transform multiplied by t
	 */
	inline Transform& operator *=(const Transform& t) {
		return this->multiply(t);
	}

	/**
	 * Operator *
	 * @param t transform to multiply by
	 * @return new transform (this * t)
	 */
	inline Transform operator *(const Transform& t) const {
		auto r = this->clone().multiply(t);
		return r;
	}

	/**
	 * Equality comparison operator
	 * @param t transform to compare to
	 * @return equality
	 */

	inline bool operator ==(const Transform& t) const {
		return transformMatrix.equals(t.transformMatrix);
	}

	/**
	 * Non equality comparison operator
	 * @param t transform to compare to
	 * @return non equality
	 */

	inline bool operator !=(const Transform& t) const {
		return transformMatrix.equals(t.transformMatrix);
	}

};
