#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;

/**
 * Prototype display view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView final
{
private:
	Engine* engine { nullptr };
	PrototypeDisplaySubController* prototypeDisplaySubController { nullptr };
	bool displayGroundPlate { true };
	bool displayShadowing { true };

public:
	/**
	 * Public constructor
	 * @param engine engine
	 * @param prototypeDisplaySubController entity display sub screen controller
	 */
	PrototypeDisplaySubView(Engine* engine, PrototypeDisplaySubController* prototypeDisplaySubController);

	/**
	 * Destructor
	 */
	 ~PrototypeDisplaySubView();

	/**
	 * @returns display ground plate
	 */
	inline bool isDisplayGroundPlate() {
		return this->displayGroundPlate;
	}

	/**
	 * Set up ground plate visibility
	 * @param groundPlate ground plate visible
	 */
	inline void setDisplayGroundPlate(bool groundPlate) {
		this->displayGroundPlate = groundPlate;
	}

	/**
	 * @returns display shadowing
	 */
	inline bool isDisplayShadowing() {
		return displayShadowing;
	}

	/**
	 * Set up shadow rendering
	 * @param shadowing shadow rendering
	 */
	inline void setDisplayShadowing(bool shadowing) {
		this->displayShadowing = shadowing;
	}

	/**
	 * Update shader parameters
	 * @param prototype prototype
	 */
	void updateShaderParameters(Prototype* prototype);

	/**
	 * Display
	 * @param prototype prototype
	 */
	 void display(Prototype* prototype);

};
