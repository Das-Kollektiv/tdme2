#include <tdme/engine/subsystems/renderer/RendererBackend.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/ByteBuffer.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::renderer::RendererBackend;

using tdme::engine::Texture;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::utilities::ByteBuffer;

RendererBackend::RendererBackend()
{
	CONTEXTINDEX_DEFAULT = 0;
	ID_NONE = -1;
	CLEAR_DEPTH_BUFFER_BIT = -1;
	CLEAR_COLOR_BUFFER_BIT = -1;
	CULLFACE_FRONT = -1;
	CULLFACE_BACK = -1;
	TEXTUREUNITS_MAX = -1;
	PROGRAM_GUI = 1;
	PROGRAM_OBJECTS = 2;
	PROGRAM_POINTS = 3;
	PROGRAM_LINES = 4;
	PROGRAM_COMPUTE = 5;
	SHADER_FRAGMENT_SHADER = -1;
	SHADER_VERTEX_SHADER = -1;
	SHADER_COMPUTE_SHADER = -1;
	DEPTHFUNCTION_ALWAYS = -1;
	DEPTHFUNCTION_EQUAL = -1;
	DEPTHFUNCTION_LESSEQUAL = -1;
	DEPTHFUNCTION_GREATEREQUAL = -1;
	FRAMEBUFFER_DEFAULT = -1;
	FRONTFACE_CW = -1;
	FRONTFACE_CCW = -1;
	LIGHTING_NONE = 0;
	CUBEMAPTEXTUREINDEX_NEGATIVE_X = -1;
	CUBEMAPTEXTUREINDEX_POSITIVE_X = -1;
	CUBEMAPTEXTUREINDEX_POSITIVE_Y = -1;
	CUBEMAPTEXTUREINDEX_NEGATIVE_Y = -1;
	CUBEMAPTEXTUREINDEX_POSITIVE_Z = -1;
	CUBEMAPTEXTUREINDEX_NEGATIVE_Z = -1;
	LIGHTING_SPECULAR = 1;
	LIGHTING_PBR = 2;
	UNIFORM_CL_SKINNING_VERTEX_COUNT = -1;
	UNIFORM_CL_SKINNING_MATRIX_COUNT = -1;
	UNIFORM_CL_SKINNING_INSTANCE_COUNT = -1;
	viewPortWidth = 0;
	viewPortHeight = 0;
	TEXTUREUNITS_MAX = 2;
	projectionMatrix.identity();
	cameraMatrix.identity();
	modelViewMatrix.identity();
	viewportMatrix.identity();
	effectPass = 0;
}

RendererBackend::~RendererBackend() {
}
