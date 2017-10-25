
#pragma once

#include <string>

#include <tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Application.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>
#include <tdme/tools/viewer/fwd-tdme.h>

using std::string;

using tdme::engine::Application;
using tdme::engine::Engine;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;
using tdme::tools::shared::views::SharedModelViewerView;

/** 
 * TDME Level Editor
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tools::viewer::TDMEViewer final
	: public Application
{

private:
	static string VERSION;
	static TDMEViewer* instance;
	Engine* engine {  };
	View* view {  };
	bool viewInitialized {  };
	View* viewNew {  };
	bool quitRequested {  };
	PopUps* popUps {  };
	SharedModelViewerView* modelViewerView;

public:
	/** 
	 * @param argument count
	 * @param argument values
	 */
	static void main(int argc, char** argv);

public:

	/** 
	 * @return level editor instance
	 */
	static TDMEViewer* getInstance();

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
	TDMEViewer();

	/**
	 * Destructor
	 */
	~TDMEViewer();
};
