// Generated from /tdme/src/tdme/tools/shared/controller/ModelViewerScreenController.java
#include <tdme/tools/shared/controller/ModelViewerScreenController.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/CharSequence.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Exception.h>
#include <java/lang/Float.h>
#include <java/lang/NumberFormatException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>
#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelViewerScreenController_ModelViewerScreenController_1.h>
#include <tdme/tools/shared/controller/ModelViewerScreenController_onModelLoad_2.h>
#include <tdme/tools/shared/controller/ModelViewerScreenController_onModelSave_3.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>
#include <tdme/tools/viewer/TDMEViewer.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::tools::shared::controller::ModelViewerScreenController;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::CharSequence;
using java::lang::ClassCastException;
using java::lang::Comparable;
using java::lang::Exception;
using java::lang::Float;
using java::lang::NumberFormatException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::math::Vector3;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::ModelViewerScreenController_ModelViewerScreenController_1;
using tdme::tools::shared::controller::ModelViewerScreenController_onModelLoad_2;
using tdme::tools::shared::controller::ModelViewerScreenController_onModelSave_3;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelViewerView;
using tdme::tools::viewer::TDMEViewer;
using tdme::utils::MutableString;
using tdme::utils::StringConverter;
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

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

ModelViewerScreenController::ModelViewerScreenController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ModelViewerScreenController::ModelViewerScreenController(SharedModelViewerView* view) 
	: ModelViewerScreenController(*static_cast< ::default_init_tag* >(0))
{
	ctor(view);
}

MutableString* ModelViewerScreenController::TEXT_EMPTY;

void ModelViewerScreenController::ctor(SharedModelViewerView* view)
{
	super::ctor();
	this->modelPath = new FileDialogPath(u"."_j);
	this->view = view;
	auto const finalView = view;
	this->entityBaseSubScreenController = new EntityBaseSubScreenController(view->getPopUpsViews(), new ModelViewerScreenController_ModelViewerScreenController_1(this, finalView));
	this->entityDisplaySubScreenController = new EntityDisplaySubScreenController();
	this->entityBoundingVolumeSubScreenController = new EntityBoundingVolumeSubScreenController(view->getPopUpsViews(), modelPath);
}

EntityDisplaySubScreenController* ModelViewerScreenController::getEntityDisplaySubScreenController()
{
	return entityDisplaySubScreenController;
}

EntityBoundingVolumeSubScreenController* ModelViewerScreenController::getEntityBoundingVolumeSubScreenController()
{
	return entityBoundingVolumeSubScreenController;
}

GUIScreenNode* ModelViewerScreenController::getScreenNode()
{
	return screenNode;
}

FileDialogPath* ModelViewerScreenController::getModelPath()
{
	return modelPath;
}

void ModelViewerScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse(u"resources/tools/viewer/gui"_j, u"screen_modelviewer.xml"_j);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = java_cast< GUITextNode* >(screenNode->getNodeById(u"screen_caption"_j));
		modelReload = java_cast< GUIElementNode* >(screenNode->getNodeById(u"button_model_reload"_j));
		modelSave = java_cast< GUIElementNode* >(screenNode->getNodeById(u"button_model_save"_j));
		pivotX = java_cast< GUIElementNode* >(screenNode->getNodeById(u"pivot_x"_j));
		pivotY = java_cast< GUIElementNode* >(screenNode->getNodeById(u"pivot_y"_j));
		pivotZ = java_cast< GUIElementNode* >(screenNode->getNodeById(u"pivot_z"_j));
		pivotApply = java_cast< GUIElementNode* >(screenNode->getNodeById(u"button_pivot_apply"_j));
		statsOpaqueFaces = java_cast< GUIElementNode* >(screenNode->getNodeById(u"stats_opaque_faces"_j));
		statsTransparentFaces = java_cast< GUIElementNode* >(screenNode->getNodeById(u"stats_transparent_faces"_j));
		statsMaterialCount = java_cast< GUIElementNode* >(screenNode->getNodeById(u"stats_material_count"_j));
		statsOpaqueFaces->getController()->setDisabled(true);
		statsTransparentFaces->getController()->setDisabled(true);
		statsMaterialCount->getController()->setDisabled(true);
	} catch (_Exception& exception) {
		_Console::print(string("ModelViewerScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
	entityDisplaySubScreenController->initialize(screenNode);
	entityBoundingVolumeSubScreenController->initialize(screenNode);
	value = new MutableString();
}

void ModelViewerScreenController::dispose()
{
}

void ModelViewerScreenController::setScreenCaption(String* text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void ModelViewerScreenController::setEntityData(String* name, String* description)
{
	entityBaseSubScreenController->setEntityData(name, description);
	modelReload->getController()->setDisabled(false);
	modelSave->getController()->setDisabled(false);
}

void ModelViewerScreenController::unsetEntityData()
{
	entityBaseSubScreenController->unsetEntityData();
	modelReload->getController()->setDisabled(true);
	modelSave->getController()->setDisabled(true);
}

void ModelViewerScreenController::setEntityProperties(String* presetId, Iterable* entityProperties, String* selectedName)
{
	entityBaseSubScreenController->setEntityProperties(view->getEntity(), presetId, entityProperties, selectedName);
}

void ModelViewerScreenController::unsetEntityProperties()
{
	entityBaseSubScreenController->unsetEntityProperties();
}

void ModelViewerScreenController::setPivot(Vector3* pivot)
{
	pivotX->getController()->setDisabled(false);
	pivotX->getController()->getValue()->set(Tools::formatFloat(pivot->getX()));
	pivotY->getController()->setDisabled(false);
	pivotY->getController()->getValue()->set(Tools::formatFloat(pivot->getY()));
	pivotZ->getController()->setDisabled(false);
	pivotZ->getController()->getValue()->set(Tools::formatFloat(pivot->getZ()));
	pivotApply->getController()->setDisabled(false);
}

void ModelViewerScreenController::unsetPivot()
{
	pivotX->getController()->setDisabled(true);
	pivotX->getController()->getValue()->set(TEXT_EMPTY);
	pivotY->getController()->setDisabled(true);
	pivotY->getController()->getValue()->set(TEXT_EMPTY);
	pivotZ->getController()->setDisabled(true);
	pivotZ->getController()->getValue()->set(TEXT_EMPTY);
	pivotApply->getController()->setDisabled(true);
}

void ModelViewerScreenController::setStatistics(int32_t statsOpaqueFaces, int32_t statsTransparentFaces, int32_t statsMaterialCount)
{
	this->statsOpaqueFaces->getController()->setValue(value->set(statsOpaqueFaces));
	this->statsTransparentFaces->getController()->setValue(value->set(statsTransparentFaces));
	this->statsMaterialCount->getController()->setValue(value->set(statsMaterialCount));
}

void ModelViewerScreenController::onQuit()
{
	TDMEViewer::getInstance()->quit();
}

void ModelViewerScreenController::onModelLoad()
{
	auto fileName = view->getEntity() != nullptr?view->getEntity()->getEntityFileName():nullptr;
	if (fileName == nullptr) {
		fileName = view->getFileName();
	}
	fileName = Tools::getFileName(fileName);
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		modelPath->getPath(),
		u"Load from: "_j,
		new StringArray({
			u"tmm"_j,
			u"dae"_j,
			u"tm"_j
		}),
		view->getFileName(),
		new ModelViewerScreenController_onModelLoad_2(this)
	);
}

void ModelViewerScreenController::onModelSave()
{
	auto fileName = view->getEntity() != nullptr?view->getEntity()->getEntityFileName():nullptr;
	if (fileName == nullptr) {
		fileName = view->getFileName();
		if (fileName->toLowerCase()->endsWith(u".tmm"_j) == false) {
			fileName = ::java::lang::StringBuilder(fileName).append(u".tmm"_j)->toString();
		}
	}
	fileName = Tools::getFileName(fileName);
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		modelPath->getPath(),
		u"Save from: "_j,
		new StringArray({u"tmm"_j}),
		fileName,
		new ModelViewerScreenController_onModelSave_3(this)
	);
}

void ModelViewerScreenController::onModelReload()
{
	view->reloadFile();
}

void ModelViewerScreenController::onPivotApply()
{
	try {
		auto x = Float::parseFloat(pivotX->getController()->getValue()->toString());
		auto y = Float::parseFloat(pivotY->getController()->getValue()->toString());
		auto z = Float::parseFloat(pivotZ->getController()->getValue()->toString());
		view->pivotApply(x, y, z);
	} catch (_Exception& exception) {
		showErrorPopUp(u"Warning"_j, new String(StringConverter::toWideString(string(exception.what()))));
	}
}

void ModelViewerScreenController::saveFile(String* pathName, String* fileName) /* throws(Exception) */
{
	view->saveFile(pathName, fileName);
}

void ModelViewerScreenController::loadFile(String* pathName, String* fileName) /* throws(Exception) */
{
	view->loadFile(pathName, fileName);
}

void ModelViewerScreenController::showErrorPopUp(String* caption, String* message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void ModelViewerScreenController::onValueChanged(GUIElementNode* node)
{
	entityBaseSubScreenController->onValueChanged(node, view->getEntity());
}

void ModelViewerScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	entityBaseSubScreenController->onActionPerformed(type, node, view->getEntity());
	entityDisplaySubScreenController->onActionPerformed(type, node);
	entityBoundingVolumeSubScreenController->onActionPerformed(type, node, view->getEntity());
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED)) {
{
				if (node->getId()->equals(u"button_model_load"_j)) {
					onModelLoad();
				} else if (node->getId()->equals(u"button_model_reload"_j)) {
					onModelReload();
				} else if (node->getId()->equals(u"button_model_save"_j)) {
					onModelSave();
				} else if (node->getId()->equals(u"button_pivot_apply"_j)) {
					onPivotApply();
				} else {
					_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ModelViewerScreenController::onActionPerformed()::unknown, type='"_j)->append(static_cast< Object* >(type))
						->append(u"', id = '"_j)
						->append(node->getId())
						->append(u"'"_j)
						->append(u", name = '"_j)
						->append(node->getName())
						->append(u"'"_j)->toString()));
				}
				goto end_switch0;;
			}		}
		if ((v == GUIActionListener_Type::PERFORMED) || (v == GUIActionListener_Type::PERFORMING)) {
{
				goto end_switch0;;
			}		}
end_switch0:;
	}

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelViewerScreenController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.controller.ModelViewerScreenController", 56);
    return c;
}

void ModelViewerScreenController::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		TEXT_EMPTY = new MutableString(u""_j);
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* ModelViewerScreenController::getClass0()
{
	return class_();
}

