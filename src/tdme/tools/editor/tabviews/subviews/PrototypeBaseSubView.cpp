#include <tdme/tools/editor/tabviews/subviews/PrototypeBaseSubView.h>

#include <string>

#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeProperty.h>
#include <tdme/engine/scene/ScenePropertyPresets.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeBaseSubController.h>

using std::string;

using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeProperty;
using tdme::engine::scene::ScenePropertyPresets;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeBaseSubController;
using tdme::tools::editor::tabviews::subviews::PrototypeBaseSubView;

PrototypeBaseSubView::PrototypeBaseSubView(PrototypeBaseSubController* prototypeBaseSubController)
{
	this->prototypeBaseSubController = prototypeBaseSubController;
}

void PrototypeBaseSubView::setPrototypeData(Prototype* prototype, const string& name, const string& description)
{
	if (prototype == nullptr)
		return;

	prototype->setName(name);
	prototype->setDescription(description);
}
