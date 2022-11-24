#include <tdme/tools/editor/tabcontrollers/ParticleSystemEditorTabController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_BoundingBoxParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_Emitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_FogParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_ObjectParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_SphereParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_Type.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transform.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
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
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/ParticleSystemEditorTabView.h>
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

using tdme::tools::editor::tabcontrollers::ParticleSystemEditorTabController;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_BoundingBoxParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::engine::prototype::PrototypeParticleSystem_Emitter;
using tdme::engine::prototype::PrototypeParticleSystem_FogParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_ObjectParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_PointParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_PointParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_SphereParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_Type;
using tdme::engine::Engine;
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeScriptSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::ParticleSystemEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

ParticleSystemEditorTabController::ParticleSystemEditorTabController(ParticleSystemEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->basePropertiesSubController = new BasePropertiesSubController(view->getEditorView(), "prototype");
	this->prototypePhysicsSubController = new PrototypePhysicsSubController(view->getEditorView(), view, false);
	this->prototypeDisplaySubController = new PrototypeDisplaySubController(view->getEditorView(), view, prototypePhysicsSubController->getView());
	this->prototypeSoundsSubController = new PrototypeSoundsSubController(view->getEditorView(), view);
	this->prototypeScriptSubController = new PrototypeScriptSubController(view->getEditorView());
}

ParticleSystemEditorTabController::~ParticleSystemEditorTabController() {
	delete basePropertiesSubController;
	delete prototypePhysicsSubController;
	delete prototypeDisplaySubController;
	delete prototypeSoundsSubController;
	delete prototypeScriptSubController;
}

ParticleSystemEditorTabView* ParticleSystemEditorTabController::getView() {
	return view;
}

GUIScreenNode* ParticleSystemEditorTabController::getScreenNode()
{
	return screenNode;
}

void ParticleSystemEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
	prototypePhysicsSubController->initialize(screenNode);
	prototypeDisplaySubController->initialize(screenNode);
	prototypeSoundsSubController->initialize(screenNode);
	prototypeScriptSubController->initialize(screenNode);
	setOutlinerContent();
}

void ParticleSystemEditorTabController::dispose()
{
}

void ParticleSystemEditorTabController::executeCommand(TabControllerCommand command)
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
					showInfoPopUp("Warning", (string(exception.what())));
				}
			}
			break;
		case COMMAND_SAVEAS:
			{
				class OnParticleSave: public virtual Action
				{
				public:
					void performAction() override {
						try {
							particleSystemEditorTabController->view->saveFile(
								particleSystemEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
								particleSystemEditorTabController->popUps->getFileDialogScreenController()->getFileName()
							);
						} catch (Exception& exception) {
							particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
						}
						particleSystemEditorTabController->popUps->getFileDialogScreenController()->close();
					}
					OnParticleSave(ParticleSystemEditorTabController* particleSystemEditorTabController): particleSystemEditorTabController(particleSystemEditorTabController) {
					}
				private:
					ParticleSystemEditorTabController* particleSystemEditorTabController;
				};

				auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
				popUps->getFileDialogScreenController()->show(
					fileName.empty() == false?Tools::getPathName(fileName):string(),
					"Save to: ",
					{{ "tparticle" }},
					Tools::getFileName(fileName),
					false,
					new OnParticleSave(this)
				);
			}
			break;
		default:
			showInfoPopUp("Warning", "This command is not supported yet");
			break;
	}
}

void ParticleSystemEditorTabController::updateInfoText(const MutableString& text) {
	required_dynamic_cast<GUITextNode*>(screenNode->getNodeById(view->getTabId() + "_tab_text_info"))->setText(text);
}

void ParticleSystemEditorTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void ParticleSystemEditorTabController::onChange(GUIElementNode* node)
{
	Console::println("ParticleSystemEditorTabController::onChange(): " + node->getId() + ": " + node->getController()->getValue().getString());

	//
	if (node->getId() == "dropdown_outliner_add") {
		if (node->getController()->getValue().getString() == "particlesystem") {
			// TODO: move me into a method as I am using it also in context menu, too lazy right now :D
			auto prototype = view->getPrototype();
			if (prototype == nullptr) return;
			auto particleSystem = prototype->addParticleSystem();
			if (particleSystem == nullptr) return;
			auto particleSystemIdx = prototype->getParticleSystemsCount() - 1;

			//
			class ReloadTabOutlinerAction: public Action {
			private:
				ParticleSystemEditorTabController* particleSystemEditorTabController;
				string outlinerNode;
			public:
				ReloadTabOutlinerAction(ParticleSystemEditorTabController* particleSystemEditorTabController, const string& outlinerNode): particleSystemEditorTabController(particleSystemEditorTabController), outlinerNode(outlinerNode) {}
				virtual void performAction() {
					particleSystemEditorTabController->view->uninitParticleSystem();
					auto editorView = particleSystemEditorTabController->view->getEditorView();
					editorView->reloadTabOutliner(outlinerNode);
					particleSystemEditorTabController->view->initParticleSystem();
				}
			};
			Engine::getInstance()->enqueueAction(new ReloadTabOutlinerAction(this, "particlesystems." + to_string(particleSystemIdx)));
		}
	} else
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(view->getEditorView()->getScreenController()->getOutlinerSelection(), "particlesystems.") == true) {
			auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
			view->setParticleSystemIndex(particleSystemIdx, false);
		} else {
			view->setParticleSystemIndex(-1, false);
		}
		updateDetails(outlinerNode);
	} else {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
			auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
			for (auto& applyOPSNode: applyOPSNodes) {
				if (node->getId() == applyOPSNode) {
					applyParticleSystemDetails(particleSystemIdx);
					break;
				}
			}
			for (auto& applyPPSNode: applyPPSNodes) {
				if (node->getId() == applyPPSNode) {
					applyParticleSystemDetails(particleSystemIdx);
					break;
				}
			}
			for (auto& applyFPSNode: applyFPSNodes) {
				if (node->getId() == applyFPSNode) {
					applyParticleSystemDetails(particleSystemIdx);
					break;
				}
			}
			for (auto& applyBaseNode: applyBaseNodes) {
				if (node->getId() == applyBaseNode) {
					applyParticleSystemDetails(particleSystemIdx);
					break;
				}
			}
			for (auto& applyBBPENode: applyBBPENodes) {
				if (node->getId() == applyBBPENode) {
					applyParticleSystemDetails(particleSystemIdx);
					break;
				}
			}
			for (auto& applyPPENode: applyPPENodes) {
				if (node->getId() == applyPPENode) {
					applyParticleSystemDetails(particleSystemIdx);
					break;
				}
			}
			for (auto& applySPENode: applySPENodes) {
				if (node->getId() == applySPENode) {
					applyParticleSystemDetails(particleSystemIdx);
					break;
				}
			}
			for (auto& applyCPENode: applyCPENodes) {
				if (node->getId() == applyCPENode) {
					applyParticleSystemDetails(particleSystemIdx);
					break;
				}
			}
			for (auto& applyRPENode: applyRPENodes) {
				if (node->getId() == applyRPENode) {
					applyParticleSystemDetails(particleSystemIdx);
					break;
				}
			}
		}
	}
	//
	basePropertiesSubController->onChange(node, view->getPrototype());
	prototypeDisplaySubController->onChange(node, view->getPrototype());
	prototypePhysicsSubController->onChange(node, view->getPrototype());
	prototypeSoundsSubController->onChange(node, view->getPrototype(), nullptr);
	prototypeScriptSubController->onChange(node, view->getPrototype());
}

void ParticleSystemEditorTabController::onFocus(GUIElementNode* node) {
	basePropertiesSubController->onFocus(node, view->getPrototype());
	prototypeSoundsSubController->onFocus(node, view->getPrototype());
}

void ParticleSystemEditorTabController::onUnfocus(GUIElementNode* node) {
	basePropertiesSubController->onUnfocus(node, view->getPrototype());
	prototypeSoundsSubController->onUnfocus(node, view->getPrototype());
}

void ParticleSystemEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {

	basePropertiesSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
	prototypePhysicsSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
	prototypeSoundsSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (outlinerNode == "particlesystems") {
			// clear
			popUps->getContextMenuScreenController()->clear();

			// delete
			class OnAddParticleSystemAction: public virtual Action
			{
			public:
				void performAction() override {
					auto prototype = particleSystemEditorTabController->view->getPrototype();
					if (prototype == nullptr) return;
					auto particleSystem = prototype->addParticleSystem();
					if (particleSystem == nullptr) return;
					auto particleSystemIdx = prototype->getParticleSystemsCount() - 1;

					//
					class ReloadTabOutlinerAction: public Action {
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						string outlinerNode;
					public:
						ReloadTabOutlinerAction(ParticleSystemEditorTabController* particleSystemEditorTabController, const string& outlinerNode): particleSystemEditorTabController(particleSystemEditorTabController), outlinerNode(outlinerNode) {}
						virtual void performAction() {
							particleSystemEditorTabController->view->uninitParticleSystem();
							auto editorView = particleSystemEditorTabController->view->getEditorView();
							editorView->reloadTabOutliner(outlinerNode);
							particleSystemEditorTabController->view->initParticleSystem();
						}
					};
					Engine::getInstance()->enqueueAction(new ReloadTabOutlinerAction(particleSystemEditorTabController, "particlesystems." + to_string(particleSystemIdx)));
				}
				OnAddParticleSystemAction(ParticleSystemEditorTabController* particleSystemEditorTabController): particleSystemEditorTabController(particleSystemEditorTabController) {
				}
			private:
				ParticleSystemEditorTabController* particleSystemEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Add Particle System", "contextmenu_add", new OnAddParticleSystemAction(this));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
			auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));

			// clear
			popUps->getContextMenuScreenController()->clear();

			// delete
			class OnRemoveParticleSystemAction: public virtual Action
			{
			public:
				void performAction() override {
					auto prototype = particleSystemEditorTabController->view->getPrototype();
					if (prototype == nullptr) return;
					prototype->removeParticleSystemAt(particleSystemIdx);

					//
					class ReloadTabOutlinerAction: public Action {
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						string outlinerNode;
					public:
						ReloadTabOutlinerAction(ParticleSystemEditorTabController* particleSystemEditorTabController, const string& outlinerNode): particleSystemEditorTabController(particleSystemEditorTabController), outlinerNode(outlinerNode) {}
						virtual void performAction() {
							particleSystemEditorTabController->view->uninitParticleSystem();
							auto editorView = particleSystemEditorTabController->view->getEditorView();
							editorView->reloadTabOutliner(outlinerNode);
							particleSystemEditorTabController->view->initParticleSystem();
						}
					};
					Engine::getInstance()->enqueueAction(new ReloadTabOutlinerAction(particleSystemEditorTabController, "particlesystems"));
				}
				OnRemoveParticleSystemAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
				}
			private:
				ParticleSystemEditorTabController* particleSystemEditorTabController;
				int particleSystemIdx;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Remove Particle System", "contextmenu_remove", new OnRemoveParticleSystemAction(this, particleSystemIdx));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		}
	}
}

void ParticleSystemEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int left, top;
	view->getEditorView()->getViewPortUnscaledOffset(left, top);
	popUps->getTooltipScreenController()->show(left + mouseX, top + mouseY, node->getToolTip());
}

void ParticleSystemEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void ParticleSystemEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	//
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId().compare("particleemitter_box_colorstart_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto bbpe = particleSystem != nullptr?particleSystem->getBoundingBoxParticleEmitters():nullptr;
				if (bbpe != nullptr) {
					//
					class OnColorChangeAction: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							if (prototype == nullptr) return;
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto bbpe = particleSystem != nullptr?particleSystem->getBoundingBoxParticleEmitters():nullptr;
							if (bbpe == nullptr) return;
							bbpe->setColorStart(Color4(particleSystemEditorTabController->popUps->getColorPickerScreenController()->getColor()));
							//
							try {
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particleemitter_box_colorstart"))->setEffectColorMul(bbpe->getColorStart());
							} catch (Exception& exception) {
								Console::println(string("OnColorChangeAction::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							particleSystemEditorTabController->view->initParticleSystem();
						}
						OnColorChangeAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};
					popUps->getColorPickerScreenController()->show(bbpe->getColorStart(), new OnColorChangeAction(this, particleSystemIdx));
				}
			}
		} else
		if (node->getId().compare("particleemitter_box_colorend_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto bbpe = particleSystem != nullptr?particleSystem->getBoundingBoxParticleEmitters():nullptr;
				if (bbpe != nullptr) {
					//
					class OnColorChangeAction: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							if (prototype == nullptr) return;
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto bbpe = particleSystem != nullptr?particleSystem->getBoundingBoxParticleEmitters():nullptr;
							if (bbpe == nullptr) return;
							bbpe->setColorEnd(Color4(particleSystemEditorTabController->popUps->getColorPickerScreenController()->getColor()));
							//
							try {
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particleemitter_box_colorend"))->setEffectColorMul(bbpe->getColorEnd());
							} catch (Exception& exception) {
								Console::println(string("OnColorChangeAction::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							particleSystemEditorTabController->view->initParticleSystem();
						}
						OnColorChangeAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};
					popUps->getColorPickerScreenController()->show(bbpe->getColorEnd(), new OnColorChangeAction(this, particleSystemIdx));
				}
			}
		} else
		if (node->getId().compare("particleemitter_point_colorstart_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto ppe = particleSystem != nullptr?particleSystem->getPointParticleEmitter():nullptr;
				if (ppe != nullptr) {
					//
					class OnColorChangeAction: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							if (prototype == nullptr) return;
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto ppe = particleSystem != nullptr?particleSystem->getPointParticleEmitter():nullptr;
							if (ppe == nullptr) return;
							ppe->setColorStart(Color4(particleSystemEditorTabController->popUps->getColorPickerScreenController()->getColor()));
							//
							try {
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particleemitter_point_colorstart"))->setEffectColorMul(ppe->getColorStart());
							} catch (Exception& exception) {
								Console::println(string("OnColorChangeAction::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							particleSystemEditorTabController->view->initParticleSystem();
						}
						OnColorChangeAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};
					popUps->getColorPickerScreenController()->show(ppe->getColorStart(), new OnColorChangeAction(this, particleSystemIdx));
				}
			}
		} else
		if (node->getId().compare("particleemitter_point_colorend_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto ppe = particleSystem != nullptr?particleSystem->getPointParticleEmitter():nullptr;
				if (ppe != nullptr) {
					//
					class OnColorChangeAction: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							if (prototype == nullptr) return;
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto ppe = particleSystem != nullptr?particleSystem->getPointParticleEmitter():nullptr;
							if (ppe == nullptr) return;
							ppe->setColorEnd(Color4(particleSystemEditorTabController->popUps->getColorPickerScreenController()->getColor()));
							//
							try {
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particleemitter_point_colorend"))->setEffectColorMul(ppe->getColorEnd());
							} catch (Exception& exception) {
								Console::println(string("OnColorChangeAction::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							particleSystemEditorTabController->view->initParticleSystem();
						}
						OnColorChangeAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};
					popUps->getColorPickerScreenController()->show(ppe->getColorEnd(), new OnColorChangeAction(this, particleSystemIdx));
				}
			}
		} else
		if (node->getId().compare("particleemitter_sphere_colorstart_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto spe = particleSystem != nullptr?particleSystem->getSphereParticleEmitter():nullptr;
				if (spe != nullptr) {
					//
					class OnColorChangeAction: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							if (prototype == nullptr) return;
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto spe = particleSystem != nullptr?particleSystem->getSphereParticleEmitter():nullptr;
							if (spe == nullptr) return;
							spe->setColorStart(Color4(particleSystemEditorTabController->popUps->getColorPickerScreenController()->getColor()));
							//
							try {
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particleemitter_sphere_colorstart"))->setEffectColorMul(spe->getColorStart());
							} catch (Exception& exception) {
								Console::println(string("OnColorChangeAction::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							particleSystemEditorTabController->view->initParticleSystem();
						}
						OnColorChangeAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};
					popUps->getColorPickerScreenController()->show(spe->getColorStart(), new OnColorChangeAction(this, particleSystemIdx));
				}
			}
		} else
		if (node->getId().compare("particleemitter_sphere_colorend_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto spe = particleSystem != nullptr?particleSystem->getSphereParticleEmitter():nullptr;
				if (spe != nullptr) {
					//
					class OnColorChangeAction: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							if (prototype == nullptr) return;
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto spe = particleSystem != nullptr?particleSystem->getSphereParticleEmitter():nullptr;
							if (spe == nullptr) return;
							spe->setColorEnd(Color4(particleSystemEditorTabController->popUps->getColorPickerScreenController()->getColor()));
							//
							try {
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particleemitter_sphere_colorend"))->setEffectColorMul(spe->getColorEnd());
							} catch (Exception& exception) {
								Console::println(string("OnColorChangeAction::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							particleSystemEditorTabController->view->initParticleSystem();
						}
						OnColorChangeAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};
					popUps->getColorPickerScreenController()->show(spe->getColorEnd(), new OnColorChangeAction(this, particleSystemIdx));
				}
			}
		}
		if (node->getId().compare("particleemitter_circle_colorstart_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto cpe = particleSystem != nullptr?particleSystem->getCircleParticleEmitter():nullptr;
				if (cpe != nullptr) {
					//
					class OnColorChangeAction: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							if (prototype == nullptr) return;
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto cpe = particleSystem != nullptr?particleSystem->getCircleParticleEmitter():nullptr;
							if (cpe == nullptr) return;
							cpe->setColorStart(Color4(particleSystemEditorTabController->popUps->getColorPickerScreenController()->getColor()));
							//
							try {
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particleemitter_circle_colorstart"))->setEffectColorMul(cpe->getColorStart());
							} catch (Exception& exception) {
								Console::println(string("OnColorChangeAction::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							particleSystemEditorTabController->view->initParticleSystem();
						}
						OnColorChangeAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};
					popUps->getColorPickerScreenController()->show(cpe->getColorStart(), new OnColorChangeAction(this, particleSystemIdx));
				}
			}
		} else
		if (node->getId().compare("particleemitter_circle_colorend_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto cpe = particleSystem != nullptr?particleSystem->getCircleParticleEmitter():nullptr;
				if (cpe != nullptr) {
					//
					class OnColorChangeAction: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							if (prototype == nullptr) return;
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto cpe = particleSystem != nullptr?particleSystem->getCircleParticleEmitter():nullptr;
							if (cpe == nullptr) return;
							cpe->setColorEnd(Color4(particleSystemEditorTabController->popUps->getColorPickerScreenController()->getColor()));
							//
							try {
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particleemitter_circle_colorend"))->setEffectColorMul(cpe->getColorEnd());
							} catch (Exception& exception) {
								Console::println(string("OnColorChangeAction::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							particleSystemEditorTabController->view->initParticleSystem();
						}
						OnColorChangeAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};
					popUps->getColorPickerScreenController()->show(cpe->getColorEnd(), new OnColorChangeAction(this, particleSystemIdx));
				}
			}
		} else
		if (node->getId().compare("particleemitter_radial_colorstart_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto rpe = particleSystem != nullptr?particleSystem->getCircleParticleEmitterPlaneVelocity():nullptr;
				if (rpe != nullptr) {
					//
					class OnColorChangeAction: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							if (prototype == nullptr) return;
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto rpe = particleSystem != nullptr?particleSystem->getCircleParticleEmitterPlaneVelocity():nullptr;
							if (rpe == nullptr) return;
							rpe->setColorStart(Color4(particleSystemEditorTabController->popUps->getColorPickerScreenController()->getColor()));
							//
							try {
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particleemitter_radial_colorstart"))->setEffectColorMul(rpe->getColorStart());
							} catch (Exception& exception) {
								Console::println(string("OnColorChangeAction::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							particleSystemEditorTabController->view->initParticleSystem();
						}
						OnColorChangeAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};
					popUps->getColorPickerScreenController()->show(rpe->getColorStart(), new OnColorChangeAction(this, particleSystemIdx));
				}
			}
		} else
		if (node->getId().compare("particleemitter_radial_colorend_edit") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto rpe = particleSystem != nullptr?particleSystem->getCircleParticleEmitterPlaneVelocity():nullptr;
				if (rpe != nullptr) {
					//
					class OnColorChangeAction: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							if (prototype == nullptr) return;
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto rpe = particleSystem != nullptr?particleSystem->getCircleParticleEmitterPlaneVelocity():nullptr;
							if (rpe == nullptr) return;
							rpe->setColorEnd(Color4(particleSystemEditorTabController->popUps->getColorPickerScreenController()->getColor()));
							//
							try {
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particleemitter_radial_colorend"))->setEffectColorMul(rpe->getColorEnd());
							} catch (Exception& exception) {
								Console::println(string("OnColorChangeAction::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							particleSystemEditorTabController->view->initParticleSystem();
						}
						OnColorChangeAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};
					popUps->getColorPickerScreenController()->show(rpe->getColorEnd(), new OnColorChangeAction(this, particleSystemIdx));
				}
			}
		} else
		if (node->getId().compare("particletype_point_texture_open") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto pps = particleSystem != nullptr?particleSystem->getPointParticleSystem():nullptr;
				if (pps != nullptr) {
					class OnPointParticleSystemLoadTexture: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto pps = particleSystem != nullptr?particleSystem->getPointParticleSystem():nullptr;
							if (pps == nullptr) return;
							particleSystemEditorTabController->view->uninitParticleSystem();
							try {
								pps->setTextureFileName(
									particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName(),
									pps->getTransparencyTextureFileName()
								);
							} catch (Exception& exception) {
								Console::println(string("OnPointParticleSystemLoadTexture::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particletype_point_texture"))->setSource(pps->getTextureFileName());
							required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particletype_point_texture"))->setTooltip(pps->getTextureFileName());
							particleSystemEditorTabController->view->initParticleSystem();
							particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
						}

						OnPointParticleSystemLoadTexture(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx)
							: particleSystemEditorTabController(particleSystemEditorTabController)
							, particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};

					popUps->getFileDialogScreenController()->show(
						pps->getTextureFileName().empty() == false?Tools::getPathName(pps->getTextureFileName()):string(),
						"Load point particle system texture from: ",
						TextureReader::getTextureExtensions(),
						Tools::getFileName(pps->getTextureFileName()),
						true,
						new OnPointParticleSystemLoadTexture(this, particleSystemIdx)
					);
				}
			}
		} else
		if (node->getId().compare("particletype_point_texture_remove") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto pps = particleSystem != nullptr?particleSystem->getPointParticleSystem():nullptr;
				if (pps != nullptr) {
					view->uninitParticleSystem();
					try {
						pps->setTextureFileName(string(), pps->getTransparencyTextureFileName());
						required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_point_texture"))->setSource(pps->getTextureFileName());
						required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_point_texture"))->setTooltip(pps->getTextureFileName());
					} catch (Exception& exception) {
						Console::println(string("ParticleSystemEditorTabController::onAction(): An error occurred: ") + exception.what());;
						showInfoPopUp("Warning", (string(exception.what())));
					}
					view->initParticleSystem();
				}
			}
		} else
		if (node->getId().compare("particletype_point_texture_browseto") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto pps = particleSystem != nullptr?particleSystem->getPointParticleSystem():nullptr;
				if (pps != nullptr && pps->getTextureFileName().empty() == false) {
					view->getEditorView()->getScreenController()->browseTo(pps->getTextureFileName());
				} else {
					showInfoPopUp("Browse To", "Nothing to browse to");
				}
			}
		} else
		if (node->getId().compare("particletype_point_transparency_open") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto pps = particleSystem != nullptr?particleSystem->getPointParticleSystem():nullptr;
				if (pps != nullptr) {
					class OnPointParticleSystemLoadTransparencyTexture: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto pps = particleSystem != nullptr?particleSystem->getPointParticleSystem():nullptr;
							if (pps == nullptr) return;
							particleSystemEditorTabController->view->uninitParticleSystem();
							try {
								pps->setTextureFileName(
									pps->getTextureFileName(),
									particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
								);
							} catch (Exception& exception) {
								Console::println(string("OnPointParticleSystemLoadTransparencyTexture::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particletype_point_transparency"))->setSource(pps->getTransparencyTextureFileName());
							required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particletype_point_transparency"))->setTooltip(pps->getTransparencyTextureFileName());
							particleSystemEditorTabController->view->initParticleSystem();
							particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
						}

						OnPointParticleSystemLoadTransparencyTexture(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx)
							: particleSystemEditorTabController(particleSystemEditorTabController)
							, particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};

					popUps->getFileDialogScreenController()->show(
						pps->getTextureFileName().empty() == false?Tools::getPathName(pps->getTextureFileName()):string(),
						"Load point particle system texture from: ",
						TextureReader::getTextureExtensions(),
						Tools::getFileName(pps->getTextureFileName()),
						true,
						new OnPointParticleSystemLoadTransparencyTexture(this, particleSystemIdx)
					);
				}
			}
		} else
		if (node->getId().compare("particletype_point_transparency_remove") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto pps = particleSystem != nullptr?particleSystem->getPointParticleSystem():nullptr;
				if (pps != nullptr) {
					view->uninitParticleSystem();
					try {
						pps->setTextureFileName(pps->getTextureFileName(), string());
						required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_point_transparency"))->setSource(pps->getTransparencyTextureFileName());
						required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_point_transparency"))->setTooltip(pps->getTransparencyTextureFileName());
					} catch (Exception& exception) {
						Console::println(string("ParticleSystemEditorTabController::onAction(): An error occurred: ") + exception.what());;
						showInfoPopUp("Warning", (string(exception.what())));
					}
					view->initParticleSystem();
				}
			}
		} else
		if (node->getId().compare("particletype_point_transparency_browseto") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto pps = particleSystem != nullptr?particleSystem->getPointParticleSystem():nullptr;
				if (pps != nullptr && pps->getTransparencyTextureFileName().empty() == false) {
					view->getEditorView()->getScreenController()->browseTo(pps->getTransparencyTextureFileName());
				} else {
					showInfoPopUp("Browse To", "Nothing to browse to");
				}
			}
		} else
		if (node->getId().compare("particletype_fog_texture_open") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto fps = particleSystem != nullptr?particleSystem->getFogParticleSystem():nullptr;
				if (fps != nullptr) {
					class OnFogParticleSystemLoadTexture: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto fps = particleSystem != nullptr?particleSystem->getFogParticleSystem():nullptr;
							if (fps == nullptr) return;
							particleSystemEditorTabController->view->uninitParticleSystem();
							try {
								fps->setTextureFileName(
									particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName(),
									fps->getTransparencyTextureFileName()
								);
							} catch (Exception& exception) {
								Console::println(string("OnFogParticleSystemLoadTexture::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particletype_fog_texture"))->setSource(fps->getTextureFileName());
							required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particletype_fog_texture"))->setTooltip(fps->getTextureFileName());
							particleSystemEditorTabController->view->initParticleSystem();
							particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
						}

						OnFogParticleSystemLoadTexture(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx)
							: particleSystemEditorTabController(particleSystemEditorTabController)
							, particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};

					popUps->getFileDialogScreenController()->show(
						fps->getTextureFileName().empty() == false?Tools::getPathName(fps->getTextureFileName()):string(),
						"Load point particle system texture from: ",
						TextureReader::getTextureExtensions(),
						Tools::getFileName(fps->getTextureFileName()),
						true,
						new OnFogParticleSystemLoadTexture(this, particleSystemIdx)
					);
				}
			}
		} else
		if (node->getId().compare("particletype_fog_texture_remove") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto fps = particleSystem != nullptr?particleSystem->getFogParticleSystem():nullptr;
				if (fps != nullptr) {
					view->uninitParticleSystem();
					try {
						fps->setTextureFileName(string(), fps->getTransparencyTextureFileName());
						required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_fog_texture"))->setSource(fps->getTextureFileName());
						required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_fog_texture"))->setTooltip(fps->getTextureFileName());
					} catch (Exception& exception) {
						Console::println(string("ParticleSystemEditorTabController::onAction(): An error occurred: ") + exception.what());;
						showInfoPopUp("Warning", (string(exception.what())));
					}
					view->initParticleSystem();
				}
			}
		} else
		if (node->getId().compare("particletype_fog_texture_browseto") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto fps = particleSystem != nullptr?particleSystem->getFogParticleSystem():nullptr;
				if (fps != nullptr && fps->getTextureFileName().empty() == false) {
					view->getEditorView()->getScreenController()->browseTo(fps->getTextureFileName());
				} else {
					showInfoPopUp("Browse To", "Nothing to browse to");
				}
			}
		} else
		if (node->getId().compare("particletype_fog_transparency_open") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto fps = particleSystem != nullptr?particleSystem->getFogParticleSystem():nullptr;
				if (fps != nullptr) {
					class OnFogParticleSystemLoadTransparencyTexture: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto fps = particleSystem != nullptr?particleSystem->getFogParticleSystem():nullptr;
							if (fps == nullptr) return;
							particleSystemEditorTabController->view->uninitParticleSystem();
							try {
								fps->setTextureFileName(
									fps->getTextureFileName(),
									particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() + "/" + particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
								);
							} catch (Exception& exception) {
								Console::println(string("OnFogParticleSystemLoadTransparencyTexture::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particletype_fog_transparency"))->setSource(fps->getTextureFileName());
							required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particletype_fog_transparency"))->setTooltip(fps->getTextureFileName());
							particleSystemEditorTabController->view->initParticleSystem();
							particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
						}

						OnFogParticleSystemLoadTransparencyTexture(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx)
							: particleSystemEditorTabController(particleSystemEditorTabController)
							, particleSystemIdx(particleSystemIdx) {
						}
					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};

					popUps->getFileDialogScreenController()->show(
						fps->getTextureFileName().empty() == false?Tools::getPathName(fps->getTextureFileName()):string(),
						"Load point particle system texture from: ",
						TextureReader::getTextureExtensions(),
						Tools::getFileName(fps->getTextureFileName()),
						true,
						new OnFogParticleSystemLoadTransparencyTexture(this, particleSystemIdx)
					);
				}
			}
		} else
		if (node->getId().compare("particletype_fog_transparency_remove") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto fps = particleSystem != nullptr?particleSystem->getFogParticleSystem():nullptr;
				if (fps != nullptr) {
					view->uninitParticleSystem();
					try {
						fps->setTextureFileName(fps->getTextureFileName(), string());
						required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_fog_transparency"))->setSource(fps->getTransparencyTextureFileName());
						required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_fog_transparency"))->setTooltip(fps->getTransparencyTextureFileName());
					} catch (Exception& exception) {
						Console::println(string("ParticleSystemEditorTabController::onAction(): An error occurred: ") + exception.what());;
						showInfoPopUp("Warning", (string(exception.what())));
					}
					view->initParticleSystem();
				}
			}
		} else
		if (node->getId().compare("particletype_fog_transparency_browseto") == 0) {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto fps = particleSystem != nullptr?particleSystem->getFogParticleSystem():nullptr;
				if (fps != nullptr && fps->getTransparencyTextureFileName().empty() == false) {
					view->getEditorView()->getScreenController()->browseTo(fps->getTransparencyTextureFileName());
				} else {
					showInfoPopUp("Browse To", "Nothing to browse to");
				}
			}
		} else
		if (node->getId() == "particletype_object_open") {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto ops = particleSystem != nullptr?particleSystem->getObjectParticleSystem():nullptr;
				if (ops != nullptr) {
					//
					class OnObjectParticleSystemLoadModel: public virtual Action
					{
					public:
						void performAction() override {
							auto prototype = particleSystemEditorTabController->view->getPrototype();
							auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
							auto ops = particleSystem != nullptr?particleSystem->getObjectParticleSystem():nullptr;
							if (ops == nullptr) return;
							particleSystemEditorTabController->view->uninitParticleSystem();
							try {
								ops->setModelFile(
									particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
									"/" +
									particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
								);
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particletype_object"))->setSource(ops->getModelFileName());
								required_dynamic_cast<GUIImageNode*>(particleSystemEditorTabController->screenNode->getNodeById("particletype_object"))->setTooltip(ops->getModelFileName());
							} catch (Exception& exception) {
								Console::println(string("OnObjectParticleSystemLoadModel::performAction(): An error occurred: ") + exception.what());;
								particleSystemEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
							}
							particleSystemEditorTabController->view->initParticleSystem();
							particleSystemEditorTabController->view->getEditorView()->reloadTabOutliner();
							particleSystemEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
						}

						OnObjectParticleSystemLoadModel(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx)
							: particleSystemEditorTabController(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {
							//
						}

					private:
						ParticleSystemEditorTabController* particleSystemEditorTabController;
						int particleSystemIdx;
					};

					//
					popUps->getFileDialogScreenController()->show(
						ops->getModelFileName().empty() == false?Tools::getPathName(ops->getModelFileName()):string(),
						"Load object particle system model from: ",
						ModelReader::getModelExtensions(),
						string(),
						true,
						new OnObjectParticleSystemLoadModel(this, particleSystemIdx)
					);
				}
			}
		} else
		if (node->getId() == "particletype_object_remove") {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto ops = particleSystem != nullptr?particleSystem->getObjectParticleSystem():nullptr;
				if (ops == nullptr) return;
				view->uninitParticleSystem();
				try {
					ops->setModelFile(string());
					required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_object"))->setSource(ops->getModelFileName());
					required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_object"))->setTooltip(ops->getModelFileName());
				} catch (Exception& exception) {
					Console::println(string("ParticleSystemEditorTabController::onAction(): An error occurred: ") + exception.what());;
					showInfoPopUp("Warning", (string(exception.what())));
				}
				view->initParticleSystem();
			}
		} else
		if (node->getId() == "particletype_object_browseto") {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
				auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
				auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
				auto ops = particleSystem != nullptr?particleSystem->getObjectParticleSystem():nullptr;
				if (ops != nullptr && ops->getModelFileName().empty() == false) {
					view->getEditorView()->getScreenController()->browseTo(ops->getModelFileName());
				} else {
					showInfoPopUp("Browse To", "Nothing to browse to");
				}
				view->initParticleSystem();
			}
		}
	}

	basePropertiesSubController->onAction(type, node, prototype);
	prototypePhysicsSubController->onAction(type, node, prototype);
	prototypeSoundsSubController->onAction(type, node, prototype);
	prototypeScriptSubController->onAction(type, node, prototype);
}

void ParticleSystemEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototype") + "\" value=\"" + GUIParser::escapeQuotes("prototype") + "\">\n";
	auto prototype = view->getPrototype();
	if (prototype != nullptr) {
		basePropertiesSubController->createBasePropertiesXML(prototype, xml);
		prototypeScriptSubController->createScriptXML(prototype, xml);
		prototypePhysicsSubController->createOutlinerPhysicsXML(prototype, xml);
		prototypeSoundsSubController->createOutlinerSoundsXML(prototype, xml);
		//
		if (prototype->getParticleSystemsCount() == 0) {
			xml+= "<selectbox-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Particle Systems") + "\" value=\"" + GUIParser::escapeQuotes("particlesystems") + "\" />\n";
		} else {
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Particle Systems") + "\" value=\"" + GUIParser::escapeQuotes("particlesystems") + "\">\n";
			for (auto i = 0; i < prototype->getParticleSystemsCount(); i++) {
				auto particleSystem = prototype->getParticleSystemAt(i);
				xml+= "	<selectbox-option image=\"resources/engine/images/particle.png\" text=\"" + GUIParser::escapeQuotes("Particle System " + to_string(i)) + "\" id=\"" + GUIParser::escapeQuotes("particlesystems." + to_string(i)) + "\" value=\"" + GUIParser::escapeQuotes("particlesystems." + to_string(i)) + "\" />\n";
			}
			xml+= "</selectbox-parent-option>\n";
		}
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void ParticleSystemEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(
		string("<dropdown-option text=\"Property\" value=\"property\" />\n") +
		string("<dropdown-option text=\"BV\" value=\"boundingvolume\" />\n") +
		string("<dropdown-option text=\"PS\" value=\"particlesystem\" />\n") +
		string("<dropdown-option text=\"Sound\" value=\"sound\" />\n")
	);
}

