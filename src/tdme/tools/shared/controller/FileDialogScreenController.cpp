// Generated from /tdme/src/tdme/tools/shared/controller/FileDialogScreenController.java
#include <tdme/tools/shared/controller/FileDialogScreenController.h>

#include <java/io/File.h>
#include <java/io/IOException.h>
#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/CharSequence.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Exception.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/tools/shared/controller/FileDialogScreenController_setupFileDialogListBox_1.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/_Console.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::tools::shared::controller::FileDialogScreenController;
using java::io::File;
using java::io::IOException;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::CharSequence;
using java::lang::ClassCastException;
using java::lang::Comparable;
using java::lang::Exception;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::GUIParser;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::tools::shared::controller::FileDialogScreenController_setupFileDialogListBox_1;
using tdme::utils::MutableString;
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

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

FileDialogScreenController::FileDialogScreenController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

FileDialogScreenController::FileDialogScreenController() 
	: FileDialogScreenController(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void FileDialogScreenController::ctor()
{
	super::ctor();
	this->cwd = _FileSystem::getInstance()->getCurrentWorkingPath();
	this->value = new MutableString();
	this->applyAction = nullptr;
}

GUIScreenNode* FileDialogScreenController::getScreenNode()
{
	return screenNode;
}

String* FileDialogScreenController::getPathName()
{
	return cwd;
}

String* FileDialogScreenController::getFileName()
{
	return fileName->getController()->getValue()->toString();
}

void FileDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse(u"resources/tools/shared/gui"_j, u"filedialog.xml"_j);
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		caption = java_cast< GUITextNode* >(screenNode->getNodeById(u"filedialog_caption"_j));
		files = java_cast< GUIElementNode* >(screenNode->getNodeById(u"filedialog_files"_j));
		fileName = java_cast< GUIElementNode* >(screenNode->getNodeById(u"filedialog_filename"_j));
	} catch (Exception* e) {
		e->printStackTrace();
	}
}

void FileDialogScreenController::dispose()
{
}

void FileDialogScreenController::setupFileDialogListBox()
{
	auto directory = cwd;
	if (directory->length() > 50) {
		directory = ::java::lang::StringBuilder().append(u"..."_j)->append(directory->substring(directory->length() - 50 + 3))->toString();
	}

	caption->getText()->set(captionText)->append(directory);

	auto fileList = new StringArray(0);
	try {
		auto directory = cwd;
		fileList = _FileSystem::getInstance()->list(directory, new FileDialogScreenController_setupFileDialogListBox_1(this));
	} catch (IOException* ioe) {
		ioe->printStackTrace();
	}
	auto filesInnerNode = java_cast< GUIParentNode* >((files->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(files->getId())->append(u"_inner"_j)->toString())));
	auto idx = 1;
	auto filesInnerNodeSubNodesXML = u""_j;
	filesInnerNodeSubNodesXML = ::java::lang::StringBuilder(filesInnerNodeSubNodesXML).append(u"<scrollarea width=\"100%\" height=\"100%\">\n"_j)->toString();
	for (auto file : *fileList) {
		filesInnerNodeSubNodesXML = ::java::lang::StringBuilder(filesInnerNodeSubNodesXML).append(::java::lang::StringBuilder().append(u"<selectbox-option text=\""_j)->append(GUIParser::escapeQuotes(file))
			->append(u"\" value=\""_j)
			->append(GUIParser::escapeQuotes(file))
			->append(u"\" />\n"_j)->toString())->toString();
	}
	filesInnerNodeSubNodesXML = ::java::lang::StringBuilder(filesInnerNodeSubNodesXML).append(u"</scrollarea>\n"_j)->toString();
	try {
		filesInnerNode->replaceSubNodes(filesInnerNodeSubNodesXML, true);
	} catch (Exception* e) {
		e->printStackTrace();
	}
}

void FileDialogScreenController::show(String* cwd, String* captionText, StringArray* extensions, String* fileName, Action* applyAction)
{
	try {
		this->cwd = _FileSystem::getInstance()->getCanonicalPath(cwd, u""_j);
	} catch (IOException* ioe) {
		ioe->printStackTrace();
	}
	this->captionText = captionText;
	this->extensions = extensions;
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
		if (node->getId()->equals(files->getId()) == true) {
			auto selectedFile = node->getController()->getValue()->toString();
			if (_FileSystem::getInstance()->isPath(new String(cwd->getCPPWString() + L"/" + selectedFile->getCPPWString())) == true) {
				try {
					cwd = _FileSystem::getInstance()->getCanonicalPath(cwd, selectedFile);
				} catch (IOException* ioe) {
				}
				setupFileDialogListBox();
			} else {
				fileName->getController()->setValue(value->set(selectedFile));
			}
		}
	} catch (Exception* e) {
		e->printStackTrace();
	}
}

void FileDialogScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED)) {
{
				if (node->getId()->equals(u"filedialog_apply"_j)) {
					if (applyAction != nullptr)
						applyAction->performAction();

				} else if (node->getId()->equals(u"filedialog_abort"_j)) {
					close();
				}
				goto end_switch0;;
			}		}
		if (((v == GUIActionListener_Type::PERFORMED) || ((v != GUIActionListener_Type::PERFORMED)))) {
{
				goto end_switch0;;
			}		}
end_switch0:;
	}

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FileDialogScreenController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.controller.FileDialogScreenController", 55);
    return c;
}

java::lang::Class* FileDialogScreenController::getClass0()
{
	return class_();
}

