#include <tdme/tools/installer/Installer.h>

#include <stdlib.h>
#include <stdio.h>

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
#include <tdme/network/httpclient/HTTPClient.h>
#include <tdme/network/httpclient/HTTPDownloadClient.h>
#include <tdme/os/filesystem/ArchiveFileSystem.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/Integer.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Properties.h>
#include <tdme/utils/StringTokenizer.h>
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
using tdme::network::httpclient::HTTPClient;
using tdme::network::httpclient::HTTPDownloadClient;
using tdme::os::filesystem::ArchiveFileSystem;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::Thread;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::Integer;
using tdme::utils::MutableString;
using tdme::utils::Properties;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;

Installer::Installer(): installThreadMutex("install-thread-mutex")
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
		#if defined(_WIN32)
			homeFolder = string(getenv("USERPROFILE"));
		#else
			homeFolder = string(getenv("HOME"));
		#endif
		installerProperties.load("resources/installer", "installer.properties");
		unordered_map<string, string> parameters = {
			{"name", installerProperties.get("name", "TDME2 based application")},
			{"diskspace", installerProperties.get("diskspace", "Unknown")},
			{"installfolder", homeFolder + "/Applications/" + installerProperties.get("name", "TDME2 based application")}
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
		dynamic_cast<GUIMultilineTextNode*>(engine->getGUI()->getScreen("installer_license")->getNodeById("licence_text"))->setText(MutableString(FileSystem::getStandardFileSystem()->getContentAsString(".", "LICENSE")));
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
				string("		<checkbox id=\"checkbox_component" + to_string(componentIdx) + "\" name=\"checkbox_component" + to_string(componentIdx) + "\" value=\"1\" selected=\"true\" disabled=\"" + (componentRequired == true?"true":"false") + "\" />\n") +
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
		engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
		engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
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
		if (node->getId() == "button_browse") {
			class OnBrowseAction: public virtual Action
			{
			public:
				void performAction() override {
					installer->popUps->getFileDialogScreenController()->close();
					dynamic_cast<GUIElementNode*>(installer->engine->getGUI()->getScreen("installer_path")->getNodeById("install_folder"))->getController()->setValue(MutableString(installer->popUps->getFileDialogScreenController()->getPathName() + "/" + installer->installerProperties.get("name", "TDME2 based application")));
				}

				/**
				 * Public constructor
				 * @param installer installer
				 */
				OnBrowseAction(Installer* installer): installer(installer) {
				}

			private:
				Installer* installer;
			};

			vector<string> extensions;
			popUps->getFileDialogScreenController()->show(
				homeFolder,
				"Install in: ",
				extensions,
				"",
				true,
				new OnBrowseAction(this)
			);
		}
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
			{
				engine->getGUI()->addRenderScreen("installer_installing");
				class InstallThread: public Thread {
					public:
						InstallThread(Installer* installer): Thread("install-thread"), installer(installer) {
						}
						void run() {
							Console::println("InstallThread::run(): init");

							//
							string cpu = "x64";
							string os;
							#if defined(__FreeBSD__)
								os = "FreeBSD";
							#elif defined(__HAIKU__)
								os = "Haiku";
							#elif defined(__linux__)
								os = "Linux";
							#elif defined(__APPLE__)
								os = "MacOSX";
							#elif defined(__NetBSD__)
								os = "NetBSD";
							#elif defined(_MSC_VER)
								os = "Windows-MSC";
							#elif defined(_WIN32)
								os = "Windows-MINGW";
							#else
								os = "Unknown";
							#endif
							auto completionFileName = os + "-" + cpu + "-upload-";
							string timestamp;

							// determine newest component file name
							if (timestamp.empty() == true) {
								vector<string> files;
								FileSystem::getInstance()->list("installer", files);
								for (auto file: files) {
									if (StringUtils::startsWith(file, completionFileName) == true) {
										Console::println("InstallThread: Have timestamp: " + file);
										timestamp = StringUtils::substring(file, completionFileName.size());
									}
								}
							}
							if (timestamp.empty() == false) {
								Console::println("InstallThread::run(): filesystem: newest timestamp: " + timestamp);
							}

							//
							auto repository = installer->installerProperties.get("repository", "");
							if (repository.empty() == false) {
								string timestampWeb;
								installer->installThreadMutex.lock();
								dynamic_cast<GUITextNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("message"))->setText(MutableString("Downloading ..."));
								dynamic_cast<GUITextNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("details"))->setText(MutableString("..."));
								dynamic_cast<GUIElementNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("progressbar"))->getController()->setValue(MutableString(0.0f, 2));
								installer->installThreadMutex.unlock();

								// check repository via apache index file for now
								try {
									HTTPClient httpClient;
									httpClient.setMethod(HTTPClient::HTTP_METHOD_GET);
									httpClient.setURL(repository);
									httpClient.execute();
									auto response = httpClient.getResponse().str();
									auto pos = 0;
									while ((pos = response.find(completionFileName, pos)) != string::npos) {
										pos+= completionFileName.size();
										auto timestampWebNew = StringUtils::substring(response, pos, pos + 14);
										pos+= 14;
										if ((timestamp.empty() == true && (timestampWeb.empty() == true || timestampWebNew > timestampWeb)) ||
											(timestamp.empty() == false && ((timestampWeb.empty() == true || timestampWebNew > timestampWeb) && timestampWebNew > timestamp))) {
											timestampWeb = timestampWebNew;
										}
									}
								} catch (Exception& exception) {
									Console::println(string("Fail: ") + exception.what());
								}

								// download archives if newer
								if (timestampWeb.empty() == false) {
									Console::println("InstallThread::run(): repository: newest timestamp: " + timestampWeb);

									// we use web installer archives
									timestamp = timestampWeb;

									// download them
									HTTPDownloadClient httpDownloadClient;
									for (auto componentIdx = 1; true; componentIdx++) {
										//
										auto componentName = installer->installerProperties.get("component" + to_string(componentIdx), "");
										if (componentName.empty() == true) break;

										//
										Console::println("InstallThread::run(): Having component: " + to_string(componentIdx) + ": " + componentName);
										auto componentInclude = installer->installerProperties.get("component" + to_string(componentIdx) + "_include", "");
										if (componentInclude.empty() == true) {
											Console::println("InstallThread::run(): component: " + to_string(componentIdx) + ": missing includes. Skipping.");
											continue;
										}
										auto componentFileName = os + "-" + cpu + "-" + StringUtils::replace(StringUtils::replace(componentName, " - ", "-"), " ", "-") + "-" + timestamp + ".ta";

										//
										Console::println("InstallThread::run(): Component: " + to_string(componentIdx) + ": component file name: " + componentFileName + ": Downloading");
										//
										dynamic_cast<GUITextNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("details"))->setText(MutableString(componentFileName));

										// sha256
										httpDownloadClient.reset();
										httpDownloadClient.setFile("./installer/" + componentFileName + ".sha256");
										httpDownloadClient.setURL(installer->installerProperties.get("repository", "") + componentFileName + ".sha256");
										httpDownloadClient.start();
										while (httpDownloadClient.isFinished() == false) {
											installer->installThreadMutex.lock();
											dynamic_cast<GUIElementNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("progressbar"))->getController()->setValue(MutableString(httpDownloadClient.getProgress(), 2));
											installer->installThreadMutex.unlock();
											Thread::sleep(250LL);
										}
										httpDownloadClient.join();

										// atchive
										httpDownloadClient.reset();
										httpDownloadClient.setFile("./installer/" + componentFileName);
										httpDownloadClient.setURL(installer->installerProperties.get("repository", "") + componentFileName);
										httpDownloadClient.start();
										while (httpDownloadClient.isFinished() == false) {
											installer->installThreadMutex.lock();
											dynamic_cast<GUIElementNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("progressbar"))->getController()->setValue(MutableString(httpDownloadClient.getProgress(), 2));
											installer->installThreadMutex.unlock();
											Thread::sleep(250LL);
										}
										httpDownloadClient.join();
									}
								}
							}

							installer->installThreadMutex.lock();
							dynamic_cast<GUITextNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("message"))->setText(MutableString("Initializing ..."));
							dynamic_cast<GUITextNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("details"))->setText(MutableString("..."));
							dynamic_cast<GUIElementNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("progressbar"))->getController()->setValue(MutableString(0.0f, 2));
							installer->installThreadMutex.unlock();

							//
							auto hadException = false;
							vector<string> log;
							vector<string> components;
							auto installPath = dynamic_cast<GUIElementNode*>(installer->engine->getGUI()->getScreen("installer_path")->getNodeById("install_folder"))->getController()->getValue().getString();
							try {
								Installer::createPathRecursively(installPath);
							} catch (Exception& exception) {
								installer->popUps->getInfoDialogScreenController()->show("An error occurred:", exception.what());
								hadException = true;
							}

							if (hadException == false) {
								for (auto componentIdx = 1; true; componentIdx++) {
									//
									auto componentName = installer->installerProperties.get("component" + to_string(componentIdx), "");
									if (componentName.empty() == true) break;

									// check if marked
									if (dynamic_cast<GUIElementNode*>(installer->engine->getGUI()->getScreen("installer_components")->getNodeById("checkbox_component" + to_string(componentIdx)))->getController()->getValue().equals("1") == false) continue;

									//
									components.push_back(componentName);

									//
									Console::println("InstallThread::run(): Having component: " + to_string(componentIdx) + ": " + componentName);
									auto componentInclude = installer->installerProperties.get("component" + to_string(componentIdx) + "_include", "");
									if (componentInclude.empty() == true) {
										Console::println("InstallThread::run(): component: " + to_string(componentIdx) + ": missing includes. Skipping.");
										continue;
									}
									auto componentFileName = os + "-" + cpu + "-" + StringUtils::replace(StringUtils::replace(componentName, " - ", "-"), " ", "-") + "-" + timestamp + ".ta";
									//
									Console::println("InstallThread::run(): Component: " + to_string(componentIdx) + ": component file name: " + componentFileName);
									//
									installer->installThreadMutex.lock();
									dynamic_cast<GUIElementNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("progressbar"))->getController()->setValue(MutableString(0.0f, 2));
									dynamic_cast<GUITextNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("details"))->setText(MutableString());
									installer->installThreadMutex.unlock();

									ArchiveFileSystem* archiveFileSystem = nullptr;
									try {
										installer->installThreadMutex.lock();
										dynamic_cast<GUITextNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("message"))->setText(MutableString("Verifying " + componentName));
										installer->installThreadMutex.unlock();
										archiveFileSystem = new ArchiveFileSystem("installer/" + componentFileName);
										if (archiveFileSystem->computeSHA256Hash() != FileSystem::getInstance()->getContentAsString("installer", componentFileName + ".sha256")) {
											throw ExceptionBase("Failed to verify: " + componentFileName + ", remove files in ./installer/ and try again");
										}
										installer->installThreadMutex.lock();
										dynamic_cast<GUITextNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("message"))->setText(MutableString("Installing " + componentName));
										installer->installThreadMutex.unlock();
										vector<string> files;
										Installer::scanArchive(archiveFileSystem, files);
										uint64_t totalSize = 0LL;
										uint64_t doneSize = 0LL;
										for (auto file: files) {
											totalSize+= archiveFileSystem->getFileSize(
												archiveFileSystem->getPathName(file),
												archiveFileSystem->getFileName(file)
											);
										}
										for (auto file: files) {
											vector<uint8_t> content;
											Console::println("InstallThread::run(): Component: " + to_string(componentIdx) + ": " + file);
											archiveFileSystem->getContent(
												archiveFileSystem->getPathName(file),
												archiveFileSystem->getFileName(file),
												content
											);
											auto generatedFileName = installPath + "/" + file;
											Installer::createPathRecursively(
												FileSystem::getStandardFileSystem()->getPathName(generatedFileName)
											);
											FileSystem::getStandardFileSystem()->setContent(
												FileSystem::getStandardFileSystem()->getPathName(generatedFileName),
												FileSystem::getStandardFileSystem()->getFileName(generatedFileName),
												content
											);
											if (archiveFileSystem->isExecutable(archiveFileSystem->getPathName(file), archiveFileSystem->getFileName(file)) == true) {
												FileSystem::getStandardFileSystem()->setExecutable(
													FileSystem::getStandardFileSystem()->getPathName(generatedFileName),
													FileSystem::getStandardFileSystem()->getFileName(generatedFileName)
												);
											}
											log.push_back(generatedFileName);
											doneSize+= content.size();
											installer->installThreadMutex.lock();
											dynamic_cast<GUITextNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("details"))->setText(MutableString(file));
											dynamic_cast<GUIElementNode*>(installer->engine->getGUI()->getScreen("installer_installing")->getNodeById("progressbar"))->getController()->setValue(MutableString(static_cast<float>(doneSize) / static_cast<float>(totalSize), 2));
											installer->installThreadMutex.unlock();
										}
										delete archiveFileSystem;
										archiveFileSystem = nullptr;
									} catch (Exception& exception) {
										if (archiveFileSystem != nullptr) delete archiveFileSystem;
										installer->popUps->getInfoDialogScreenController()->show("An error occurred:", exception.what());
										hadException = true;
										break;
									}
								}
							}

							try {
								log.push_back(installPath);
								FileSystem::getStandardFileSystem()->setContentFromStringArray(installPath, "install.files.db", log);
								FileSystem::getStandardFileSystem()->setContentFromStringArray(installPath, "install.components.db", components);
							} catch (Exception& exception) {
								installer->popUps->getInfoDialogScreenController()->show("An error occurred:", exception.what());
								hadException = true;
							}

							//
							if (hadException == false) {
								installer->installThreadMutex.lock();
								installer->screen = SCREEN_FINISHED;
								installer->engine->getGUI()->resetRenderScreens();
								installer->engine->getGUI()->addRenderScreen("installer_finished");
								installer->installThreadMutex.unlock();
							}
							// determine set names
							Console::println("InstallThread::run(): done");
							delete this;
						}
					private:
						Installer* installer;
				};
				InstallThread* installThread = new InstallThread(this);
				installThread->start();
				break;
			}
		case SCREEN_FINISHED:
			engine->getGUI()->addRenderScreen("installer_finished");
			break;
		default:
			Console::println("Installer::onActionPerformed(): Unhandled screen: " + to_string(screen));
			break;
	}
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
}

