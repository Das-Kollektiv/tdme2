#include <tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>

using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;

using std::string;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityShaderParameters;
using tdme::engine::Object;
using tdme::engine::ShaderParameter;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;

PrototypeDisplaySubView::PrototypeDisplaySubView(Engine* engine, PrototypeDisplaySubController* prototypeDisplaySubController)
{
	this->engine = engine;
	this->prototypeDisplaySubController = prototypeDisplaySubController;
}

PrototypeDisplaySubView::~PrototypeDisplaySubView() {
}

void PrototypeDisplaySubView::updateShaderParameters(Prototype* prototype) {
	auto object = dynamic_cast<Object*>(engine->getEntity("model"));
	if (object == nullptr || prototype == nullptr) return;
	auto shaderParametersDefault = Engine::getShaderParameterDefaults(prototype->getShader());
	for (const auto& [parameterName, defaultParameterValue]: shaderParametersDefault) {
		auto parameterValue = prototype->getShaderParameters().getShaderParameter(parameterName);
		object->setShaderParameter(parameterName, parameterValue);
	}
}

void PrototypeDisplaySubView::display(Prototype* prototype)
{
	if (prototype != nullptr) {
		auto model = engine->getEntity("model");
		if (model != nullptr) model->setContributesShadows(displayShadowing == true && prototype->isContributesShadows() == true);
		if (model != nullptr) model->setReceivesShadows(displayShadowing == true && prototype->isReceivesShadows() == true);
		auto ground = engine->getEntity("ground");
		if (ground != nullptr) ground->setEnabled(displayGroundPlate);
		if (ground != nullptr) ground->setContributesShadows(false);
		if (ground != nullptr) ground->setReceivesShadows(displayShadowing);
	}
}
