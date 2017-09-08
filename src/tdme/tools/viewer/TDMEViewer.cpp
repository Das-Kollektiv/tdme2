#include <tdme/tools/viewer/TDMEViewer.h>

#include <string>

#include <java/lang/System.h>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/utils/_Console.h>

using std::wstring;

using tdme::tools::viewer::TDMEViewer;

using java::lang::System;

using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelViewerView;
using tdme::tools::shared::views::View;
using tdme::utils::_Console;

wstring TDMEViewer::VERSION = L"0.9.9";

TDMEViewer* TDMEViewer::instance = nullptr;

TDMEViewer::TDMEViewer()
{
	TDMEViewer::instance = this;
	engine = Engine::getInstance();
	view = nullptr;
	viewInitialized = false;
	viewNew = nullptr;
	popUps = new PopUps();
	quitRequested = false;
}

void TDMEViewer::main(int argc, char** argv)
{
	String* modelFileName = nullptr;
	_Console::println(wstring(L"TDMEViewer "+ VERSION));
	_Console::println(wstring(L"Programmed 2014,...,2017 by Andreas Drewke, drewke.net."));
	_Console::println();

	auto tdmeLevelEditor = new TDMEViewer();
	tdmeLevelEditor->run(argc, argv, L"TDMEViewer");
}

TDMEViewer* TDMEViewer::getInstance()
{
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

void TDMEViewer::initialize()
{
	_Console::println(L"initialize");
	engine->initialize();
	setInputEventHandler(engine->getGUI());
	Tools::oseInit();
	popUps->initialize();
	setView(new SharedModelViewerView(popUps));
}

void TDMEViewer::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}
