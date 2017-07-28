// Generated from /tdme/src/tdme/engine/subsystems/renderer/GLRenderer.java

#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <java/lang/Object.h>

using std::array;

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
	int32_t enabled { 0 };
	array<float, 4> ambient { 0.0f, 0.0f, 0.0f, 1.0f };
	array<float, 4> diffuse { 1.0f, 1.0f, 1.0f, 1.0f };
	array<float, 4> specular { 1.0f, 1.0f, 1.0f, 1.0f };
	array<float, 4> position { 0.0f, 0.0f, 0.0f, 0.0f };
	array<float, 3> spotDirection { 0.0f, 0.0f, -1.0f };
	float spotExponent { 0.0f };
	float spotCosCutoff {  };
	float constantAttenuation { 1.0f };
	float linearAttenuation { 0.0f };
	float quadraticAttenuation { 0.0f };

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
