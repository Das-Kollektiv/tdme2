#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/DeferredLightingShaderTerrainImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::string;

using tdme::engine::subsystems::lighting::DeferredLightingShaderTerrainEditorImplementation;

using tdme::engine::subsystems::renderer::Renderer;

/**
 * Lighting shader implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::lighting::DeferredLightingShaderTerrainEditorImplementation: public DeferredLightingShaderTerrainImplementation
{
public:
	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	DeferredLightingShaderTerrainEditorImplementation(Renderer* renderer);

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void registerShader() override;
	virtual void useProgram(Engine* engine, void* context) override;

private:
	int32_t uniformBrushEnabled { -1 };
	int32_t uniformBrushTextureUnit { -1 };
	int32_t uniformBrushTextureMatrix { -1 };
	int32_t uniformBrushPosition { -1 };
	int32_t uniformBrushTextureDimension { -1 };

};
