#include <tdme/tools/editor/tabviews/ModelEditorTabView.h>

#include <string>

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
#include <tdme/engine/Object3D.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/ProgressBarScreenController.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandler.h>
#include <tdme/tools/editor/misc/FileDialogPath.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>
#include <tdme/tools/editor/tabcontrollers/ModelEditorTabController.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeSoundsSubView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/views/PlayableSoundView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::audio::Audio;
using tdme::audio::Sound;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::fileio::ProgressCallback;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeAudio;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::subsystems::rendering::ModelStatistics;
using tdme::engine::Engine;
using tdme::engine::ModelUtilities;
using tdme::engine::Object3D;
using tdme::engine::PartitionNone;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::FileDialogPath;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::ModelEditorTabController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView;
using tdme::tools::editor::tabviews::ModelEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::PlayableSoundView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ModelTools;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;

ModelEditorTabView::ModelEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	engine = Engine::createOffScreenInstance(512, 512, true);
	engine->setPartition(new PartitionNone());
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	audio = Audio::getInstance();
	modelEditorTabController = nullptr;
	prototypeDisplayView = nullptr;
	prototypePhysicsView = nullptr;
	prototypeSoundsView = nullptr;
	loadModelRequested = false;
	initModelRequested = false;
	initModelRequestedReset = false;
	prototypeFileName = "";
	lodLevel = 1;
	audioStarted = -1LL;
	audioOffset = -1LL;
	cameraRotationInputHandler = new CameraRotationInputHandler(engine, this);
	setPrototype(prototype);
}

ModelEditorTabView::~ModelEditorTabView() {
	delete prototype;
	delete modelEditorTabController;
	delete cameraRotationInputHandler;
	delete engine;
}

EditorView* ModelEditorTabView::getEditorView() {
	return editorView;
}

TabController* ModelEditorTabView::getTabController() {
	return dynamic_cast<TabController*>(modelEditorTabController);
}

PopUps* ModelEditorTabView::getPopUps()
{
	return popUps;
}

Prototype* ModelEditorTabView::getPrototype()
{
	return prototype;
}

void ModelEditorTabView::setPrototype(Prototype* prototype)
{
	engine->reset();
	if (this->prototype != nullptr) delete this->prototype;
	this->prototype = prototype;
	lodLevel = 1;
	initModelRequested = true;
	initModelRequestedReset = false;
}

void ModelEditorTabView::resetPrototype()
{
	engine->reset();
	initModelRequested = true;
	initModelRequestedReset = true;
}

void ModelEditorTabView::reloadPrototype()
{
	engine->reset();
	initModelRequested = true;
	initModelRequestedReset = false;
}

void ModelEditorTabView::reimportPrototype()
{
	engine->reset();
	initModelRequested = true;
	initModelRequestedReset = false;
}

void ModelEditorTabView::initModel()
{
	if (prototype == nullptr) return;
	engine->removeEntity("model");
	engine->removeEntity("attachment1");
	if (attachment1Model != nullptr) {
		delete attachment1Model;
		attachment1Model = nullptr;
	}
	prototypeFileName = prototype->getFileName().length() > 0 ? prototype->getFileName() : prototype->getModelFileName();
	Tools::setupPrototype(prototype, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale(), lodLevel, objectScale);
	cameraRotationInputHandler->setMaxAxisDimension(Tools::computeMaxAxisDimension(prototype->getModel()->getBoundingBox()));
	auto currentModelObject = dynamic_cast<Object3D*>(engine->getEntity("model"));
	if (currentModelObject != nullptr) {
		ModelStatistics modelStatistics;
		ModelUtilities::computeModelStatistics(currentModelObject->getModel(), &modelStatistics);
		modelEditorTabController->setStatistics(modelStatistics.opaqueFaceCount, modelStatistics.transparentFaceCount, modelStatistics.materialCount);
	} else
	{
		modelEditorTabController->unsetStatistics();
	}
	if (initModelRequestedReset == true) modelEditorTabController->setOutlinerContent();
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
		engine->reset();
		initModelRequested = true;
	}
}

void ModelEditorTabView::updateLODLevel() {
	engine->reset();
	initModelRequested = true;
}

