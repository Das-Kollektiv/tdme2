#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>

using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * GUI shader
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::renderer::GUIShader final
{

private:
	GLRenderer* renderer {  };
	int32_t vertexShaderId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t programId { -1 };
	int32_t uniformDiffuseTextureUnit { -1 };
	int32_t uniformDiffuseTextureAvailable { -1 };
	int32_t uniformEffectColorMul { -1 };
	int32_t uniformEffectColorAdd { -1 };
	int32_t uniformTextureMatrix { -1 };
	bool initialized {  };
	bool isRunning {  };

public:

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
	 * @param renderer renderer
	 * @param textureId texture id
	 */
	void bindTexture(GLRenderer* renderer, int32_t textureId);

	/** 
	 * Update effect to program
	 * @param renderer renderer
	 */
	void updateEffect(GLRenderer* renderer);

	/**
	 * Update texure matrix to program
	 * @param renderer renderer
	 */
	void updateTextureMatrix(GLRenderer* renderer);

	/**
	 * Public constructor
	 */
	GUIShader(GLRenderer* renderer);
};
