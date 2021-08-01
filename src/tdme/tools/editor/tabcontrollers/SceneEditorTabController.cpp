#include <tdme/tools/editor/tabcontrollers/SceneEditorTabController.h>

#include <string>

#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/Transformations.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/SceneEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::tools::editor::tabcontrollers::SceneEditorTabController;

using tdme::engine::Transformations;
using tdme::engine::model::RotationOrder;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::SceneLibrary;
using tdme::utilities::Action;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabviews::SceneEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

SceneEditorTabController::SceneEditorTabController(SceneEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->basePropertiesSubController = new BasePropertiesSubController(view->getEditorView(), "scene");
}

SceneEditorTabController::~SceneEditorTabController() {
	delete basePropertiesSubController;
}

SceneEditorTabView* SceneEditorTabController::getView() {
	return view;
}

GUIScreenNode* SceneEditorTabController::getScreenNode()
{
	return screenNode;
}

void SceneEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
}

void SceneEditorTabController::dispose()
{
}

void SceneEditorTabController::save()
{
}

void SceneEditorTabController::saveAs()
{
}

void SceneEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void SceneEditorTabController::onValueChanged(GUIElementNode* node)
{
	if (node->getId() == "dropdown_outliner_add") {
		auto addOutlinerType = node->getController()->getValue().getString();
		// TODO
	} else
	if (node->getId() == "selectbox_outliner") {
		updateDetails(view->getEditorView()->getScreenController()->getOutlinerSelection());
	} else {
		basePropertiesSubController->onValueChanged(node, view->getScene());
	}
}

void SceneEditorTabController::onFocus(GUIElementNode* node) {
	basePropertiesSubController->onFocus(node, view->getScene());
}

void SceneEditorTabController::onUnfocus(GUIElementNode* node) {
	basePropertiesSubController->onUnfocus(node, view->getScene());
}

void SceneEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
	basePropertiesSubController->onContextMenuRequested(node, mouseX, mouseY, view->getScene());
}

void SceneEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	basePropertiesSubController->onActionPerformed(type, node, view->getScene());
}

