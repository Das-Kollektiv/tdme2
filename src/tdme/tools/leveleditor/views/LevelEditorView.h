// Generated from /tdme/src/tdme/tools/leveleditor/views/LevelEditorView.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/_HashMap.h>
#include <java/lang/Object.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/gui/events/GUIInputEventHandler.h>

using std::vector;

using java::lang::Object;
using tdme::tools::shared::views::View;
using tdme::gui::events::GUIInputEventHandler;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityPickingFilter;
using tdme::engine::Rotation;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::leveleditor::controller::LevelEditorScreenController;
using tdme::tools::leveleditor::views::LevelEditorView_ObjectColor;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::tools::shared::views::PopUps;
using tdme::utils::_HashMap;

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

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

struct default_init_tag;

/** 
 * TDME Level Editor View
 * @author andreas.drewke
 * @version $Id: 04313d20d0978eefc881024d6e0af748196c1425 $
 */
class tdme::tools::leveleditor::views::LevelEditorView final
	: public virtual Object
	, public View
	, public GUIInputEventHandler
{

public:
	typedef Object super;

private:
	static StringArray* OBJECTCOLOR_NAMES;
	static constexpr int32_t MOUSE_BUTTON_NONE { 0 };
	static constexpr int32_t MOUSE_BUTTON_LEFT { 1 };
	static constexpr int32_t MOUSE_BUTTON_MIDDLE { 2 };
	static constexpr int32_t MOUSE_BUTTON_RIGHT { 3 };
	static constexpr int32_t MOUSE_DOWN_LAST_POSITION_NONE { -1 };
	static constexpr int32_t MOUSE_PANNING_NONE { 0 };
	static constexpr int32_t MOUSE_ROTATION_NONE { 0 };
	int32_t GRID_DIMENSION_X {  };
	int32_t GRID_DIMENSION_Y {  };
	LevelEditorScreenController* levelEditorScreenController {  };
	Engine* engine {  };
	LevelEditorEntity* selectedEntity {  };
	bool reloadEntityLibrary {  };
	_HashMap* objectColors {  };
	Rotation* camLookRotationX {  };
	Rotation* camLookRotationY {  };
	float camScale {  };
	float camScaleMax {  };
	float camScaleMin {  };
	Vector3* FORWARD_VECTOR {  };
	Vector3* SIDE_VECTOR {  };
	Vector3* camForwardVector {  };
	Vector3* camSideVector {  };
	Vector3* camLookAtToFromVector {  };
	Vector3* camLookAt {  };
	int32_t mouseDownLastX {  };
	int32_t mouseDownLastY {  };
	bool mouseDragging {  };
	Entity* mouseDraggingLastObject {  };
	int32_t mousePanningSide {  };
	int32_t mousePanningForward {  };
	int32_t mouseRotationX {  };
	int32_t mouseRotationY {  };
	Vector3* gridCenter {  };
	Vector3* gridCenterLast {  };
	bool gridEnabled {  };
	float gridY {  };
	bool keyLeft {  };
	bool keyRight {  };
	bool keyUp {  };
	bool keyDown {  };
	bool keyA {  };
	bool keyD {  };
	bool keyW {  };
	bool keyS {  };
	bool keyC {  };
	bool keyV {  };
	bool keyX {  };
	bool keyDelete {  };
	bool keyPlus {  };
	bool keyMinus {  };
	bool keyR {  };
	bool keyControl {  };
	bool keyEscape {  };

public: /* package */
	float groundPlateWidth {  };
	float groundPlateDepth {  };

private:
	Model* levelEditorGround {  };
	LevelEditorLevel* level {  };
	vector<Entity*> selectedObjects {  };
	_HashMap* selectedObjectsById {  };
	vector<LevelEditorObject*> pasteObjects_ {  };
	PopUps* popUps {  };
	EntityPickingFilter* entityPickingFilterNoGrid {  };
	Vector3* tmpVector3 {  };
protected:

	/** 
	 * Public constructor
	 * @param pop ups 
	 */
	void ctor(PopUps* popUps);

public:

	/** 
	 * @return pop ups
	 */
	PopUps* getPopUps();

	/** 
	 * @return level file name
	 */
	String* getFileName();

	/** 
	 * @return level
	 */
	LevelEditorLevel* getLevel();

	/** 
	 * @return selected entity
	 */
	LevelEditorEntity* getSelectedEntity();

	/** 
	 * @return selected level editor object
	 */
	LevelEditorObject* getSelectedObject();

	/** 
	 * @return grid enabled
	 */
	bool isGridEnabled();

	/** 
	 * @param grid enabled
	 */
	void setGridEnabled(bool gridEnabled);

	/** 
	 * @return grid y
	 */
	float getGridY();

	/** 
	 * Set grid y position 
	 * @param grid y
	 */
	void setGridY(float gridY);

	/** 
	 * Load selected entity from library
	 * @param id
	 */
	void loadEntityFromLibrary(int32_t id);
	void handleInputEvents() override;

	/** 
	 * Renders the scene 
	 */
	void display() override;

	/** 
	 * Select objects
	 * @param object ids
	 */
	void selectObjects(vector<String*>& objectIds);

	/** 
	 * Select objects by id
	 * @param id
	 */
	void unselectObjects();

private:

	/** 
	 * Update GUI elements
	 * screen caption
	 * level size
	 * selected object
	 * object properties
	 * object 3d transformations
	 * object data  
	 */
	void updateGUIElements();

public:

	/** 
	 * Updates objects list box
	 */
	void setObjectsListBox();

	/** 
	 * Unselect light presets
	 */
	void unselectLightPresets();

private:

	/** 
	 * Load settings
	 */
	void loadSettings();

public:
	void initialize() override;
	void activate() override;
	void deactivate() override;

private:

	/** 
	 * Store settings
	 */
	void storeSettings();

public:
	void dispose() override;

private:

	/** 
	 * Set highlight object color effect
	 * @param object
	 */
	void setHighlightObjectColorEffect(Entity* object);

	/** 
	 * Set standard object color effect
	 * @param object
	 */
	void setStandardObjectColorEffect(Entity* object);

public:

	/** 
	 * Loads a level from internal level representation to tdme
	 */
	void loadLevel();

private:

	/** 
	 * Update dynamic grid
	 */
	void updateGrid();

	/** 
	 * Remove grid
	 */
	void removeGrid();

	/** 
	 * Creates a level editor ground plate
	 * @return ground
	 */
	Model* createLevelEditorGroundPlateModel();

public:

	/** 
	 * On object data apply
	 * @param name
	 * @param description
	 */
	bool objectDataApply(String* name, String* description);

	/** 
	 * Places selected model on selected object
	 */
	void placeObject();

	/** 
	 * Places selected model on given object
	 */
	void placeObject(Entity* selectedObject);

	/** 
	 * Removes selected object
	 */
	void removeObject();

	/** 
	 * Centers selected objects
	 */
	void colorObject();

	/** 
	 * Centers selected objects
	 */
	void centerObject();

	/** 
	 * Apply object translation
	 * @param x
	 * @param y
	 * @param z
	 */
	void objectTranslationApply(float x, float y, float z);

	/** 
	 * Apply object scale
	 * @param x
	 * @param y
	 * @param z
	 */
	void objectScaleApply(float x, float y, float z);

	/** 
	 * Apply object rotations
	 * @param x
	 * @param y
	 * @param z
	 */
	void objectRotationsApply(float x, float y, float z);

	/** 
	 * Save a map property
	 * @param old name
	 * @param name
	 * @param value
	 * @return success
	 */
	bool mapPropertySave(String* oldName, String* name, String* value);

	/** 
	 * Add a map property
	 * @return success
	 */
	bool mapPropertyAdd();

	/** 
	 * Remove a map property from model properties
	 * @param name
	 * @return success
	 */
	bool mapPropertyRemove(String* name);

	/** 
	 * Remove a object property from object properties
	 * @param name
	 * @return success
	 */
	bool objectPropertyRemove(String* name);

	/** 
	 * Apply object property preset
	 * @param preset id
	 */
	void objectPropertiesPreset(String* presetId);

	/** 
	 * Save a model property
	 * @param old name
	 * @param name
	 * @param value
	 * @return success
	 */
	bool objectPropertySave(String* oldName, String* name, String* value);

	/** 
	 * Add a model property
	 * @return success
	 */
	bool objectPropertyAdd();

	/** 
	 * Triggers loading a map
	 */
	void loadMap(String* path, String* file);

	/** 
	 * Triggers saving a map
	 */
	void saveMap(String* pathName, String* fileName);

private:

	/** 
	 * Copy current selected objects
	 */
	void copyObjects();

	/** 
	 * Paste objects
	 */
	void pasteObjects();

public:

	/** 
	 * Compute spot direction
	 * @param i
	 */
	void computeSpotDirection(int32_t i, Vector4* position, Vector3* spotTo);

	/** 
	 * Apply light with index i
	 * @param i
	 * @param ambient
	 * @param diffuse
	 * @param position
	 * @param constant attenuation
	 * @param linear attenuation
	 * @param quadratic attenuation
	 * @param spot to
	 * @param spot direction
	 * @param spot exponent
	 * @param spot cutoff
	 * @param enabled
	 */
	void applyLight(int32_t i, Color4* ambient, Color4* diffuse, Color4* specular, Vector4* position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, Vector3* spotTo, Vector3* spotDirection, float spotExponent, float spotCutoff, bool enabled);

	// Generated
	LevelEditorView(PopUps* popUps);
protected:
	LevelEditorView(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
	friend class LevelEditorView_ObjectColor;
	friend class LevelEditorView_LevelEditorView_1;
};
