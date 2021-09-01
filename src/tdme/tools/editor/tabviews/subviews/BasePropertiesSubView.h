#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>

using std::string;

using tdme::engine::prototype::Prototype;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;

/**
 * Model base view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabviews::subviews::BasePropertiesSubView final
{
private:
	BasePropertiesSubController* prototypeBaseSubController { nullptr };

public:
	/**
	 * Public constructor
	 * @param prototypeBaseSubController model base sub screen controller
	 */
	BasePropertiesSubView(BasePropertiesSubController* prototypeBaseSubController);

	/**
	 * Update current model data
	 * @param prototype prototype
	 * @param name name
	 * @param description description
	 */
	void setPrototypeData(Prototype* prototype, const string& name, const string& description);

};