void ModelEditorTabView::loadModel(const string& pathName, const string& fileName)
{
	// new model file
	prototypeFileName = FileSystem::getInstance()->getFileName(pathName, fileName);
	try {
		// set model in entity
		prototype->setModel(
			ModelReader::read(
				pathName,
				fileName
			)
		);
	} catch (Exception& exception) {
		modelEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
	}
	reimportPrototype();
}

void ModelEditorTabView::reimportModel(const string& pathName, const string& fileName)
{
	if (prototype == nullptr) return;
	engine->removeEntity("model");
	engine->removeEntity("attachment1");
	if (attachment1Model != nullptr) {
		delete attachment1Model;
		attachment1Model = nullptr;
	}
	struct AnimationSetupStruct {
		bool loop;
		string overlayFromNodeId;
		float speed;
	};
	// store old animation setups
	map<string, AnimationSetupStruct> originalAnimationSetups;
	for (auto animationSetupIt: prototype->getModel()->getAnimationSetups()) {
		auto animationSetup = animationSetupIt.second;
		originalAnimationSetups[animationSetup->getId()] = {
			.loop = animationSetup->isLoop(),
			.overlayFromNodeId = animationSetup->getOverlayFromNodeId(),
			.speed = animationSetup->getSpeed()
		};
	}
	// new model file
	prototypeFileName = FileSystem::getInstance()->getFileName(pathName, fileName);
	string log;
	try {
		// load model
		auto model = ModelReader::read(
			pathName,
			fileName
		);
		// restore animation setup properties
		for (auto originalAnimationSetupIt: originalAnimationSetups) {
			auto originalAnimationSetupId = originalAnimationSetupIt.first;
			auto originalAnimationSetup = originalAnimationSetupIt.second;
			auto animationSetup = model->getAnimationSetup(originalAnimationSetupId);
			if (animationSetup == nullptr) {
				Console::println("ModelEditorTabView::reimportModel(): missing animation setup: " + originalAnimationSetupId);
				log+= "Missing animation setup: " + originalAnimationSetupId + ", skipping.\n";
				continue;
			}
			Console::println("ModelEditorTabView::reimportModel(): reimport animation setup: " + originalAnimationSetupId);
			animationSetup->setLoop(originalAnimationSetup.loop);
			animationSetup->setOverlayFromNodeId(originalAnimationSetup.overlayFromNodeId);
			animationSetup->setSpeed(originalAnimationSetup.speed);
		}
		// set model in entity
		prototype->setModel(model);
	} catch (Exception& exception) {
		modelEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
	}
	reimportPrototype();
	if (log.size() > 0) {
		modelEditorTabController->showErrorPopUp("Warning", log);
	}
}

void ModelEditorTabView::saveFile(const string& pathName, const string& fileName)
{
	PrototypeWriter::write(pathName, fileName, prototype);
}

void ModelEditorTabView::reloadFile()
{
	loadModelRequested = true;
}

void ModelEditorTabView::pivotApply(float x, float y, float z)
{
	if (prototype == nullptr) return;
	prototype->getPivot().set(x, y, z);
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
	popUps->getProgressBarScreenController()->show();
	ModelTools::computeNormals(prototype->getModel(), new ComputeNormalsProgressCallback(popUps->getProgressBarScreenController()));
	popUps->getProgressBarScreenController()->close();
	resetPrototype();
}

void ModelEditorTabView::optimizeModel() {
	if (prototype == nullptr || prototype->getModel() == nullptr) return;
	engine->removeEntity("model");
	prototype->setModel(ModelTools::optimizeModel(prototype->unsetModel()));
	initModelRequested = true;
}

