#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/object/TransparentRenderFacesGroup.h>
#include "Object3DVBORenderer_TransparentRenderFacesGroupPool.h"

using tdme::engine::subsystems::object::Object3DVBORenderer_TransparentRenderFacesGroupPool;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::object::TransparentRenderFacesGroup;

Object3DVBORenderer_TransparentRenderFacesGroupPool::Object3DVBORenderer_TransparentRenderFacesGroupPool()
{
}

TransparentRenderFacesGroup* Object3DVBORenderer_TransparentRenderFacesGroupPool::instantiate()
{
	return new TransparentRenderFacesGroup();
}
