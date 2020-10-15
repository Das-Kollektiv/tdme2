#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::array;

/**
 * Renderer PBR material data entity
 */
struct tdme::engine::subsystems::renderer::Renderer_PBRMaterial
{
	array<float, 4> baseColorFactor {{ 1.0f, 1.0f, 1.0f, 1.0f }};
	float metallicFactor { 1.0f };
	float roughnessFactor { 1.0f };
	float normalScale { 1.0f };
	float exposure { 1.0f };
	int baseColorTextureMaskedTransparency { 0 };
	float baseColorTextureMaskedTransparencyThreshold { 0.0f };
};
