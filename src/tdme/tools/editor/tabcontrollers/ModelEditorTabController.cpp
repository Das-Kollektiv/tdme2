#include <tdme/tools/editor/tabcontrollers/ModelEditorTabController.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/ShaderModel.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeImposterLOD.h>
#include <tdme/engine/prototype/PrototypeLODLevel.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/GenerateBillboardLOD.h>
#include <tdme/tools/editor/misc/GenerateImposterLOD.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeScriptSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/ModelEditorTabView.h>
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
using std::unordered_map;
using std::vector;

using tdme::tools::editor::tabcontrollers::ModelEditorTabController;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::ShaderModel;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeImposterLOD;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::engine::Engine;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::GenerateBillboardLOD;
using tdme::tools::editor::misc::GenerateImposterLOD;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeScriptSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::ModelEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

ModelEditorTabController::ModelEditorTabController(ModelEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->basePropertiesSubController = make_unique<BasePropertiesSubController>(view->getEditorView(), "prototype");
	this->prototypePhysicsSubController = make_unique<PrototypePhysicsSubController>(view->getEditorView(), view, true);
	this->prototypeSoundsSubController = make_unique<PrototypeSoundsSubController>(view->getEditorView(), view);
	this->prototypeDisplaySubController = make_unique<PrototypeDisplaySubController>(view->getEditorView(), view, this->prototypePhysicsSubController->getView());
	this->prototypeScriptSubController = make_unique<PrototypeScriptSubController>(view->getEditorView());
}

ModelEditorTabController::~ModelEditorTabController() {
}

void ModelEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
	prototypeDisplaySubController->initialize(screenNode);
	prototypePhysicsSubController->initialize(screenNode);
	prototypeSoundsSubController->initialize(screenNode);
	prototypeScriptSubController->initialize(screenNode);
}

void ModelEditorTabController::dispose()
{
}

void ModelEditorTabController::onCommand(TabControllerCommand command)
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
				class OnModelSave: public virtual Action
				{
				public:
					void performAction() override {
						try {
							modelEditorTabController->view->saveFile(
								modelEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
								modelEditorTabController->popUps->getFileDialogScreenController()->getFileName()
							);
						} catch (Exception& exception) {
							modelEditorTabController->showInfoPopUp("Warning", string(exception.what()));
						}
						modelEditorTabController->popUps->getFileDialogScreenController()->close();
					}

					/**
					 * Public constructor
					 * @param modelEditorTabController model editor tab controller
					 */
					OnModelSave(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
					}

				private:
					ModelEditorTabController* modelEditorTabController;
				};

				auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
				if (fileName.length() == 0) {
					fileName = view->getFileName();
					if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".tmodel") == false) {
						fileName = Tools::removeFileExtension(fileName) + ".tmodel";
					}
				}
				vector<string> extensions = {
					"tmodel"
				};
				popUps->getFileDialogScreenController()->show(
					Tools::getPathName(fileName),
					"Save to: ",
					extensions,
					Tools::getFileName(fileName),
					false,
					new OnModelSave(this)
				);
			}
			break;
		default:
			showInfoPopUp("Warning", "This command is not supported yet");
			break;
	}
}

void ModelEditorTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	if (prototypeSoundsSubController->onDrop(payload, mouseX, mouseY, view->getPrototype()) == true) return;
	if (prototypePhysicsSubController->onDrop(payload, mouseX, mouseY, view->getPrototype()) == true) return;
	if (prototypeScriptSubController->onDrop(payload, mouseX, mouseY, view->getPrototype()) == true) return;
	if (StringTools::startsWith(payload, "file:") == false) {
		showInfoPopUp("Warning", "Unknown payload in drop");
	} else {
		auto fileName = StringTools::substring(payload, string("file:").size());
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "specularmaterial_diffuse_texture") == true) {
			if (Tools::hasFileExtension(fileName, TextureReader::getTextureExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(TextureReader::getTextureExtensions()));
			} else {
				setMaterialDiffuseTexture(fileName);
			}
		} else
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "specularmaterial_transparency_texture") == true) {
			if (Tools::hasFileExtension(fileName, TextureReader::getTextureExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(TextureReader::getTextureExtensions()));
			} else {
				setMaterialDiffuseTransparencyTexture(fileName);
			}
		} else
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "specularmaterial_normal_texture") == true) {
			if (Tools::hasFileExtension(fileName, TextureReader::getTextureExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(TextureReader::getTextureExtensions()));
			} else {
				setMaterialNormalTexture(fileName);
			}
		} else
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "specularmaterial_specular_texture") == true) {
			if (Tools::hasFileExtension(fileName, TextureReader::getTextureExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(TextureReader::getTextureExtensions()));
			} else {
				setMaterialSpecularTexture(fileName);
			}
		} else
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "pbrmaterial_basecolor_texture") == true) {
			if (Tools::hasFileExtension(fileName, TextureReader::getTextureExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(TextureReader::getTextureExtensions()));
			} else {
				setMaterialPBRBaseColorTexture(fileName);
			}
		} else
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "pbrmaterial_metallic_roughness_texture") == true) {
			if (Tools::hasFileExtension(fileName, TextureReader::getTextureExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(TextureReader::getTextureExtensions()));
			} else {
				setMaterialPBRMetallicRoughnessTexture(fileName);
			}
		} else
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "pbrmaterial_normal_texture") == true) {
			if (Tools::hasFileExtension(fileName, TextureReader::getTextureExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(TextureReader::getTextureExtensions()));
			} else {
				setMaterialPBRNormalTexture(fileName);
			}
		} else
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "pbrmaterial_emissive_texture") == true) {
			if (Tools::hasFileExtension(fileName, TextureReader::getTextureExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(TextureReader::getTextureExtensions()));
			} else {
				setMaterialPBREmissiveTexture(fileName);
			}
		} else
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "animationpreview_attachment1_model") == true) {
			if (Tools::hasFileExtension(fileName, ModelReader::getModelExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(ModelReader::getModelExtensions()));
			} else {
				setPreviewAnimationsAttachment1Model(fileName);
			}
		} else {
			showInfoPopUp("Warning", "You can not drop a file here");
		}
	}
}

void ModelEditorTabController::createOutlinerModelNodesXML(const string& prefix, const unordered_map<string, Node*>& subNodes, string& xml) {
	for (const auto& [nodeId, node]: subNodes) {
		string image;
		if (node->isJoint() == true) {
			image = "bone.png";
		} else
		if (node->isEmpty() == true) {
			image = "empty.png";
		} else {
			image = "mesh.png";
		}
		if (node->getSubNodes().empty() == false) {
			xml+= "<selectbox-parent-option image=\"resources/engine/images/" + image + "\" text=\"" + GUIParser::escape(node->getId()) + "\" value=\"" + GUIParser::escape(prefix + ".nodes." + node->getId()) + "\">\n";
			createOutlinerModelNodesXML(prefix, node->getSubNodes(), xml);
			xml+= "</selectbox-parent-option>\n";
		} else {
			xml+= "	<selectbox-option image=\"resources/engine/images/" + image + "\" text=\"" + GUIParser::escape(node->getId()) + "\" value=\"" + GUIParser::escape(prefix + ".nodes." + node->getId()) + "\" />\n";
		}
	}
}

void ModelEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Prototype") + "\" value=\"" + GUIParser::escape("prototype") + "\">\n";
	auto prototype = view->getPrototype();
	if (prototype != nullptr) {
		basePropertiesSubController->createBasePropertiesXML(prototype, xml);
		prototypeScriptSubController->createScriptXML(prototype, xml);
		prototypeDisplaySubController->createDisplayPropertiesXML(prototype, xml);
		prototypePhysicsSubController->createOutlinerPhysicsXML(prototype, xml);
		prototypeSoundsSubController->createOutlinerSoundsXML(prototype, xml);
		for (auto lodLevel = 1; lodLevel < 5; lodLevel++) {
			Model* model = nullptr;
			switch (lodLevel) {
				case 1:
					model = prototype->getModel();
					break;
				case 2:
					model = prototype->getLODLevel2() != nullptr?prototype->getLODLevel2()->getModel():nullptr;
					if (prototype->getLODLevel2() == nullptr) continue;
					break;
				case 3:
					model = prototype->getLODLevel3() != nullptr?prototype->getLODLevel3()->getModel():nullptr;
					if (prototype->getLODLevel3() == nullptr) continue;
					break;
				case 4:
					model = nullptr;
					if (prototype->getImposterLOD() == nullptr) continue;
					break;
			}
			auto modelPrefix = lodLevel == 1?"model":"lod" + to_string(lodLevel) + ".model";
			// TODO: clean up "model != nullpt" stuff here
			if (model != nullptr) {
				xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape(lodLevel != 1?"LOD " + to_string(lodLevel) + " Model":"Model") + "\" value=\"" + GUIParser::escape(modelPrefix) + "\">\n";
			} else {
				xml+= "<selectbox-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape(lodLevel != 1?"LOD " + to_string(lodLevel) + " Model":"Model") + "\" value=\"" + GUIParser::escape(modelPrefix) + "\" />\n";
			}
			if (model != nullptr) {
				xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Materials") + "\" value=\"" + GUIParser::escape(modelPrefix + ".materials") + "\">\n";
				for (const auto& materialId: model->getMaterialIds()) {
					xml+= "	<selectbox-option image=\"resources/engine/images/material.png\" text=\"" + GUIParser::escape(materialId) + "\" value=\"" + GUIParser::escape(modelPrefix + ".materials." + materialId) + "\" />\n";
				}
				xml+= "</selectbox-parent-option>\n";
			}
			if (model != nullptr && model->getSubNodes().empty() == false) {
				xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Nodes") + "\" value=\"" + GUIParser::escape(modelPrefix + ".nodes") + "\">\n";
				createOutlinerModelNodesXML(modelPrefix, model->getSubNodes(), xml);
				xml+= "</selectbox-parent-option>\n";
			}
			if (model != nullptr &&
				(model->getAnimationSetups().size() > 1 || model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT) == nullptr)) {
				xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Animations") + "\" value=\"" + GUIParser::escape(modelPrefix + ".animations") + "\">\n";
				for (const auto& animationSetupId: model->getAnimationSetupIds()) {
					if (animationSetupId == Model::ANIMATIONSETUP_DEFAULT) continue;
					xml+= "	<selectbox-option image=\"resources/engine/images/animation.png\" text=\"" + GUIParser::escape(animationSetupId) + "\" id=\"" + GUIParser::escape(modelPrefix + ".animations." + animationSetupId) + "\" value=\"" + GUIParser::escape(modelPrefix + ".animations." + animationSetupId) + "\" />\n";
				}
				xml+= "</selectbox-parent-option>\n";
			}
			if (model != nullptr) xml+= "</selectbox-parent-option>\n";
		}
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void ModelEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(
		string("<dropdown-option text=\"Property\" value=\"property\" />\n") +
		string("<dropdown-option text=\"BV\" value=\"boundingvolume\" />\n") +
		string("<dropdown-option text=\"Sound\" value=\"sound\" />\n") +
		string("<dropdown-option text=\"Animation\" value=\"animation\" />\n") +
		string("<dropdown-option text=\"LOD\" value=\"lod\" />\n") +
		string("<dropdown-option text=\"LOD None\" value=\"lod_none\" />\n")
	);
}

void ModelEditorTabController::setDetailsContent() {
	view->getEditorView()->setDetailsContent(string());
}

