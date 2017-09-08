// Generated from /tdme/src/tdme/tools/shared/controller/ParticleSystemScreenController.java
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>

#include <string>
#include <vector>

#include <java/lang/String.h>

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
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using std::vector;
using std::wstring;

using tdme::tools::shared::controller::ParticleSystemScreenController;
using java::lang::String;
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
using tdme::utils::StringConverter;
using tdme::utils::_Exception;
using tdme::utils::_Console;

String* ParticleSystemScreenController::TYPE_NONE = u"None"_j;
String* ParticleSystemScreenController::TYPE_OBJECTPARTICLESYSTEM = u"Object Particle System"_j;
String* ParticleSystemScreenController::TYPE_POINTSPARTICLESYSTEM = u"Points Particle System"_j;
String* ParticleSystemScreenController::EMITTER_NONE = u"None"_j;
String* ParticleSystemScreenController::EMITTER_POINTPARTICLEEMITTER = u"Point Particle Emitter"_j;
String* ParticleSystemScreenController::EMITTER_BOUNDINGBOXPARTICLEEMITTER = u"BoundingBox Particle Emitter"_j;
String* ParticleSystemScreenController::EMITTER_CIRCLEPARTICLEEMITTER = u"Circle Particle Emitter"_j;
String* ParticleSystemScreenController::EMITTER_CIRCLEPARTICLEEMITTERPLANEVELOCITY = u"Circle Particle Emitter Plane Velocity"_j;
String* ParticleSystemScreenController::EMITTER_SPHEREPARTICLEEMITTER = u"Sphere Particle Emitter"_j;

