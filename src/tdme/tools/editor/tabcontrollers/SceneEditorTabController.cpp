#include <tdme/tools/editor/tabcontrollers/SceneEditorTabController.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/scenes/SceneWriter.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Transform.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Math.h>
#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/SceneEditorTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::tools::editor::tabcontrollers::SceneEditorTabController;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::scenes::SceneWriter;
using tdme::engine::model::RotationOrder;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::math::Math;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::SceneEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

SceneEditorTabController::SceneEditorTabController(SceneEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->basePropertiesSubController = make_unique<BasePropertiesSubController>(view->getEditorView(), "scene");
}

SceneEditorTabController::~SceneEditorTabController() {
}

void SceneEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_toolbar"))->getActiveConditions().add("tools");
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_toolbar"))->getActiveConditions().add("snapping");
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_toolbar"))->getActiveConditions().add("scene");
	view->setGridEnabled(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_checkbox_grid"))->getController()->getValue().equals("1"));
}

void SceneEditorTabController::dispose()
{
}

void SceneEditorTabController::onCommand(TabControllerCommand command)
{
	switch (command) {
		case COMMAND_SAVE:
			{
				auto scene = view->getScene();
				if (scene == nullptr) return;

				//
				save(Tools::getPathName(scene->getFileName()), Tools::getFileName(scene->getFileName()));
			}
			break;
		case COMMAND_SAVEAS:
			{
				class OnSceneSave: public virtual Action
				{
				public:
					void performAction() override {
						sceneEditorTabController->save(
							sceneEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
							sceneEditorTabController->popUps->getFileDialogScreenController()->getFileName()
						);
						sceneEditorTabController->popUps->getFileDialogScreenController()->close();
					}

					OnSceneSave(SceneEditorTabController* sceneEditorTabController): sceneEditorTabController(sceneEditorTabController) {
					}

				private:
					SceneEditorTabController* sceneEditorTabController;
				};

				auto scene = view->getScene();
				if (scene == nullptr) return;

				auto fileName = scene->getFileName();
				vector<string> extensions = {
					"tscene"
				};
				popUps->getFileDialogScreenController()->show(
					Tools::getPathName(fileName),
					"Save Scene to: ",
					extensions,
					Tools::getFileName(fileName),
					false,
					new OnSceneSave(this)
				);
			}
			break;
		default:
			showInfoPopUp("Warning", "This command is not supported yet");
			break;
	}
}

void SceneEditorTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	if (StringTools::startsWith(payload, "file:") == false) {
		showInfoPopUp("Warning", "Unknown payload in drop");
	} else {
		auto fileName = StringTools::substring(payload, string("file:").size());
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "gui") == true) {
			vector<string> guiExtensions = {{ "xml" }};
			if (Tools::hasFileExtension(fileName, guiExtensions) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(guiExtensions));
			} else {
				setGUIFileName(fileName);
			}
		} else
		if (Tools::hasFileExtension(fileName, PrototypeReader::getPrototypeExtensions()) == false) {
			showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(PrototypeReader::getPrototypeExtensions()));
		} else {
			auto xScale = static_cast<float>(Engine::getInstance()->getWidth()) / static_cast<float>(screenNode->getScreenWidth());
			auto yScale = static_cast<float>(Engine::getInstance()->getHeight()) / static_cast<float>(screenNode->getScreenHeight());
			int left, top, width, height, offsetX, offsetY;
			if (view->getEditorView()->getCurrentTabViewPort(left, top, width, height, offsetX, offsetY) == true) {
				auto tabMouseX = (mouseX - left) / xScale + offsetX;
				auto tabMouseY = (mouseY - top) / yScale + offsetY;
				if (tabMouseX < 0 || tabMouseX >= width || tabMouseX < 0 || tabMouseY >= height) {
					showInfoPopUp("Warning", "You can not drop a file here");
				} else {
					//
					try {
						// load prototype and mark as non embedded
						auto prototype = unique_ptr<Prototype>(
							PrototypeReader::read(
								Tools::getPathName(fileName),
								Tools::getFileName(fileName)
							)
						);
						prototype->setEmbedded(false);
						// check if we have prototype already in library
						auto libraryPrototype = view->getScene()->getLibrary()->getPrototypeByName(prototype->getName());
						if (libraryPrototype == nullptr) {
							// yep, delete prototype
							libraryPrototype = prototype.release();
							view->addPrototype(libraryPrototype);
						}
						// and place it
						if (view->placeEntity(libraryPrototype, tabMouseX, tabMouseY) == false) {
							showInfoPopUp("Warning", "Could not place prototype entity.");
						}
					} catch (Exception& exception) {
						Console::println("SceneEditorTabController::onDrop(): An error occurred: " + string(exception.what()));
						showInfoPopUp("Warning", string(exception.what()));
					}
				}
			} else {
				showInfoPopUp("Warning", "Could not place prototype entity.");
			}
		}
	}
}