void SceneEditorTabController::setEntityDetails(const string& entityId) {
	Console::println("SceneEditorTabController::setEntityDetails(): " + entityId);

	auto scene = view->getScene();
	auto entity = scene->getEntity(entityId);
	auto transformations = entity != nullptr?&entity->getTransformations():nullptr;

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_base\" src=\"resources/engine/gui/template_details_base.xml\" />") +
		string("<template id=\"details_transformations\" src=\"resources/engine/gui/template_details_transformation.xml\" />") +
		string("<template id=\"details_reflections\" src=\"resources/engine/gui/template_details_reflection.xml\" />")
	);

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_base"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_name"))->getController()->setValue(entity->getId());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_description"))->getController()->setValue(entity->getDescription());

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_transformations"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_translation_x"))->getController()->setValue(transformations->getTranslation().getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_translation_y"))->getController()->setValue(transformations->getTranslation().getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_translation_z"))->getController()->setValue(transformations->getTranslation().getX());

		if ((entity->getPrototype()->getType()->getGizmoTypeMask() & Gizmo::GIZMOTYPE_ROTATE) == Gizmo::GIZMOTYPE_ROTATE) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_transformations"))->getActiveConditions().add("rotation");
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_rotation_x"))->getController()->setValue(transformations->getRotationAngle(scene->getRotationOrder()->getAxisXIndex()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_rotation_y"))->getController()->setValue(transformations->getRotationAngle(scene->getRotationOrder()->getAxisYIndex()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_rotation_z"))->getController()->setValue(transformations->getRotationAngle(scene->getRotationOrder()->getAxisZIndex()));
		}

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_scale_x"))->getController()->setValue(transformations->getScale().getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_scale_y"))->getController()->setValue(transformations->getScale().getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_scale_z"))->getController()->setValue(transformations->getScale().getX());

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_reflections"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::setAnimationDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void SceneEditorTabController::updateEntityDetails(const string& entityId) {
	Console::println("SceneEditorTabController::updateEntityDetails(): " + entityId);

	auto scene = view->getScene();
	auto entity = scene->getEntity(entityId);
	auto transformations = entity != nullptr?&entity->getTransformations():nullptr;
	if (transformations == nullptr) return;

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_base"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_name"))->getController()->setValue(entity->getId());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_description"))->getController()->setValue(entity->getDescription());

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_transformations"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_translation_x"))->getController()->setValue(transformations->getTranslation().getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_translation_y"))->getController()->setValue(transformations->getTranslation().getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_translation_z"))->getController()->setValue(transformations->getTranslation().getX());

		if ((entity->getPrototype()->getType()->getGizmoTypeMask() & Gizmo::GIZMOTYPE_ROTATE) == Gizmo::GIZMOTYPE_ROTATE) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_rotation_x"))->getController()->setValue(transformations->getRotationAngle(scene->getRotationOrder()->getAxisXIndex()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_rotation_y"))->getController()->setValue(transformations->getRotationAngle(scene->getRotationOrder()->getAxisYIndex()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_rotation_z"))->getController()->setValue(transformations->getRotationAngle(scene->getRotationOrder()->getAxisZIndex()));
		}

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_scale_x"))->getController()->setValue(transformations->getScale().getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_scale_y"))->getController()->setValue(transformations->getScale().getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transformation_scale_z"))->getController()->setValue(transformations->getScale().getX());

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_reflections"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::setAnimationDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void SceneEditorTabController::setOutlinerContent() {

	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Scene") + "\" value=\"" + GUIParser::escapeQuotes("scene") + "\">\n";
	auto scene = view->getScene();
	if (scene != nullptr) {
		basePropertiesSubController->createBasePropertiesXML(scene, xml);
		{
			auto sceneLibrary = scene->getLibrary();
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototypes") + "\" value=\"" + GUIParser::escapeQuotes("scene.prototypes") + "\">\n";
			for (auto i = 0; i < sceneLibrary->getPrototypeCount(); i++) {
				auto prototype = sceneLibrary->getPrototypeAt(i);
				auto icon = getPrototypeIcon(prototype->getType());
				auto prototypeName = prototype->getName();
				xml+= "	<selectbox-option image=\"resources/engine/images/" + icon +"\" text=\"" + GUIParser::escapeQuotes(prototypeName) + "\" value=\"" + GUIParser::escapeQuotes("scene.prototypes." + prototypeName) + "\" />\n";
			}
			xml+= "</selectbox-parent-option>\n";
		}
		{
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Entities") + "\" value=\"" + GUIParser::escapeQuotes("scene.entities") + "\">\n";
			for (auto i = 0; i < scene->getEntityCount(); i++) {
				auto entity = scene->getEntityAt(i);
				auto entityName = entity->getName();
				auto prototype = entity->getPrototype();
				auto icon = getPrototypeIcon(prototype->getType());
				xml+= "	<selectbox-option image=\"resources/engine/images/" + icon + "\" text=\"" + GUIParser::escapeQuotes(entityName) + "\" value=\"" + GUIParser::escapeQuotes("scene.entities." + entityName) + "\" />\n";
			}
			xml+= "</selectbox-parent-option>\n";
		}
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void SceneEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(
		string("<dropdown-option text=\"Property\" value=\"property\" />\n")
	);
}

void SceneEditorTabController::setDetailsContent() {
	view->getEditorView()->setDetailsContent(string());
}

void SceneEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	if (StringTools::startsWith(outlinerNode, "scene.entities.") == true) {
		auto entityId = StringTools::substring(outlinerNode, string("scene.entities.").size());
		setEntityDetails(entityId);
	} else {
		basePropertiesSubController->updateDetails(view->getScene(), outlinerNode);
	}
}

void SceneEditorTabController::unselectEntities() {
	view->getEditorView()->getScreenController()->setOutlinerSelection("scene.entities");
	updateDetails("scene.entities");
}

void SceneEditorTabController::unselectEntity(const string& entityId) {
	unselectEntities();
}

void SceneEditorTabController::selectEntity(const string& entityId) {
	view->getEditorView()->getScreenController()->setOutlinerSelection(string("scene.entities.") + entityId);
	setEntityDetails(entityId);
}
