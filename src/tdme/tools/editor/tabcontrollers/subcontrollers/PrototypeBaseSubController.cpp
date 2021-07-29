#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeBaseSubController.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/engine/Engine.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeProperty.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeBaseSubView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeProperty;
using tdme::utilities::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeBaseSubController;
using tdme::tools::editor::tabviews::subviews::PrototypeBaseSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

PrototypeBaseSubController::PrototypeBaseSubController(EditorView* editorView, Action* onSetEntityDataAction)
{
	this->editorView = editorView;
	this->view = new PrototypeBaseSubView(this);
	this->popUps = editorView->getPopUps();
	this->onSetPrototypeDataAction = onSetEntityDataAction;
}

PrototypeBaseSubController::~PrototypeBaseSubController() {
	delete view;
	delete onSetPrototypeDataAction;
}

void PrototypeBaseSubController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void PrototypeBaseSubController::createPrototypePropertiesXML(Prototype* prototype, string& xml) {
	if (prototype->getPropertyCount() > 0) {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Properties") + "\" value=\"" + GUIParser::escapeQuotes("properties") + "\">\n";
		for (auto i = 0; i < prototype->getPropertyCount(); i++) {
			auto property = prototype->getPropertyByIndex(i);
			xml+= "	<selectbox-option image=\"resources/engine/images/script.png\" text=\"" + GUIParser::escapeQuotes(property->getName() + ": " + property->getValue()) + "\" id=\"" + GUIParser::escapeQuotes("properties." + property->getName()) + "\" value=\"" + GUIParser::escapeQuotes("properties." + property->getName()) + "\" />\n";
		}
		xml+= "</selectbox-parent-option>\n";
	}
}

