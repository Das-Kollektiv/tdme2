// Generated from /tdme/src/tdme/tools/viewer/TDMEViewer.java
#include <tdme/tools/viewer/TDMEViewer.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/util/logging/Level.h>
#include <java/util/logging/Logger.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/utils/_Console.h>

using tdme::tools::viewer::TDMEViewer;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::util::logging::Level;
using java::util::logging::Logger;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelViewerView;
using tdme::tools::shared::views::View;
using tdme::utils::_Console;

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

TDMEViewer::TDMEViewer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TDMEViewer::TDMEViewer()
	: TDMEViewer(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void TDMEViewer::init()
{
	quitRequested = false;
}

String* TDMEViewer::VERSION;

TDMEViewer* TDMEViewer::instance;

void TDMEViewer::main(StringArray* args)
{
	clinit();
	String* modelFileName = nullptr;
	_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"TDMEViewer "_j)->append(VERSION)->toString()));
	_Console::println(static_cast< Object* >(u"Programmed 2014,...,2017 by Andreas Drewke, drewke.net."_j));
	_Console::println();
	auto tdmeLevelEditor = new TDMEViewer();
}

void TDMEViewer::ctor()
{
	super::ctor();
	init();
	TDMEViewer::instance = this;
	engine = Engine::getInstance();
	view = nullptr;
	viewInitialized = false;
	viewNew = nullptr;
	popUps = new PopUps();
}

TDMEViewer* TDMEViewer::getInstance()
{
	clinit();
	return instance;
}

void TDMEViewer::setView(View* view)
{
	viewNew = view;
}

View* TDMEViewer::getView()
{
	return view;
}

void TDMEViewer::quit()
{
	quitRequested = true;
}

void TDMEViewer::display()
{
	if (viewNew != nullptr) {
		if (view != nullptr && viewInitialized == true) {
			view->deactivate();
			view->dispose();
			viewInitialized = false;
		}
		view = viewNew;
		viewNew = nullptr;
	}
	if (view != nullptr) {
		if (viewInitialized == false) {
			view->initialize();
			view->activate();
			viewInitialized = true;
		}
		view->display();
	}
	engine->display();
	view->display();
	if (quitRequested == true) {
		if (view != nullptr) {
			view->deactivate();
			view->dispose();
		}
		System::exit(0);
	}
}

void TDMEViewer::dispose()
{
	if (view != nullptr && viewInitialized == true) {
		view->deactivate();
		view->dispose();
		view = nullptr;
	}
	engine->dispose();
	Tools::oseDispose();
}

void TDMEViewer::init_()
{
	engine->initialize();
	Tools::oseInit();
	popUps->initialize();
	setView(new SharedModelViewerView(popUps));
}

void TDMEViewer::reshape(int32_t x, int32_t y, int32_t width, int32_t height)
{
	engine->reshape(x, y, width, height);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TDMEViewer::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.viewer.TDMEViewer", 28);
    return c;
}

void TDMEViewer::clinit()
{
struct string_init_ {
	string_init_() {
	VERSION = u"0.9.9"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* TDMEViewer::getClass0()
{
	return class_();
}

