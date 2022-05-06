#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/subsystems/rendering/ObjectBase.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::array;

using tdme::engine::model::Node;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Transformed faces iterator
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::ObjectBase_TransformedFacesIterator
{
private:
	ObjectBase* objectBase { nullptr };
	Node* node { nullptr };
	array<Vector3, 3> vertices;
	Matrix4x4 matrix;
	int32_t faceCount;
	int32_t faceIdxTotal;
	int32_t faceIdx;
	int32_t objectNodeIdx;
	int32_t facesEntityIdx;

private:

	/**
	 * Reset
	 */
	void reset();
public:
	/**
	 * Public constructor
	 */
	ObjectBase_TransformedFacesIterator(ObjectBase* objectBase);

	/**
	 * Return iterator ready to iterate
	 */
	ObjectBase_TransformedFacesIterator* iterator();

	/**
	 * Has next
	 */
	inline bool hasNext() {
		return faceIdxTotal < faceCount;
	}

	/**
	 * Retrieve next triangle
	 * @return next 3 triangle vectors
	 */
	const array<Vector3, 3>& next();

	/**
	 * @return current node
	 */
	inline Node* getNode() {
		return node;
	}

};
