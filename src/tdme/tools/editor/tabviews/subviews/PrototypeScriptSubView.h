#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>

using std::string;

using tdme::engine::prototype::Prototype;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeScriptSubController;

/**
 * Model base view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::subviews::PrototypeScriptSubView final
{
private:
	PrototypeScriptSubController* prototypeBaseSubController { nullptr };

public:
	/**
	 * Public constructor
	 * @param prototypeScriptSubController model base sub screen controller
	 */
	PrototypeScriptSubView(PrototypeScriptSubController* prototypeBaseSubController);

	/**
	 * Update prototype script
	 * @param prototype prototype
	 * @param fileName file name
	 */
	void setScript(Prototype* prototype, const string& fileName);

};
