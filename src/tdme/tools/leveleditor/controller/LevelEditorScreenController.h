// Generated from /tdme/src/tdme/tools/leveleditor/controller/LevelEditorScreenController.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/controller/ScreenController.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/utils/_HashMap.h>

using std::map;
using std::wstring;
using std::vector;

using tdme::tools::shared::controller::ScreenController;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIChangeListener;
using java::lang::Iterable;
using java::lang::String;
using java::util::Collection;
using java::util::Iterator;
using tdme::engine::model::Color4;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::leveleditor::views::LevelEditorView;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::model::LevelEditorLight;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::utils::MutableString;
using tdme::utils::_HashMap;
using java::lang::Object;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace gui {
namespace nodes {
typedef ::SubArray< ::tdme::gui::nodes::GUINode, ::java::lang::ObjectArray > GUINodeArray;
typedef ::SubArray< ::tdme::gui::nodes::GUIParentNode, GUINodeArray > GUIParentNodeArray;
typedef ::SubArray< ::tdme::gui::nodes::GUIElementNode, GUIParentNodeArray > GUIElementNodeArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::gui::nodes::GUIElementNodeArray;
using tdme::gui::nodes::GUINodeArray;
using tdme::gui::nodes::GUIParentNodeArray;

struct default_init_tag;

/** 
 * Level Editor Screen Controller
 * @author Andreas Drewke
 * @version $Id: ModelLibraryController.java 82 2013-12-26 13:56:48Z drewke.net $
 */
class tdme::tools::leveleditor::controller::LevelEditorScreenController final
	: public ScreenController
	, public GUIActionListener
	, public GUIChangeListener
{

public:
	typedef ScreenController super;

private:
	static MutableString* CHECKBOX_CHECKED;
	static MutableString* CHECKBOX_UNCHECKED;
	static MutableString* TEXT_EMPTY;
	LevelEditorView* view {  };
	GUIScreenNode* screenNode {  };
	GUITextNode* screenCaption {  };
	GUIElementNode* btnObjectTranslationApply {  };
	GUIElementNode* btnObjectScaleApply {  };
	GUIElementNode* btnObjectRotationApply {  };
	GUIElementNode* btnObjectColor {  };
	GUIElementNode* btnObjectCenter {  };
	GUIElementNode* btnObjectRemove {  };
	GUIElementNode* gridYPosition {  };
	GUIElementNode* gridEnabled {  };
	GUIElementNode* mapWidth {  };
	GUIElementNode* mapDepth {  };
	GUIElementNode* mapHeight {  };
	GUIElementNode* mapPropertyName {  };
	GUIElementNode* mapPropertyValue {  };
	GUIElementNode* mapPropertySave {  };
	GUIElementNode* mapPropertyRemove {  };
	GUIElementNode* mapPropertiesListBox {  };
	GUIElementNode* objectName {  };
	GUIElementNode* objectDescription {  };
	GUIElementNode* objectModel {  };
	GUIElementNode* objectCenter {  };
	GUIElementNode* btnObjectDataApply {  };
	GUIElementNode* objectTranslationX {  };
	GUIElementNode* objectTranslationY {  };
	GUIElementNode* objectTranslationZ {  };
	GUIElementNode* objectScaleX {  };
	GUIElementNode* objectScaleY {  };
	GUIElementNode* objectScaleZ {  };
	GUIElementNode* objectRotationX {  };
	GUIElementNode* objectRotationY {  };
	GUIElementNode* objectRotationZ {  };
	GUIElementNode* objectPropertyName {  };
	GUIElementNode* objectPropertyValue {  };
	GUIElementNode* btnObjectPropertySave {  };
	GUIElementNode* btnObjectPropertyAdd {  };
	GUIElementNode* btnObjectPropertyRemove {  };
	GUIElementNode* btnObjectPropertyPresetApply {  };
	GUIElementNode* objectPropertiesListBox {  };
	GUIElementNode* objectPropertiesPresets {  };
	GUIElementNode* objectsListBox {  };
	GUIElementNodeArray* lightsPresets {  };
	GUIElementNodeArray* lightsAmbient {  };
	GUIElementNodeArray* lightsDiffuse {  };
	GUIElementNodeArray* lightsSpecular {  };
	GUIElementNodeArray* lightsPosition {  };
	GUIElementNodeArray* lightsLinAttenuation {  };
	GUIElementNodeArray* lightsConstAttenuation {  };
	GUIElementNodeArray* lightsQuadAttenuation {  };
	GUIElementNodeArray* lightsSpotTo {  };
	GUIElementNodeArray* lightsSpotDirection {  };
	GUIElementNodeArray* lightsSpotExponent {  };
	GUIElementNodeArray* lightsSpotCutoff {  };
	GUIElementNodeArray* ligthsSpotDirectionCompute {  };
	GUIElementNodeArray* lightsEnabled {  };
	MutableString* value {  };
	MutableString* selectedObjects {  };
	FileDialogPath* mapPath {  };
protected:

	/** 
	 * Public constructor
	 * @param view
	 */
	void ctor(LevelEditorView* view);

public:
	GUIScreenNode* getScreenNode() override;

	/** 
	 * @return map path
	 */
	FileDialogPath* getMapPath();
	void initialize() override;
	void dispose() override;

	/** 
	 * Set up screen caption
	 * @param text
	 */
	void setScreenCaption(String* text);

	/** 
	 * Set grid
	 * @param enabled
	 * @param grid y position
	 */
	void setGrid(bool enabled, float gridY);

	/** 
	 * Set up level size
	 * @param width
	 * @param height
	 */
	void setLevelSize(float width, float depth, float height);

	/** 
	 * Unset object properties
	 */
	void unsetObjectProperties();

	/** 
	 * @return object property preset selection
	 */
	String* getObjectPropertyPresetSelection();

	/** 
	 * Set up general object data
	 * @param name
	 * @param description
	 * @param model name
	 * @param center
	 */
	void setObjectData(String* name, String* description, String* modelName, Vector3* center);

	/** 
	 * Unset model data
	 */
	void unsetObjectData();

	/** 
	 * On object data apply
	 */
	void onObjectDataApply();

	/** 
	 * Set up object list box
	 * @param object by ids hash map
	 */
	void setObjectListbox(_HashMap* objectsByIds);

	/** 
	 * Unselect objects in object list box
	 */
	void unselectObjectInObjectListBox(String* objectId);

	/** 
	 * Unselect objects in object list box
	 */
	void unselectObjectsInObjectListBox();

	/** 
	 * Select a object in object list box
	 * @param object id
	 */
	void selectObjectInObjectListbox(String* objectId);

	/** 
	 * On objects select button click event
	 */
	void onObjectsSelect();

	/** 
	 * On objects unselect button click event
	 */
	void onObjectsUnselect();

	/** 
	 * Set up object
	 * @param translation
	 * @param scale
	 * @param rotation x
	 * @param rotation y
	 * @param rotation z
	 */
	void setObject(Vector3* translation, Vector3* scale, float rotationX, float rotationY, float rotationZ);

	/** 
	 * Unset current object
	 */
	void unsetObject();

	/** 
	 * Event callback for map properties selection
	 * @param id
	 * @param event
	 */
	void onMapPropertiesSelectionChanged();

	/** 
	 * Set up map properties
	 * @param map properties
	 */
	void setMapProperties(Iterable* mapProperties, String* selectedName);

	/** 
	 * On map property save
	 */
	void onMapPropertySave();

	/** 
	 * On model property add
	 */
	void onMapPropertyAdd();

	/** 
	 * On model property remove
	 */
	void onMapPropertyRemove();

	/** 
	 * Set up object property preset ids
	 * @param object property preset ids
	 */
	void setObjectPresetIds(const map<wstring, vector<PropertyModelClass*>>* objectPresetIds);

	/** 
	 * Event callback for object properties selection
	 * @param id
	 * @param event
	 */
	void onObjectPropertiesSelectionChanged();

	/** 
	 * Set up object properties
	 * @param preset id
	 * @param object properties
	 * @param selected name
	 */
	void setObjectProperties(String* presetId, Iterable* objectProperties, String* selectedName);

	/** 
	 * On object property save
	 */
	void onObjectPropertySave();

	/** 
	 * On object property add
	 */
	void onObjectPropertyAdd();

	/** 
	 * On object property remove
	 */
	void onObjectPropertyRemove();

	/** 
	 * On quit action
	 */
	void onQuit();

	/** 
	 * On object translation apply action
	 */
	void onObjectTranslationApply();

	/** 
	 * On object scale apply action
	 */
	void onObjectScaleApply();

	/** 
	 * On object rotations apply action
	 */
	void onObjectRotationsApply();

	/** 
	 * On object remove action
	 */
	void onObjectRemove();

	/** 
	 * On object color action
	 */
	void onObjectColor();

	/** 
	 * On object center action
	 */
	void onObjectCenter();

	/** 
	 * On map load action
	 */
	void onMapLoad();

	/** 
	 * On map save action
	 */
	void onMapSave();

	/** 
	 * On grid apply button
	 */
	void onGridApply();

	/** 
	 * On object property preset apply 
	 */
	void onObjectPropertyPresetApply();

	/** 
	 * Set up light presets
	 * @param light presets
	 */
	void setLightPresetsIds(const map<wstring, LevelEditorLight*>* lightPresetIds);

	/** 
	 * Unselect light presets
	 */
	void unselectLightPresets();

	/** 
	 * Set up light indexed by i
	 * @param i
	 * @param ambient
	 * @param diffuse
	 * @param specular
	 * @param position
	 * @param const attenuation
	 * @param linear attenuation
	 * @param quadratic attenuation
	 * @param spot to
	 * @param spot direction
	 * @param spot exponent
	 * @param spot cutoff
	 * @param enabled
	 */
	void setLight(int32_t i, Color4* ambient, Color4* diffuse, Color4* specular, Vector4* position, float constAttenuation, float linearAttenuation, float quadraticAttenuation, Vector3* spotTo, Vector3* spotDirection, float spotExponent, float spotCutoff, bool enabled);

	/** 
	 * On light 0 apply
	 */
	void onLight0Apply();

	/** 
	 * On light 1 apply
	 */
	void onLight1Apply();

	/** 
	 * On light 2 apply
	 */
	void onLight2Apply();

	/** 
	 * On light 3 apply
	 */
	void onLight3Apply();

	/** 
	 * On light 3 apply
	 * @param light idx
	 */
	void onLightApply(int32_t lightIdx);

	/** 
	 * On light 0 preset apply
	 */
	void onLight0PresetApply();

	/** 
	 * On light 1 preset apply
	 */
	void onLight1PresetApply();

	/** 
	 * On light 2 preset apply
	 */
	void onLight2PresetApply();

	/** 
	 * On light 3 preset apply
	 */
	void onLight3PresetApply();

	/** 
	 * On light preset apply for light
	 * @param i
	 */
	void onLightPresetApply(int32_t lightIdx);

	/** 
	 * On Light 0 spot direction compute 
	 */
	void onLight0SpotDirectionCompute();

	/** 
	 * On Light 1 spot direction compute 
	 */
	void onLight1SpotDirectionCompute();

	/** 
	 * On Light 2 spot direction compute 
	 */
	void onLight2SpotDirectionCompute();

	/** 
	 * On Light 3 spot direction compute 
	 */
	void onLight3SpotDirectionCompute();

	/** 
	 * On Light spot direction compute for given light idx 
	 */
	void onLightSpotDirectionCompute(int32_t lightIdx);
	void saveFile(String* pathName, String* fileName) /* throws(Exception) */;
	void loadFile(String* pathName, String* fileName) /* throws(Exception) */;
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	/** 
	 * Shows the error pop up
	 */
	void showErrorPopUp(String* caption, String* message);

	// Generated
	LevelEditorScreenController(LevelEditorView* view);
protected:
	LevelEditorScreenController(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
	friend class LevelEditorScreenController_onMapLoad_1;
	friend class LevelEditorScreenController_onMapSave_2;
};
