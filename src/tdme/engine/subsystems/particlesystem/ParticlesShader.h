// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/ParticlesShader.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::Engine;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;


struct default_init_tag;

/** 
 * Interface to particles shader program
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::ParticlesShader final
	: public Object
{

public:
	typedef Object super;

private:
	int32_t renderProgramId {  };
	int32_t renderFragmentShaderId {  };
	int32_t renderVertexShaderId {  };
	int32_t uniformMVPMatrix {  };
	int32_t uniformMVMatrix {  };
	int32_t uniformPointSize {  };
	int32_t uniformDiffuseTextureUnit {  };
	int32_t uniformEffectColorMul {  };
	int32_t uniformEffectColorAdd {  };
	Matrix4x4* mvpMatrix {  };
	int32_t pointTextureId {  };
	bool isRunning {  };
	bool initialized {  };
	Engine* engine {  };
	GLRenderer* renderer {  };
protected:

	/** 
	 * Protected constructor
	 * @param renderer
	 */
	void ctor(Engine* engine, GLRenderer* renderer);

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
	 * Update effect to program
	 * @param renderer
	 */
	void updateEffect(GLRenderer* renderer);

	/** 
	 * Unuse lighting program
	 */
	void unUseProgram();

	/** 
	 * Update matrices to program
	 * @param renderer
	 */
	void updateMatrices(GLRenderer* renderer);

	// Generated
	ParticlesShader(Engine* engine, GLRenderer* renderer);
protected:
	ParticlesShader(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
