#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>

#include <array>
#include <memory>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::array;
using std::make_unique;
using std::unique_ptr;

using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::Engine;
using tdme::engine::EntityShaderParameters;
using tdme::engine::ShaderParameter;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUIParser;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
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
		Console::println("PrototypeDisplaySubController::setDisplayDetails(): An error occurred: " + string(exception.what()));
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
		Console::println("PrototypeDisplaySubController::applyDisplayDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
	setDisplayShaderDetails(prototype);
}

void PrototypeDisplaySubController::createDisplayShaderDetailsXML(Prototype* prototype, const string& shaderParameterPrefix, const string& shader, const EntityShaderParameters& shaderParameters, string& xml) {
	for (const auto& parameterName: Engine::getShaderParameterNames(shader)) {
		auto parameter = shaderParameters.getShaderParameter(parameterName);
		auto parameterValue = parameter.toString();
		auto parameterType = "string";
		switch (parameter.getType()) {
		case ShaderParameter::TYPE_FLOAT:
			xml+= "<template name=\"" + GUIParser::escape(parameterName) + "\" id=\"" + GUIParser::escape(shaderParameterPrefix + parameterName) + "\" src=\"resources/engine/gui/template_details_rendering_shader_float.xml\" value=\"" + parameterValue + "\" />\n";
			break;
		case ShaderParameter::TYPE_INTEGER:
			xml+= "<template name=\"" + GUIParser::escape(parameterName) + "\" id=\"" + GUIParser::escape(shaderParameterPrefix + parameterName) + "\" src=\"resources/engine/gui/template_details_rendering_shader_int.xml\" value=\"" + parameterValue + "\" />\n";
			break;
		case ShaderParameter::TYPE_BOOLEAN:
			xml+= "<template name=\"" + GUIParser::escape(parameterName) + "\" id=\"" + GUIParser::escape(shaderParameterPrefix + parameterName) + "\" src=\"resources/engine/gui/template_details_rendering_shader_bool.xml\" value=\"" + parameterValue + "\" />\n";
			break;
		case ShaderParameter::TYPE_VECTOR2:
			{
				auto vec2 = parameter.getVector2Value();
				xml+= "<template name=\"" + GUIParser::escape(parameterName) + "\" id=\"" + GUIParser::escape(shaderParameterPrefix + parameterName) + "\" src=\"resources/engine/gui/template_details_rendering_shader_vector2.xml\" value_x=\"" + to_string(vec2.getX()) + "\" value_y=\"" + to_string(vec2.getY()) + "\" />\n";
			}
			break;
		case ShaderParameter::TYPE_VECTOR3:
			{
				auto vec3 = parameter.getVector3Value();
				xml+= "<template name=\"" + GUIParser::escape(parameterName) + "\" id=\"" + GUIParser::escape(shaderParameterPrefix + parameterName) + "\" src=\"resources/engine/gui/template_details_rendering_shader_vector3.xml\" value_x=\"" + to_string(vec3.getX()) + "\" value_y=\"" + to_string(vec3.getY()) + "\" value_z=\"" + to_string(vec3.getZ()) + "\" />\n";
			}
			break;
		case ShaderParameter::TYPE_VECTOR4:
			{
				auto vec4 = parameter.getVector4Value();
				xml+= "<template name=\"" + GUIParser::escape(parameterName) + "\" id=\"" + GUIParser::escape(shaderParameterPrefix + parameterName) + "\" src=\"resources/engine/gui/template_details_rendering_shader_vector4.xml\" value_x=\"" + to_string(vec4.getX()) + "\" value_y=\"" + to_string(vec4.getY()) + "\" value_z=\"" + to_string(vec4.getZ()) + "\" value_w=\"" + to_string(vec4.getW()) + "\" />\n";
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
}

void PrototypeDisplaySubController::setDisplayShaderDetails(Prototype* prototype) {
	string xml;
	createDisplayShaderDetailsXML(prototype, "rendering.shader.", prototype->getShader(), prototype->getShaderParameters(), xml);
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("rendering_shader_details"))->replaceSubNodes(xml, false);
	} catch (Exception& exception) {
		Console::println("PrototypeDisplaySubController::setDisplayShaderDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void PrototypeDisplaySubController::applyDisplayShaderDetails(Prototype* prototype, const string& shaderParameterPrefix, const string& parameterName, EntityShaderParameters& shaderParameters) {
	try {
		auto parameter = shaderParameters.getShaderParameter(parameterName);
		switch (parameter.getType()) {
			case ShaderParameter::TYPE_FLOAT:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName))->getController()->getValue().getString())
					)
				);
				break;
			case ShaderParameter::TYPE_INTEGER:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName))->getController()->getValue().getString())
					)
				);
				break;
			case ShaderParameter::TYPE_BOOLEAN:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName))->getController()->getValue().getString() == "1"
					)
				);
				break;
			case ShaderParameter::TYPE_VECTOR2:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Vector2(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName + "_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName + "_y"))->getController()->getValue().getString())
						)
					)
				);
				break;
			case ShaderParameter::TYPE_VECTOR3:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Vector3(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName + "_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName + "_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName + "_z"))->getController()->getValue().getString())
						)
					)
				);
				break;
			case ShaderParameter::TYPE_VECTOR4:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Vector4(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName + "_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName + "_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName + "_z"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(shaderParameterPrefix + parameterName + "_w"))->getController()->getValue().getString())
						)
					)
				);
				break;
			case ShaderParameter::TYPE_NONE:
				break;
		}
	} catch (Exception& exception) {
		Console::println("PrototypeDisplaySubController::applyDisplayShaderDetails(): An error occurred: " + string(exception.what()));
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
		applyDisplayShaderDetails(prototype, "rendering.shader.", StringTools::substring(node->getId(), string("rendering.shader.").size(), node->getId().size()), shaderParameters);
		prototype->setShaderParameters(shaderParameters);
		view->updateShaderParameters(prototype);
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
