// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DBase.java
#include <tdme/engine/subsystems/object/Object3DBase_TransformedFacesIterator.h>

#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/subsystems/object/Object3DBase.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::engine::subsystems::object::Object3DBase_TransformedFacesIterator;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::subsystems::object::Object3DBase;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Face, ::java::lang::ObjectArray > FaceArray;
typedef ::SubArray< ::tdme::engine::model::FacesEntity, ::java::lang::ObjectArray > FacesEntityArray;
}  // namespace model

namespace subsystems {
namespace object {
typedef ::SubArray< ::tdme::engine::subsystems::object::Object3DGroup, ::java::lang::ObjectArray > Object3DGroupArray;
}  // namespace object
}  // namespace subsystems
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

Object3DBase_TransformedFacesIterator::Object3DBase_TransformedFacesIterator(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Object3DBase_TransformedFacesIterator::Object3DBase_TransformedFacesIterator(Object3DBase* object3DBase) 
	: Object3DBase_TransformedFacesIterator(*static_cast< ::default_init_tag* >(0))
{
	ctor(object3DBase);
}

void Object3DBase_TransformedFacesIterator::ctor(Object3DBase* object3DBase)
{
	super::ctor();
	this->object3DBase = object3DBase;
	this->vertices = new Vector3Array(3);
	this->vertices->set(0, new Vector3());
	this->vertices->set(1, new Vector3());
	this->vertices->set(2, new Vector3());
	this->matrix = new Matrix4x4();
	reset();
}

void Object3DBase_TransformedFacesIterator::reset()
{
	faceCount = 0;
	for (auto object3DGroup : *object3DBase->object3dGroups) {
		for (auto facesEntity : *object3DGroup->group->getFacesEntities()) {
			faceCount += facesEntity->getFaces()->length;
		}
	}
	faceIdx = 0;
	faceIdxTotal = 0;
	object3DGroupIdx = 0;
	facesEntityIdx = 0;
	auto object3DGroup = (*object3DBase->object3dGroups)[object3DGroupIdx];
	matrix = (object3DGroup->mesh->skinning == true ? matrix->identity() : matrix->set(object3DGroup->groupTransformationsMatrix))->multiply(object3DBase->transformationsMatrix);
}

Iterator* Object3DBase_TransformedFacesIterator::iterator()
{
	reset();
	return this;
}

bool Object3DBase_TransformedFacesIterator::hasNext()
{
	return faceIdxTotal < faceCount;
}

Vector3Array* Object3DBase_TransformedFacesIterator::next()
{
	auto object3DGroup = (*object3DBase->object3dGroups)[object3DGroupIdx];
	auto facesEntities = object3DGroup->group->getFacesEntities();
	auto facesEntity = (*facesEntities)[facesEntityIdx];
	auto faces = facesEntity->getFaces();
	auto face = (*faces)[faceIdx];
	auto faceVertexIndices = face->getVertexIndices();
	auto groupVerticesTransformed = object3DGroup->mesh->vertices;
	matrix->multiply((*groupVerticesTransformed)[(*faceVertexIndices)[0]], (*vertices)[0]);
	matrix->multiply((*groupVerticesTransformed)[(*faceVertexIndices)[1]], (*vertices)[1]);
	matrix->multiply((*groupVerticesTransformed)[(*faceVertexIndices)[2]], (*vertices)[2]);
	faceIdxTotal++;
	faceIdx++;
	if (faceIdxTotal < faceCount) {
		if (faceIdx == faces->length) {
			faceIdx = 0;
			facesEntityIdx++;
			if (facesEntityIdx == facesEntities->length) {
				facesEntityIdx = 0;
				object3DGroupIdx++;
				object3DGroup = (*object3DBase->object3dGroups)[object3DGroupIdx];
				matrix = (object3DGroup->mesh->skinning == true ? matrix->identity() : matrix->set(object3DGroup->groupTransformationsMatrix))->multiply(object3DBase->transformationsMatrix);
			}
		}
	}
	return vertices;
}

void Object3DBase_TransformedFacesIterator::remove()
{
	// TODO: throw exception here maybe
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3DBase_TransformedFacesIterator::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.Object3DBase.TransformedFacesIterator", 67);
    return c;
}

java::lang::Class* Object3DBase_TransformedFacesIterator::getClass0()
{
	return class_();
}