PrototypeLODLevel* ModelEditorTabController::getLODLevel(int level) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return nullptr;
	switch (level) {
		case 2:
			{
				auto prototypeLodLevel = prototype->getLODLevel2();
				if (prototypeLodLevel == nullptr) {
					auto newPrototypeLodLevel = make_unique<PrototypeLODLevel>(
						LODObject::LODLEVELTYPE_NONE,
						"",
						nullptr,
						75.0f
					);
					prototype->setLODLevel2(newPrototypeLodLevel.get());
					prototypeLodLevel = newPrototypeLodLevel.release();
				}
				return prototypeLodLevel;
			}
		case 3:
			{
				auto prototypeLodLevel = prototype->getLODLevel3();
				if (prototypeLodLevel == nullptr) {
					auto newPrototypeLodLevel = make_unique<PrototypeLODLevel>(
						LODObject::LODLEVELTYPE_NONE,
						"",
						nullptr,
						150.0f
					);
					prototype->setLODLevel3(newPrototypeLodLevel.get());
					prototypeLodLevel = newPrototypeLodLevel.release();
				}
				return prototypeLodLevel;
			}
	}
	return nullptr;
}

Model* ModelEditorTabController::getLODLevelModel(int level) {
	Model* model = nullptr;
	switch (level) {
		case 1: model = view->getPrototype()->getModel(); break;
		case 2: model = view->getPrototype()->getLODLevel2() != nullptr?view->getPrototype()->getLODLevel2()->getModel():nullptr; break;
		case 3: model = view->getPrototype()->getLODLevel3() != nullptr?view->getPrototype()->getLODLevel3()->getModel():nullptr; break;
		default: model = nullptr;
	}
	return model;
}

Model* ModelEditorTabController::getSelectedModel() {
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	string outlinerNodeModel;
	Model* model = nullptr;
	getOutlinerNodeLOD(outlinerNode, outlinerNodeModel, &model);
	return model;
}

Material* ModelEditorTabController::getSelectedMaterial() {
	string materialId;
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	string outlinerNodeModel;
	Model* model = nullptr;
	getOutlinerNodeLOD(outlinerNode, outlinerNodeModel, &model);
	if (model == nullptr) return nullptr;
	if (StringTools::startsWith(outlinerNodeModel, "model.materials.") == true) {
		materialId = StringTools::substring(outlinerNodeModel, string("model.materials.").size(), outlinerNode.size());
	} else {
		return nullptr;
	}
	auto materialIt = model->getMaterials().find(materialId);
	return materialIt != model->getMaterials().end()?materialIt->second:nullptr;
}

AnimationSetup* ModelEditorTabController::getSelectedAnimationSetup() {
	string animationId;
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	string outlinerNodeModel;
	Model* model = nullptr;
	getOutlinerNodeLOD(outlinerNode, outlinerNodeModel, &model);
	if (model == nullptr) return nullptr;
	if (StringTools::startsWith(outlinerNodeModel, "model.animations.") == true) {
		animationId = StringTools::substring(outlinerNodeModel, string("model.animations.").size(), outlinerNode.size());
	} else {
		return nullptr;
	}
	return model->getAnimationSetup(animationId);
}

void ModelEditorTabController::setStatistics(int statsOpaqueFaces, int statsTransparentFaces, int statsMaterialCount)
{
}

void ModelEditorTabController::unsetStatistics()
{
}

void ModelEditorTabController::onToolsComputeNormal() {
	view->computeNormals();
}

void ModelEditorTabController::onToolsOptimizeModel() {
	view->optimizeModel();
}

void ModelEditorTabController::onModelReload()
{
	view->reloadFile();
}

void ModelEditorTabController::onModelLoad() {
	class OnModelLoad: public virtual Action
	{

	public:
		void performAction() override {
			modelEditorTabController->view->loadModel(
				modelEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->popUps->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->popUps->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 */
		OnModelLoad(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
		}

	private:
		ModelEditorTabController* modelEditorTabController;
	};

	popUps->getFileDialogScreenController()->show(
		string(),
		"Load model from: ",
		ModelReader::getModelExtensions(),
		view->getFileName(),
		true,
		new OnModelLoad(this)
	);
}

void ModelEditorTabController::onModelReimport()
{
	class OnModelReimport: public virtual Action
	{

	public:
		void performAction() override {
			modelEditorTabController->view->reimportModel(
				modelEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->popUps->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->popUps->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 */
		OnModelReimport(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
		}

	private:
		ModelEditorTabController* modelEditorTabController;
	};

	popUps->getFileDialogScreenController()->show(
		string(),
		"Reimport model from: ",
		ModelReader::getModelExtensions(),
		view->getFileName(),
		true,
		new OnModelReimport(this)
	);
}

void ModelEditorTabController::saveFile(const string& pathName, const string& fileName)
{
	view->saveFile(pathName, fileName);
}

void ModelEditorTabController::loadFile(const string& pathName, const string& fileName)
{
	view->loadModel(pathName, fileName);
}

void ModelEditorTabController::onLODLoad(int lodLevel) {
	class OnLODLoad: public virtual Action
	{

	public:
		void performAction() override {
			PrototypeLODLevel* prototypeLODLevel = nullptr;
			switch (lodLevel) {
				case 2: prototypeLODLevel = prototype->getLODLevel2(); break;
				case 3: prototypeLODLevel = prototype->getLODLevel3(); break;
				default: break;
			}
			if (prototypeLODLevel == nullptr) return;

			modelEditorTabController->view->setLODLevel(1);

			try {
				// set model in LOD level
				prototypeLODLevel->setModel(
					ModelReader::read(
						modelEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
						modelEditorTabController->popUps->getFileDialogScreenController()->getFileName()
					)
				);
			} catch (Exception& exception) {
				Console::printLine("OnLODLoad::performAction(): An error occurred: " + string(exception.what()));
				modelEditorTabController->showInfoPopUp("Warning", string(exception.what()));
			}

			modelEditorTabController->view->setLODLevel(lodLevel);
			modelEditorTabController->view->getEditorView()->reloadTabOutliner("lod" + to_string(lodLevel) + ".model");
			modelEditorTabController->popUps->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param prototype prototype
		 * @param lodLevel LOD level
		 */
		OnLODLoad(ModelEditorTabController* modelEditorTabController, Prototype* prototype, int lodLevel): modelEditorTabController(modelEditorTabController), prototype(prototype), lodLevel(lodLevel) {
		}

	private:
		ModelEditorTabController* modelEditorTabController;
		Prototype* prototype;
		int lodLevel;
	};

	popUps->getFileDialogScreenController()->show(
		string(),
		"Load LOD " + to_string(lodLevel) + " model from: ",
		ModelReader::getModelExtensions(),
		view->getFileName(),
		true,
		new OnLODLoad(this, view->getPrototype(), lodLevel)
	);
}

void ModelEditorTabController::updateInfoText(const MutableString& text) {
	required_dynamic_cast<GUITextNode*>(screenNode->getNodeById(view->getTabId() + "_tab_text_info"))->setText(text);
}

void ModelEditorTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void ModelEditorTabController::setMaterialBaseDetails() {
	view->getEditorView()->setDetailsContent(
		"<template id=\"details_material_base\" src=\"resources/engine/gui/template_details_material.xml\" />\n"
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_material_base"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::setMaterialBaseDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	updateMaterialBaseDetails();
}

void ModelEditorTabController::updateMaterialBaseDetails() {
	auto model = getSelectedModel();
	if (model == nullptr) return;

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("material_specular_embedtextures_enabled"))->getController()->setValue(MutableString(model->hasEmbeddedSpecularTextures() == true?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("material_pbr_embedtextures_enabled"))->getController()->setValue(MutableString(model->hasEmbeddedPBRTextures() == true?"1":""));
		auto shaderModel = model->getShaderModel();
		if (shaderModel == ShaderModel::SPECULAR) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("material_lightningmodel"))->getController()->setValue(MutableString("specular"));
		} else
		if (shaderModel == ShaderModel::PBR) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("material_lightningmodel"))->getController()->setValue(MutableString("pbr"));
		} else
		if (shaderModel == ShaderModel::SPECULARPBR) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("material_lightningmodel"))->getController()->setValue(MutableString("pbrspecular"));
		}
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::updateMaterialBaseDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void ModelEditorTabController::applyMaterialBaseDetails() {
	auto model = getSelectedModel();
	if (model == nullptr) return;

	//
	try {
		model->setEmbedSpecularTextures(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("material_specular_embedtextures_enabled"))->getController()->getValue().getString() == "1");
		model->setEmbedPBRTextures(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("material_pbr_embedtextures_enabled"))->getController()->getValue().getString() == "1");
		auto shaderModel = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("material_lightningmodel"))->getController()->getValue().getString();
		if (shaderModel == "specular") {
			model->setShaderModel(ShaderModel::SPECULAR);
		} else
		if (shaderModel == "pbr") {
			model->setShaderModel(ShaderModel::PBR);
		} else
		if (shaderModel == "specularpbr") {
			model->setShaderModel(ShaderModel::SPECULARPBR);
		}
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::applyMaterialBaseDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	view->reloadPrototype();
}

void ModelEditorTabController::setMaterialDetails() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto model = getSelectedModel();
	if (model == nullptr) return;

	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	auto pbrMaterialProperties = material->getPBRMaterialProperties();

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_material_spec\" src=\"resources/engine/gui/template_details_material_specular.xml\" />\n") +
		string(model->getShaderModel() != ShaderModel::SPECULAR?"<template id=\"details_material_pbr\" src=\"resources/engine/gui/template_details_material_pbr.xml\" />\n":"")
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_material_spec"))->getActiveConditions().add("open");
		if (model->getShaderModel() != ShaderModel::SPECULAR) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_material_pbr"))->getActiveConditions().add("open");
		}
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::setMaterialDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	updateMaterialDetails();
}

