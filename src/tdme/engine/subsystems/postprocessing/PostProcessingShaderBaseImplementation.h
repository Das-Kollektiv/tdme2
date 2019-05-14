#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::FrameBuffer;
using tdme::engine::subsystems::renderer::Renderer;

/** 
 * Post processing shader base implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::postprocessing::PostProcessingShaderBaseImplementation: public PostProcessingShaderImplementation
{
protected:
	int32_t programId {  };

	int32_t vertexShaderId {  };
	int32_t fragmentShaderId {  };

	int32_t uniformColorBufferTextureUnit { -1 };
	int32_t uniformDepthBufferTextureUnit { -1 };
	int32_t uniformTemporaryColorBufferTextureUnit { -1 };
	int32_t uniformTemporaryDepthBufferTextureUnit { -1 };
	int32_t uniformBufferTexturePixelWidth { -1 };
	int32_t uniformBufferTexturePixelHeight { -1 };

	bool isRunning {  };
	bool initialized {  };
	Renderer* renderer {  };

public:

	// overridden methods
	virtual bool isInitialized() override;
	virtual void initialize() override;
	virtual void useProgram(void* context) override;
	virtual void unUseProgram() override;
	virtual void setBufferPixelWidth(void* context, float pixelWidth) override;
	virtual void setBufferPixelHeight(void* context, float pixelHeight) override;

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	PostProcessingShaderBaseImplementation(Renderer* renderer);

};
