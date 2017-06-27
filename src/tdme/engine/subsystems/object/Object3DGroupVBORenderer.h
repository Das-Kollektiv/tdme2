// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DGroupVBORenderer.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DVBORenderer;


struct default_init_tag;

/** 
 * Object 3D group render 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::Object3DGroupVBORenderer final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	Object3DGroup* object3DGroup {  };
	int32_tArray* vboBaseIds {  };
	int32_tArray* vboTangentBitangentIds {  };
	int32_tArray* vboSkinningIds {  };
protected:

	/** 
	 * Constructor
	 * @param object 3D group
	 */
	void ctor(Object3DGroup* object3DGroup);

public: /* protected */
	void preRender(Object3DVBORenderer* object3DVBORenderer);

	/** 
	 * Disposes the object 3d group
	 * @param gl
	 */
	void dispose();

	// Generated
	Object3DGroupVBORenderer(Object3DGroup* object3DGroup);
protected:
	Object3DGroupVBORenderer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