void PrototypeBaseSubController::setPrototypeBaseDetails(Prototype* prototype) {
	editorView->setDetailsContent(
		"<template id=\"details_prototype_base\" src=\"resources/engine/gui/template_details_base.xml\" />\n"
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_prototype_base"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("prototype_name"))->getController()->setValue(MutableString(prototype->getName()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("prototype_description"))->getController()->setValue(MutableString(prototype->getDescription()));
	} catch (Exception& exception) {
		Console::println(string("PrototypeBaseSubController::setPrototypeBaseDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypeBaseSubController::applyPrototypeBaseDetails(Prototype* prototype) {
	try {
		prototype->setName(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("prototype_name"))->getController()->getValue().getString());
		prototype->setDescription(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("prototype_description"))->getController()->getValue().getString());
	} catch (Exception& exception) {
		Console::println(string("PrototypeBaseSubController::applyPrototypeBaseDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypeBaseSubController::setPropertyDetails(Prototype* prototype, const string& propertyName) {
	auto property = prototype->getProperty(propertyName);
	if (property == nullptr) return;

	editorView->setDetailsContent(
		"<template id=\"details_property\" src=\"resources/engine/gui/template_details_property.xml\" />\n"
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_property"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("property_value"))->getController()->setValue(MutableString(property->getValue()));
	} catch (Exception& exception) {
		Console::println(string("PrototypeBaseSubController::setPropertyDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypeBaseSubController::updateDetails(Prototype* prototype, const string& outlinerNode) {
	if (StringTools::startsWith(outlinerNode, "prototype") == true) {
		setPrototypeBaseDetails(prototype);
	} else
	if (StringTools::startsWith(outlinerNode, "properties.") == true) {
		auto selectedPropertyName = StringTools::substring(outlinerNode, string("properties.").size(), outlinerNode.size());
		setPropertyDetails(prototype, selectedPropertyName);
	}
}

void PrototypeBaseSubController::applyPropertyDetails(Prototype* prototype, const string& propertyName) {
	try {
		if (prototype->updateProperty(
			propertyName,
			propertyName,
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("property_value"))->getController()->getValue().getString()) == false) {
			throw ExceptionBase("Could not apply property details");
		}
	} catch (Exception& exception) {
		Console::println(string("PrototypeBaseSubController::applyPropertyDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypeBaseSubController::createProperty(Prototype* prototype) {
	auto propertyCreated = false;
	auto propertyName = string() + "New property";
	if (prototype->addProperty(
		propertyName,
		"No value"
		) == true) {
		propertyCreated = true;
	} else {
		//
		for (auto i = 1; i < 10001; i++) {
			propertyName = string() + "New property " + to_string(i);
			if (prototype->addProperty(
				propertyName,
				"No value"
				) == true) {
				propertyCreated = true;
				//
				break;
			}
		}
	}
	try {
		if (propertyCreated == false) {
			throw ExceptionBase("Could not create property");
		}
	} catch (Exception& exception) {
		Console::println(string("PrototypeBaseSubController::createProperty(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}

	if (propertyCreated == true) {
		editorView->reloadTabOutliner(string() + "properties." + propertyName);
		startRenameProperty(
			prototype,
			propertyName
		);
	}
}

void PrototypeBaseSubController::startRenameProperty(Prototype* prototype, const string& propertyName) {
	auto property = prototype->getProperty(propertyName);
	if (property == nullptr) return;
	auto selectBoxOptionParentNode = dynamic_cast<GUIParentNode*>(editorView->getScreenController()->getScreenNode()->getNodeById("properties." + propertyName));
	if (selectBoxOptionParentNode == nullptr) return;
	renamePropertyName = propertyName;
	selectBoxOptionParentNode->replaceSubNodes(
		"<template id=\"tdme.properties.rename_input\" hint=\"Property name\" text=\"" + GUIParser::escapeQuotes(property->getName()) + "\"src=\"resources/engine/gui/template_outliner_rename.xml\" />\n",
		true
	);
	Engine::getInstance()->getGUI()->setFoccussedNode(dynamic_cast<GUIElementNode*>(editorView->getScreenController()->getScreenNode()->getNodeById("tdme.properties.rename_input")));
	editorView->getScreenController()->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(editorView->getScreenController()->getScreenNode()->getNodeById("selectbox_outliner")));
}

void PrototypeBaseSubController::renameProperty(Prototype* prototype) {
	auto property = prototype->getProperty(renamePropertyName);
	renamePropertyName.clear();
	if (property != nullptr) {
		try {
			if (prototype->renameProperty(
				property->getName(),
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("tdme.properties.rename_input"))->getController()->getValue().getString()
				) == false) {
				//
				throw ExceptionBase("Could not rename property");
			}
		} catch (Exception& exception) {
			Console::println(string("PrototypeBaseSubController::renameProperty(): An error occurred: ") + exception.what());;
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
			editorView->getScreenController()->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(editorView->getScreenController()->getScreenNode()->getNodeById("selectbox_outliner")));
		}
	};
	Engine::getInstance()->enqueueAction(new ReloadTabOutlinerAction(editorView, "properties" + (property != nullptr?"." + property->getName():"")));
}

void PrototypeBaseSubController::onValueChanged(GUIElementNode* node, Prototype* prototype)
{
	if (node->getId() == "dropdown_outliner_add") {
		auto addOutlinerType = node->getController()->getValue().getString();
		if (addOutlinerType == "property") {
			createProperty(prototype);
		}
	} else
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "properties.") == true) {
			auto selectedPropertyName = StringTools::substring(outlinerNode, string("properties.").size(), outlinerNode.size());
			setPropertyDetails(prototype, selectedPropertyName);
		}
	}
}

void PrototypeBaseSubController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "tdme.properties.rename_input") {
			renameProperty(prototype);
		}
	}
}

void PrototypeBaseSubController::onFocus(GUIElementNode* node, Prototype* prototype) {
}

void PrototypeBaseSubController::onUnfocus(GUIElementNode* node, Prototype* prototype) {
	if (node->getId() == "tdme.properties.rename_input") {
		renameProperty(prototype);
	} else {
		for (auto& applyPropertyNode: applyPropertyNodes) {
			if (node->getId() == applyPropertyNode) {
				applyPropertyValue(prototype);
				break;
			}
		}
		for (auto& applyBaseNode: applyBaseNodes) {
			if (node->getId() == applyBaseNode) {
				applyPrototypeBaseDetails(prototype);
				break;
			}
		}
	}
}

void PrototypeBaseSubController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY, Prototype* prototype) {
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "properties.") == true) {
			// clear
			popUps->getContextMenuScreenController()->clear();
			// rename
			class OnRenameAction: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = prototypeBaseSubController->editorView->getScreenController()->getOutlinerSelection();
					if (StringTools::startsWith(outlinerNode, "properties.") == true) {
						prototypeBaseSubController->startRenameProperty(
							prototype,
							StringTools::substring(outlinerNode, string("properties.").size(), outlinerNode.size())
						);
					}
				}
				OnRenameAction(PrototypeBaseSubController* prototypeBaseSubController, Prototype* prototype): prototypeBaseSubController(prototypeBaseSubController), prototype(prototype) {
				}
			private:
				PrototypeBaseSubController* prototypeBaseSubController;
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
					auto outlinerNode = prototypeBaseSubController->editorView->getScreenController()->getOutlinerSelection();
					if (StringTools::startsWith(outlinerNode, "properties.") == true) {
						auto selectedPropertyName = StringTools::substring(outlinerNode, string("properties.").size(), outlinerNode.size());
						prototype->removeProperty(selectedPropertyName);
						prototypeBaseSubController->editorView->reloadTabOutliner("properties");
					}
				}
				OnDeleteAction(PrototypeBaseSubController* prototypeBaseSubController, Prototype* prototype): prototypeBaseSubController(prototypeBaseSubController), prototype(prototype) {
				}
			private:
				PrototypeBaseSubController* prototypeBaseSubController;
				Prototype* prototype;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete", "contextmenu_delete", new OnDeleteAction(this, prototype));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		}
	}
}

void PrototypeBaseSubController::applyPropertyValue(Prototype* prototype) {
	auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
	auto selectedPropertyName = StringTools::substring(outlinerNode, string("properties.").size(), outlinerNode.size());
	applyPropertyDetails(prototype, selectedPropertyName);
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
	Engine::getInstance()->enqueueAction(new ReloadTabOutlinerAction(editorView, outlinerNode));
}

void PrototypeBaseSubController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}
