#include <tdme/tools/shared/controller/FileDialogScreenController.h>

#include <string>
#include <vector>


#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>
#include <tdme/tools/shared/controller/FileDialogScreenController_setupFileDialogListBox_1.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringUtils.h>

using std::vector;
using std::wstring;


using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::gui::GUIParser;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemInterface;
using tdme::tools::shared::controller::FileDialogScreenController_setupFileDialogListBox_1;
using tdme::utils::MutableString;
using tdme::utils::StringUtils;
using tdme::utils::Console;
using tdme::utils::Exception;

FileDialogScreenController::FileDialogScreenController() 
{
	this->cwd = _FileSystem::getInstance()->getCurrentWorkingPathName();
	this->value = new MutableString();
	this->applyAction = nullptr;
}

GUIScreenNode* FileDialogScreenController::getScreenNode()
{
	return screenNode;
}

const wstring& FileDialogScreenController::getPathName()
{
	return cwd;
}

const wstring FileDialogScreenController::getFileName()
{
	return fileName->getController()->getValue()->toWString();
}

void FileDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse(L"resources/tools/shared/gui", L"filedialog.xml");
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		caption = dynamic_cast< GUITextNode* >(screenNode->getNodeById(L"filedialog_caption"));
		files = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"filedialog_files"));
		fileName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"filedialog_filename"));
	} catch (Exception& exception) {
		Console::print(string("FileDialogScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void FileDialogScreenController::dispose()
{
}

void FileDialogScreenController::setupFileDialogListBox()
{
	auto directory = cwd;
	if (directory.length() > 50) {
		directory = L"..." + StringUtils::substring(directory, directory.length() - 50 + 3);
	}

	caption->getText()->set(captionText)->append(directory);

	vector<wstring> fileList;
	try {
		auto directory = cwd;
		_FileSystem::getInstance()->list(directory, &fileList, new FileDialogScreenController_setupFileDialogListBox_1(this));
	} catch (Exception& exception) {
		Console::print(string("FileDialogScreenController::setupFileDialogListBox(): An error occurred: "));
		Console::println(string(exception.what()));
	}

	auto filesInnerNode = dynamic_cast< GUIParentNode* >(files->getScreenNode()->getNodeById(files->getId() + L"_inner"));
	auto idx = 1;
	wstring filesInnerNodeSubNodesXML = L"";
	filesInnerNodeSubNodesXML =
		filesInnerNodeSubNodesXML +
		L"<scrollarea width=\"100%\" height=\"100%\">\n";
	for (auto& file : fileList) {
		filesInnerNodeSubNodesXML =
			filesInnerNodeSubNodesXML +
			L"<selectbox-option text=\"" +
			GUIParser::escapeQuotes(file) +
			L"\" value=\"" +
			GUIParser::escapeQuotes(file) +
			L"\" />\n";
	}
	filesInnerNodeSubNodesXML =
		filesInnerNodeSubNodesXML + L"</scrollarea>\n";
	try {
		filesInnerNode->replaceSubNodes(filesInnerNodeSubNodesXML, true);
	} catch (Exception& exception) {
		Console::print(string("FileDialogScreenController::setupFileDialogListBox(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void FileDialogScreenController::show(const wstring& cwd, const wstring& captionText, vector<wstring>* extensions, const wstring& fileName, Action* applyAction)
{
	try {
		this->cwd = _FileSystem::getInstance()->getCanonicalPath(cwd, L"");
	} catch (Exception& exception) {
		Console::print(string("FileDialogScreenController::show(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	this->captionText = captionText;
	this->extensions = *extensions;
	this->fileName->getController()->setValue(value->set(fileName));
	setupFileDialogListBox();
	screenNode->setVisible(true);
	this->applyAction = applyAction;
}

void FileDialogScreenController::close()
{
	screenNode->setVisible(false);
}

void FileDialogScreenController::onValueChanged(GUIElementNode* node)
{
	try {
		if (node->getId().compare(files->getId()) == 0) {
			auto selectedFile = node->getController()->getValue()->toWString();
			if (_FileSystem::getInstance()->isPath(cwd + L"/" + selectedFile) == true) {
				try {
					cwd = _FileSystem::getInstance()->getCanonicalPath(cwd, selectedFile);
				} catch (Exception& exception) {
					Console::print(string("FileDialogScreenController::onValueChanged(): An error occurred: "));
					Console::println(string(exception.what()));
				}
				setupFileDialogListBox();
			} else {
				fileName->getController()->setValue(value->set(selectedFile));
			}
		}
	} catch (Exception& exception) {
		Console::print(string("FileDialogScreenController::onValueChanged(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void FileDialogScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED))
		{
			{
				if (node->getId().compare(L"filedialog_apply") == 0) {
					if (applyAction != nullptr)
						applyAction->performAction();

				} else if (node->getId().compare(L"filedialog_abort") == 0) {
					close();
				}
				goto end_switch0;;
			}
		}
		if (((v == GUIActionListener_Type::PERFORMED) || ((v != GUIActionListener_Type::PERFORMED))))
		{
			{
				goto end_switch0;;
			}
		}
		end_switch0:;
	}

}
