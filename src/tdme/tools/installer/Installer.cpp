#include <tdme/tools/installer/Installer.h>

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/effects/GUIColorEffect.h>
#include <tdme/gui/effects/GUIPositionEffect.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIMultilineTextNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/Integer.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Properties.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/gui/events/GUIChangeListener.h>


using tdme::tools::installer::Installer;

using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::model::Color4;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::effects::GUIColorEffect;
using tdme::gui::effects::GUIPositionEffect;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::Integer;
using tdme::utils::MutableString;
using tdme::utils::Properties;
using tdme::utils::StringUtils;

Installer::Installer()
{
	Application::setLimitFPS(true);
	Tools::loadSettings(this);
	this->engine = Engine::getInstance();
	this->popUps = new PopUps();
	screen = SCREEN_WELCOME;
}

void Installer::initialize()
{
	try {
		engine->initialize();
		engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
		setInputEventHandler(engine->getGUI());
		popUps->initialize();
		installerProperties.load("resources/installer", "installer.properties");
		unordered_map<string, string> parameters = {
			{"name", installerProperties.get("name", "TDME2 based application")},
			{"diskspace", installerProperties.get("diskspace", "Unknown")},
			{"installfolder", "/home/andreas/Applications/TDME2"}
		};
		engine->getGUI()->addScreen(
			"installer_welcome",
			GUIParser::parse(
				"resources/screens/installer",
				"installer_welcome.xml",
				parameters
			)
		);
		engine->getGUI()->addScreen(
			"installer_license",
			GUIParser::parse(
				"resources/screens/installer",
				"installer_license.xml",
				parameters
			)
		);
		dynamic_cast<GUIParentNode*>(engine->getGUI()->getScreen("installer_license")->getNodeById("scrollarea_licence_inner"))->replaceSubNodes(
			string("<multiline-text font=\"resources/gui-system/fonts/Roboto_20.fnt\" color=\"#000000\" width=\"100%\" height=\"auto\">\n") +
			string("	<![CDATA[\n") +
			FileSystem::getStandardFileSystem()->getContentAsString(".", "LICENSE") +
			string("	]]>\n") +
			string("</multiline-text>\n"),
			true
		);
		engine->getGUI()->addScreen(
			"installer_components",
			GUIParser::parse(
				"resources/screens/installer",
				"installer_components.xml",
				parameters
			)
		);
		string componentsXML = "<space height=\"10\" />\n";
		for (auto componentIdx = 1; true; componentIdx++) {
			auto componentName = installerProperties.get("component" + to_string(componentIdx), "");
			auto componentRequired = StringUtils::trim(StringUtils::toLowerCase(installerProperties.get("component" + to_string(componentIdx) + "_required", "false"))) == "true";
			if (componentName.empty() == true) break;
			componentsXML+=
				string("<element id=\"component" + to_string(componentIdx) + "\" width=\"100%\" height=\"25\">\n") +
				string("	<layout width=\"100%\" alignment=\"horizontal\">\n") +
				string("		<space width=\"10\" />\n") +
				string("		<checkbox name=\"checkbox_component" + to_string(componentIdx) + "\" value=\"1\" selected=\"true\" disabled=\"" + (componentRequired == true?"true":"false") + "\" />\n") +
				string("		<space width=\"10\" />\n") +
				string("		<text width=\"*\" font=\"resources/gui-system/fonts/Roboto_20.fnt\" text=\"" + GUIParser::escapeQuotes(componentName) + "\" color=\"#000000\" height=\"100%\" vertical-align=\"center\" />\n") +
				string("	</layout>\n") +
				string("</element>\n");
		}
		dynamic_cast<GUIParentNode*>(engine->getGUI()->getScreen("installer_components")->getNodeById("scrollarea_components_inner"))->replaceSubNodes(
			componentsXML,
			true
		);
		engine->getGUI()->addScreen(
			"installer_path",
			GUIParser::parse(
				"resources/screens/installer",
				"installer_path.xml",
				parameters
			)
		);
		engine->getGUI()->addScreen(
			"installer_installing",
			GUIParser::parse(
				"resources/screens/installer",
				"installer_installing.xml",
				parameters
			)
		);
		engine->getGUI()->addScreen(
			"installer_finished",
			GUIParser::parse(
				"resources/screens/installer",
				"installer_finished.xml",
				parameters
			)
		);
		engine->getGUI()->resetRenderScreens();
		engine->getGUI()->getScreen("installer_welcome")->addActionListener(this);
		engine->getGUI()->getScreen("installer_welcome")->addChangeListener(this);
		engine->getGUI()->getScreen("installer_license")->addActionListener(this);
		engine->getGUI()->getScreen("installer_license")->addChangeListener(this);
		engine->getGUI()->getScreen("installer_components")->addActionListener(this);
		engine->getGUI()->getScreen("installer_components")->addChangeListener(this);
		engine->getGUI()->getScreen("installer_path")->addActionListener(this);
		engine->getGUI()->getScreen("installer_path")->addChangeListener(this);
		engine->getGUI()->getScreen("installer_installing")->addActionListener(this);
		engine->getGUI()->getScreen("installer_installing")->addChangeListener(this);
		engine->getGUI()->getScreen("installer_finished")->addActionListener(this);
		engine->getGUI()->getScreen("installer_finished")->addChangeListener(this);
		engine->getGUI()->addRenderScreen("installer_welcome");
	} catch (Exception& exception) {
		engine->getGUI()->resetRenderScreens();
		engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
		engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
		popUps->getInfoDialogScreenController()->show("An error occurred:", exception.what());
	}
}

