#include <tdme/tools/editor/tabcontrollers/DecalEditorTabController.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeDecal.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIImageNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUITextNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeScriptSubController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/tabviews/DecalEditorTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Base64.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Integer.h>
#include <agui/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::tools::editor::tabcontrollers::DecalEditorTabController;

using tdme::engine::fileio::textures::PNGTextureWriter;
using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::prototype::Prototype;
using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIImageNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::GUIParser;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::DecalEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Base64;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Integer;
using agui::utilities::MutableString;
using tdme::utilities::StringTools;

DecalEditorTabController::DecalEditorTabController(DecalEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->basePropertiesSubController = make_unique<BasePropertiesSubController>(view->getEditorView(), "prototype");
	this->prototypePhysicsSubController = make_unique<PrototypePhysicsSubController>(view->getEditorView(), view, false);
	this->prototypeDisplaySubController = make_unique<PrototypeDisplaySubController>(view->getEditorView(), view, this->prototypePhysicsSubController->getView());
	this->prototypeScriptSubController = make_unique<PrototypeScriptSubController>(view->getEditorView());
}

DecalEditorTabController::~DecalEditorTabController() {
}

void DecalEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
	prototypeDisplaySubController->initialize(screenNode);
	prototypePhysicsSubController->initialize(screenNode);
	prototypeScriptSubController->initialize(screenNode);
}

void DecalEditorTabController::dispose()
{
}

void DecalEditorTabController::onCommand(TabControllerCommand command)
{
	switch (command) {
		case COMMAND_SAVE:
			{
				auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
				try {
					if (fileName.empty() == true) throw ExceptionBase("Could not save file. No filename known");
					view->saveFile(
						Tools::getPathName(fileName),
						Tools::getFileName(fileName)
					);
				} catch (Exception& exception) {
					showInfoPopUp("Warning", string(exception.what()));
				}
			}
			break;
		case COMMAND_SAVEAS:
			{
				class OnDecalSave: public virtual Action
				{
				public:
					void performAction() override {
						try {
							decalEditorTabController->view->saveFile(
								decalEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
								decalEditorTabController->popUps->getFileDialogScreenController()->getFileName()
							);
						} catch (Exception& exception) {
							decalEditorTabController->showInfoPopUp("Warning", string(exception.what()));
						}
						decalEditorTabController->popUps->getFileDialogScreenController()->close();
					}
					OnDecalSave(DecalEditorTabController* decalEditorTabController): decalEditorTabController(decalEditorTabController) {
					}
				private:
					DecalEditorTabController* decalEditorTabController;
				};

				auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
				vector<string> extensions = {
					"tdecal"
				};
				popUps->getFileDialogScreenController()->show(
					fileName.empty() == false?Tools::getPathName(fileName):string(),
					"Save to: ",
					extensions,
					Tools::getFileName(fileName),
					false,
					new OnDecalSave(this)
				);
			}
			break;
		default:
			showInfoPopUp("Warning", "This command is not supported yet");
			break;
	}
}

void DecalEditorTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	if (prototypePhysicsSubController->onDrop(payload, mouseX, mouseY, view->getPrototype()) == true) return;
	if (prototypeScriptSubController->onDrop(payload, mouseX, mouseY, view->getPrototype()) == true) return;
	if (StringTools::startsWith(payload, "file:") == false) {
		showInfoPopUp("Warning", "Unknown payload in drop");
	} else {
		auto fileName = StringTools::substring(payload, string("file:").size());
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "decal_texture") == true) {
			if (Tools::hasFileExtension(fileName, TextureReader::getTextureExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(TextureReader::getTextureExtensions()));
			} else {
				setDecalTexture(fileName);
			}
		} else {
			showInfoPopUp("Warning", "You can not drop a file here");
		}
	}
}

