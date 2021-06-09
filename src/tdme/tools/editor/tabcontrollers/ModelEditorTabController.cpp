#include <tdme/tools/editor/tabcontrollers/ModelEditorTabController.h>

#include <string>
#include <vector>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeLODLevel.h>
#include <tdme/engine/prototype/PrototypeProperty.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/nodes/GUITextureNode.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/FileDialogPath.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeBaseSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/ModelEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::vector;

using tdme::tools::editor::tabcontrollers::ModelEditorTabController;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::engine::prototype::PrototypeProperty;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::nodes::GUITextureNode;
using tdme::gui::GUIParser;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::FileDialogPath;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeBaseSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::ModelEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

ModelEditorTabController::ModelEditorTabController(ModelEditorTabView* view)
{
	class OnSetPrototypeDataAction: public virtual Action
	{
	public:
		void performAction() override {
			finalView->reloadOutliner();
			finalView->onSetPrototypeData();
		}

		/**
		 * Public constructor
		 * @param ModelEditorTabController model editor tab controller
		 * @param finalView final view
		 */
		OnSetPrototypeDataAction(ModelEditorTabController* modelEditorTabController, ModelEditorTabView* finalView)
			: modelEditorTabController(modelEditorTabController)
			, finalView(finalView) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		ModelEditorTabView* finalView;
	};

	this->view = view;
	auto const finalView = view;
	this->prototypeBaseSubController = new PrototypeBaseSubController(view->getEditorView(), new OnSetPrototypeDataAction(this, finalView));
	this->prototypePhysicsSubController = new PrototypePhysicsSubController(view->getEditorView(), view->getEngine(), &modelPath, true);
	this->prototypeSoundsSubController = new PrototypeSoundsSubController(view->getEditorView(), view, &audioPath);
	this->prototypeDisplaySubController = new PrototypeDisplaySubController(view->getEditorView(), view, view->getEngine(), this->prototypePhysicsSubController->getView());
}

ModelEditorTabController::~ModelEditorTabController() {
	delete prototypeBaseSubController;
	delete prototypeDisplaySubController;
	delete prototypePhysicsSubController;
}

ModelEditorTabView* ModelEditorTabController::getView() {
	return view;
}

PrototypeDisplaySubController* ModelEditorTabController::getPrototypeDisplaySubController()
{
	return prototypeDisplaySubController;
}

PrototypePhysicsSubController* ModelEditorTabController::getPrototypePhysicsSubController()
{
	return prototypePhysicsSubController;
}

PrototypeSoundsSubController* ModelEditorTabController::getPrototypeSoundsSubController()
{
	return prototypeSoundsSubController;
}

GUIScreenNode* ModelEditorTabController::getScreenNode()
{
	return screenNode;
}

FileDialogPath* ModelEditorTabController::getModelPath()
{
	return &modelPath;
}

FileDialogPath* ModelEditorTabController::getAudioPath()
{
	return &audioPath;
}

void ModelEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	prototypeBaseSubController->initialize(screenNode);
	prototypeDisplaySubController->initialize(screenNode);
	prototypePhysicsSubController->initialize(screenNode);
	prototypeSoundsSubController->initialize(screenNode);
}

void ModelEditorTabController::dispose()
{
}

void ModelEditorTabController::createOutlinerModelNodesXML(const map<string, Node*>& subNodes, string& xml) {
	for (auto nodeIt: subNodes) {
		auto node = nodeIt.second;
		if (node->getSubNodes().empty() == false) {
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes(node->getId()) + "\" value=\"" + GUIParser::escapeQuotes("model.nodes." + node->getId()) + "\">\n";
			createOutlinerModelNodesXML(node->getSubNodes(), xml);
			xml+= "</selectbox-parent-option>\n";
		} else {
			xml+= "	<selectbox-option text=\"" + GUIParser::escapeQuotes(node->getId()) + "\" value=\"" + GUIParser::escapeQuotes("model.nodes." + node->getId()) + "\" />\n";
		}
	}
}

void ModelEditorTabController::setOutlinerContent() {

	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototype") + "\" value=\"" + GUIParser::escapeQuotes("prototype") + "\">\n";
	auto prototype = view->getPrototype();
	if (prototype != nullptr) {
		prototypeBaseSubController->createPrototypePropertiesXML(prototype, xml);
		prototypeDisplaySubController->createDisplayPropertiesXML(prototype, xml);
		prototypePhysicsSubController->createOutlinerPhysicsXML(prototype, xml);
		prototypeSoundsSubController->createOutlinerSoundsXML(prototype, xml);
		Model* model = view->getLodLevel() == 1?prototype->getModel():getLODLevel(view->getLodLevel())->getModel();
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Model") + "\" value=\"" + GUIParser::escapeQuotes("model") + "\">\n";
		if (model != nullptr) {
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Materials") + "\" value=\"" + GUIParser::escapeQuotes("model.materials") + "\">\n";
			for (auto it: model->getMaterials()) {
				auto materialId = it.second->getId();
				xml+= "	<selectbox-option text=\"" + GUIParser::escapeQuotes(materialId) + "\" value=\"" + GUIParser::escapeQuotes("model.material." + materialId) + "\" />\n";
			}
			xml+= "</selectbox-parent-option>\n";
		}
		if (model != nullptr && model->getSubNodes().empty() == false) {
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Nodes") + "\" value=\"" + GUIParser::escapeQuotes("model.nodes") + "\">\n";
			createOutlinerModelNodesXML(model->getSubNodes(), xml);
			xml+= "</selectbox-parent-option>\n";
		}
		if (model != nullptr &&
			(model->getAnimationSetups().size() > 1 || model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT) == nullptr)) {
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Animations") + "\" value=\"" + GUIParser::escapeQuotes("model.animations") + "\">\n";
			for (auto it: model->getAnimationSetups()) {
				auto animationSetupId = it.second->getId();
				if (animationSetupId == Model::ANIMATIONSETUP_DEFAULT) continue;
				xml+= "	<selectbox-option text=\"" + GUIParser::escapeQuotes(animationSetupId) + "\" value=\"" + GUIParser::escapeQuotes("model.animations." + animationSetupId) + "\" />\n";
			}
			xml+= "</selectbox-parent-option>\n";
		}
		xml+= "</selectbox-parent-option>\n";
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
		string("<dropdown-option text=\"LOD\" value=\"lod\" />\n")
	);
}