void ParticleSystemEditorTabController::setParticleSystemDetails(int particleSystemIdx) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
	if (particleSystem == nullptr) return;

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_particletype\" src=\"resources/engine/gui/template_details_particletype.xml\" />\n") +
		string("<template id=\"details_particleemitter\" src=\"resources/engine/gui/template_details_particleemitter.xml\" />\n")
	);

	//
	try {
		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_particletype"))->getActiveConditions().add("open");

		//
		if (particleSystem->getType() == PrototypeParticleSystem_Type::NONE) {
		} else
		if (particleSystem->getType() == PrototypeParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): ops");
			auto ops = particleSystem->getObjectParticleSystem();
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_type"))->getController()->setValue(MutableString(1));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_type_details"))->getActiveConditions().set("object");
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_object"))->setSource(ops->getModelFileName());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_object"))->setTooltip(ops->getModelFileName());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_object_scale"))->getController()->setValue(MutableString(Math::max(ops->getScale().getX(), Math::max(ops->getScale().getY(), ops->getScale().getZ()))));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_object_maxcount"))->getController()->setValue(MutableString(ops->getMaxCount()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_object_autoemit"))->getController()->setValue(MutableString(ops->isAutoEmit() == true?"1":""));
		} else
		if (particleSystem->getType() == PrototypeParticleSystem_Type::POINT_PARTICLE_SYSTEM) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): pps");
			auto pps = particleSystem->getPointParticleSystem();
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_type"))->getController()->setValue(MutableString(2));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_type_details"))->getActiveConditions().set("point");
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_point_texture"))->setSource(pps->getTextureFileName());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_point_texture"))->setTooltip(pps->getTextureFileName());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_point_transparency"))->setSource(pps->getTransparencyTextureFileName());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_point_transparency"))->setTooltip(pps->getTransparencyTextureFileName());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_size"))->getController()->setValue(MutableString(pps->getPointSize()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_maxcount"))->getController()->setValue(MutableString(pps->getMaxPoints()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_horizontal_sprites"))->getController()->setValue(MutableString(pps->getTextureHorizontalSprites()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_vertical_sprites"))->getController()->setValue(MutableString(pps->getTextureVerticalSprites()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_fps"))->getController()->setValue(MutableString(pps->getTextureSpritesFPS()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_autoemit"))->getController()->setValue(MutableString(pps->isAutoEmit() == true?"1":""));
		} else
		if (particleSystem->getType() == PrototypeParticleSystem_Type::FOG_PARTICLE_SYSTEM) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): fps");
			auto fps = particleSystem->getFogParticleSystem();
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_type"))->getController()->setValue(MutableString(3));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_type_details"))->getActiveConditions().set("fog");
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_fog_texture"))->setSource(fps->getTextureFileName());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_fog_texture"))->setTooltip(fps->getTextureFileName());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_fog_transparency"))->setSource(fps->getTransparencyTextureFileName());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_fog_transparency"))->setTooltip(fps->getTransparencyTextureFileName());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_fog_size"))->getController()->setValue(MutableString(fps->getPointSize()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_fog_maxcount"))->getController()->setValue(MutableString(fps->getMaxPoints()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_fog_horizontal_sprites"))->getController()->setValue(MutableString(fps->getTextureHorizontalSprites()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_fog_vertical_sprites"))->getController()->setValue(MutableString(fps->getTextureVerticalSprites()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_fog_fps"))->getController()->setValue(MutableString(fps->getTextureSpritesFPS()));
		} else {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): Unknown particle system type");
		}

		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_particleemitter"))->getActiveConditions().add("open");

		//
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::POINT_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): ppe");
			auto ppse = particleSystem->getPointParticleEmitter();
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type"))->getController()->setValue(MutableString(1));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type_details"))->getActiveConditions().set("point");
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_x"))->getController()->setValue(MutableString(ppse->getPosition().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_y"))->getController()->setValue(MutableString(ppse->getPosition().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_z"))->getController()->setValue(MutableString(ppse->getPosition().getZ()));
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_point_colorstart"))->setEffectColorMul(ppse->getColorStart());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_point_colorend"))->setEffectColorMul(ppse->getColorEnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_count"))->getController()->setValue(MutableString(ppse->getCount()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_lifetime_min"))->getController()->setValue(MutableString(static_cast<int32_t>(ppse->getLifeTime())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_lifetime_max"))->getController()->setValue(MutableString(static_cast<int32_t>(ppse->getLifeTime() + ppse->getLifeTimeRnd())));
			auto velocityMax = ppse->getVelocity().clone().add(ppse->getVelocityRnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_min_x"))->getController()->setValue(MutableString(ppse->getVelocity().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_min_y"))->getController()->setValue(MutableString(ppse->getVelocity().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_min_z"))->getController()->setValue(MutableString(ppse->getVelocity().getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_max_x"))->getController()->setValue(MutableString(velocityMax.getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_max_y"))->getController()->setValue(MutableString(velocityMax.getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_max_z"))->getController()->setValue(MutableString(velocityMax.getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_mass_min"))->getController()->setValue(MutableString(static_cast<int32_t>(ppse->getMass())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_mass_max"))->getController()->setValue(MutableString(static_cast<int32_t>(ppse->getMass() + ppse->getMassRnd())));
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): bbpe");
			auto bbpe = particleSystem->getBoundingBoxParticleEmitters();

			Matrix4x4 rotationMatrix;
			rotationMatrix.identity();
			rotationMatrix.setAxes(bbpe->getObbAxis0(), bbpe->getObbAxis1(), bbpe->getObbAxis2());
			auto rotation = rotationMatrix.computeEulerAngles();

			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type"))->getController()->setValue(MutableString(2));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type_details"))->getActiveConditions().set("box");
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_x"))->getController()->setValue(MutableString(bbpe->getObbCenter().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_y"))->getController()->setValue(MutableString(bbpe->getObbCenter().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_z"))->getController()->setValue(MutableString(bbpe->getObbCenter().getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_x"))->getController()->setValue(MutableString(rotation.getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_y"))->getController()->setValue(MutableString(rotation.getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_z"))->getController()->setValue(MutableString(rotation.getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_x"))->getController()->setValue(MutableString(bbpe->getObbHalfextension().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_y"))->getController()->setValue(MutableString(bbpe->getObbHalfextension().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_z"))->getController()->setValue(MutableString(bbpe->getObbHalfextension().getZ()));
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_box_colorstart"))->setEffectColorMul(bbpe->getColorStart());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_box_colorend"))->setEffectColorMul(bbpe->getColorEnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_count"))->getController()->setValue(MutableString(bbpe->getCount()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_lifetime_min"))->getController()->setValue(MutableString(static_cast<int32_t>(bbpe->getLifeTime())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_lifetime_max"))->getController()->setValue(MutableString(static_cast<int32_t>(bbpe->getLifeTime() + bbpe->getLifeTimeRnd())));
			auto velocityMax = bbpe->getVelocity().clone().add(bbpe->getVelocityRnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_min_x"))->getController()->setValue(MutableString(bbpe->getVelocity().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_min_y"))->getController()->setValue(MutableString(bbpe->getVelocity().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_min_z"))->getController()->setValue(MutableString(bbpe->getVelocity().getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_max_x"))->getController()->setValue(MutableString(velocityMax.getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_max_y"))->getController()->setValue(MutableString(velocityMax.getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_max_z"))->getController()->setValue(MutableString(velocityMax.getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_mass_min"))->getController()->setValue(MutableString(static_cast<int32_t>(bbpe->getMass())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_mass_max"))->getController()->setValue(MutableString(static_cast<int32_t>(bbpe->getMass() + bbpe->getMassRnd())));
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): cpe");
			auto cpse = particleSystem->getCircleParticleEmitter();

			Matrix4x4 rotationMatrix;
			rotationMatrix.identity();
			rotationMatrix.setAxes(cpse->getAxis0(), Vector3::computeCrossProduct(cpse->getAxis0(), cpse->getAxis1()), cpse->getAxis1());
			auto rotation = rotationMatrix.computeEulerAngles();

			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type"))->getController()->setValue(MutableString(3));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type_details"))->getActiveConditions().set("circle");
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_location_x"))->getController()->setValue(MutableString(cpse->getCenter().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_location_y"))->getController()->setValue(MutableString(cpse->getCenter().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_location_z"))->getController()->setValue(MutableString(cpse->getCenter().getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_rotation_x"))->getController()->setValue(MutableString(rotation.getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_rotation_y"))->getController()->setValue(MutableString(rotation.getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_rotation_z"))->getController()->setValue(MutableString(rotation.getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_radius"))->getController()->setValue(MutableString(cpse->getRadius()));
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_circle_colorstart"))->setEffectColorMul(cpse->getColorStart());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_circle_colorend"))->setEffectColorMul(cpse->getColorEnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_count"))->getController()->setValue(MutableString(cpse->getCount()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_lifetime_min"))->getController()->setValue(MutableString(static_cast<int32_t>(cpse->getLifeTime())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_lifetime_max"))->getController()->setValue(MutableString(static_cast<int32_t>(cpse->getLifeTime() + cpse->getLifeTimeRnd())));
			auto velocityMax = cpse->getVelocity().clone().add(cpse->getVelocityRnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_min_x"))->getController()->setValue(MutableString(cpse->getVelocity().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_min_y"))->getController()->setValue(MutableString(cpse->getVelocity().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_min_z"))->getController()->setValue(MutableString(cpse->getVelocity().getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_max_x"))->getController()->setValue(MutableString(velocityMax.getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_max_y"))->getController()->setValue(MutableString(velocityMax.getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_max_z"))->getController()->setValue(MutableString(velocityMax.getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_mass_min"))->getController()->setValue(MutableString(static_cast<int32_t>(cpse->getMass())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_mass_max"))->getController()->setValue(MutableString(static_cast<int32_t>(cpse->getMass() + cpse->getMassRnd())));
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): cpepv");
			auto rpse = particleSystem->getCircleParticleEmitterPlaneVelocity();

			Matrix4x4 rotationMatrix;
			rotationMatrix.identity();
			rotationMatrix.setAxes(rpse->getAxis0(), Vector3::computeCrossProduct(rpse->getAxis0(), rpse->getAxis1()), rpse->getAxis1());
			auto rotation = rotationMatrix.computeEulerAngles();

			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type"))->getController()->setValue(MutableString(4));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type_details"))->getActiveConditions().set("radial");
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_location_x"))->getController()->setValue(MutableString(rpse->getCenter().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_location_y"))->getController()->setValue(MutableString(rpse->getCenter().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_location_z"))->getController()->setValue(MutableString(rpse->getCenter().getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_rotation_x"))->getController()->setValue(MutableString(rotation.getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_rotation_y"))->getController()->setValue(MutableString(rotation.getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_rotation_z"))->getController()->setValue(MutableString(rotation.getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_radius"))->getController()->setValue(MutableString(rpse->getRadius()));
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_radial_colorstart"))->setEffectColorMul(rpse->getColorStart());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_radial_colorend"))->setEffectColorMul(rpse->getColorEnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_count"))->getController()->setValue(MutableString(rpse->getCount()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_lifetime_min"))->getController()->setValue(MutableString(static_cast<int32_t>(rpse->getLifeTime())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_lifetime_max"))->getController()->setValue(MutableString(static_cast<int32_t>(rpse->getLifeTime() + rpse->getLifeTimeRnd())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_velocity_min"))->getController()->setValue(MutableString(rpse->getVelocity()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_velocity_max"))->getController()->setValue(MutableString(rpse->getVelocity() + rpse->getVelocityRnd()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_mass_min"))->getController()->setValue(MutableString(static_cast<int32_t>(rpse->getMass())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_mass_max"))->getController()->setValue(MutableString(static_cast<int32_t>(rpse->getMass() + rpse->getMassRnd())));
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): spe");
			auto spse = particleSystem->getSphereParticleEmitter();
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type"))->getController()->setValue(MutableString(5));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type_details"))->getActiveConditions().set("sphere");
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_location_x"))->getController()->setValue(MutableString(spse->getCenter().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_location_y"))->getController()->setValue(MutableString(spse->getCenter().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_location_z"))->getController()->setValue(MutableString(spse->getCenter().getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_radius"))->getController()->setValue(MutableString(spse->getRadius()));
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_sphere_colorstart"))->setEffectColorMul(spse->getColorStart());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_sphere_colorend"))->setEffectColorMul(spse->getColorEnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_count"))->getController()->setValue(MutableString(spse->getCount()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_lifetime_min"))->getController()->setValue(MutableString(static_cast<int32_t>(spse->getLifeTime())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_lifetime_max"))->getController()->setValue(MutableString(static_cast<int32_t>(spse->getLifeTime() + spse->getLifeTimeRnd())));
			auto velocityMax = spse->getVelocity().clone().add(spse->getVelocityRnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_min_x"))->getController()->setValue(MutableString(spse->getVelocity().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_min_y"))->getController()->setValue(MutableString(spse->getVelocity().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_min_z"))->getController()->setValue(MutableString(spse->getVelocity().getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_max_x"))->getController()->setValue(MutableString(velocityMax.getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_max_y"))->getController()->setValue(MutableString(velocityMax.getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_max_z"))->getController()->setValue(MutableString(velocityMax.getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_mass_min"))->getController()->setValue(MutableString(static_cast<int32_t>(spse->getMass())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_mass_max"))->getController()->setValue(MutableString(static_cast<int32_t>(spse->getMass() + spse->getMassRnd())));
		} else {
			Console::println("ParticleSystemEditorTabController::applyParticleSystemDetails(): unknown emitter");
		}
	} catch (Exception& exception) {
		Console::println(string("ParticleSystemEditorTabController::setParticleSystemDetails(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
	}
}

void ParticleSystemEditorTabController::applyParticleSystemDetails(int particleSystemIdx) {

	Console::println("ParticleSystemEditorTabController::applyParticleSystemDetails(): " + to_string(particleSystemIdx));

	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
	if (particleSystem == nullptr) return;

	//
	try {
		{
			auto newParticleSystemTypeId = Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_type"))->getController()->getValue().getString());
			auto newParticleSystemType = PrototypeParticleSystem_Type::NONE;
			switch (newParticleSystemTypeId) {
				case 1: newParticleSystemType = PrototypeParticleSystem_Type::OBJECT_PARTICLE_SYSTEM; break;
				case 2: newParticleSystemType = PrototypeParticleSystem_Type::POINT_PARTICLE_SYSTEM; break;
				case 3: newParticleSystemType = PrototypeParticleSystem_Type::FOG_PARTICLE_SYSTEM; break;
				default:
					Console::println("ParticleSystemEditorTabController::applyParticleSystemDetails: unknown particle system type");
					break;
			}

			// check if to change particle system emitter
			if (particleSystem->getType() != newParticleSystemType) {
				view->uninitParticleSystem();
				particleSystem->setType(newParticleSystemType);
				//
				class ChangeTypeAction: public Action {
				private:
					ParticleSystemEditorTabController* editorView;
					int particleSystemIdx;
				public:
					ChangeTypeAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): editorView(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {}
					virtual void performAction() {
						editorView->setParticleSystemDetails(particleSystemIdx);
						editorView->view->initParticleSystem();
					}
				};
				Engine::getInstance()->enqueueAction(new ChangeTypeAction(this, particleSystemIdx));
				return;
			}
		}

		//
		if (particleSystem->getType() == PrototypeParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) {
			auto ops = particleSystem->getObjectParticleSystem();
			auto scale = Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_object_scale"))->getController()->getValue().getString());
			ops->setScale(Vector3(scale, scale, scale));
			ops->setMaxCount(Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_object_maxcount"))->getController()->getValue().getString()));
			ops->setAutoEmit(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_object_autoemit"))->getController()->getValue().getString() == "1");
		} else
		if (particleSystem->getType() == PrototypeParticleSystem_Type::POINT_PARTICLE_SYSTEM) {
			auto pps = particleSystem->getPointParticleSystem();
			pps->setPointSize(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_size"))->getController()->getValue().getString()));
			pps->setMaxPoints(Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_maxcount"))->getController()->getValue().getString()));
			pps->setTextureHorizontalSprites(Math::max(1, Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_horizontal_sprites"))->getController()->getValue().getString())));
			pps->setTextureVerticalSprites(Math::max(1, Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_vertical_sprites"))->getController()->getValue().getString())));
			pps->setTextureSpritesFPS(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_fps"))->getController()->getValue().getString()));
			pps->setAutoEmit(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_autoemit"))->getController()->getValue().getString() == "1");
		} else
		if (particleSystem->getType() == PrototypeParticleSystem_Type::FOG_PARTICLE_SYSTEM) {
			auto fps = particleSystem->getFogParticleSystem();
			fps->setPointSize(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_fog_size"))->getController()->getValue().getString()));
			fps->setMaxPoints(Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_fog_maxcount"))->getController()->getValue().getString()));
			fps->setTextureHorizontalSprites(Math::max(1, Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_fog_horizontal_sprites"))->getController()->getValue().getString())));
			fps->setTextureVerticalSprites(Math::max(1, Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_fog_vertical_sprites"))->getController()->getValue().getString())));
			fps->setTextureSpritesFPS(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_fog_fps"))->getController()->getValue().getString()));
		}

		//
		auto newEmitterTypeId = Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type"))->getController()->getValue().getString());
		auto newEmitterType = PrototypeParticleSystem_Emitter::NONE;
		switch (newEmitterTypeId) {
			case 1: newEmitterType = PrototypeParticleSystem_Emitter::POINT_PARTICLE_EMITTER; break;
			case 2: newEmitterType = PrototypeParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER; break;
			case 3: newEmitterType = PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER; break;
			case 4: newEmitterType = PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY; break;
			case 5: newEmitterType = PrototypeParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER; break;
			default:
				Console::println("ParticleSystemEditorTabController::applyParticleSystemDetails: unknown emitter");
				break;
		}

		// check if to change particle system emitter
		if (particleSystem->getEmitter() != newEmitterType) {
			view->uninitParticleSystem();
			particleSystem->setEmitter(newEmitterType);
			//
			class ChangeEmitterAction: public Action {
			private:
				ParticleSystemEditorTabController* editorView;
				int particleSystemIdx;
			public:
				ChangeEmitterAction(ParticleSystemEditorTabController* particleSystemEditorTabController, int particleSystemIdx): editorView(particleSystemEditorTabController), particleSystemIdx(particleSystemIdx) {}
				virtual void performAction() {
					editorView->setParticleSystemDetails(particleSystemIdx);
					editorView->view->initParticleSystem();
				}
			};
			Engine::getInstance()->enqueueAction(new ChangeEmitterAction(this, particleSystemIdx));
			return;
		}

		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_particletype"))->getActiveConditions().add("open");

		//
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::POINT_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::applyParticleSystemDetails(): ppe");
			auto ppse = particleSystem->getPointParticleEmitter();
			ppse->setPosition(
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_z"))->getController()->getValue().getString())
				)
			);
			ppse->setCount(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_count"))->getController()->getValue().getString()));
			ppse->setLifeTime(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_lifetime_min"))->getController()->getValue().getString()));
			ppse->setLifeTimeRnd(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_lifetime_max"))->getController()->getValue().getString()) -
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_lifetime_min"))->getController()->getValue().getString())
			);
			ppse->setMass(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_mass_min"))->getController()->getValue().getString()));
			ppse->setMassRnd(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_mass_max"))->getController()->getValue().getString()) -
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_mass_min"))->getController()->getValue().getString())
			);
			auto velocityMin =
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_min_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_min_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_min_z"))->getController()->getValue().getString())
				);
			auto velocityMax =
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_max_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_max_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_max_z"))->getController()->getValue().getString())
				);
			ppse->setVelocity(velocityMin);
			ppse->setVelocityRnd(velocityMax.clone().sub(velocityMin));
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::applyParticleSystemDetails(): bbpe");
			auto bbpe = particleSystem->getBoundingBoxParticleEmitters();
			bbpe->setObbCenter(
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_z"))->getController()->getValue().getString())
				)
			);
			Transform transform;
			transform.addRotation(OrientedBoundingBox::AABB_AXIS_Z, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_z"))->getController()->getValue().getString()));
			transform.addRotation(OrientedBoundingBox::AABB_AXIS_Y, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_y"))->getController()->getValue().getString()));
			transform.addRotation(OrientedBoundingBox::AABB_AXIS_X, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_x"))->getController()->getValue().getString()));
			transform.update();
			Vector3 obbAxis0;
			Vector3 obbAxis1;
			Vector3 obbAxis2;
			transform.getTransformMatrix().getAxes(obbAxis0, obbAxis1, obbAxis2);
			bbpe->setObbAxis0(obbAxis0);
			bbpe->setObbAxis1(obbAxis1);
			bbpe->setObbAxis2(obbAxis2);
			bbpe->setObbHalfextension(
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_z"))->getController()->getValue().getString())
				)
			);
			bbpe->setCount(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_count"))->getController()->getValue().getString()));
			bbpe->setLifeTime(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_lifetime_min"))->getController()->getValue().getString()));
			bbpe->setLifeTimeRnd(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_lifetime_max"))->getController()->getValue().getString()) -
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_lifetime_min"))->getController()->getValue().getString())
			);
			bbpe->setMass(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_mass_min"))->getController()->getValue().getString()));
			bbpe->setMassRnd(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_mass_max"))->getController()->getValue().getString()) -
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_mass_min"))->getController()->getValue().getString())
			);
			auto velocityMin =
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_min_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_min_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_min_z"))->getController()->getValue().getString())
				);
			auto velocityMax =
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_max_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_max_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_max_z"))->getController()->getValue().getString())
				);
			bbpe->setVelocity(velocityMin);
			bbpe->setVelocityRnd(velocityMax.clone().sub(velocityMin));
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::applyParticleSystemDetails(): cpe");
			auto cpse = particleSystem->getCircleParticleEmitter();
			cpse->setCenter(
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_location_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_location_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_location_z"))->getController()->getValue().getString())
				)
			);

			Transform transform;
			transform.addRotation(OrientedBoundingBox::AABB_AXIS_Z, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_rotation_z"))->getController()->getValue().getString()));
			transform.addRotation(OrientedBoundingBox::AABB_AXIS_Y, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_rotation_y"))->getController()->getValue().getString()));
			transform.addRotation(OrientedBoundingBox::AABB_AXIS_X, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_rotation_x"))->getController()->getValue().getString()));
			transform.update();
			Vector3 unusedAxis;
			Vector3 axis0;
			Vector3 axis1;
			transform.getTransformMatrix().getAxes(axis0, unusedAxis, axis1);
			cpse->setAxis0(axis0);
			cpse->setAxis1(axis1);

			cpse->setRadius(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_radius"))->getController()->getValue().getString()));
			cpse->setCount(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_count"))->getController()->getValue().getString()));
			cpse->setLifeTime(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_lifetime_min"))->getController()->getValue().getString()));
			cpse->setLifeTimeRnd(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_lifetime_max"))->getController()->getValue().getString()) -
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_lifetime_min"))->getController()->getValue().getString())
			);
			cpse->setMass(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_mass_min"))->getController()->getValue().getString()));
			cpse->setMassRnd(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_mass_max"))->getController()->getValue().getString()) -
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_mass_min"))->getController()->getValue().getString())
			);
			auto velocityMin =
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_min_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_min_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_min_z"))->getController()->getValue().getString())
				);
			auto velocityMax =
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_max_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_max_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_velocity_max_z"))->getController()->getValue().getString())
				);
			cpse->setVelocity(velocityMin);
			cpse->setVelocityRnd(velocityMax.clone().sub(velocityMin));
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
			Console::println("ParticleSystemEditorTabController::applyParticleSystemDetails(): cpepv");
			auto cpse = particleSystem->getCircleParticleEmitterPlaneVelocity();
			cpse->setCenter(
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_location_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_location_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_location_z"))->getController()->getValue().getString())
				)
			);

			Transform transform;
			transform.addRotation(OrientedBoundingBox::AABB_AXIS_Z, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_rotation_z"))->getController()->getValue().getString()));
			transform.addRotation(OrientedBoundingBox::AABB_AXIS_Y, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_rotation_y"))->getController()->getValue().getString()));
			transform.addRotation(OrientedBoundingBox::AABB_AXIS_X, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_rotation_x"))->getController()->getValue().getString()));
			transform.update();
			Vector3 unusedAxis;
			Vector3 axis0;
			Vector3 axis1;
			transform.getTransformMatrix().getAxes(axis0, unusedAxis, axis1);
			cpse->setAxis0(axis0);
			cpse->setAxis1(axis1);

			cpse->setRadius(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_radius"))->getController()->getValue().getString()));
			cpse->setCount(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_count"))->getController()->getValue().getString()));
			cpse->setLifeTime(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_lifetime_min"))->getController()->getValue().getString()));
			cpse->setLifeTimeRnd(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_lifetime_max"))->getController()->getValue().getString()) -
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_lifetime_min"))->getController()->getValue().getString())
			);
			cpse->setMass(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_mass_min"))->getController()->getValue().getString()));
			cpse->setMassRnd(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_mass_max"))->getController()->getValue().getString()) -
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_mass_min"))->getController()->getValue().getString())
			);
			cpse->setVelocity(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_velocity_min"))->getController()->getValue().getString()));
			cpse->setVelocityRnd(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_velocity_max"))->getController()->getValue().getString()) -
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_velocity_min"))->getController()->getValue().getString())
			);
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::applyParticleSystemDetails(): spe");
			auto spse = particleSystem->getSphereParticleEmitter();
			spse->setCenter(
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_location_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_location_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_location_z"))->getController()->getValue().getString())
				)
			);
			spse->setRadius(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_radius"))->getController()->getValue().getString()));
			spse->setCount(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_count"))->getController()->getValue().getString()));
			spse->setLifeTime(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_lifetime_min"))->getController()->getValue().getString()));
			spse->setLifeTimeRnd(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_lifetime_max"))->getController()->getValue().getString()) -
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_lifetime_min"))->getController()->getValue().getString())
			);
			spse->setMass(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_mass_min"))->getController()->getValue().getString()));
			spse->setMassRnd(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_mass_max"))->getController()->getValue().getString()) -
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_mass_min"))->getController()->getValue().getString())
			);
			auto velocityMin =
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_min_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_min_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_min_z"))->getController()->getValue().getString())
				);
			auto velocityMax =
				Vector3(
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_max_x"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_max_y"))->getController()->getValue().getString()),
					Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_velocity_max_z"))->getController()->getValue().getString())
				);
			spse->setVelocity(velocityMin);
			spse->setVelocityRnd(velocityMax.clone().sub(velocityMin));
		} else {
			Console::println("ParticleSystemEditorTabController::applyParticleSystemDetails(): unknown emitter");
		}
	} catch (Exception& exception) {
		Console::println(string("ParticleSystemEditorTabController::applyParticleSystemDetails(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
	}
	//
	view->initParticleSystem();
}

void ParticleSystemEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
		auto particleSystemIdx = Integer::parse(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
		setParticleSystemDetails(particleSystemIdx);
	}
	prototypePhysicsSubController->updateDetails(view->getPrototype(), outlinerNode);
	prototypeSoundsSubController->updateDetails(view->getPrototype(), nullptr, outlinerNode);
}

void ParticleSystemEditorTabController::updatePointParticleSystemEmitter(const Vector3& position) {
	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_x"))->getController()->setValue(MutableString(position.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_y"))->getController()->setValue(MutableString(position.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_z"))->getController()->setValue(MutableString(position.getZ()));
	} catch (Exception& exception) {
		Console::println(string("ParticleSystemEditorTabController::updatePointParticleSystemEmitter(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
	}
}

void ParticleSystemEditorTabController::updateBoundingBoxParticleSystemEmitter(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension) {
	//
	try {
		Matrix4x4 rotationMatrix;
		rotationMatrix.identity();
		rotationMatrix.setAxes(axis0, axis1, axis2);
		auto rotation = rotationMatrix.computeEulerAngles();

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type"))->getController()->setValue(MutableString(2));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type_details"))->getActiveConditions().set("box");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_x"))->getController()->setValue(MutableString(center.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_y"))->getController()->setValue(MutableString(center.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_z"))->getController()->setValue(MutableString(center.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_x"))->getController()->setValue(MutableString(rotation.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_y"))->getController()->setValue(MutableString(rotation.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_z"))->getController()->setValue(MutableString(rotation.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_x"))->getController()->setValue(MutableString(halfExtension.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_y"))->getController()->setValue(MutableString(halfExtension.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_z"))->getController()->setValue(MutableString(halfExtension.getZ()));
	} catch (Exception& exception) {
		Console::println(string("ParticleSystemEditorTabController::updateBoundingBoxParticleSystemEmitter(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
	}
}

void ParticleSystemEditorTabController::updateCircleParticleSystemEmitter(const Vector3& center, const Vector3& axis0, const Vector3& axis1, float radius) {
	//
	try {
		Matrix4x4 rotationMatrix;
		rotationMatrix.identity();
		rotationMatrix.setAxes(axis0, Vector3::computeCrossProduct(axis0, axis1), axis1);
		auto rotation = rotationMatrix.computeEulerAngles();

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type"))->getController()->setValue(MutableString(3));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type_details"))->getActiveConditions().set("circle");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_location_x"))->getController()->setValue(MutableString(center.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_location_y"))->getController()->setValue(MutableString(center.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_location_z"))->getController()->setValue(MutableString(center.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_rotation_x"))->getController()->setValue(MutableString(rotation.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_rotation_y"))->getController()->setValue(MutableString(rotation.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_rotation_z"))->getController()->setValue(MutableString(rotation.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_circle_radius"))->getController()->setValue(MutableString(radius));
	} catch (Exception& exception) {
		Console::println(string("ParticleSystemEditorTabController::updateCircleParticleSystemEmitter(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
	}
}

void ParticleSystemEditorTabController::updateRadialParticleSystemEmitter(const Vector3& center, const Vector3& axis0, const Vector3& axis1, float radius) {
	//
	try {
		Matrix4x4 rotationMatrix;
		rotationMatrix.identity();
		rotationMatrix.setAxes(axis0, Vector3::computeCrossProduct(axis0, axis1), axis1);
		auto rotation = rotationMatrix.computeEulerAngles();

		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type"))->getController()->setValue(MutableString(4));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type_details"))->getActiveConditions().set("radial");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_location_x"))->getController()->setValue(MutableString(center.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_location_y"))->getController()->setValue(MutableString(center.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_location_z"))->getController()->setValue(MutableString(center.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_rotation_x"))->getController()->setValue(MutableString(rotation.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_rotation_y"))->getController()->setValue(MutableString(rotation.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_rotation_z"))->getController()->setValue(MutableString(rotation.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_radial_radius"))->getController()->setValue(MutableString(radius));
	} catch (Exception& exception) {
		Console::println(string("ParticleSystemEditorTabController::updateRadialParticleSystemEmitter(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
	}
}

void ParticleSystemEditorTabController::updateSphereParticleSystemEmitter(const Vector3& center, float radius) {
	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type"))->getController()->setValue(MutableString(5));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type_details"))->getActiveConditions().set("sphere");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_location_x"))->getController()->setValue(MutableString(center.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_location_y"))->getController()->setValue(MutableString(center.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_location_z"))->getController()->setValue(MutableString(center.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_sphere_radius"))->getController()->setValue(MutableString(radius));
	} catch (Exception& exception) {
		Console::println(string("ParticleSystemEditorTabController::updateSphereParticleSystemEmitter(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
	}
}
