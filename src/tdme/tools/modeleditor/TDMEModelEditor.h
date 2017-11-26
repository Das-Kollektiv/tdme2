
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/application/Application.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/SharedModelEditorView.h>
#include <tdme/tools/modeleditor/fwd-tdme.h>

using std::string;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;
using tdme::tools::shared::views::SharedModelEditorView;

/** 
 * TDME Level Editor
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tools::viewer::TDMEModelEditor final
	: public Application
{

private:
	static string VERSION;
	static TDMEModelEditor* instance;
	Engine* engine {  };
	View* view {  };
	bool viewInitialized {  };
	View* viewNew {  };
	bool quitRequested {  };
	PopUps* popUps {  };
	SharedModelEditorView* modelViewerView;

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
	static TDMEModelEditor* getInstance();

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
	TDMEModelEditor();

	/**
	 * Destructor
	 */
	~TDMEModelEditor();
};
