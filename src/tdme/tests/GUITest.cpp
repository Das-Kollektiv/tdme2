#include <tdme/tests/GUITest.h>

#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/effects/GUIColorEffect.h>
#include <tdme/gui/effects/GUIPositionEffect.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tests/GUITest_init_1.h>
#include <tdme/tests/GUITest_init_2.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using tdme::tests::GUITest;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::effects::GUIColorEffect;
using tdme::gui::effects::GUIPositionEffect;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tests::GUITest_init_1;
using tdme::tests::GUITest_init_2;
using tdme::utils::Console;
using tdme::utils::Exception;


GUITest::GUITest()
{
	this->engine = Engine::getInstance();
}

void GUITest::initialize()
{
	engine->initialize();
	setInputEventHandler(engine->getGUI());
	try {
		engine->getGUI()->addScreen("test", GUIParser::parse("resources/tests/gui", "test.xml"));
		engine->getGUI()->getScreen("test")->setScreenSize(640, 480);
		engine->getGUI()->getScreen("test")->addActionListener(new GUITest_init_1(this));
		engine->getGUI()->getScreen("test")->addChangeListener(new GUITest_init_2(this));
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

void GUITest::display()
{
	engine->display();
	engine->getGUI()->handleEvents();
	engine->getGUI()->render();
}

void GUITest::main(int argc, char** argv)
{
	auto guiTest = new GUITest();
	guiTest->run(argc, argv, "GUITest");
}