void ModelEditorTabController::setDetailsContent() {
	view->getEditorView()->setDetailsContent(string());
}

PrototypeLODLevel* ModelEditorTabController::getLODLevel(int level) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return nullptr;
	switch(level) {
		case 2:
			{
				auto prototypeLodLevel = prototype->getLODLevel2();
				if (prototypeLodLevel == nullptr) {
					prototypeLodLevel = new PrototypeLODLevel(
						LODObject3D::LODLEVELTYPE_NONE,
						"",
						nullptr,
						0.0f
					);
					prototype->setLODLevel2(prototypeLodLevel);
				}
				return prototypeLodLevel;
			}
		case 3:
			{
				auto prototypeLodLevel = prototype->getLODLevel3();
				if (prototypeLodLevel == nullptr) {
					prototypeLodLevel = new PrototypeLODLevel(
						LODObject3D::LODLEVELTYPE_NONE,
						"",
						nullptr,
						0.0f
					);
					prototype->setLODLevel3(prototypeLodLevel);
				}
				return prototypeLodLevel;
			}
		default:
			{
				return nullptr;
			}
	}
}

void ModelEditorTabController::setLODLevel(int level) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	auto prototypeLodLevel = getLODLevel(level);

	view->setLodLevel(level);
}

Material* ModelEditorTabController::getSelectedMaterial() {
	string materialId;
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	if (StringTools::startsWith(outlinerNode, "model.material.") == true) {
		materialId = StringTools::substring(outlinerNode, string("model.material.").size(), outlinerNode.size());
	} else {
		return nullptr;
	}
	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return nullptr;
	auto materialIt = model->getMaterials().find(materialId);
	return materialIt != model->getMaterials().end()?materialIt->second:nullptr;
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

void ModelEditorTabController::onQuit()
{
}

void ModelEditorTabController::onModelLoad()
{
	class OnModelLoad: public virtual Action
	{

	public:
		void performAction() override {
			modelEditorTabController->view->loadFile(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->modelPath.setPath(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
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

	auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
	if (fileName.length() == 0) {
		fileName = view->getFileName();
	}
	fileName = Tools::getFileName(fileName);
	vector<string> extensions = ModelReader::getModelExtensions();
	extensions.push_back("tmodel");
	view->getPopUps()->getFileDialogScreenController()->show(
		modelPath.getPath(),
		"Load from: ",
		extensions,
		view->getFileName(),
		true,
		new OnModelLoad(this)
	);
}

void ModelEditorTabController::onModelSave()
{
	class OnModelSave: public virtual Action
	{
	public:
		void performAction() override {
			try {
				modelEditorTabController->view->saveFile(
					modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
					modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
				);
				modelEditorTabController->modelPath.setPath(
					modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName()
				);
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
			} catch (Exception& exception) {
				modelEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
			}
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
			fileName = Tools::removeFileEnding(fileName) + ".tmodel";
		}
	}
	vector<string> extensions = {
		"tmm"
	};
	fileName = Tools::getFileName(fileName);
	view->getPopUps()->getFileDialogScreenController()->show(
		modelPath.getPath(),
		"Save to: ",
		extensions,
		fileName,
		false,
		new OnModelSave(this)
	);
}

void ModelEditorTabController::onModelReload()
{
	view->reloadFile();
}

void ModelEditorTabController::onModelReimport()
{
	class OnModelLoad: public virtual Action
	{

	public:
		void performAction() override {
			modelEditorTabController->view->reimportModel(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->modelPath.setPath(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
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

	vector<string> extensions = ModelReader::getModelExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		modelPath.getPath(),
		"Reimport model: ",
		ModelReader::getModelExtensions(),
		view->getFileName(),
		true,
		new OnModelLoad(this)
	);
}

void ModelEditorTabController::saveFile(const string& pathName, const string& fileName)
{
	view->saveFile(pathName, fileName);
}

void ModelEditorTabController::loadFile(const string& pathName, const string& fileName)
{
	view->loadFile(pathName, fileName);
}

void ModelEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUps()->getInfoDialogScreenController()->show(caption, message);
}

void ModelEditorTabController::setMaterialDetails() {
	Material* material = getSelectedMaterial();
	if (material == nullptr) return;

	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	auto pbrMaterialProperties = material->getPBRMaterialProperties();

	view->getEditorView()->setDetailsContent(
		"<template id=\"details_material_spec\" src=\"resources/engine/gui/template_details_specularmaterial.xml\" />\n"
		"<template id=\"details_material_pbr\" src=\"resources/engine/gui/template_details_pbrmaterial.xml\" />\n"
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_material_spec"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_material_pbr"))->getActiveConditions().add("open");

		if (pbrMaterialProperties != nullptr) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_details"))->getActiveConditions().add("pbr");
		} else {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_details"))->getActiveConditions().remove("pbr");
		}
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::setMaterialDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}

	//
	updateMaterialDetails();
}

void ModelEditorTabController::updateMaterialDetails() {
	Material* material = getSelectedMaterial();
	if (material == nullptr) return;

	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	auto pbrMaterialProperties = material->getPBRMaterialProperties();

	try {
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_diffuse_texture"))->setSource(
			PrototypeReader::getResourcePathName(
				view->getEditorView()->getScreenController()->getProjectPath(),
				specularMaterialProperties->getDiffuseTexturePathName() + "/" + specularMaterialProperties->getDiffuseTextureFileName()
			) +
			"/" +
			specularMaterialProperties->getDiffuseTextureFileName()
		);
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_transparency_texture"))->setSource(
			PrototypeReader::getResourcePathName(
				view->getEditorView()->getScreenController()->getProjectPath(),
				specularMaterialProperties->getDiffuseTransparencyTexturePathName() + "/" + specularMaterialProperties->getDiffuseTransparencyTextureFileName()
			) +
			"/" +
			specularMaterialProperties->getDiffuseTextureFileName()
		);
		required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("specularmaterial_normal_texture"))->setTexture(specularMaterialProperties->getNormalTexture());
		required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("specularmaterial_specular_texture"))->setTexture(specularMaterialProperties->getSpecularTexture());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_shininess"))->getController()->setValue(specularMaterialProperties->getShininess());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_reflection"))->getController()->setValue(specularMaterialProperties->getReflection());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_maskedtransparency"))->getController()->setValue(MutableString(specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true?"1":""));

		if (pbrMaterialProperties != nullptr) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_enabled"))->getController()->setValue(MutableString("1"));
			required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("pbrmaterial_basecolor_texture"))->setTexture(pbrMaterialProperties->getBaseColorTexture());
			required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("pbrmaterial_metallic_roughness_texture"))->setTexture(pbrMaterialProperties->getMetallicRoughnessTexture());
			required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("pbrmaterial_normal_texture"))->setTexture(pbrMaterialProperties->getNormalTexture());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_metallic_factor"))->getController()->setValue(pbrMaterialProperties->getMetallicFactor());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_roughness_factor"))->getController()->setValue(pbrMaterialProperties->getRoughnessFactor());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_normal_scale"))->getController()->setValue(pbrMaterialProperties->getNormalScale());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_exposure"))->getController()->setValue(pbrMaterialProperties->getExposure());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_maskedtransparency"))->getController()->setValue(MutableString(pbrMaterialProperties->hasBaseColorTextureMaskedTransparency() == true?"1":""));
		} else {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_enabled"))->getController()->setValue(MutableString());
		}
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::updateMaterialDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}

	//
	updateMaterialColorDetails();
}

