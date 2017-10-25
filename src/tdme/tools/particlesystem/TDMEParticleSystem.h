
#pragma once

#include <string>

#include <tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Application.h>
#include <tdme/tools/particlesystem/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>

using std::string;

using tdme::engine::Application;
using tdme::engine::Engine;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;
using tdme::tools::shared::views::SharedParticleSystemView;

/** 
 * TDME Particle System
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tools::particlesystem::TDMEParticleSystem final
	: public virtual Application
{
private:
	static string VERSION;
	static TDMEParticleSystem* instance;
	Engine* engine {  };
	View* view {  };
	bool viewInitialized {  };
	View* viewNew {  };
	bool quitRequested {  };
	PopUps* popUps {  };
	SharedParticleSystemView* particleSystemView;

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

	/**
	 * Destructor
	 */
	~TDMEParticleSystem();
};
