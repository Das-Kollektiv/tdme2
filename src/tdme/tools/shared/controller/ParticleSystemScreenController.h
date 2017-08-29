// Generated from /tdme/src/tdme/tools/shared/controller/ParticleSystemScreenController.java

#pragma once

#include <vector>

#include <java/lang/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/controller/ScreenController.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>

using std::vector;

using tdme::tools::shared::controller::ScreenController;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIChangeListener;
using java::lang::Iterable;
using java::lang::String;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::SharedParticleSystemView;
using tdme::utils::MutableString;

/** 
 * Model viewer screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::ParticleSystemScreenController final
	: public ScreenController
	, public GUIActionListener
	, public GUIChangeListener
{
	friend class ParticleSystemScreenController_ParticleSystemScreenController_1;
	friend class ParticleSystemScreenController_onParticleSystemLoad_2;
	friend class ParticleSystemScreenController_onEntitySave_3;
	friend class ParticleSystemScreenController_onActionPerformed_4;

private:
	static String* TYPE_NONE;
	static String* TYPE_OBJECTPARTICLESYSTEM;
	static String* TYPE_POINTSPARTICLESYSTEM;
	static String* EMITTER_NONE;
	static String* EMITTER_POINTPARTICLEEMITTER;
	static String* EMITTER_BOUNDINGBOXPARTICLEEMITTER;
	static String* EMITTER_CIRCLEPARTICLEEMITTER;
	static String* EMITTER_CIRCLEPARTICLEEMITTERPLANEVELOCITY;
	static String* EMITTER_SPHEREPARTICLEEMITTER;
	EntityBaseSubScreenController* entityBaseSubScreenController {  };
	EntityDisplaySubScreenController* entityDisplaySubScreenController {  };
	EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController {  };
	SharedParticleSystemView* view {  };
	GUIScreenNode* screenNode {  };
	GUITextNode* screenCaption {  };
	GUIElementNode* particleSystemReload {  };
	GUIElementNode* particleSystemSave {  };
	GUIElementNode* particleSystemTypes {  };
	GUIElementNode* particleSystemType {  };
	GUIElementNode* particleSystemEmitters {  };
	GUIElementNode* particleSystemEmitter {  };
	GUIElementNode* opsScale {  };
	GUIElementNode* opsMaxCount {  };
	GUIElementNode* opsModel {  };
	GUIElementNode* opsAutoEmit {  };
	GUIElementNode* ppsAutoEmit {  };
	GUIElementNode* ppsMaxPoints {  };
	GUIElementNode* ppeCount {  };
	GUIElementNode* ppeLifeTime {  };
	GUIElementNode* ppeLifeTimeRnd {  };
	GUIElementNode* ppeMass {  };
	GUIElementNode* ppeMassRnd {  };
	GUIElementNode* ppePosition {  };
	GUIElementNode* ppeVelocity {  };
	GUIElementNode* ppeVelocityRnd {  };
	GUIElementNode* ppeColorStart {  };
	GUIElementNode* ppeColorEnd {  };
	GUIElementNode* bbpeCount {  };
	GUIElementNode* bbpeLifeTime {  };
	GUIElementNode* bbpeLifeTimeRnd {  };
	GUIElementNode* bbpeMass {  };
	GUIElementNode* bbpeMassRnd {  };
	GUIElementNode* bbpeVelocity {  };
	GUIElementNode* bbpeVelocityRnd {  };
	GUIElementNode* bbpeColorStart {  };
	GUIElementNode* bbpeColorEnd {  };
	GUIElementNode* bbpeObbCenter {  };
	GUIElementNode* bbpeObbHalfextension {  };
	GUIElementNode* bbpeObbRotationX {  };
	GUIElementNode* bbpeObbRotationY {  };
	GUIElementNode* bbpeObbRotationZ {  };
	GUIElementNode* cpeCount {  };
	GUIElementNode* cpeLifeTime {  };
	GUIElementNode* cpeLifeTimeRnd {  };
	GUIElementNode* cpeMass {  };
	GUIElementNode* cpeMassRnd {  };
	GUIElementNode* cpeVelocity {  };
	GUIElementNode* cpeVelocityRnd {  };
	GUIElementNode* cpeColorStart {  };
	GUIElementNode* cpeColorEnd {  };
	GUIElementNode* cpeCenter {  };
	GUIElementNode* cpeRadius {  };
	GUIElementNode* cpeRotationX {  };
	GUIElementNode* cpeRotationY {  };
	GUIElementNode* cpeRotationZ {  };
	GUIElementNode* cpepvCount {  };
	GUIElementNode* cpepvLifeTime {  };
	GUIElementNode* cpepvLifeTimeRnd {  };
	GUIElementNode* cpepvMass {  };
	GUIElementNode* cpepvMassRnd {  };
	GUIElementNode* cpepvVelocity {  };
	GUIElementNode* cpepvVelocityRnd {  };
	GUIElementNode* cpepvColorStart {  };
	GUIElementNode* cpepvColorEnd {  };
	GUIElementNode* cpepvCenter {  };
	GUIElementNode* cpepvRadius {  };
	GUIElementNode* cpepvRotationX {  };
	GUIElementNode* cpepvRotationY {  };
	GUIElementNode* cpepvRotationZ {  };
	GUIElementNode* speCount {  };
	GUIElementNode* speLifeTime {  };
	GUIElementNode* speLifeTimeRnd {  };
	GUIElementNode* speMass {  };
	GUIElementNode* speMassRnd {  };
	GUIElementNode* speVelocity {  };
	GUIElementNode* speVelocityRnd {  };
	GUIElementNode* speColorStart {  };
	GUIElementNode* speColorEnd {  };
	GUIElementNode* speCenter {  };
	GUIElementNode* speRadius {  };
	MutableString* value {  };
	FileDialogPath* particleSystemPath {  };
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
	 * @return particle system path
	 */
	FileDialogPath* getParticleSystemPath();

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
	void setEntityData(String* name, String* description);

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
	 * Set up particle system types
	 * @param particle system types
	 */
	void setParticleSystemTypes(const vector<String*>* particleSystemTypesCollection);

	/** 
	 * Set up emitters
	 * @param emitters
	 */
	void setParticleSystemEmitters(const vector<String*>* emittersCollection);

	/** 
	 * On quit
	 */
	void onQuit();

	/** 
	 * Set particle system type
	 */
	void setParticleSystemType();

	/** 
	 * Set particle system type
	 */
	void onParticleSystemTypeDataApply();

	/** 
	 * On particle system type apply
	 */
	void onParticleSystemTypeApply();

	/** 
	 * On particle system emitter apply
	 */
	void onParticleSystemEmitterApply();

	/** 
	 * Set particle system emitter
	 */
	void onParticleSystemEmitterDataApply();

	/** 
	 * Set particle system emitter
	 */
	void setParticleSystemEmitter();

	/** 
	 * On particle system load
	 */
	void onParticleSystemLoad();

	/** 
	 * On model save
	 */
	void onEntitySave();

	/** 
	 * On particle system reload
	 */
	void onParticleSystemReload();
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
	ParticleSystemScreenController(SharedParticleSystemView* view);
};
