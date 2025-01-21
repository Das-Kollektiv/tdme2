#include <tdme/tools/editor/tabviews/ModelEditorTabView.h>

#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>

#include <tdme/tdme.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/Sound.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeWriter.h>
#include <tdme/engine/fileio/ProgressCallback.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeAudio.h>
#include <tdme/engine/subsystems/rendering/ModelStatistics.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/ModelUtilities.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/SimplePartition.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/ProgressBarScreenController.h>
#include <tdme/engine/tools/CameraRotationInputHandler.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/engine/tools/FileSystemTools.h>
#include <tdme/engine/tools/ThumbnailTool.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>
#include <tdme/tools/editor/tabcontrollers/ModelEditorTabController.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeSoundsSubView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/views/PlayableSoundView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;

using tdme::audio::Audio;
using tdme::audio::Sound;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::fileio::ProgressCallback;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeAudio;
using tdme::engine::subsystems::rendering::ModelStatistics;
using tdme::engine::Engine;
using tdme::engine::ModelUtilities;
using tdme::engine::Object;
using tdme::engine::SimplePartition;
using tdme::engine::Timing;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::engine::tools::CameraRotationInputHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::engine::tools::FileSystemTools;
using tdme::engine::tools::ThumbnailTool;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::ModelEditorTabController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView;
using tdme::tools::editor::tabviews::ModelEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::PlayableSoundView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ModelTools;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

ModelEditorTabView::ModelEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, true, true, true));
	engine->setPartition(new SimplePartition());
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	audio = Audio::getInstance();
	prototypeDisplayView = nullptr;
	prototypePhysicsView = nullptr;
	prototypeSoundsView = nullptr;
	prototypeFileName = "";
	lodLevel = 1;
	audioStarted = -1LL;
	audioOffset = -1LL;
	cameraRotationInputHandler = make_unique<CameraRotationInputHandler>(engine.get(), this);
	setPrototype(prototype);
	outlinerState.expandedOutlinerParentOptionValues.push_back("prototype");
}

ModelEditorTabView::~ModelEditorTabView() {
}

TabController* ModelEditorTabView::getTabController() {
	return modelEditorTabController.get();
}

void ModelEditorTabView::setPrototype(Prototype* prototype)
{
	engine->reset();
	this->prototype = unique_ptr<Prototype>(prototype);
	lodLevel = 1;
	//
	initModel(false);
	// if setting a prototype before initalize() we have no controller yet
	if (modelEditorTabController != nullptr) modelEditorTabController->setOutlinerContent();
}

void ModelEditorTabView::resetPrototype()
{
	engine->reset();
	initModel(true);
	modelEditorTabController->setOutlinerContent();
}

void ModelEditorTabView::reloadPrototype()
{
	engine->reset();
	initModel(true);
	modelEditorTabController->setOutlinerContent();
}

void ModelEditorTabView::reimportPrototype()
{
	engine->reset();
	initModel(false);
	modelEditorTabController->setOutlinerContent();
}

void ModelEditorTabView::initModel(bool resetup)
{
	if (prototype == nullptr) return;
	engine->removeEntity("model");
	engine->removeEntity("attachment1");
	attachment1Model = nullptr;
	attachment1Bone.clear();
	prototypeFileName = prototype->getFileName().length() > 0 ? prototype->getFileName() : prototype->getModelFileName();
	ThumbnailTool::setupPrototype(prototype.get(), engine.get(), cameraRotationInputHandler->getLookFromRotations(), lodLevel, objectScale, cameraRotationInputHandler.get(), 1.5f, resetup);
	if (prototypePhysicsView != nullptr) prototypePhysicsView->setObjectScale(objectScale);
	auto currentModelObject = dynamic_cast<Object*>(engine->getEntity("model"));
	if (currentModelObject != nullptr) {
		ModelStatistics modelStatistics;
		ModelUtilities::computeModelStatistics(currentModelObject->getModel(), &modelStatistics);
		modelEditorTabController->setStatistics(modelStatistics.opaqueFaceCount, modelStatistics.transparentFaceCount, modelStatistics.materialCount);
	} else
	{
		modelEditorTabController->unsetStatistics();
	}
}

const string& ModelEditorTabView::getFileName()
{
	return prototypeFileName;
}

int ModelEditorTabView::getLODLevel() const {
	return lodLevel;
}

void ModelEditorTabView::setLODLevel(int lodLevel) {
	if (this->lodLevel != lodLevel) {
		this->lodLevel = lodLevel;
		initModel(false);
	}
}

