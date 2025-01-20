#include <tdme/engine/subsystems/rendering/ObjectModelInternal.h>

using tdme::engine::subsystems::rendering::ObjectModelInternal;

ObjectModelInternal::ObjectModelInternal(Model* model) :
	ObjectBase(model, false, Engine::AnimationProcessingTarget::CPU_NORENDERING, 1)
{
}

ObjectModelInternal::~ObjectModelInternal() {
	dispose();
}

