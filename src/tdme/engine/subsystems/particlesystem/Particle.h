// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/Particle.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::model::Color4;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Particle entity
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::Particle final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	bool active {  };
	Vector3* velocity {  };
	Vector3* position {  };
	float mass {  };
	int64_t lifeTimeMax {  };
	int64_t lifeTimeCurrent {  };
	Color4* color {  };
	Color4* colorAdd {  };

public:
	String* toString() override;

	// Generated
	Particle();
protected:
	void ctor();
	Particle(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