void SceneEditorTabController::save(const string& pathName, const string& fileName)
{
	auto scene = view->getScene();
	if (scene == nullptr) return;

	//
	try {
		SceneWriter::write(
			pathName,
			fileName,
			scene
		);
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::save(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void SceneEditorTabController::updateInfoText(const MutableString& text) {
	required_dynamic_cast<GUITextNode*>(screenNode->getNodeById(view->getTabId() + "_tab_text_info"))->setText(text);
}

void SceneEditorTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void SceneEditorTabController::onChange(GUIElementNode* node)
{
	if (basePropertiesSubController->onChange(node, view->getScene()) == true) return;
	//
	if (node->getId() == "dropdown_outliner_add") {
		auto addOutlinerType = node->getController()->getValue().getString();
		// TODO
	} else
	if (node->getId() == "selectbox_outliner") {
		updateDetails(view->getEditorView()->getScreenController()->getOutlinerSelection());
		vector<string> selectedEntityIds;
		auto outlinerSelection = StringTools::tokenize(view->getEditorView()->getScreenController()->getOutlinerSelection(), "|");
		for (const auto& selectedEntityId: outlinerSelection) {
			if (StringTools::startsWith(selectedEntityId, "scene.entities.") == false) continue;
			selectedEntityIds.push_back(StringTools::substring(selectedEntityId, string("scene.entities.").size()));
		}
		view->selectEntities(selectedEntityIds);
	} else
	if (node->getId() == view->getTabId() + "_tab_button_translate") {
		view->setGizmoType(Gizmo::GIZMOTYPE_TRANSLATE);
		view->updateGizmo();
	} else
	if (node->getId() == view->getTabId() + "_tab_button_rotate") {
		view->setGizmoType(Gizmo::GIZMOTYPE_ROTATE);
		view->updateGizmo();
	} else
	if (node->getId() == view->getTabId() + "_tab_button_scale") {
		view->setGizmoType(Gizmo::GIZMOTYPE_SCALE);
		view->updateGizmo();
	} else
	if (node->getId() == view->getTabId() + "_tab_button_gizmo") {
		view->setGizmoType(Gizmo::GIZMOTYPE_ALL);
		view->updateGizmo();
	} else
	if (node->getId() == view->getTabId() + "_tab_checkbox_grid") {
		view->setGridEnabled(node->getController()->getValue().equals("1"));
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_checkbox_snapping") == true ||
		StringTools::startsWith(node->getId(), view->getTabId() + "_tab_snapping_x") == true ||
		StringTools::startsWith(node->getId(), view->getTabId() + "_tab_snapping_z") == true) {
		view->setSnapping(
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_checkbox_snapping"))->getController()->getValue().equals("1") == true,
			Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_snapping_x"))->getController()->getValue().getString()),
			Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_snapping_z"))->getController()->getValue().getString())
		);
	} else
	if (StringTools::startsWith(node->getId(), "sky.shader.") == true) {
		applySkyShaderDetails(StringTools::substring(node->getId(), string("sky.shader.").size(), node->getId().size()));
	} else {
		for (const auto& applyTranslationNode: applyTranslationNodes) {
			if (node->getId() == applyTranslationNode) {
				//
				try {
					view->applyTranslation(
						Vector3(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_translation_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_translation_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_translation_z"))->getController()->getValue().getString())
						)
					);
				} catch (Exception& exception) {
					Console::println("SceneEditorTabController::onChange(): An error occurred: " + string(exception.what()));
					showInfoPopUp("Warning", string(exception.what()));
				}
				//
				break;
			}
		}
		for (const auto& applyRotationNode: applyRotationNodes) {
			if (node->getId() == applyRotationNode) {
				//
				try {
					view->applyRotation(
						Vector3(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_rotation_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_rotation_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_rotation_z"))->getController()->getValue().getString())
						)
					);
				} catch (Exception& exception) {
					Console::println("SceneEditorTabController::onChange(): An error occurred: " + string(exception.what()));
					showInfoPopUp("Warning", string(exception.what()));
				}
				//
				break;
			}
		}
		for (const auto& applyScaleNode: applyScaleNodes) {
			if (node->getId() == applyScaleNode) {
				//
				try {
					view->applyScale(
						Vector3(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_scale_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_scale_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_scale_z"))->getController()->getValue().getString())
						)
					);
				} catch (Exception& exception) {
					Console::println("SceneEditorTabController::onChange(): An error occurred: " + string(exception.what()));
					showInfoPopUp("Warning", string(exception.what()));
				}
				//
				break;
			}
		}
		for (const auto& applyReflectionEnvironmentMappingNode: applyReflectionEnvironmentMappingNodes) {
			if (node->getId() == applyReflectionEnvironmentMappingNode) {
				//
				try {
					view->applyReflectionEnvironmentMappingId(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("reflection_environmentmap"))->getController()->getValue().getString());
				} catch (Exception& exception) {
					Console::println("SceneEditorTabController::onChange(): An error occurred: " + string(exception.what()));
					showInfoPopUp("Warning", string(exception.what()));
				}
				//
				break;
			}
		}
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "scene.lights.") == true) {
			auto lightIdx = Integer::parse(StringTools::substring(outlinerNode, string("scene.lights.light").size()));
			for (const auto& applyLightNode: applyLightNodes) {
				if (node->getId() == applyLightNode) {
					applyLightDetails(lightIdx);
					//
					break;
				}
			}
		}
		//
	}
}

void SceneEditorTabController::onFocus(GUIElementNode* node) {
	if (basePropertiesSubController->onFocus(node, view->getScene()) == true) return;
}

void SceneEditorTabController::onUnfocus(GUIElementNode* node) {
	if (basePropertiesSubController->onUnfocus(node, view->getScene()) == true) return;
	//
	if (node->getId() == "tdme.entities.rename_input") {
		renameEntity();
	} else {
		for (const auto& applyBaseNode: applyBaseNodes) {
			if (node->getId() == applyBaseNode) {
				//
				try {
					auto name = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_name"))->getController()->getValue().getString();
					if (name.empty() == true) throw ExceptionBase("Please enter a name");
					if (view->applyBase(
							name,
							required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_description"))->getController()->getValue().getString()
						) == false) {
						throw ExceptionBase("Could not rename entity");
					}
				} catch (Exception& exception) {
					Console::println("SceneEditorTabController::onChange(): An error occurred: " + string(exception.what()));
					showInfoPopUp("Warning", string(exception.what()));
				}
				//
				break;
			}
		}
	}
}

void SceneEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (outlinerNode == "scene.lights") {
			// clear
			popUps->getContextMenuScreenController()->clear();
			{
				// add light
				class OnAddLightAction: public virtual Action
				{
				public:
					void performAction() override {
						auto scene = sceneEditorTabController->view->getScene();
						if (scene == nullptr) return;
						auto light = scene->addLight();
						if (light == nullptr) return;
						light->setEnabled(true);
						//
						sceneEditorTabController->view->getEditorView()->reloadTabOutliner("scene.lights.light" + to_string(light->getId()));
					}
					OnAddLightAction(SceneEditorTabController* sceneEditorTabController): sceneEditorTabController(sceneEditorTabController) {
					}
				private:
					SceneEditorTabController* sceneEditorTabController;
				};
				popUps->getContextMenuScreenController()->addMenuItem("Add light", "contextmenu_add", new OnAddLightAction(this));
			}
			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (StringTools::startsWith(outlinerNode, "scene.lights.") == true) {
			// clear
			popUps->getContextMenuScreenController()->clear();
			{
				auto lightIdx = Integer::parse(StringTools::substring(outlinerNode, string("scene.lights.light").size()));
				auto scene = view->getScene();
				if (scene == nullptr) return;

				//
				if (scene->getLightCount() < 2) return;

				// remove light
				class OnDeleteLightAction: public virtual Action
				{
				public:
					void performAction() override {
						auto scene = sceneEditorTabController->view->getScene();
						if (scene == nullptr) return;
						scene->removeLightAt(lightIdx);
						//
						sceneEditorTabController->view->getEditorView()->reloadTabOutliner("scene.lights");
					}
					OnDeleteLightAction(SceneEditorTabController* sceneEditorTabController, int lightIdx): sceneEditorTabController(sceneEditorTabController), lightIdx(lightIdx) {
					}
				private:
					SceneEditorTabController* sceneEditorTabController;
					int lightIdx;
				};
				popUps->getContextMenuScreenController()->addMenuItem("Delete light", "contextmenu_delete", new OnDeleteLightAction(this, lightIdx));
			}
			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (StringTools::startsWith(outlinerNode, "scene.entities.") == true) {
			// clear
			popUps->getContextMenuScreenController()->clear();
			{
				// rename
				class OnCenterAction: public virtual Action
				{
				public:
					void performAction() override {
						auto outlinerSelection = StringTools::tokenize(sceneEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection(), "|");
						if (outlinerSelection.size() != 1) return;
						string selectedEntityId;
						if (StringTools::startsWith(outlinerSelection[0], "scene.entities.") == false) return;
						selectedEntityId = StringTools::substring(outlinerSelection[0], string("scene.entities.").size());
						sceneEditorTabController->startRenameEntity(selectedEntityId);
					}
					OnCenterAction(SceneEditorTabController* sceneEditorTabController): sceneEditorTabController(sceneEditorTabController) {
					}
				private:
					SceneEditorTabController* sceneEditorTabController;
				};
				popUps->getContextMenuScreenController()->addMenuItem("Rename", "contextmenu_rename", new OnCenterAction(this));
			}
			{
				// center
				class OnCenterAction: public virtual Action
				{
				public:
					void performAction() override {
						sceneEditorTabController->view->centerEntities();
					}
					OnCenterAction(SceneEditorTabController* sceneEditorTabController): sceneEditorTabController(sceneEditorTabController) {
					}
				private:
					SceneEditorTabController* sceneEditorTabController;
				};
				popUps->getContextMenuScreenController()->addMenuItem("Center", "contextmenu_center", new OnCenterAction(this));
			}
			{
				// select same
				class OnSelectSameAction: public virtual Action
				{
				public:
					void performAction() override {
						sceneEditorTabController->view->selectSameEntities();
					}
					OnSelectSameAction(SceneEditorTabController* sceneEditorTabController): sceneEditorTabController(sceneEditorTabController) {
					}
				private:
					SceneEditorTabController* sceneEditorTabController;
				};
				popUps->getContextMenuScreenController()->addMenuItem("Select same", "contextmenu_same", new OnSelectSameAction(this));
			}
			{
				// open prototype
				class OnOpenPrototype: public virtual Action
				{
				public:
					void performAction() override {
						sceneEditorTabController->view->openPrototype();
					}
					OnOpenPrototype(SceneEditorTabController* sceneEditorTabController): sceneEditorTabController(sceneEditorTabController) {
					}
				private:
					SceneEditorTabController* sceneEditorTabController;
				};
				popUps->getContextMenuScreenController()->addMenuItem("Open prototype", "contextmenu_openprototype", new OnOpenPrototype(this));
			}
			{
				// replace prototype
				class OnReplacePrototypeAction: public virtual Action
				{
				public:
					void performAction() override {
						sceneEditorTabController->onReplacePrototype();
					}
					OnReplacePrototypeAction(SceneEditorTabController* sceneEditorTabController): sceneEditorTabController(sceneEditorTabController) {
					}
				private:
					SceneEditorTabController* sceneEditorTabController;
				};
				popUps->getContextMenuScreenController()->addMenuItem("Replace prototype", "contextmenu_replaceprototype", new OnReplacePrototypeAction(this));
			}
			{
				// jump to prototype
				class JumpToPrototypeAction: public virtual Action
				{
				public:
					void performAction() override {
						auto outlinerSelection = StringTools::tokenize(sceneEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection(), "|");
						if (outlinerSelection.size() != 1) return;
						string selectedEntityId;
						if (StringTools::startsWith(outlinerSelection[0], "scene.entities.") == false) return;
						auto scene = sceneEditorTabController->view->getScene();
						selectedEntityId = StringTools::substring(outlinerSelection[0], string("scene.entities.").size());
						auto sceneEntity = scene->getEntity(selectedEntityId);
						if (sceneEntity == nullptr) return;
						sceneEditorTabController->view->getEditorView()->getScreenController()->setOutlinerSelection("scene.prototypes." + GUIParser::escape(to_string(sceneEntity->getPrototype()->getId())));
						sceneEditorTabController->updateDetails(sceneEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection());
					}
					JumpToPrototypeAction(SceneEditorTabController* sceneEditorTabController): sceneEditorTabController(sceneEditorTabController) {
					}
				private:
					SceneEditorTabController* sceneEditorTabController;
				};
				popUps->getContextMenuScreenController()->addMenuItem("Jump to prototype", "contextmenu_jumptoprototype", new JumpToPrototypeAction(this));
			}
			{
				// delete
				class OnDeleteAction: public virtual Action
				{
				public:
					void performAction() override {
						sceneEditorTabController->view->removeEntities();
					}
					OnDeleteAction(SceneEditorTabController* sceneEditorTabController): sceneEditorTabController(sceneEditorTabController) {
					}
				private:
					SceneEditorTabController* sceneEditorTabController;
				};
				popUps->getContextMenuScreenController()->addMenuSeparator();
				popUps->getContextMenuScreenController()->addMenuItem("Delete", "contextmenu_delete", new OnDeleteAction(this));
			}
			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		}
	}
	//
	basePropertiesSubController->onContextMenuRequest(node, mouseX, mouseY, view->getScene());
}

void SceneEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void SceneEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void SceneEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	//
	if (basePropertiesSubController->onAction(type, node, view->getScene()) == true) return;
	//
	if (type != GUIActionListenerType::PERFORMED) return;
	if (node->getId() == view->getTabId() + "_tab_button_play") {
		view->runScene();
	} else
	if (node->getId() == view->getTabId() + "_tab_button_stop") {
		view->stopScene();
	} else
	if (node->getId() == "menu_view_scene_run") {
		view->runScene();
	} else
	if (node->getId() == "menu_view_scene_stop") {
		view->stopScene();
	}
	if (node->getId() == "tdme.entities.rename_input") {
		renameEntity();
	} else
	if (StringTools::startsWith(node->getId(), "sky.shader.") == true &&
		StringTools::endsWith(node->getId(), "_color_edit") == true) {
		//
		auto parameterName = StringTools::substring(node->getId(), string("sky.shader.").size(), node->getId().size() - string("_color_edit").size());
		auto parameter = view->getScene()->getSkyShaderParameters().getShaderParameter(parameterName);
		auto color4 = parameter.getColor4Value();
		//
		class OnColorChangeAction: public virtual Action
		{
		public:
			void performAction() override {
				//
				auto view = sceneEditorTabController->getView();
				auto scene = view->getScene();
				auto shaderParameters = scene->getSkyShaderParameters();
				auto parameter = shaderParameters.getShaderParameter(parameterName);
				auto color4 = sceneEditorTabController->popUps->getColorPickerScreenController()->getColor();
				shaderParameters.setShaderParameter(parameterName, color4);
				try {
					required_dynamic_cast<GUIImageNode*>(sceneEditorTabController->screenNode->getNodeById("sky.shader." + parameterName + "_color"))->setEffectColorMul(color4);
				} catch (Exception& exception) {
					Console::println("SceneEditorTabController::onAction(): An error occurred: " + string(exception.what()));
					sceneEditorTabController->showInfoPopUp("Warning", string(exception.what()));
				}
				//
				scene->setSkyShaderParameters(shaderParameters);
				view->applySkyShaderParameters();
			}
			OnColorChangeAction(SceneEditorTabController* sceneEditorTabController, const string& parameterName): sceneEditorTabController(sceneEditorTabController), parameterName(parameterName) {
			}
		private:
			SceneEditorTabController* sceneEditorTabController;
			string parameterName;
		};
		//
		popUps->getColorPickerScreenController()->show(color4, new OnColorChangeAction(this, parameterName));
		//
	} else
	if (node->getId() == "gui_open") {
		class OnLoadGUIAction: public virtual Action
		{
		public:
			void performAction() override {
				try {
					sceneEditorTabController->setGUIFileName(
						sceneEditorTabController->popUps->getFileDialogScreenController()->getPathName() +
						"/" +
						sceneEditorTabController->popUps->getFileDialogScreenController()->getFileName()
					);
				} catch (Exception& exception) {
					Console::println("OnLoadGUIAction::performAction(): An error occurred: " + string(exception.what()));
					sceneEditorTabController->showInfoPopUp("Warning", string(exception.what()));
				}
				sceneEditorTabController->setGUIDetails();
				sceneEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
			}

			/**
			 * Public constructor
			 * @param sceneEditorTabController scene editor tab controller
			 */
			OnLoadGUIAction(SceneEditorTabController* sceneEditorTabController)
				: sceneEditorTabController(sceneEditorTabController) {
				//
			}

		private:
			SceneEditorTabController* sceneEditorTabController;
		};

		popUps->getFileDialogScreenController()->show(
			string(),
			"Load GUI from: ",
			{{ "xml" }},
			string(),
			true,
			new OnLoadGUIAction(this)
		);
	} else
	if (node->getId() == "gui_remove") {
		auto scene = view->getScene();
		unsetGUIFileName();
	} else
	if (node->getId() == "gui_browseto") {
		auto scene = view->getScene();
		if (scene->getGUIFileName().empty() == true) {
			showInfoPopUp("Browse To", "Nothing to browse to");
		} else {
			view->getEditorView()->getScreenController()->browseTo(scene->getGUIFileName());
		}
	} else
	if (node->getId() == "prototype_place") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		auto prototypeId = Integer::parse(StringTools::substring(outlinerNode, string("scene.prototypes.").size()));
		auto scene = view->getScene();
		auto sceneLibrary = scene->getLibrary();
		auto prototype = sceneLibrary->getPrototype(prototypeId);
		if (prototype != nullptr) view->setPlaceEntityMode(prototype);
	} else
	if (node->getId() == "light_ambient_ambient_edit" ||
		node->getId() == "light_spot_ambient_edit" ||
		node->getId() == "light_directional_ambient_edit") {
		class OnColorChangeAction: public virtual Action
		{
		public:
			void performAction() override {
				auto scene = sceneEditorTabController->view->getScene();
				if (scene == nullptr) return;
				auto light = scene->getLightAt(lightIdx);
				if (scene == nullptr) return;
				light->setAmbient(sceneEditorTabController->popUps->getColorPickerScreenController()->getColor());
				sceneEditorTabController->updateLightDetails(lightIdx);
			}
			OnColorChangeAction(SceneEditorTabController* sceneEditorTabController, int lightIdx): sceneEditorTabController(sceneEditorTabController), lightIdx(lightIdx) {
			}
		private:
			SceneEditorTabController* sceneEditorTabController;
			int lightIdx;
		};
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "scene.lights.") == true) {
			auto lightIdx = Integer::parse(StringTools::substring(outlinerNode, string("scene.lights.light").size()));
			auto scene = view->getScene();
			if (scene == nullptr) return;
			auto light = scene->getLightAt(lightIdx);
			if (light == nullptr) return;
			popUps->getColorPickerScreenController()->show(light->getAmbient(), new OnColorChangeAction(this, lightIdx));
		}
	} else
	if (node->getId() == "light_ambient_diffuse_edit" ||
		node->getId() == "light_spot_diffuse_edit" ||
		node->getId() == "light_directional_diffuse_edit") {
		class OnColorChangeAction: public virtual Action
		{
		public:
			void performAction() override {
				auto scene = sceneEditorTabController->view->getScene();
				if (scene == nullptr) return;
				auto light = scene->getLightAt(lightIdx);
				if (scene == nullptr) return;
				light->setDiffuse(sceneEditorTabController->popUps->getColorPickerScreenController()->getColor());
				sceneEditorTabController->updateLightDetails(lightIdx);
			}
			OnColorChangeAction(SceneEditorTabController* sceneEditorTabController, int lightIdx): sceneEditorTabController(sceneEditorTabController), lightIdx(lightIdx) {
			}
		private:
			SceneEditorTabController* sceneEditorTabController;
			int lightIdx;
		};
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "scene.lights.") == true) {
			auto lightIdx = Integer::parse(StringTools::substring(outlinerNode, string("scene.lights.light").size()));
			auto scene = view->getScene();
			if (scene == nullptr) return;
			auto light = scene->getLightAt(lightIdx);
			if (light == nullptr) return;
			popUps->getColorPickerScreenController()->show(light->getDiffuse(), new OnColorChangeAction(this, lightIdx));
		}
	} else
	if (node->getId() == "light_ambient_specular_edit" ||
		node->getId() == "light_spot_specular_edit" ||
		node->getId() == "light_directional_specular_edit") {
		class OnColorChangeAction: public virtual Action
		{
		public:
			void performAction() override {
				auto scene = sceneEditorTabController->view->getScene();
				if (scene == nullptr) return;
				auto light = scene->getLightAt(lightIdx);
				if (scene == nullptr) return;
				light->setSpecular(sceneEditorTabController->popUps->getColorPickerScreenController()->getColor());
				sceneEditorTabController->updateLightDetails(lightIdx);
			}
			OnColorChangeAction(SceneEditorTabController* sceneEditorTabController, int lightIdx): sceneEditorTabController(sceneEditorTabController), lightIdx(lightIdx) {
			}
		private:
			SceneEditorTabController* sceneEditorTabController;
			int lightIdx;
		};
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "scene.lights.") == true) {
			auto lightIdx = Integer::parse(StringTools::substring(outlinerNode, string("scene.lights.light").size()));
			auto scene = view->getScene();
			if (scene == nullptr) return;
			auto light = scene->getLightAt(lightIdx);
			if (light == nullptr) return;
			popUps->getColorPickerScreenController()->show(light->getSpecular(), new OnColorChangeAction(this, lightIdx));
		}
	}
}

