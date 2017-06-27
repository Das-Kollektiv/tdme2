// Generated from /tdme/src/tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;


struct default_init_tag;

/** 
 * Pre shadow mapping shader for render shadow map pass 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre
	: public virtual Object
{

public:
	typedef Object super;

private:
	GLRenderer* renderer {  };
	int32_t preVertexShaderGlId {  };
	int32_t preFragmentShaderGlId {  };
	int32_t preUniformMVPMatrix {  };
	int32_t preProgramGlId {  };
	bool initialized {  };
protected:

	/** 
	 * Constructor
	 */
	void ctor(GLRenderer* renderer);

public:

	/** 
	 * @return if initialized and ready to use
	 */
	virtual bool isInitialized();

	/** 
	 * Init shadow mapping
	 */
	virtual void initialize();

	/** 
	 * Use pre render shadow mapping program
	 */
	virtual void useProgram();

	/** 
	 * Un use pre render shadow mapping program
	 */
	virtual void unUseProgram();

	/** 
	 * Set up pre program mvp matrix
	 * @param mvp matrix
	 */
	virtual void setProgramMVPMatrix(Matrix4x4* mvpMatrix);

	// Generated
	ShadowMappingShaderPre(GLRenderer* renderer);
protected:
	ShadowMappingShaderPre(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
