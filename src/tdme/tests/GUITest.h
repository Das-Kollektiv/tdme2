// Generated from /tdme/src/tdme/tests/GUITest.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Application.h>
#include <tdme/tests/fwd-tdme.h>

using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Application;
using tdme::engine::Engine;

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

using tdme::engine::Application;

/** 
 * GUI Test
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tests::GUITest final
	: public virtual Application
{
	friend class GUITest_init_1;
	friend class GUITest_init_2;

private:
	Engine* engine {  };

public:
	void initialize();
	void dispose();
	void reshape(int32_t width, int32_t height);
	void display();

	/** 
	 * Main
	 * @param argument count
	 * @param argument values
	 */
	static void main(int argc, char** argv);

	/**
	 * Public constructor
	 */
	GUITest();
};
