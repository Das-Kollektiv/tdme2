#pragma once

#if defined(_WIN32) && defined(_MSC_VER)
	#include <windows.h>
#endif

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>

using std::string;

using tdme::engine::Camera;
using tdme::engine::model::Material;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;

/** 
 * Object 3D renderer parameters
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::rendering::Object3DRenderer_InstancedRenderFunctionParameters final {
	string shader;
	uint32_t renderTypes;
	Camera* camera;
	Matrix4x4 cameraMatrix;
	int object3DGroupIdx;
	int faceEntityIdx;
	int faces;
	int faceIdx;
	bool isTextureCoordinatesAvailable;
	Material* material;
	int32_t frontFace;
	Matrix2D3x3 textureMatrix;
	bool collectTransparentFaces;
};
