#include <tdme/tools/editor/tabviews/subviews/PrototypeScriptSubView.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/ScenePropertyPresets.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeScriptSubController.h>

using std::string;

using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::ScenePropertyPresets;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeScriptSubController;
using tdme::tools::editor::tabviews::subviews::PrototypeScriptSubView;

PrototypeScriptSubView::PrototypeScriptSubView(PrototypeScriptSubController* prototypeBaseSubController)
{
	this->prototypeBaseSubController = prototypeBaseSubController;
}

void PrototypeScriptSubView::setScript(Prototype* prototype, const string& fileName)
{
	if (prototype == nullptr)
		return;

	prototype->setScript(fileName);
}
