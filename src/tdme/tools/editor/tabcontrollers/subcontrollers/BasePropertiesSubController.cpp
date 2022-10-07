#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/BaseProperties.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabviews/subviews/BasePropertiesSubView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>


using std::map;
using std::string;
using std::vector;

using tdme::engine::prototype::BaseProperties;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
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
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabviews::subviews::BasePropertiesSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

BasePropertiesSubController::BasePropertiesSubController(EditorView* editorView, const string& rootNode)
{
	this->editorView = editorView;
	this->view = new BasePropertiesSubView(this);
	this->popUps = editorView->getPopUps();
	this->rootNodeId = rootNode;
}

BasePropertiesSubController::~BasePropertiesSubController() {
	delete view;
}

void BasePropertiesSubController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void BasePropertiesSubController::createBasePropertiesXML(BaseProperties* prototype, string& xml) {
	if (prototype->getPropertyCount() > 0) {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Properties") + "\" value=\"" + GUIParser::escapeQuotes("properties") + "\">\n";
		for (auto i = 0; i < prototype->getPropertyCount(); i++) {
			auto property = prototype->getPropertyByIndex(i);
			xml+= "	<selectbox-option image=\"resources/engine/images/script.png\" text=\"" + GUIParser::escapeQuotes(property->getName() + ": " + property->getValue()) + "\" id=\"" + GUIParser::escapeQuotes("properties." + property->getName()) + "\" value=\"" + GUIParser::escapeQuotes("properties." + property->getName()) + "\" />\n";
		}
		xml+= "</selectbox-parent-option>\n";
	}
}

