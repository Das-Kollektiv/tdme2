#include <tdme/engine/subsystems/renderer/SingleThreadedRenderer.h>

#include <tdme/tdme.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/Time.h>

using tdme::engine::subsystems::renderer::SingleThreadedRenderer;

using tdme::engine::EntityShaderParameters;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::utilities::Time;

SingleThreadedRenderer::SingleThreadedRenderer(): Renderer()
{
}

SingleThreadedRenderer::~SingleThreadedRenderer() {
}

const Renderer::Renderer_Statistics SingleThreadedRenderer::getStatistics() {
	auto stats = statistics;
	statistics.time = Time::getCurrentMillis();
	statistics.memoryUsageGPU = -1LL;
	statistics.memoryUsageShared = -1LL;
	statistics.clearCalls = 0;
	statistics.renderCalls = 0;
	statistics.instances = 0;
	statistics.computeCalls = 0;
	statistics.triangles = 0;
	statistics.points = 0;
	statistics.linePoints = 0;
	statistics.bufferUploads = 0;
	statistics.textureUploads = 0;
	statistics.renderPasses = 0;
	statistics.drawCommands = 0;
	statistics.submits = 0;
	statistics.disposedTextures = 0;
	statistics.disposedBuffers = 0;
	return stats;
}
