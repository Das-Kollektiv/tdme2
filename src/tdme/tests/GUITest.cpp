// Generated from /tdme/src/tdme/tests/GUITest.java
#include <tdme/tests/GUITest.h>

#include <java/lang/String.h>
#include <java/lang/System.h>
#include <java/util/logging/Level.h>
#include <java/util/logging/Logger.h>
#include <tdme/engine/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/effects/GUIColorEffect.h>
#include <tdme/gui/effects/GUIPositionEffect.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tests/GUITest_init_1.h>
#include <tdme/tests/GUITest_init_2.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using tdme::tests::GUITest;
using java::lang::String;
using java::lang::System;
using java::util::logging::Level;
using java::util::logging::Logger;
using tdme::engine::Application;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::effects::GUIColorEffect;
using tdme::gui::effects::GUIPositionEffect;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tests::GUITest_init_1;
using tdme::tests::GUITest_init_2;
using tdme::utils::_Console;
using tdme::utils::_Exception;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java


GUITest::GUITest()
{
	this->engine = Engine::getInstance();
}

void GUITest::initialize()
{
	engine->initialize();
	setInputEventHandler(engine->getGUI());
	try {
		engine->getGUI()->addScreen(u"test"_j, GUIParser::parse(u"resources/tests/gui"_j, u"test.xml"_j));
		engine->getGUI()->getScreen(u"test"_j)->setScreenSize(640, 480);
		engine->getGUI()->getScreen(u"test"_j)->addActionListener(new GUITest_init_1(this));
		engine->getGUI()->getScreen(u"test"_j)->addChangeListener(new GUITest_init_2(this));
		auto effectFadeIn = new GUIColorEffect();
		effectFadeIn->getColorMulStart()->set(0.0f, 0.0f, 0.0f, 1.0f);
		effectFadeIn->getColorMulEnd()->set(1.0f, 1.0f, 1.0f, 1.0f);
		effectFadeIn->setTimeTotal(1.0f);
		effectFadeIn->start();
		engine->getGUI()->getScreen(u"test"_j)->addEffect(u"fadein"_j, effectFadeIn);
		auto effectScrollIn = new GUIPositionEffect();
		effectScrollIn->setPositionXStart(-800.0f);
		effectScrollIn->setPositionXEnd(0.0f);
		effectScrollIn->setTimeTotal(1.0f);
		effectScrollIn->start();
		engine->getGUI()->getScreen(u"test"_j)->addEffect(u"scrollin"_j, effectScrollIn);
		engine->getGUI()->addRenderScreen(u"test"_j);
	} catch (_Exception& exception) {
		_Console::print(string("GUITest::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
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
	engine->getGUI()->render();
	engine->getGUI()->handleEvents();
}

void GUITest::main(int argc, char** argv)
{
	auto guiTest = new GUITest();
	guiTest->run(argc, argv, L"GUITest");
}

