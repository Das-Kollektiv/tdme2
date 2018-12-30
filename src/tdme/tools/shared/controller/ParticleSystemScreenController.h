
#pragma once

#include <vector>
#include <string>

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/controller/ScreenController.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>

using std::vector;
using std::string;

using tdme::tools::shared::controller::ScreenController;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::SharedParticleSystemView;

/** 
 * Particle system screen controller
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
	friend class ParticleSystemScreenController_onActionPerformed_5;

private:
	static string TYPE_NONE;
	static string TYPE_OBJECTPARTICLESYSTEM;
	static string TYPE_POINTSPARTICLESYSTEM;
	static string EMITTER_NONE;
	static string EMITTER_POINTPARTICLEEMITTER;
	static string EMITTER_BOUNDINGBOXPARTICLEEMITTER;
	static string EMITTER_CIRCLEPARTICLEEMITTER;
	static string EMITTER_CIRCLEPARTICLEEMITTERPLANEVELOCITY;
	static string EMITTER_SPHEREPARTICLEEMITTER;
	EntityBaseSubScreenController* entityBaseSubScreenController {  };
	EntityDisplaySubScreenController* entityDisplaySubScreenController {  };
	EntityPhysicsSubScreenController* entityPhysicsSubScreenController {  };
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
	GUIElementNode* ppsPointSize {  };
	GUIElementNode* ppsTexture {  };
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
	EntityPhysicsSubScreenController* getEntityPhysicsSubScreenController();
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
	 * @param text text
	 */
	void setScreenCaption(const string& text);

	/** 
	 * Set up general entity data
	 * @param name name
	 * @param description description
	 */
	void setEntityData(const string& name, const string& description);

	/** 
	 * Unset entity data
	 */
	void unsetEntityData();

	/** 
	 * Set up entity properties
	 * @param presetId preset id
	 * @param entity entity properties
	 * @param selectedName selected name
	 */
	void setEntityProperties(const string& presetId, LevelEditorEntity* entity, const string& selectedName);

	/** 
	 * Unset entity properties
	 */
	void unsetEntityProperties();

	/** 
	 * Set up particle system types
	 * @param particleSystemTypesCollection particle system types
	 */
	void setParticleSystemTypes(const vector<string>& particleSystemTypesCollection);

	/** 
	 * Set up emitters
	 * @param emittersCollection emitters
	 */
	void setParticleSystemEmitters(const vector<string>& emittersCollection);

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
	void saveFile(const string& pathName, const string& fileName) /* throws(Exception) */;
	void loadFile(const string& pathName, const string& fileName) /* throws(Exception) */;

	/** 
	 * Shows the error pop up
	 */
	void showErrorPopUp(const string& caption, const string& message);
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	/**
	 * Public constructor
	 * @param view view
	 */
	ParticleSystemScreenController(SharedParticleSystemView* view);

	/**
	 * Destructor
	 */
	virtual ~ParticleSystemScreenController();
};
