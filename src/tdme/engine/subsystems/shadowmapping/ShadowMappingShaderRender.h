#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderImplementation;
using tdme::math::Matrix4x4;

/** 
 * Shadow mapping shader to render shadow maps
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender final
{
private:
	struct ShadowMappingShaderRenderContext {
		ShadowMappingShaderRenderImplementation* implementation { nullptr };
	};
	map<string, ShadowMappingShaderRenderImplementation*> shader;
	bool running { false };
	Matrix4x4 depthBiasMVPMatrix {  };
	Engine* engine { nullptr };
	Renderer* renderer { nullptr };
	vector<ShadowMappingShaderRenderContext> contexts;
	int32_t lightId { -1 };

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
	 * Use render shadow mapping program
	 * @param engine engine
	 */
	void useProgram(Engine* engine);

	/** 
	 * Un use render shadow mapping program
	 */
	void unUseProgram();

	/** 
	 * Set up program projection and camera matrix
	 */
	void setProgramViewMatrices();

	/**
	 * Set up program model view matrix
	 * @param context context
	 * @param mvMatrix model view matrix
	 */
	void setProgramMVMatrix(void* context, const Matrix4x4& mvMatrix);

	/** 
	 * Set up program mvp matrix
	 * @param context context
	 * @param mvpMatrix mvp matrix
	 */
	void setProgramMVPMatrix(void* context, const Matrix4x4& mvpMatrix);

	/** 
	 * Set up program normal matrix
	 * @param context context
	 * @param normalMatrix normal matrix
	 */
	void setProgramNormalMatrix(void* context, const Matrix4x4& normalMatrix);

	/**
	 * Set up pre program texture matrix
	 * @param renderer renderer
	 * @param context context
	 */
	void updateTextureMatrix(Renderer* renderer, void* context);

	/**
	 * Update material
	 * @param renderer renderer
	 * @param context context
	 */
	void updateMaterial(Renderer* renderer, void* context);

	/**
	 * Update light
	 * @param renderer renderer
	 * @param context context
	 * @param lightId light id
	 */
	void updateLight(Renderer* renderer, void* context, int32_t lightId);

	/**
	 * Bind texture
	 * @param renderer renderer
	 * @param context context
	 * @param textureId texture id
	 */
	void bindTexture(Renderer* renderer, void* context, int32_t textureId);

	/** 
	 * Set up program depth bias mvp matrix
	 * @param context context
	 * @param depthBiasMVPMatrix depth bias mvp matrix
	 */
	void setProgramDepthBiasMVPMatrix(void* context, const Matrix4x4& depthBiasMVPMatrix);

	/**
	 * Set light id
	 * @param lightId light id to render
	 */
	void setRenderLightId(int32_t lightId);

	/**
	 * Set shader
	 * @param id id
	 */
	void setShader(void* context, const string& id);

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	ShadowMappingShaderRender(Renderer* renderer);

	/**
	 * Destructor
	 */
	~ShadowMappingShaderRender();
};
