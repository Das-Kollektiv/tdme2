// Generated from /tdme/src/tdme/tests/PhysicsTest3.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::physics::World;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

struct default_init_tag;

/** 
 * Engine with physics test 3
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::PhysicsTest3 final
	: public virtual Object
{

public:
	typedef Object super;

private:
	static constexpr int32_t RIGID_TYPEID_STANDARD { 1 };
	static constexpr int32_t BOX_COUNT { 5 };
	static constexpr int32_t BOXSTACK_COUNT { 2 };
	static constexpr int32_t CAPSULE_COUNT { 10 };
	static constexpr int32_t SPHERE_COUNT { 10 };
	Engine* engine {  };
	bool keyLeft {  };
	bool keyRight {  };
	bool keyUp {  };
	bool keyDown {  };
	bool keyW {  };
	bool keyA {  };
	bool keyS {  };
	bool keyD {  };
	World* world {  };

public:

	/** 
	 * Main
	 * @param args
	 */
	static void main(StringArray* args);
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

public:

	/** 
	 * Display
	 */
	void display();
	void dispose();
	void init_();
	void reshape(int32_t x, int32_t y, int32_t width, int32_t height);

	// Generated
	PhysicsTest3();
protected:
	PhysicsTest3(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
