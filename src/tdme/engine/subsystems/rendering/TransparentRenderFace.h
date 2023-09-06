#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>

using tdme::engine::subsystems::rendering::ObjectNode;

/**
 * Transparent face to be rendered
 * @author Andreas Drewke
 */
struct tdme::engine::subsystems::rendering::TransparentRenderFace final
{
	ObjectNode* objectNode;
	int32_t facesEntityIdx;
	int32_t faceIdx;
	float distanceFromCamera;
};
