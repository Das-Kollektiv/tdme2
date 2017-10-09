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
#include <tdme/utils/Console.h>

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
using tdme::utils::Console;

constexpr int32_t TransparentRenderFacesPool::FACES_MAX;

TransparentRenderFacesPool::TransparentRenderFacesPool() 
{
}

int32_t TransparentRenderFacesPool::size()
{
	return transparentRenderFacesPool.size();
}

void TransparentRenderFacesPool::reset()
{
	transparentRenderFacesPool.reset();
	transparentRenderFaces.clear();
}

vector<TransparentRenderFace*>* TransparentRenderFacesPool::getTransparentRenderFaces()
{
	return &transparentRenderFaces;
}

