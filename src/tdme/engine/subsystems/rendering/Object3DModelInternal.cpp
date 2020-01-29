#include <tdme/engine/subsystems/rendering/Object3DModelInternal.h>

using tdme::engine::subsystems::rendering::Object3DModelInternal;

Object3DModelInternal::Object3DModelInternal(Model* model) :
	Object3DBase(model, false, Engine::AnimationProcessingTarget::CPU_NORENDERING, 1)
{
}

Object3DModelInternal::~Object3DModelInternal() {
	dispose();
}

