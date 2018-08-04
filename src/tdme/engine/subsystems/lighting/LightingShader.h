#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::map;
using std::string;

using tdme::engine::subsystems::lighting::LightingShaderImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Interface to gl3 lighting shader program
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::lighting::LightingShader final
{
private:
	map<string, LightingShaderImplementation*> shader;
	LightingShaderImplementation* implementation { nullptr };
	bool running { false };

public:
	/** 
	 * @return initialized and ready to be used
	 */
	bool isInitialized();

	/** 
	 * Initialize renderer
	 */
	void initialize();

	/** 
	 * Use lighting program
	 */
	void useProgram();

	/** 
	 * Unuse lighting program
	 */
	void unUseProgram();

	/** 
	 * Update effect to program
	 * @param renderer
	 */
	void updateEffect(GLRenderer* renderer);

	/** 
	 * Update material to program
	 * @param gl3 renderer
	 */
	void updateMaterial(GLRenderer* renderer);

	/** 
	 * Update light to program
	 * @param renderer
	 * @param light id
	 */
	void updateLight(GLRenderer* renderer, int32_t lightId);

	/** 
	 * Update matrices to program
	 * @param renderer
	 */
	void updateMatrices(GLRenderer* renderer);

	/** 
	 * Update texture matrix to program
	 * @param renderer
	 */
	void updateTextureMatrix(GLRenderer* renderer);

	/**
	 * Set shader
	 * @param id
	 */
	void setShader(const string& id);

	/**
	 * Bind texture
	 * @param renderer
	 * @param texture id
	 */
	void bindTexture(GLRenderer* renderer, int32_t textureId);

	/**
	 * Public constructor
	 * @param renderer
	 */
	LightingShader(GLRenderer* renderer);

	/**
	 * Destructor
	 */
	~LightingShader();
};
