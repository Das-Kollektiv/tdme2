#pragma once

#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFace.h>

using tdme::utils::Pool;
using tdme::engine::subsystems::rendering::TransparentRenderFace;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool;

class tdme::engine::subsystems::rendering::TransparentRenderFacesPool_TransparentRenderFacesPool
	: public Pool<TransparentRenderFace*>
{
protected:
	inline TransparentRenderFace* instantiate() override {
		return new TransparentRenderFace();
	}

public:
	TransparentRenderFacesPool_TransparentRenderFacesPool();
};
