// Generated from /tdme/src/tdme/tools/leveleditor/TDMELevelEditor.java
#include <tdme/tools/leveleditor/TDMELevelEditor.h>

#include <com/jogamp/newt/opengl/GLWindow.h>
#include <com/jogamp/opengl/GLAutoDrawable.h>
#include <com/jogamp/opengl/GLCapabilities.h>
#include <com/jogamp/opengl/GLCapabilitiesImmutable.h>
#include <com/jogamp/opengl/GLProfile.h>
#include <com/jogamp/opengl/util/FPSAnimator.h>
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
using com::jogamp::newt::opengl::GLWindow;
using com::jogamp::opengl::GLAutoDrawable;
using com::jogamp::opengl::GLCapabilities;
using com::jogamp::opengl::GLCapabilitiesImmutable;
using com::jogamp::opengl::GLProfile;
using com::jogamp::opengl::util::FPSAnimator;
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

TDMELevelEditor::TDMELevelEditor(GLWindow* glWindow, FPSAnimator* animator, String* modelFileName) 
	: TDMELevelEditor(*static_cast< ::default_init_tag* >(0))
{
	ctor(glWindow,animator,modelFileName);
}

void TDMELevelEditor::init()
{
	quitRequested = false;
}

String* TDMELevelEditor::VERSION;

TDMELevelEditor* TDMELevelEditor::instance;

void TDMELevelEditor::main(StringArray* args)
{
	clinit();
	String* modelFileName = nullptr;
	_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"TDMELevelEditor "_j)->append(VERSION)->toString()));
	_Console::println(static_cast< Object* >(u"Programmed 2014,...,2017 by Andreas Drewke, drewke.net."_j));
	_Console::println();
	Logger::getLogger(u""_j)->setLevel(Level::SEVERE);
	auto glp = Engine::getProfile();
	auto caps = new GLCapabilities(glp);
	_Console::println(static_cast< Object* >(glp));
	_Console::println(static_cast< Object* >(caps));
	auto glWindow = GLWindow::create(static_cast< GLCapabilitiesImmutable* >(caps));
	glWindow->setTitle(::java::lang::StringBuilder().append(u"TDMELevelEditor "_j)->append(VERSION)->toString());
	auto animator = new FPSAnimator(static_cast< GLAutoDrawable* >(glWindow), 60);
	auto tdmeLevelEditor = new TDMELevelEditor(glWindow, animator, modelFileName);
	glWindow->addWindowListener(tdmeLevelEditor);
	glWindow->addGLEventListener(tdmeLevelEditor);
	glWindow->setSize(1024, 600);
	glWindow->setVisible(true);
	animator->start();
}

void TDMELevelEditor::ctor(GLWindow* glWindow, FPSAnimator* animator, String* modelFileName)
{
	super::ctor();
	init();
	this->glWindow = glWindow;
	this->animator = animator;
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

void TDMELevelEditor::display(GLAutoDrawable* drawable)
{
	engine->display(drawable);
	Engine::getInstance()->initGUIMode();
	if (view != nullptr)
		view->display(drawable);

	Engine::getInstance()->doneGUIMode();
	if (quitRequested == true) {
		dispose(drawable);
		animator->stop();
		glWindow->setVisible(false);
		System::exit(0);
	}
}

void TDMELevelEditor::dispose(GLAutoDrawable* drawable)
{
	if (view != nullptr)
		view->deactivate();

	levelEditorView->dispose();
	modelViewerView->dispose();
	triggerView->dispose();
	emptyView->dispose();
	particleSystemView->dispose();
	engine->dispose(drawable);
	Tools::oseDispose(drawable);
}

void TDMELevelEditor::init_(GLAutoDrawable* drawable)
{
	engine->initialize(drawable);
	glWindow->addMouseListener(engine->getGUI());
	glWindow->addKeyListener(engine->getGUI());
	Tools::oseInit(drawable);
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

void TDMELevelEditor::reshape(GLAutoDrawable* drawable, int32_t x, int32_t y, int32_t width, int32_t height)
{
	engine->reshape(drawable, x, y, width, height);
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

void TDMELevelEditor::windowDestroyNotify(WindowEvent* arg0)
{
}

void TDMELevelEditor::windowDestroyed(WindowEvent* arg0)
{
	System::exit(0);
}

void TDMELevelEditor::windowGainedFocus(WindowEvent* arg0)
{
}

void TDMELevelEditor::windowLostFocus(WindowEvent* arg0)
{
}

void TDMELevelEditor::windowMoved(WindowEvent* arg0)
{
}

void TDMELevelEditor::windowRepaint(WindowUpdateEvent* arg0)
{
}

void TDMELevelEditor::windowResized(WindowEvent* arg0)
{
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

