// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderFacesPool.java
#include <tdme/engine/subsystems/object/TransparentRenderFacesPool.h>

#include <java/lang/ArrayStoreException.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/object/TransparentRenderFace.h>
#include <tdme/engine/subsystems/object/TransparentRenderFacesPool_TransparentRenderFacesPool_1.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::engine::subsystems::object::TransparentRenderFacesPool;
using java::lang::ArrayStoreException;
using java::lang::ClassCastException;
using java::lang::Object;
using java::lang::String;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::engine::subsystems::object::TransparentRenderFace;
using tdme::engine::subsystems::object::TransparentRenderFacesPool_TransparentRenderFacesPool_1;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::Pool;
using tdme::utils::_ArrayList;
using tdme::utils::_Console;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Face, ::java::lang::ObjectArray > FaceArray;
typedef ::SubArray< ::tdme::engine::model::FacesEntity, ::java::lang::ObjectArray > FacesEntityArray;
}  // namespace model
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

TransparentRenderFacesPool::TransparentRenderFacesPool(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TransparentRenderFacesPool::TransparentRenderFacesPool() 
	: TransparentRenderFacesPool(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void TransparentRenderFacesPool::init()
{
	transparentRenderFaces = nullptr;
	transparentRenderFacesPool = nullptr;
}

constexpr int32_t TransparentRenderFacesPool::FACES_MAX;

void TransparentRenderFacesPool::ctor()
{
	super::ctor();
	init();
	tmpVector3 = new Vector3();
	transparentRenderFaces = new _ArrayList();
	transparentRenderFacesPool = new TransparentRenderFacesPool_TransparentRenderFacesPool_1(this);
}

void TransparentRenderFacesPool::createTransparentRenderFaces(Matrix4x4* modelViewMatrix, Object3DGroup* object3DGroup, int32_t facesEntityIdx, int32_t faceIdx)
{
	auto facesEntities = object3DGroup->group->getFacesEntities();
	auto facesEntity = (*facesEntities)[facesEntityIdx];
	auto faces = facesEntity->getFaces();
	auto groupTransformedVertices = object3DGroup->mesh->vertices;
	float distanceFromCamera;
	for (auto i = 0; i < faces->length; i++) {
		if (size() >= FACES_MAX) {
			_Console::println(static_cast< Object* >(u"TransparentRenderFacesPool::createTransparentRenderFaces(): Too many transparent render faces"_j));
			break;
		}
		auto faceVertexIndices = (*faces)[i]->getVertexIndices();
		tmpVector3->set(0.0f, 0.0f, 0.0f);
		tmpVector3->add((*groupTransformedVertices)[(*faceVertexIndices)[0]]);
		tmpVector3->add((*groupTransformedVertices)[(*faceVertexIndices)[1]]);
		tmpVector3->add((*groupTransformedVertices)[(*faceVertexIndices)[2]]);
		tmpVector3->scale(1.0f / 3.0f);
		modelViewMatrix->multiply(tmpVector3, tmpVector3);
		distanceFromCamera = -tmpVector3->getZ();
		auto transparentRenderFace = java_cast< TransparentRenderFace* >(transparentRenderFacesPool->allocate());
		transparentRenderFace->object3DGroup = object3DGroup;
		transparentRenderFace->facesEntityIdx = facesEntityIdx;
		transparentRenderFace->faceIdx = faceIdx;
		transparentRenderFace->distanceFromCamera = distanceFromCamera;
		transparentRenderFaces->add(transparentRenderFace);
		faceIdx++;
	}
}

int32_t TransparentRenderFacesPool::size()
{
	return transparentRenderFacesPool->size();
}

void TransparentRenderFacesPool::reset()
{
	transparentRenderFacesPool->reset();
	transparentRenderFaces->clear();
}

_ArrayList* TransparentRenderFacesPool::getTransparentRenderFaces()
{
	return transparentRenderFaces;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TransparentRenderFacesPool::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.TransparentRenderFacesPool", 56);
    return c;
}

java::lang::Class* TransparentRenderFacesPool::getClass0()
{
	return class_();
}