void ModelEditorTabController::updateMaterialColorDetails() {
	Material* material = getSelectedMaterial();
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
		}
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::updateMaterialColorDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}


void ModelEditorTabController::applySpecularMaterialDetails() {
	Material* material = getSelectedMaterial();
	if (material == nullptr) return;

	auto specularMaterialProperties = material->getSpecularMaterialProperties();

	try {
		specularMaterialProperties->setShininess(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_shininess"))->getController()->getValue().getString()));
		specularMaterialProperties->setReflection(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_reflection"))->getController()->getValue().getString()));
		specularMaterialProperties->setDiffuseTextureMaskedTransparency(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_maskedtransparency"))->getController()->getValue().getString() == "1");
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::applySpecularMaterialDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::applyPBRMaterialDetails() {
	Material* material = getSelectedMaterial();
	if (material == nullptr) return;

	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	try {
		pbrMaterialProperties->setMetallicFactor(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_metallic_factor"))->getController()->getValue().getString()));
		pbrMaterialProperties->setRoughnessFactor(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_roughness_factor"))->getController()->getValue().getString()));
		pbrMaterialProperties->setNormalScale(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_normal_scale"))->getController()->getValue().getString()));
		pbrMaterialProperties->setExposure(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_exposure"))->getController()->getValue().getString()));
		pbrMaterialProperties->setBaseColorTextureMaskedTransparency(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_maskedtransparency"))->getController()->getValue().getString() == "1");
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::applyPBRMaterialDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::setAnimationDetails(const string& animationId) {
	Console::println("ModelEditorTabController::setAnimationDetails(): " + animationId);

	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	auto animationSetup = model->getAnimationSetup(animationId);
	auto defaultAnimation = animationSetup != nullptr && animationSetup->getId() == Model::ANIMATIONSETUP_DEFAULT;

	if (animationSetup == nullptr) return;

	auto defaultAnimationSetup = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_animation\" src=\"resources/engine/gui/template_details_animation.xml\" max-frames=\"") +
		to_string(defaultAnimationSetup != nullptr?defaultAnimationSetup->getEndFrame():0) +
		string("\" />\n")
	);

	{
		auto idx = 0;
		string animationsXML;
		animationsXML =
			animationsXML +
			"<dropdown-option text=\"<None>\" value=\"\" " + (idx == 0 ? "selected=\"true\" " : "") + " />\n";
		idx++;
		for (auto it: model->getNodes()) {
			auto nodeId = it.second->getId();
			animationsXML+=
				"<dropdown-option text=\"" +
				GUIParser::escapeQuotes(nodeId) +
				"\" value=\"" +
				GUIParser::escapeQuotes(nodeId) +
				"\" " +
				(idx == 0 ? "selected=\"true\" " : "") +
				" />\n";
			idx++;
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animation_overlaybone_scrollarea"))->replaceSubNodes(animationsXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

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
		Console::println(string("ModelEditorTabController::setAnimationDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::applyAnimationDetails(const string& animationId) {
	Console::println("ModelEditorTabController::applyAnimationDetails(): " + animationId);

	view->playAnimation(Model::ANIMATIONSETUP_DEFAULT);

	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	auto animationSetup = model->getAnimationSetup(animationId);
	auto defaultAnimation = animationSetup != nullptr && animationSetup->getId() == Model::ANIMATIONSETUP_DEFAULT;

	if (animationSetup == nullptr) return;

	try {
		auto startFrame = Integer::parseInt(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_startframe"))->getController()->getValue().getString());
		auto endFrame = Integer::parseInt(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_endframe"))->getController()->getValue().getString());
		auto speed = Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_speed"))->getController()->getValue().getString());
		auto loop = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_loop"))->getController()->getValue().getString() == "1";
		auto overlayFromNodeId = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_overlaybone"))->getController()->getValue().getString();

		animationSetup->setStartFrame(startFrame < endFrame?startFrame:endFrame);
		animationSetup->setEndFrame(endFrame > startFrame?endFrame:startFrame);
		animationSetup->setSpeed(speed);
		animationSetup->setLoop(loop);
		animationSetup->setOverlayFromNodeId(overlayFromNodeId);

		view->playAnimation(animationId);
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::setAnimationDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}

}

void ModelEditorTabController::setAnimationPreviewDetails() {
	Console::println("ModelEditorTabController::setAnimationPreviewDetails(): ");

	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) {
		return;
	}

	auto defaultAnimationSetup = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_animationpreview\" src=\"resources/engine/gui/template_details_animationpreview.xml\" />\n")
	);

	{
		string animationsXML;
		animationsXML = animationsXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getAnimationSetups()) {
			auto animationSetup = it.second;
			if (animationSetup->isOverlayAnimationSetup() == true) continue;
			animationsXML =
				animationsXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" " +
				" />\n";
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_base_scrollarea"))->replaceSubNodes(animationsXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	{
		string overlayAnimationsXML;
		overlayAnimationsXML = overlayAnimationsXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getAnimationSetups()) {
			auto animationSetup = it.second;
			if (animationSetup->isOverlayAnimationSetup() == false) continue;
			overlayAnimationsXML =
				overlayAnimationsXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" " +
				" />\n";
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_overlay1_scrollarea"))->replaceSubNodes(overlayAnimationsXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_overlay2_scrollarea"))->replaceSubNodes(overlayAnimationsXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_overlay3_scrollarea"))->replaceSubNodes(overlayAnimationsXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	{
		string bonesXML;
		bonesXML = bonesXML + "<dropdown-option text=\"<No bone>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getNodes()) {
			auto node = it.second;
			bonesXML =
				bonesXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(node->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(node->getId()) +
				"\" " +
				" />\n";
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_attachment1_bone_scrollarea"))->replaceSubNodes(bonesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_animationpreview"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::onPreviewAnimationsAttachment1ModelLoad() {
	class OnPreviewAnimationsAttachment1ModelLoad: public virtual Action
	{

	public:
		void performAction() override {
			modelEditorTabController->view->addAttachment1(
				required_dynamic_cast<GUIElementNode*>(modelEditorTabController->screenNode->getNodeById("animationpreview_attachment1_bone"))->getController()->getValue().getString(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->modelPath.setPath(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
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

	vector<string> extensions = ModelReader::getModelExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		modelPath.getPath(),
		"Load animation preview attachment 1 model from: ",
		extensions,
		string(),
		true,
		new OnPreviewAnimationsAttachment1ModelLoad(this)
	);
}

void ModelEditorTabController::onPreviewAnimationsAttachment1ModelClear() {
	view->addAttachment1(string(), string());
}

void ModelEditorTabController::applyAnimationPreviewDetails() {
	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	try {
		view->playAnimation(
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animationpreview_base"))->getController()->getValue().getString(),
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animationpreview_overlay1"))->getController()->getValue().getString(),
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animationpreview_overlay2"))->getController()->getValue().getString(),
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animationpreview_overlay3"))->getController()->getValue().getString()
		);
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::applyAnimationPreviewDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::setSoundDetails(const string& soundId) {
	Console::println("ModelEditorTabController::setSoundDetails(): " + soundId);

	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	prototypeSoundsSubController->setSoundDetails(view->getPrototype(), model, soundId);
}

void ModelEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	if (StringTools::startsWith(outlinerNode, "model.material.") == true) {
		setMaterialDetails();
	} else
	if (outlinerNode == "model.animations") {
		setAnimationPreviewDetails();
	} else
	if (StringTools::startsWith(outlinerNode, "model.animations.") == true) {
		auto animationId = StringTools::substring(outlinerNode, string("model.animations.").size(), outlinerNode.size());
		view->playAnimation(animationId);
		setAnimationDetails(animationId);
	} else {
		prototypeBaseSubController->updateDetails(view->getPrototype(), outlinerNode);
		prototypeDisplaySubController->updateDetails(view->getPrototype(),outlinerNode);
		prototypePhysicsSubController->updateDetails(view->getPrototype(), outlinerNode);
	}
}

void ModelEditorTabController::onMaterialLoadDiffuseTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			specularMaterialProperties->setDiffuseTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName(),
				specularMaterialProperties->getDiffuseTransparencyTexturePathName(),
				specularMaterialProperties->getDiffuseTransparencyTextureFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
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
	view->getPopUps()->getFileDialogScreenController()->show(
		specularMaterialProperties->getDiffuseTextureFileName().empty() == false?specularMaterialProperties->getDiffuseTexturePathName():modelPath.getPath(),
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
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
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

void ModelEditorTabController::onMaterialLoadDiffuseTransparencyTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			specularMaterialProperties->setDiffuseTexture(
				specularMaterialProperties->getDiffuseTexturePathName(),
				specularMaterialProperties->getDiffuseTextureFileName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
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
	view->getPopUps()->getFileDialogScreenController()->show(
		specularMaterialProperties->getDiffuseTransparencyTextureFileName().empty() == false?specularMaterialProperties->getDiffuseTransparencyTexturePathName():modelPath.getPath(),
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
		material->setSpecularMaterialProperties(specularMaterialProperties);
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

void ModelEditorTabController::onMaterialLoadNormalTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			specularMaterialProperties->setNormalTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
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
	view->getPopUps()->getFileDialogScreenController()->show(
		specularMaterialProperties->getNormalTextureFileName().empty() == false?specularMaterialProperties->getNormalTexturePathName():modelPath.getPath(),
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
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}
	view->reloadPrototype();
	specularMaterialProperties->setNormalTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadSpecularTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			specularMaterialProperties->setSpecularTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
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
	view->getPopUps()->getFileDialogScreenController()->show(
		specularMaterialProperties->getSpecularTextureFileName().empty() == false?specularMaterialProperties->getSpecularTexturePathName():modelPath.getPath(),
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
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}
	view->reloadPrototype();
	specularMaterialProperties->setSpecularTexture(
		string(),
		string()
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
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			pbrMaterialProperties->setBaseColorTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
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
	view->getPopUps()->getFileDialogScreenController()->show(
		pbrMaterialProperties->getBaseColorTextureFileName().empty() == false?pbrMaterialProperties->getBaseColorTexturePathName():modelPath.getPath(),
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

void ModelEditorTabController::onMaterialLoadPBRMetallicRoughnessTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			pbrMaterialProperties->setMetallicRoughnessTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
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
	view->getPopUps()->getFileDialogScreenController()->show(
		pbrMaterialProperties->getMetallicRoughnessTextureFileName().empty() == false?pbrMaterialProperties->getMetallicRoughnessTexturePathName():modelPath.getPath(),
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

void ModelEditorTabController::onMaterialLoadPBRNormalTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			pbrMaterialProperties->setNormalTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
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
	view->getPopUps()->getFileDialogScreenController()->show(
		pbrMaterialProperties->getNormalTextureFileName().empty() == false?pbrMaterialProperties->getNormalTexturePathName():modelPath.getPath(),
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

void ModelEditorTabController::onValueChanged(GUIElementNode* node)
{
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	if (node->getId() == "selectbox_outliner") {
		updateDetails(outlinerNode);
	}
	for (auto& applyAnimationNode: applyAnimationNodes) {
		if (node->getId() == applyAnimationNode) {
			auto animationId = StringTools::substring(outlinerNode, string("model.animations.").size(), outlinerNode.size());
			applyAnimationDetails(animationId);
		}
	}
	for (auto& applySpecularMaterialNode: applySpecularMaterialNodes) {
		if (node->getId() == applySpecularMaterialNode) {
			applySpecularMaterialDetails();
			break;
		}
	}
	for (auto& applyPBRMaterialNode: applyPBRMaterialNodes) {
		if (node->getId() == applyPBRMaterialNode) {
			applyPBRMaterialDetails();
			break;
		}
	}
	for (auto& applyAnimationPreviewNode: applyAnimationPreviewNodes) {
		if (node->getId() == applyAnimationPreviewNode) {
			applyAnimationPreviewDetails();
			break;
		}
	}
	prototypeBaseSubController->onValueChanged(node, view->getPrototype());
	prototypeDisplaySubController->onValueChanged(node, view->getPrototype());
	prototypePhysicsSubController->onValueChanged(node, view->getPrototype());
	{
		Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
		if (model != nullptr) prototypeSoundsSubController->onValueChanged(node, view->getPrototype(), model);
	}
}

void ModelEditorTabController::onFocus(GUIElementNode* node) {
	prototypeBaseSubController->onFocus(node, view->getPrototype());
	prototypeSoundsSubController->onFocus(node, view->getPrototype());
}

void ModelEditorTabController::onUnfocus(GUIElementNode* node) {
	prototypeBaseSubController->onUnfocus(node, view->getPrototype());
	prototypeSoundsSubController->onUnfocus(node, view->getPrototype());
}

void ModelEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
	prototypeBaseSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
	prototypePhysicsSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
	prototypeSoundsSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
}

void ModelEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	auto prototype = view->getPrototype();
	prototypeBaseSubController->onActionPerformed(type, node, prototype);
	prototypeDisplaySubController->onActionPerformed(type, node, prototype);
	prototypePhysicsSubController->onActionPerformed(type, node, prototype);
	prototypeSoundsSubController->onActionPerformed(type, node, prototype);
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId().compare("specularmaterial_diffuse_texture_open") == 0) {
			onMaterialLoadDiffuseTexture();
		} else
		if (node->getId().compare("specularmaterial_diffuse_texture_remove") == 0) {
			onMaterialClearDiffuseTexture();
		} else
		if (node->getId().compare("specularmaterial_transparency_texture_open") == 0) {
			onMaterialLoadDiffuseTransparencyTexture();
		} else
		if (node->getId().compare("specularmaterial_transparency_texture_remove") == 0) {
			onMaterialClearDiffuseTransparencyTexture();
		} else
		if (node->getId().compare("specularmaterial_normal_texture_open") == 0) {
			onMaterialLoadNormalTexture();
		} else
		if (node->getId().compare("specularmaterial_normal_texture_remove") == 0) {
			onMaterialClearNormalTexture();
		} else
		if (node->getId().compare("specularmaterial_specular_texture_open") == 0) {
			onMaterialLoadSpecularTexture();
		} else
		if (node->getId().compare("specularmaterial_specular_texture_remove") == 0) {
			onMaterialClearSpecularTexture();
		} else
		if (node->getId().compare("pbrmaterial_basecolor_texture_open") == 0) {
			onMaterialLoadPBRBaseColorTexture();
		} else
		if (node->getId().compare("pbrmaterial_basecolor_texture_remove") == 0) {
			onMaterialClearPBRBaseColorTexture();
		} else
		if (node->getId().compare("pbrmaterial_metallic_roughness_texture_open") == 0) {
			onMaterialLoadPBRMetallicRoughnessTexture();
		} else
		if (node->getId().compare("pbrmaterial_metallic_roughness_texture_remove") == 0) {
			onMaterialClearPBRMetallicRoughnessTexture();
		} else
		if (node->getId().compare("pbrmaterial_normal_texture_open") == 0) {
			onMaterialLoadPBRNormalTexture();
		} else
		if (node->getId().compare("pbrmaterial_normal_texture_remove") == 0) {
			onMaterialClearPBRNormalTexture();
		} else
		if (node->getId().compare("animationpreview_attachment1_model_open") == 0) {
			onPreviewAnimationsAttachment1ModelLoad();
		} else
		if (node->getId().compare("animationpreview_attachment1_model_remove") == 0) {
			onPreviewAnimationsAttachment1ModelClear();
		} else
		if (node->getId().compare("specularmaterial_ambient_edit") == 0) {
			auto material = getSelectedMaterial();
			auto specularMaterialProperties = material != nullptr?material->getSpecularMaterialProperties():nullptr;
			if (specularMaterialProperties != nullptr) {
				class OnColorChangeAction: public virtual Action
				{
				public:
					void performAction() override {
						material->getSpecularMaterialProperties()->setAmbientColor(Color4(modelEditorTabController->view->getPopUps()->getColorPickerScreenController()->getColor()));
						modelEditorTabController->updateMaterialColorDetails();
					}
					OnColorChangeAction(ModelEditorTabController* modelEditorTabController, Material* material): modelEditorTabController(modelEditorTabController), material(material) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
					Material* material;
				};
				view->getPopUps()->getColorPickerScreenController()->show(specularMaterialProperties->getAmbientColor(), new OnColorChangeAction(this, material));
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
						material->getSpecularMaterialProperties()->setDiffuseColor(Color4(modelEditorTabController->view->getPopUps()->getColorPickerScreenController()->getColor()));
						modelEditorTabController->updateMaterialColorDetails();
					}
					OnColorChangeAction(ModelEditorTabController* modelEditorTabController, Material* material): modelEditorTabController(modelEditorTabController), material(material) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
					Material* material;
				};
				view->getPopUps()->getColorPickerScreenController()->show(specularMaterialProperties->getDiffuseColor(), new OnColorChangeAction(this, material));
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
						material->getSpecularMaterialProperties()->setEmissionColor(Color4(modelEditorTabController->view->getPopUps()->getColorPickerScreenController()->getColor()));
						modelEditorTabController->updateMaterialColorDetails();
					}
					OnColorChangeAction(ModelEditorTabController* modelEditorTabController, Material* material): modelEditorTabController(modelEditorTabController), material(material) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
					Material* material;
				};
				view->getPopUps()->getColorPickerScreenController()->show(specularMaterialProperties->getEmissionColor(), new OnColorChangeAction(this, material));
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
						material->getSpecularMaterialProperties()->setSpecularColor(Color4(modelEditorTabController->view->getPopUps()->getColorPickerScreenController()->getColor()));
						modelEditorTabController->updateMaterialColorDetails();
					}
					OnColorChangeAction(ModelEditorTabController* modelEditorTabController, Material* material): modelEditorTabController(modelEditorTabController), material(material) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
					Material* material;
				};
				view->getPopUps()->getColorPickerScreenController()->show(specularMaterialProperties->getSpecularColor(), new OnColorChangeAction(this, material));
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
						material->getPBRMaterialProperties()->setBaseColorFactor(Color4(modelEditorTabController->view->getPopUps()->getColorPickerScreenController()->getColor()));
						modelEditorTabController->updateMaterialColorDetails();
					}
					OnColorChangeAction(ModelEditorTabController* modelEditorTabController, Material* material): modelEditorTabController(modelEditorTabController), material(material) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
					Material* material;
				};
				view->getPopUps()->getColorPickerScreenController()->show(pbrMaterialProperties->getBaseColorFactor(), new OnColorChangeAction(this, material));
			}
		}
		/*
		if (node->getId().compare("button_model_load") == 0) {
			onModelLoad();
		} else
		if (node->getId().compare("button_model_reload") == 0) {
			onModelReload();
		} else
		if (node->getId().compare("button_model_reimport") == 0) {
			onModelReimport();
		} else
		if (node->getId().compare("button_model_save") == 0) {
			onModelSave();
		} else
		if (node->getId().compare("button_pivot_apply") == 0) {
			onPivotApply();
		} else
		if (node->getId().compare("button_rendering_apply") == 0) {
			onRenderingApply();
		} else
		if (node->getId().compare("button_shaderparameters_apply") == 0) {
			onShaderParametersApply();
		} else
		if (node->getId().compare("lod_level_apply") == 0) {
			onLODLevelApply();
		} elsevoid ModelEditorTabController::setPreview() {
	previewAnimationsBaseDropDown->getController()->setDisabled(false);
	previewAnimationsOverlay1DropDown->getController()->setDisabled(false);
	previewAnimationsOverlay2DropDown->getController()->setDisabled(false);
	previewAnimationsOverlay3DropDown->getController()->setDisabled(false);
	previewAnimationsAttachment1BoneDropdown->getController()->setDisabled(false);
	previewAnimationsAttachment1ModelModel->getController()->setDisabled(false);
	previewAnimationsAttachment1ModelLoad->getController()->setDisabled(false);
	previewAnimationsAttachment1ModelClear->getController()->setDisabled(false);
	buttonPreviewApply->getController()->setDisabled(false);

	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) {
		return;
	}

	{
		auto animationsDropDownInnerNode = dynamic_cast< GUIParentNode* >((previewAnimationsBaseDropDown->getScreenNode()->getNodeById(previewAnimationsBaseDropDown->getId() + "_inner")));
		string animationsDropDownInnerNodeSubNodesXML = "";
		animationsDropDownInnerNodeSubNodesXML =
			animationsDropDownInnerNodeSubNodesXML +
			"<scrollarea id=\"" +
			previewAnimationsBaseDropDown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
		animationsDropDownInnerNodeSubNodesXML = animationsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getAnimationSetups()) {
			auto animationSetup = it.second;
			if (animationSetup->isOverlayAnimationSetup() == true) continue;
			animationsDropDownInnerNodeSubNodesXML =
				animationsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" " +
				" />\n";
		}
		animationsDropDownInnerNodeSubNodesXML = animationsDropDownInnerNodeSubNodesXML + "</scrollarea>";
		try {
			animationsDropDownInnerNode->replaceSubNodes(animationsDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setPreview(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	{
		auto animationsDropDownInnerNode1 = dynamic_cast< GUIParentNode* >((previewAnimationsOverlay1DropDown->getScreenNode()->getNodeById(previewAnimationsOverlay1DropDown->getId() + "_inner")));
		auto animationsDropDownInnerNode2 = dynamic_cast< GUIParentNode* >((previewAnimationsOverlay2DropDown->getScreenNode()->getNodeById(previewAnimationsOverlay2DropDown->getId() + "_inner")));
		auto animationsDropDownInnerNode3 = dynamic_cast< GUIParentNode* >((previewAnimationsOverlay3DropDown->getScreenNode()->getNodeById(previewAnimationsOverlay3DropDown->getId() + "_inner")));
		string animationsDropDownInnerNodeSubNodesXML = "";
		animationsDropDownInnerNodeSubNodesXML = animationsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getAnimationSetups()) {
			auto animationSetup = it.second;
			if (animationSetup->isOverlayAnimationSetup() == false) continue;
			animationsDropDownInnerNodeSubNodesXML =
				animationsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" " +
				" />\n";
		}
		try {
			animationsDropDownInnerNode1->replaceSubNodes(
				"<scrollarea id=\"" +
				previewAnimationsOverlay1DropDown->getId() +
				"_inner_scrollarea\" width=\"100%\" height=\"100\">\n" +
				animationsDropDownInnerNodeSubNodesXML +
				"</scrollarea>",
				true
			);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setPreview(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		try {
			animationsDropDownInnerNode2->replaceSubNodes(
				"<scrollarea id=\"" +
				previewAnimationsOverlay2DropDown->getId() +
				"_inner_scrollarea\" width=\"100%\" height=\"100\">\n" +
				animationsDropDownInnerNodeSubNodesXML +
				"</scrollarea>",
				true
			);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setPreview(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		try {
			animationsDropDownInnerNode3->replaceSubNodes(
				"<scrollarea id=\"" +
				previewAnimationsOverlay3DropDown->getId() +
				"_inner_scrollarea\" width=\"100%\" height=\"100\">\n" +
				animationsDropDownInnerNodeSubNodesXML +
				"</scrollarea>",
				true
			);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setPreview(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	{
		auto animationsAttachment1BoneDropDownInnerNode = dynamic_cast< GUIParentNode* >((previewAnimationsAttachment1BoneDropdown->getScreenNode()->getNodeById(previewAnimationsAttachment1BoneDropdown->getId() + "_inner")));
		string animationsAttachment1BoneDropDownInnerNodeSubNodesXML = "";
		animationsAttachment1BoneDropDownInnerNodeSubNodesXML =
			animationsAttachment1BoneDropDownInnerNodeSubNodesXML +
			"<scrollarea id=\"" +
			previewAnimationsAttachment1BoneDropdown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
		animationsAttachment1BoneDropDownInnerNodeSubNodesXML = animationsAttachment1BoneDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"<No bone>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getNodes()) {
			auto node = it.second;
			animationsAttachment1BoneDropDownInnerNodeSubNodesXML =
				animationsAttachment1BoneDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(node->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(node->getId()) +
				"\" " +
				" />\n";
		}
		animationsAttachment1BoneDropDownInnerNodeSubNodesXML = animationsAttachment1BoneDropDownInnerNodeSubNodesXML + "</scrollarea>";
		try {
			animationsAttachment1BoneDropDownInnerNode->replaceSubNodes(animationsAttachment1BoneDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setPreview(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

}

		if (node->getId().compare("lod_model_file_load") == 0) {
			onLODLevelLoadModel();
		} else
		if (node->getId().compare("lod_model_file_clear") == 0) {
			onLODLevelClearModel();
		} else
		if (node->getId().compare("button_lod_apply") == 0) {
			onLODLevelApplySettings();
		} else
		if (node->getId().compare("button_materials_dropdown_apply") == 0) {
			onMaterialDropDownApply();
		} else
		if (node->getId().compare("button_materials_material_apply") == 0) {
			onMaterialApply();
		} else
		if (node->getId().compare("button_materials_material_diffuse_texture_load") == 0) {
			onMaterialLoadDiffuseTexture();
		} else
		if (node->getId().compare("button_materials_material_diffuse_transparency_texture_load") == 0) {
			onMaterialLoadDiffuseTransparencyTexture();
		} else
		if (node->getId().compare("button_materials_material_normal_texture_load") == 0) {
			onMaterialLoadNormalTexture();
		} else
		if (node->getId().compare("button_materials_material_specular_texture_load") == 0) {
			onMaterialLoadSpecularTexture();
		} else
		if (node->getId().compare("button_materials_material_diffuse_texture_clear") == 0) {
			onMaterialClearTexture(materialsMaterialDiffuseTexture);
		} else
		if (node->getId().compare("button_materials_material_diffuse_transparency_texture_clear") == 0) {
			onMaterialClearTexture(materialsMaterialDiffuseTransparencyTexture);
		} else
		if (node->getId().compare("button_materials_material_normal_texture_clear") == 0) {
			onMaterialClearTexture(materialsMaterialNormalTexture);
		} else
		if (node->getId().compare("button_materials_material_specular_texture_clear") == 0) {
			onMaterialClearTexture(materialsMaterialSpecularTexture);
		} else
		if (node->getId().compare("button_materials_material_pbr_base_color_texture_load") == 0) {
			onMaterialLoadPBRBaseColorTexture();
		} else
		if (node->getId().compare("button_materials_material_pbr_base_color_texture_clear") == 0) {
			onMaterialClearTexture(materialsMaterialPBRBaseColorTexture);
		} else
		if (node->getId().compare("button_materials_material_pbr_metallic_roughness_texture_load") == 0) {
			onMaterialLoadPBRMetallicRoughnessTexture();
		} else
		if (node->getId().compare("button_materials_material_pbr_metallic_roughness_texture_clear") == 0) {
			onMaterialClearTexture(materialsMaterialPBRMetallicRoughnessTexture);
		} else
		if (node->getId().compare("button_materials_material_pbr_normal_texture_load") == 0) {
			onMaterialLoadPBRNormalTexture();
		} else
		if (node->getId().compare("button_materials_material_pbr_normal_texture_clear") == 0) {
			onMaterialClearTexture(materialsMaterialPBRNormalTexture);
		} else
		if (node->getId().compare("animations_dropdown_apply") == 0) {
			onAnimationDropDownApply();
		} else
		if (node->getId().compare("animations_dropdown_delete") == 0) {
			onAnimationDropDownDelete();
		} else
		if (node->getId().compare("button_animations_animation_apply") == 0) {
			onAnimationApply();
		} else
		if (node->getId().compare("preview_animations_attachment1_model_load") == 0) {
			onPreviewAnimationsAttachment1ModelLoad();
		} else
		if (node->getId().compare("preview_animations_attachment1_model_clear") == 0) {
			onPreviewAnimationsAttachment1ModelClear();
		} else
		if (node->getId().compare("button_preview_apply") == 0) {
			onPreviewApply();
		} else
		if (node->getId().compare("button_tools_computenormals") == 0) {
			onToolsComputeNormal();
		} else
		if (node->getId().compare("button_tools_optimizemodel") == 0) {
			onToolsOptimizeModel();
		}
		*/
	}
}
