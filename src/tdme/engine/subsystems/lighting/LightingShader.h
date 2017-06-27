// Generated from /tdme/src/tdme/engine/subsystems/lighting/LightingShader.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;


struct default_init_tag;

/** 
 * Interface to gl3 lighting shader program
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::lighting::LightingShader final
	: public Object
{

public:
	typedef Object super;
	static constexpr int32_t MAX_LIGHTS { 8 };
	static constexpr int32_t TEXTUREUNIT_DIFFUSE { 0 };
	static constexpr int32_t TEXTUREUNIT_SPECULAR { 1 };
	static constexpr int32_t TEXTUREUNIT_DISPLACEMENT { 2 };
	static constexpr int32_t TEXTUREUNIT_NORMAL { 3 };

private:
	int32_t renderLightingProgramId {  };
	int32_t renderLightingFragmentShaderId {  };
	int32_t renderLightingVertexShaderId {  };
	int32_t uniformDiffuseTextureUnit {  };
	int32_t uniformDiffuseTextureAvailable {  };
	int32_t uniformSpecularTextureUnit {  };
	int32_t uniformSpecularTextureAvailable {  };
	int32_t uniformNormalTextureUnit {  };
	int32_t uniformNormalTextureAvailable {  };
	int32_t uniformDisplacementTextureUnit {  };
	int32_t uniformDisplacementTextureAvailable {  };
	int32_t uniformMVPMatrix {  };
	int32_t uniformMVMatrix {  };
	int32_t uniformNormalMatrix {  };
	int32_t uniformSceneColor {  };
	int32_t uniformEffectColorMul {  };
	int32_t uniformEffectColorAdd {  };
	int32_t uniformMaterialAmbient {  };
	int32_t uniformMaterialDiffuse {  };
	int32_t uniformMaterialSpecular {  };
	int32_t uniformMaterialEmission {  };
	int32_t uniformMaterialShininess {  };
	int32_tArray* uniformLightEnabled {  };
	int32_tArray* uniformLightAmbient {  };
	int32_tArray* uniformLightDiffuse {  };
	int32_tArray* uniformLightSpecular {  };
	int32_tArray* uniformLightPosition {  };
	int32_tArray* uniformLightSpotDirection {  };
	int32_tArray* uniformLightSpotExponent {  };
	int32_tArray* uniformLightSpotCosCutoff {  };
	int32_tArray* uniformLightConstantAttenuation {  };
	int32_tArray* uniformLightLinearAttenuation {  };
	int32_tArray* uniformLightQuadraticAttenuation {  };
	Matrix4x4* mvMatrix {  };
	Matrix4x4* mvpMatrix {  };
	Matrix4x4* normalMatrix {  };
	floatArray* defaultSceneColor {  };
	floatArray* tmpColor4 {  };
	bool isRunning {  };
	bool initialized {  };
	GLRenderer* renderer {  };
protected:

	/** 
	 * Protected constructor
	 * @param renderer
	 */
	void ctor(GLRenderer* renderer);

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
	 * Bind texture
	 * @param renderer
	 * @param texture id
	 */
	void bindTexture(GLRenderer* renderer, int32_t textureId);

	// Generated
	LightingShader(GLRenderer* renderer);
protected:
	LightingShader(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
