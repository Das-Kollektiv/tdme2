// Generated from /tdme/src/tdme/tools/shared/controller/ParticleSystemScreenController.java
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/CharSequence.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Exception.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/NumberFormatException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>
#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController_onParticleSystemLoad_2.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController_onEntitySave_3.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController_onActionPerformed_4.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController_ParticleSystemScreenController_1.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Emitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_ObjectParticleSystem.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleSystem.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_SphereParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Type.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>
#include <tdme/tools/viewer/TDMEViewer.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::tools::shared::controller::ParticleSystemScreenController;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::CharSequence;
using java::lang::ClassCastException;
using java::lang::Comparable;
using java::lang::Exception;
using java::lang::NullPointerException;
using java::lang::NumberFormatException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::ParticleSystemScreenController_onParticleSystemLoad_2;
using tdme::tools::shared::controller::ParticleSystemScreenController_onEntitySave_3;
using tdme::tools::shared::controller::ParticleSystemScreenController_onActionPerformed_4;
using tdme::tools::shared::controller::ParticleSystemScreenController_ParticleSystemScreenController_1;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedParticleSystemView;
using tdme::tools::viewer::TDMEViewer;
using tdme::utils::MutableString;
using tdme::utils::_ArrayList;
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

ParticleSystemScreenController::ParticleSystemScreenController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ParticleSystemScreenController::ParticleSystemScreenController(SharedParticleSystemView* view) 
	: ParticleSystemScreenController(*static_cast< ::default_init_tag* >(0))
{
	ctor(view);
}

String* ParticleSystemScreenController::TYPE_NONE;

String* ParticleSystemScreenController::TYPE_OBJECTPARTICLESYSTEM;

String* ParticleSystemScreenController::TYPE_POINTSPARTICLESYSTEM;

String* ParticleSystemScreenController::EMITTER_NONE;

String* ParticleSystemScreenController::EMITTER_POINTPARTICLEEMITTER;

String* ParticleSystemScreenController::EMITTER_BOUNDINGBOXPARTICLEEMITTER;

String* ParticleSystemScreenController::EMITTER_CIRCLEPARTICLEEMITTER;

String* ParticleSystemScreenController::EMITTER_CIRCLEPARTICLEEMITTERPLANEVELOCITY;

String* ParticleSystemScreenController::EMITTER_SPHEREPARTICLEEMITTER;

void ParticleSystemScreenController::ctor(SharedParticleSystemView* view)
{
	super::ctor();
	this->particleSystemPath = new FileDialogPath(u"."_j);
	this->modelPath = new FileDialogPath(u"."_j);
	this->view = view;
	auto const finalView = view;
	this->entityBaseSubScreenController = new EntityBaseSubScreenController(view->getPopUpsViews(), new ParticleSystemScreenController_ParticleSystemScreenController_1(this, finalView));
	this->entityDisplaySubScreenController = new EntityDisplaySubScreenController();
	this->entityBoundingVolumeSubScreenController = new EntityBoundingVolumeSubScreenController(view->getPopUpsViews(), particleSystemPath);
	this->value = new MutableString();
}

EntityDisplaySubScreenController* ParticleSystemScreenController::getEntityDisplaySubScreenController()
{
	return entityDisplaySubScreenController;
}

EntityBoundingVolumeSubScreenController* ParticleSystemScreenController::getEntityBoundingVolumeSubScreenController()
{
	return entityBoundingVolumeSubScreenController;
}

GUIScreenNode* ParticleSystemScreenController::getScreenNode()
{
	return screenNode;
}

FileDialogPath* ParticleSystemScreenController::getParticleSystemPath()
{
	return particleSystemPath;
}

FileDialogPath* ParticleSystemScreenController::getModelPath()
{
	return modelPath;
}

void ParticleSystemScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse(u"resources/tools/particlesystem/gui"_j, u"screen_particlesystem.xml"_j);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = java_cast< GUITextNode* >(screenNode->getNodeById(u"screen_caption"_j));
		particleSystemReload = java_cast< GUIElementNode* >(screenNode->getNodeById(u"button_entity_reload"_j));
		particleSystemSave = java_cast< GUIElementNode* >(screenNode->getNodeById(u"button_entity_save"_j));
		particleSystemTypes = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ps_types"_j));
		particleSystemType = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ps_type"_j));
		particleSystemEmitters = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ps_emitters"_j));
		particleSystemEmitter = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ps_emitter"_j));
		opsScale = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ops_scale"_j));
		opsMaxCount = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ops_maxcount"_j));
		opsModel = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ops_model"_j));
		opsAutoEmit = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ops_auto_emit"_j));
		ppsMaxPoints = java_cast< GUIElementNode* >(screenNode->getNodeById(u"pps_maxpoints"_j));
		ppsAutoEmit = java_cast< GUIElementNode* >(screenNode->getNodeById(u"pps_auto_emit"_j));
		ppeCount = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_count"_j));
		ppeLifeTime = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_lifetime"_j));
		ppeLifeTimeRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_lifetimernd"_j));
		ppeMass = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_mass"_j));
		ppeMassRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_massrnd"_j));
		ppePosition = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_position"_j));
		ppeVelocity = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_velocity"_j));
		ppeVelocityRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_velocityrnd"_j));
		ppeColorStart = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_colorstart"_j));
		ppeColorEnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_colorend"_j));
		bbpeCount = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_count"_j));
		bbpeLifeTime = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_lifetime"_j));
		bbpeLifeTimeRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_lifetimernd"_j));
		bbpeMass = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_mass"_j));
		bbpeMassRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_massrnd"_j));
		bbpeVelocity = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_velocity"_j));
		bbpeVelocityRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_velocityrnd"_j));
		bbpeColorStart = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_colorstart"_j));
		bbpeColorEnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_colorend"_j));
		bbpeObbCenter = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_obb_center"_j));
		bbpeObbHalfextension = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_obb_halfextension"_j));
		bbpeObbRotationX = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_obb_rotation_x"_j));
		bbpeObbRotationY = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_obb_rotation_y"_j));
		bbpeObbRotationZ = java_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_obb_rotation_z"_j));
		cpeCount = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_count"_j));
		cpeLifeTime = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_lifetime"_j));
		cpeLifeTimeRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_lifetimernd"_j));
		cpeMass = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_mass"_j));
		cpeMassRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_massrnd"_j));
		cpeVelocity = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_velocity"_j));
		cpeVelocityRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_velocityrnd"_j));
		cpeColorStart = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_colorstart"_j));
		cpeColorEnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_colorend"_j));
		cpeCenter = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_center"_j));
		cpeRadius = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_radius"_j));
		cpeRotationX = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_rotation_x"_j));
		cpeRotationY = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_rotation_y"_j));
		cpeRotationZ = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_rotation_z"_j));
		cpepvCount = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_count"_j));
		cpepvLifeTime = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_lifetime"_j));
		cpepvLifeTimeRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_lifetimernd"_j));
		cpepvMass = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_mass"_j));
		cpepvMassRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_massrnd"_j));
		cpepvVelocity = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_velocity"_j));
		cpepvVelocityRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_velocityrnd"_j));
		cpepvColorStart = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_colorstart"_j));
		cpepvColorEnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_colorend"_j));
		cpepvCenter = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_center"_j));
		cpepvRadius = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_radius"_j));
		cpepvRotationX = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_rotation_x"_j));
		cpepvRotationY = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_rotation_y"_j));
		cpepvRotationZ = java_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_rotation_z"_j));
		speCount = java_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_count"_j));
		speLifeTime = java_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_lifetime"_j));
		speLifeTimeRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_lifetimernd"_j));
		speMass = java_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_mass"_j));
		speMassRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_massrnd"_j));
		speVelocity = java_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_velocity"_j));
		speVelocityRnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_velocityrnd"_j));
		speColorStart = java_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_colorstart"_j));
		speColorEnd = java_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_colorend"_j));
		speCenter = java_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_center"_j));
		speRadius = java_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_radius"_j));
	} catch (Exception* e) {
		e->printStackTrace();
	}
	entityBaseSubScreenController->initialize(screenNode);
	entityDisplaySubScreenController->initialize(screenNode);
	entityBoundingVolumeSubScreenController->initialize(screenNode);
}

void ParticleSystemScreenController::dispose()
{
}

void ParticleSystemScreenController::setScreenCaption(String* text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void ParticleSystemScreenController::setEntityData(String* name, String* description)
{
	entityBaseSubScreenController->setEntityData(name, description);
	particleSystemReload->getController()->setDisabled(false);
	particleSystemSave->getController()->setDisabled(false);
}

void ParticleSystemScreenController::unsetEntityData()
{
	entityBaseSubScreenController->unsetEntityData();
	particleSystemReload->getController()->setDisabled(true);
	particleSystemSave->getController()->setDisabled(true);
}

void ParticleSystemScreenController::setEntityProperties(String* presetId, Iterable* entityProperties, String* selectedName)
{
	entityBaseSubScreenController->setEntityProperties(view->getEntity(), presetId, entityProperties, selectedName);
}

void ParticleSystemScreenController::unsetEntityProperties()
{
	entityBaseSubScreenController->unsetEntityProperties();
}

void ParticleSystemScreenController::setParticleSystemTypes(_ArrayList* particleSystemTypesCollection)
{
	auto particleSystemTypesInnerNode = java_cast< GUIParentNode* >((particleSystemTypes->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(particleSystemTypes->getId())->append(u"_inner"_j)->toString())));
	auto idx = 0;
	auto particleSystemTypesInnerNodeSubNodesXML = u""_j;
	particleSystemTypesInnerNodeSubNodesXML = ::java::lang::StringBuilder(particleSystemTypesInnerNodeSubNodesXML).append(::java::lang::StringBuilder().append(u"<scrollarea-vertical id=\""_j)->append(particleSystemTypes->getId())
		->append(u"_inner_scrollarea\" width=\"100%\" height=\"100\">\n"_j)->toString())->toString();
	for (auto _i = particleSystemTypesCollection->iterator(); _i->hasNext(); ) {
		String* particleSystem = java_cast< String* >(_i->next());
		{
			particleSystemTypesInnerNodeSubNodesXML = ::java::lang::StringBuilder(particleSystemTypesInnerNodeSubNodesXML).append(::java::lang::StringBuilder().append(u"<dropdown-option text=\""_j)->append(GUIParser::escapeQuotes(particleSystem))
				->append(u"\" value=\""_j)
				->append(GUIParser::escapeQuotes(particleSystem))
				->append(u"\" "_j)
				->append((idx == 0 ? u"selected=\"true\" "_j : u""_j))
				->append(u" />\n"_j)->toString())->toString();
			idx++;
		}
	}
	particleSystemTypesInnerNodeSubNodesXML = ::java::lang::StringBuilder(particleSystemTypesInnerNodeSubNodesXML).append(u"</scrollarea-vertical>"_j)->toString();
	try {
		particleSystemTypesInnerNode->replaceSubNodes(particleSystemTypesInnerNodeSubNodesXML, true);
	} catch (Exception* e) {
		e->printStackTrace();
	}
}