void DecalEditorTabController::onChange(GUIElementNode* node)
{
	if (basePropertiesSubController->onChange(node, view->getPrototype(), view->getPrototype()) == true) return;
	if (prototypeDisplaySubController->onChange(node, view->getPrototype()) == true) return;
	if (prototypePhysicsSubController->onChange(node, view->getPrototype()) == true) return;
	if (prototypeScriptSubController->onChange(node, view->getPrototype()) == true) return;
	//
	for (const auto& applyDecalNode: applyDecalNodes) {
		if (node->getId() == applyDecalNode) {
			applyDecalDetails();
			return;
		}
	}
	//
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		updateDetails(outlinerNode);
	}
}

void DecalEditorTabController::onFocus(GUIElementNode* node) {
	if (basePropertiesSubController->onFocus(node, view->getPrototype()) == true) return;
}

void DecalEditorTabController::onUnfocus(GUIElementNode* node) {
	if (basePropertiesSubController->onUnfocus(node, view->getPrototype()) == true) return;
}

void DecalEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
	basePropertiesSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
	prototypePhysicsSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
}

void DecalEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void DecalEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void DecalEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (basePropertiesSubController->onAction(type, node, view->getPrototype()) == true) return;
	if (prototypeDisplaySubController->onAction(type, node, view->getPrototype()) == true) return;
	if (prototypePhysicsSubController->onAction(type, node, view->getPrototype()) == true) return;
	if (prototypeScriptSubController->onAction(type, node, view->getPrototype()) == true) return;
	//
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "decal_texture_open") {
			//
			class OnDecalTextureFileOpenAction: public virtual Action
			{
			public:
				void performAction() override {
					decalEditorTabController->setDecalTexture(
						decalEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
						"/" +
						decalEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
					);
					decalEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
				}

				/**
				 * Public constructor
				 * @param decalEditorTabController decal editor tab controller
				 */
				OnDecalTextureFileOpenAction(DecalEditorTabController* decalEditorTabController): decalEditorTabController(decalEditorTabController) {
				}

			private:
				DecalEditorTabController* decalEditorTabController;
			};

			auto prototype = view->getPrototype();
			if (prototype == nullptr) return;
			auto decal = prototype->getDecal();
			if (decal == nullptr) return;
			vector<string> extensions = TextureReader::getTextureExtensions();
			view->getPopUps()->getFileDialogScreenController()->show(
				decal->getTextureFileName().empty() == false?Tools::getPathName(decal->getTextureFileName()):string(),
				"Load decal texture from: ",
				extensions,
				Tools::getFileName(decal->getTextureFileName()),
				true,
				new OnDecalTextureFileOpenAction(this)
			);
		} else
		if (node->getId() == "decal_texture_remove") {
			auto prototype = view->getPrototype();
			if (prototype == nullptr) return;
			auto decal = prototype->getDecal();
			if (decal == nullptr) return;
			decal->setTextureFileName(string());
			prototype->setThumbnail(string());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("decal_texture"))->setSource(prototype->getDecal()->getTextureFileName());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("decal_texture"))->setTooltip(prototype->getDecal()->getTextureFileName());
		} else
		if (node->getId() == "decal_texture_browseto") {
			auto prototype = view->getPrototype();
			if (prototype == nullptr) return;
			auto decal = prototype->getDecal();
			if (decal != nullptr && decal->getTextureFileName().empty() == false) {
				view->getEditorView()->getScreenController()->browseTo(decal->getTextureFileName());
			} else {
				showInfoPopUp("Browse To", "Nothig to browse to");
			}
		}
	}
}