void ModelEditorTabController::updateMaterialDetails() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto model = getSelectedModel();
	if (model == nullptr) return;

	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	auto pbrMaterialProperties = material->getPBRMaterialProperties();

	try {
		{
			auto diffuseTextureFileName =
				specularMaterialProperties->getDiffuseTextureFileName().empty() == true?
					string():
					(
						PrototypeReader::getResourcePathName(
							view->getEditorView()->getScreenController()->getProjectPath() + "/resources",
							specularMaterialProperties->getDiffuseTexturePathName() + "/" + specularMaterialProperties->getDiffuseTextureFileName()
						) +
						"/" +
						specularMaterialProperties->getDiffuseTextureFileName()
					);
			auto diffuseTransparencyTextureFileName =
				specularMaterialProperties->getDiffuseTransparencyTextureFileName().empty() == true?
					string():
					(
						PrototypeReader::getResourcePathName(
							view->getEditorView()->getScreenController()->getProjectPath() + "/resources",
							specularMaterialProperties->getDiffuseTransparencyTexturePathName() + "/" + specularMaterialProperties->getDiffuseTransparencyTextureFileName()
						) +
						"/" +
						specularMaterialProperties->getDiffuseTransparencyTextureFileName()
					);
			auto normalTextureFileName =
					specularMaterialProperties->getNormalTextureFileName().empty() == true?
						string():
						(
							PrototypeReader::getResourcePathName(
								view->getEditorView()->getScreenController()->getProjectPath() + "/resources",
								specularMaterialProperties->getNormalTexturePathName() + "/" + specularMaterialProperties->getNormalTextureFileName()
							) +
							"/" +
							specularMaterialProperties->getNormalTextureFileName()
						);
			auto specularTextureFileName =
					specularMaterialProperties->getSpecularTextureFileName().empty() == true?
						string():
						(
							PrototypeReader::getResourcePathName(
								view->getEditorView()->getScreenController()->getProjectPath() + "/resources",
								specularMaterialProperties->getSpecularTexturePathName() + "/" + specularMaterialProperties->getSpecularTextureFileName()
							) +
							"/" +
							specularMaterialProperties->getSpecularTextureFileName()
						);
			//
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_diffuse_texture"))->setTexture(specularMaterialProperties->getDiffuseTexture());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_diffuse_texture"))->setTooltip(diffuseTextureFileName);
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_transparency_texture"))->setSource(diffuseTransparencyTextureFileName);
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_transparency_texture"))->setTooltip(diffuseTransparencyTextureFileName);
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_normal_texture"))->setTexture(specularMaterialProperties->getNormalTexture());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_normal_texture"))->setTooltip(normalTextureFileName);
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_specular_texture"))->setTexture(specularMaterialProperties->getSpecularTexture());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_specular_texture"))->setTooltip(specularTextureFileName);
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_shininess"))->getController()->setValue(specularMaterialProperties->getShininess());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_reflection"))->getController()->setValue(specularMaterialProperties->getReflection());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_maskedtransparency"))->getController()->setValue(MutableString(specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true?"1":""));
		}

		if (model->getShaderModel() != ShaderModel::SPECULAR && pbrMaterialProperties != nullptr) {
			auto baseColorTextureFileName =
				pbrMaterialProperties->getBaseColorTextureFileName().empty() == true?
					string():
					(
						PrototypeReader::getResourcePathName(
							view->getEditorView()->getScreenController()->getProjectPath() + "/resources",
							pbrMaterialProperties->getBaseColorTexturePathName() + "/" + pbrMaterialProperties->getBaseColorTextureFileName()
						) +
						"/" +
						pbrMaterialProperties->getBaseColorTextureFileName()
					);
			auto metallicRoughnessTextureFileName =
				pbrMaterialProperties->getMetallicRoughnessTextureFileName().empty() == true?
					string():
					(
						PrototypeReader::getResourcePathName(
							view->getEditorView()->getScreenController()->getProjectPath() + "/resources",
							pbrMaterialProperties->getMetallicRoughnessTexturePathName() + "/" + pbrMaterialProperties->getMetallicRoughnessTextureFileName()
						) +
						"/" +
						pbrMaterialProperties->getMetallicRoughnessTextureFileName()
					);
			auto normalTextureFileName =
				pbrMaterialProperties->getNormalTextureFileName().empty() == true?
					string():
					(
						PrototypeReader::getResourcePathName(
							view->getEditorView()->getScreenController()->getProjectPath() + "/resources",
							pbrMaterialProperties->getNormalTexturePathName() + "/" + pbrMaterialProperties->getNormalTextureFileName()
					) +
					"/" +
					pbrMaterialProperties->getNormalTextureFileName()
				);
			auto emissiveTextureFileName =
				pbrMaterialProperties->getEmissiveTextureFileName().empty() == true?
					string():
					(
						PrototypeReader::getResourcePathName(
							view->getEditorView()->getScreenController()->getProjectPath() + "/resources",
							pbrMaterialProperties->getEmissiveTexturePathName() + "/" + pbrMaterialProperties->getEmissiveTextureFileName()
					) +
					"/" +
					pbrMaterialProperties->getEmissiveTextureFileName()
				);
			//
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("pbrmaterial_basecolor_texture"))->setTexture(pbrMaterialProperties->getBaseColorTexture());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("pbrmaterial_basecolor_texture"))->setTooltip(baseColorTextureFileName);
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("pbrmaterial_metallic_roughness_texture"))->setTexture(pbrMaterialProperties->getMetallicRoughnessTexture());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("pbrmaterial_metallic_roughness_texture"))->setTooltip(metallicRoughnessTextureFileName);
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("pbrmaterial_normal_texture"))->setTexture(pbrMaterialProperties->getNormalTexture());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("pbrmaterial_normal_texture"))->setTooltip(normalTextureFileName);
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("pbrmaterial_emissive_texture"))->setTexture(pbrMaterialProperties->getEmissiveTexture());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("pbrmaterial_emissive_texture"))->setTooltip(emissiveTextureFileName);
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_metallic_factor"))->getController()->setValue(pbrMaterialProperties->getMetallicFactor());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_roughness_factor"))->getController()->setValue(pbrMaterialProperties->getRoughnessFactor());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_normal_scale"))->getController()->setValue(pbrMaterialProperties->getNormalScale());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_exposure"))->getController()->setValue(pbrMaterialProperties->getExposure());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_maskedtransparency"))->getController()->setValue(MutableString(pbrMaterialProperties->hasBaseColorTextureMaskedTransparency() == true?"1":""));
		}
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::updateMaterialDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	updateMaterialColorDetails();
}

