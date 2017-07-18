// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderFace.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::subsystems::object::Object3DGroup;


struct default_init_tag;

/** 
 * Transparent face to be rendered
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::TransparentRenderFace final
	: public virtual Object
{

public:
	typedef Object super;

public: /* protected */
	Object3DGroup* object3DGroup {  };
	int32_t facesEntityIdx {  };
	int32_t faceIdx {  };
	float distanceFromCamera {  };

public:
	static bool compare(TransparentRenderFace* face1, TransparentRenderFace* face2);
	String* toString() override;

	// Generated
	TransparentRenderFace();
protected:
	TransparentRenderFace(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