void BasePropertiesSubController::setBasePropertiesDetails(BaseProperties* baseProperties, Prototype* prototype) {
	editorView->setDetailsContent(
		"<template id=\"details_base\" src=\"resources/engine/gui/template_details_base.xml\" />\n"
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_base"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_name"))->getController()->setValue(MutableString(baseProperties->getName()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_description"))->getController()->setValue(MutableString(baseProperties->getDescription()));
		if (prototype != nullptr) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_base"))->getActiveConditions().add("entity_hierarchy");
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_prototype_entityhierarchy"))->getController()->setValue(MutableString(prototype->isEntityHierarchy() == true?"1":""));
		}
	} catch (Exception& exception) {
		Console::println(string("PrototypeBaseSubController::setPrototypeBaseDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void BasePropertiesSubController::applyPropertyDetails(BaseProperties* baseProperties) {
	try {
		baseProperties->setName(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_name"))->getController()->getValue().getString());
		baseProperties->setDescription(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("base_description"))->getController()->getValue().getString());
	} catch (Exception& exception) {
		Console::println(string("PrototypeBaseSubController::applyPrototypeBaseDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void BasePropertiesSubController::setPropertyDetails(BaseProperties* baseProperties, const string& propertyName) {
	auto property = baseProperties->getProperty(propertyName);
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

void BasePropertiesSubController::updateDetails(BaseProperties* baseProperties, const string& outlinerNode, Prototype* prototype) {
	if (outlinerNode == rootNodeId) {
		setBasePropertiesDetails(baseProperties, prototype);
	} else
	if (StringTools::startsWith(outlinerNode, "properties.") == true) {
		auto selectedPropertyName = StringTools::substring(outlinerNode, string("properties.").size(), outlinerNode.size());
		setPropertyDetails(baseProperties, selectedPropertyName);
	}
}

void BasePropertiesSubController::applyPropertyDetails(BaseProperties* baseProperties, const string& propertyName) {
	try {
		if (baseProperties->updateProperty(
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

void BasePropertiesSubController::createProperty(BaseProperties* baseProperties) {
	auto propertyCreated = false;
	auto propertyName = string() + "New property";
	if (baseProperties->addProperty(
		propertyName,
		"No value"
		) == true) {
		propertyCreated = true;
	} else {
		//
		for (auto i = 1; i < 10001; i++) {
			propertyName = string() + "New property " + to_string(i);
			if (baseProperties->addProperty(
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
			baseProperties,
			propertyName
		);
	}
}

void BasePropertiesSubController::startRenameProperty(BaseProperties* baseProperties, const string& propertyName) {
	auto property = baseProperties->getProperty(propertyName);
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

void BasePropertiesSubController::renameProperty(BaseProperties* baseProperties) {
	auto property = baseProperties->getProperty(renamePropertyName);
	renamePropertyName.clear();
	if (property != nullptr) {
		try {
			if (baseProperties->renameProperty(
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
		}
	};
	Engine::getInstance()->enqueueAction(new ReloadTabOutlinerAction(editorView, "properties" + (property != nullptr?"." + property->getName():"")));
}

void BasePropertiesSubController::onValueChanged(GUIElementNode* node, BaseProperties* baseProperties, Prototype* prototype)
{
	if (node->getId() == "dropdown_outliner_add") {
		auto addOutlinerType = node->getController()->getValue().getString();
		if (addOutlinerType == "property") {
			createProperty(baseProperties);
		}
	} else
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "properties.") == true) {
			auto selectedPropertyName = StringTools::substring(outlinerNode, string("properties.").size(), outlinerNode.size());
			setPropertyDetails(baseProperties, selectedPropertyName);
		}
	} else
	if (prototype != nullptr && node->getId() == "base_prototype_entityhierarchy") {
		prototype->setEntityHierarchy(node->getController()->getValue().equals("1"));
	}
}

void BasePropertiesSubController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node, BaseProperties* baseProperties)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "tdme.properties.rename_input") {
			renameProperty(baseProperties);
		}
	}
}

void BasePropertiesSubController::onFocus(GUIElementNode* node, BaseProperties* baseProperties) {
}

void BasePropertiesSubController::onUnfocus(GUIElementNode* node, BaseProperties* baseProperties) {
	if (node->getId() == "tdme.properties.rename_input") {
		renameProperty(baseProperties);
	} else {
		for (auto& applyPropertyNode: applyPropertyNodes) {
			if (node->getId() == applyPropertyNode) {
				applyPropertyValue(baseProperties);
				break;
			}
		}
		for (auto& applyBaseNode: applyBaseNodes) {
			if (node->getId() == applyBaseNode) {
				applyPropertyDetails(baseProperties);
				break;
			}
		}
	}
}

void BasePropertiesSubController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY, BaseProperties* baseProperties) {
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (outlinerNode == "properties") {
			// clear
			popUps->getContextMenuScreenController()->clear();
			// add
			class OnAddPropertyAction: public virtual Action
			{
			public:
				void performAction() override {
					prototypeBaseSubController->createProperty(baseProperties);
				}
				OnAddPropertyAction(BasePropertiesSubController* prototypeBaseSubController, BaseProperties* baseProperties): prototypeBaseSubController(prototypeBaseSubController), baseProperties(baseProperties) {
				}
			private:
				BasePropertiesSubController* prototypeBaseSubController;
				BaseProperties* baseProperties;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Add Property", "contextmenu_add", new OnAddPropertyAction(this, baseProperties));
			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
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
							baseProperties,
							StringTools::substring(outlinerNode, string("properties.").size(), outlinerNode.size())
						);
					}
				}
				OnRenameAction(BasePropertiesSubController* prototypeBaseSubController, BaseProperties* baseProperties): prototypeBaseSubController(prototypeBaseSubController), baseProperties(baseProperties) {
				}
			private:
				BasePropertiesSubController* prototypeBaseSubController;
				BaseProperties* baseProperties;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Rename", "contextmenu_rename", new OnRenameAction(this, baseProperties));

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
						baseProperties->removeProperty(selectedPropertyName);
						prototypeBaseSubController->editorView->reloadTabOutliner("properties");
					}
				}
				OnDeleteAction(BasePropertiesSubController* prototypeBaseSubController, BaseProperties* baseProperties): prototypeBaseSubController(prototypeBaseSubController), baseProperties(baseProperties) {
				}
			private:
				BasePropertiesSubController* prototypeBaseSubController;
				BaseProperties* baseProperties;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete", "contextmenu_delete", new OnDeleteAction(this, baseProperties));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		}
	}
}

void BasePropertiesSubController::applyPropertyValue(BaseProperties* baseProperties) {
	auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
	auto selectedPropertyName = StringTools::substring(outlinerNode, string("properties.").size(), outlinerNode.size());
	applyPropertyDetails(baseProperties, selectedPropertyName);
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

void BasePropertiesSubController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}