void ModelEditorTabController::updateMaterialColorDetails() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;

	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	auto pbrMaterialProperties = material->getPBRMaterialProperties();

	try {
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_ambient"))->setEffectColorMul(Color4(specularMaterialProperties->getAmbientColor()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_diffuse"))->setEffectColorMul(Color4(specularMaterialProperties->getDiffuseColor()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_emission"))->setEffectColorMul(Color4(specularMaterialProperties->getEmissionColor()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_specular"))->setEffectColorMul(Color4(specularMaterialProperties->getSpecularColor()));

		if (pbrMaterialProperties != nullptr) {
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("pbrmaterial_basecolor"))->setEffectColorMul(Color4(pbrMaterialProperties->getBaseColorFactor()));
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("pbrmaterial_emissivefactor"))->setEffectColorMul(Color4(pbrMaterialProperties->getEmissiveFactor()));
		}
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::updateMaterialColorDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void ModelEditorTabController::applySpecularMaterialDetails() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;

	auto specularMaterialProperties = material->getSpecularMaterialProperties();

	try {
		specularMaterialProperties->setShininess(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_shininess"))->getController()->getValue().getString()));
		specularMaterialProperties->setReflection(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_reflection"))->getController()->getValue().getString()));
		specularMaterialProperties->setDiffuseTextureMaskedTransparency(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_maskedtransparency"))->getController()->getValue().getString() == "1");
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::applySpecularMaterialDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void ModelEditorTabController::applyPBRMaterialDetails() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;

	try {
		if (material->getPBRMaterialProperties() == nullptr) {
			view->reloadPrototype();
			string outlinerNodeModel;
			Model* model = nullptr;
			getOutlinerNodeLOD(view->getEditorView()->getScreenController()->getOutlinerSelection(), outlinerNodeModel, &model);
			material->setPBRMaterialProperties(make_unique<PBRMaterialProperties>().release());
			updateMaterialDetails();
		}
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::applyPBRMaterialDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	try {
		pbrMaterialProperties->setMetallicFactor(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_metallic_factor"))->getController()->getValue().getString()));
		pbrMaterialProperties->setRoughnessFactor(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_roughness_factor"))->getController()->getValue().getString()));
		pbrMaterialProperties->setNormalScale(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_normal_scale"))->getController()->getValue().getString()));
		pbrMaterialProperties->setExposure(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_exposure"))->getController()->getValue().getString()));
		pbrMaterialProperties->setBaseColorTextureMaskedTransparency(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_maskedtransparency"))->getController()->getValue().getString() == "1");
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::applyPBRMaterialDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void ModelEditorTabController::setAnimationDetails() {
	auto model = getSelectedModel();
	auto animationSetup = getSelectedAnimationSetup();
	auto defaultAnimation = animationSetup != nullptr && animationSetup->getId() == Model::ANIMATIONSETUP_DEFAULT;

	if (animationSetup == nullptr) return;

	auto defaultAnimationSetup = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_animation\" src=\"resources/engine/gui/template_details_animation.xml\" max-frames=\"") +
		to_string(defaultAnimationSetup != nullptr?defaultAnimationSetup->getEndFrame():0) +
		string("\" />\n")
	);

	//
	{
		string animationsXML;
		animationsXML =
			animationsXML +
			"<dropdown-option text=\"<None>\" value=\"\" " + (animationSetup->getOverlayFromNodeId().empty() == true?"selected=\"true\" ":"") + " />\n";
		for (const auto& nodeId: model->getNodeIds()) {
			animationsXML+=
				"<dropdown-option text=\"" +
				GUIParser::escape(nodeId) +
				"\" value=\"" +
				GUIParser::escape(nodeId) +
				"\" " +
				(animationSetup->getOverlayFromNodeId() == nodeId?"selected=\"true\" ":"") +
				" />\n";
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animation_overlaybone_scrollarea"))->replaceSubNodes(animationsXML, true);
		} catch (Exception& exception) {
			Console::printLine("ModelEditorTabController::setAnimationDetails(): An error occurred: " + string(exception.what()));
		}
	}

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_animation"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_startframe"))->getController()->setValue(animationSetup->getStartFrame());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_startframe"))->getController()->setDisabled(defaultAnimation == true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_endframe"))->getController()->setValue(animationSetup->getEndFrame());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_endframe"))->getController()->setDisabled(defaultAnimation == true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_speed"))->getController()->setValue(animationSetup->getSpeed());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_speed"))->getController()->setDisabled(defaultAnimation == true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_loop"))->getController()->setValue(MutableString(animationSetup->isLoop() == true?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_loop"))->getController()->setDisabled(defaultAnimation == true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_overlaybone"))->getController()->setValue(animationSetup->getOverlayFromNodeId());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_overlaybone"))->getController()->setDisabled(defaultAnimation == true);
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::setAnimationDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void ModelEditorTabController::applyAnimationDetails() {
	//
	view->playAnimation(Model::ANIMATIONSETUP_DEFAULT);

	auto model = getSelectedModel();
	auto animationSetup = getSelectedAnimationSetup();
	auto defaultAnimation = animationSetup != nullptr && animationSetup->getId() == Model::ANIMATIONSETUP_DEFAULT;

	if (animationSetup == nullptr) return;

	try {
		auto startFrame = Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_startframe"))->getController()->getValue().getString());
		auto endFrame = Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_endframe"))->getController()->getValue().getString());
		auto speed = Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_speed"))->getController()->getValue().getString());
		auto loop = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_loop"))->getController()->getValue().getString() == "1";
		auto overlayFromNodeId = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_overlaybone"))->getController()->getValue().getString();

		animationSetup->setStartFrame(startFrame < endFrame?startFrame:endFrame);
		animationSetup->setEndFrame(endFrame > startFrame?endFrame:startFrame);
		animationSetup->setSpeed(speed);
		animationSetup->setLoop(loop);
		animationSetup->setOverlayFromNodeId(overlayFromNodeId);

		view->playAnimation(animationSetup->getId());
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::setAnimationDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void ModelEditorTabController::setAnimationPreviewDetails() {
	auto model = getSelectedModel();
	auto defaultAnimationSetup = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_animationpreview\" src=\"resources/engine/gui/template_details_animationpreview.xml\" />\n")
	);

	{
		string animationsXML;
		animationsXML = animationsXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		for (const auto& animationSetupId: model->getAnimationSetupIds()) {
			auto animationSetup = model->getAnimationSetup(animationSetupId);
			if (animationSetup == nullptr || animationSetup->isOverlayAnimationSetup() == true) continue;
			animationsXML =
				animationsXML + "<dropdown-option text=\"" +
				GUIParser::escape(animationSetup->getId()) +
				"\" value=\"" +
				GUIParser::escape(animationSetup->getId()) +
				"\" " +
				" />\n";
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_base_scrollarea"))->replaceSubNodes(animationsXML, true);
		} catch (Exception& exception) {
			Console::printLine("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: " + string(exception.what()));
		}
	}

	{
		string overlayAnimationsXML;
		overlayAnimationsXML = overlayAnimationsXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		for (const auto& animationSetupId: model->getAnimationSetupIds()) {
			auto animationSetup = model->getAnimationSetup(animationSetupId);
			if (animationSetup == nullptr || animationSetup->isOverlayAnimationSetup() == false) continue;
			overlayAnimationsXML =
				overlayAnimationsXML + "<dropdown-option text=\"" +
				GUIParser::escape(animationSetup->getId()) +
				"\" value=\"" +
				GUIParser::escape(animationSetup->getId()) +
				"\" " +
				" />\n";
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_overlay1_scrollarea"))->replaceSubNodes(overlayAnimationsXML, true);
		} catch (Exception& exception) {
			Console::printLine("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: " + string(exception.what()));
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_overlay2_scrollarea"))->replaceSubNodes(overlayAnimationsXML, true);
		} catch (Exception& exception) {
			Console::printLine("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: " + string(exception.what()));
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_overlay3_scrollarea"))->replaceSubNodes(overlayAnimationsXML, true);
		} catch (Exception& exception) {
			Console::printLine("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: " + string(exception.what()));
		}
	}

	{
		string bonesXML;
		bonesXML = bonesXML + "<dropdown-option text=\"<No bone>\" value=\"\" selected=\"true\" />";
		for (const auto& nodeId: model->getNodeIds()) {
			bonesXML =
				bonesXML + "<dropdown-option text=\"" +
				GUIParser::escape(nodeId) +
				"\" value=\"" +
				GUIParser::escape(nodeId) +
				"\" " +
				" />\n";
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_attachment1_bone_scrollarea"))->replaceSubNodes(bonesXML, true);
		} catch (Exception& exception) {
			Console::printLine("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: " + string(exception.what()));
		}
	}

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_animationpreview"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void ModelEditorTabController::setPreviewAnimationsAttachment1Model(const string& fileName) {
	attachment1ModelFileName = fileName;
	view->addAttachment1(
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animationpreview_attachment1_bone"))->getController()->getValue().getString(),
		attachment1ModelFileName
	);
	try {
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("animationpreview_attachment1_model"))->setSource(attachment1ModelFileName);
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("animationpreview_attachment1_model"))->setTooltip(attachment1ModelFileName);
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::setPreviewAnimationsAttachment1Model(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void ModelEditorTabController::onPreviewAnimationsAttachment1ModelLoad() {
	class OnPreviewAnimationsAttachment1ModelLoad: public virtual Action
	{

	public:
		void performAction() override {
			modelEditorTabController->setPreviewAnimationsAttachment1Model(modelEditorTabController->popUps->getFileDialogScreenController()->getPathName() + "/" + modelEditorTabController->popUps->getFileDialogScreenController()->getFileName());
			modelEditorTabController->popUps->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 */
		OnPreviewAnimationsAttachment1ModelLoad(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
		}

	private:
		ModelEditorTabController* modelEditorTabController;
	};

	popUps->getFileDialogScreenController()->show(
		string(),
		"Load animation preview attachment 1 model from: ",
		ModelReader::getModelExtensions(),
		string(),
		true,
		new OnPreviewAnimationsAttachment1ModelLoad(this)
	);
}

void ModelEditorTabController::onPreviewAnimationsAttachment1ModelClear() {
	attachment1ModelFileName.clear();
	required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("animationpreview_attachment1_model"))->setSource(attachment1ModelFileName);
	required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("animationpreview_attachment1_model"))->setTooltip(attachment1ModelFileName);
	view->addAttachment1(string(), attachment1ModelFileName);
}

void ModelEditorTabController::onPreviewAnimationsAttachment1ModelBrowseTo() {
	if (attachment1ModelFileName.empty() == true) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	view->getEditorView()->getScreenController()->browseTo(attachment1ModelFileName);
}

void ModelEditorTabController::applyAnimationPreviewDetails() {
	try {
		view->setAttachment1NodeId(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animationpreview_attachment1_bone"))->getController()->getValue().getString());
		view->playAnimation(
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animationpreview_base"))->getController()->getValue().getString(),
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animationpreview_overlay1"))->getController()->getValue().getString(),
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animationpreview_overlay2"))->getController()->getValue().getString(),
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animationpreview_overlay3"))->getController()->getValue().getString()
		);
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::applyAnimationPreviewDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void ModelEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	string outlinerNodeModel;
	Model* model = nullptr;
	getOutlinerNodeLOD(outlinerNode, outlinerNodeModel, &model);
	if (outlinerNodeModel == "model.materials") {
		setMaterialBaseDetails();
	} else
	if (StringTools::startsWith(outlinerNodeModel, "model.materials.") == true) {
		setMaterialDetails();
	} else
	if (outlinerNodeModel == "model.animations") {
		setAnimationPreviewDetails();
	} else
	if (StringTools::startsWith(outlinerNodeModel, "model.animations.") == true) {
		auto animationSetup = getSelectedAnimationSetup();
		view->playAnimation(animationSetup == nullptr?Model::ANIMATIONSETUP_DEFAULT:animationSetup->getId());
		setAnimationDetails();
	} else {
		basePropertiesSubController->updateDetails(view->getPrototype(), outlinerNode, view->getPrototype());
		prototypeDisplaySubController->updateDetails(view->getPrototype(), outlinerNode);
		prototypePhysicsSubController->updateDetails(view->getPrototype(), outlinerNode);
		// TODO: model is here always NULLPTR, you cant have selected a LOD and at the same time sounds currently
		prototypeSoundsSubController->updateDetails(view->getPrototype(), view->getPrototype()->getModel(), outlinerNode);
		prototypeScriptSubController->updateDetails(view->getPrototype(), outlinerNode);
	}
}

void ModelEditorTabController::setMaterialDiffuseTexture(const string& fileName) {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
	}
	view->reloadPrototype();
	specularMaterialProperties->setDiffuseTexture(
		Tools::getPathName(fileName),
		Tools::getFileName(fileName),
		specularMaterialProperties->getDiffuseTransparencyTexturePathName(),
		specularMaterialProperties->getDiffuseTransparencyTextureFileName()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadDiffuseTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			modelEditorTabController->setMaterialDiffuseTexture(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, SpecularMaterialProperties* specularMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, specularMaterialProperties(specularMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		SpecularMaterialProperties* specularMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	popUps->getFileDialogScreenController()->show(
		specularMaterialProperties->getDiffuseTextureFileName().empty() == false?specularMaterialProperties->getDiffuseTexturePathName():string(),
		"Load specular diffuse texture from: ",
		extensions,
		specularMaterialProperties->getDiffuseTextureFileName(),
		true,
		new OnLoadTexture(this, specularMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearDiffuseTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
	}
	view->reloadPrototype();
	specularMaterialProperties->setDiffuseTexture(
		string(),
		string(),
		specularMaterialProperties->getDiffuseTransparencyTexturePathName(),
		specularMaterialProperties->getDiffuseTransparencyTextureFileName()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialBrowseToDiffuseTexture() {
	auto model = getSelectedModel();
	if (model == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	if (model->hasEmbeddedSpecularTextures() == true) {
		showInfoPopUp("Browse To", "This model has embedded specular material textures");
		return;
	}
	auto material = getSelectedMaterial();
	if (material == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr || specularMaterialProperties->getDiffuseTextureFileName().empty() == true) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	view->getEditorView()->getScreenController()->browseTo(specularMaterialProperties->getDiffuseTexturePathName() + "/" + specularMaterialProperties->getDiffuseTextureFileName());
}

void ModelEditorTabController::setMaterialDiffuseTransparencyTexture(const string& fileName) {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
	}
	view->reloadPrototype();
	specularMaterialProperties->setDiffuseTexture(
		specularMaterialProperties->getDiffuseTexturePathName(),
		specularMaterialProperties->getDiffuseTextureFileName(),
		Tools::getPathName(fileName),
		Tools::getFileName(fileName)
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadDiffuseTransparencyTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			modelEditorTabController->setMaterialDiffuseTransparencyTexture(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, SpecularMaterialProperties* specularMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, specularMaterialProperties(specularMaterialProperties) {
		}

	private:
		ModelEditorTabController* modelEditorTabController;
		SpecularMaterialProperties* specularMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	popUps->getFileDialogScreenController()->show(
		specularMaterialProperties->getDiffuseTransparencyTextureFileName().empty() == false?specularMaterialProperties->getDiffuseTransparencyTexturePathName():string(),
		"Load specular diffuse transparency texture from: ",
		extensions,
		specularMaterialProperties->getDiffuseTransparencyTextureFileName(),
		true,
		new OnLoadTexture(this, specularMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearDiffuseTransparencyTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
	}
	view->reloadPrototype();
	specularMaterialProperties->setDiffuseTexture(
		specularMaterialProperties->getDiffuseTexturePathName(),
		specularMaterialProperties->getDiffuseTextureFileName(),
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialBrowseToDiffuseTransparencyTexture() {
	auto model = getSelectedModel();
	if (model == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	if (model->hasEmbeddedSpecularTextures() == true) {
		showInfoPopUp("Browse To", "This model has embedded specular material textures");
		return;
	}
	auto material = getSelectedMaterial();
	if (material == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	if (specularMaterialProperties->getDiffuseTransparencyTextureFileName().empty() == false) {
		view->getEditorView()->getScreenController()->browseTo(specularMaterialProperties->getDiffuseTransparencyTexturePathName() + "/" + specularMaterialProperties->getDiffuseTransparencyTextureFileName());
	} else
	if (specularMaterialProperties->getDiffuseTextureFileName().empty() == false) {
		view->getEditorView()->getScreenController()->browseTo(specularMaterialProperties->getDiffuseTexturePathName() + "/" + specularMaterialProperties->getDiffuseTextureFileName());
	} else {
		showInfoPopUp("Browse To", "Nothing to browse to");
	}
}

void ModelEditorTabController::setMaterialNormalTexture(const string& fileName) {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
	}
	view->reloadPrototype();
	specularMaterialProperties->setNormalTexture(
		Tools::getPathName(fileName),
		Tools::getFileName(fileName)
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadNormalTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			modelEditorTabController->setMaterialNormalTexture(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, SpecularMaterialProperties* specularMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, specularMaterialProperties(specularMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		SpecularMaterialProperties* specularMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	popUps->getFileDialogScreenController()->show(
		specularMaterialProperties->getNormalTextureFileName().empty() == false?specularMaterialProperties->getNormalTexturePathName():string(),
		"Load specular normal texture from: ",
		extensions,
		specularMaterialProperties->getNormalTextureFileName(),
		true,
		new OnLoadTexture(this, specularMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearNormalTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
	}
	view->reloadPrototype();
	specularMaterialProperties->setNormalTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialBrowseToNormalTexture() {
	auto model = getSelectedModel();
	if (model == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	if (model->hasEmbeddedSpecularTextures() == true) {
		showInfoPopUp("Browse To", "This model has embedded specular material textures");
		return;
	}
	auto material = getSelectedMaterial();
	if (material == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr || specularMaterialProperties->getNormalTextureFileName().empty() == true) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	view->getEditorView()->getScreenController()->browseTo(specularMaterialProperties->getNormalTexturePathName() + "/" + specularMaterialProperties->getNormalTextureFileName());
}

void ModelEditorTabController::setMaterialSpecularTexture(const string& fileName) {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
	}
	//
	view->reloadPrototype();
	specularMaterialProperties->setSpecularTexture(
		Tools::getPathName(fileName),
		Tools::getFileName(fileName)
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadSpecularTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			modelEditorTabController->setMaterialSpecularTexture(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, SpecularMaterialProperties* specularMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, specularMaterialProperties(specularMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		SpecularMaterialProperties* specularMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	popUps->getFileDialogScreenController()->show(
		specularMaterialProperties->getSpecularTextureFileName().empty() == false?specularMaterialProperties->getSpecularTexturePathName():string(),
		"Load specular specular texture from: ",
		extensions,
		specularMaterialProperties->getSpecularTextureFileName(),
		true,
		new OnLoadTexture(this, specularMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearSpecularTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		material->setSpecularMaterialProperties(specularMaterialProperties = (make_unique<SpecularMaterialProperties>()).release());
	}
	view->reloadPrototype();
	specularMaterialProperties->setSpecularTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialBrowseToSpecularTexture() {
	auto model = getSelectedModel();
	if (model == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	if (model->hasEmbeddedSpecularTextures() == true) {
		showInfoPopUp("Browse To", "This model has embedded specular material textures");
		return;
	}
	auto material = getSelectedMaterial();
	if (material == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr || specularMaterialProperties->getSpecularTextureFileName().empty() == true) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	view->getEditorView()->getScreenController()->browseTo(specularMaterialProperties->getSpecularTexturePathName() + "/" + specularMaterialProperties->getSpecularTextureFileName());
}

void ModelEditorTabController::setMaterialPBRBaseColorTexture(const string& fileName) {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;
	//
	view->reloadPrototype();
	pbrMaterialProperties->setBaseColorTexture(
		Tools::getPathName(fileName),
		Tools::getFileName(fileName)
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadPBRBaseColorTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			modelEditorTabController->setMaterialPBRBaseColorTexture(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, PBRMaterialProperties* pbrMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, pbrMaterialProperties(pbrMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		PBRMaterialProperties* pbrMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	popUps->getFileDialogScreenController()->show(
		pbrMaterialProperties->getBaseColorTextureFileName().empty() == false?pbrMaterialProperties->getBaseColorTexturePathName():string(),
		"Load PBR base color texture from: ",
		extensions,
		pbrMaterialProperties->getBaseColorTextureFileName(),
		true,
		new OnLoadTexture(this, pbrMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearPBRBaseColorTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;
	view->reloadPrototype();
	pbrMaterialProperties->setBaseColorTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialBrowseToPBRBaseColorTexture() {
	auto model = getSelectedModel();
	if (model == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	if (model->hasEmbeddedPBRTextures() == true) {
		showInfoPopUp("Browse To", "This model has embedded PBR material textures");
		return;
	}
	auto material = getSelectedMaterial();
	if (material == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr || pbrMaterialProperties->getBaseColorTextureFileName().empty() == true) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	view->getEditorView()->getScreenController()->browseTo(pbrMaterialProperties->getBaseColorTexturePathName() + "/" + pbrMaterialProperties->getBaseColorTextureFileName());
}

void ModelEditorTabController::setMaterialPBRMetallicRoughnessTexture(const string& fileName) {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;
	//
	view->reloadPrototype();
	pbrMaterialProperties->setMetallicRoughnessTexture(
		Tools::getPathName(fileName),
		Tools::getFileName(fileName)
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadPBRMetallicRoughnessTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			modelEditorTabController->setMaterialPBRMetallicRoughnessTexture(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, PBRMaterialProperties* pbrMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, pbrMaterialProperties(pbrMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		PBRMaterialProperties* pbrMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	popUps->getFileDialogScreenController()->show(
		pbrMaterialProperties->getMetallicRoughnessTextureFileName().empty() == false?pbrMaterialProperties->getMetallicRoughnessTexturePathName():string(),
		"Load PBR metallic/roughness texture from: ",
		extensions,
		pbrMaterialProperties->getMetallicRoughnessTextureFileName(),
		true,
		new OnLoadTexture(this, pbrMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearPBRMetallicRoughnessTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;
	view->reloadPrototype();
	pbrMaterialProperties->setMetallicRoughnessTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialBrowseToPBRMetallicRoughnessTexture() {
	auto model = getSelectedModel();
	if (model == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	if (model->hasEmbeddedPBRTextures() == true) {
		showInfoPopUp("Browse To", "This model has embedded PBR material textures");
		return;
	}
	auto material = getSelectedMaterial();
	if (material == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr || pbrMaterialProperties->getMetallicRoughnessTextureFileName().empty() == true) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	view->getEditorView()->getScreenController()->browseTo(pbrMaterialProperties->getMetallicRoughnessTexturePathName() + "/" + pbrMaterialProperties->getMetallicRoughnessTextureFileName());
}

void ModelEditorTabController::setMaterialPBRNormalTexture(const string& fileName) {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;
	//
	view->reloadPrototype();
	pbrMaterialProperties->setNormalTexture(
		Tools::getPathName(fileName),
		Tools::getFileName(fileName)
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadPBRNormalTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			modelEditorTabController->setMaterialPBRNormalTexture(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, PBRMaterialProperties* pbrMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, pbrMaterialProperties(pbrMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		PBRMaterialProperties* pbrMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	popUps->getFileDialogScreenController()->show(
		pbrMaterialProperties->getNormalTextureFileName().empty() == false?pbrMaterialProperties->getNormalTexturePathName():string(),
		"Load PBR normal texture from: ",
		extensions,
		pbrMaterialProperties->getNormalTextureFileName(),
		true,
		new OnLoadTexture(this, pbrMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearPBRNormalTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;
	view->reloadPrototype();
	pbrMaterialProperties->setNormalTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialBrowseToPBRNormalTexture() {
	auto model = getSelectedModel();
	if (model == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	if (model->hasEmbeddedPBRTextures() == true) {
		showInfoPopUp("Browse To", "This model has embedded PBR material textures");
		return;
	}
	auto material = getSelectedMaterial();
	if (material == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr || pbrMaterialProperties->getNormalTextureFileName().empty() == true) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	view->getEditorView()->getScreenController()->browseTo(pbrMaterialProperties->getNormalTexturePathName() + "/" + pbrMaterialProperties->getNormalTextureFileName());
}

void ModelEditorTabController::setMaterialPBREmissiveTexture(const string& fileName) {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;
	//
	view->reloadPrototype();
	pbrMaterialProperties->setEmissiveTexture(
		Tools::getPathName(fileName),
		Tools::getFileName(fileName)
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadPBREmissiveTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			modelEditorTabController->setMaterialPBREmissiveTexture(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, PBRMaterialProperties* pbrMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, pbrMaterialProperties(pbrMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		PBRMaterialProperties* pbrMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	popUps->getFileDialogScreenController()->show(
		pbrMaterialProperties->getEmissiveTextureFileName().empty() == false?pbrMaterialProperties->getEmissiveTexturePathName():string(),
		"Load PBR emissive texture from: ",
		extensions,
		pbrMaterialProperties->getEmissiveTextureFileName(),
		true,
		new OnLoadTexture(this, pbrMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearPBREmissiveTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;
	view->reloadPrototype();
	pbrMaterialProperties->setEmissiveTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialBrowseToPBREmissiveTexture() {
	auto model = getSelectedModel();
	if (model == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	if (model->hasEmbeddedPBRTextures() == true) {
		showInfoPopUp("Browse To", "This model has embedded PBR material textures");
		return;
	}
	auto material = getSelectedMaterial();
	if (material == nullptr) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr || pbrMaterialProperties->getEmissiveTextureFileName().empty() == true) {
		showInfoPopUp("Browse To", "Nothing to browse to");
		return;
	}
	view->getEditorView()->getScreenController()->browseTo(pbrMaterialProperties->getEmissiveTexturePathName() + "/" + pbrMaterialProperties->getEmissiveTextureFileName());
}

void ModelEditorTabController::startRenameAnimation(int lodLevel, const string& animationId) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	auto selectBoxOptionParentNode = dynamic_cast<GUIParentNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById((lodLevel == 1?"model":"lod" + to_string(lodLevel) + ".model") + ".animations." + animationId));
	if (selectBoxOptionParentNode == nullptr) return;

	renameAnimationId = animationId;
	renameAnimationLOD = lodLevel;
	selectBoxOptionParentNode->replaceSubNodes(
		"<template id=\"tdme.animations.rename_input\" hint=\"Animation name\" text=\"" + GUIParser::escape(animationId) + "\"src=\"resources/engine/gui/template_outliner_rename.xml\" />\n",
		true
	);
	Engine::getInstance()->getGUI()->setFoccussedNode(dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById("tdme.animations.rename_input")));
	view->getEditorView()->getScreenController()->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById("selectbox_outliner")));
}

void ModelEditorTabController::renameAnimation() {
	Model* model = getLODLevelModel(renameAnimationLOD);
	if (model == nullptr) {
		renameAnimationLOD = -1;
		renameAnimationId.clear();
		return;
	}

	auto animationSetup = model->getAnimationSetup(renameAnimationId);
	renameAnimationId.clear();
	if (animationSetup != nullptr) {
		view->playAnimation(Model::ANIMATIONSETUP_DEFAULT);
		try {
			if (model->renameAnimationSetup(
				animationSetup->getId(),
				required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById("tdme.animations.rename_input"))->getController()->getValue().getString()
				) == false) {
				//
				throw ExceptionBase("Could not rename animation");
			}
		} catch (Exception& exception) {
			Console::printLine("ModelEditorTabController::renameAnimation(): An error occurred: " + string(exception.what()));
			showInfoPopUp("Warning", string(exception.what()));
		}
	}

	view->getEditorView()->reloadTabOutliner((renameAnimationLOD == 1?"model":"lod" + to_string(renameAnimationLOD) + ".model") + ".animations" + (animationSetup != nullptr?"." + animationSetup->getId():""));
	renameAnimationLOD = -1;
}

void ModelEditorTabController::createAnimationSetup(int lodLevel) {
	Model* model = getSelectedModel();
	if (model == nullptr) return;

	//
	auto defaultAnimationSetup = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);

	auto animationSetupCreated = false;
	auto animationSetupName = string() + "New animation";
	if (model->getAnimationSetup(animationSetupName) == nullptr &&
		model->addAnimationSetup(animationSetupName, defaultAnimationSetup != nullptr?defaultAnimationSetup->getStartFrame():0, defaultAnimationSetup != nullptr?defaultAnimationSetup->getEndFrame():0, false, 1.0f) != nullptr) {
		animationSetupCreated = true;
	} else {
		//
		for (auto i = 1; i < 10001; i++) {
			animationSetupName = string() + "New animation " + to_string(i);
			if (model->getAnimationSetup(animationSetupName) == nullptr &&
				model->addAnimationSetup(animationSetupName, defaultAnimationSetup != nullptr?defaultAnimationSetup->getStartFrame():0, defaultAnimationSetup != nullptr?defaultAnimationSetup->getEndFrame():0, false, 1.0f) != nullptr) {
				animationSetupCreated = true;
				//
				break;
			}
		}
	}
	try {
		if (animationSetupCreated == false) {
			throw ExceptionBase("Could not create animation");
		}
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::createAnimationSetup(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	if (animationSetupCreated == true) {
		view->getEditorView()->reloadTabOutliner(string() + "model.animations." + animationSetupName);
		startRenameAnimation(lodLevel, animationSetupName);
	}
}

void ModelEditorTabController::createLOD() {
	class OnLoadLODModel: public virtual Action
	{
	public:
		void performAction() override {
			auto lodLevelIdx = -1;
			PrototypeLODLevel* lodLevel = nullptr;
			if (modelEditorTabController->view->getPrototype()->getLODLevel2() == nullptr) {
				lodLevel = modelEditorTabController->getLODLevel(2);
				lodLevelIdx = 2;
			} else
			if (modelEditorTabController->view->getPrototype()->getLODLevel3() == nullptr) {
				lodLevel = modelEditorTabController->getLODLevel(3);
				lodLevelIdx = 3;
			}
			if (lodLevel == nullptr) return;

			lodLevel->setFileName(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
				"/" +
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			lodLevel->setType(LODObject::LODLEVELTYPE_MODEL);
			try {
				lodLevel->setModel(
						lodLevel->getType() == LODObject::LODLEVELTYPE_MODEL?
						ModelReader::read(
							Tools::getPathName(lodLevel->getFileName()),
							Tools::getFileName(lodLevel->getFileName())
						):
						nullptr
				);
			} catch (Exception& exception) {
				Console::printLine("OnLoadLODModel::performAction(): An error occurred: " + string(exception.what()));
				modelEditorTabController->showInfoPopUp("Warning", string(exception.what()));
			}
			modelEditorTabController->view->getEditorView()->reloadTabOutliner("lod" + to_string(lodLevelIdx) + ".model");
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 */
		OnLoadLODModel(ModelEditorTabController* modelEditorTabController)
			: modelEditorTabController(modelEditorTabController) {
			//
		}

	private:
		ModelEditorTabController* modelEditorTabController;
	};

	PrototypeLODLevel* lodLevel = nullptr;
	if (view->getPrototype()->getLODLevel2() != nullptr && view->getPrototype()->getLODLevel3() != nullptr) {
		Console::printLine("ModelEditorTabController::createLOD(): LOD level 2 and LOD level 3 is already in use");
		showInfoPopUp("Warning", "LOD level 2 and LOD level 3 is already in use");
		return;
	}

	popUps->getFileDialogScreenController()->show(
		string(),
		"Load LOD model from: ",
		ModelReader::getModelExtensions(),
		string(),
		true,
		new OnLoadLODModel(this)
	);
}

void ModelEditorTabController::createLODNone() {
	PrototypeLODLevel* lodLevel = nullptr;
	if (view->getPrototype()->getLODLevel2() == nullptr) {
		lodLevel = getLODLevel(2);
	} else
	if (view->getPrototype()->getLODLevel3() == nullptr) {
		lodLevel = getLODLevel(3);
	}
	if (lodLevel == nullptr) return;

	lodLevel->setType(LODObject::LODLEVELTYPE_IGNORE);
	view->getEditorView()->reloadTabOutliner();
	view->getPopUps()->getFileDialogScreenController()->close();
}

void ModelEditorTabController::setLODDetails(int lodLevel) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	PrototypeLODLevel* prototypeLODLevel = nullptr;
	switch (lodLevel) {
		case 2: prototypeLODLevel = prototype->getLODLevel2(); break;
		case 3: prototypeLODLevel = prototype->getLODLevel3(); break;
	}
	if (prototypeLODLevel == nullptr) return;

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_lod\" src=\"resources/engine/gui/template_details_lod.xml\" />\n")
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_lod"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("lod_min_distance"))->getController()->setValue(prototypeLODLevel->getMinDistance());
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::setLODDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	updateLODColorDetails(lodLevel);
}

void ModelEditorTabController::updateLODColorDetails(int lodLevel) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	PrototypeLODLevel* prototypeLODLevel = nullptr;
	switch (lodLevel) {
		case 2: prototypeLODLevel = prototype->getLODLevel2(); break;
		case 3: prototypeLODLevel = prototype->getLODLevel3(); break;
	}
	if (prototypeLODLevel == nullptr) return;

	try {
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("lod_color_add"))->setEffectColorMul(Color4(prototypeLODLevel->getColorAdd()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("lod_color_mul"))->setEffectColorMul(Color4(prototypeLODLevel->getColorMul()));
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::updateLODColorDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void ModelEditorTabController::applyLODDetails(int lodLevel) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	PrototypeLODLevel* prototypeLODLevel = nullptr;
	switch (lodLevel) {
		case 2: prototypeLODLevel = prototype->getLODLevel2(); break;
		case 3: prototypeLODLevel = prototype->getLODLevel3(); break;
	}
	if (prototypeLODLevel == nullptr) return;

	try {
		prototypeLODLevel->setMinDistance(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("lod_min_distance"))->getController()->getValue().getString()));
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabController::applyLODDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

bool ModelEditorTabController::getOutlinerNodeLOD(const string& outlinerNode, string& modelOutlinerNode, Model** model, int* lodLevel) {
	if (StringTools::startsWith(outlinerNode, "model.") == true) {
		if (model != nullptr) *model = view->getPrototype()->getModel();
		if (lodLevel != nullptr) *lodLevel = 1;
		modelOutlinerNode = outlinerNode;
	} else
	if (outlinerNode == "lod2.model") {
		if (model != nullptr) *model = view->getPrototype()->getLODLevel2() != nullptr?view->getPrototype()->getLODLevel2()->getModel():nullptr;
		if (lodLevel != nullptr) *lodLevel = 2;
		modelOutlinerNode = outlinerNode;
	} else
	if (StringTools::startsWith(outlinerNode, "lod2.model.") == true) {
		if (model != nullptr) *model = view->getPrototype()->getLODLevel2() != nullptr?view->getPrototype()->getLODLevel2()->getModel():nullptr;
		if (lodLevel != nullptr) *lodLevel = 2;
		modelOutlinerNode = StringTools::substring(outlinerNode, string("lod2.").size(), outlinerNode.size());
	} else
	if (outlinerNode == "lod3.model") {
		if (model != nullptr) *model = view->getPrototype()->getLODLevel3() != nullptr?view->getPrototype()->getLODLevel3()->getModel():nullptr;
		if (lodLevel != nullptr) *lodLevel = 3;
		modelOutlinerNode = outlinerNode;
	} else
	if (StringTools::startsWith(outlinerNode, "lod3.model.") == true) {
		if (model != nullptr) *model = view->getPrototype()->getLODLevel3() != nullptr?view->getPrototype()->getLODLevel3()->getModel():nullptr;
		if (lodLevel != nullptr) *lodLevel = 3;
		modelOutlinerNode = StringTools::substring(outlinerNode, string("lod3.").size(), outlinerNode.size());
	} else
	if (outlinerNode == "lod4.model") {
		if (model != nullptr) *model = nullptr;
		if (lodLevel != nullptr) *lodLevel = 4;
		modelOutlinerNode = outlinerNode;
	} else
	if (StringTools::startsWith(outlinerNode, "lod4.model.") == true) {
		if (model != nullptr) *model = nullptr;
		if (lodLevel != nullptr) *lodLevel = 4;
		modelOutlinerNode = StringTools::substring(outlinerNode, string("lod4.").size(), outlinerNode.size());
	} else {
		if (model != nullptr) *model = view->getPrototype()->getModel();
		if (lodLevel != nullptr) *lodLevel = 1;
		modelOutlinerNode = outlinerNode;
	}
	return model != nullptr;
}

void ModelEditorTabController::onChange(GUIElementNode* node)
{
	if (basePropertiesSubController->onChange(node, view->getPrototype(), view->getPrototype()) == true) return;
	if (prototypeDisplaySubController->onChange(node, view->getPrototype()) == true) return;
	if (prototypePhysicsSubController->onChange(node, view->getPrototype()) == true) return;
	if (prototypeScriptSubController->onChange(node, view->getPrototype()) == true) return;
	//
	auto model = getSelectedModel();
	if (model != nullptr) {
		if (prototypeSoundsSubController->onChange(node, view->getPrototype(), model) == true) return;
	}
	//
	if (node->getId() == "dropdown_outliner_add") {
		auto addOutlinerType = node->getController()->getValue().getString();
		if (addOutlinerType == "animation") {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			string modelOutlinerNode;
			int lodLevel = -1;
			getOutlinerNodeLOD(outlinerNode, modelOutlinerNode, nullptr, &lodLevel);
			createAnimationSetup(lodLevel);
		} else
		if (addOutlinerType == "lod") {
			createLOD();
		} else
		if (addOutlinerType == "lod_none") {
			createLODNone();
		}
	} else
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		auto haveDetails = false;
		if (outlinerNode == "lod2.model" ||
			StringTools::startsWith(outlinerNode, "lod2.model.") == true) {
			if (view->getLODLevel() != 2) view->setLODLevel(2);
			if (outlinerNode == "lod2.model") {
				haveDetails = true;
				setLODDetails(2);
			}
		} else
		if (outlinerNode == "lod3.model" ||
			StringTools::startsWith(outlinerNode, "lod3.model.") == true) {
			if (view->getLODLevel() != 3) view->setLODLevel(3);
			if (outlinerNode == "lod3.model") {
				haveDetails = true;
				setLODDetails(3);
			}
		} else
		if (outlinerNode == "lod4.model" ||
			StringTools::startsWith(outlinerNode, "lod4.model.") == true) {
			if (view->getLODLevel() != 3) view->setLODLevel(4);
			if (outlinerNode == "lod4.model") {
				haveDetails = true;
				setLODDetails(4);
			}
		} else {
			if (view->getLODLevel() != 1) view->setLODLevel(1);
		}
		//
		if (haveDetails == false) updateDetails(outlinerNode);
	} else {
		//
		for (const auto& applyAnimationNode: applyAnimationNodes) {
			if (node->getId() == applyAnimationNode) {
				applyAnimationDetails();
				break;
			}
		}
		for (const auto& applyMaterialBaseNode: applyMaterialBaseNodes) {
			if (node->getId() == applyMaterialBaseNode) {
				applyMaterialBaseDetails();
				break;
			}
		}
		for (const auto& applySpecularMaterialNode: applySpecularMaterialNodes) {
			if (node->getId() == applySpecularMaterialNode) {
				applySpecularMaterialDetails();
				break;
			}
		}
		for (const auto& applyPBRMaterialNode: applyPBRMaterialNodes) {
			if (node->getId() == applyPBRMaterialNode) {
				applyPBRMaterialDetails();
				break;
			}
		}
		for (const auto& applyAnimationPreviewNode: applyAnimationPreviewNodes) {
			if (node->getId() == applyAnimationPreviewNode) {
				applyAnimationPreviewDetails();
				break;
			}
		}
		{
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			for (const auto& applyLODNode: applyLODNodes) {
				if (node->getId() == applyLODNode) {
					auto lodLevel = -1;
					if (outlinerNode == "lod2.model") {
						lodLevel = 2;
					} else
					if (outlinerNode == "lod3.model") {
						lodLevel = 3;
					}
					if (lodLevel != -1) applyLODDetails(lodLevel);
					break;
				}
			}
		}
	}
}

void ModelEditorTabController::onFocus(GUIElementNode* node) {
	if (basePropertiesSubController->onFocus(node, view->getPrototype()) == true) return;
	if (prototypeSoundsSubController->onFocus(node, view->getPrototype()) == true) return;
}

void ModelEditorTabController::onUnfocus(GUIElementNode* node) {
	if (basePropertiesSubController->onUnfocus(node, view->getPrototype()) == true) return;
	if (prototypeSoundsSubController->onUnfocus(node, view->getPrototype()) == true) return;
	//
	if (node->getId() == "tdme.animations.rename_input") {
		renameAnimation();
	}
}

void ModelEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
	basePropertiesSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
	prototypePhysicsSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
	prototypeSoundsSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		string modelOutlinerNode;
		int lodLevel = -1;
		getOutlinerNodeLOD(outlinerNode, modelOutlinerNode, nullptr, &lodLevel);
		if (outlinerNode == "model") {
			// clear
			popUps->getContextMenuScreenController()->clear();

			// reload
			class OnModelReloadAction: public virtual Action
			{
			public:
				void performAction() override {
					modelEditorTabController->onModelReload();
				}
				OnModelReloadAction(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Reload", "contextmenu_reload", new OnModelReloadAction(this));

			// load
			class OnModelLoadAction: public virtual Action
			{
			public:
				void performAction() override {
					modelEditorTabController->onModelLoad();
				}
				OnModelLoadAction(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Load", "contextmenu_load", new OnModelLoadAction(this));

			// reimport
			class OnModelReimportAction: public virtual Action
			{
			public:
				void performAction() override {
					modelEditorTabController->onModelReimport();
				}
				OnModelReimportAction(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Reimport", "contextmenu_reimport", new OnModelReimportAction(this));

			// generate billboard lod
			class EnqueueOnModelGenerateBillboardLodAction: public virtual Action {
				public:
					void performAction() override {
						auto prototype = modelEditorTabController->getView()->getPrototype();
						if (prototype == nullptr) return;
						auto model = prototype->getModel();
						auto fileName = prototype->getModelFileName();
						try {
							if (prototype->getLODLevel2() != nullptr && prototype->getLODLevel3() != nullptr) {
								throw ExceptionBase("All 3 LOD levels are in use");
							}
							if (fileName.empty() == true) throw ExceptionBase("Could not save file. No filename known");
							auto billboardModelPathName = Tools::getPathName(fileName);
							auto billboardModelFileName = Tools::removeFileExtension(Tools::getFileName(fileName)) + ".lod" + to_string(prototype->getLODLevel2() == nullptr?2:3) + ".tm";
							auto billboardLODModel = GenerateBillboardLOD::generate(
								model,
								billboardModelPathName,
								billboardModelFileName
							);
							if (prototype->getLODLevel2() == nullptr) {
								prototype->setLODLevel2(
									make_unique<PrototypeLODLevel>(
										LODObject::LODLEVELTYPE_MODEL,
										billboardModelPathName + "/" + billboardModelFileName,
										billboardLODModel,
										75.0f
									).release()
								);
							} else
							if (prototype->getLODLevel2() == nullptr) {
								prototype->setLODLevel3(
									make_unique<PrototypeLODLevel>(
										LODObject::LODLEVELTYPE_MODEL,
										billboardModelPathName + "/" + billboardModelFileName,
										billboardLODModel,
										150.0f
									).release()
								);
							}
							modelEditorTabController->getView()->reloadPrototype();
						} catch (Exception& exception) {
							modelEditorTabController->showInfoPopUp("Warning", string(exception.what()));
						}
					}
					EnqueueOnModelGenerateBillboardLodAction(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
			};

			popUps->getContextMenuScreenController()->addMenuItem("Generate billboard LOD", "contextmenu_generatebillboardlod", new EnqueueOnModelGenerateBillboardLodAction(this));

			// generate imposter lod
			class EnqueueOnModelGenerateImposterLodAction: public virtual Action {
				public:
					void performAction() override {
						auto prototype = modelEditorTabController->getView()->getPrototype();
						if (prototype == nullptr) return;
						auto model = prototype->getModel();
						auto fileName = prototype->getModelFileName();
						try {
							if (fileName.empty() == true) throw ExceptionBase("Could not save file. No filename known");
							auto imposterModelPathName = Tools::getPathName(fileName);
							auto imposterModelFileName = Tools::removeFileExtension(Tools::getFileName(fileName)) + ".lod" + to_string(prototype->getLODLevel2() == nullptr?2:3) + ".tm";
							vector<Model*> imposterLODModels;
							vector<string> imposterLODFileNames;
							GenerateImposterLOD::generate(
								model,
								imposterModelPathName,
								imposterModelFileName,
								24,
								imposterLODFileNames,
								imposterLODModels
							);
							prototype->setImposterLOD(
								make_unique<PrototypeImposterLOD>(
									imposterLODFileNames,
									imposterLODModels,
									75.0f
								).release()
							);
							modelEditorTabController->getView()->reloadPrototype();
						} catch (Exception& exception) {
							modelEditorTabController->showInfoPopUp("Warning", string(exception.what()));
						}
					}
					EnqueueOnModelGenerateImposterLodAction(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
			};

			popUps->getContextMenuScreenController()->addMenuItem("Generate imposter LOD", "contextmenu_generateimposterlod", new EnqueueOnModelGenerateImposterLodAction(this));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (outlinerNode == "lod2.model") {
			// clear
			popUps->getContextMenuScreenController()->clear();

			// load
			class OnLODLoadAction: public virtual Action
			{
			public:
				void performAction() override {
					modelEditorTabController->onLODLoad(lodLevel);
				}
				OnLODLoadAction(ModelEditorTabController* modelEditorTabController, int lodLevel): modelEditorTabController(modelEditorTabController), lodLevel(lodLevel) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
				int lodLevel;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Load", "contextmenu_load", new OnLODLoadAction(this, 2));

			// delete
			class OnLODDeleteAction: public virtual Action
			{
			public:
				void performAction() override {
					if (prototype == nullptr) return;
					modelEditorTabController->view->setLODLevel(1);
					prototype->removeLODLevel(lodLevel);
					modelEditorTabController->view->getEditorView()->reloadTabOutliner("model");
				}
				OnLODDeleteAction(ModelEditorTabController* modelEditorTabController, Prototype* prototype, int lodLevel): modelEditorTabController(modelEditorTabController), prototype(prototype), lodLevel(lodLevel) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
				Prototype* prototype;
				int lodLevel;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete", "contextmenu_delete", new OnLODDeleteAction(this, view->getPrototype(), 2));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (outlinerNode == "lod3.model") {
			// clear
			popUps->getContextMenuScreenController()->clear();

			// load
			class OnLODLoadAction: public virtual Action
			{
			public:
				void performAction() override {
					modelEditorTabController->onLODLoad(lodLevel);
				}
				OnLODLoadAction(ModelEditorTabController* modelEditorTabController, int lodLevel): modelEditorTabController(modelEditorTabController), lodLevel(lodLevel) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
				int lodLevel;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Load", "contextmenu_load", new OnLODLoadAction(this, 3));

			// delete
			class OnLODDeleteAction: public virtual Action
			{
			public:
				void performAction() override {
					if (prototype == nullptr) return;
					modelEditorTabController->view->setLODLevel(2);
					prototype->removeLODLevel(lodLevel);
					modelEditorTabController->view->getEditorView()->reloadTabOutliner("lod2.model");
				}
				OnLODDeleteAction(ModelEditorTabController* modelEditorTabController, Prototype* prototype, int lodLevel): modelEditorTabController(modelEditorTabController), prototype(prototype), lodLevel(lodLevel) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
				Prototype* prototype;
				int lodLevel;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete", "contextmenu_delete", new OnLODDeleteAction(this, view->getPrototype(), 3));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (outlinerNode == "lod4.model") {
			// clear
			popUps->getContextMenuScreenController()->clear();

			// delete
			class OnLOD4DeleteAction: public virtual Action
			{
			public:
				void performAction() override {
					if (prototype == nullptr) return;
					modelEditorTabController->view->setLODLevel(1);
					prototype->setImposterLOD(nullptr);
					modelEditorTabController->view->getEditorView()->reloadTabOutliner("model");
				}
				OnLOD4DeleteAction(ModelEditorTabController* modelEditorTabController, Prototype* prototype): modelEditorTabController(modelEditorTabController), prototype(prototype) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
				Prototype* prototype;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete", "contextmenu_delete", new OnLOD4DeleteAction(this, view->getPrototype()));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (modelOutlinerNode == "model.animations") {
			// clear
			popUps->getContextMenuScreenController()->clear();
			// add
			class OnAddAnimationAction: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = modelEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection();
					string modelOutlinerNode;
					int lodLevel = -1;
					modelEditorTabController->getOutlinerNodeLOD(outlinerNode, modelOutlinerNode, nullptr, &lodLevel);
					if (modelOutlinerNode == "model.animations") modelEditorTabController->createAnimationSetup(lodLevel);
				}
				OnAddAnimationAction(ModelEditorTabController* modelEditorTabController, Prototype* prototype): modelEditorTabController(modelEditorTabController), prototype(prototype) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
				Prototype* prototype;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Add Animation", "contextmenu_add", new OnAddAnimationAction(this, view->getPrototype()));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (StringTools::startsWith(modelOutlinerNode, "model.animations.") == true) {
			// clear
			popUps->getContextMenuScreenController()->clear();
			// rename
			class OnRenameAction: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = modelEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection();
					string modelOutlinerNode;
					int lodLevel = -1;
					modelEditorTabController->getOutlinerNodeLOD(outlinerNode, modelOutlinerNode, nullptr, &lodLevel);
					if (StringTools::startsWith(modelOutlinerNode, "model.animations.") == true) {
						modelEditorTabController->startRenameAnimation(
							lodLevel,
							StringTools::substring(modelOutlinerNode, string("model.animations.").size(), modelOutlinerNode.size())
						);
					}
				}
				OnRenameAction(ModelEditorTabController* modelEditorTabController, Prototype* prototype): modelEditorTabController(modelEditorTabController), prototype(prototype) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
				Prototype* prototype;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Rename", "contextmenu_rename", new OnRenameAction(this, view->getPrototype()));

			// separator
			popUps->getContextMenuScreenController()->addMenuSeparator();

			// delete
			class OnDeleteAction: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = modelEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection();
					string modelOutlinerNode;
					int lodLevel = -1;
					modelEditorTabController->getOutlinerNodeLOD(outlinerNode, modelOutlinerNode, nullptr, &lodLevel);
					if (StringTools::startsWith(modelOutlinerNode, "model.animations.") == true) {
						modelEditorTabController->view->playAnimation(Model::ANIMATIONSETUP_DEFAULT);
						auto animationId = StringTools::substring(modelOutlinerNode, string("model.animations.").size(), modelOutlinerNode.size());
						Model* model = modelEditorTabController->getLODLevelModel(lodLevel);
						model->removeAnimationSetup(animationId);
						modelEditorTabController->view->getEditorView()->reloadTabOutliner((lodLevel == 1?"model":"lod" + to_string(lodLevel) + ".model") + ".animations");
					}
				}
				OnDeleteAction(ModelEditorTabController* modelEditorTabController, Prototype* prototype): modelEditorTabController(modelEditorTabController), prototype(prototype) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
				Prototype* prototype;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete", "contextmenu_delete", new OnDeleteAction(this, view->getPrototype()));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		}
	}
}

void ModelEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void ModelEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void ModelEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	auto prototype = view->getPrototype();
	//
	if (basePropertiesSubController->onAction(type, node, prototype) == true) return;
	if (prototypeDisplaySubController->onAction(type, node, prototype) == true) return;
	if (prototypePhysicsSubController->onAction(type, node, prototype) == true) return;
	if (prototypeSoundsSubController->onAction(type, node, prototype) == true) return;
	if (prototypeScriptSubController->onAction(type, node, prototype) == true) return;
	//
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId().compare("specularmaterial_diffuse_texture_open") == 0) {
			onMaterialLoadDiffuseTexture();
		} else
		if (node->getId().compare("specularmaterial_diffuse_texture_remove") == 0) {
			onMaterialClearDiffuseTexture();
		} else
		if (node->getId().compare("specularmaterial_diffuse_texture_browseto") == 0) {
			onMaterialBrowseToDiffuseTexture();
		} else
		if (node->getId().compare("specularmaterial_transparency_texture_open") == 0) {
			onMaterialLoadDiffuseTransparencyTexture();
		} else
		if (node->getId().compare("specularmaterial_transparency_texture_remove") == 0) {
			onMaterialClearDiffuseTransparencyTexture();
		} else
		if (node->getId().compare("specularmaterial_transparency_texture_browseto") == 0) {
			onMaterialBrowseToDiffuseTransparencyTexture();
		} else
		if (node->getId().compare("specularmaterial_normal_texture_open") == 0) {
			onMaterialLoadNormalTexture();
		} else
		if (node->getId().compare("specularmaterial_normal_texture_remove") == 0) {
			onMaterialClearNormalTexture();
		} else
		if (node->getId().compare("specularmaterial_normal_texture_browseto") == 0) {
			onMaterialBrowseToNormalTexture();
		} else
		if (node->getId().compare("specularmaterial_specular_texture_open") == 0) {
			onMaterialLoadSpecularTexture();
		} else
		if (node->getId().compare("specularmaterial_specular_texture_remove") == 0) {
			onMaterialClearSpecularTexture();
		} else
		if (node->getId().compare("specularmaterial_specular_texture_browseto") == 0) {
			onMaterialBrowseToSpecularTexture();
		} else
		if (node->getId().compare("pbrmaterial_basecolor_texture_open") == 0) {
			onMaterialLoadPBRBaseColorTexture();
		} else
		if (node->getId().compare("pbrmaterial_basecolor_texture_remove") == 0) {
			onMaterialClearPBRBaseColorTexture();
		} else
		if (node->getId().compare("pbrmaterial_basecolor_texture_browseto") == 0) {
			onMaterialBrowseToPBRBaseColorTexture();
		} else
		if (node->getId().compare("pbrmaterial_metallic_roughness_texture_open") == 0) {
			onMaterialLoadPBRMetallicRoughnessTexture();
		} else
		if (node->getId().compare("pbrmaterial_metallic_roughness_texture_remove") == 0) {
			onMaterialClearPBRMetallicRoughnessTexture();
		} else
		if (node->getId().compare("pbrmaterial_metallic_roughness_texture_browseto") == 0) {
			onMaterialBrowseToPBRMetallicRoughnessTexture();
		} else
		if (node->getId().compare("pbrmaterial_normal_texture_open") == 0) {
			onMaterialLoadPBRNormalTexture();
		} else
		if (node->getId().compare("pbrmaterial_normal_texture_remove") == 0) {
			onMaterialClearPBRNormalTexture();
		} else
		if (node->getId().compare("pbrmaterial_normal_texture_browseto") == 0) {
			onMaterialBrowseToPBRNormalTexture();
		} else
		if (node->getId().compare("pbrmaterial_emissive_texture_open") == 0) {
			onMaterialLoadPBREmissiveTexture();
		} else
		if (node->getId().compare("pbrmaterial_emissive_texture_remove") == 0) {
			onMaterialClearPBREmissiveTexture();
		} else
		if (node->getId().compare("pbrmaterial_emissive_texture_browseto") == 0) {
			onMaterialBrowseToPBREmissiveTexture();
		} else
		if (node->getId().compare("animationpreview_attachment1_model_open") == 0) {
			onPreviewAnimationsAttachment1ModelLoad();
		} else
		if (node->getId().compare("animationpreview_attachment1_model_remove") == 0) {
			onPreviewAnimationsAttachment1ModelClear();
		} else
		if (node->getId().compare("animationpreview_attachment1_model_browseto") == 0) {
			onPreviewAnimationsAttachment1ModelBrowseTo();
		} else
		if (node->getId().compare("specularmaterial_ambient_edit") == 0) {
			auto material = getSelectedMaterial();
			auto specularMaterialProperties = material != nullptr?material->getSpecularMaterialProperties():nullptr;
			if (specularMaterialProperties != nullptr) {
				class OnColorChangeAction: public virtual Action
				{
				public:
					void performAction() override {
						material->getSpecularMaterialProperties()->setAmbientColor(Color4(modelEditorTabController->popUps->getColorPickerScreenController()->getColor()));
						modelEditorTabController->updateMaterialColorDetails();
					}
					OnColorChangeAction(ModelEditorTabController* modelEditorTabController, Material* material): modelEditorTabController(modelEditorTabController), material(material) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
					Material* material;
				};
				popUps->getColorPickerScreenController()->show(specularMaterialProperties->getAmbientColor(), new OnColorChangeAction(this, material));
			}
		} else
		if (node->getId().compare("specularmaterial_diffuse_edit") == 0) {
			auto material = getSelectedMaterial();
			auto specularMaterialProperties = material != nullptr?material->getSpecularMaterialProperties():nullptr;
			if (specularMaterialProperties != nullptr) {
				class OnColorChangeAction: public virtual Action
				{
				public:
					void performAction() override {
						material->getSpecularMaterialProperties()->setDiffuseColor(Color4(modelEditorTabController->popUps->getColorPickerScreenController()->getColor()));
						modelEditorTabController->updateMaterialColorDetails();
					}
					OnColorChangeAction(ModelEditorTabController* modelEditorTabController, Material* material): modelEditorTabController(modelEditorTabController), material(material) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
					Material* material;
				};
				popUps->getColorPickerScreenController()->show(specularMaterialProperties->getDiffuseColor(), new OnColorChangeAction(this, material));
			}
		} else
		if (node->getId().compare("specularmaterial_emission_edit") == 0) {
			auto material = getSelectedMaterial();
			auto specularMaterialProperties = material != nullptr?material->getSpecularMaterialProperties():nullptr;
			if (specularMaterialProperties != nullptr) {
				class OnColorChangeAction: public virtual Action
				{
				public:
					void performAction() override {
						material->getSpecularMaterialProperties()->setEmissionColor(Color4(modelEditorTabController->popUps->getColorPickerScreenController()->getColor()));
						modelEditorTabController->updateMaterialColorDetails();
					}
					OnColorChangeAction(ModelEditorTabController* modelEditorTabController, Material* material): modelEditorTabController(modelEditorTabController), material(material) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
					Material* material;
				};
				popUps->getColorPickerScreenController()->show(specularMaterialProperties->getEmissionColor(), new OnColorChangeAction(this, material));
			}
		} else
		if (node->getId().compare("specularmaterial_specular_edit") == 0) {
			auto material = getSelectedMaterial();
			auto specularMaterialProperties = material != nullptr?material->getSpecularMaterialProperties():nullptr;
			if (specularMaterialProperties != nullptr) {
				class OnColorChangeAction: public virtual Action
				{
				public:
					void performAction() override {
						material->getSpecularMaterialProperties()->setSpecularColor(Color4(modelEditorTabController->popUps->getColorPickerScreenController()->getColor()));
						modelEditorTabController->updateMaterialColorDetails();
					}
					OnColorChangeAction(ModelEditorTabController* modelEditorTabController, Material* material): modelEditorTabController(modelEditorTabController), material(material) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
					Material* material;
				};
				popUps->getColorPickerScreenController()->show(specularMaterialProperties->getSpecularColor(), new OnColorChangeAction(this, material));
			}
		} else
		if (node->getId().compare("pbrmaterial_basecolor_edit") == 0) {
			auto material = getSelectedMaterial();
			auto pbrMaterialProperties = material != nullptr?material->getPBRMaterialProperties():nullptr;
			if (pbrMaterialProperties != nullptr) {
				class OnColorChangeAction: public virtual Action
				{
				public:
					void performAction() override {
						material->getPBRMaterialProperties()->setBaseColorFactor(Color4(modelEditorTabController->popUps->getColorPickerScreenController()->getColor()));
						modelEditorTabController->updateMaterialColorDetails();
					}
					OnColorChangeAction(ModelEditorTabController* modelEditorTabController, Material* material): modelEditorTabController(modelEditorTabController), material(material) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
					Material* material;
				};
				popUps->getColorPickerScreenController()->show(pbrMaterialProperties->getBaseColorFactor(), new OnColorChangeAction(this, material));
			}
		} else
		if (node->getId().compare("pbrmaterial_emissivefactor_edit") == 0) {
			auto material = getSelectedMaterial();
			auto pbrMaterialProperties = material != nullptr?material->getPBRMaterialProperties():nullptr;
			if (pbrMaterialProperties != nullptr) {
				class OnColorChangeAction: public virtual Action
				{
				public:
					void performAction() override {
						material->getPBRMaterialProperties()->setEmissiveFactor(Color4(modelEditorTabController->popUps->getColorPickerScreenController()->getColor()));
						modelEditorTabController->updateMaterialColorDetails();
					}
					OnColorChangeAction(ModelEditorTabController* modelEditorTabController, Material* material): modelEditorTabController(modelEditorTabController), material(material) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
					Material* material;
				};
				popUps->getColorPickerScreenController()->show(pbrMaterialProperties->getEmissiveFactor(), new OnColorChangeAction(this, material));
			}
		} else
		if (node->getId().compare("lod_color_add_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			string modelOutlinerNode;
			int lodLevel = -1;
			getOutlinerNodeLOD(outlinerNode, modelOutlinerNode, nullptr, &lodLevel);
			PrototypeLODLevel* prototypeLODLevel = nullptr;
			switch (lodLevel) {
				case 2: prototypeLODLevel = prototype->getLODLevel2(); break;
				case 3: prototypeLODLevel = prototype->getLODLevel3(); break;
				default: break;
			}
			if (prototypeLODLevel == nullptr) return;
			class OnColorChangeAction: public virtual Action
			{
			public:
				void performAction() override {
					prototypeLODLevel->setColorAdd(Color4(modelEditorTabController->popUps->getColorPickerScreenController()->getColor()));
					modelEditorTabController->updateLODColorDetails(lodLevel);
					modelEditorTabController->view->updateLODLevel();
				}
				OnColorChangeAction(ModelEditorTabController* modelEditorTabController, int lodLevel, PrototypeLODLevel* prototypeLODLevel): modelEditorTabController(modelEditorTabController), lodLevel(lodLevel), prototypeLODLevel(prototypeLODLevel) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
				int lodLevel;
				PrototypeLODLevel* prototypeLODLevel;
			};
			popUps->getColorPickerScreenController()->show(prototypeLODLevel->getColorAdd(), new OnColorChangeAction(this, lodLevel, prototypeLODLevel));
		} else
		if (node->getId().compare("lod_color_mul_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			string modelOutlinerNode;
			int lodLevel = -1;
			getOutlinerNodeLOD(outlinerNode, modelOutlinerNode, nullptr, &lodLevel);
			PrototypeLODLevel* prototypeLODLevel = nullptr;
			switch (lodLevel) {
				case 2: prototypeLODLevel = prototype->getLODLevel2(); break;
				case 3: prototypeLODLevel = prototype->getLODLevel3(); break;
				default: break;
			}
			if (prototypeLODLevel == nullptr) return;
			class OnColorChangeAction: public virtual Action
			{
			public:
				void performAction() override {
					prototypeLODLevel->setColorMul(Color4(modelEditorTabController->popUps->getColorPickerScreenController()->getColor()));
					modelEditorTabController->updateLODColorDetails(lodLevel);
					modelEditorTabController->view->updateLODLevel();
				}
				OnColorChangeAction(ModelEditorTabController* modelEditorTabController, int lodLevel, PrototypeLODLevel* prototypeLODLevel): modelEditorTabController(modelEditorTabController), lodLevel(lodLevel), prototypeLODLevel(prototypeLODLevel) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
				int lodLevel;
				PrototypeLODLevel* prototypeLODLevel;
			};
			popUps->getColorPickerScreenController()->show(prototypeLODLevel->getColorMul(), new OnColorChangeAction(this, lodLevel, prototypeLODLevel));
		} else
		if (node->getId() == "tdme.animations.rename_input") {
			renameAnimation();
		}
	}
}
