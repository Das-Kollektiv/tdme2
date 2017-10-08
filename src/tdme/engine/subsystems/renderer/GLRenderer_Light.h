
#pragma once

#include <array>

#include <tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::array;

/** 
 * Bean holding light data
 */
struct tdme::engine::subsystems::renderer::GLRenderer_Light
{
	int32_t enabled { 0 };
	array<float, 4> ambient {{ 0.0f, 0.0f, 0.0f, 1.0f }};
	array<float, 4> diffuse {{ 1.0f, 1.0f, 1.0f, 1.0f }};
	array<float, 4> specular {{ 1.0f, 1.0f, 1.0f, 1.0f }};
	array<float, 4> position {{ 0.0f, 0.0f, 0.0f, 0.0f }};
	array<float, 3> spotDirection {{ 0.0f, 0.0f, -1.0f }};
	float spotExponent { 0.0f };
	float spotCosCutoff {  };
	float constantAttenuation { 1.0f };
	float linearAttenuation { 0.0f };
	float quadraticAttenuation { 0.0f };
};