void SceneEditorTabController::setRunButtonMode(bool running) {
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_toolbar"))->getActiveConditions().remove("running");
	if (running == true) required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_toolbar"))->getActiveConditions().add("running");
}

void SceneEditorTabController::setSkyShaderDetails() {
	view->getEditorView()->setDetailsContent(
		"<template id=\"details_sky\" src=\"resources/engine/gui/template_details_sky.xml\" />\n"
	);
	//
	string xml;
	auto scene = view->getScene();
	for (const auto& parameterName: Engine::getShaderParameterNames("sky")) {
		auto parameterDefaults = Engine::getDefaultShaderParameter("sky", parameterName);
		if (parameterDefaults == nullptr) continue;
		auto parameter = scene->getSkyShaderParameters().getShaderParameter(parameterName);
		switch (parameter.getType()) {
			case ShaderParameter::TYPE_FLOAT:
				{
					auto parameterValue = parameter.getValueAsString();
					xml+=
						"<template name=\"" +
						GUIParser::escape(parameterName) + "\" " +
						"id=\"" + GUIParser::escape("sky.shader." + parameterName) + "\" " +
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
						"id=\"" + GUIParser::escape("sky.shader." + parameterName) + "\" " +
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
						"id=\"" + GUIParser::escape("sky.shader." + parameterName) + "\" " +
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
						"id=\"" + GUIParser::escape("sky.shader." + parameterName) + "\" " +
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
						"id=\"" + GUIParser::escape("sky.shader." + parameterName) + "\" " +
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
						"id=\"" + GUIParser::escape("sky.shader." + parameterName) + "\" " +
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
						"id=\"" + GUIParser::escape("sky.shader." + parameterName) + "\" " +
						"src=\"resources/engine/gui/template_details_rendering_shader_color4.xml\" " +
						"/>\n";
				}
				break;
			case ShaderParameter::TYPE_NONE:
				break;
		}
	}
	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_sky"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("rendering_shader_details"))->replaceSubNodes(xml, false);
		//
		for (const auto& parameterName: Engine::getShaderParameterNames("sky")) {
			auto parameter = scene->getSkyShaderParameters().getShaderParameter(parameterName);
			switch (parameter.getType()) {
				case ShaderParameter::TYPE_COLOR4:
					{
						auto color4 = parameter.getColor4Value();
						required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_color"))->setEffectColorMul(color4);
					}
					break;
				default:
					break;
			}
		}
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::setSkyShaderDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void SceneEditorTabController::applySkyShaderDetails(const string& parameterName) {
	//
	auto scene = view->getScene();
	auto shaderParameters = scene->getSkyShaderParameters();
	//
	try {
		auto parameter = shaderParameters.getShaderParameter(parameterName);
		switch (parameter.getType()) {
			case ShaderParameter::TYPE_FLOAT:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName))->getController()->getValue().getString())
					)
				);
				break;
			case ShaderParameter::TYPE_INTEGER:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName))->getController()->getValue().getString())
					)
				);
				break;
			case ShaderParameter::TYPE_BOOLEAN:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName))->getController()->getValue().getString() == "1"
					)
				);
				break;
			case ShaderParameter::TYPE_VECTOR2:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Vector2(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_y"))->getController()->getValue().getString())
						)
					)
				);
				break;
			case ShaderParameter::TYPE_VECTOR3:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Vector3(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_z"))->getController()->getValue().getString())
						)
					)
				);
				break;
			case ShaderParameter::TYPE_VECTOR4:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Vector4(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_z"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_w"))->getController()->getValue().getString())
						)
					)
				);
				break;
			case ShaderParameter::TYPE_COLOR4:
				shaderParameters.setShaderParameter(
					parameterName,
					ShaderParameter(
						Color4(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_z"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sky.shader." + parameterName + "_w"))->getController()->getValue().getString())
						)
					)
				);
				break;
			case ShaderParameter::TYPE_NONE:
				break;
		}
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::applySkyShaderDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
	//
	scene->setSkyShaderParameters(shaderParameters);
	view->applySkyShaderParameters();
}

void SceneEditorTabController::setGUIDetails() {
	auto scene = view->getScene();

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_gui\" src=\"resources/engine/gui/template_details_gui.xml\" />")
	);

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_gui"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("gui"))->setSource(scene->getGUIFileName());
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("gui"))->setTooltip(scene->getGUIFileName());
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::setGUIDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void SceneEditorTabController::setGUIFileName(const string& fileName) {
	auto scene = view->getScene();
	if (scene == nullptr) return;
	scene->setGUIFileName(fileName);
	setGUIDetails();
}

void SceneEditorTabController::unsetGUIFileName() {
	auto scene = view->getScene();
	if (scene == nullptr) return;
	scene->setGUIFileName(string());
	setGUIDetails();
}

