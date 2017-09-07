// Generated from /tdme/src/tdme/tools/leveleditor/controller/LevelEditorScreenController.java
#include <tdme/tools/leveleditor/controller/LevelEditorScreenController.h>

#include <vector>
#include <string>

#include <java/io/Serializable.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Comparable.h>
#include <java/lang/Float.h>
#include <java/lang/Iterable.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Collection.h>
#include <java/util/Iterator.h>
#include <java/util/StringTokenizer.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/LevelEditorScreenController_onMapLoad_1.h>
#include <tdme/tools/leveleditor/controller/LevelEditorScreenController_onMapSave_2.h>
#include <tdme/tools/leveleditor/views/LevelEditorView.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelEditorLight.h>
#include <tdme/tools/shared/model/LevelEditorObject.h>
#include <tdme/tools/shared/model/LevelPropertyPresets.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>
#include <tdme/utils/_ExceptionBase.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::vector;
using std::wstring;

using tdme::tools::leveleditor::controller::LevelEditorScreenController;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::Float;
using java::lang::Iterable;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Collection;
using java::util::Iterator;
using java::util::StringTokenizer;
using tdme::engine::model::Color4;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::LevelEditorScreenController_onMapLoad_1;
using tdme::tools::leveleditor::controller::LevelEditorScreenController_onMapSave_2;
using tdme::tools::leveleditor::views::LevelEditorView;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorLight;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::tools::shared::model::LevelPropertyPresets;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;
using tdme::utils::StringConverter;
using tdme::utils::StringUtils;
using tdme::utils::_Exception;
using tdme::utils::_ExceptionBase;
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

