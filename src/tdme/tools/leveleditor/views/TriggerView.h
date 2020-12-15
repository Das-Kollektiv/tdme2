#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/CameraRotationInputHandlerEventHandler.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/gui/events/GUIInputEventHandler.h>

using tdme::tools::shared::views::View;
using tdme::gui::events::GUIInputEventHandler;
using tdme::engine::Engine;
using tdme::math::Vector3;
using tdme::tools::leveleditor::controller::TriggerScreenController;
using tdme::engine::prototype::Prototype;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::CameraRotationInputHandlerEventHandler;
using tdme::tools::shared::views::EntityPhysicsView;
using tdme::tools::shared::views::PopUps;

/**
 * Trigger view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::views::TriggerView final
	: public View
	, public GUIInputEventHandler
	, protected CameraRotationInputHandlerEventHandler
{
private:
	Engine* engine { nullptr };
	PopUps* popUps { nullptr };
	TriggerScreenController* triggerScreenController { nullptr };
	EntityPhysicsView* entityPhysicsView { nullptr };
	Prototype* entity { nullptr };
	CameraRotationInputHandler* cameraRotationInputHandler { nullptr };
	Vector3 objectScale;

public:
	/**
	 * Public constructor
	 * @param popUps pop ups view
	 */
	TriggerView(PopUps* popUps);

	/**
	 * Destructor
	 */
	~TriggerView();

	/**
	 * @return pop up views
	 */
	PopUps* getPopUpsViews();

	/**
	 * @return entity
	 */
	Prototype* getEntity();

	/**
	 * @return selected entity
	 */
	void setEntity(Prototype* entity);

	/**
	 * Renders the scene
	 */
	void display() override;

	/**
	 * Init GUI elements
	 */
	void updateGUIElements();

	// overridden methods
	void initialize() override;
	void activate() override;
	void deactivate() override;
	void dispose() override;
	void handleInputEvents() override;

	/**
	 * On rotation event to be overloaded
	 */
	void onRotation() override;

	/**
	 * On scale event to be overloaded
	 */
	void onScale() override;

};
