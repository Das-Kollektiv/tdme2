#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>

using tdme::engine::subsystems::renderer::RendererBackend;

using std::array;

using tdme::gui::nodes::GUIColor;

/**
 * GUI shader
 * @author Andreas Drewke
 */
class tdme::gui::renderer::GUIShader final
{

private:
	RendererBackend* rendererBackend { nullptr };
	int32_t vertexShaderId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t programId { -1 };
	int32_t uniformDiffuseTextureUnit { -1 };
	int32_t uniformDiffuseTextureAvailable { -1 };
	int32_t uniformMaskTextureUnit { -1 };
	int32_t uniformMaskTextureAvailable { -1 };
	int32_t uniformMaskMaxValue { -1 };
	int32_t uniformEffectColorMul { -1 };
	int32_t uniformEffectColorAdd { -1 };
	int32_t uniformTextureMatrix { -1 };
	int32_t uniformGradientAvailable { -1 };
	array<int32_t, 10> uniformGradientColors { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int32_t uniformGradientColorCount { -1 };
	array<int32_t, 10> uniformGradientColorStarts { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int32_t uniformInverseGradientTextureMatrix { -1 };
	bool initialized;
	bool isRunning;

public:
	// forbid class copy
	FORBID_CLASS_COPY(GUIShader)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	GUIShader(RendererBackend* rendererBackend);

	/**
	 * @return if initialized and ready to use
	 */
	bool isInitialized();

	/**
	 * Init shadow mapping
	 */
	void initialize();

	/**
	 * Use render GUI program
	 */
	void useProgram();

	/**
	 * Un use render GUI program
	 */
	void unUseProgram();

	/**
	 * Bind texture
	 * @param textureId texture id
	 */
	void bindTexture(int32_t textureId);

	/**
	 * Update effect to program
	 */
	void updateEffect();

	/**
	 * Update texure matrix to program
	 */
	void updateTextureMatrix();

	/**
	 * Set gradient properties
	 * @deprecated use rather custom UI shader and parameters
	 * @param count color count
	 * @param colors colors
	 * @param colorStarts color starts
	 * @param rotationAngle rotation angle
	 */
	void setGradient(int count, array<GUIColor, 10>& colors, array<float, 10>& colorStarts, float rotationAngle);

	/**
	 * Disable gradient
	 * @deprecated use rather custom UI shader and parameters
	 */
	void unsetGradient();

};