void Installer::onValueChanged(GUIElementNode* node) {
	Console::println(node->getName() + ": onValueChanged(): " + node->getController()->getValue().getString());
}


void Installer::display()
{
	installThreadMutex.lock();
	engine->display();
	engine->getGUI()->handleEvents();
	engine->getGUI()->render();
	installThreadMutex.unlock();
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

void Installer::scanArchive(ArchiveFileSystem* archiveFileSystem, vector<string>& totalFiles, const string& pathName) {
	vector<string> files;
	archiveFileSystem->list(pathName, files);
	for (auto fileName: files) {
		if (archiveFileSystem->isPath(pathName + "/" + fileName) == false) {
			totalFiles.push_back((pathName.empty() == true?"":pathName + "/") + fileName);
		} else {
			scanArchive(archiveFileSystem, totalFiles, pathName + "/" + fileName);
		}
	}

}

void Installer::createPathRecursively(const string& pathName) {
	StringTokenizer t;
	t.tokenize(pathName, "/");
	string pathCreating;
	while (t.hasMoreTokens() == true) {
		string pathComponent = t.nextToken();
		pathCreating+= "/" + pathComponent;
		if (FileSystem::getStandardFileSystem()->fileExists(pathCreating) == false) {
			FileSystem::getStandardFileSystem()->createPath(pathCreating);
		}
	}

}