void ParticleSystemScreenController::setParticleSystemEmitters(_ArrayList* emittersCollection)
{
	auto particleSystemEmittersInnerNode = java_cast< GUIParentNode* >((particleSystemEmitters->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(particleSystemEmitters->getId())->append(u"_inner"_j)->toString())));
	auto idx = 0;
	auto particleSystemEmittersInnerNodeSubNodesXML = u""_j;
	particleSystemEmittersInnerNodeSubNodesXML = ::java::lang::StringBuilder(particleSystemEmittersInnerNodeSubNodesXML).append(::java::lang::StringBuilder().append(u"<scrollarea-vertical id=\""_j)->append(particleSystemEmitters->getId())
		->append(u"_inner_scrollarea\" width=\"100%\" height=\"100\">\n"_j)->toString())->toString();
	for (auto _i = emittersCollection->iterator(); _i->hasNext(); ) {
		String* particleSystemEmitter = java_cast< String* >(_i->next());
		{
			particleSystemEmittersInnerNodeSubNodesXML = ::java::lang::StringBuilder(particleSystemEmittersInnerNodeSubNodesXML).append(::java::lang::StringBuilder().append(u"<dropdown-option text=\""_j)->append(GUIParser::escapeQuotes(particleSystemEmitter))
				->append(u"\" value=\""_j)
				->append(GUIParser::escapeQuotes(particleSystemEmitter))
				->append(u"\" "_j)
				->append((idx == 0 ? u"selected=\"true\" "_j : u""_j))
				->append(u" />\n"_j)->toString())->toString();
			idx++;
		}
	}
	particleSystemEmittersInnerNodeSubNodesXML = ::java::lang::StringBuilder(particleSystemEmittersInnerNodeSubNodesXML).append(u"</scrollarea-vertical>"_j)->toString();
	try {
		particleSystemEmittersInnerNode->replaceSubNodes(particleSystemEmittersInnerNodeSubNodesXML, true);
	} catch (Exception* e) {
		e->printStackTrace();
	}
}

void ParticleSystemScreenController::onQuit()
{
	TDMEViewer::getInstance()->quit();
}

void ParticleSystemScreenController::setParticleSystemType()
{
	auto particleSystem = view->getEntity()->getParticleSystem();
	particleSystemType->getActiveConditions()->removeAll();
	{
		auto v = particleSystem->getType();
		if ((v == LevelEditorEntityParticleSystem_Type::NONE)) {
			particleSystemTypes->getController()->setValue(value->set(TYPE_NONE));
			particleSystemType->getActiveConditions()->add(TYPE_NONE);
			goto end_switch0;;
		}
		if ((v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM)) {
			particleSystemTypes->getController()->setValue(value->set(TYPE_OBJECTPARTICLESYSTEM));
			particleSystemType->getActiveConditions()->add(TYPE_OBJECTPARTICLESYSTEM);
			opsMaxCount->getController()->setValue(value->set(particleSystem->getObjectParticleSystem()->getMaxCount()));
			opsScale->getController()->setValue(value->set(Tools::formatVector3(particleSystem->getObjectParticleSystem()->getScale())));
			opsModel->getController()->setValue(value->set(particleSystem->getObjectParticleSystem()->getModelFile()));
			opsAutoEmit->getController()->setValue(value->set(particleSystem->getObjectParticleSystem()->isAutoEmit() == true ? u"1"_j : u""_j));
			goto end_switch0;;
		}
		if ((v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)) {
			particleSystemTypes->getController()->setValue(value->set(TYPE_POINTSPARTICLESYSTEM));
			particleSystemType->getActiveConditions()->add(TYPE_POINTSPARTICLESYSTEM);
			ppsMaxPoints->getController()->setValue(value->set(particleSystem->getPointParticleSystem()->getMaxPoints()));
			ppsAutoEmit->getController()->setValue(value->set(particleSystem->getPointParticleSystem()->isAutoEmit() == true ? u"1"_j : u""_j));
			goto end_switch0;;
		}
		if ((((v != LevelEditorEntityParticleSystem_Type::NONE) && (v != LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) && (v != LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)))) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ParticleSystemScreenController::setParticleSystemType(): unknown particle system type '"_j)->append(static_cast< Object* >(particleSystem->getType()))
				->append(u"'"_j)->toString()));
			goto end_switch0;;
		}
end_switch0:;
	}

	view->initParticleSystem();
}

void ParticleSystemScreenController::onParticleSystemTypeDataApply()
{
	try {
		auto particleSystem = view->getEntity()->getParticleSystem();
		{
			auto v = particleSystem->getType();
			if ((v == LevelEditorEntityParticleSystem_Type::NONE)) {
				goto end_switch1;;
			}
			if ((v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM)) {
				particleSystem->getObjectParticleSystem()->setMaxCount(Tools::convertToInt(opsMaxCount->getController()->getValue()->toString()));
				particleSystem->getObjectParticleSystem()->getScale()->set(Tools::convertToVector3(opsScale->getController()->getValue()->toString()));
				particleSystem->getObjectParticleSystem()->setAutoEmit(opsAutoEmit->getController()->getValue()->equals(u"1"_j));
				try {
					particleSystem->getObjectParticleSystem()->setModelFile(opsModel->getController()->getValue()->toString());
				} catch (Exception* exception) {
					view->getPopUpsViews()->getInfoDialogScreenController()->show(u"Error"_j, ::java::lang::StringBuilder().append(u"An error occurred: "_j)->append(exception->getMessage())->toString());
				}
				goto end_switch1;;
			}
			if ((v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)) {
				particleSystem->getPointParticleSystem()->setMaxPoints(Tools::convertToInt(ppsMaxPoints->getController()->getValue()->toString()));
				particleSystem->getPointParticleSystem()->setAutoEmit(ppsAutoEmit->getController()->getValue()->equals(u"1"_j));
				goto end_switch1;;
			}
			if ((((v != LevelEditorEntityParticleSystem_Type::NONE) && (v != LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) && (v != LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)))) {
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ParticleSystemScreenController::setParticleSystemType(): unknown particle system type '"_j)->append(static_cast< Object* >(particleSystem->getType()))
					->append(u"'"_j)->toString()));
				goto end_switch1;;
			}
end_switch1:;
		}

	} catch (NumberFormatException* exception) {
		showErrorPopUp(u"Warning"_j, u"Invalid number entered"_j);
	}
	view->initParticleSystem();
}

