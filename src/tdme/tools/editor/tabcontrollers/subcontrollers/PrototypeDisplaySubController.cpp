#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>

#include <array>
#include <memory>

#include <agui/agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIImageNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <agui/utilities/MutableString.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTools.h>

using std::array;
using std::make_unique;
using std::unique_ptr;

using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIImageNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUIParser;
using agui::utilities::MutableString;

using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::Engine;
using tdme::engine::EntityShaderParameters;
using tdme::engine::ShaderParameter;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::StringTools;

PrototypeDisplaySubController::PrototypeDisplaySubController(EditorView* editorView, TabView* tabView, PrototypePhysicsSubView* physicsView)
{
	this->editorView = editorView;
	this->tabView = tabView;
	view = make_unique<PrototypeDisplaySubView>(tabView->getEngine(), this);
	this->physicsView = physicsView;
	this->popUps = editorView->getPopUps();
}

PrototypeDisplaySubController::~PrototypeDisplaySubController() {
}

void PrototypeDisplaySubController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void PrototypeDisplaySubController::createDisplayPropertiesXML(Prototype* prototype, string& xml) {
	xml+= "	<selectbox-option image=\"resources/engine/images/rendering.png\" text=\"Rendering\" value=\"rendering\" />\n";
}

void PrototypeDisplaySubController::setDisplayDetails(Prototype* prototype) {
	editorView->setDetailsContent(
		"<template id=\"details_rendering\" src=\"resources/engine/gui/template_details_rendering.xml\" />\n"
	);

	string shaderXML;
	{
		for (const auto& shader: Engine::getRegisteredShader(Engine::ShaderType::SHADERTYPE_OBJECT)) {
			shaderXML =
				shaderXML +
				"<dropdown-option text=\"" +
				GUIParser::escape(shader) +
				"\" value=\"" +
				GUIParser::escape(shader) +
				"\" " +
				(shader == "default"?"selected=\"true\" " : "") +
				"/>\n";
		}
	}

	try {
		// physics
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_rendering"))->getActiveConditions().add("open");
		if (prototype->getType() == Prototype_Type::MODEL) required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_rendering"))->getActiveConditions().add("shader");

		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("rendering_shader"))->replaceSubNodes(shaderXML, true);

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_shader"))->getController()->setValue(MutableString(prototype->getShader()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_contributes_shadows"))->getController()->setValue(MutableString(prototype->isContributesShadows() == true?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_receives_shadows"))->getController()->setValue(MutableString(prototype->isReceivesShadows() == true?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_render_groups"))->getController()->setValue(MutableString(prototype->isRenderGroups() == true?"1":""));

	} catch (Exception& exception) {
		Console::printLine("PrototypeDisplaySubController::setDisplayDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	setDisplayShaderDetails(prototype);
}

void PrototypeDisplaySubController::updateDetails(Prototype* prototype, const string& outlinerNode) {
	if (outlinerNode == "rendering") setDisplayDetails(prototype);
}

void PrototypeDisplaySubController::applyDisplayDetails(Prototype* prototype) {
	try {
		prototype->setShader(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_shader"))->getController()->getValue().getString());
		prototype->setContributesShadows(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_contributes_shadows"))->getController()->getValue().getString() == "1");
		prototype->setReceivesShadows(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_receives_shadows"))->getController()->getValue().getString() == "1");
		prototype->setRenderGroups(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_render_groups"))->getController()->getValue().getString() == "1");
	} catch (Exception& exception) {
		Console::printLine("PrototypeDisplaySubController::applyDisplayDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
	setDisplayShaderDetails(prototype);
}

void PrototypeDisplaySubController::setDisplayShaderDetails(Prototype* prototype) {
	string xml;
	const auto& shaderParameters = prototype->getShaderParameters();
	for (const auto& parameterName: Engine::getShaderParameterNames(prototype->getShader())) {
		auto parameterDefaults = Engine::getDefaultShaderParameter(prototype->getShader(), parameterName);
		if (parameterDefaults == nullptr) continue;
		auto parameter = shaderParameters.getShaderParameter(parameterName);
		switch (parameter.getType()) {
			case ShaderParameter::TYPE_FLOAT:
				{
					auto parameterValue = parameter.getValueAsString();
					xml+=
						"<template name=\"" +
						GUIParser::escape(parameterName) + "\" " +
						"id=\"" + GUIParser::escape("rendering.shader." + parameterName) + "\" " +
						"src=\"resources/engine/gui/template_details_rendering_shader_float.xml\" " +
						"value=\"" + parameterValue + "\" " +
						"min=\"" + to_string(parameterDefaults->min.getFloatValue()) + "\" " +
						"max=\"" + to_string(parameterDefaults->max.getFloatValue()) + "\" " +
						"step=\"" + to_string(parameterDefaults->step.getFloatValue()) + "\" " +
						"/>\n";
					break;
				}
			case ShaderParameter::TYPE_INTEGER:
				{
					auto parameterValue = parameter.getValueAsString();
					xml+=
						"<template name=\"" + GUIParser::escape(parameterName) + "\" " +
						"id=\"" + GUIParser::escape("rendering.shader." + parameterName) + "\" " +
						"src=\"resources/engine/gui/template_details_rendering_shader_int.xml\" " +
						"value=\"" + parameterValue + "\" " +
						"min=\"" + to_string(parameterDefaults->min.getIntegerValue()) + "\" " +
						"max=\"" + to_string(parameterDefaults->max.getIntegerValue()) + "\" " +
						"step=\"" + to_string(parameterDefaults->step.getIntegerValue()) + "\" " +
						"/>\n";
					break;
				}
			case ShaderParameter::TYPE_BOOLEAN:
				{
					auto parameterValue = parameter.getValueAsString();
					xml+=
						"<template name=\"" + GUIParser::escape(parameterName) + "\" " +
						"id=\"" + GUIParser::escape("rendering.shader." + parameterName) + "\" " +
						"src=\"resources/engine/gui/template_details_rendering_shader_bool.xml\" " +
						"value=\"" + parameterValue + "\" " +
						"/>\n";
					break;
				}
			case ShaderParameter::TYPE_VECTOR2:
				{
					auto vec2 = parameter.getVector2Value();
					xml+=
						"<template name=\"" + GUIParser::escape(parameterName) + "\" " +
						"id=\"" + GUIParser::escape("rendering.shader." + parameterName) + "\" " +
						"src=\"resources/engine/gui/template_details_rendering_shader_vector2.xml\" " +
						"value_x=\"" + to_string(vec2.getX()) + "\" " +
						"min_x=\"" + to_string(parameterDefaults->min.getVector2Value().getX()) + "\" " +
						"max_x=\"" + to_string(parameterDefaults->max.getVector2Value().getX()) + "\" " +
						"step_x=\"" + to_string(parameterDefaults->step.getVector2Value().getX()) + "\" " +
						"value_y=\"" + to_string(vec2.getY()) + "\" "+
						"min_y=\"" + to_string(parameterDefaults->min.getVector2Value().getY()) + "\" " +
						"max_y=\"" + to_string(parameterDefaults->max.getVector2Value().getY()) + "\" " +
						"step_y=\"" + to_string(parameterDefaults->step.getVector2Value().getY()) + "\" " +
						"/>\n";
				}
				break;
			case ShaderParameter::TYPE_VECTOR3:
				{
					auto vec3 = parameter.getVector3Value();
					xml+=
						"<template name=\"" + GUIParser::escape(parameterName) + "\" " +
						"id=\"" + GUIParser::escape("rendering.shader." + parameterName) + "\" " +
						"src=\"resources/engine/gui/template_details_rendering_shader_vector3.xml\" " +
						"value_x=\"" + to_string(vec3.getX()) + "\" " +
						"min_x=\"" + to_string(parameterDefaults->min.getVector3Value().getX()) + "\" " +
						"max_x=\"" + to_string(parameterDefaults->max.getVector3Value().getX()) + "\" " +
						"step_x=\"" + to_string(parameterDefaults->step.getVector3Value().getX()) + "\" " +
						"value_y=\"" + to_string(vec3.getY()) + "\" "+
						"min_y=\"" + to_string(parameterDefaults->min.getVector3Value().getY()) + "\" " +
						"max_y=\"" + to_string(parameterDefaults->max.getVector3Value().getY()) + "\" " +
						"step_y=\"" + to_string(parameterDefaults->step.getVector3Value().getY()) + "\" " +
						"value_z=\"" + to_string(vec3.getZ()) + "\" "+
						"min_z=\"" + to_string(parameterDefaults->min.getVector3Value().getZ()) + "\" " +
						"max_z=\"" + to_string(parameterDefaults->max.getVector3Value().getZ()) + "\" " +
						"step_z=\"" + to_string(parameterDefaults->step.getVector3Value().getZ()) + "\" " +
						"/>\n";
				}
				break;
			case ShaderParameter::TYPE_VECTOR4:
				{
					auto vec4 = parameter.getVector4Value();
					xml+=
						"<template name=\"" + GUIParser::escape(parameterName) + "\" " +
						"id=\"" + GUIParser::escape("rendering.shader." + parameterName) + "\" " +
						"src=\"resources/engine/gui/template_details_rendering_shader_vector4.xml\" " +
						"value_x=\"" + to_string(vec4.getX()) + "\" " +
						"min_x=\"" + to_string(parameterDefaults->min.getVector4Value().getX()) + "\" " +
						"max_x=\"" + to_string(parameterDefaults->max.getVector4Value().getX()) + "\" " +
						"step_x=\"" + to_string(parameterDefaults->step.getVector4Value().getX()) + "\" " +
						"value_y=\"" + to_string(vec4.getY()) + "\" "+
						"min_y=\"" + to_string(parameterDefaults->min.getVector4Value().getY()) + "\" " +
						"max_y=\"" + to_string(parameterDefaults->max.getVector4Value().getY()) + "\" " +
						"step_y=\"" + to_string(parameterDefaults->step.getVector4Value().getY()) + "\" " +
						"value_z=\"" + to_string(vec4.getZ()) + "\" "+
						"min_z=\"" + to_string(parameterDefaults->min.getVector4Value().getZ()) + "\" " +
						"max_z=\"" + to_string(parameterDefaults->max.getVector4Value().getZ()) + "\" " +
						"step_z=\"" + to_string(parameterDefaults->step.getVector4Value().getZ()) + "\" " +
						"value_w=\"" + to_string(vec4.getW()) + "\" "+
						"min_w=\"" + to_string(parameterDefaults->min.getVector4Value().getW()) + "\" " +
						"max_w=\"" + to_string(parameterDefaults->max.getVector4Value().getW()) + "\" " +
						"step_w=\"" + to_string(parameterDefaults->step.getVector4Value().getW()) + "\" " +
						"/>\n";
				}
				break;
			case ShaderParameter::TYPE_COLOR4:
				{
					xml+=
						"<template name=\"" + GUIParser::escape(parameterName) + "\" "
						"id=\"" + GUIParser::escape("rendering.shader." + parameterName) + "\" " +
						"src=\"resources/engine/gui/template_details_rendering_shader_color4.xml\" " +
						"/>\n";
				}
				break;
			case ShaderParameter::TYPE_NONE:
				break;
		}
	}
	if (xml.empty() == false) {
		xml+=
			string("<space height=\"5\" />") + string("\n") +
			string("<menu-separator />") + string("\n") +
			string("<space height=\"5\" />") + string("\n");

	}
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("rendering_shader_details"))->replaceSubNodes(xml, false);
		//
		for (const auto& parameterName: Engine::getShaderParameterNames(prototype->getShader())) {
			auto parameter = shaderParameters.getShaderParameter(parameterName);
			switch (parameter.getType()) {
				case ShaderParameter::TYPE_COLOR4:
					{
						auto color4 = parameter.getColor4Value();
						required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_color"))->setEffectColorMul(color4.getArray());
					}
					break;
				default:
					break;
			}
		}

	} catch (Exception& exception) {
		Console::printLine("PrototypeDisplaySubController::setDisplayShaderDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void PrototypeDisplaySubController::applyDisplayShaderDetails(Prototype* prototype, const string& parameterName, EntityShaderParameters& shaderParameters) {
	try {
		auto parameter = shaderParameters.getShaderParameter(parameterName);
		switch (parameter.getType()) {
			case ShaderParameter::TYPE_FLOAT:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName))->getController()->getValue().getString())
					)
				);
				break;
			case ShaderParameter::TYPE_INTEGER:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName))->getController()->getValue().getString())
					)
				);
				break;
			case ShaderParameter::TYPE_BOOLEAN:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName))->getController()->getValue().getString() == "1"
					)
				);
				break;
			case ShaderParameter::TYPE_VECTOR2:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Vector2(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_y"))->getController()->getValue().getString())
						)
					)
				);
				break;
			case ShaderParameter::TYPE_VECTOR3:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Vector3(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_z"))->getController()->getValue().getString())
						)
					)
				);
				break;
			case ShaderParameter::TYPE_VECTOR4:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Vector4(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_z"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_w"))->getController()->getValue().getString())
						)
					)
				);
				break;
			case ShaderParameter::TYPE_COLOR4:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Color4(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_z"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering.shader." + parameterName + "_w"))->getController()->getValue().getString())
						)
					)
				);
				break;
			case ShaderParameter::TYPE_NONE:
				break;
		}
	} catch (Exception& exception) {
		Console::printLine("PrototypeDisplaySubController::applyDisplayShaderDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

bool PrototypeDisplaySubController::onChange(GUIElementNode* node, Prototype* prototype) {
	for (const auto& applyDisplayNode: applyDisplayNodes) {
		if (node->getId() == applyDisplayNode) {
			applyDisplayDetails(prototype);
			tabView->updateRendering();
			return true;
		}
	}
	if (node->getId() == tabView->getTabId() + "_tab_checkbox_grid") {
		view->setDisplayGroundPlate(node->getController()->getValue().equals("1"));
		//
		return true;
	} else
	if (StringTools::startsWith(node->getId(), "rendering.shader.") == true) {
		auto shaderParameters = prototype->getShaderParameters();
		applyDisplayShaderDetails(prototype, StringTools::substring(node->getId(), string("rendering.shader.").size(), node->getId().size()), shaderParameters);
		prototype->setShaderParameters(shaderParameters);
		view->updateShaderParameters(prototype);
		//
		return true;
	}
	//
	return false;
}

bool PrototypeDisplaySubController::onAction(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype) {
	if (type != GUIActionListenerType::PERFORMED) return false;
	//
	if (StringTools::startsWith(node->getId(), "rendering.shader.") == true &&
		StringTools::endsWith(node->getId(), "_color_edit") == true) {
		//
		auto parameterName = StringTools::substring(node->getId(), string("rendering.shader.").size(), node->getId().size() - string("_color_edit").size());
		const auto& shaderParameters = prototype->getShaderParameters();
		auto parameter = shaderParameters.getShaderParameter(parameterName);
		auto color4 = parameter.getColor4Value();
		//
		class OnColorChangeAction: public Action
		{
		public:
			void performAction() override {
				//
				auto view = prototypeDisplaySubController->getView();
				auto shaderParameters = prototype->getShaderParameters();
				auto parameter = shaderParameters.getShaderParameter(parameterName);
				auto color4 = prototypeDisplaySubController->popUps->getColorPickerScreenController()->getColor();
				shaderParameters.setShaderParameter(parameterName, color4);
				try {
					required_dynamic_cast<GUIImageNode*>(prototypeDisplaySubController->screenNode->getNodeById("rendering.shader." + parameterName + "_color"))->setEffectColorMul(color4.getArray());
				} catch (Exception& exception) {
					Console::printLine("PrototypeDisplaySubController::onAction(): An error occurred: " + string(exception.what()));
					prototypeDisplaySubController->showInfoPopUp("Warning", string(exception.what()));
				}
				//
				prototype->setShaderParameters(shaderParameters);
				prototypeDisplaySubController->view->updateShaderParameters(prototype);
			}
			OnColorChangeAction(PrototypeDisplaySubController* prototypeDisplaySubController, Prototype* prototype, const string& parameterName): prototypeDisplaySubController(prototypeDisplaySubController), prototype(prototype), parameterName(parameterName) {
			}
		private:
			PrototypeDisplaySubController* prototypeDisplaySubController;
			Prototype* prototype;
			string parameterName;
		};
		//
		popUps->getColorPickerScreenController()->show(color4, new OnColorChangeAction(this, prototype, parameterName));
		//
		return true;
	}
	//
	return false;
}

void PrototypeDisplaySubController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}
