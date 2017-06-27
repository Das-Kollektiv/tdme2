// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderFace.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/lang/Comparable.h>

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
	, public Comparable
{

public:
	typedef Object super;

public: /* protected */
	Object3DGroup* object3DGroup {  };
	int32_t facesEntityIdx {  };
	int32_t faceIdx {  };
	float distanceFromCamera {  };

public:
	int32_t compareTo(TransparentRenderFace* face2);
	String* toString() override;

	// Generated
	TransparentRenderFace();
protected:
	TransparentRenderFace(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* arg0) override;

private:
	virtual ::java::lang::Class* getClass0();
};