void ParticleSystemScreenController::onParticleSystemTypeApply()
{
	auto particleSystemTypeString = particleSystemTypes->getController()->getValue()->toString();
	particleSystemType->getActiveConditions()->removeAll();
	particleSystemType->getActiveConditions()->add(particleSystemTypeString);
	if (particleSystemTypeString->equals(TYPE_NONE) == true) {
		view->getEntity()->getParticleSystem()->setType(LevelEditorEntityParticleSystem_Type::NONE);
	} else if (particleSystemTypeString->equals(TYPE_OBJECTPARTICLESYSTEM) == true) {
		view->getEntity()->getParticleSystem()->setType(LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM);
	} else if (particleSystemTypeString->equals(TYPE_POINTSPARTICLESYSTEM) == true) {
		view->getEntity()->getParticleSystem()->setType(LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM);
	} else {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ParticleSystemScreenController::onParticleSystemTypeApply(): unknown particle system type '"_j)->append(particleSystemTypeString)
			->append(u"'"_j)->toString()));
	}
	setParticleSystemType();
	view->initParticleSystem();
}

void ParticleSystemScreenController::onParticleSystemEmitterApply()
{
	auto particleSystem = view->getEntity()->getParticleSystem();
	auto particleSystemEmitterString = particleSystemEmitters->getController()->getValue()->toString();
	particleSystemEmitter->getActiveConditions()->removeAll();
	particleSystemEmitter->getActiveConditions()->add(particleSystemEmitterString);
	if (particleSystemEmitterString->equals(EMITTER_NONE) == true) {
		particleSystem->setEmitter(LevelEditorEntityParticleSystem_Emitter::NONE);
	} else if (particleSystemEmitterString->equals(EMITTER_POINTPARTICLEEMITTER) == true) {
		particleSystem->setEmitter(LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER);
	} else if (particleSystemEmitterString->equals(EMITTER_BOUNDINGBOXPARTICLEEMITTER) == true) {
		particleSystem->setEmitter(LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER);
	} else if (particleSystemEmitterString->equals(EMITTER_CIRCLEPARTICLEEMITTER) == true) {
		particleSystem->setEmitter(LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER);
	} else if (particleSystemEmitterString->equals(EMITTER_CIRCLEPARTICLEEMITTERPLANEVELOCITY) == true) {
		particleSystem->setEmitter(LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY);
	} else if (particleSystemEmitterString->equals(EMITTER_SPHEREPARTICLEEMITTER) == true) {
		particleSystem->setEmitter(LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER);
	} else {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ParticleSystemScreenController::onParticleSystemEmitterApply(): unknown particle system emitter '"_j)->append(particleSystemEmitterString)
			->append(u"'"_j)->toString()));
	}
	setParticleSystemEmitter();
}