void ModelEditorTabView::updateLODLevel() {
	engine->reset();
	reloadPrototype();
}

void ModelEditorTabView::loadModel(const string& pathName, const string& fileName)
{
	// new model file
	prototypeFileName = FileSystem::getInstance()->composeURI(pathName, fileName);
	try {
		// set model in entity
		prototype->setModel(
			ModelReader::read(
				pathName,
				fileName
			)
		);
	} catch (Exception& exception) {
		modelEditorTabController->showInfoPopUp("Warning", string(exception.what()));
	}
	reimportPrototype();
}

void ModelEditorTabView::reimportModel(const string& pathName, const string& fileName)
{
	if (prototype == nullptr) return;
	engine->removeEntity("model");
	engine->removeEntity("attachment1");
	attachment1Model = nullptr;
	attachment1Bone.clear();
	struct AnimationSetupStruct {
		bool loop;
		string overlayFromNodeId;
		float speed;
	};
	// store old animation setups
	map<string, AnimationSetupStruct> originalAnimationSetups;
	for (const auto& [animationSetupId, animationSetup]: prototype->getModel()->getAnimationSetups()) {
		originalAnimationSetups[animationSetup->getId()] = {
			.loop = animationSetup->isLoop(),
			.overlayFromNodeId = animationSetup->getOverlayFromNodeId(),
			.speed = animationSetup->getSpeed()
		};
	}
	// new model file
	prototypeFileName = FileSystem::getInstance()->composeURI(pathName, fileName);
	string log;
	try {
		// load model
		auto model = unique_ptr<Model>(
			ModelReader::read(
				pathName,
				fileName
			)
		);
		// restore animation setup properties
		for (const auto& [originalAnimationSetupId, originalAnimationSetup]: originalAnimationSetups) {
			auto animationSetup = model->getAnimationSetup(originalAnimationSetupId);
			if (animationSetup == nullptr) {
				Console::printLine("ModelEditorTabView::reimportModel(): missing animation setup: " + originalAnimationSetupId);
				log+= "Missing animation setup: " + originalAnimationSetupId + ", skipping.\n";
				continue;
			}
			Console::printLine("ModelEditorTabView::reimportModel(): reimport animation setup: " + originalAnimationSetupId);
			animationSetup->setLoop(originalAnimationSetup.loop);
			animationSetup->setOverlayFromNodeId(originalAnimationSetup.overlayFromNodeId);
			animationSetup->setSpeed(originalAnimationSetup.speed);
		}
		// set model in entity
		prototype->setModel(model.release());
	} catch (Exception& exception) {
		modelEditorTabController->showInfoPopUp("Warning", string(exception.what()));
	}
	reimportPrototype();
	if (log.size() > 0) {
		modelEditorTabController->showInfoPopUp("Warning", log);
	}
}

void ModelEditorTabView::saveFile(const string& pathName, const string& fileName)
{
	PrototypeWriter::write(pathName, fileName, prototype.get());
}

void ModelEditorTabView::reloadFile()
{
	engine->reset();
	loadModel();
	initModel(true);
	modelEditorTabController->setOutlinerContent();
}

void ModelEditorTabView::computeNormals() {
	if (prototype == nullptr || prototype->getModel() == nullptr) return;
	engine->removeEntity("model");
	class ComputeNormalsProgressCallback: public ProgressCallback {
	private:
		ProgressBarScreenController* progressBarScreenController;
	public:
		ComputeNormalsProgressCallback(ProgressBarScreenController* progressBarScreenController): progressBarScreenController(progressBarScreenController) {
		}
		virtual void progress(float value) {
			progressBarScreenController->progress(value);
		}
	};
	popUps->getProgressBarScreenController()->show("Computing smooth normals ...");
	ModelTools::computeNormals(prototype->getModel(), make_unique<ComputeNormalsProgressCallback>(popUps->getProgressBarScreenController()).release());
	popUps->getProgressBarScreenController()->close();
	resetPrototype();
}

void ModelEditorTabView::optimizeModel() {
	if (prototype == nullptr || prototype->getModel() == nullptr) return;
	engine->removeEntity("model");
	prototype->setModel(ModelTools::optimizeModel(prototype->unsetModel()));
	reloadPrototype();
}

void ModelEditorTabView::handleInputEvents()
{
	prototypePhysicsView->handleInputEvents(prototype.get());
	cameraRotationInputHandler->handleInputEvents();
}

