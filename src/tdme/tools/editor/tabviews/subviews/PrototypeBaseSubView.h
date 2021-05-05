#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>

using std::string;

using tdme::engine::prototype::Prototype;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeBaseSubController;

/**
 * Model base view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabviews::subviews::PrototypeBaseSubView final
{
private:
	PrototypeBaseSubController* prototypeBaseSubController { nullptr };

public:
	/**
	 * Public constructor
	 * @param prototypeBaseSubController model base sub screen controller
	 */
	PrototypeBaseSubView(PrototypeBaseSubController* prototypeBaseSubController);

	/**
	 * Update current model data
	 * @param prototype prototype
	 * @param name name
	 * @param description description
	 */
	void setPrototypeData(Prototype* prototype, const string& name, const string& description);

};
