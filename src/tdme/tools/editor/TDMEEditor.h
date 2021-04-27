#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/editor/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/tools/editor/views/EditorView.h>

using std::string;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::View;

/**
 * TDME editor
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tools::editor::TDMEEditor final
	: public virtual Application
{
private:
	static TDMEEditor* instance;
	Engine* engine { nullptr };
	View* view { nullptr };
	bool viewInitialized;
	View* viewNew { nullptr };
	bool quitRequested;
	PopUps* popUps { nullptr };
	EditorView* editorView { nullptr };

public:

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

public:

	/**
	 * @return particle system instance
	 */
	static TDMEEditor* getInstance();

	/**
	 * Public constructor
	 */
	TDMEEditor();

	/**
	 * Destructor
	 */
	~TDMEEditor();

	/**
	 * Set up new view
	 * @param view view
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
	 * Initialize tdme scene editor
	 */
	void initialize();

	/**
	 * Reshape tdme scene editor
	 * @param width width
	 * @param height height
	 */
	void reshape(int width, int height);

};
