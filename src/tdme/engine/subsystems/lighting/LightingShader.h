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
using tdme::engine::subsystems::renderer::Renderer;

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
	 * @param context context
	 */
	void unUseProgram(void* context);

	/** 
	 * Update effect to program
	 * @param renderer renderer
	 * @param context context
	 */
	void updateEffect(Renderer* renderer, void* context);

	/** 
	 * Update material to program
	 * @param renderer renderer
	 * @param context context
	 */
	void updateMaterial(Renderer* renderer, void* context);

	/** 
	 * Update light to program
	 * @param renderer renderer
	 * @param context context
	 * @param lightId light id
	 */
	void updateLight(Renderer* renderer, void* context, int32_t lightId);

	/** 
	 * Update matrices to program
	 * @param renderer renderer
	 * @param context context
	 */
	void updateMatrices(Renderer* renderer, void* context);

	/** 
	 * Update texture matrix to program
	 * @param renderer renderer
	 * @param context context
	 */
	void updateTextureMatrix(Renderer* renderer, void* context);

	/**
	 * Set shader
	 * @param context context
	 * @param id id
	 */
	void setShader(void* context, const string& id);

	/**
	 * Bind texture
	 * @param renderer renderer
	 * @param context context
	 * @param textureId texture id
	 */
	void bindTexture(Renderer* renderer, void* context, int32_t textureId);

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	LightingShader(Renderer* renderer);

	/**
	 * Destructor
	 */
	~LightingShader();
};