void ModelEditorTabView::handleInputEvents()
{
	prototypePhysicsView->handleInputEvents(prototype, objectScale);
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
	auto model = static_cast<Object3D*>(engine->getEntity("model"));

	// attachment1
	auto attachment1 = static_cast<Object3D*>(engine->getEntity("attachment1"));
	if (model != nullptr && attachment1 != nullptr) {
		// model attachment bone matrix
		auto transformationsMatrix = model->getNodeTransformationsMatrix(attachment1Bone);
		transformationsMatrix*= model->getTransformations().getTransformationsMatrix();
		attachment1->setTranslation(transformationsMatrix * Vector3(0.0f, 0.0f, 0.0f));
		// euler angles
		auto euler = transformationsMatrix.computeEulerAngles();
		// rotations
		attachment1->setRotationAngle(0, euler.getZ());
		attachment1->setRotationAngle(1, euler.getY());
		attachment1->setRotationAngle(2, euler.getX());
		// scale
		Vector3 scale;
		transformationsMatrix.getScale(scale);
		attachment1->setScale(scale);
		// finally update
		attachment1->update();
	}

	// commands
	if (loadModelRequested == true) {
		initModelRequested = true;
		initModelRequestedReset = false;
		loadModelRequested = false;
		loadModel();
		cameraRotationInputHandler->reset();
	}
	if (initModelRequested == true) {
		initModel();
		initModelRequested = false;
		initModelRequestedReset = false;
		cameraRotationInputHandler->reset();
	}

	// rendering
	prototypeDisplayView->display(prototype);
	prototypePhysicsView->display(prototype);
	engine->display();
}