void Installer::dispose()
{
	engine->dispose();
}

void Installer::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}

void Installer::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) {
	Console::println(node->getId() + ": onActionPerformed(): " + type->getName());
	if (type == GUIActionListener_Type::PERFORMED) {
		if (node->getId() == "button_next") {
			screen = static_cast<Screen>(static_cast<int>(screen) + 1 % static_cast<int>(SCREEN_MAX));
		} else
		if (node->getId() == "button_back") {
			screen = static_cast<Screen>(static_cast<int>(screen) - 1 % static_cast<int>(SCREEN_MAX));
		} else
		if (node->getId() == "button_agree") {
			screen = SCREEN_COMPONENTS;
		} else
		if (node->getId() == "button_install") {
			screen = SCREEN_INSTALLING;
		} else
		if (node->getId() == "button_cancel") {
			exit(0);
		} else
		if (node->getId() == "button_finish") {
			exit(0);
		} else
		if (StringUtils::startsWith(node->getId(), "component") == true) {
			auto componentIdx = Integer::parseInt(StringUtils::substring(node->getId(), string("component").size()));
			dynamic_cast<GUIMultilineTextNode*>(engine->getGUI()->getScreen("installer_components")->getNodeById("component_description"))->setText(MutableString(installerProperties.get("component" + to_string(componentIdx) + "_description", "No detail description.")));
		}
	}
	engine->getGUI()->resetRenderScreens();
	switch (screen) {
		case SCREEN_WELCOME:
			engine->getGUI()->addRenderScreen("installer_welcome");
			break;
		case SCREEN_LICENSE:
			engine->getGUI()->addRenderScreen("installer_license");
			break;
		case SCREEN_COMPONENTS:
			engine->getGUI()->addRenderScreen("installer_components");
			break;
		case SCREEN_PATH:
			engine->getGUI()->addRenderScreen("installer_path");
			break;
		case SCREEN_INSTALLING:
			engine->getGUI()->addRenderScreen("installer_installing");
			break;
		case SCREEN_FINISHED:
			engine->getGUI()->addRenderScreen("installer_finished");
			break;
	}
}

void Installer::onValueChanged(GUIElementNode* node) {
	Console::println(node->getName() + ": onValueChanged(): " + node->getController()->getValue().getString());
}


void Installer::display()
{
	engine->display();
	engine->getGUI()->handleEvents();
	engine->getGUI()->render();
}

void Installer::main(int argc, char** argv)
{
	Console::println(string("Installer 1.9.9"));
	Console::println(string("Programmed 2017-2018 by Andreas Drewke, drewke.net."));
	Console::println();
	if (argc > 1) {
		Console::println("Usage: Installer");
		exit(0);
	}
	auto installer = new Installer();
	installer->run(argc, argv, "Installer");
}
