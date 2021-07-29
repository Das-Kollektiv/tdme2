#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>

#include <array>
#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeAudio.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/FileDialogPath.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeSoundsSubView.h>
#include <tdme/tools/editor/tabviews/ModelEditorTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/views/PlayableSoundView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::array;
using std::string;
using std::to_string;

using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;

using tdme::engine::Engine;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Model;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeAudio;
using tdme::utilities::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::FileDialogPath;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::PlayableSoundView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

PrototypeSoundsSubController::PrototypeSoundsSubController(EditorView* editorView, PlayableSoundView* playableSoundView, FileDialogPath* audioPath)
{
	this->editorView = editorView;
	this->audioPath = audioPath;
	this->playableSoundView = playableSoundView;
	this->view = new PrototypeSoundsSubView(this, editorView->getPopUps());
	this->popUps = editorView->getPopUps();
}

PrototypeSoundsSubController::~PrototypeSoundsSubController() {
	delete view;
}

PrototypeSoundsSubView* PrototypeSoundsSubController::getView()
{
	return view;
}

GUIScreenNode* PrototypeSoundsSubController::getScreenNode() {
	return screenNode;
}

void PrototypeSoundsSubController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void PrototypeSoundsSubController::onSoundClear(Prototype* prototype, const string& soundId) {
	playableSoundView->stopSound();
	prototype->removeSound(soundId);
	editorView->reloadTabOutliner();
}

void PrototypeSoundsSubController::onSoundLoad(Prototype* prototype, const string& soundId) {
	class LoadSoundAction: public virtual Action
	{
	public:
		LoadSoundAction(PrototypeSoundsSubController* prototypeSoundsSubController, Prototype* prototype, const string& soundId): prototypeSoundsSubController(prototypeSoundsSubController), prototype(prototype), soundId(soundId) {
		}
		void performAction() override {
			auto sound = prototype->getSound(soundId);
			if (sound == nullptr) return;
			sound->setFileName(
				prototypeSoundsSubController->getView()->getPopUps()->getFileDialogScreenController()->getPathName() +
				"/" +
				prototypeSoundsSubController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			prototypeSoundsSubController->audioPath->setPath(prototypeSoundsSubController->getView()->getPopUps()->getFileDialogScreenController()->getPathName());
			prototypeSoundsSubController->getView()->getPopUps()->getFileDialogScreenController()->close();
			prototypeSoundsSubController->playableSoundView->playSound(sound->getId());
		}
	private:
		PrototypeSoundsSubController* prototypeSoundsSubController;
		Prototype* prototype;
		string soundId;
	};

	auto sound = prototype->getSound(soundId);
	if (sound == nullptr) return;
	auto fileName = sound->getFileName();

	vector<string> extensions = {{"ogg"}};
	view->getPopUps()->getFileDialogScreenController()->show(
		fileName.empty() == false?Tools::getPathName(fileName):audioPath->getPath(),
		"Load audio from: ",
		extensions,
		fileName.empty() == false?Tools::getFileName(fileName):"",
		true,
		new LoadSoundAction(this, prototype, soundId)
	);
}

void PrototypeSoundsSubController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUps()->getInfoDialogScreenController()->show(caption, message);
}

void PrototypeSoundsSubController::createOutlinerSoundsXML(Prototype* prototype, string& xml) {
	if (prototype->getSounds().empty() == false) {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Sounds") + "\" value=\"" + GUIParser::escapeQuotes("sounds") + "\">\n";
		for (auto sound: prototype->getSounds()) {
			auto soundId = sound->getId();
			xml+= "	<selectbox-option image=\"resources/engine/images/sound.png\" text=\"" + GUIParser::escapeQuotes(soundId) + "\" id=\"" + GUIParser::escapeQuotes("sounds." + soundId) + "\" value=\"" + GUIParser::escapeQuotes("sounds." + soundId) + "\" />\n";
		}
		xml+= "</selectbox-parent-option>\n";
	}
}