ParticleSystemScreenController::ParticleSystemScreenController(SharedParticleSystemView* view)
{
	this->particleSystemPath = new FileDialogPath(L".");
	this->modelPath = new FileDialogPath(L".");
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
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById(u"screen_caption"_j));
		particleSystemReload = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_entity_reload"_j));
		particleSystemSave = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_entity_save"_j));
		particleSystemTypes = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ps_types"_j));
		particleSystemType = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ps_type"_j));
		particleSystemEmitters = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ps_emitters"_j));
		particleSystemEmitter = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ps_emitter"_j));
		opsScale = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ops_scale"_j));
		opsMaxCount = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ops_maxcount"_j));
		opsModel = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ops_model"_j));
		opsAutoEmit = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ops_auto_emit"_j));
		ppsMaxPoints = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"pps_maxpoints"_j));
		ppsAutoEmit = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"pps_auto_emit"_j));
		ppeCount = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_count"_j));
		ppeLifeTime = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_lifetime"_j));
		ppeLifeTimeRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_lifetimernd"_j));
		ppeMass = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_mass"_j));
		ppeMassRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_massrnd"_j));
		ppePosition = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_position"_j));
		ppeVelocity = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_velocity"_j));
		ppeVelocityRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_velocityrnd"_j));
		ppeColorStart = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_colorstart"_j));
		ppeColorEnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"ppe_colorend"_j));
		bbpeCount = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_count"_j));
		bbpeLifeTime = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_lifetime"_j));
		bbpeLifeTimeRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_lifetimernd"_j));
		bbpeMass = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_mass"_j));
		bbpeMassRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_massrnd"_j));
		bbpeVelocity = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_velocity"_j));
		bbpeVelocityRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_velocityrnd"_j));
		bbpeColorStart = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_colorstart"_j));
		bbpeColorEnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_colorend"_j));
		bbpeObbCenter = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_obb_center"_j));
		bbpeObbHalfextension = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_obb_halfextension"_j));
		bbpeObbRotationX = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_obb_rotation_x"_j));
		bbpeObbRotationY = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_obb_rotation_y"_j));
		bbpeObbRotationZ = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"bbpe_obb_rotation_z"_j));
		cpeCount = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_count"_j));
		cpeLifeTime = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_lifetime"_j));
		cpeLifeTimeRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_lifetimernd"_j));
		cpeMass = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_mass"_j));
		cpeMassRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_massrnd"_j));
		cpeVelocity = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_velocity"_j));
		cpeVelocityRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_velocityrnd"_j));
		cpeColorStart = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_colorstart"_j));
		cpeColorEnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_colorend"_j));
		cpeCenter = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_center"_j));
		cpeRadius = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_radius"_j));
		cpeRotationX = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_rotation_x"_j));
		cpeRotationY = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_rotation_y"_j));
		cpeRotationZ = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpe_rotation_z"_j));
		cpepvCount = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_count"_j));
		cpepvLifeTime = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_lifetime"_j));
		cpepvLifeTimeRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_lifetimernd"_j));
		cpepvMass = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_mass"_j));
		cpepvMassRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_massrnd"_j));
		cpepvVelocity = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_velocity"_j));
		cpepvVelocityRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_velocityrnd"_j));
		cpepvColorStart = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_colorstart"_j));
		cpepvColorEnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_colorend"_j));
		cpepvCenter = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_center"_j));
		cpepvRadius = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_radius"_j));
		cpepvRotationX = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_rotation_x"_j));
		cpepvRotationY = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_rotation_y"_j));
		cpepvRotationZ = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"cpepv_rotation_z"_j));
		speCount = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_count"_j));
		speLifeTime = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_lifetime"_j));
		speLifeTimeRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_lifetimernd"_j));
		speMass = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_mass"_j));
		speMassRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_massrnd"_j));
		speVelocity = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_velocity"_j));
		speVelocityRnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_velocityrnd"_j));
		speColorStart = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_colorstart"_j));
		speColorEnd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_colorend"_j));
		speCenter = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_center"_j));
		speRadius = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"spe_radius"_j));
	} catch (_Exception& exception) {
		_Console::print(string("ParticleSystemScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
	entityDisplaySubScreenController->initialize(screenNode);
	entityBoundingVolumeSubScreenController->initialize(screenNode);
}

void ParticleSystemScreenController::dispose()
{
}

void ParticleSystemScreenController::setScreenCaption(const wstring& text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void ParticleSystemScreenController::setEntityData(const wstring& name, const wstring& description)
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

void ParticleSystemScreenController::setEntityProperties(const wstring& presetId, LevelEditorEntity* entity, const wstring& selectedName)
{
	entityBaseSubScreenController->setEntityProperties(view->getEntity(), presetId, selectedName);
}

void ParticleSystemScreenController::unsetEntityProperties()
{
	entityBaseSubScreenController->unsetEntityProperties();
}

void ParticleSystemScreenController::setParticleSystemTypes(const vector<String*>* particleSystemTypesCollection)
{
	auto particleSystemTypesInnerNode = dynamic_cast< GUIParentNode* >(particleSystemTypes->getScreenNode()->getNodeById(new String(particleSystemTypes->getId()->getCPPWString() + L"_inner")));
	auto idx = 0;
	wstring particleSystemTypesInnerNodeSubNodesXML = L"";
	particleSystemTypesInnerNodeSubNodesXML =
		particleSystemTypesInnerNodeSubNodesXML +
		L"<scrollarea-vertical id=\"" +
		particleSystemTypes->getId()->getCPPWString() +
		L"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
	for (auto particleSystem: *particleSystemTypesCollection) {
		particleSystemTypesInnerNodeSubNodesXML =
			particleSystemTypesInnerNodeSubNodesXML +
			L"<dropdown-option text=\"" +
			GUIParser::escapeQuotes(particleSystem->getCPPWString()) +
			L"\" value=\"" +
			GUIParser::escapeQuotes(particleSystem->getCPPWString()) +
			L"\" " +
			(idx == 0 ? L"selected=\"true\" " : L"") +
			L" />\n";
		idx++;
	}
	particleSystemTypesInnerNodeSubNodesXML =
		particleSystemTypesInnerNodeSubNodesXML +
		L"</scrollarea-vertical>";
	try {
		particleSystemTypesInnerNode->replaceSubNodes(new String(particleSystemTypesInnerNodeSubNodesXML), true);
	} catch (_Exception& exception) {
		_Console::print(string("ParticleSystemScreenController::setParticleSystemTypes(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
}

void ParticleSystemScreenController::setParticleSystemEmitters(const vector<String*>* emittersCollection)
{
	auto particleSystemEmittersInnerNode = dynamic_cast< GUIParentNode* >((particleSystemEmitters->getScreenNode()->getNodeById(new String(particleSystemEmitters->getId()->getCPPWString() + L"_inner"))));
	auto idx = 0;
	wstring particleSystemEmittersInnerNodeSubNodesXML = L"";
	particleSystemEmittersInnerNodeSubNodesXML =
		particleSystemEmittersInnerNodeSubNodesXML +
		L"<scrollarea-vertical id=\"" +
		particleSystemEmitters->getId()->getCPPWString() +
		L"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
	for (auto particleSystemEmitter: *emittersCollection) {
		particleSystemEmittersInnerNodeSubNodesXML =
			particleSystemEmittersInnerNodeSubNodesXML +
			L"<dropdown-option text=\"" +
			GUIParser::escapeQuotes(particleSystemEmitter->getCPPWString()) +
			L"\" value=\"" +
			GUIParser::escapeQuotes(particleSystemEmitter->getCPPWString()) +
			L"\" " +
			(idx == 0 ? L"selected=\"true\" " : L"") +
			L" />\n";
		idx++;
	}
	particleSystemEmittersInnerNodeSubNodesXML =
		particleSystemEmittersInnerNodeSubNodesXML +
		L"</scrollarea-vertical>";
	try {
		particleSystemEmittersInnerNode->replaceSubNodes(new String(particleSystemEmittersInnerNodeSubNodesXML), true);
	} catch (_Exception& exception) {
		_Console::print(string("ParticleSystemScreenController::setParticleSystemEmitters: An error occurred: "));
		_Console::println(string(exception.what()));
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
			_Console::println(
				wstring(
					L"ParticleSystemScreenController::setParticleSystemType(): unknown particle system type '" +
					particleSystem->getType()->toWString() +
					L"'"
				)
			);
			goto end_switch0;
		}
		end_switch0:;
	}

	view->initParticleSystemRequest();
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
					particleSystem->getObjectParticleSystem()->setModelFile(opsModel->getController()->getValue()->toString()->getCPPWString());
				} catch (_Exception& exception) {
					view->getPopUpsViews()->getInfoDialogScreenController()->show(L"Error", L"An error occurred: " + StringConverter::toWideString(string(exception.what())));
				}
				goto end_switch1;;
			}
			if ((v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)) {
				particleSystem->getPointParticleSystem()->setMaxPoints(Tools::convertToInt(ppsMaxPoints->getController()->getValue()->toString()));
				particleSystem->getPointParticleSystem()->setAutoEmit(ppsAutoEmit->getController()->getValue()->equals(u"1"_j));
				goto end_switch1;;
			}
			if ((((v != LevelEditorEntityParticleSystem_Type::NONE) && (v != LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) && (v != LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)))) {
				_Console::println(
					wstring(
						L"ParticleSystemScreenController::setParticleSystemType(): unknown particle system type '" +
						particleSystem->getType()->toWString() +
						L"'"
					)
				);
				goto end_switch1;;
			}
			end_switch1:;
		}

	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(string(exception.what())));
	}
	view->initParticleSystemRequest();
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
		_Console::println(
			wstring(
				L"ParticleSystemScreenController::onParticleSystemTypeApply(): unknown particle system type '" +
				particleSystemTypeString->getCPPWString() +
				L"'"
			)
		);
	}
	setParticleSystemType();
	view->initParticleSystemRequest();
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
		_Console::println(
			wstring(
				L"ParticleSystemScreenController::onParticleSystemEmitterApply(): unknown particle system emitter '" +
				particleSystemEmitterString->getCPPWString() +
				L"'"
			)
		);
	}
	setParticleSystemEmitter();
}

