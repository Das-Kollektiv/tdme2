#include <tdme/engine/subsystems/rendering/Object3DBase_TransformedFacesIterator.h>

#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/subsystems/rendering/Object3DBase.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::rendering::Object3DBase_TransformedFacesIterator;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::subsystems::rendering::Object3DBase;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Object3DBase_TransformedFacesIterator::Object3DBase_TransformedFacesIterator(Object3DBase* object3DBase)
{
	this->object3DBase = object3DBase;
	reset();
}

void Object3DBase_TransformedFacesIterator::reset()
{
	faceCount = 0;
	for (auto object3DGroup : object3DBase->object3dGroups) {
		for (auto& facesEntity : object3DGroup->group->getFacesEntities()) {
			faceCount += facesEntity.getFaces().size();
		}
	}
	faceIdx = 0;
	faceIdxTotal = 0;
	object3DGroupIdx = 0;
	facesEntityIdx = 0;
	auto object3DGroup = object3DBase->object3dGroups[object3DGroupIdx];
	if (object3DGroup->mesh->skinning == true) {
		matrix.identity();
	} else {
		matrix.set(*object3DGroup->groupTransformationsMatrix);
	}
	matrix.multiply(object3DBase->getTransformationsMatrix());
	group = object3DGroup->group;
}

Object3DBase_TransformedFacesIterator* Object3DBase_TransformedFacesIterator::iterator() {
	reset();
	return this;
}

const array<Vector3, 3>& Object3DBase_TransformedFacesIterator::next()
{
	auto object3DGroup = object3DBase->object3dGroups[object3DGroupIdx];
	auto& facesEntities = object3DGroup->group->getFacesEntities();
	auto& facesEntity = facesEntities[facesEntityIdx];
	auto& faces = facesEntity.getFaces();
	auto& face = faces[faceIdx];
	// compute vertices
	auto& faceVertexIndices = face.getVertexIndices();
	auto groupVerticesTransformed = object3DGroup->mesh->vertices;
	matrix.multiply((*groupVerticesTransformed)[faceVertexIndices[0]], vertices[0]);
	matrix.multiply((*groupVerticesTransformed)[faceVertexIndices[1]], vertices[1]);
	matrix.multiply((*groupVerticesTransformed)[faceVertexIndices[2]], vertices[2]);
	// set up current group
	group = object3DGroup->group;
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
				object3DGroupIdx++;
				object3DGroup = object3DBase->object3dGroups[object3DGroupIdx];
				if (object3DGroup->mesh->skinning == true) {
					matrix.identity();
				} else {
					matrix.set(*object3DGroup->groupTransformationsMatrix);
				}
				matrix.multiply(object3DBase->getTransformationsMatrix());
			}
		}
	}
	//
	return vertices;
}