void ModelEditorTabView::display()
{
	// audio
	if (audioOffset > 0 && Time::getCurrentMillis() - audioStarted >= audioOffset) {
		auto sound = audio->getEntity("sound");
		if (sound != nullptr) sound->play();
		audioOffset = -1LL;
	}

	//
	auto model = static_cast<Object*>(engine->getEntity("model"));

	// attachment1
	auto attachment1 = static_cast<Object*>(engine->getEntity("attachment1"));
	if (model != nullptr && attachment1 != nullptr) {
		// model attachment bone matrix
		auto transformMatrix = model->getNodeTransformMatrix(attachment1Bone);
		transformMatrix*= model->getTransform().getTransformMatrix();
		attachment1->setTranslation(transformMatrix * Vector3(0.0f, 0.0f, 0.0f));
		// euler angles
		auto euler = transformMatrix.computeEulerAngles();
		// rotations
		attachment1->setRotationAngle(0, euler.getZ());
		attachment1->setRotationAngle(1, euler.getY());
		attachment1->setRotationAngle(2, euler.getX());
		// scale
		Vector3 scale;
		transformMatrix.getScale(scale);
		attachment1->setScale(scale);
		// finally update
		attachment1->update();
	}

	//
	modelEditorTabController->updateInfoText(MutableString(engine->getTiming()->getAvarageFPS()).append(" FPS"));

	// rendering
	prototypeDisplayView->display(prototype.get());
	prototypePhysicsView->display(prototype.get());
	engine->display();
}

void ModelEditorTabView::loadSettings()
{
	// TODO: a.drewke
	try {
		Properties settings;
		settings.load("settings", "modeleditor.properties");
		prototypePhysicsView->setDisplayBoundingVolume(settings.get("display.boundingvolumes", "false") == "true");
		prototypeDisplayView->setDisplayGroundPlate(settings.get("display.groundplate", "true") == "true");
		prototypeDisplayView->setDisplayShadowing(settings.get("display.shadowing", "true") == "true");
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabView::loadSettings(): An error occurred: " + string(exception.what()));
	}
}

