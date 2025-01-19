#include <agui/gui/renderer/GUIRendererBackend.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/math/Math.h>
#include <agui/math/Matrix4x4.h>
#include <agui/utilities/ByteBuffer.h>

using std::string;
using std::to_string;

using agui::gui::renderer::GUIRendererBackend;

using agui::gui::textures::GUITexture;
using agui::math::Math;
using agui::math::Matrix4x4;
using agui::utilities::ByteBuffer;

GUIRendererBackend::GUIRendererBackend()
{
	CONTEXTINDEX_DEFAULT = 0;
	ID_NONE = -1;
	CLEAR_DEPTH_BUFFER_BIT = -1;
	CLEAR_COLOR_BUFFER_BIT = -1;
	TEXTUREUNITS_MAX = -1;
	PROGRAM_GUI = 1;
	SHADER_FRAGMENT_SHADER = -1;
	SHADER_VERTEX_SHADER = -1;
	SHADER_COMPUTE_SHADER = -1;
	FRAMEBUFFER_DEFAULT = -1;
	viewPortWidth = 0;
	viewPortHeight = 0;
	TEXTUREUNITS_MAX = 2;
	viewportMatrix.identity();
}

GUIRendererBackend::~GUIRendererBackend() {
}
