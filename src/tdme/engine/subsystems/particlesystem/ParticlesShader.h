#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/fwd-tdme.h>

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;
using tdme::utilities::TextureAtlas;

/**
 * Particles shader program
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::particlesystem::ParticlesShader final
{
private:
	static constexpr int ATLASTEXTURE_COUNT { 128 };

	int32_t programId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t vertexShaderId { -1 };
	int32_t uniformMVPMatrix { -1 };
	int32_t uniformViewPortWidth { -1 };
	int32_t uniformViewPortHeight { -1 };
	int32_t uniformProjectionMatrixXx { -1 };
	int32_t uniformProjectionMatrixYy { -1 };
	int32_t uniformTextureAtlasTextureUnit { -1 };
	array<int32_t, ATLASTEXTURE_COUNT> uniformAtlasTextureOrientation;
	array<int32_t, ATLASTEXTURE_COUNT> uniformAtlasTexturePosition;
	array<int32_t, ATLASTEXTURE_COUNT> uniformAtlasTextureDimension;
	int32_t ppsTextureAtlasTextureId { 0 };
	Matrix4x4 mvpMatrix;
	bool isRunning;
	bool initialized;
	Engine* engine { nullptr };
	RendererBackend* rendererBackend { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(ParticlesShader)

	/**
	 * Public constructor
	 * @param engine engine
	 * @param rendererBackend renderer backend
	 */
	ParticlesShader(Engine* engine, RendererBackend* rendererBackend);

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
	 * @param contextIdx context index
	 */
	void updateMatrices(int contextIdx);

	/**
	 * Set texture atlas
	 * @param contextIdx context index
	 * @param textureAtlas texture atlas
	 */
	void setTextureAtlas(int contextIdx, TextureAtlas* textureAtlas);

};
