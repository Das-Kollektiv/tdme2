// Generated from /tdme/src/tdme/tools/leveleditor/TDMELevelEditor.java
#include <tdme/tools/leveleditor/TDMELevelEditor.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/util/logging/Level.h>
#include <java/util/logging/Logger.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/leveleditor/views/EmptyView.h>
#include <tdme/tools/leveleditor/views/LevelEditorView.h>
#include <tdme/tools/leveleditor/views/ModelViewerView.h>
#include <tdme/tools/leveleditor/views/ParticleSystemView.h>
#include <tdme/tools/leveleditor/views/TriggerView.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelPropertyPresets.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/utils/_Console.h>

using tdme::tools::leveleditor::TDMELevelEditor;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::util::logging::Level;
using java::util::logging::Logger;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::leveleditor::views::EmptyView;
using tdme::tools::leveleditor::views::LevelEditorView;
using tdme::tools::leveleditor::views::ModelViewerView;
using tdme::tools::leveleditor::views::ParticleSystemView;
using tdme::tools::leveleditor::views::TriggerView;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelPropertyPresets;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
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

TDMELevelEditor::TDMELevelEditor(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TDMELevelEditor::TDMELevelEditor()
	: TDMELevelEditor(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void TDMELevelEditor::init()
{
	quitRequested = false;
}

String* TDMELevelEditor::VERSION;

TDMELevelEditor* TDMELevelEditor::instance;

void TDMELevelEditor::main(int argc, char** argv)
{
	clinit();
	String* modelFileName = nullptr;
	_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"TDMELevelEditor "_j)->append(VERSION)->toString()));
	_Console::println(static_cast< Object* >(u"Programmed 2014,...,2017 by Andreas Drewke, drewke.net."_j));
	_Console::println();
	auto tdmeLevelEditor = new TDMELevelEditor();
	tdmeLevelEditor->run(argc, argv, L"TDMELevelEditor");
}

void TDMELevelEditor::ctor()
{
	super::ctor();
	init();
	TDMELevelEditor::instance = this;
	level = new LevelEditorLevel();
	LevelPropertyPresets::getInstance()->setDefaultLevelProperties(level);
	engine = Engine::getInstance();
	view = nullptr;
	popUps = new PopUps();
}

TDMELevelEditor* TDMELevelEditor::getInstance()
{
	clinit();
	return instance;
}

LevelEditorEntityLibraryScreenController* TDMELevelEditor::getLevelEditorEntityLibraryScreenController()
{
	return levelEditorEntityLibraryScreenController;
}

LevelEditorEntityLibrary* TDMELevelEditor::getEntityLibrary()
{
	return level->getEntityLibrary();
}

LevelEditorLevel* TDMELevelEditor::getLevel()
{
	return level;
}

void TDMELevelEditor::setView(View* view)
{
	if (this->view != nullptr)
		this->view->deactivate();

	this->view = view;
	if (this->view != nullptr)
		this->view->activate();

}

View* TDMELevelEditor::getView()
{
	return view;
}

void TDMELevelEditor::quit()
{
	quitRequested = true;
}

void TDMELevelEditor::display()
{
	engine->display();
	Engine::getInstance()->initGUIMode();
	if (view != nullptr)
		view->display();

	Engine::getInstance()->doneGUIMode();
	if (quitRequested == true) {
		dispose();
		System::exit(0);
	}
}

void TDMELevelEditor::dispose()
{
	if (view != nullptr)
		view->deactivate();

	levelEditorView->dispose();
	modelViewerView->dispose();
	triggerView->dispose();
	emptyView->dispose();
	particleSystemView->dispose();
	engine->dispose();
	Tools::oseDispose();
}

void TDMELevelEditor::initialize()
{
	engine->initialize();
	setInputEventHandler(engine->getGUI());
	Tools::oseInit();
	levelEditorEntityLibraryScreenController = new LevelEditorEntityLibraryScreenController(popUps);
	levelEditorEntityLibraryScreenController->initialize();
	engine->getGUI()->addScreen(levelEditorEntityLibraryScreenController->getScreenNode()->getId(), levelEditorEntityLibraryScreenController->getScreenNode());
	popUps->initialize();
	levelEditorView = new LevelEditorView(popUps);
	levelEditorView->initialize();
	modelViewerView = new ModelViewerView(popUps);
	modelViewerView->initialize();
	triggerView = new TriggerView(popUps);
	triggerView->initialize();
	emptyView = new EmptyView(popUps);
	emptyView->initialize();
	particleSystemView = new ParticleSystemView(popUps);
	particleSystemView->initialize();
	setView(levelEditorView);
}

void TDMELevelEditor::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}

void TDMELevelEditor::switchToLevelEditor()
{
	setView(levelEditorView);
}

void TDMELevelEditor::switchToModelViewer()
{
	setView(modelViewerView);
}

void TDMELevelEditor::switchToTriggerView()
{
	setView(triggerView);
}

void TDMELevelEditor::switchToEmptyView()
{
	setView(emptyView);
}

void TDMELevelEditor::switchToParticleSystemView()
{
	setView(particleSystemView);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TDMELevelEditor::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.leveleditor.TDMELevelEditor", 38);
    return c;
}

void TDMELevelEditor::clinit()
{
struct string_init_ {
	string_init_() {
	VERSION = u"0.9.9"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* TDMELevelEditor::getClass0()
{
	return class_();
}

