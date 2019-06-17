#include <tdme/engine/subsystems/rendering/Object3DRenderer.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesGroup.h>
#include "Object3DRenderer_TransparentRenderFacesGroupPool.h"

using tdme::engine::subsystems::rendering::Object3DRenderer_TransparentRenderFacesGroupPool;
using tdme::engine::subsystems::rendering::Object3DRenderer;
using tdme::engine::subsystems::rendering::TransparentRenderFacesGroup;

Object3DRenderer_TransparentRenderFacesGroupPool::Object3DRenderer_TransparentRenderFacesGroupPool()
{
}

TransparentRenderFacesGroup* Object3DRenderer_TransparentRenderFacesGroupPool::instantiate()
{
	return new TransparentRenderFacesGroup();
}