void ModelEditorTabView::loadSettings()
{
	try {
		Properties settings;
		settings.load("settings", "modeleditor.properties");
		prototypePhysicsView->setDisplayBoundingVolume(settings.get("display.boundingvolumes", "false") == "true");
		prototypeDisplayView->setDisplayGroundPlate(settings.get("display.groundplate", "true") == "true");
		prototypeDisplayView->setDisplayShadowing(settings.get("display.shadowing", "true") == "true");
		modelEditorTabController->getModelPath()->setPath(settings.get("model.path", "."));
		modelEditorTabController->getAudioPath()->setPath(settings.get("audio.path", "."));
	} catch (Exception& exception) {
		Console::print(string("ModelEditorTabView::loadSettings(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void ModelEditorTabView::initialize()
{
	try {
		modelEditorTabController = new ModelEditorTabController(this);
		modelEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
		prototypePhysicsView = modelEditorTabController->getPrototypePhysicsSubController()->getView();
		prototypeDisplayView = modelEditorTabController->getPrototypeDisplaySubController()->getView();
		prototypeSoundsView = modelEditorTabController->getPrototypeSoundsSubController()->getView();
	} catch (Exception& exception) {
		Console::print(string("ModelEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	loadSettings();
	modelEditorTabController->setOutlinerContent();
}

void ModelEditorTabView::storeSettings()
{
	try {
		Properties settings;
		settings.put("display.boundingvolumes", prototypePhysicsView->isDisplayBoundingVolume() == true ? "true" : "false");
		settings.put("display.groundplate", prototypeDisplayView->isDisplayGroundPlate() == true ? "true" : "false");
		settings.put("display.shadowing", prototypeDisplayView->isDisplayShadowing() == true ? "true" : "false");
		settings.put("model.path", modelEditorTabController->getModelPath()->getPath());
		settings.put("audio.path", modelEditorTabController->getAudioPath()->getPath());
		settings.store("settings", "modeleditor.properties");
	} catch (Exception& exception) {
		Console::print(string("ModelEditorTabView::storeSettings(): An error occurred: "));
		Console::println(string(exception.what()));
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
	Console::println(string("Model file: " + prototypeFileName));
	try {
		setPrototype(
			loadModelPrototype(
				FileSystem::getInstance()->getFileName(prototypeFileName),
				"",
				FileSystem::getInstance()->getPathName(prototypeFileName),
				FileSystem::getInstance()->getFileName(prototypeFileName),
				Vector3()
			)
		);
	} catch (Exception& exception) {
		popUps->getInfoDialogScreenController()->show("Warning", (exception.what()));
	}
}

Prototype* ModelEditorTabView::loadModelPrototype(const string& name, const string& description, const string& pathName, const string& fileName, const Vector3& pivot)
{
	if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".tmodel") == true) {
		auto prototype = PrototypeReader::read(
			pathName,
			fileName
		);
		prototype->setDefaultBoundingVolumes();
		return prototype;
	} else {
		auto model = ModelReader::read(
			pathName,
			fileName
		);
		auto prototype = new Prototype(
			Prototype::ID_NONE,
			Prototype_Type::MODEL,
			name,
			description,
			"",
			pathName + "/" + fileName,
			StringTools::replace(StringTools::replace(StringTools::replace(model->getId(), "\\", "_"), "/", "_"), ":", "_") + ".png",
			model,
			pivot
			);
		prototype->setDefaultBoundingVolumes();
		return prototype;

	}
	return nullptr;
}

void ModelEditorTabView::playAnimation(const string& baseAnimationId, const string& overlay1AnimationId, const string& overlay2AnimationId, const string& overlay3AnimationId) {
	auto object = dynamic_cast<Object3D*>(engine->getEntity("model"));
	if (object != nullptr) {
		audio->removeEntity("sound");
		object->removeOverlayAnimations();
		object->setAnimation(baseAnimationId);
		if (overlay1AnimationId.empty() == false) object->addOverlayAnimation(overlay1AnimationId);
		if (overlay2AnimationId.empty() == false) object->addOverlayAnimation(overlay2AnimationId);
		if (overlay3AnimationId.empty() == false) object->addOverlayAnimation(overlay3AnimationId);
	}
}

void ModelEditorTabView::addAttachment1(const string& nodeId, const string& attachmentModelFile) {
	engine->removeEntity("attachment1");
	try {
		if (attachment1Model != nullptr) delete attachment1Model;
		attachment1Model = attachmentModelFile.empty() == true?nullptr:ModelReader::read(Tools::getPathName(attachmentModelFile), Tools::getFileName(attachmentModelFile));
	} catch (Exception& exception) {
		Console::print(string("ModelEditorTabView::addAttachment1(): An error occurred: "));
		Console::println(string(exception.what()));
		popUps->getInfoDialogScreenController()->show("Warning", (exception.what()));
	}
	if (attachment1Model != nullptr) {
		Entity* attachment = nullptr;
		engine->addEntity(attachment = new Object3D("attachment1", attachment1Model));
		attachment->addRotation(Vector3(0.0f, 0.0f, 1.0f), 0.0f);
		attachment->addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
		attachment->addRotation(Vector3(1.0f, 0.0f, 0.0f), 0.0f);
	}
	attachment1Bone = nodeId;
}

void ModelEditorTabView::playSound(const string& soundId) {
	audio->removeEntity("sound");
	auto object = dynamic_cast<Object3D*>(engine->getEntity("model"));
	auto soundDefinition = prototype->getSound(soundId);
	if (soundDefinition != nullptr && soundDefinition->getFileName().length() > 0) {
		if (object != nullptr && soundDefinition->getAnimation().size() > 0) object->setAnimation(soundDefinition->getAnimation());
		auto pathName = PrototypeReader::getResourcePathName(
			Tools::getPathName(prototype->getFileName()),
			soundDefinition->getFileName()
		);
		auto fileName = Tools::getFileName(soundDefinition->getFileName());
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
}

void ModelEditorTabView::stopSound() {
	audio->removeEntity("sound");
}

void ModelEditorTabView::updateRendering() {
	auto object = dynamic_cast<Object3D*>(engine->getEntity("model"));
	if (object == nullptr || prototype == nullptr) return;
	engine->removeEntity("model");
	ModelTools::prepareForShader(prototype->getModel(), prototype->getShader());
	reloadPrototype();
}

void ModelEditorTabView::updateShaderParemeters() {
	auto object = dynamic_cast<Object3D*>(engine->getEntity("model"));
	if (object == nullptr || prototype == nullptr) return;
	auto shaderParametersDefault = Engine::getShaderParameterDefaults(prototype->getShader());
	auto distanceShaderParametersDefault = Engine::getShaderParameterDefaults(prototype->getDistanceShader());
	for (auto& parameterIt: shaderParametersDefault) {
		auto& parameterName = parameterIt.first;
		auto parameterValue = prototype->getShaderParameters().getShaderParameter(parameterName);
		object->setShaderParameter(parameterName, parameterValue);
	}
	for (auto& parameterIt: distanceShaderParametersDefault) {
		auto& parameterName = parameterIt.first;
		auto parameterValue = prototype->getDistanceShaderParameters().getShaderParameter(parameterName);
		object->setDistanceShaderParameter(parameterName, parameterValue);
	}
}

void ModelEditorTabView::onCameraRotation() {
	prototypePhysicsView->updateGizmo(prototype);
}

void ModelEditorTabView::onCameraScale() {
	prototypePhysicsView->updateGizmo(prototype);
}

Engine* ModelEditorTabView::getEngine() {
	return engine;
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