void ParticleSystemScreenController::onParticleSystemEmitterDataApply()
{
	try {
		auto particleSystem = view->getEntity()->getParticleSystem();
		{
			auto v = particleSystem->getEmitter();
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE)) {
{
					particleSystemEmitters->getController()->setValue(value->set(EMITTER_NONE));
					goto end_switch2;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER)) {
{
					particleSystemEmitters->getController()->setValue(value->set(EMITTER_POINTPARTICLEEMITTER));
					auto emitter = particleSystem->getPointParticleEmitter();
					emitter->setCount(Tools::convertToInt(ppeCount->getController()->getValue()->toString()));
					emitter->setLifeTime(Tools::convertToInt(ppeLifeTime->getController()->getValue()->toString()));
					emitter->setLifeTimeRnd(Tools::convertToInt(ppeLifeTimeRnd->getController()->getValue()->toString()));
					emitter->setMass(Tools::convertToFloat(ppeMass->getController()->getValue()->toString()));
					emitter->setMassRnd(Tools::convertToFloat(ppeMassRnd->getController()->getValue()->toString()));
					emitter->getPosition()->set(Tools::convertToVector3(ppePosition->getController()->getValue()->toString()));
					emitter->getVelocity()->set(Tools::convertToVector3(ppeVelocity->getController()->getValue()->toString()));
					emitter->getVelocityRnd()->set(Tools::convertToVector3(ppeVelocityRnd->getController()->getValue()->toString()));
					emitter->getColorStart()->set(static_cast< Color4Base* >(Tools::convertToColor4(ppeColorStart->getController()->getValue()->toString())));
					emitter->getColorEnd()->set(static_cast< Color4Base* >(Tools::convertToColor4(ppeColorEnd->getController()->getValue()->toString())));
					goto end_switch2;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER)) {
{
					particleSystemEmitters->getController()->setValue(value->set(EMITTER_BOUNDINGBOXPARTICLEEMITTER));
					auto emitter = particleSystem->getBoundingBoxParticleEmitters();
					emitter->setCount(Tools::convertToInt(bbpeCount->getController()->getValue()->toString()));
					emitter->setLifeTime(Tools::convertToInt(bbpeLifeTime->getController()->getValue()->toString()));
					emitter->setLifeTimeRnd(Tools::convertToInt(bbpeLifeTimeRnd->getController()->getValue()->toString()));
					emitter->setMass(Tools::convertToFloat(bbpeMass->getController()->getValue()->toString()));
					emitter->setMassRnd(Tools::convertToFloat(bbpeMassRnd->getController()->getValue()->toString()));
					emitter->getVelocity()->set(Tools::convertToVector3(bbpeVelocity->getController()->getValue()->toString()));
					emitter->getVelocityRnd()->set(Tools::convertToVector3(bbpeVelocityRnd->getController()->getValue()->toString()));
					emitter->getColorStart()->set(static_cast< Color4Base* >(Tools::convertToColor4(bbpeColorStart->getController()->getValue()->toString())));
					emitter->getColorEnd()->set(static_cast< Color4Base* >(Tools::convertToColor4(bbpeColorEnd->getController()->getValue()->toString())));
					emitter->getObbCenter()->set(Tools::convertToVector3(bbpeObbCenter->getController()->getValue()->toString()));
					emitter->getObbHalfextension()->set(Tools::convertToVector3(bbpeObbHalfextension->getController()->getValue()->toString()));
					auto rotations = new Transformations();
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(bbpeObbRotationZ->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_Z));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(bbpeObbRotationY->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_Y));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(bbpeObbRotationX->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_X));
					rotations->update();
					rotations->getTransformationsMatrix()->getAxes(emitter->getObbAxis0(), emitter->getObbAxis1(), emitter->getObbAxis2());
					goto end_switch2;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER)) {
{
					particleSystemEmitters->getController()->setValue(value->set(EMITTER_CIRCLEPARTICLEEMITTER));
					auto emitter = particleSystem->getCircleParticleEmitter();
					emitter->setCount(Tools::convertToInt(cpeCount->getController()->getValue()->toString()));
					emitter->setLifeTime(Tools::convertToInt(cpeLifeTime->getController()->getValue()->toString()));
					emitter->setLifeTimeRnd(Tools::convertToInt(cpeLifeTimeRnd->getController()->getValue()->toString()));
					emitter->setMass(Tools::convertToFloat(cpeMass->getController()->getValue()->toString()));
					emitter->setMassRnd(Tools::convertToFloat(cpeMassRnd->getController()->getValue()->toString()));
					emitter->getVelocity()->set(Tools::convertToVector3(cpeVelocity->getController()->getValue()->toString()));
					emitter->getVelocityRnd()->set(Tools::convertToVector3(cpeVelocityRnd->getController()->getValue()->toString()));
					emitter->getColorStart()->set(static_cast< Color4Base* >(Tools::convertToColor4(cpeColorStart->getController()->getValue()->toString())));
					emitter->getColorEnd()->set(static_cast< Color4Base* >(Tools::convertToColor4(cpeColorEnd->getController()->getValue()->toString())));
					emitter->getCenter()->set(Tools::convertToVector3(cpeCenter->getController()->getValue()->toString()));
					emitter->setRadius(Tools::convertToFloat(cpeRadius->getController()->getValue()->toString()));
					auto rotations = new Transformations();
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpeRotationZ->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_Z));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpeRotationY->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_Y));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpeRotationX->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_X));
					rotations->update();
					rotations->getTransformationsMatrix()->getAxes(emitter->getAxis0(), new Vector3(), emitter->getAxis1());
					goto end_switch2;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY)) {
{
					particleSystemEmitters->getController()->setValue(value->set(EMITTER_CIRCLEPARTICLEEMITTERPLANEVELOCITY));
					auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
					emitter->setCount(Tools::convertToInt(cpepvCount->getController()->getValue()->toString()));
					emitter->setLifeTime(Tools::convertToInt(cpepvLifeTime->getController()->getValue()->toString()));
					emitter->setLifeTimeRnd(Tools::convertToInt(cpepvLifeTimeRnd->getController()->getValue()->toString()));
					emitter->setMass(Tools::convertToFloat(cpepvMass->getController()->getValue()->toString()));
					emitter->setMassRnd(Tools::convertToFloat(cpepvMassRnd->getController()->getValue()->toString()));
					emitter->setVelocity(Tools::convertToFloat(cpepvVelocity->getController()->getValue()->toString()));
					emitter->setVelocityRnd(Tools::convertToFloat(cpepvVelocityRnd->getController()->getValue()->toString()));
					emitter->getColorStart()->set(static_cast< Color4Base* >(Tools::convertToColor4(cpepvColorStart->getController()->getValue()->toString())));
					emitter->getColorEnd()->set(static_cast< Color4Base* >(Tools::convertToColor4(cpepvColorEnd->getController()->getValue()->toString())));
					emitter->getCenter()->set(Tools::convertToVector3(cpepvCenter->getController()->getValue()->toString()));
					emitter->setRadius(Tools::convertToFloat(cpepvRadius->getController()->getValue()->toString()));
					auto rotations = new Transformations();
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpepvRotationZ->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_Z));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpepvRotationY->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_Y));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpepvRotationX->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_X));
					rotations->update();
					rotations->getTransformationsMatrix()->getAxes(emitter->getAxis0(), new Vector3(), emitter->getAxis1());
					goto end_switch2;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)) {
{
					particleSystemEmitters->getController()->setValue(value->set(EMITTER_SPHEREPARTICLEEMITTER));
					auto emitter = particleSystem->getSphereParticleEmitter();
					emitter->setCount(Tools::convertToInt(speCount->getController()->getValue()->toString()));
					emitter->setLifeTime(Tools::convertToInt(speLifeTime->getController()->getValue()->toString()));
					emitter->setLifeTimeRnd(Tools::convertToInt(speLifeTimeRnd->getController()->getValue()->toString()));
					emitter->setMass(Tools::convertToFloat(speMass->getController()->getValue()->toString()));
					emitter->setMassRnd(Tools::convertToFloat(speMassRnd->getController()->getValue()->toString()));
					emitter->getVelocity()->set(Tools::convertToVector3(speVelocity->getController()->getValue()->toString()));
					emitter->getVelocityRnd()->set(Tools::convertToVector3(speVelocityRnd->getController()->getValue()->toString()));
					emitter->getColorStart()->set(static_cast< Color4Base* >(Tools::convertToColor4(speColorStart->getController()->getValue()->toString())));
					emitter->getColorEnd()->set(static_cast< Color4Base* >(Tools::convertToColor4(speColorEnd->getController()->getValue()->toString())));
					emitter->getCenter()->set(Tools::convertToVector3(speCenter->getController()->getValue()->toString()));
					emitter->setRadius(Tools::convertToFloat(speRadius->getController()->getValue()->toString()));
					goto end_switch2;;
				}			}
			if (((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) || ((v != LevelEditorEntityParticleSystem_Emitter::NONE) && (v != LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) && (v != LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)))) {
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ParticleSystemScreenController::onParticleSystemEmitterApply(): unknown particle system emitter '"_j)->append(static_cast< Object* >(particleSystem->getEmitter()))
					->append(u"'"_j)->toString()));
			}
