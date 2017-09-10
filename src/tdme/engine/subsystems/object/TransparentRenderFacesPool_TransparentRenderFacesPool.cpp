#include <tdme/engine/subsystems/object/TransparentRenderFace.h>
#include <tdme/engine/subsystems/object/TransparentRenderFacesPool.h>
#include <tdme/engine/subsystems/object/TransparentRenderFacesPool_TransparentRenderFacesPool.h>

using tdme::engine::subsystems::object::TransparentRenderFacesPool_TransparentRenderFacesPool;
using tdme::engine::subsystems::object::TransparentRenderFace;
using tdme::engine::subsystems::object::TransparentRenderFacesPool;

TransparentRenderFacesPool_TransparentRenderFacesPool::TransparentRenderFacesPool_TransparentRenderFacesPool()
{
}

TransparentRenderFace* TransparentRenderFacesPool_TransparentRenderFacesPool::instantiate()
{
	return new TransparentRenderFace();
}