void SceneEditorTabController::setLightDetails(int lightIdx) {
	auto scene = view->getScene();
	if (scene == nullptr) return;
	auto light = scene->getLightAt(lightIdx);
	if (light == nullptr) return;
	enum LightType { LIGHTTYPE_AMBIENT, LIGHTTYPE_SPOTLIGHT, LIGHTTYPE_DIRECTIONAL };
	LightType lightType;
	if (Math::abs(light->getPosition().getW()) < Math::EPSILON) lightType = LIGHTTYPE_DIRECTIONAL; else
	if (Math::abs(light->getSpotExponent()) > Math::EPSILON) lightType = LIGHTTYPE_SPOTLIGHT; else
		lightType = LIGHTTYPE_AMBIENT;

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_light\" src=\"resources/engine/gui/template_details_light.xml\" />")
	);

	//
	try {
		//
		auto spotDirection = light->getSpotDirection().computeLengthSquared() < Math::square(Math::EPSILON)?Vector3(0.0f, -1.0f, 1.0f):light->getSpotDirection().clone().normalize();

		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_ambient_constant_attenuation"))->getController()->setValue(MutableString(light->getConstantAttenuation()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_ambient_linear_attenuation"))->getController()->setValue(MutableString(light->getLinearAttenuation()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_ambient_quadratic_attenuation"))->getController()->setValue(MutableString(light->getQuadraticAttenuation()));

		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_constant_attenuation"))->getController()->setValue(MutableString(light->getConstantAttenuation()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_linear_attenuation"))->getController()->setValue(MutableString(light->getLinearAttenuation()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_quadratic_attenuation"))->getController()->setValue(MutableString(light->getQuadraticAttenuation()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_position_x"))->getController()->setValue(MutableString(light->getPosition().getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_position_y"))->getController()->setValue(MutableString(light->getPosition().getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_position_z"))->getController()->setValue(MutableString(light->getPosition().getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_direction_x"))->getController()->setValue(MutableString(spotDirection.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_direction_y"))->getController()->setValue(MutableString(spotDirection.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_direction_z"))->getController()->setValue(MutableString(spotDirection.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_cutoff"))->getController()->setValue(MutableString(light->getSpotCutOff()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_exponent"))->getController()->setValue(MutableString(light->getSpotExponent()));

		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_constant_attenuation"))->getController()->setValue(MutableString(light->getConstantAttenuation()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_linear_attenuation"))->getController()->setValue(MutableString(light->getLinearAttenuation()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_quadratic_attenuation"))->getController()->setValue(MutableString(light->getQuadraticAttenuation()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_direction_x"))->getController()->setValue(MutableString(spotDirection.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_direction_y"))->getController()->setValue(MutableString(spotDirection.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_direction_z"))->getController()->setValue(MutableString(spotDirection.getZ()));

		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_light"))->getActiveConditions().add("open");
		switch (lightType) {
			case LIGHTTYPE_AMBIENT:
				{
					required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_type"))->getController()->setValue(MutableString(4));
					required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_type_details"))->getActiveConditions().set("ambient");
					break;
				}
			case LIGHTTYPE_SPOTLIGHT:
				{
					required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_type"))->getController()->setValue(MutableString(2));
					required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_type_details"))->getActiveConditions().set("spot");
					break;
				}
			case LIGHTTYPE_DIRECTIONAL:
				{
					required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_type"))->getController()->setValue(MutableString(3));
					required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_type_details"))->getActiveConditions().set("directional");
					break;
				}
		}
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::setLightDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	updateLightDetails(lightIdx);
}

void SceneEditorTabController::updateLightDetails(int lightIdx) {
	auto scene = view->getScene();
	if (scene == nullptr) return;
	auto light = scene->getLightAt(lightIdx);
	if (light == nullptr) return;

	try {
		//
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("light_ambient_ambient"))->setEffectColorMul(Color4(light->getAmbient()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("light_ambient_diffuse"))->setEffectColorMul(Color4(light->getDiffuse()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("light_ambient_specular"))->setEffectColorMul(Color4(light->getSpecular()));

		//
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("light_spot_ambient"))->setEffectColorMul(Color4(light->getAmbient()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("light_spot_diffuse"))->setEffectColorMul(Color4(light->getDiffuse()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("light_spot_specular"))->setEffectColorMul(Color4(light->getSpecular()));

		//
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("light_directional_ambient"))->setEffectColorMul(Color4(light->getAmbient()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("light_directional_diffuse"))->setEffectColorMul(Color4(light->getDiffuse()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("light_directional_specular"))->setEffectColorMul(Color4(light->getSpecular()));
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::updateLightDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	view->updateLights();
}

void SceneEditorTabController::applyLightDetails(int lightIdx) {
	//
	auto scene = view->getScene();
	if (scene == nullptr) return;
	auto light = scene->getLightAt(lightIdx);
	if (light == nullptr) return;

	//
	try {
		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_light"))->getActiveConditions().add("open");
		switch (Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_type"))->getController()->getValue().getString())) {
			case 4:
				//ambient
				{
					//
					light->setConstantAttenuation(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_ambient_constant_attenuation"))->getController()->getValue().getString()));
					light->setLinearAttenuation(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_ambient_linear_attenuation"))->getController()->getValue().getString()));
					light->setQuadraticAttenuation(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_ambient_quadratic_attenuation"))->getController()->getValue().getString()));
					light->setPosition(Vector4());
					light->setSpotDirection(Vector3());
					light->setSpotCutOff(180.0f);
					light->setSpotExponent(0.0f);
					break;
				}
			case 2:
				// spot light
				{
					//
					light->setConstantAttenuation(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_constant_attenuation"))->getController()->getValue().getString()));
					light->setLinearAttenuation(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_linear_attenuation"))->getController()->getValue().getString()));
					light->setQuadraticAttenuation(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_quadratic_attenuation"))->getController()->getValue().getString()));
					light->setPosition(
						Vector4(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_position_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_position_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_position_z"))->getController()->getValue().getString()),
							1.0f
						)
					);
					light->setSpotDirection(
						Vector3(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_direction_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_direction_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_direction_z"))->getController()->getValue().getString())
						).normalize()
					);
					light->setSpotCutOff(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_cutoff"))->getController()->getValue().getString()));
					light->setSpotExponent(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_spot_exponent"))->getController()->getValue().getString()));
					break;
				}
			case 3:
				// directional
				{
					//
					light->setConstantAttenuation(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_constant_attenuation"))->getController()->getValue().getString()));
					light->setLinearAttenuation(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_linear_attenuation"))->getController()->getValue().getString()));
					light->setQuadraticAttenuation(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_quadratic_attenuation"))->getController()->getValue().getString()));
					light->setPosition(
						Vector4(
							light->getPosition().getX(),
							light->getPosition().getY(),
							light->getPosition().getZ(),
							0.0f
						)
					);
					light->setSpotDirection(
						Vector3(
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_direction_x"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_direction_y"))->getController()->getValue().getString()),
							Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("light_directional_direction_z"))->getController()->getValue().getString())
						).normalize()
					);
					light->setSpotCutOff(180.0f);
					light->setSpotExponent(0.0f);
					break;
				}
		}
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::applyLightDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	view->updateLights();
}

void SceneEditorTabController::setPrototypeDetails() {
	auto scene = view->getScene();

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_prototype\" src=\"resources/engine/gui/template_details_prototype.xml\" />")
	);

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_prototype"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::setEntityDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void SceneEditorTabController::updateReflectionEnvironmentMappingDetailsDropDown(const string& selectedReflectionEnvironmentMappingId) {
	auto scene = view->getScene();
	if (scene == nullptr) return;

	string reflectionEnvironmentMappingIdsXML =
		string() + "<dropdown-option text=\"<None>\" value=\"\" " + (selectedReflectionEnvironmentMappingId.empty() == true?"selected=\"true\" ":"") + " />\n";
	for (auto& environmentMappingId: scene->getEnvironmentMappingIds()) {
		reflectionEnvironmentMappingIdsXML+=
			"<dropdown-option text=\"" +
			GUIParser::escape(environmentMappingId) +
			"\" value=\"" +
			GUIParser::escape(environmentMappingId) +
			"\" " +
			(selectedReflectionEnvironmentMappingId == environmentMappingId?"selected=\"true\" ":"") +
			" />\n";
	}

	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("reflection_environmentmap"))->replaceSubNodes(reflectionEnvironmentMappingIdsXML, true);
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::updateReflectionEnvironmentMappingDetailsDropDown(): An error occurred: " + string(exception.what()));
	}
}

void SceneEditorTabController::setEntityDetails(const string& entityId) {
	auto scene = view->getScene();
	auto entity = scene->getEntity(entityId);
	if (entity == nullptr) return;

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_base\" src=\"resources/engine/gui/template_details_base.xml\" />") +
		string("<template id=\"details_transform\" src=\"resources/engine/gui/template_details_transform.xml\" />") +
		string("<template id=\"details_reflections\" src=\"resources/engine/gui/template_details_reflection.xml\" />")
	);

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_base"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_transform"))->getActiveConditions().add("open");
		if ((entity->getPrototype()->getType()->getGizmoTypeMask() & Gizmo::GIZMOTYPE_ROTATE) == Gizmo::GIZMOTYPE_ROTATE) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_transform"))->getActiveConditions().add("rotation");
		}
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_reflections"))->getActiveConditions().add("open");

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_name"))->getController()->setValue(entity->getId());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_description"))->getController()->setValue(entity->getDescription());
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::setEntityDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	updateReflectionEnvironmentMappingDetailsDropDown(entity->getReflectionEnvironmentMappingId());
	updateEntityDetails(entity->getTransform());
}

