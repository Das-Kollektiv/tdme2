#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>

#include <array>

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::array;

using tdme::engine::Engine;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

PrototypeDisplaySubController::PrototypeDisplaySubController(EditorView* editorView, Engine* engine, PrototypePhysicsSubView* physicsView)
{
	this->editorView = editorView;
	view = new PrototypeDisplaySubView(engine, this);
	this->physicsView = physicsView;
	this->popUps = editorView->getPopUps();
}

PrototypeDisplaySubController::~PrototypeDisplaySubController() {
	delete view;
}

PrototypeDisplaySubView* PrototypeDisplaySubController::getView()
{
	return view;
}

void PrototypeDisplaySubController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

bool PrototypeDisplaySubController::getDisplayShadowing()
{
	return displayShadowing;
}

bool PrototypeDisplaySubController::getDisplayGround()
{
	return displayGround;
}

bool PrototypeDisplaySubController::getDisplayBoundingVolume()
{
	return displayBoundingVolumes;
}

void PrototypeDisplaySubController::createDisplayPropertiesXML(Prototype* prototype, string& xml) {
	if (prototype->getType() == Prototype_Type::MODEL) {
		xml+= "	<selectbox-parent-option text=\"Rendering\" value=\"rendering\">\n";
		xml+= "		<selectbox-option text=\"" + GUIParser::escapeQuotes("Shader: " + prototype->getShader()) + "\" value=\"rendering.shader\" />\n";
		xml+= "		<selectbox-option text=\"" + GUIParser::escapeQuotes("Distance Shader: " + prototype->getDistanceShader()) + "\" value=\"rendering.distanceshader\" />\n";
		xml+= "	</selectbox-parent-option>\n";
	} else {
		xml+= "	<selectbox-option text=\"Rendering\" value=\"rendering\" />\n";
	}
}

void PrototypeDisplaySubController::setDisplayDetails(Prototype* prototype) {
	editorView->setDetailsContent(
		"<template id=\"details_rendering\" src=\"resources/engine/gui/template_details_rendering.xml\" />\n"
	);

	string shaderXML;
	{
		for (auto& shader: Engine::getRegisteredShader(Engine::ShaderType::SHADERTYPE_OBJECT3D)) {
			shaderXML =
				shaderXML +
				"<dropdown-option text=\"" +
				GUIParser::escapeQuotes(shader) +
				"\" value=\"" +
				GUIParser::escapeQuotes(shader) +
				"\" " +
				(shader == "default"?"selected=\"true\" " : "") +
				"/>\n";
		}
	}

	try {
		// physics
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_rendering"))->getActiveConditions().add("open");
		if (prototype->getType() == Prototype_Type::MODEL) required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_rendering"))->getActiveConditions().add("shaders");

		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("rendering_shader"))->replaceSubNodes(shaderXML, true);
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("rendering_distance_shader"))->replaceSubNodes(shaderXML, true);

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_shader"))->getController()->setValue(MutableString(prototype->getShader()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_distance_shader"))->getController()->setValue(MutableString(prototype->getDistanceShader()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_distanceshader_distance"))->getController()->setValue(MutableString(prototype->getDistanceShaderDistance()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_contributes_shadows"))->getController()->setValue(MutableString(prototype->isContributesShadows() == true?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_receives_shadows"))->getController()->setValue(MutableString(prototype->isReceivesShadows() == true?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_render_groups"))->getController()->setValue(MutableString(prototype->isRenderGroups() == true?"1":""));

	} catch (Exception& exception) {
		Console::println(string("PrototypeDisplaySubController::setDisplayDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypeDisplaySubController::applyDisplayDetails(Prototype* prototype) {
	try {
		prototype->setShader(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_shader"))->getController()->getValue().getString());
		prototype->setDistanceShader(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_distance_shader"))->getController()->getValue().getString());
		prototype->setDistanceShaderDistance(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_distanceshader_distance"))->getController()->getValue().getString()));
		prototype->setContributesShadows(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_contributes_shadows"))->getController()->getValue().getString() == "1");
		prototype->setReceivesShadows(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_receives_shadows"))->getController()->getValue().getString() == "1");
		prototype->setRenderGroups(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendering_render_groups"))->getController()->getValue().getString() == "1");
	} catch (Exception& exception) {
		Console::println(string("PrototypeDisplaySubController::applyDisplayDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypeDisplaySubController::onValueChanged(GUIElementNode* node, Prototype* prototype) {
	for (auto& applyDisplayNode: applyDisplayNodes) {
		if (node->getId() == applyDisplayNode) {
			applyDisplayDetails(prototype);
			break;
		}
	}
	for (auto& reloadOutlinerNode: reloadOuterlinerDisplayNodes) {
		if (node->getId() == reloadOutlinerNode) {
			editorView->reloadTabOutliner();
			break;
		}
	}
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (outlinerNode == "rendering") setDisplayDetails(prototype);
	}
}

void PrototypeDisplaySubController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype)
{
}

void PrototypeDisplaySubController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}
