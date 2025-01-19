#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;

/**
 * Post processing shader base implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderBaseImplementation: public PostProcessingShaderImplementation
{
protected:
	int32_t programId { -1 };

	int32_t vertexShaderId { -1 };
	int32_t fragmentShaderId { -1 };

	int32_t uniformColorBufferTextureUnit { -1 };
	int32_t uniformDepthBufferTextureUnit { -1 };
	int32_t uniformTemporaryColorBufferTextureUnit { -1 };
	int32_t uniformTemporaryDepthBufferTextureUnit { -1 };
	int32_t uniformBufferTexturePixelWidth { -1 };
	int32_t uniformBufferTexturePixelHeight { -1 };

	bool isRunning { false };
	bool initialized { false };
	RendererBackend* rendererBackend { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(PostProcessingShaderBaseImplementation)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	PostProcessingShaderBaseImplementation(RendererBackend* rendererBackend);

	// overridden methods
	virtual bool isInitialized() override;
	virtual void initialize() override;
	virtual void useProgram(int contextIdx) override;
	virtual void unUseProgram() override;
	virtual void setBufferPixelWidth(int contextIdx, float pixelWidth) override;
	virtual void setBufferPixelHeight(int contextIdx, float pixelHeight) override;
	virtual void setShaderParameters(int contextIdx, Engine* engine) override = 0;
	virtual void unloadTextures();
	virtual void loadTextures(const string& pathName);

};