void SceneEditorTabController::setEntityDetailsMultiple(const Vector3& pivot, const string& selectedReflectionEnvironmentMappingId) {
	auto scene = view->getScene();

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_transform\" src=\"resources/engine/gui/template_details_transform.xml\" />") +
		string("<template id=\"details_reflections\" src=\"resources/engine/gui/template_details_reflection.xml\" />")
	);

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_transform"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_transform"))->getActiveConditions().add("rotation");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_reflections"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::setEntityDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	updateReflectionEnvironmentMappingDetailsDropDown(selectedReflectionEnvironmentMappingId);
	updateEntityDetails(
		pivot,
		Vector3(),
		Vector3(1.0f, 1.0f, 1.0f)
	);
}

void SceneEditorTabController::updateEntityDetails(const Transform& transform) {
	auto scene = view->getScene();
	updateEntityDetails(
		transform.getTranslation(),
		Vector3(
			transform.getRotationAngle(scene->getRotationOrder()->getAxisXIndex()),
			transform.getRotationAngle(scene->getRotationOrder()->getAxisYIndex()),
			transform.getRotationAngle(scene->getRotationOrder()->getAxisZIndex())
		),
		transform.getScale()
	);

}

void SceneEditorTabController::updateEntityDetails(const Vector3& translation, const Vector3& rotation, const Vector3& scale) {
	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_translation_x"))->getController()->setValue(translation.getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_translation_y"))->getController()->setValue(translation.getY());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_translation_z"))->getController()->setValue(translation.getZ());

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_rotation_x"))->getController()->setValue(rotation.getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_rotation_y"))->getController()->setValue(rotation.getY());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_rotation_z"))->getController()->setValue(rotation.getZ());

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_scale_x"))->getController()->setValue(scale.getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_scale_y"))->getController()->setValue(scale.getY());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("transform_scale_z"))->getController()->setValue(scale.getZ());
	} catch (Exception& exception) {
		Console::println("SceneEditorTabController::updateEntityDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void SceneEditorTabController::setOutlinerContent() {

	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Scene") + "\" value=\"" + GUIParser::escape("scene") + "\">\n";
	auto scene = view->getScene();
	if (scene != nullptr) {
		basePropertiesSubController->createBasePropertiesXML(scene, xml);
		xml+= "	<selectbox-option image=\"resources/engine/images/gui.png\" text=\"" + GUIParser::escape("GUI") + "\" value=\"" + GUIParser::escape("scene.gui") + "\" />\n";
		xml+= "	<selectbox-option image=\"resources/engine/images/sky.png\" text=\"Sky\" value=\"scene.sky\" />\n";
		{
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Lights") + "\" value=\"" + GUIParser::escape("scene.lights") + "\">\n";
			auto i = 0;
			for (auto light: scene->getLights()) {
				xml+= "	<selectbox-option image=\"resources/engine/images/light.png\" text=\"" + GUIParser::escape("Light " + to_string(i)) + "\" id=\"" + GUIParser::escape("scene.lights.light" + to_string(i)) + "\" value=\"" + GUIParser::escape("scene.lights.light" + to_string(i)) + "\" />\n";
				i++;
			}
			xml+= "</selectbox-parent-option>\n";
		}
		{
			auto sceneLibrary = scene->getLibrary();
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Prototypes") + "\" value=\"" + GUIParser::escape("scene.prototypes") + "\">\n";
			for (auto prototype: sceneLibrary->getPrototypes()) {
				auto icon = getPrototypeIcon(prototype->getType());
				auto prototypeId = prototype->getId();
				auto prototypeName = prototype->getName();
				xml+= "	<selectbox-option image=\"resources/engine/images/" + icon +"\" text=\"" + GUIParser::escape(prototypeName) + "\" value=\"" + GUIParser::escape("scene.prototypes." + to_string(prototypeId)) + "\" />\n";
			}
			xml+= "</selectbox-parent-option>\n";
		}
		{
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Entities") + "\" value=\"" + GUIParser::escape("scene.entities") + "\">\n";
			for (auto entity: scene->getEntities()) {
				auto entityName = entity->getName();
				auto prototype = entity->getPrototype();
				auto icon = getPrototypeIcon(prototype->getType());
				if (prototype->isRenderGroups() == true) continue;
				xml+= "	<selectbox-option image=\"resources/engine/images/" + icon + "\" text=\"" + GUIParser::escape(entityName) + "\" id=\"" + GUIParser::escape("scene.entities." + entityName) + "\" value=\"" + GUIParser::escape("scene.entities." + entityName) + "\" />\n";
			}
			xml+= "</selectbox-parent-option>\n";
		}
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void SceneEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(string());
}

void SceneEditorTabController::setDetailsContent() {
	view->getEditorView()->setDetailsContent(string());
}

void SceneEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	if (outlinerNode == "scene.gui") {
		setGUIDetails();
	} else
	if (outlinerNode == "scene.sky") {
		setSkyShaderDetails();
	} else
	if (StringTools::startsWith(outlinerNode, "scene.lights.") == true) {
		auto lightIdx = Integer::parse(StringTools::substring(outlinerNode, string("scene.lights.light").size()));
		setLightDetails(lightIdx);
	} else
	if (StringTools::startsWith(outlinerNode, "scene.prototypes.") == true) {
		setPrototypeDetails();
	} else
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
	auto outlinerSelection = StringTools::tokenize(view->getEditorView()->getScreenController()->getOutlinerSelection(), "|");
	vector<string> selectedEntityIds;
	auto entityIdToRemove = "scene.entities." + entityId;
	for (const auto& selectedEntityId: outlinerSelection) {
		if (StringTools::startsWith(selectedEntityId, "scene.entities.") == false) continue;
		if (selectedEntityId == entityIdToRemove) continue;
		selectedEntityIds.push_back(selectedEntityId);
	}
	selectEntities(selectedEntityIds);
}

void SceneEditorTabController::selectEntity(const string& entityId) {
	auto outlinerSelection = StringTools::tokenize(view->getEditorView()->getScreenController()->getOutlinerSelection(), "|");
	vector<string> selectedEntityIds;
	auto entityIdToAdd = "scene.entities." + entityId;
	for (const auto& selectedEntityId: outlinerSelection) {
		if (StringTools::startsWith(selectedEntityId, "scene.entities.") == false) continue;
		if (selectedEntityId == entityIdToAdd) continue;
		selectedEntityIds.push_back(selectedEntityId);
	}
	selectedEntityIds.push_back(entityIdToAdd);
	selectEntities(selectedEntityIds);
}

void SceneEditorTabController::selectEntities(const vector<string>& selectedOutlinerEntityIds) {
	if (selectedOutlinerEntityIds.empty() == true) {
		auto newOutlinerSelection = string("scene.entities");
		view->getEditorView()->getScreenController()->setOutlinerSelection(newOutlinerSelection);
		updateDetails(newOutlinerSelection);
	} else
	if (selectedOutlinerEntityIds.size() == 1) {
		auto newOutlinerSelection = string(selectedOutlinerEntityIds[0]);
		view->getEditorView()->getScreenController()->setOutlinerSelection(newOutlinerSelection);
		updateDetails(StringTools::substring(newOutlinerSelection, string("scene.entities.").size()));
	} else {
		auto newOutlinerSelection = string("|");
		for (const auto& entityId: selectedOutlinerEntityIds) {
			newOutlinerSelection+= entityId + "|";
		}
		view->getEditorView()->getScreenController()->setOutlinerSelection(newOutlinerSelection);
		updateDetails("scene.entities");
	}
}

void SceneEditorTabController::onReplacePrototype() {
	class OnReplacePrototypeAction: public virtual Action
	{
	public:
		void performAction() override {
			try {
				auto outlinerSelection = StringTools::tokenize(sceneEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection(), "|");
				if (outlinerSelection.size() != 1) return;
				string selectedEntityId;
				if (StringTools::startsWith(outlinerSelection[0], "scene.entities.") == false) return;
				selectedEntityId = StringTools::substring(outlinerSelection[0], string("scene.entities.").size());
				auto scene = sceneEditorTabController->view->getScene();
				auto sceneLibrary = scene->getLibrary();
				auto selectedSceneEntity = scene->getEntity(selectedEntityId);
				auto prototype = selectedSceneEntity != nullptr?selectedSceneEntity->getPrototype():nullptr;
				if (prototype == nullptr) return;
				auto newPrototype = PrototypeReader::read(
					Prototype::ID_NONE,
					sceneEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
					sceneEditorTabController->popUps->getFileDialogScreenController()->getFileName()
				);
				sceneLibrary->addPrototype(newPrototype);
				sceneEditorTabController->view->clearScene();
				scene->replacePrototypeByIds(prototype->getId(), newPrototype->getId());
				sceneLibrary->removePrototype(prototype->getId());
				sceneEditorTabController->view->reloadScene();
				//
				sceneEditorTabController->view->getEditorView()->reloadTabOutliner("scene.entities");
			} catch (Exception& exception) {
				Console::println("OnReplacePrototypeAction::performAction(): An error occurred: " + string(exception.what()));
				sceneEditorTabController->showInfoPopUp("Warning", string(exception.what()));
			}
			sceneEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param sceneEditorTabController scene editor tab controller
		 */
		OnReplacePrototypeAction(SceneEditorTabController* sceneEditorTabController)
			: sceneEditorTabController(sceneEditorTabController) {
			//
		}

	private:
		SceneEditorTabController* sceneEditorTabController;
	};

	auto extensions = PrototypeReader::getPrototypeExtensions();
	popUps->getFileDialogScreenController()->show(
		string(),
		"Replace prototype with: ",
		extensions,
		string(),
		true,
		new OnReplacePrototypeAction(this)
	);
}

void SceneEditorTabController::startRenameEntity(const string& entityName) {
	auto scene = view->getScene();
	auto sceneEntity = scene->getEntity(entityName);
	if (sceneEntity == nullptr) return;
	auto selectBoxOptionParentNode = dynamic_cast<GUIParentNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById("scene.entities." + entityName));
	if (selectBoxOptionParentNode == nullptr) return;
	renameEntityName = entityName;
	selectBoxOptionParentNode->replaceSubNodes(
		"<template id=\"tdme.entities.rename_input\" hint=\"Property name\" text=\"" + GUIParser::escape(sceneEntity->getName()) + "\"src=\"resources/engine/gui/template_outliner_rename.xml\" />\n",
		true
	);
	Engine::getInstance()->getGUI()->setFoccussedNode(dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById("tdme.entities.rename_input")));
	view->getEditorView()->getScreenController()->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById("selectbox_outliner")));
}

void SceneEditorTabController::renameEntity() {
	auto scene = view->getScene();
	auto sceneEntity = scene->getEntity(renameEntityName);
	renameEntityName.clear();
	if (sceneEntity != nullptr) {
		try {
			auto name = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("tdme.entities.rename_input"))->getController()->getValue().getString();
			if (name.empty() == true) throw ExceptionBase("Please enter a name");
			if (view->applyBase(
					name,
					sceneEntity->getDescription()
				) == false) {
				throw ExceptionBase("Could not rename entity");
			}
			view->reloadScene();
		} catch (Exception& exception) {
			Console::println("SceneEditorTabController::renameProperty(): An error occurred: " + string(exception.what()));
			showInfoPopUp("Warning", string(exception.what()));
		}
	}

	//
	view->getEditorView()->reloadTabOutliner("scene.entities" + (sceneEntity != nullptr?"." + sceneEntity->getName():""));
}
