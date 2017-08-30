// Generated from /tdme/src/tdme/tools/particlesystem/TDMEParticleSystem.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Application.h>
#include <tdme/tools/particlesystem/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>

using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Application;
using tdme::engine::Engine;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;

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

/** 
 * TDME Particle System
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tools::particlesystem::TDMEParticleSystem final
	: public virtual Application
{
private:
	static String* VERSION;
	static TDMEParticleSystem* instance;
	Engine* engine {  };
	View* view {  };
	bool viewInitialized {  };
	View* viewNew {  };
	bool quitRequested {  };
	PopUps* popUps {  };

public:

	/** 
	 * Main
	 * @param argument count
	 * @param argument values
	 */
	static void main(int argc, char** argv);

public:

	/** 
	 * @return particle system instance
	 */
	static TDMEParticleSystem* getInstance();

	/** 
	 * Set up new view
	 * @param view
	 */
	void setView(View* view);

	/** 
	 * @return current view
	 */
	View* getView();

	/** 
	 * Request to exit the viewer
	 */
	void quit();

	/** 
	 * Renders the scene 
	 */
	void display();

	/** 
	 * Shutdown tdme viewer
	 */
	void dispose();

	/** 
	 * Initialize tdme level editor
	 */
	void initialize();

	/** 
	 * Reshape tdme level editor
	 * @param width
	 * @param height
	 */
	void reshape(int32_t width, int32_t height);

	/**
	 * Public constructor
	 */
	TDMEParticleSystem();
};
