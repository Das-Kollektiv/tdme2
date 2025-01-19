#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/Entity.h>

using std::string;

using tdme::engine::Entity;
using tdme::engine::Object;

/**
 * Entity rendererBackend parameters
 * @author Andreas Drewke
 */
struct tdme::engine::subsystems::rendering::EntityRenderer_InstancedRenderFunctionParameters final {
	Entity::RenderPass renderPass;
	vector<Object*> objects;
	uint32_t renderTypes;
	bool collectTransparentFaces;
};