void DecalEditorTabController::setDecalTexture(const string& fileName) {
	//
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	//
	auto decal = prototype != nullptr?prototype->getDecal():nullptr;
	if (decal == nullptr) return;
	//
	try {
		decal->setTextureFileName(fileName);
		//
		if (decal->getTexture() == nullptr) {
			showInfoPopUp("Warning", "Unsupported file format or corrupt file");
		} else {
			// thumbnail
			auto decalTextureThumbnail = TextureReader::scale(decal->getTexture(), 128, 128);
			vector<uint8_t> pngData;
			string base64PNGData;
			PNGTextureWriter::write(decalTextureThumbnail, pngData, false, false);
			Base64::encode(pngData, base64PNGData);
			prototype->setThumbnail(base64PNGData);
			decalTextureThumbnail->releaseReference();
			// adjust oriented bounding box
			auto physicsSubView = prototypePhysicsSubController->getView();
			physicsSubView->applyBoundingVolumeObb(
				prototype,
				0,
				Vector3(),
				OrientedBoundingBox::AABB_AXIS_X,
				OrientedBoundingBox::AABB_AXIS_Y,
				OrientedBoundingBox::AABB_AXIS_Z,
				Vector3(
					0.5f * (static_cast<float>(decal->getTexture()->getWidth()) / static_cast<float>(decal->getTexture()->getHeight())),
					0.5f,
					0.5f
				)
			);
			physicsSubView->updateGizmo(prototype);
		}
	} catch (Exception& exception) {
		Console::printLine("OnDecalTextureFileOpenAction::performAction(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
	//
	setDecalDetails();
}

void DecalEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Prototype") + "\" value=\"" + GUIParser::escape("prototype") + "\">\n";
	auto prototype = view->getPrototype();
	if (prototype != nullptr) {
		xml+= "<selectbox-option text=\"" + GUIParser::escape("Decal") + "\" value=\"" + GUIParser::escape("decal") + "\" />\n";
		basePropertiesSubController->createBasePropertiesXML(prototype, xml);
		prototypeScriptSubController->createScriptXML(prototype, xml);
		prototypePhysicsSubController->createOutlinerPhysicsXML(prototype, xml);
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void DecalEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(
		string("<dropdown-option text=\"Property\" value=\"property\" />\n") +
		string("<dropdown-option text=\"BV\" value=\"boundingvolume\" />\n")
	);
}

void DecalEditorTabController::setDecalDetails() {
	view->getEditorView()->setDetailsContent(
		"<template id=\"details_decal\" src=\"resources/engine/gui/template_details_decal.xml\" />\n"
	);

	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	auto decal = prototype->getDecal();
	if (decal == nullptr) return;

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_decal"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("decal_texture"))->setSource(decal->getTextureFileName());
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("decal_texture"))->setTooltip(decal->getTextureFileName());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("decal_texture_horizontal_sprites"))->getController()->setValue(MutableString(decal->getTextureHorizontalSprites()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("decal_texture_vertical_sprites"))->getController()->setValue(MutableString(decal->getTextureVerticalSprites()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("decal_texture_fps"))->getController()->setValue(MutableString(decal->getTextureSpritesFPS()));
	} catch (Exception& exception) {
		Console::printLine("DecalEditorTabController::setDecalDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void DecalEditorTabController::updateDetails(const string& outlinerNode) {
	if (outlinerNode == "decal") {
		setDecalDetails();
	} else {
		view->getEditorView()->setDetailsContent(string());
		basePropertiesSubController->updateDetails(view->getPrototype(), outlinerNode);
		prototypeDisplaySubController->updateDetails(view->getPrototype(), outlinerNode);
		prototypePhysicsSubController->updateDetails(view->getPrototype(), outlinerNode);
		prototypePhysicsSubController->getView()->setDisplayBoundingVolume(true);
		prototypeScriptSubController->updateDetails(view->getPrototype(), outlinerNode);
	}
}

void DecalEditorTabController::applyDecalDetails() {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	auto decal = prototype->getDecal();
	if (decal == nullptr) return;
	//
	decal->setTextureHorizontalSprites(Math::max(1, Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("decal_texture_horizontal_sprites"))->getController()->getValue().getString())));
	decal->setTextureVerticalSprites(Math::max(1, Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("decal_texture_vertical_sprites"))->getController()->getValue().getString())));
	decal->setTextureSpritesFPS(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("decal_texture_fps"))->getController()->getValue().getString()));
}

void DecalEditorTabController::updateInfoText(const MutableString& text) {
	required_dynamic_cast<GUITextNode*>(screenNode->getNodeById(view->getTabId() + "_tab_text_info"))->setText(text);
}

void DecalEditorTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}