namespace tdme {
namespace gui {
namespace nodes {
typedef ::SubArray< ::tdme::gui::nodes::GUINode, ::java::lang::ObjectArray > GUINodeArray;
typedef ::SubArray< ::tdme::gui::nodes::GUIParentNode, GUINodeArray > GUIParentNodeArray;
typedef ::SubArray< ::tdme::gui::nodes::GUIElementNode, GUIParentNodeArray > GUIElementNodeArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

MutableString* LevelEditorScreenController::CHECKBOX_CHECKED = new MutableString(L"1");

MutableString* LevelEditorScreenController::CHECKBOX_UNCHECKED = new MutableString(L"");

MutableString* LevelEditorScreenController::TEXT_EMPTY = new MutableString(L"");

LevelEditorScreenController::LevelEditorScreenController(LevelEditorView* view) 
{
	this->view = view;
	this->mapPath = new FileDialogPath(L".");
}

GUIScreenNode* LevelEditorScreenController::getScreenNode()
{
	return screenNode;
}

FileDialogPath* LevelEditorScreenController::getMapPath()
{
	return mapPath;
}

void LevelEditorScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse(u"resources/tools/leveleditor/gui"_j, u"screen_leveleditor.xml"_j);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById(u"screen_caption"_j));
		gridEnabled = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"grid_enabled"_j));
		gridYPosition = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"grid_y_position"_j));
		mapWidth = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"map_width"_j));
		mapDepth = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"map_depth"_j));
		mapHeight = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"map_height"_j));
		mapPropertyName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"map_property_name"_j));
		mapPropertyValue = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"map_property_value"_j));
		mapPropertySave = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_map_properties_save"_j));
		mapPropertyRemove = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_map_properties_remove"_j));
		mapPropertiesListBox = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"map_properties_listbox"_j));
		objectName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_name"_j));
		objectDescription = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_description"_j));
		objectModel = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_model"_j));
		objectCenter = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_center"_j));
		btnObjectDataApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_objectdata_apply"_j));
		btnObjectTranslationApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_translation_apply"_j));
		btnObjectScaleApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_scale_apply"_j));
		btnObjectRotationApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_rotation_apply"_j));
		btnObjectColor = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_object_color"_j));
		btnObjectCenter = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_object_center"_j));
		btnObjectRemove = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_object_remove"_j));
		objectTranslationX = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_translation_x"_j));
		objectTranslationY = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_translation_y"_j));
		objectTranslationZ = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_translation_z"_j));
		objectScaleX = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_scale_x"_j));
		objectScaleY = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_scale_y"_j));
		objectScaleZ = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_scale_z"_j));
		objectRotationX = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_rotation_x"_j));
		objectRotationY = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_rotation_y"_j));
		objectRotationZ = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_rotation_z"_j));
		objectPropertyName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_property_name"_j));
		objectPropertyValue = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_property_value"_j));
		btnObjectPropertySave = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_object_properties_save"_j));
		btnObjectPropertyRemove = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_object_properties_remove"_j));
		btnObjectPropertyAdd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_object_properties_add"_j));
		btnObjectPropertyRemove = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_object_properties_remove"_j));
		btnObjectPropertyPresetApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_object_properties_presetapply"_j));
		objectPropertiesListBox = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_properties_listbox"_j));
		objectPropertiesPresets = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"object_properties_presets"_j));
		objectsListBox = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"objects_listbox"_j));
		mapWidth->getController()->setDisabled(true);
		mapDepth->getController()->setDisabled(true);
		mapHeight->getController()->setDisabled(true);
		objectModel->getController()->setDisabled(true);
		objectCenter->getController()->setDisabled(true);
		lightsPresets = new GUIElementNodeArray(4);
		lightsAmbient = new GUIElementNodeArray(4);
		lightsDiffuse = new GUIElementNodeArray(4);
		lightsSpecular = new GUIElementNodeArray(4);
		lightsPosition = new GUIElementNodeArray(4);
		lightsConstAttenuation = new GUIElementNodeArray(4);
		lightsLinAttenuation = new GUIElementNodeArray(4);
		lightsQuadAttenuation = new GUIElementNodeArray(4);
		lightsSpotTo = new GUIElementNodeArray(4);
		lightsSpotDirection = new GUIElementNodeArray(4);
		lightsSpotExponent = new GUIElementNodeArray(4);
		lightsSpotCutoff = new GUIElementNodeArray(4);
		ligthsSpotDirectionCompute = new GUIElementNodeArray(4);
		lightsEnabled = new GUIElementNodeArray(4);
		for (auto i = 0; i < 4; i++) {
			lightsPresets->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"presets_light"_j)->append(i)->toString())));
			lightsAmbient->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_ambient"_j)->toString())));
			lightsDiffuse->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_diffuse"_j)->toString())));
			lightsSpecular->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_specular"_j)->toString())));
			lightsPosition->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_position"_j)->toString())));
			lightsLinAttenuation->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_linear_attenuation"_j)->toString())));
			lightsConstAttenuation->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_constant_attenuation"_j)->toString())));
			lightsQuadAttenuation->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_quadratic_attenuation"_j)->toString())));
			lightsSpotTo->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_spot_to"_j)->toString())));
			lightsSpotDirection->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_spot_direction"_j)->toString())));
			lightsSpotExponent->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_spot_exponent"_j)->toString())));
			lightsSpotCutoff->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_spot_cutoff"_j)->toString())));
			ligthsSpotDirectionCompute->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"button_light"_j)->append(i)
				->append(u"_spotdirection_compute"_j)->toString())));
			lightsEnabled->set(i, dynamic_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"light"_j)->append(i)
				->append(u"_enabled"_j)->toString())));
		}
		value = new MutableString();
		selectedObjects = new MutableString();
 	} catch (_Exception& exception) {
		_Console::print(string("LevelEditorScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
}

void LevelEditorScreenController::dispose()
{
}

void LevelEditorScreenController::setScreenCaption(const wstring& text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void LevelEditorScreenController::setGrid(bool enabled, float gridY)
{
	gridEnabled->getController()->setValue(enabled == true ? CHECKBOX_CHECKED : CHECKBOX_UNCHECKED);
	gridYPosition->getController()->setValue(value->set(String::valueOf(gridY)));
}

void LevelEditorScreenController::setLevelSize(float width, float depth, float height)
{
	mapWidth->getController()->setValue(value->set(Tools::formatFloat(width)));
	mapDepth->getController()->setValue(value->set(Tools::formatFloat(depth)));
	mapHeight->getController()->setValue(value->set(Tools::formatFloat(height)));
}

void LevelEditorScreenController::unsetObjectProperties()
{
	objectPropertiesPresets->getController()->setValue(value->set(u"none"_j));
	objectPropertiesPresets->getController()->setDisabled(true);
	btnObjectPropertyPresetApply->getController()->setDisabled(true);
	objectPropertiesListBox->getController()->setDisabled(true);
	btnObjectPropertyAdd->getController()->setDisabled(true);
	btnObjectPropertyRemove->getController()->setDisabled(true);
	btnObjectPropertySave->getController()->setDisabled(true);
	objectPropertyName->getController()->setValue(TEXT_EMPTY);
	objectPropertyName->getController()->setDisabled(true);
	objectPropertyValue->getController()->setValue(TEXT_EMPTY);
	objectPropertyValue->getController()->setDisabled(true);
	auto objectPropertiesListBoxInnerNode = dynamic_cast< GUIParentNode* >((objectPropertiesListBox->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(objectPropertiesListBox->getId())->append(u"_inner"_j)->toString())));
	objectPropertiesListBoxInnerNode->clearSubNodes();
}

const wstring& LevelEditorScreenController::getObjectPropertyPresetSelection()
{
	return L"";
}

void LevelEditorScreenController::setObjectData(const wstring& name, const wstring& description, const wstring& modelName, Vector3* center)
{
	objectName->getController()->setDisabled(false);
	objectName->getController()->setValue(value->set(name));
	objectDescription->getController()->setDisabled(false);
	objectDescription->getController()->setValue(value->set(description));
	objectModel->getController()->setValue(value->set(modelName));
	objectCenter->getController()->setValue(value->reset()->append(Tools::formatFloat(center->getX()))->append(u", "_j)->append(Tools::formatFloat(center->getY()))->append(u", "_j)->append(Tools::formatFloat(center->getZ())));
	btnObjectDataApply->getController()->setDisabled(false);
}

void LevelEditorScreenController::unsetObjectData()
{
	objectName->getController()->setValue(TEXT_EMPTY);
	objectName->getController()->setDisabled(true);
	objectDescription->getController()->setValue(TEXT_EMPTY);
	objectDescription->getController()->setDisabled(true);
	objectModel->getController()->setValue(TEXT_EMPTY);
	objectModel->getController()->setDisabled(true);
	objectCenter->getController()->setValue(TEXT_EMPTY);
	objectCenter->getController()->setDisabled(true);
	btnObjectDataApply->getController()->setDisabled(true);
}

void LevelEditorScreenController::onObjectDataApply()
{
	if (view->objectDataApply(objectName->getController()->getValue()->toString()->getCPPWString(), objectDescription->getController()->getValue()->toString()->getCPPWString()) == false) {
		showErrorPopUp(L"Warning", L"Changing object data failed");
	}
}

void LevelEditorScreenController::setObjectListbox(LevelEditorLevel* level)
{
	selectedObjects->set(objectsListBox->getController()->getValue());
	auto objectsListBoxInnerNode = dynamic_cast< GUIParentNode* >((objectsListBox->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(objectsListBox->getId())->append(u"_inner"_j)->toString())));
	auto idx = 1;
	auto objectsListBoxSubNodesXML = u""_j;
	objectsListBoxSubNodesXML = ::java::lang::StringBuilder(objectsListBoxSubNodesXML).append(::java::lang::StringBuilder().append(u"<scrollarea-vertical id=\""_j)->append(objectsListBox->getId())
		->append(u"_inner_scrollarea\" width=\"100%\" height=\"100%\">\n"_j)->toString())->toString();
	for (int i = 0; i < level->getObjectCount(); i++) {
		auto objectId = level->getObjectAt(i)->getId();
		objectsListBoxSubNodesXML = ::java::lang::StringBuilder(objectsListBoxSubNodesXML).append(::java::lang::StringBuilder().append(u"<selectbox-multiple-option text=\""_j)->append(GUIParser::escapeQuotes(objectId))
			->append(u"\" value=\""_j)
			->append(GUIParser::escapeQuotes(objectId))
			->append(u"\" "_j)
			->append(u"/>\n"_j)->toString())->toString();
	}
	objectsListBoxSubNodesXML = ::java::lang::StringBuilder(objectsListBoxSubNodesXML).append(u"</scrollarea-vertical>\n"_j)->toString();
	try {
		objectsListBoxInnerNode->replaceSubNodes(objectsListBoxSubNodesXML, false);
	} catch (_Exception& exception) {
		_Console::print(string("LevelEditorScreenController::setObjectListbox(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	objectsListBox->getController()->setValue(selectedObjects);
}

void LevelEditorScreenController::unselectObjectInObjectListBox(const wstring& objectId)
{
	selectedObjects->set(objectsListBox->getController()->getValue());
	value->set(u'|')->append(objectId)->append(u'|');
	auto pos = selectedObjects->indexOf(value);
	if (pos != -1)
		selectedObjects->delete_(pos, value->length());

	objectsListBox->getController()->setValue(selectedObjects);
}

void LevelEditorScreenController::unselectObjectsInObjectListBox()
{
	objectsListBox->getController()->setValue(value->reset());
}

void LevelEditorScreenController::selectObjectInObjectListbox(const wstring& objectId)
{
	selectedObjects->set(objectsListBox->getController()->getValue());
	value->set(u'|')->append(objectId)->append(u'|');
	auto pos = selectedObjects->indexOf(value);
	if (pos == -1)
		selectedObjects->append(value);

	objectsListBox->getController()->setValue(selectedObjects);
}

void LevelEditorScreenController::onObjectsSelect()
{
	vector<wstring> selectedObjectList;
	auto t = new StringTokenizer(objectsListBox->getController()->getValue()->toString(), u"|"_j);
	while (t->hasMoreTokens()) {
		selectedObjectList.push_back(t->nextToken()->getCPPWString());
	}
	if (selectedObjectList.empty() == false)
		view->selectObjects(&selectedObjectList);

}

void LevelEditorScreenController::onObjectsUnselect()
{
	view->unselectObjects();
}

void LevelEditorScreenController::setObject(Vector3* translation, Vector3* scale, float rotationX, float rotationY, float rotationZ)
{
	btnObjectTranslationApply->getController()->setDisabled(false);
	btnObjectScaleApply->getController()->setDisabled(false);
	btnObjectRotationApply->getController()->setDisabled(false);
	btnObjectColor->getController()->setDisabled(false);
	btnObjectCenter->getController()->setDisabled(false);
	btnObjectRemove->getController()->setDisabled(false);
	objectTranslationX->getController()->setDisabled(false);
	objectTranslationY->getController()->setDisabled(false);
	objectTranslationZ->getController()->setDisabled(false);
	objectScaleX->getController()->setDisabled(false);
	objectScaleY->getController()->setDisabled(false);
	objectScaleZ->getController()->setDisabled(false);
	objectRotationX->getController()->setDisabled(false);
	objectRotationY->getController()->setDisabled(false);
	objectRotationZ->getController()->setDisabled(false);
	objectTranslationX->getController()->setValue(value->set(Tools::formatFloat(translation->getX())));
	objectTranslationY->getController()->setValue(value->set(Tools::formatFloat(translation->getY())));
	objectTranslationZ->getController()->setValue(value->set(Tools::formatFloat(translation->getZ())));
	objectScaleX->getController()->setValue(value->set(Tools::formatFloat(scale->getX())));
	objectScaleY->getController()->setValue(value->set(Tools::formatFloat(scale->getY())));
	objectScaleZ->getController()->setValue(value->set(Tools::formatFloat(scale->getZ())));
	objectRotationX->getController()->setValue(value->set(Tools::formatFloat(rotationX)));
	objectRotationY->getController()->setValue(value->set(Tools::formatFloat(rotationY)));
	objectRotationZ->getController()->setValue(value->set(Tools::formatFloat(rotationZ)));
}

void LevelEditorScreenController::unsetObject()
{
	btnObjectTranslationApply->getController()->setDisabled(true);
	btnObjectScaleApply->getController()->setDisabled(true);
	btnObjectRotationApply->getController()->setDisabled(true);
	btnObjectColor->getController()->setDisabled(true);
	btnObjectCenter->getController()->setDisabled(true);
	btnObjectRemove->getController()->setDisabled(true);
	objectTranslationX->getController()->setDisabled(true);
	objectTranslationY->getController()->setDisabled(true);
	objectTranslationZ->getController()->setDisabled(true);
	objectScaleX->getController()->setDisabled(true);
	objectScaleY->getController()->setDisabled(true);
	objectScaleZ->getController()->setDisabled(true);
	objectRotationX->getController()->setDisabled(true);
	objectRotationY->getController()->setDisabled(true);
	objectRotationZ->getController()->setDisabled(true);
	objectTranslationX->getController()->setValue(TEXT_EMPTY);
	objectTranslationY->getController()->setValue(TEXT_EMPTY);
	objectTranslationZ->getController()->setValue(TEXT_EMPTY);
	objectScaleX->getController()->setValue(TEXT_EMPTY);
	objectScaleY->getController()->setValue(TEXT_EMPTY);
	objectScaleZ->getController()->setValue(TEXT_EMPTY);
	objectRotationX->getController()->setValue(TEXT_EMPTY);
	objectRotationY->getController()->setValue(TEXT_EMPTY);
	objectRotationZ->getController()->setValue(TEXT_EMPTY);
}

void LevelEditorScreenController::onMapPropertiesSelectionChanged()
{
	mapPropertyName->getController()->setDisabled(true);
	mapPropertyName->getController()->setValue(TEXT_EMPTY);
	mapPropertyValue->getController()->setDisabled(true);
	mapPropertyValue->getController()->setValue(TEXT_EMPTY);
	mapPropertySave->getController()->setDisabled(true);
	mapPropertyRemove->getController()->setDisabled(true);
	auto mapProperty = view->getLevel()->getProperty(mapPropertiesListBox->getController()->getValue()->toString()->getCPPWString());
	if (mapProperty != nullptr) {
		mapPropertyName->getController()->setValue(value->set(mapProperty->getName()));
		mapPropertyValue->getController()->setValue(value->set(mapProperty->getValue()));
		mapPropertyName->getController()->setDisabled(false);
		mapPropertyValue->getController()->setDisabled(false);
		mapPropertySave->getController()->setDisabled(false);
		mapPropertyRemove->getController()->setDisabled(false);
	}
}

void LevelEditorScreenController::setMapProperties(LevelEditorLevel* level, const wstring& selectedName)
{
	mapPropertyName->getController()->setDisabled(true);
	mapPropertyValue->getController()->setDisabled(true);
	mapPropertySave->getController()->setDisabled(true);
	auto mapPropertiesListBoxInnerNode = dynamic_cast< GUIParentNode* >((mapPropertiesListBox->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(mapPropertiesListBox->getId())->append(u"_inner"_j)->toString())));
	auto idx = 1;
	auto mapPropertiesListBoxSubNodesXML = u""_j;
	mapPropertiesListBoxSubNodesXML = ::java::lang::StringBuilder(mapPropertiesListBoxSubNodesXML).append(::java::lang::StringBuilder().append(u"<scrollarea-vertical id=\""_j)->append(mapPropertiesListBox->getId())
		->append(u"_inner_scrollarea\" width=\"100%\" height=\"100%\">\n"_j)->toString())->toString();
	for (auto i = 0; i < level->getPropertyCount(); i++) {
		PropertyModelClass* mapProperty = level->getPropertyByIndex(i);
		mapPropertiesListBoxSubNodesXML = ::java::lang::StringBuilder(mapPropertiesListBoxSubNodesXML).append(::java::lang::StringBuilder().append(u"<selectbox-option text=\""_j)->append(GUIParser::escapeQuotes(mapProperty->getName()))
			->append(u": "_j)
			->append(GUIParser::escapeQuotes(mapProperty->getValue()))
			->append(u"\" value=\""_j)
			->append(GUIParser::escapeQuotes(mapProperty->getName()))
			->append(u"\" "_j)
			->append((selectedName.length() > 0 && mapProperty->getName() == selectedName ? u"selected=\"true\" "_j : u""_j))
			->append(u"/>\n"_j)->toString())->toString();
	}
	mapPropertiesListBoxSubNodesXML = ::java::lang::StringBuilder(mapPropertiesListBoxSubNodesXML).append(u"</scrollarea-vertical>\n"_j)->toString();
	try {
		mapPropertiesListBoxInnerNode->replaceSubNodes(mapPropertiesListBoxSubNodesXML, false);
	} catch (_Exception& exception) {
		_Console::print(string("LevelEditorScreenController::setMapProperties(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	onMapPropertiesSelectionChanged();
}

void LevelEditorScreenController::onMapPropertySave()
{
	if (view->mapPropertySave(
		mapPropertiesListBox->getController()->getValue()->toString()->getCPPWString(),
		mapPropertyName->getController()->getValue()->toString()->getCPPWString(),
		mapPropertyValue->getController()->getValue()->toString()->getCPPWString()) == false) {
		showErrorPopUp(L"Warning", L"Saving map property failed");
	}
}

void LevelEditorScreenController::onMapPropertyAdd()
{
	if (view->mapPropertyAdd() == false) {
		showErrorPopUp(L"Warning", L"Adding new map property failed");
	}
}

void LevelEditorScreenController::onMapPropertyRemove()
{
	if (view->mapPropertyRemove(mapPropertiesListBox->getController()->getValue()->toString()->getCPPWString()) == false) {
		showErrorPopUp(L"Warning", L"Removing map property failed");
	}
}

void LevelEditorScreenController::setObjectPresetIds(const map<wstring, vector<PropertyModelClass*>>* objectPresetIds)
{
	auto objectPropertiesPresetsInnerNode = dynamic_cast< GUIParentNode* >((objectPropertiesPresets->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(objectPropertiesPresets->getId())->append(u"_inner"_j)->toString())));
	auto idx = 0;
	auto objectPropertiesPresetsInnerNodeSubNodesXML = u""_j;
	objectPropertiesPresetsInnerNodeSubNodesXML = ::java::lang::StringBuilder(objectPropertiesPresetsInnerNodeSubNodesXML).append(::java::lang::StringBuilder().append(u"<scrollarea-vertical id=\""_j)->append(objectPropertiesPresets->getId())
		->append(u"_inner_scrollarea\" width=\"100%\" height=\"100\">\n"_j)->toString())->toString();
	for (auto it: *objectPresetIds) {
		auto modelPresetId = new String(it.first);
		objectPropertiesPresetsInnerNodeSubNodesXML = ::java::lang::StringBuilder(objectPropertiesPresetsInnerNodeSubNodesXML).append(::java::lang::StringBuilder().append(u"<dropdown-option text=\""_j)->append(GUIParser::escapeQuotes(modelPresetId))
			->append(u"\" value=\""_j)
			->append(GUIParser::escapeQuotes(modelPresetId))
			->append(u"\" "_j)
			->append((idx == 0 ? u"selected=\"true\" "_j : u""_j))
			->append(u" />\n"_j)->toString())->toString();
		idx++;
	}
	objectPropertiesPresetsInnerNodeSubNodesXML = ::java::lang::StringBuilder(objectPropertiesPresetsInnerNodeSubNodesXML).append(u"</scrollarea-vertical>\n"_j)->toString();
	try {
		objectPropertiesPresetsInnerNode->replaceSubNodes(objectPropertiesPresetsInnerNodeSubNodesXML, true);
	} catch (_Exception& exception) {
		_Console::print(string("LevelEditorScreenController::setObjectPresetIds(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
}

void LevelEditorScreenController::onObjectPropertiesSelectionChanged()
{
	objectPropertyName->getController()->setDisabled(true);
	objectPropertyName->getController()->setValue(TEXT_EMPTY);
	objectPropertyValue->getController()->setDisabled(true);
	objectPropertyValue->getController()->setValue(TEXT_EMPTY);
	btnObjectPropertySave->getController()->setDisabled(true);
	btnObjectPropertyRemove->getController()->setDisabled(true);
	auto levelEditorObject = view->getSelectedObject();
	if (levelEditorObject == nullptr)
		return;

	auto modelProperty = levelEditorObject->getProperty(objectPropertiesListBox->getController()->getValue()->toString()->getCPPWString());
	if (modelProperty != nullptr) {
		objectPropertyName->getController()->setValue(value->set(modelProperty->getName()));
		objectPropertyValue->getController()->setValue(value->set(modelProperty->getValue()));
		objectPropertyName->getController()->setDisabled(false);
		objectPropertyValue->getController()->setDisabled(false);
		btnObjectPropertySave->getController()->setDisabled(false);
		btnObjectPropertyRemove->getController()->setDisabled(false);
	}
}

void LevelEditorScreenController::setObjectProperties(const wstring& presetId, LevelEditorObject* object, const wstring& selectedName)
{
	objectPropertiesPresets->getController()->setDisabled(false);
	btnObjectPropertyPresetApply->getController()->setDisabled(false);
	objectPropertiesListBox->getController()->setDisabled(false);
	btnObjectPropertyAdd->getController()->setDisabled(false);
	btnObjectPropertyRemove->getController()->setDisabled(false);
	btnObjectPropertySave->getController()->setDisabled(true);
	objectPropertyName->getController()->setDisabled(true);
	objectPropertyValue->getController()->setDisabled(true);
	objectPropertiesPresets->getController()->setValue(presetId.length() > 0 ? value->set(presetId) : value->set(L"none"));
	auto objectPropertiesListBoxInnerNode = dynamic_cast< GUIParentNode* >((objectPropertiesListBox->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(objectPropertiesListBox->getId())->append(u"_inner"_j)->toString())));
	auto idx = 1;
	auto objectPropertiesListBoxSubNodesXML = u""_j;
	objectPropertiesListBoxSubNodesXML = ::java::lang::StringBuilder(objectPropertiesListBoxSubNodesXML).append(::java::lang::StringBuilder().append(u"<scrollarea-vertical id=\""_j)->append(objectPropertiesListBox->getId())
		->append(u"_inner_scrollarea\" width=\"100%\" height=\"100%\">\n"_j)->toString())->toString();
	for (auto i = 0; i < object->getPropertyCount(); i++) {
	PropertyModelClass* objectProperty = object->getPropertyByIndex(i);
		objectPropertiesListBoxSubNodesXML = ::java::lang::StringBuilder(objectPropertiesListBoxSubNodesXML).append(::java::lang::StringBuilder().append(u"<selectbox-option text=\""_j)->append(GUIParser::escapeQuotes(objectProperty->getName()))
			->append(u": "_j)
			->append(GUIParser::escapeQuotes(objectProperty->getValue()))
			->append(u"\" value=\""_j)
			->append(GUIParser::escapeQuotes(objectProperty->getName()))
			->append(u"\" "_j)
			->append((selectedName.length() > 0 && objectProperty->getName() == selectedName? u"selected=\"true\" "_j : u""_j))
			->append(u"/>\n"_j)->toString())->toString();
	}
	objectPropertiesListBoxSubNodesXML = ::java::lang::StringBuilder(objectPropertiesListBoxSubNodesXML).append(u"</scrollarea-vertical>\n"_j)->toString();
	try {
		objectPropertiesListBoxInnerNode->replaceSubNodes(objectPropertiesListBoxSubNodesXML, false);
	} catch (_Exception& exception) {
		_Console::print(string("LevelEditorScreenController::setObjectProperties(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	onObjectPropertiesSelectionChanged();
}

void LevelEditorScreenController::onObjectPropertySave()
{
	if (view->objectPropertySave(
		objectPropertiesListBox->getController()->getValue()->toString()->getCPPWString(),
		objectPropertyName->getController()->getValue()->toString()->getCPPWString(),
		objectPropertyValue->getController()->getValue()->toString()->getCPPWString()) == false) {
		showErrorPopUp(L"Warning", L"Saving object property failed");
	}
}

void LevelEditorScreenController::onObjectPropertyAdd()
{
	if (view->objectPropertyAdd() == false) {
		showErrorPopUp(L"Warning", L"Adding new object property failed");
	}
}

void LevelEditorScreenController::onObjectPropertyRemove()
{
	if (view->objectPropertyRemove(objectPropertiesListBox->getController()->getValue()->toString()->getCPPWString()) == false) {
		showErrorPopUp(L"Warning", L"Removing object property failed");
	}
}

void LevelEditorScreenController::onQuit()
{
	TDMELevelEditor::getInstance()->quit();
}

void LevelEditorScreenController::onObjectTranslationApply()
{
	try {
		auto x = Float::parseFloat(objectTranslationX->getController()->getValue()->toString());
		auto y = Float::parseFloat(objectTranslationY->getController()->getValue()->toString());
		auto z = Float::parseFloat(objectTranslationZ->getController()->getValue()->toString());
		view->objectTranslationApply(x, y, z);
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(exception.what()));
	}
}

void LevelEditorScreenController::onObjectScaleApply()
{
	try {
		auto x = Float::parseFloat(objectScaleX->getController()->getValue()->toString());
		auto y = Float::parseFloat(objectScaleY->getController()->getValue()->toString());
		auto z = Float::parseFloat(objectScaleZ->getController()->getValue()->toString());
		if (x < -10.0f || x > 10.0f)
			throw _ExceptionBase("x scale must be within -10 .. +10");

		if (y < -10.0f || y > 10.0f)
			throw _ExceptionBase("y scale must be within -10 .. +10");

		if (z < -10.0f || z > 10.0f)
			throw _ExceptionBase("z scale must be within -10 .. +10");

		view->objectScaleApply(x, y, z);
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(exception.what()));
	}
}

void LevelEditorScreenController::onObjectRotationsApply()
{
	try {
		auto x = Float::parseFloat(objectRotationX->getController()->getValue()->toString());
		auto y = Float::parseFloat(objectRotationY->getController()->getValue()->toString());
		auto z = Float::parseFloat(objectRotationZ->getController()->getValue()->toString());
		if (x < -360.0f || x > 360.0f)
			throw _ExceptionBase("x axis rotation must be within -360 .. +360");

		if (y < -360.0f || y > 360.0f)
			throw _ExceptionBase("y axis rotation must be within -360 .. +360");

		if (z < -360.0f || z > 360.0f)
			throw _ExceptionBase("z axis rotation must be within -360 .. +360");

		view->objectRotationsApply(x, y, z);
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(exception.what()));
	}
}

void LevelEditorScreenController::onObjectRemove()
{
	view->removeObject();
}

void LevelEditorScreenController::onObjectColor()
{
	view->colorObject();
}

void LevelEditorScreenController::onObjectCenter()
{
	view->centerObject();
}

void LevelEditorScreenController::onMapLoad()
{
	view->getPopUps()->getFileDialogScreenController()->show(
		mapPath->getPath(),
		L"Load from: ",
		new StringArray({
			u"tl"_j,
			u"dae"_j
		}),
		view->getFileName(),
		new LevelEditorScreenController_onMapLoad_1(this)
	);
}

void LevelEditorScreenController::onMapSave()
{
	view->getPopUps()->getFileDialogScreenController()->show(
		mapPath->getPath(),
		L"Save to: ",
		new StringArray({u"tl"_j}),
		view->getFileName(),
		new LevelEditorScreenController_onMapSave_2(this)
	);
}

void LevelEditorScreenController::onGridApply()
{
	try {
		auto gridY = Float::parseFloat(gridYPosition->getController()->getValue()->toString());
		if (gridY < -5.0f || gridY > 5.0f)
			throw _ExceptionBase("grid y position must be within -5 .. +5");

		view->setGridY(gridY);
		view->setGridEnabled(gridEnabled->getController()->getValue()->equals(CHECKBOX_CHECKED));
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(exception.what()));
	}
}

void LevelEditorScreenController::onObjectPropertyPresetApply()
{
	view->objectPropertiesPreset(objectPropertiesPresets->getController()->getValue()->toString()->getCPPWString());
}

void LevelEditorScreenController::setLightPresetsIds(const map<wstring, LevelEditorLight*>* lightPresetIds)
{
	for (auto i = 0; i < 4; i++) {
		auto lightPresetsInnerNode = dynamic_cast< GUIParentNode* >(((*lightsPresets)[i]->getScreenNode()->getNodeById(::java::lang::StringBuilder().append((*lightsPresets)[i]->getId())->append(u"_inner"_j)->toString())));
		auto idx = 0;
		auto lightPresetsInnerNodeSubNodesXML = u""_j;
		lightPresetsInnerNodeSubNodesXML = ::java::lang::StringBuilder(lightPresetsInnerNodeSubNodesXML).append(::java::lang::StringBuilder().append(u"<scrollarea-vertical id=\""_j)->append((*lightsPresets)[i]->getId())
			->append(u"_inner_scrollarea\" width=\"100%\" height=\"50\">\n"_j)->toString())->toString();
		for (auto it: *lightPresetIds) {
			wstring lightPresetId = it.first;
			lightPresetsInnerNodeSubNodesXML = ::java::lang::StringBuilder(lightPresetsInnerNodeSubNodesXML).append(::java::lang::StringBuilder().append(u"<dropdown-option text=\""_j)->append(GUIParser::escapeQuotes(lightPresetId))
				->append(u"\" value=\""_j)
				->append(GUIParser::escapeQuotes(lightPresetId))
				->append(u"\" "_j)
				->append((idx == 0 ? u"selected=\"true\" "_j : u""_j))
				->append(u" />\n"_j)->toString())->toString();
			idx++;
		}
		lightPresetsInnerNodeSubNodesXML = ::java::lang::StringBuilder(lightPresetsInnerNodeSubNodesXML).append(u"</scrollarea-vertical>\n"_j)->toString();
		try {
			lightPresetsInnerNode->replaceSubNodes(lightPresetsInnerNodeSubNodesXML, true);
		} catch (_Exception& exception) {
			_Console::print(string("LevelEditorScreenController::setLightPresetsIds(): An error occurred: "));
			_Console::println(string(exception.what()));
		}
	}
}

void LevelEditorScreenController::unselectLightPresets()
{
}

void LevelEditorScreenController::setLight(int32_t i, Color4* ambient, Color4* diffuse, Color4* specular, Vector4* position, float constAttenuation, float linearAttenuation, float quadraticAttenuation, Vector3* spotTo, Vector3* spotDirection, float spotExponent, float spotCutoff, bool enabled)
{
	(*lightsAmbient)[i]->getController()->setValue(value->reset()->append(Tools::formatFloat(ambient->getRed()))->append(u", "_j)->append(Tools::formatFloat(ambient->getGreen()))->append(u", "_j)->append(Tools::formatFloat(ambient->getBlue()))->append(u", "_j)->append(Tools::formatFloat(ambient->getAlpha())));
	(*lightsDiffuse)[i]->getController()->setValue(value->reset()->append(Tools::formatFloat(diffuse->getRed()))->append(u", "_j)->append(Tools::formatFloat(diffuse->getGreen()))->append(u", "_j)->append(Tools::formatFloat(diffuse->getBlue()))->append(u", "_j)->append(Tools::formatFloat(diffuse->getAlpha())));
	(*lightsSpecular)[i]->getController()->setValue(value->reset()->append(Tools::formatFloat(specular->getRed()))->append(u", "_j)->append(Tools::formatFloat(specular->getGreen()))->append(u", "_j)->append(Tools::formatFloat(specular->getBlue()))->append(u", "_j)->append(Tools::formatFloat(specular->getAlpha())));
	(*lightsPosition)[i]->getController()->setValue(value->reset()->append(Tools::formatFloat(position->getX()))->append(u", "_j)->append(Tools::formatFloat(position->getY()))->append(u", "_j)->append(Tools::formatFloat(position->getZ()))->append(u", "_j)->append(Tools::formatFloat(position->getW())));
	(*lightsConstAttenuation)[i]->getController()->setValue(value->set(Tools::formatFloat(constAttenuation)));
	(*lightsLinAttenuation)[i]->getController()->setValue(value->set(Tools::formatFloat(linearAttenuation)));
	(*lightsQuadAttenuation)[i]->getController()->setValue(value->set(Tools::formatFloat(quadraticAttenuation)));
	(*lightsSpotTo)[i]->getController()->setValue(value->reset()->append(Tools::formatFloat(spotTo->getX()))->append(u", "_j)->append(Tools::formatFloat(spotTo->getY()))->append(u", "_j)->append(Tools::formatFloat(spotTo->getZ())));
	(*lightsSpotDirection)[i]->getController()->setValue(value->reset()->append(Tools::formatFloat(spotDirection->getX()))->append(u", "_j)->append(Tools::formatFloat(spotDirection->getY()))->append(u", "_j)->append(Tools::formatFloat(spotDirection->getZ())));
	(*lightsSpotExponent)[i]->getController()->setValue(value->set(Tools::formatFloat(spotExponent)));
	(*lightsSpotCutoff)[i]->getController()->setValue(value->set(Tools::formatFloat(spotCutoff)));
	(*lightsEnabled)[i]->getController()->setValue(enabled == true ? CHECKBOX_CHECKED : CHECKBOX_UNCHECKED);
	(*lightsAmbient)[i]->getController()->setDisabled(enabled == false);
	(*lightsDiffuse)[i]->getController()->setDisabled(enabled == false);
	(*lightsSpecular)[i]->getController()->setDisabled(enabled == false);
	(*lightsPosition)[i]->getController()->setDisabled(enabled == false);
	(*lightsConstAttenuation)[i]->getController()->setDisabled(enabled == false);
	(*lightsLinAttenuation)[i]->getController()->setDisabled(enabled == false);
	(*lightsQuadAttenuation)[i]->getController()->setDisabled(enabled == false);
	(*lightsSpotTo)[i]->getController()->setDisabled(enabled == false);
	(*lightsSpotDirection)[i]->getController()->setDisabled(enabled == false);
	(*lightsSpotExponent)[i]->getController()->setDisabled(enabled == false);
	(*lightsSpotCutoff)[i]->getController()->setDisabled(enabled == false);
	(*ligthsSpotDirectionCompute)[i]->getController()->setDisabled(enabled == false);
}

void LevelEditorScreenController::onLight0Apply()
{
	onLightApply(0);
}

void LevelEditorScreenController::onLight1Apply()
{
	onLightApply(1);
}

void LevelEditorScreenController::onLight2Apply()
{
	onLightApply(2);
}

void LevelEditorScreenController::onLight3Apply()
{
	onLightApply(3);
}

void LevelEditorScreenController::onLightApply(int32_t lightIdx)
{
	try {
		auto enabled = (*lightsEnabled)[lightIdx]->getController()->getValue()->equals(CHECKBOX_CHECKED);
		view->applyLight(lightIdx, Tools::convertToColor4((*lightsAmbient)[lightIdx]->getController()->getValue()->toString()), Tools::convertToColor4((*lightsDiffuse)[lightIdx]->getController()->getValue()->toString()), Tools::convertToColor4((*lightsSpecular)[lightIdx]->getController()->getValue()->toString()), Tools::convertToVector4((*lightsPosition)[lightIdx]->getController()->getValue()->toString()), Tools::convertToFloat((*lightsConstAttenuation)[lightIdx]->getController()->getValue()->toString()), Tools::convertToFloat((*lightsLinAttenuation)[lightIdx]->getController()->getValue()->toString()), Tools::convertToFloat((*lightsQuadAttenuation)[lightIdx]->getController()->getValue()->toString()), Tools::convertToVector3((*lightsSpotTo)[lightIdx]->getController()->getValue()->toString()), Tools::convertToVector3((*lightsSpotDirection)[lightIdx]->getController()->getValue()->toString()), Tools::convertToFloat((*lightsSpotExponent)[lightIdx]->getController()->getValue()->toString()), Tools::convertToFloat((*lightsSpotCutoff)[lightIdx]->getController()->getValue()->toString()), enabled);
		(*lightsAmbient)[lightIdx]->getController()->setDisabled(enabled == false);
		(*lightsDiffuse)[lightIdx]->getController()->setDisabled(enabled == false);
		(*lightsSpecular)[lightIdx]->getController()->setDisabled(enabled == false);
		(*lightsPosition)[lightIdx]->getController()->setDisabled(enabled == false);
		(*lightsConstAttenuation)[lightIdx]->getController()->setDisabled(enabled == false);
		(*lightsLinAttenuation)[lightIdx]->getController()->setDisabled(enabled == false);
		(*lightsQuadAttenuation)[lightIdx]->getController()->setDisabled(enabled == false);
		(*lightsSpotTo)[lightIdx]->getController()->setDisabled(enabled == false);
		(*lightsSpotDirection)[lightIdx]->getController()->setDisabled(enabled == false);
		(*lightsSpotExponent)[lightIdx]->getController()->setDisabled(enabled == false);
		(*lightsSpotCutoff)[lightIdx]->getController()->setDisabled(enabled == false);
		(*ligthsSpotDirectionCompute)[lightIdx]->getController()->setDisabled(enabled == false);
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(exception.what()));
	}
}

void LevelEditorScreenController::onLight0PresetApply()
{
	onLightPresetApply(0);
}

void LevelEditorScreenController::onLight1PresetApply()
{
	onLightPresetApply(1);
}

void LevelEditorScreenController::onLight2PresetApply()
{
	onLightPresetApply(2);
}

void LevelEditorScreenController::onLight3PresetApply()
{
	onLightPresetApply(3);
}

void LevelEditorScreenController::onLightPresetApply(int32_t lightIdx)
{
	auto lightPresets = LevelPropertyPresets::getInstance()->getLightPresets();
	LevelEditorLight* lightPreset = nullptr;
	auto lightPresetIt = lightPresets->find((*lightsPresets)[lightIdx]->getController()->getValue()->toString()->getCPPWString());
	if (lightPresetIt != lightPresets->end()) lightPreset = lightPresetIt->second;
	if (lightPreset == nullptr) return;

	view->applyLight(lightIdx, lightPreset->getAmbient(), lightPreset->getDiffuse(), lightPreset->getSpecular(), lightPreset->getPosition(), lightPreset->getConstantAttenuation(), lightPreset->getLinearAttenuation(), lightPreset->getQuadraticAttenuation(), lightPreset->getSpotTo(), lightPreset->getSpotDirection(), lightPreset->getSpotExponent(), lightPreset->getSpotCutOff(), lightPreset->isEnabled());
}

void LevelEditorScreenController::onLight0SpotDirectionCompute()
{
	onLightSpotDirectionCompute(0);
}

void LevelEditorScreenController::onLight1SpotDirectionCompute()
{
	onLightSpotDirectionCompute(1);
}

void LevelEditorScreenController::onLight2SpotDirectionCompute()
{
	onLightSpotDirectionCompute(2);
}

void LevelEditorScreenController::onLight3SpotDirectionCompute()
{
	onLightSpotDirectionCompute(3);
}

void LevelEditorScreenController::onLightSpotDirectionCompute(int32_t lightIdx)
{
	try {
		view->computeSpotDirection(lightIdx, Tools::convertToVector4((*lightsPosition)[lightIdx]->getController()->getValue()->toString()), Tools::convertToVector3((*lightsSpotTo)[lightIdx]->getController()->getValue()->toString()));
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(exception.what()));
	}
}

void LevelEditorScreenController::saveFile(const wstring& pathName, const wstring& fileName) /* throws(Exception) */
{
	view->saveMap(pathName, fileName);
}

void LevelEditorScreenController::loadFile(const wstring& pathName, const wstring& fileName) /* throws(Exception) */
{
	view->loadMap(pathName, fileName);
}

void LevelEditorScreenController::onValueChanged(GUIElementNode* node)
{
	if (node->getId()->equals(L"objects_listbox") == true) {
	} else
	if (node->getId()->equals(L"map_properties_listbox") == true) {
		onMapPropertiesSelectionChanged();
	} else
	if (node->getId()->equals(L"object_properties_listbox") == true) {
		onObjectPropertiesSelectionChanged();
	} else {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"LevelEditorScreenController::onValueChanged: "_j)->append(node->getId())->toString()));
	}
}

void LevelEditorScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	if (type == GUIActionListener_Type::PERFORMED) {
		if (node->getId()->equals(L"button_objects_select") == true) {
			onObjectsSelect();
		} else
		if (node->getId()->equals(L"button_objects_unselect") == true) {
			onObjectsUnselect();
		} else
		if (node->getId()->equals(L"button_grid_apply") == true) {
			onGridApply();
		} else
		if (node->getId()->equals(L"button_map_load") == true) {
			onMapLoad();
		} else
		if (node->getId()->equals(L"button_map_save") == true) {
			onMapSave();
		} else
		if (node->getId()->equals(L"button_map_properties_add") == true) {
			onMapPropertyAdd();
		} else
		if (node->getId()->equals(L"button_map_properties_remove") == true) {
			onMapPropertyRemove();
		} else
		if (node->getId()->equals(L"button_map_properties_save") == true) {
			onMapPropertySave();
		} else
		if (node->getId()->equals(L"button_objectdata_apply") == true) {
			onObjectDataApply();
		} else
		if (node->getId()->equals(L"button_translation_apply") == true) {
			onObjectTranslationApply();
		} else
		if (node->getId()->equals(L"button_scale_apply") == true) {
			onObjectScaleApply();
		} else
		if (node->getId()->equals(L"button_rotation_apply") == true) {
			onObjectRotationsApply();
		} else
		if (node->getId()->equals(L"button_object_color") == true) {
			onObjectColor();
		} else
		if (node->getId()->equals(L"button_object_center") == true) {
			onObjectCenter();
		} else
		if (node->getId()->equals(L"button_object_remove") == true) {
			onObjectRemove();
		} else
		if (node->getId()->equals(L"button_object_properties_presetapply") == true) {
			onObjectPropertyPresetApply();
		} else
		if (node->getId()->equals(L"button_object_properties_add") == true) {
			onObjectPropertyAdd();
		} else
		if (node->getId()->equals(L"button_object_properties_remove") == true) {
			onObjectPropertyRemove();
		} else
		if (node->getId()->equals(L"button_object_properties_save") == true) {
			onObjectPropertySave();
		} else
		if (node->getId()->equals(L"button_light0_presetapply") == true) {
			onLight0PresetApply();
		} else
		if (node->getId()->equals(L"button_light0_spotdirection_compute") == true) {
			onLight0SpotDirectionCompute();
		} else
		if (node->getId()->equals(L"button_light0_apply") == true) {
			onLight0Apply();
		} else
		if (node->getId()->equals(L"button_light1_presetapply") == true) {
			onLight1PresetApply();
		} else
		if (node->getId()->equals(L"button_light1_spotdirection_compute") == true) {
			onLight1SpotDirectionCompute();
		} else
		if (node->getId()->equals(L"button_light1_apply") == true) {
			onLight1Apply();
		} else
		if (node->getId()->equals(L"button_light2_presetapply") == true) {
			onLight2PresetApply();
		} else
		if (node->getId()->equals(L"button_light2_spotdirection_compute") == true) {
			onLight2SpotDirectionCompute();
		} else
		if (node->getId()->equals(L"button_light2_apply") == true) {
			onLight2Apply();
		} else
		if (node->getId()->equals(L"button_light3_presetapply") == true) {
			onLight3PresetApply();
		} else
		if (node->getId()->equals(L"button_light3_spotdirection_compute") == true) {
			onLight3SpotDirectionCompute();
		} else
		if (node->getId()->equals(L"button_light3_apply") == true) {
			onLight3Apply();
		} else {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"LevelEditorScreenController::onActionPerformed: "_j)->append(node->getId())->toString()));
		}
	}
}

void LevelEditorScreenController::showErrorPopUp(const wstring& caption, const wstring& message)
{
	_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(caption)->append(u":"_j)
		->append(message)->toString()));
	view->getPopUps()->getInfoDialogScreenController()->show(caption, message);
}