void ModelEditorTabView::initialize()
{
	try {
		modelEditorTabController = make_unique<ModelEditorTabController>(this);
		modelEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
		prototypePhysicsView = modelEditorTabController->getPrototypePhysicsSubController()->getView();
		prototypeDisplayView = modelEditorTabController->getPrototypeDisplaySubController()->getView();
		prototypeSoundsView = modelEditorTabController->getPrototypeSoundsSubController()->getView();
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	//
	loadSettings();
	//
	if (prototypePhysicsView != nullptr) prototypePhysicsView->setObjectScale(objectScale);
}

void ModelEditorTabView::storeSettings()
{
	// TODO: a.drewke
	try {
		Properties settings;
		settings.put("display.boundingvolumes", prototypePhysicsView->isDisplayBoundingVolume() == true ? "true" : "false");
		settings.put("display.groundplate", prototypeDisplayView->isDisplayGroundPlate() == true ? "true" : "false");
		settings.put("display.shadowing", prototypeDisplayView->isDisplayShadowing() == true ? "true" : "false");
		settings.store("settings", "modeleditor.properties");
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabView::storeSettings(): An error occurred: " + string(exception.what()));
	}
}

void ModelEditorTabView::dispose()

{
	storeSettings();
	engine->dispose();
	audio->removeEntity("sound");
}

void ModelEditorTabView::loadModel()
{
	try {
		setPrototype(
			loadModelPrototype(
				FileSystem::getInstance()->getFileName(prototypeFileName),
				"",
				FileSystem::getInstance()->getPathName(prototypeFileName),
				FileSystem::getInstance()->getFileName(prototypeFileName)
			)
		);
	} catch (Exception& exception) {
		popUps->getInfoDialogScreenController()->show("Warning", exception.what());
	}
}

Prototype* ModelEditorTabView::loadModelPrototype(const string& name, const string& description, const string& pathName, const string& fileName)
{
	try {
		auto prototype = unique_ptr<Prototype>(
			PrototypeReader::read(
				pathName,
				fileName
			)
		);
		return prototype.release();
	} catch (Exception& exception) {
		popUps->getInfoDialogScreenController()->show("Warning", exception.what());
	}
	//
	return nullptr;
}

void ModelEditorTabView::playAnimation(const string& baseAnimationId, const string& overlay1AnimationId, const string& overlay2AnimationId, const string& overlay3AnimationId) {
	auto object = dynamic_cast<Object*>(engine->getEntity("model"));
	if (object == nullptr) return;
	audio->removeEntity("sound");
	object->removeOverlayAnimations();
	object->setAnimation(baseAnimationId);
	if (overlay1AnimationId.empty() == false) object->addOverlayAnimation(overlay1AnimationId);
	if (overlay2AnimationId.empty() == false) object->addOverlayAnimation(overlay2AnimationId);
	if (overlay3AnimationId.empty() == false) object->addOverlayAnimation(overlay3AnimationId);
}

void ModelEditorTabView::addAttachment1(const string& nodeId, const string& attachmentModelFile) {
	engine->removeEntity("attachment1");
	try {
		attachment1Model =
			unique_ptr<Model>(
				attachmentModelFile.empty() == true?
					nullptr:
					ModelReader::read(FileSystemTools::getPathName(attachmentModelFile), FileSystemTools::getFileName(attachmentModelFile))
			);
	} catch (Exception& exception) {
		Console::printLine("ModelEditorTabView::addAttachment1(): An error occurred: " + string(exception.what()));
		popUps->getInfoDialogScreenController()->show("Warning", (exception.what()));
	}
	if (attachment1Model != nullptr) {
		Entity* attachment = nullptr;
		engine->addEntity(attachment = new Object("attachment1", attachment1Model.get()));
		attachment->addRotation(Vector3(0.0f, 0.0f, 1.0f), 0.0f);
		attachment->addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
		attachment->addRotation(Vector3(1.0f, 0.0f, 0.0f), 0.0f);
	}
	attachment1Bone = nodeId;
}

void ModelEditorTabView::setAttachment1NodeId(const string& nodeId) {
	attachment1Bone = nodeId;
}

void ModelEditorTabView::playSound(const string& soundId) {
	audio->removeEntity("sound");
	auto object = dynamic_cast<Object*>(engine->getEntity("model"));
	auto soundDefinition = prototype->getSound(soundId);
	if (soundDefinition == nullptr || soundDefinition->getFileName().empty() == true) return;
	///
	if (object != nullptr && soundDefinition->getAnimation().empty() == false) object->setAnimation(soundDefinition->getAnimation());
	auto pathName = PrototypeReader::getResourcePathName(
		FileSystemTools::getPathName(prototype->getFileName()),
		soundDefinition->getFileName()
	);
	auto fileName = FileSystemTools::getFileName(soundDefinition->getFileName());
	auto sound = new Sound(
		"sound",
		pathName,
		fileName
	);
	sound->setGain(soundDefinition->getGain());
	sound->setPitch(soundDefinition->getPitch());
	sound->setLooping(soundDefinition->isLooping());
	sound->setFixed(true);
	audio->addEntity(sound);
	audioStarted = Time::getCurrentMillis();
	audioOffset = -1LL;
	if (soundDefinition->getOffset() <= 0) {
		sound->play();
	} else {
		audioOffset = soundDefinition->getOffset();
	}
}

void ModelEditorTabView::stopSound() {
	audio->removeEntity("sound");
}

void ModelEditorTabView::updateRendering() {
	auto object = dynamic_cast<Object*>(engine->getEntity("model"));
	if (object == nullptr || prototype == nullptr) return;
	engine->removeEntity("model");
	ModelTools::prepareForShader(prototype->getModel(), prototype->getShader());
	reloadPrototype();
}

void ModelEditorTabView::updateShaderParemeters() {
	auto object = dynamic_cast<Object*>(engine->getEntity("model"));
	if (object == nullptr || prototype == nullptr) return;
	for (const auto& parameterName: Engine::getShaderParameterNames(prototype->getShader())) {
		auto parameterValue = prototype->getShaderParameters().getShaderParameter(parameterName);
		object->setShaderParameter(parameterName, parameterValue);
	}
}

void ModelEditorTabView::onCameraRotation() {
	prototypePhysicsView->updateGizmo(prototype.get());
}

void ModelEditorTabView::onCameraScale() {
	prototypePhysicsView->updateGizmo(prototype.get());
}

Engine* ModelEditorTabView::getEngine() {
	return engine.get();
}

void ModelEditorTabView::activate() {
	modelEditorTabController->setOutlinerAddDropDownContent();
	modelEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	modelEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void ModelEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void ModelEditorTabView::reloadOutliner() {
	modelEditorTabController->setOutlinerContent();
	modelEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}