end_switch2:;
		}

	} catch (NumberFormatException* exception) {
		showErrorPopUp(u"Warning"_j, u"Invalid number entered"_j);
	}
	view->initParticleSystem();
}

void ParticleSystemScreenController::setParticleSystemEmitter()
{
	particleSystemEmitter->getActiveConditions()->removeAll();
	auto particleSystem = view->getEntity()->getParticleSystem();
	{
		auto v = particleSystem->getEmitter();
		if ((v == LevelEditorEntityParticleSystem_Emitter::NONE)) {
{
				particleSystemEmitters->getController()->setValue(value->set(EMITTER_NONE));
				particleSystemEmitter->getActiveConditions()->add(EMITTER_NONE);
				goto end_switch3;;
			}		}
		if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER)) {
{
				particleSystemEmitters->getController()->setValue(value->set(EMITTER_POINTPARTICLEEMITTER));
				particleSystemEmitter->getActiveConditions()->add(EMITTER_POINTPARTICLEEMITTER);
				auto emitter = particleSystem->getPointParticleEmitter();
				ppeCount->getController()->setValue(value->set(emitter->getCount()));
				ppeLifeTime->getController()->setValue(value->set(static_cast< int32_t >(emitter->getLifeTime())));
				ppeLifeTimeRnd->getController()->setValue(value->set(static_cast< int32_t >(emitter->getLifeTimeRnd())));
				ppeMass->getController()->setValue(value->set(emitter->getMass(), 4));
				ppeMassRnd->getController()->setValue(value->set(emitter->getMassRnd(), 4));
				ppePosition->getController()->setValue(value->set(Tools::formatVector3(emitter->getPosition())));
				ppeVelocity->getController()->setValue(value->set(Tools::formatVector3(emitter->getVelocity())));
				ppeVelocityRnd->getController()->setValue(value->set(Tools::formatVector3(emitter->getVelocityRnd())));
				ppeColorStart->getController()->setValue(value->set(Tools::formatColor4(emitter->getColorStart())));
				ppeColorEnd->getController()->setValue(value->set(Tools::formatColor4(emitter->getColorEnd())));
				goto end_switch3;;
			}		}
		if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER)) {
{
				particleSystemEmitters->getController()->setValue(value->set(EMITTER_BOUNDINGBOXPARTICLEEMITTER));
				particleSystemEmitter->getActiveConditions()->add(EMITTER_BOUNDINGBOXPARTICLEEMITTER);
				auto emitter = particleSystem->getBoundingBoxParticleEmitters();
				bbpeCount->getController()->setValue(value->set(emitter->getCount()));
				bbpeLifeTime->getController()->setValue(value->set(static_cast< int32_t >(emitter->getLifeTime())));
				bbpeLifeTimeRnd->getController()->setValue(value->set(static_cast< int32_t >(emitter->getLifeTimeRnd())));
				bbpeMass->getController()->setValue(value->set(emitter->getMass(), 4));
				bbpeMassRnd->getController()->setValue(value->set(emitter->getMassRnd(), 4));
				bbpeVelocity->getController()->setValue(value->set(Tools::formatVector3(emitter->getVelocity())));
				bbpeVelocityRnd->getController()->setValue(value->set(Tools::formatVector3(emitter->getVelocityRnd())));
				bbpeColorStart->getController()->setValue(value->set(Tools::formatColor4(emitter->getColorStart())));
				bbpeColorEnd->getController()->setValue(value->set(Tools::formatColor4(emitter->getColorEnd())));
				bbpeObbCenter->getController()->setValue(value->set(Tools::formatVector3(emitter->getObbCenter())));
				bbpeObbHalfextension->getController()->setValue(value->set(Tools::formatVector3(emitter->getObbHalfextension())));
				auto rotation = new Vector3();
				auto rotationMatrix = (new Matrix4x4())->identity();
				rotationMatrix->setAxes(emitter->getObbAxis0(), emitter->getObbAxis1(), emitter->getObbAxis2());
				rotationMatrix->computeEulerAngles(rotation);
				bbpeObbRotationX->getController()->setValue(value->set(Tools::formatFloat(rotation->getX())));
				bbpeObbRotationY->getController()->setValue(value->set(Tools::formatFloat(rotation->getY())));
				bbpeObbRotationZ->getController()->setValue(value->set(Tools::formatFloat(rotation->getZ())));
				goto end_switch3;;
			}		}
		if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER)) {
{
				particleSystemEmitters->getController()->setValue(value->set(EMITTER_CIRCLEPARTICLEEMITTER));
				particleSystemEmitter->getActiveConditions()->add(EMITTER_CIRCLEPARTICLEEMITTER);
				auto emitter = particleSystem->getCircleParticleEmitter();
				cpeCount->getController()->setValue(value->set(emitter->getCount()));
				cpeLifeTime->getController()->setValue(value->set(static_cast< int32_t >(emitter->getLifeTime())));
				cpeLifeTimeRnd->getController()->setValue(value->set(static_cast< int32_t >(emitter->getLifeTimeRnd())));
				cpeMass->getController()->setValue(value->set(emitter->getMass(), 4));
				cpeMassRnd->getController()->setValue(value->set(emitter->getMassRnd(), 4));
				cpeVelocity->getController()->setValue(value->set(Tools::formatVector3(emitter->getVelocity())));
				cpeVelocityRnd->getController()->setValue(value->set(Tools::formatVector3(emitter->getVelocityRnd())));
				cpeColorStart->getController()->setValue(value->set(Tools::formatColor4(emitter->getColorStart())));
				cpeColorEnd->getController()->setValue(value->set(Tools::formatColor4(emitter->getColorEnd())));
				cpeCenter->getController()->setValue(value->set(Tools::formatVector3(emitter->getCenter())));
				cpeRadius->getController()->setValue(value->set(emitter->getRadius(), 4));
				auto rotation = new Vector3();
				auto rotationMatrix = (new Matrix4x4())->identity();
				rotationMatrix->setAxes(emitter->getAxis0(), Vector3::computeCrossProduct(emitter->getAxis0(), emitter->getAxis1()), emitter->getAxis1());
				rotationMatrix->computeEulerAngles(rotation);
				cpeRotationX->getController()->setValue(value->set(Tools::formatFloat(rotation->getX())));
				cpeRotationY->getController()->setValue(value->set(Tools::formatFloat(rotation->getY())));
				cpeRotationZ->getController()->setValue(value->set(Tools::formatFloat(rotation->getZ())));
				goto end_switch3;;
			}		}
		if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY)) {
{
				particleSystemEmitters->getController()->setValue(value->set(EMITTER_CIRCLEPARTICLEEMITTERPLANEVELOCITY));
				particleSystemEmitter->getActiveConditions()->add(EMITTER_CIRCLEPARTICLEEMITTERPLANEVELOCITY);
				auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
				cpepvCount->getController()->setValue(value->set(emitter->getCount()));
				cpepvLifeTime->getController()->setValue(value->set(static_cast< int32_t >(emitter->getLifeTime())));
				cpepvLifeTimeRnd->getController()->setValue(value->set(static_cast< int32_t >(emitter->getLifeTimeRnd())));
				cpepvMass->getController()->setValue(value->set(emitter->getMass(), 4));
				cpepvMassRnd->getController()->setValue(value->set(emitter->getMassRnd(), 4));
				cpepvVelocity->getController()->setValue(value->set(emitter->getVelocity(), 4));
				cpepvVelocityRnd->getController()->setValue(value->set(emitter->getVelocityRnd(), 4));
				cpepvColorStart->getController()->setValue(value->set(Tools::formatColor4(emitter->getColorStart())));
				cpepvColorEnd->getController()->setValue(value->set(Tools::formatColor4(emitter->getColorEnd())));
				cpepvCenter->getController()->setValue(value->set(Tools::formatVector3(emitter->getCenter())));
				cpepvRadius->getController()->setValue(value->set(emitter->getRadius(), 4));
				auto rotation = new Vector3();
				auto rotationMatrix = (new Matrix4x4())->identity();
				rotationMatrix->setAxes(emitter->getAxis0(), Vector3::computeCrossProduct(emitter->getAxis0(), emitter->getAxis1()), emitter->getAxis1());
				rotationMatrix->computeEulerAngles(rotation);
				cpepvRotationX->getController()->setValue(value->set(Tools::formatFloat(rotation->getX())));
				cpepvRotationY->getController()->setValue(value->set(Tools::formatFloat(rotation->getY())));
				cpepvRotationZ->getController()->setValue(value->set(Tools::formatFloat(rotation->getZ())));
				goto end_switch3;;
			}		}
		if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)) {
{
				particleSystemEmitters->getController()->setValue(value->set(EMITTER_SPHEREPARTICLEEMITTER));
				particleSystemEmitter->getActiveConditions()->add(EMITTER_SPHEREPARTICLEEMITTER);
				auto emitter = particleSystem->getSphereParticleEmitter();
				speCount->getController()->setValue(value->set(emitter->getCount()));
				speLifeTime->getController()->setValue(value->set(static_cast< int32_t >(emitter->getLifeTime())));
				speLifeTimeRnd->getController()->setValue(value->set(static_cast< int32_t >(emitter->getLifeTimeRnd())));
				speMass->getController()->setValue(value->set(emitter->getMass(), 4));
				speMassRnd->getController()->setValue(value->set(emitter->getMassRnd(), 4));
				speVelocity->getController()->setValue(value->set(Tools::formatVector3(emitter->getVelocity())));
				speVelocityRnd->getController()->setValue(value->set(Tools::formatVector3(emitter->getVelocityRnd())));
				speColorStart->getController()->setValue(value->set(Tools::formatColor4(emitter->getColorStart())));
				speColorEnd->getController()->setValue(value->set(Tools::formatColor4(emitter->getColorEnd())));
				speCenter->getController()->setValue(value->set(Tools::formatVector3(emitter->getCenter())));
				speRadius->getController()->setValue(value->set(emitter->getRadius(), 4));
				goto end_switch3;;
			}		}
		if (((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) || ((v != LevelEditorEntityParticleSystem_Emitter::NONE) && (v != LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) && (v != LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)))) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ParticleSystemScreenController::onParticleSystemEmitterApply(): unknown particle system emitter '"_j)->append(static_cast< Object* >(particleSystem->getEmitter()))
				->append(u"'"_j)->toString()));
		}
