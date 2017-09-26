#include <tdme/engine/subsystems/object/TransparentRenderFacesPool.h>

#include <vector>
#include <string>

#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/object/TransparentRenderFace.h>
#include <tdme/engine/subsystems/object/TransparentRenderFacesPool_TransparentRenderFacesPool.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/_Console.h>

using std::vector;
using std::wstring;

using tdme::engine::subsystems::object::TransparentRenderFacesPool;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::engine::subsystems::object::TransparentRenderFace;
using tdme::engine::subsystems::object::TransparentRenderFacesPool_TransparentRenderFacesPool;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::Pool;
using tdme::utils::_Console;

constexpr int32_t TransparentRenderFacesPool::FACES_MAX;

TransparentRenderFacesPool::TransparentRenderFacesPool() 
{
	transparentRenderFacesPool = new TransparentRenderFacesPool_TransparentRenderFacesPool();
}

void TransparentRenderFacesPool::createTransparentRenderFaces(Matrix4x4& modelViewMatrix, Object3DGroup* object3DGroup, int32_t facesEntityIdx, int32_t faceIdx)
{
	auto facesEntities = object3DGroup->group->getFacesEntities();
	auto& facesEntity = (*facesEntities)[facesEntityIdx];
	auto faces = facesEntity.getFaces();
	auto groupTransformedVertices = object3DGroup->mesh->vertices;
	float distanceFromCamera;
	Vector3 tmpVector3;
	for (auto i = 0; i < faces->size(); i++) {
		if (size() >= FACES_MAX) {
			_Console::println(wstring(L"TransparentRenderFacesPool::createTransparentRenderFaces(): Too many transparent render faces"));
			break;
		}
		auto faceVertexIndices = (*faces)[i].getVertexIndices();
		tmpVector3.set(0.0f, 0.0f, 0.0f);
		tmpVector3.add(&(*groupTransformedVertices)[(*faceVertexIndices)[0]]);
		tmpVector3.add(&(*groupTransformedVertices)[(*faceVertexIndices)[1]]);
		tmpVector3.add(&(*groupTransformedVertices)[(*faceVertexIndices)[2]]);
		tmpVector3.scale(1.0f / 3.0f);
		modelViewMatrix.multiply(tmpVector3, tmpVector3);
		distanceFromCamera = -tmpVector3.getZ();
		auto transparentRenderFace = transparentRenderFacesPool->allocate();
		transparentRenderFace->object3DGroup = object3DGroup;
		transparentRenderFace->facesEntityIdx = facesEntityIdx;
		transparentRenderFace->faceIdx = faceIdx;
		transparentRenderFace->distanceFromCamera = distanceFromCamera;
		transparentRenderFaces.push_back(transparentRenderFace);
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
	transparentRenderFaces.clear();
}

vector<TransparentRenderFace*>* TransparentRenderFacesPool::getTransparentRenderFaces()
{
	return &transparentRenderFaces;
}

