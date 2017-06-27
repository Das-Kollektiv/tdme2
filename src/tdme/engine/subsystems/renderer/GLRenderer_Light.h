// Generated from /tdme/src/tdme/engine/subsystems/renderer/GLRenderer.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::subsystems::renderer::GLRenderer_Material;
using tdme::engine::subsystems::renderer::GLRenderer;


struct default_init_tag;

/** 
 * Bean holding light data
 */
class tdme::engine::subsystems::renderer::GLRenderer_Light
	: public virtual Object
{

public:
	typedef Object super;
	int32_t enabled {  };
	floatArray* ambient {  };
	floatArray* diffuse {  };
	floatArray* specular {  };
	floatArray* position {  };
	floatArray* spotDirection {  };
	float spotExponent {  };
	float spotCosCutoff {  };
	float constantAttenuation {  };
	float linearAttenuation {  };
	float quadraticAttenuation {  };

	// Generated
	GLRenderer_Light(GLRenderer *GLRenderer_this);
protected:
	GLRenderer_Light(GLRenderer *GLRenderer_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	GLRenderer *GLRenderer_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class GLRenderer;
	friend class GLRenderer_Material;
};
