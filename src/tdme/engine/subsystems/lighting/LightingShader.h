#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::map;
using std::string;

using tdme::engine::Engine;
using tdme::engine::subsystems::lighting::LightingShaderImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Interface to lighting shader program
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::lighting::LightingShader final
{
private:
	map<string, LightingShaderImplementation*> shader;
	LightingShaderImplementation* implementation { nullptr };
	bool running { false };
	Engine* engine { nullptr };

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
	 * @param engine engine
	 */
	void useProgram(Engine* engine);

	/** 
	 * Unuse lighting program
	 */
	void unUseProgram();

	/** 
	 * Update effect to program
	 * @param renderer renderer
	 */
	void updateEffect(GLRenderer* renderer);

	/** 
	 * Update material to program
	 * @param renderer gl3 renderer
	 */
	void updateMaterial(GLRenderer* renderer);

	/** 
	 * Update light to program
	 * @param renderer renderer
	 * @param lightId light id
	 */
	void updateLight(GLRenderer* renderer, int32_t lightId);

	/** 
	 * Update matrices to program
	 * @param renderer renderer
	 */
	void updateMatrices(GLRenderer* renderer);

	/** 
	 * Update texture matrix to program
	 * @param renderer renderer
	 */
	void updateTextureMatrix(GLRenderer* renderer);

	/**
	 * Set shader
	 * @param id id
	 */
	void setShader(const string& id);

	/**
	 * Bind texture
	 * @param renderer renderer
	 * @param textureId texture id
	 */
	void bindTexture(GLRenderer* renderer, int32_t textureId);

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	LightingShader(GLRenderer* renderer);

	/**
	 * Destructor
	 */
	~LightingShader();
};
