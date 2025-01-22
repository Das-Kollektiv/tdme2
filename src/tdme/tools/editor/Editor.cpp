#include <tdme/tools/editor/Editor.h>

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/GUI.h>
#include <agui/gui/fileio/PNGTextureReader.h>
#include <agui/gui/nodes/GUIImageNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/tools/FileSystemTools.h>
#include <tdme/engine/tools/ThumbnailTool.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/SimplePartition.h>
#include <tdme/engine/Version.h>
#include <tdme/minitscript/EngineMinitScript.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/views/View.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Time.h>

using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::tools::editor::Editor;

using tdme::utilities::Time;

using agui::gui::GUI;
using agui::gui::fileio::PNGTextureReader;
using agui::gui::nodes::GUIImageNode;
using agui::gui::nodes::GUIScreenNode;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::tools::FileSystemTools;
using tdme::engine::tools::ThumbnailTool;
using tdme::engine::Color4;
using tdme::engine::Engine;
using tdme::engine::SimplePartition;
using tdme::engine::Version;
using tdme::minitscript::EngineMinitScript;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::View;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Time;

Editor* Editor::instance = nullptr;

Editor::Editor()
{
	FileSystemTools::loadSettings(this);
	Editor::instance = this;
	engine = Engine::getInstance();
	engine->setPartition(new SimplePartition());
	view = nullptr;
	viewInitialized = false;
	viewNew = nullptr;
	popUps = make_unique<PopUps>();
	editorView = nullptr;
	quitRequested = false;
}

Editor::~Editor() {
}

int Editor::main(int argc, char** argv)
{
	Console::printLine(string("Editor ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();
	//
	EngineMinitScript::initialize();
	// source handlers
	{
		//	tm files
		class TMSourceHandler: public GUIImageNode::SourceHandler {
			bool setSource(GUIImageNode* imageNode, const string& source) {
				if (StringTools::endsWith(StringTools::toLowerCase(source), ".tm") == false) return false;
				//
				try {
					vector<uint8_t> thumbnailPNGData;
					if (FileSystem::getInstance()->getThumbnailAttachment(
							FileSystem::getInstance()->getPathName(source),
							FileSystem::getInstance()->getFileName(source),
							thumbnailPNGData
						) == true) {
						//
						auto thumbnailTexture = PNGTextureReader::read("tdme.gui.guiimagenode." + to_string(GUIImageNode::allocateThumbnailTextureIdx()), thumbnailPNGData, true);
						if (thumbnailTexture != nullptr) {
							imageNode->assignTexture(thumbnailTexture, true);
						} else {
							imageNode->assignTexture(imageNode->getScreenNode()->getImage("resources/engine/images/mesh_big.png"), false);
						}
					} else {
						imageNode->assignTexture(imageNode->getScreenNode()->getImage("resources/engine/images/mesh_big.png"), false);
					}
				} catch (Exception& exception) {
					Console::printLine("TMSourceHandler::setSource(): " + string(exception.what()));
				}
				//
				return true;
			}
		};
		GUIImageNode::addSourceHandler(new TMSourceHandler());
	}
	{
		//	tmodel files
		class TModelSourceHandler: public GUIImageNode::SourceHandler {
			bool setSource(GUIImageNode* imageNode, const string& source) {
				if (StringTools::endsWith(StringTools::toLowerCase(source), ".tmodel") == false) return false;
				//
				try {
					vector<uint8_t> thumbnailPNGData;
					if (PrototypeReader::readThumbnail(
							FileSystem::getInstance()->getPathName(source),
							FileSystem::getInstance()->getFileName(source),
							thumbnailPNGData
						) == true) {
						//
						auto thumbnailTexture = PNGTextureReader::read("tdme.gui.guiimagenode." + to_string(GUIImageNode::allocateThumbnailTextureIdx()), thumbnailPNGData, true);
						if (thumbnailTexture != nullptr) {
							imageNode->assignTexture(thumbnailTexture, true);
						} else {
							imageNode->assignTexture(imageNode->getScreenNode()->getImage("resources/engine/images/tdme_big.png"), false);
						}
					} else {
						imageNode->assignTexture(imageNode->getScreenNode()->getImage("resources/engine/images/tdme_big.png"), false);
					}
				} catch (Exception& exception) {
					Console::printLine("TModelSourceHandler::setSource(): " + string(exception.what()));
				}
				//
				return true;
			}
		};
		GUIImageNode::addSourceHandler(new TModelSourceHandler());
	}
	{
		//	xml files
		class XMLSourceHandler: public GUIImageNode::SourceHandler {
			bool setSource(GUIImageNode* imageNode, const string& source) {
				if (StringTools::endsWith(StringTools::toLowerCase(source), ".xml") == false) return false;
				//
				try {
					imageNode->assignTexture(imageNode->getScreenNode()->getImage("resources/engine/images/gui_big.png"), false);
				} catch (Exception& exception) {
					Console::printLine("XMLSourceHandler::setSource(): " + string(exception.what()));
				}
				//
				return true;
			}
		};
		GUIImageNode::addSourceHandler(new XMLSourceHandler());
	}
	{
		//	other files
		class OtherSourceHandler: public GUIImageNode::SourceHandler {
			bool setSource(GUIImageNode* imageNode, const string& source) {
				// other model without thumbnail
				for (const auto& extension: ModelReader::getModelExtensions()) {
					if (StringTools::endsWith(StringTools::toLowerCase(source), "." + extension) == true) {
						imageNode->assignTexture(imageNode->getScreenNode()->getImage("resources/engine/images/mesh_big.png"), false);
						// done
						return true;
					}
				}
				//
				return false;
			}
		};
		GUIImageNode::addSourceHandler(new OtherSourceHandler());
	}
	//
	auto tdmeEditor = new Editor();
	return tdmeEditor->run(argc, argv, "Editor", nullptr, Application::WINDOW_HINT_MAXIMIZED);
}

bool Editor::isFullScreen() {
	if (editorView == nullptr) return false;
	return editorView->getScreenController()->isFullScreen();
}

void Editor::setView(View* view)
{
	viewNew = view;
}

View* Editor::getView()
{
	return view;
}

void Editor::quit()
{
	quitRequested = true;
}

void Editor::display()
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
	engine->getGUI()->render();
	engine->getGUI()->handleEvents();
	if (view != nullptr) view->tick();
	if (quitRequested == true) {
		if (view != nullptr) {
			view->deactivate();
			view->dispose();
		}
		Application::exit(0);
	}
}

void Editor::dispose()
{
	if (view != nullptr && viewInitialized == true) {
		view->deactivate();
		view->dispose();
		view = nullptr;
	}
	popUps->dispose();
	engine->dispose();
	ThumbnailTool::oseDispose();
}

void Editor::initialize()
{
	engine->initialize();
	// TODO: settings maybe for the next 2
	Application::setVSyncEnabled(true);
	Application::setLimitFPS(true);
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	setEventHandler(engine->getGUI());
	ThumbnailTool::oseInit();
	popUps->initialize();
	setView((editorView = make_unique<EditorView>(popUps.get())).get());
}

void Editor::reshape(int width, int height)
{
	engine->reshape(width, height);
}

void Editor::onDrop(const vector<string>& paths) {
	editorView->onDrop(paths);
}

void Editor::onClose() {
	editorView->getScreenController()->closeProject();
}
