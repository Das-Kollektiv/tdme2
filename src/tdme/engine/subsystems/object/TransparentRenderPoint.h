// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderPoint.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::model::Color4;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Transparent point to be rendered
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::TransparentRenderPoint final
	: public virtual Object
{

public:
	typedef Object super;

public: /* protected */
	bool acquired {  };
	Vector3* point {  };
	Color4* color {  };
	float distanceFromCamera {  };

public:
	static bool compare(TransparentRenderPoint* point1, TransparentRenderPoint* point2);
	String* toString() override;

	// Generated
	TransparentRenderPoint();
protected:
	TransparentRenderPoint(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