void ParticleSystemScreenController::onParticleSystemEmitterDataApply()
{
	try {
		auto particleSystem = view->getEntity()->getParticleSystem();
		{
			auto v = particleSystem->getEmitter();
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE))
			{
				{
					particleSystemEmitters->getController()->setValue(value->set(EMITTER_NONE));
					goto end_switch2;;
				}
			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER))
			{
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
				}
			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER))
			{
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
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(bbpeObbRotationZ->getController()->getValue()->toString()), &OrientedBoundingBox::AABB_AXIS_Z));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(bbpeObbRotationY->getController()->getValue()->toString()), &OrientedBoundingBox::AABB_AXIS_Y));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(bbpeObbRotationX->getController()->getValue()->toString()), &OrientedBoundingBox::AABB_AXIS_X));
					rotations->update();
					rotations->getTransformationsMatrix()->getAxes(emitter->getObbAxis0(), emitter->getObbAxis1(), emitter->getObbAxis2());
					goto end_switch2;;
				}
			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER))
			{
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
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpeRotationZ->getController()->getValue()->toString()), &OrientedBoundingBox::AABB_AXIS_Z));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpeRotationY->getController()->getValue()->toString()), &OrientedBoundingBox::AABB_AXIS_Y));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpeRotationX->getController()->getValue()->toString()), &OrientedBoundingBox::AABB_AXIS_X));
					rotations->update();
					rotations->getTransformationsMatrix()->getAxes(emitter->getAxis0(), new Vector3(), emitter->getAxis1());
					goto end_switch2;;
				}
			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY))
			{
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
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpepvRotationZ->getController()->getValue()->toString()), &OrientedBoundingBox::AABB_AXIS_Z));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpepvRotationY->getController()->getValue()->toString()), &OrientedBoundingBox::AABB_AXIS_Y));
					rotations->getRotations()->add(new Rotation(Tools::convertToFloat(cpepvRotationX->getController()->getValue()->toString()), &OrientedBoundingBox::AABB_AXIS_X));
					rotations->update();
					rotations->getTransformationsMatrix()->getAxes(emitter->getAxis0(), new Vector3(), emitter->getAxis1());
					goto end_switch2;;
				}
			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER))
			{
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
				}
			}
			if (((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) || ((v != LevelEditorEntityParticleSystem_Emitter::NONE) && (v != LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) && (v != LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER))))
			{
				_Console::println(
					wstring(
						L"ParticleSystemScreenController::onParticleSystemEmitterApply(): unknown particle system emitter '" +
						particleSystem->getEmitter()->toWString() +
						L"'"
					)
				);
			}
			end_switch2:;
		}

	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(string(exception.what())));
	}
	view->initParticleSystemRequest();
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
			}
		}
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
			}
		}
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
			}
		}
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
			}
		}
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
			}
		}
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
			}
		}
		if (((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) || ((v != LevelEditorEntityParticleSystem_Emitter::NONE) && (v != LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) && (v != LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)))) {
			_Console::println(
				wstring(
					L"ParticleSystemScreenController::onParticleSystemEmitterApply(): unknown particle system emitter '" +
					particleSystem->getEmitter()->toWString() +
					L"'"
				)
			);
		}
		end_switch3:;
	}

	view->initParticleSystemRequest();
}

