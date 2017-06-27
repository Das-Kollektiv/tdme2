// Generated from /tdme/src/tdme/engine/subsystems/object/AnimationState.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::model::AnimationSetup;


struct default_init_tag;

/** 
 * Animation state class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::AnimationState final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	AnimationSetup* setup {  };
	int64_t currentAtTime {  };
	int64_t lastAtTime {  };
	bool finished {  };
	float time {  };

	// Generated

public:
	AnimationState();
protected:
	void ctor();
	AnimationState(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
