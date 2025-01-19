#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/lines/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;

/**
 * Lines shader program
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::lines::LinesShader final
{
private:
	int32_t programId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t vertexShaderId { -1 };
	int32_t uniformMVPMatrix { -1 };
	int32_t uniformDiffuseTextureUnit { -1 };
	int32_t uniformEffectColorMul { -1 };
	int32_t uniformEffectColorAdd { -1 };
	Matrix4x4 mvpMatrix;
	bool isRunning;
	bool initialized;
	Engine* engine { nullptr };
	RendererBackend* rendererBackend { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(LinesShader)

	/**
	 * Public constructor
	 * @param engine engine
	 * @param rendererBackend renderer backend
	 */
	LinesShader(Engine* engine, RendererBackend* rendererBackend);

	/**
	 * @return initialized and ready to be used
	 */
	bool isInitialized();

	/**
	 * Initialize rendererBackend
	 */
	void initialize();

	/**
	 * Use lighting program
	 * @param contextIdx context index
	 */
	void useProgram(int contextIdx);

	/**
	 * Update effect to program
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 */
	void updateEffect(int contextIdx);

	/**
	 * Unuse particles shader program
	 * @param contextIdx context index
	 */
	void unUseProgram(int contextIdx);

	/**
	 * Update matrices to program
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 */
	void updateMatrices(int contextIdx);

	/**
	 * Set parameters
	 * @param contextIdx context index
	 * @param textureId texture id
	 * @param lineWidth line width
	 */
	void setParameters(int contextIdx, int32_t textureId, float lineWidth);

};
