#include <tdme/tools/gui/GUITest.h>

#include <string>

#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/effects/GUIColorEffect.h>
#include <tdme/gui/effects/GUIPositionEffect.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/MutableString.h>

using tdme::tools::gui::GUITest;

using std::string;
using std::to_string;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::effects::GUIColorEffect;
using tdme::gui::effects::GUIPositionEffect;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::MutableString;


GUITest::GUITest(const string& screenFileName)
{
	this->screenFileName = screenFileName;
	this->engine = Engine::getInstance();
}

void GUITest::initialize()
{
	engine->initialize();
	setInputEventHandler(engine->getGUI());
	try {
		engine->getGUI()->addScreen("test",
			GUIParser::parse(
				FileSystem::getInstance()->getPathName(screenFileName),
				FileSystem::getInstance()->getFileName(screenFileName)
			)
		);
		engine->getGUI()->getScreen("test")->setScreenSize(640, 480);
		engine->getGUI()->getScreen("test")->addActionListener(this);
		engine->getGUI()->getScreen("test")->addChangeListener(this);
		auto effectFadeIn = new GUIColorEffect();
		effectFadeIn->setColorMulStart(GUIColor(0.0f, 0.0f, 0.0f, 1.0f));
		effectFadeIn->setColorMulEnd(GUIColor(1.0f, 1.0f, 1.0f, 1.0f));
		effectFadeIn->setTimeTotal(1.0f);
		effectFadeIn->start();
		engine->getGUI()->getScreen("test")->addEffect("fadein", effectFadeIn);
		auto effectScrollIn = new GUIPositionEffect();
		effectScrollIn->setPositionXStart(-800.0f);
		effectScrollIn->setPositionXEnd(0.0f);
		effectScrollIn->setTimeTotal(1.0f);
		effectScrollIn->start();
		engine->getGUI()->getScreen("test")->addEffect("scrollin", effectScrollIn);
		engine->getGUI()->addRenderScreen("test");
	} catch (Exception& exception) {
		Console::print(string("GUITest::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
		exit(0);
	}
}

void GUITest::dispose()
{
	engine->dispose();
}

void GUITest::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}

void GUITest::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) {
	Console::println(node->getId() + ": onActionPerformed(): " + type->getName());
}

void GUITest::onValueChanged(GUIElementNode* node) {
	Console::println(node->getName() + ": onValueChanged(): " + node->getController()->getValue().getString());
}


void GUITest::display()
{
	engine->display();
	engine->getGUI()->handleEvents();
	engine->getGUI()->render();
}

void GUITest::main(int argc, char** argv)
{
	Console::println(string("GUITest 1.9.9"));
	Console::println(string("Programmed 2017-2018 by Andreas Drewke, drewke.net."));
	Console::println();
	if (argc > 2) {
		Console::println("Usage: GUITest [screen.xml]");
		exit(0);
	}
	string screenFileName = argc == 2?argv[1]:"resources/screens/test.xml";
	Console::println("Loading: " + screenFileName);
	Console::println();
	auto guiTest = new GUITest(screenFileName);
	guiTest->run(argc, argv, "GUITest");
}

