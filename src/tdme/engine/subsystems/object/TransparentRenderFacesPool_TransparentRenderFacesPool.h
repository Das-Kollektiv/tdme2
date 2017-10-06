
#pragma once

#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/subsystems/object/TransparentRenderFace.h>

using tdme::utils::Pool;
using tdme::engine::subsystems::object::TransparentRenderFace;
using tdme::engine::subsystems::object::TransparentRenderFacesPool;

class tdme::engine::subsystems::object::TransparentRenderFacesPool_TransparentRenderFacesPool
	: public Pool<TransparentRenderFace*>
{
public: /* protected */
	TransparentRenderFace* instantiate() override;

public:
	TransparentRenderFacesPool_TransparentRenderFacesPool();
};
