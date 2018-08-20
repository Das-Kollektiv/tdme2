#pragma once

#include <tdme/tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::gui::nodes::GUIElementNode;

class tdme::tools::shared::controller::ModelEditorScreenController_onMaterialLoadTexture: public virtual Action
{
public:
	void performAction() override;

	/**
	 * Public constructor
	 * @param modelEditorScreenController model editor screen controller
	 * @param guiElementNode gui element node
	 */
	ModelEditorScreenController_onMaterialLoadTexture(ModelEditorScreenController* modelEditorScreenController, GUIElementNode* guiElementNode);

private:
	ModelEditorScreenController* modelEditorScreenController;
	GUIElementNode* guiElementNode;
};