end_switch3:;
	}

	view->initParticleSystem();
}

void ParticleSystemScreenController::onParticleSystemLoad()
{
	view->getPopUpsViews()->getFileDialogScreenController()->show(particleSystemPath->getPath(), u"Load from: "_j, new StringArray({u"tps"_j}), view->getFileName(), new ParticleSystemScreenController_onParticleSystemLoad_2(this));
}

void ParticleSystemScreenController::onEntitySave()
{
	auto fileName = view->getEntity()->getEntityFileName();
	if (fileName == nullptr) {
		fileName = u"untitle.tps"_j;
	}
	fileName = Tools::getFileName(fileName);
	view->getPopUpsViews()->getFileDialogScreenController()->show(particleSystemPath->getPath(), u"Save from: "_j, new StringArray({u"tps"_j}), fileName, new ParticleSystemScreenController_onEntitySave_3(this));
}

void ParticleSystemScreenController::onParticleSystemReload()
{
	view->reloadFile();
}

void ParticleSystemScreenController::saveFile(String* pathName, String* fileName) /* throws(Exception) */
{
	view->saveFile(pathName, fileName);
}

void ParticleSystemScreenController::loadFile(String* pathName, String* fileName) /* throws(Exception) */
{
	view->loadFile(pathName, fileName);
}

