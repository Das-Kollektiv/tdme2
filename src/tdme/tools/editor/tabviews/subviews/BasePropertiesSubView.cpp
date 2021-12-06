#include <tdme/tools/editor/tabviews/subviews/BasePropertiesSubView.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/ScenePropertyPresets.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>

using std::string;

using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::ScenePropertyPresets;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabviews::subviews::BasePropertiesSubView;

BasePropertiesSubView::BasePropertiesSubView(BasePropertiesSubController* prototypeBaseSubController)
{
	this->prototypeBaseSubController = prototypeBaseSubController;
}

void BasePropertiesSubView::setPrototypeData(Prototype* prototype, const string& name, const string& description)
{
	if (prototype == nullptr)
		return;

	prototype->setName(name);
	prototype->setDescription(description);
}
