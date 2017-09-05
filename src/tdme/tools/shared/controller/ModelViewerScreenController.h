// Generated from /tdme/src/tdme/tools/shared/controller/ModelViewerScreenController.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/controller/ScreenController.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>

using std::wstring;

using tdme::tools::shared::controller::ScreenController;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIChangeListener;
using java::lang::Iterable;
using java::lang::String;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::math::Vector3;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::SharedModelViewerView;
using tdme::utils::MutableString;

/** 
 * Model viewer screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::ModelViewerScreenController final
	: public ScreenController
	, public GUIActionListener
	, public GUIChangeListener
{
	friend class ModelViewerScreenController_ModelViewerScreenController_1;
	friend class ModelViewerScreenController_onModelLoad_2;
	friend class ModelViewerScreenController_onModelSave_3;

private:
	static MutableString* TEXT_EMPTY;
	EntityBaseSubScreenController* entityBaseSubScreenController {  };
	EntityDisplaySubScreenController* entityDisplaySubScreenController {  };
	EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController {  };
	SharedModelViewerView* view {  };
	GUIScreenNode* screenNode {  };
	GUITextNode* screenCaption {  };
	GUIElementNode* modelReload {  };
	GUIElementNode* modelSave {  };
	GUIElementNode* pivotX {  };
	GUIElementNode* pivotY {  };
	GUIElementNode* pivotZ {  };
	GUIElementNode* pivotApply {  };
	GUIElementNode* statsOpaqueFaces {  };
	GUIElementNode* statsTransparentFaces {  };
	GUIElementNode* statsMaterialCount {  };
	MutableString* value {  };
	FileDialogPath* modelPath {  };

public:

	/** 
	 * @return entity display sub screen controller
	 */
	EntityDisplaySubScreenController* getEntityDisplaySubScreenController();

	/** 
	 * @return entity bounding volume sub screen controller
	 */
	EntityBoundingVolumeSubScreenController* getEntityBoundingVolumeSubScreenController();
	GUIScreenNode* getScreenNode() override;

	/** 
	 * @return model path
	 */
	FileDialogPath* getModelPath();
	void initialize() override;
	void dispose() override;

	/** 
	 * Set screen caption
	 * @param text
	 */
	void setScreenCaption(String* text);

	/** 
	 * Set up general entity data
	 * @param name
	 * @param description
	 */
	void setEntityData(const wstring& name, const wstring& description);

	/** 
	 * Unset entity data
	 */
	void unsetEntityData();

	/** 
	 * Set up entity properties
	 * @param preset id
	 * @param entity properties
	 * @param selected name
	 */
	void setEntityProperties(String* presetId, LevelEditorEntity* entity, String* selectedName);

	/** 
	 * Unset entity properties
	 */
	void unsetEntityProperties();

	/** 
	 * Set pivot tab
	 * @param pivot
	 */
	void setPivot(Vector3* pivot);

	/** 
	 * Unset pivot tab
	 */
	void unsetPivot();

	/** 
	 * Set up model statistics
	 * @param stats opaque faces
	 * @param stats transparent faces
	 * @param stats material count
	 */
	void setStatistics(int32_t statsOpaqueFaces, int32_t statsTransparentFaces, int32_t statsMaterialCount);

	/** 
	 * On quit
	 */
	void onQuit();

	/** 
	 * On model load
	 */
	void onModelLoad();

	/** 
	 * On model save
	 */
	void onModelSave();

	/** 
	 * On model reload
	 */
	void onModelReload();

	/** 
	 * On pivot apply
	 */
	void onPivotApply();
	void saveFile(String* pathName, String* fileName) /* throws(Exception) */;
	void loadFile(String* pathName, String* fileName) /* throws(Exception) */;

	/** 
	 * Shows the error pop up
	 */
	void showErrorPopUp(String* caption, String* message);
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	/**
	 * Public constructor
	 * @param view
	 */
	ModelViewerScreenController(SharedModelViewerView* view);
};