void ParticleSystemScreenController::showErrorPopUp(String* caption, String* message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void ParticleSystemScreenController::onValueChanged(GUIElementNode* node)
{
	entityBaseSubScreenController->onValueChanged(node, view->getEntity());
}

void ParticleSystemScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	entityBaseSubScreenController->onActionPerformed(type, node, view->getEntity());
	entityDisplaySubScreenController->onActionPerformed(type, node);
	entityBoundingVolumeSubScreenController->onActionPerformed(type, node, view->getEntity());
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED)) {
{
				if (node->getId()->equals(u"button_entity_load"_j)) {
					onParticleSystemLoad();
				} else if (node->getId()->equals(u"button_entity_reload"_j)) {
					onParticleSystemReload();
				} else if (node->getId()->equals(u"button_entity_save"_j)) {
					onEntitySave();
				} else if (node->getId()->equals(u"button_ps_type_apply"_j)) {
					onParticleSystemTypeApply();
				} else if (node->getId()->equals(u"button_ops_apply"_j) || node->getId()->equals(u"button_pps_type_apply"_j)) {
					onParticleSystemTypeDataApply();
				} else if (node->getId()->equals(u"button_emitter_apply"_j)) {
					onParticleSystemEmitterApply();
				} else if (node->getId()->equals(u"button_ppe_emitter_apply"_j) || node->getId()->equals(u"button_bbpe_emitter_apply"_j) || node->getId()->equals(u"button_cpe_emitter_apply"_j)|| node->getId()->equals(u"button_cpepv_emitter_apply"_j)|| node->getId()->equals(u"button_spe_emitter_apply"_j)) {
					onParticleSystemEmitterDataApply();
				} else if (node->getId()->equals(u"button_ops_model_file"_j)) {
					view->getPopUpsViews()->getFileDialogScreenController()->show(modelPath->getPath(), u"Load from: "_j, new StringArray({
						u"dae"_j,
						u"tm"_j
					}), u""_j, new ParticleSystemScreenController_onActionPerformed_4(this));
				} else {
					_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ModelViewerScreenController::onActionPerformed()::unknown, type='"_j)->append(static_cast< Object* >(type))
						->append(u"', id = '"_j)
						->append(node->getId())
						->append(u"'"_j)
						->append(u", name = '"_j)
						->append(node->getName())
						->append(u"'"_j)->toString()));
				}
				goto end_switch4;;
			}		}
		if ((v == GUIActionListener_Type::PERFORMED) || (v == GUIActionListener_Type::PERFORMING)) {
{
				goto end_switch4;;
			}		}
end_switch4:;
	}

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ParticleSystemScreenController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.controller.ParticleSystemScreenController", 59);
    return c;
}

void ParticleSystemScreenController::clinit()
{
struct string_init_ {
	string_init_() {
	TYPE_NONE = u"None"_j;
	TYPE_OBJECTPARTICLESYSTEM = u"Object Particle System"_j;
	TYPE_POINTSPARTICLESYSTEM = u"Points Particle System"_j;
	EMITTER_NONE = u"None"_j;
	EMITTER_POINTPARTICLEEMITTER = u"Point Particle Emitter"_j;
	EMITTER_BOUNDINGBOXPARTICLEEMITTER = u"BoundingBox Particle Emitter"_j;
	EMITTER_CIRCLEPARTICLEEMITTER = u"Circle Particle Emitter"_j;
	EMITTER_CIRCLEPARTICLEEMITTERPLANEVELOCITY = u"Circle Particle Emitter Plane Velocity"_j;
	EMITTER_SPHEREPARTICLEEMITTER = u"Sphere Particle Emitter"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* ParticleSystemScreenController::getClass0()
{
	return class_();
}