void ParticleSystemScreenController::onParticleSystemLoad()
{
	vector<wstring> extensions = {
		L"tps"
	};
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		particleSystemPath->getPath(),
		L"Load from: ",
		&extensions,
		view->getFileName(),
		new ParticleSystemScreenController_onParticleSystemLoad_2(this)
	);
}

void ParticleSystemScreenController::onEntitySave()
{
	auto fileName = view->getEntity()->getEntityFileName();
	if (fileName.length() == 0) {
		fileName = L"untitle.tps";
	}
	fileName = Tools::getFileName(fileName);
	vector<wstring> extensions = {
		L"tps"
	};
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		particleSystemPath->getPath(),
		L"Save from: ",
		&extensions,
		fileName,
		new ParticleSystemScreenController_onEntitySave_3(this)
);
}

void ParticleSystemScreenController::onParticleSystemReload()
{
	view->reloadFile();
}

void ParticleSystemScreenController::saveFile(const wstring& pathName, const wstring& fileName) /* throws(Exception) */
{
	view->saveFile(pathName, fileName);
}

void ParticleSystemScreenController::loadFile(const wstring& pathName, const wstring& fileName) /* throws(Exception) */
{
	view->loadFile(pathName, fileName);
}

void ParticleSystemScreenController::showErrorPopUp(const wstring& caption, const wstring& message)
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
				if (node->getId()->equals(L"button_entity_load")) {
					onParticleSystemLoad();
				} else
				if (node->getId()->equals(L"button_entity_reload")) {
					onParticleSystemReload();
				} else
				if (node->getId()->equals(L"button_entity_save")) {
					onEntitySave();
				} else
				if (node->getId()->equals(L"button_ps_type_apply")) {
					onParticleSystemTypeApply();
				} else
				if (node->getId()->equals(L"button_ops_apply") || node->getId()->equals(L"button_pps_type_apply")) {
					onParticleSystemTypeDataApply();
				} else
				if (node->getId()->equals(L"button_emitter_apply")) {
					onParticleSystemEmitterApply();
				} else
				if (node->getId()->equals(L"button_ppe_emitter_apply") || node->getId()->equals(L"button_bbpe_emitter_apply") || node->getId()->equals(L"button_cpe_emitter_apply")|| node->getId()->equals(L"button_cpepv_emitter_apply")|| node->getId()->equals(L"button_spe_emitter_apply")) {
					onParticleSystemEmitterDataApply();
				} else
				if (node->getId()->equals(L"button_ops_model_file")) {
					vector<wstring> extensions = {
						L"dae",
						L"tm"
					};
					view->getPopUpsViews()->getFileDialogScreenController()->show(
						modelPath->getPath(),
						L"Load from: ",
						&extensions,
						L"",
						new ParticleSystemScreenController_onActionPerformed_4(this)
					);
				} else {
					_Console::println(
						wstring(
							L"ModelViewerScreenController::onActionPerformed()::unknown, type='" +
							type->toWString() +
							L"', id = '" +
							node->getId()->getCPPWString() +
							L"'" +
							L", name = '" +
							node->getName()->getCPPWString() +
							L"'"
						)
					);
				}
				goto end_switch4;;
			}		}
		if ((v == GUIActionListener_Type::PERFORMED) || (v == GUIActionListener_Type::PERFORMING)) {
			{
				goto end_switch4;;
			}
		}
		end_switch4:;
	}

}
