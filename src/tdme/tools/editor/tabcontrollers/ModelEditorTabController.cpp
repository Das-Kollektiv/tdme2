#include <tdme/tools/editor/tabcontrollers/ModelEditorTabController.h>

#include <string>
#include <vector>

#include "subcontrollers/BasePropertiesSubController.h"
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
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
#include <tdme/gui/nodes/GUITextureNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/GenerateBillboardLOD.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
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

using std::string;
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
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::engine::Engine;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextureNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::GenerateBillboardLOD;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
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
	this->basePropertiesSubController = new BasePropertiesSubController(view->getEditorView(), "prototype");
	this->prototypePhysicsSubController = new PrototypePhysicsSubController(view->getEditorView(), view, true);
	this->prototypeSoundsSubController = new PrototypeSoundsSubController(view->getEditorView(), view);
	this->prototypeDisplaySubController = new PrototypeDisplaySubController(view->getEditorView(), view, this->prototypePhysicsSubController->getView());
}

ModelEditorTabController::~ModelEditorTabController() {
	delete basePropertiesSubController;
	delete prototypeDisplaySubController;
	delete prototypePhysicsSubController;
	delete prototypeSoundsSubController;
}

ModelEditorTabView* ModelEditorTabController::getView() {
	return view;
}

GUIScreenNode* ModelEditorTabController::getScreenNode()
{
	return screenNode;
}

void ModelEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
	prototypeDisplaySubController->initialize(screenNode);
	prototypePhysicsSubController->initialize(screenNode);
	prototypeSoundsSubController->initialize(screenNode);
}

void ModelEditorTabController::dispose()
{
}

