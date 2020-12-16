
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/application/Application.h>
#include <tdme/tools/leveleditor/fwd-tdme.h>
#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/tools/shared/views/fwd-tdme.h>

using std::string;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::tools::leveleditor::controller::SceneEditorLibraryScreenController;
using tdme::tools::leveleditor::views::EmptyView;
using tdme::tools::leveleditor::views::EnvironmentMappingView;
using tdme::tools::leveleditor::views::SceneEditorView;
using tdme::tools::leveleditor::views::ModelEditorView;
using tdme::tools::leveleditor::views::ParticleSystemView;
using tdme::tools::leveleditor::views::TriggerView;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneLibrary;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;

/**
 * TDME Scene Editor
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::TDMESceneEditor final
	: public virtual Application
{
private:
	static string VERSION;
	static TDMESceneEditor* instance;
	Engine* engine { nullptr };
	View* view { nullptr };
	bool quitRequested;
	SceneEditorLibraryScreenController* prototypeLibraryScreenController { nullptr };
	PopUps* popUps { nullptr };
	SceneEditorView* sceneEditorView { nullptr };
	ModelEditorView* modelEditorView { nullptr };
	TriggerView* triggerView { nullptr };
	EnvironmentMappingView* environmentMappingView { nullptr };
	EmptyView* emptyView { nullptr };
	ParticleSystemView* particleSystemView { nullptr };

public:

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

public:
	/**
	 * @return scene editor instance
	 */
	static TDMESceneEditor* getInstance();

	/**
	 * Public constructor
	 */
	TDMESceneEditor();

	/**
	 * Destructor
	 */
	~TDMESceneEditor();

	/**
	 * @return prototype library screen controller
	 */
	SceneEditorLibraryScreenController* getSceneEditorLibraryScreenController();

	/**
	 * @return scene prototype library
	 */
	SceneLibrary* getSceneLibrary();

	/**
	 * @return scene
	 */
	Scene* getScene();

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
	 * reshape tdme scene editor
	 */
	void reshape(int width, int height);

	/**
	 * Switch to scene editor
	 */
	void switchToSceneEditor();

	/**
	 * Switch to model editor
	 */
	void switchToModelEditor();

	/**
	 * Switch to trigger view
	 */
	void switchToTriggerView();

	/**
	 * Switch to environment mappingview
	 */
	void switchToEnvironmentMappingView();

	/**
	 * Switch to empty view
	 */
	void switchToEmptyView();

	/**
	 * Switch to particle system view
	 */
	void switchToParticleSystemView();

};