void PrototypeSoundsSubController::updateDetails(Prototype* prototype, Model* model, const string& outlinerNode) {
	Console::println("PrototypeSoundsSubController::updateDetails(): " + outlinerNode);

	if (StringTools::startsWith(outlinerNode, "sounds.") == false) return;

	auto soundId = StringTools::substring(outlinerNode, string("sounds.").size(), outlinerNode.size());
	auto sound = prototype->getSound(soundId);
	if (sound == nullptr) return;

	editorView->setDetailsContent(
		"<template id=\"details_sound\" src=\"resources/engine/gui/template_details_sound.xml\" />\n"
	);

	//
	if (model != nullptr) {
		auto idx = 0;
		string animationsDropDownXML;
		animationsDropDownXML =
			animationsDropDownXML + "<dropdown-option text=\"" +
			GUIParser::escapeQuotes("<None>") +
			"\" value=\"" +
			GUIParser::escapeQuotes("") +
			"\" " +
			(idx == 0 ? "selected=\"true\" " : "") +
			" />\n";
		for (auto it: model->getAnimationSetups()) {
			auto animationSetupId = it.second->getId();
			animationsDropDownXML =
				animationsDropDownXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(animationSetupId) +
				"\" value=\"" +
				GUIParser::escapeQuotes(animationSetupId) +
				"\" " +
				(idx == 0 ? "selected=\"true\" " : "") +
				" />\n";
			idx++;
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("sound_animation_scrollarea"))->replaceSubNodes(animationsDropDownXML, true);
		} catch (Exception& exception) {
			Console::print(string("PrototypeSoundsSubController::setSoundDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_sound"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_animation"))->getController()->setValue(MutableString(sound->getAnimation()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_gain"))->getController()->setValue(MutableString(sound->getGain()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_pitch"))->getController()->setValue(MutableString(sound->getPitch()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_offset"))->getController()->setValue(MutableString(sound->getOffset()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_looping"))->getController()->setValue(MutableString(sound->isLooping() == true?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_ambient"))->getController()->setValue(MutableString(sound->isFixed() == true?"1":""));

	} catch (Exception& exception) {
		Console::println(string("PrototypeSoundsSubController::setSoundDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypeSoundsSubController::applySoundDetails(Prototype* prototype, const string& soundId) {
	try {
		auto sound = prototype->getSound(soundId);
		sound->setAnimation(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_animation"))->getController()->getValue().getString());
		sound->setGain(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_gain"))->getController()->getValue().getString()));
		sound->setPitch(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_pitch"))->getController()->getValue().getString()));
		sound->setOffset(Integer::parseInt(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_offset"))->getController()->getValue().getString()));
		sound->setLooping(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_looping"))->getController()->getValue().getString() == "1");
		sound->setFixed(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_ambient"))->getController()->getValue().getString() == "1");
		playableSoundView->playSound(sound->getId());
	} catch (Exception& exception) {
		Console::println(string("PrototypeSoundsSubController::updateSoundDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

const string PrototypeSoundsSubController::applySoundDetailsRename(Prototype* prototype, const string& soundId) {
	string newSoundId;
	try {
		auto sound = prototype->getSound(soundId);
		if (sound == nullptr) return newSoundId;
		newSoundId = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_key"))->getController()->getValue().getString();
		if (sound->getId() != newSoundId) {
			if (prototype->renameSound(sound->getId(), newSoundId) == false) {
				throw ExceptionBase("Audio key could not be renamed");
			}
		}
		sound->setId(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("sound_key"))->getController()->getValue().getString());
		playableSoundView->playSound(sound->getId());
	} catch (Exception& exception) {
		Console::println(string("PrototypeSoundsSubController::updateSoundDetailsRename(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
	return newSoundId;
}

void PrototypeSoundsSubController::createSound(Prototype* prototype) {
	auto soundCreate = false;
	auto soundName = string() + "New sound";
	if (prototype->getSound(soundName) == nullptr) {
		soundCreate = true;
	} else {
		//
		for (auto i = 1; i < 10001; i++) {
			soundName = string() + "New sound " + to_string(i);
			if (prototype->getSound(soundName) == nullptr) {
				soundCreate = true;
				//
				break;
			}
		}
	}
	try {
		if (soundCreate == false) {
			throw ExceptionBase("Could not create sound");
		}
	} catch (Exception& exception) {
		Console::println(string("PrototypeSoundsSubController::createSound(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}

	if (soundCreate == true) {
		prototype->addSound(soundName);
		editorView->reloadTabOutliner(string() + "sounds." + soundName);
		startRenameSound(
			prototype,
			soundName
		);
	}
}

void PrototypeSoundsSubController::startRenameSound(Prototype* prototype, const string& soundName) {
	auto sound = prototype->getSound(soundName);
	if (sound == nullptr) return;
	auto selectBoxOptionParentNode = dynamic_cast<GUIParentNode*>(editorView->getScreenController()->getScreenNode()->getNodeById("sounds." + soundName));
	if (selectBoxOptionParentNode == nullptr) return;
	renameSoundName = soundName;
	selectBoxOptionParentNode->replaceSubNodes(
		"<template id=\"tdme.sounds.rename_input\" hint=\"Sound name\" text=\"" + GUIParser::escapeQuotes(sound->getId()) + "\"src=\"resources/engine/gui/template_outliner_rename.xml\" />\n",
		true
	);
	Engine::getInstance()->getGUI()->setFoccussedNode(dynamic_cast<GUIElementNode*>(editorView->getScreenController()->getScreenNode()->getNodeById("tdme.sounds.rename_input")));
	editorView->getScreenController()->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(editorView->getScreenController()->getScreenNode()->getNodeById("selectbox_outliner")));
}

void PrototypeSoundsSubController::renameSound(Prototype* prototype) {
	auto newSoundName = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("tdme.sounds.rename_input"))->getController()->getValue().getString();
	try {
		if (prototype->renameSound(renameSoundName, newSoundName) == false) {
			//
			renameSoundName.clear();
			throw ExceptionBase("Could not rename sound");
		}
	} catch (Exception& exception) {
		Console::println(string("PrototypeSoundsSubController::renameSound(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
		return;
	}

	//
	renameSoundName.clear();

	//
	class ReloadTabOutlinerAction: public Action {
	private:
		EditorView* editorView;
		string outlinerNode;
	public:
		ReloadTabOutlinerAction(EditorView* editorView, const string& outlinerNode): editorView(editorView), outlinerNode(outlinerNode) {}
		virtual void performAction() {
			editorView->reloadTabOutliner(outlinerNode);
			editorView->getScreenController()->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(editorView->getScreenController()->getScreenNode()->getNodeById("selectbox_outliner")));
		}
	};
	Engine::getInstance()->enqueueAction(new ReloadTabOutlinerAction(editorView, string("sounds") + "." + newSoundName));
}

void PrototypeSoundsSubController::onValueChanged(GUIElementNode* node, Prototype* prototype, Model* model) {
	if (node->getId() == "dropdown_outliner_add") {
		auto addOutlinerType = node->getController()->getValue().getString();
		if (addOutlinerType == "sound") {
			createSound(prototype);
		}
	} else {
		for (auto& audioChangeNode: applyAudioNodes) {
			if (node->getId() == audioChangeNode) {
				auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
				if (StringTools::startsWith(outlinerNode, "sounds.") == true) {
					applySoundDetails(prototype, StringTools::substring(outlinerNode, string("sounds.").size(), outlinerNode.size()));
				}
			}
		}
		if (node->getId() == "selectbox_outliner") {
			auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "sounds.") == true) {
				auto soundId = StringTools::substring(outlinerNode, string("sounds.").size(), outlinerNode.size());
				updateDetails(prototype, model, soundId);
				playableSoundView->playSound(soundId);
			} else {
				playableSoundView->stopSound();
			}
		}
	}
}

void PrototypeSoundsSubController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype)
{
	if (type != GUIActionListenerType::PERFORMED) return;
	if (StringTools::startsWith(node->getId(), "sound_remove") == true) {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "sounds.") == true) {
			onSoundClear(prototype, StringTools::substring(outlinerNode, string("sounds.").size(), outlinerNode.size()));
		}
	} else
	if (StringTools::startsWith(node->getId(), "sound_open") == true) {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "sounds.") == true) {
			onSoundLoad(prototype, StringTools::substring(outlinerNode, string("sounds.").size(), outlinerNode.size()));
		}
	} else
	if (node->getId() == "tdme.sounds.rename_input") {
		renameSound(prototype);
	}
}

void PrototypeSoundsSubController::onFocus(GUIElementNode* node, Prototype* prototype) {
}

void PrototypeSoundsSubController::onUnfocus(GUIElementNode* node, Prototype* prototype) {
	if (node->getId() == "tdme.sounds.rename_input") {
		renameSound(prototype);
	} else
	if (node->getId() == "sound_key") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "sounds.") == true) {
			auto soundId = StringTools::substring(outlinerNode, string("sounds.").size(), outlinerNode.size());
			editorView->reloadTabOutliner(applySoundDetailsRename(prototype, soundId));
		}
	}
}

void PrototypeSoundsSubController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY, Prototype* prototype) {
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "sounds.") == true) {
			// clear
			popUps->getContextMenuScreenController()->clear();
			// rename
			class OnRenameAction: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = prototypeSoundsSubController->editorView->getScreenController()->getOutlinerSelection();
					if (StringTools::startsWith(outlinerNode, "sounds.") == true) {
						prototypeSoundsSubController->startRenameSound(
							prototype,
							StringTools::substring(outlinerNode, string("sounds.").size(), outlinerNode.size())
						);
					}
				}
				OnRenameAction(PrototypeSoundsSubController* prototypeSoundsSubController, Prototype* prototype): prototypeSoundsSubController(prototypeSoundsSubController), prototype(prototype) {
				}
			private:
				PrototypeSoundsSubController* prototypeSoundsSubController;
				Prototype* prototype;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Rename", "contextmenu_rename", new OnRenameAction(this, prototype));

			// separator
			popUps->getContextMenuScreenController()->addMenuSeparator();

			// delete
			class OnDeleteAction: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = prototypeSoundsSubController->editorView->getScreenController()->getOutlinerSelection();
					if (StringTools::startsWith(outlinerNode, "sounds.") == true) {
						prototypeSoundsSubController->playableSoundView->stopSound();
						auto selectedSoundId = StringTools::substring(outlinerNode, string("sounds.").size(), outlinerNode.size());
						prototype->removeSound(selectedSoundId);
						prototypeSoundsSubController->editorView->reloadTabOutliner("sounds");
					}
				}
				OnDeleteAction(PrototypeSoundsSubController* prototypeSoundsSubController, Prototype* prototype): prototypeSoundsSubController(prototypeSoundsSubController), prototype(prototype) {
				}
			private:
				PrototypeSoundsSubController* prototypeSoundsSubController;
				Prototype* prototype;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete", "contextmenu_delete", new OnDeleteAction(this, prototype));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		}
	}
}
