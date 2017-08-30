// Generated from /tdme/src/tdme/tools/particlesystem/TDMEParticleSystem.java
#include <tdme/tools/particlesystem/TDMEParticleSystem.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/util/logging/Level.h>
#include <java/util/logging/Logger.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/utils/_Console.h>

using tdme::tools::particlesystem::TDMEParticleSystem;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::util::logging::Level;
using java::util::logging::Logger;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedParticleSystemView;
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

String* TDMEParticleSystem::VERSION = u"0.9.9"_j;

TDMEParticleSystem* TDMEParticleSystem::instance = nullptr;

TDMEParticleSystem::TDMEParticleSystem()
{
	TDMEParticleSystem::instance = this;
	engine = Engine::getInstance();
	view = nullptr;
	viewInitialized = false;
	viewNew = nullptr;
	popUps = new PopUps();
	quitRequested = false;
}

void TDMEParticleSystem::main(int argc, char** argv)
{
	_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"TDMEParticleSystem "_j)->append(VERSION)->toString()));
	_Console::println(static_cast< Object* >(u"Programmed 2017 by Andreas Drewke, drewke.net."_j));
	_Console::println();
	auto tdmeParticleSystem = new TDMEParticleSystem();
	tdmeParticleSystem->run(argc, argv, L"TDMEParticleSystem");
}

TDMEParticleSystem* TDMEParticleSystem::getInstance()
{
	return instance;
}

void TDMEParticleSystem::setView(View* view)
{
	viewNew = view;
}

View* TDMEParticleSystem::getView()
{
	return view;
}

void TDMEParticleSystem::quit()
{
	quitRequested = true;
}

void TDMEParticleSystem::display()
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

void TDMEParticleSystem::dispose()
{
	if (view != nullptr && viewInitialized == true) {
		view->deactivate();
		view->dispose();
		view = nullptr;
	}
	engine->dispose();
	Tools::oseDispose();
}

void TDMEParticleSystem::initialize()
{
	engine->initialize();
	setInputEventHandler(engine->getGUI());
	Tools::oseInit();
	popUps->initialize();
	setView(new SharedParticleSystemView(popUps));
}

void TDMEParticleSystem::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}
