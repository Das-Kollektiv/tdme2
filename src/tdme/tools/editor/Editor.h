#pragma once

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/editor/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/tools/editor/views/EditorView.h>

using std::string;
using std::unique_ptr;
using std::vector;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::View;

/**
 * TDME editor
 * @author andreas.drewke
 */
class tdme::tools::editor::Editor final
	: public virtual Application
{
private:
	static Editor* instance;
	Engine* engine { nullptr };
	View* view { nullptr };
	bool viewInitialized;
	View* viewNew { nullptr };
	bool quitRequested;
	unique_ptr<PopUps> popUps;
	unique_ptr<EditorView> editorView;

public:

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 * @return exit code
	 */
	static int main(int argc, char** argv);

	/**
	 * @return particle system instance
	 */
	inline static Editor* getInstance() {
		return instance;
	}

	// forbid class copy
	FORBID_CLASS_COPY(Editor)

	/**
	 * Public constructor
	 */
	Editor();

	/**
	 * Destructor
	 */
	~Editor();

	/**
	 * @return if editor is running in full screen
	 */
	bool isFullScreen();

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

	/**
	 * On drop
	 * @param paths paths of items that were dropped
	 */
	void onDrop(const vector<string>& paths);
};
