#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/FileDialogPath.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::FileDialogPath;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;
using tdme::tools::editor::tabviews::ParticleSystemEditorTabView;
using tdme::utilities::MutableString;

/**
 * Particle system editor tab controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabcontrollers::ParticleSystemEditorTabController final
	: public TabController
{

private:
	BasePropertiesSubController* basePropertiesSubController { nullptr };
	PrototypePhysicsSubController* prototypePhysicsSubController { nullptr };
	PrototypeSoundsSubController* prototypeSoundsSubController { nullptr };
	ParticleSystemEditorTabView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };

	FileDialogPath modelPath;
	FileDialogPath audioPath;

public:
	/**
	 * Public constructor
	 * @param view view
	 */
	ParticleSystemEditorTabController(ParticleSystemEditorTabView* view);

	/**
	 * Destructor
	 */
	virtual ~ParticleSystemEditorTabController();

	/**
	 * @return prototype bounding volume sub screen controller
	 */
	inline PrototypePhysicsSubController* getPrototypePhysicsSubController() {
		return prototypePhysicsSubController;
	}

	/**
	 * @return prototype sounds sub screen controller
	 */
	inline PrototypeSoundsSubController* getPrototypeSoundsSubController() {
		return prototypeSoundsSubController;
	}

	/**
	 * Get view
	 */
	ParticleSystemEditorTabView* getView();

	// overridden method
	GUIScreenNode* getScreenNode() override;

	/**
	 * @return model path
	 */
	FileDialogPath* getModelPath();

	/**
	 * @return audio path
	 */
	FileDialogPath* getAudioPath();

	// overridden methods
	void initialize(GUIScreenNode* screenNode) override;
	void dispose() override;
	void save() override;
	void saveAs() override;

	// overridden methods
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) override;

	/**
	 * Set outliner content
	 */
	void setOutlinerContent();

	/**
	 * Update details panel
	 * @param outlinerNode outliner node
	 */
	void updateDetails(const string& outlinerNode);

	/**
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

};