void ModelEditorTabController::save()
{
	auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
	try {
		if (fileName.empty() == true) throw ExceptionBase("Could not save file. No filename known");
		view->saveFile(
			Tools::getPathName(fileName),
			Tools::getFileName(fileName)
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::saveAs()
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
				modelEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
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
			fileName = Tools::removeFileEnding(fileName) + ".tmodel";
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

void ModelEditorTabController::createOutlinerModelNodesXML(const string& prefix, const map<string, Node*>& subNodes, string& xml) {
	for (auto nodeIt: subNodes) {
		auto node = nodeIt.second;
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
			xml+= "<selectbox-parent-option image=\"resources/engine/images/" + image + "\" text=\"" + GUIParser::escapeQuotes(node->getId()) + "\" value=\"" + GUIParser::escapeQuotes(prefix + ".nodes." + node->getId()) + "\">\n";
			createOutlinerModelNodesXML(prefix, node->getSubNodes(), xml);
			xml+= "</selectbox-parent-option>\n";
		} else {
			xml+= "	<selectbox-option image=\"resources/engine/images/" + image + "\" text=\"" + GUIParser::escapeQuotes(node->getId()) + "\" value=\"" + GUIParser::escapeQuotes(prefix + ".nodes." + node->getId()) + "\" />\n";
		}
	}
}

void ModelEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototype") + "\" value=\"" + GUIParser::escapeQuotes("prototype") + "\">\n";
	auto prototype = view->getPrototype();
	if (prototype != nullptr) {
		basePropertiesSubController->createBasePropertiesXML(prototype, xml);
		prototypeDisplaySubController->createDisplayPropertiesXML(prototype, xml);
		prototypePhysicsSubController->createOutlinerPhysicsXML(prototype, xml);
		prototypeSoundsSubController->createOutlinerSoundsXML(prototype, xml);
		for (auto lodLevel = 1; lodLevel < 4; lodLevel++) {
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
			}
			auto modelPrefix = lodLevel == 1?"model":"lod" + to_string(lodLevel) + ".model";
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes(lodLevel != 1?"LOD " + to_string(lodLevel) + " Model":"Model") + "\" value=\"" + GUIParser::escapeQuotes(modelPrefix) + "\">\n";
			if (model != nullptr) {
				xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Materials") + "\" value=\"" + GUIParser::escapeQuotes(modelPrefix + ".materials") + "\">\n";
				for (auto it: model->getMaterials()) {
					auto materialId = it.second->getId();
					xml+= "	<selectbox-option image=\"resources/engine/images/material.png\" text=\"" + GUIParser::escapeQuotes(materialId) + "\" value=\"" + GUIParser::escapeQuotes(modelPrefix + ".materials." + materialId) + "\" />\n";
				}
				xml+= "</selectbox-parent-option>\n";
			}
			if (model != nullptr && model->getSubNodes().empty() == false) {
				xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Nodes") + "\" value=\"" + GUIParser::escapeQuotes(modelPrefix + ".nodes") + "\">\n";
				createOutlinerModelNodesXML(modelPrefix, model->getSubNodes(), xml);
				xml+= "</selectbox-parent-option>\n";
			}
			if (model != nullptr &&
				(model->getAnimationSetups().size() > 1 || model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT) == nullptr)) {
				xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Animations") + "\" value=\"" + GUIParser::escapeQuotes(modelPrefix + ".animations") + "\">\n";
				for (auto it: model->getAnimationSetups()) {
					auto animationSetupId = it.second->getId();
					if (animationSetupId == Model::ANIMATIONSETUP_DEFAULT) continue;
					xml+= "	<selectbox-option image=\"resources/engine/images/animation.png\" text=\"" + GUIParser::escapeQuotes(animationSetupId) + "\" id=\"" + GUIParser::escapeQuotes(modelPrefix + ".animations." + animationSetupId) + "\" value=\"" + GUIParser::escapeQuotes(modelPrefix + ".animations." + animationSetupId) + "\" />\n";
				}
				xml+= "</selectbox-parent-option>\n";
			}
			xml+= "</selectbox-parent-option>\n";
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
		string("<dropdown-option text=\"LOD\" value=\"lod\" />\n")
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
					prototypeLodLevel = new PrototypeLODLevel(
						LODObject3D::LODLEVELTYPE_NONE,
						"",
						nullptr,
						75.0f
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
						150.0f
					);
					prototype->setLODLevel3(prototypeLodLevel);
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
				Console::println(string("OnLODLoad::performAction(): An error occurred: ") + exception.what());;
				modelEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
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

void ModelEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
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
				view->getEditorView()->getScreenController()->getProjectPath() + "/resources",
				specularMaterialProperties->getDiffuseTexturePathName() + "/" + specularMaterialProperties->getDiffuseTextureFileName()
			) +
			"/" +
			specularMaterialProperties->getDiffuseTextureFileName()
		);
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_transparency_texture"))->setSource(
			PrototypeReader::getResourcePathName(
				view->getEditorView()->getScreenController()->getProjectPath() + "/resources",
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

void ModelEditorTabController::setAnimationDetails() {
	Console::println("ModelEditorTabController::setAnimationDetails(): ");

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

void ModelEditorTabController::applyAnimationDetails() {
	Console::println("ModelEditorTabController::applyAnimationDetails(): ");

	view->playAnimation(Model::ANIMATIONSETUP_DEFAULT);

	auto model = getSelectedModel();
	auto animationSetup = getSelectedAnimationSetup();
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

		view->playAnimation(animationSetup->getId());
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::setAnimationDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::setAnimationPreviewDetails() {
	Console::println("ModelEditorTabController::setAnimationPreviewDetails(): ");

	auto model = getSelectedModel();
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
				modelEditorTabController->popUps->getFileDialogScreenController()->getPathName() + "/" + modelEditorTabController->popUps->getFileDialogScreenController()->getFileName()
			);
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
	view->addAttachment1(string(), string());
}

void ModelEditorTabController::applyAnimationPreviewDetails() {
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

void ModelEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	string outlinerNodeModel;
	Model* model = nullptr;
	getOutlinerNodeLOD(outlinerNode, outlinerNodeModel, &model);
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
		basePropertiesSubController->updateDetails(view->getPrototype(), outlinerNode);
		prototypeDisplaySubController->updateDetails(view->getPrototype(), outlinerNode);
		prototypePhysicsSubController->updateDetails(view->getPrototype(), outlinerNode);
		prototypeSoundsSubController->updateDetails(view->getPrototype(), model, outlinerNode);
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
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName(),
				specularMaterialProperties->getDiffuseTransparencyTexturePathName(),
				specularMaterialProperties->getDiffuseTransparencyTextureFileName()
			);
			modelEditorTabController->updateMaterialDetails();
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
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
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
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
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
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
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
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
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
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
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
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
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

void ModelEditorTabController::startRenameAnimation(int lodLevel, const string& animationId) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	auto selectBoxOptionParentNode = dynamic_cast<GUIParentNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById((lodLevel == 1?"model":"lod" + to_string(lodLevel) + ".model") + ".animations." + animationId));
	if (selectBoxOptionParentNode == nullptr) return;

	renameAnimationId = animationId;
	renameAnimationLOD = lodLevel;
	selectBoxOptionParentNode->replaceSubNodes(
		"<template id=\"tdme.animations.rename_input\" hint=\"Animation name\" text=\"" + GUIParser::escapeQuotes(animationId) + "\"src=\"resources/engine/gui/template_outliner_rename.xml\" />\n",
		true
	);
	Engine::getInstance()->getGUI()->setFoccussedNode(dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById("tdme.animations.rename_input")));
	view->getEditorView()->getScreenController()->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById("selectbox_outliner")));
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
			Console::println(string("ModelEditorTabController::renameAnimation(): An error occurred: ") + exception.what());;
			showErrorPopUp("Warning", (string(exception.what())));
		}
	}

	//
	class ReloadTabOutlinerAction: public Action {
	private:
		EditorView* editorView;
		string outlinerNode;
	public:
		ReloadTabOutlinerAction(EditorView* editorView, const string& outlinerNode): editorView(editorView), outlinerNode(outlinerNode) {}
		virtual void performAction() {
			editorView->reloadTabOutliner(outlinerNode);
		}
	};
	Engine::getInstance()->enqueueAction(new ReloadTabOutlinerAction(view->getEditorView(), (renameAnimationLOD == 1?"model":"lod" + to_string(renameAnimationLOD) + ".model") + ".animations" + (animationSetup != nullptr?"." + animationSetup->getId():"")));
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
		Console::println(string("ModelEditorTabController::createAnimationSetup(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
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
			PrototypeLODLevel* lodLevel = nullptr;
			if (modelEditorTabController->view->getPrototype()->getLODLevel2() == nullptr) {
				lodLevel = modelEditorTabController->getLODLevel(2);
			} else
			if (modelEditorTabController->view->getPrototype()->getLODLevel3() == nullptr) {
				lodLevel = modelEditorTabController->getLODLevel(3);
			}
			if (lodLevel == nullptr) return;

			lodLevel->setFileName(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
				"/" +
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			lodLevel->setType(LODObject3D::LODLEVELTYPE_MODEL);
			try {
				lodLevel->setModel(
						lodLevel->getType() == LODObject3D::LODLEVELTYPE_MODEL?
						ModelReader::read(
							Tools::getPathName(lodLevel->getFileName()),
							Tools::getFileName(lodLevel->getFileName())
						):
						nullptr
				);
			} catch (Exception& exception) {
				Console::println(string("OnLoadLODModel::performAction(): An error occurred: ") + exception.what());;
				modelEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
			}
			modelEditorTabController->view->getEditorView()->reloadTabOutliner();
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
		Console::println("ModelEditorTabController::createLOD(): LOD level 2 and LOD level 3 is already in use");
		showErrorPopUp("Warning", "LOD level 2 and LOD level 3 is already in use");
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

void ModelEditorTabController::setLODDetails(int lodLevel) {
	Console::println("ModelEditorTabController::setLODDetails(): ");

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
		Console::println(string("ModelEditorTabController::setLODDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}

	//
	updateLODColorDetails(lodLevel);
}

void ModelEditorTabController::updateLODColorDetails(int lodLevel) {
	Console::println("ModelEditorTabController::updateLODColorDetails(): ");

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
		Console::println(string("ModelEditorTabController::updateLODColorDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::applyLODDetails(int lodLevel) {
	Console::println("ModelEditorTabController::applyLODDetails(): ");

	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	PrototypeLODLevel* prototypeLODLevel = nullptr;
	switch (lodLevel) {
		case 2: prototypeLODLevel = prototype->getLODLevel2(); break;
		case 3: prototypeLODLevel = prototype->getLODLevel3(); break;
	}
	if (prototypeLODLevel == nullptr) return;

	try {
		prototypeLODLevel->setMinDistance(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("lod_min_distance"))->getController()->getValue().getString()));
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::applyLODDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
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
		if (lodLevel != nullptr) *lodLevel = 2;
		modelOutlinerNode = StringTools::substring(outlinerNode, string("lod3.").size(), outlinerNode.size());
	} else {
		if (model != nullptr) *model = view->getPrototype()->getModel();
		if (lodLevel != nullptr) *lodLevel = 1;
		modelOutlinerNode = outlinerNode;
	}
	return model != nullptr;
}

void ModelEditorTabController::onValueChanged(GUIElementNode* node)
{
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
		}
	} else
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		Console::println(outlinerNode);
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
		} else {
			if (view->getLODLevel() != 1) view->setLODLevel(1);
		}
		if (haveDetails == false) updateDetails(outlinerNode);
	} else {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		for (auto& applyAnimationNode: applyAnimationNodes) {
			if (node->getId() == applyAnimationNode) {
				applyAnimationDetails();
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
		for (auto& applyLODNode: applyLODNodes) {
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
	basePropertiesSubController->onValueChanged(node, view->getPrototype());
	prototypeDisplaySubController->onValueChanged(node, view->getPrototype());
	prototypePhysicsSubController->onValueChanged(node, view->getPrototype());
	{
		auto model = getSelectedModel();
		if (model != nullptr) prototypeSoundsSubController->onValueChanged(node, view->getPrototype(), model);
	}
}

void ModelEditorTabController::onFocus(GUIElementNode* node) {
	basePropertiesSubController->onFocus(node, view->getPrototype());
	prototypeSoundsSubController->onFocus(node, view->getPrototype());
}

void ModelEditorTabController::onUnfocus(GUIElementNode* node) {
	basePropertiesSubController->onUnfocus(node, view->getPrototype());
	prototypeSoundsSubController->onUnfocus(node, view->getPrototype());
	if (node->getId() == "tdme.animations.rename_input") {
		renameAnimation();
	}
}

void ModelEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
	basePropertiesSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
	prototypePhysicsSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
	prototypeSoundsSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
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
			class OnModelGenerateBillboardLodAction: public virtual Action
			{
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
						auto billboardModelFileName = Tools::removeFileEnding(Tools::getFileName(fileName)) + ".lod" + to_string(prototype->getLODLevel2() == nullptr?2:3) + ".tm";
						auto billboardLODModel = GenerateBillboardLOD::generateBillboardLOD(
							model,
							billboardModelPathName,
							billboardModelFileName
						);
						if (prototype->getLODLevel2() == nullptr) {
							prototype->setLODLevel2(
								new PrototypeLODLevel(
									LODObject3D::LODLEVELTYPE_MODEL,
									billboardModelPathName + "/" + billboardModelFileName,
									billboardLODModel,
									75.0f
								)
							);
						} else
						if (prototype->getLODLevel2() == nullptr) {
							prototype->setLODLevel3(
								new PrototypeLODLevel(
									LODObject3D::LODLEVELTYPE_MODEL,
									billboardModelPathName + "/" + billboardModelFileName,
									billboardLODModel,
									150.0f
								)
							);
						}
						modelEditorTabController->getView()->reloadPrototype();
					} catch (Exception& exception) {
						modelEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
					}
				}
				OnModelGenerateBillboardLodAction(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
				}
			private:
				ModelEditorTabController* modelEditorTabController;
			};

			class EnqueueOnModelGenerateBillboardLodAction: public virtual Action {
				public:
					void performAction() override {
						Engine::getInstance()->enqueueAction(new OnModelGenerateBillboardLodAction(modelEditorTabController));
					}
					EnqueueOnModelGenerateBillboardLodAction(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
					}
				private:
					ModelEditorTabController* modelEditorTabController;
			};

			popUps->getContextMenuScreenController()->addMenuItem("Generate billboard LOD", "contextmenu_generatebillboardlod", new EnqueueOnModelGenerateBillboardLodAction(this));

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

void ModelEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	auto prototype = view->getPrototype();
	basePropertiesSubController->onActionPerformed(type, node, prototype);
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
