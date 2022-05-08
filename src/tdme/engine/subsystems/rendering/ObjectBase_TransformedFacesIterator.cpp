#include <tdme/engine/subsystems/rendering/ObjectBase_TransformedFacesIterator.h>

#include <tdme/tdme.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/subsystems/rendering/ObjectBase.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Node;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectBase_TransformedFacesIterator;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

ObjectBase_TransformedFacesIterator::ObjectBase_TransformedFacesIterator(ObjectBase* objectBase)
{
	this->objectBase = objectBase;
	reset();
}

void ObjectBase_TransformedFacesIterator::reset()
{
	faceCount = 0;
	for (auto objectNode : objectBase->objectNodes) {
		for (auto& facesEntity : objectNode->node->getFacesEntities()) {
			faceCount += facesEntity.getFaces().size();
		}
	}
	faceIdx = 0;
	faceIdxTotal = 0;
	objectNodeIdx = 0;
	facesEntityIdx = 0;
	auto objectNode = objectBase->objectNodes[objectNodeIdx];
	if (objectNode->mesh->skinning == true) {
		matrix.identity();
	} else {
		matrix.set(*objectNode->nodeTransformMatrix);
	}
	matrix.multiply(objectBase->getTransformMatrix());
	node = objectNode->node;
}

ObjectBase_TransformedFacesIterator* ObjectBase_TransformedFacesIterator::iterator() {
	reset();
	return this;
}

const array<Vector3, 3>& ObjectBase_TransformedFacesIterator::next()
{
	auto objectNode = objectBase->objectNodes[objectNodeIdx];
	auto& facesEntities = objectNode->node->getFacesEntities();
	auto& facesEntity = facesEntities[facesEntityIdx];
	auto& faces = facesEntity.getFaces();
	auto& face = faces[faceIdx];
	// compute vertices
	auto& faceVertexIndices = face.getVertexIndices();
	auto nodeVerticesTransformed = objectNode->mesh->vertices;
	vertices[0] = matrix.multiply((*nodeVerticesTransformed)[faceVertexIndices[0]]);
	vertices[1] = matrix.multiply((*nodeVerticesTransformed)[faceVertexIndices[1]]);
	vertices[2] = matrix.multiply((*nodeVerticesTransformed)[faceVertexIndices[2]]);
	// set up current node
	node = objectNode->node;
	// increment to next face
	faceIdxTotal++;
	faceIdx++;
	// check if idxes over flow, if not yet finished
	if (faceIdxTotal < faceCount) {
		if (faceIdx == faces.size()) {
			faceIdx = 0;
			facesEntityIdx++;
			if (facesEntityIdx == facesEntities.size()) {
				facesEntityIdx = 0;
				objectNodeIdx++;
				objectNode = objectBase->objectNodes[objectNodeIdx];
				if (objectNode->mesh->skinning == true) {
					matrix.identity();
				} else {
					matrix.set(*objectNode->nodeTransformMatrix);
				}
				matrix.multiply(objectBase->getTransformMatrix());
			}
		}
	}
	//
	return vertices;
}

