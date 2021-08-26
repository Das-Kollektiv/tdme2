#include <tdme/tools/editor/tabcontrollers/ParticleSystemEditorTabController.h>

#include <string>

#include <tdme/engine/prototype/PrototypeParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_BoundingBoxParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_Emitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_FogParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_ObjectParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_SphereParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_Type.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>
#include <tdme/tools/editor/tabviews/ParticleSystemEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::tools::editor::tabcontrollers::ParticleSystemEditorTabController;

using tdme::utilities::Action;
using tdme::engine::prototype::PrototypeParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_BoundingBoxParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::engine::prototype::PrototypeParticleSystem_Emitter;
using tdme::engine::prototype::PrototypeParticleSystem_FogParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_ObjectParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_PointParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_PointParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_SphereParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_Type;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;
using tdme::tools::editor::tabviews::ParticleSystemEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

ParticleSystemEditorTabController::ParticleSystemEditorTabController(ParticleSystemEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->basePropertiesSubController = new BasePropertiesSubController(view->getEditorView(), "prototype");
	this->prototypePhysicsSubController = new PrototypePhysicsSubController(view->getEditorView(), view, &modelPath, false);
	this->prototypeSoundsSubController = new PrototypeSoundsSubController(view->getEditorView(), view, &audioPath);
}

ParticleSystemEditorTabController::~ParticleSystemEditorTabController() {
	delete basePropertiesSubController;
	delete prototypePhysicsSubController;
	delete prototypeSoundsSubController;
}

ParticleSystemEditorTabView* ParticleSystemEditorTabController::getView() {
	return view;
}

GUIScreenNode* ParticleSystemEditorTabController::getScreenNode()
{
	return screenNode;
}

void ParticleSystemEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
	prototypePhysicsSubController->initialize(screenNode);
	prototypeSoundsSubController->initialize(screenNode);
	setOutlinerContent();
}

void ParticleSystemEditorTabController::dispose()
{
}

void ParticleSystemEditorTabController::save()
{
}

void ParticleSystemEditorTabController::saveAs()
{
}

void ParticleSystemEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void ParticleSystemEditorTabController::onValueChanged(GUIElementNode* node)
{
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		updateDetails(outlinerNode);
	}
	basePropertiesSubController->onValueChanged(node, view->getPrototype());
	prototypePhysicsSubController->onValueChanged(node, view->getPrototype());
	prototypeSoundsSubController->onValueChanged(node, view->getPrototype(), nullptr);
}

void ParticleSystemEditorTabController::onFocus(GUIElementNode* node) {
	basePropertiesSubController->onFocus(node, view->getPrototype());
	prototypeSoundsSubController->onFocus(node, view->getPrototype());
}

void ParticleSystemEditorTabController::onUnfocus(GUIElementNode* node) {
	basePropertiesSubController->onUnfocus(node, view->getPrototype());
	prototypeSoundsSubController->onUnfocus(node, view->getPrototype());
}

void ParticleSystemEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
	basePropertiesSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
	prototypePhysicsSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
	prototypeSoundsSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
}

void ParticleSystemEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	auto prototype = view->getPrototype();
	basePropertiesSubController->onActionPerformed(type, node, prototype);
	prototypePhysicsSubController->onActionPerformed(type, node, prototype);
	prototypeSoundsSubController->onActionPerformed(type, node, prototype);
}

void ParticleSystemEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototype") + "\" value=\"" + GUIParser::escapeQuotes("prototype") + "\">\n";
	auto prototype = view->getPrototype();
	if (prototype != nullptr) {
		basePropertiesSubController->createBasePropertiesXML(prototype, xml);
		prototypePhysicsSubController->createOutlinerPhysicsXML(prototype, xml);
		prototypeSoundsSubController->createOutlinerSoundsXML(prototype, xml);
		//
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Particle Systems") + "\" value=\"" + GUIParser::escapeQuotes("particlesystems") + "\">\n";
		for (auto i = 0; i < prototype->getParticleSystemsCount(); i++) {
			auto particleSystem = prototype->getParticleSystemAt(i);
			xml+= "	<selectbox-option image=\"resources/engine/images/particle.png\" text=\"" + GUIParser::escapeQuotes("Particle System " + to_string(i)) + "\" id=\"" + GUIParser::escapeQuotes("particlesystems." + to_string(i)) + "\" value=\"" + GUIParser::escapeQuotes("particlesystems." + to_string(i)) + "\" />\n";
		}
		xml+= "</selectbox-parent-option>\n";
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void ParticleSystemEditorTabController::setParticleSystemDetails(int particleSystemIdx) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
	if (particleSystem == nullptr) return;

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_particletype\" src=\"resources/engine/gui/template_details_particletype.xml\" />\n") +
		string("<template id=\"details_particleemitter\" src=\"resources/engine/gui/template_details_particleemitter.xml\" />\n")
	);

	//
	try {
		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_particletype"))->getActiveConditions().add("open");

		//
		if (particleSystem->getType() == PrototypeParticleSystem_Type::NONE) {
		} else
		if (particleSystem->getType() == PrototypeParticleSystem_Type::FOG_PARTICLE_SYSTEM) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): fps");
		} else
		if (particleSystem->getType() == PrototypeParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): ops");
		} else
		if (particleSystem->getType() == PrototypeParticleSystem_Type::POINT_PARTICLE_SYSTEM) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): pps");
			auto pps = particleSystem->getPointParticleSystem();
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_type"))->getController()->setValue(MutableString(2));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_type_details"))->getActiveConditions().set("point");
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_point_texture"))->setSource(pps->getTextureFileName());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particletype_point_transparency"))->setSource(pps->getTransparencyTextureFileName());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_size"))->getController()->setValue(MutableString(pps->getPointSize()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_maxcount"))->getController()->setValue(MutableString(pps->getMaxPoints()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_horizontal_sprites"))->getController()->setValue(MutableString(pps->getTextureHorizontalSprites()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_vertical_sprites"))->getController()->setValue(MutableString(pps->getTextureVerticalSprites()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_fps"))->getController()->setValue(MutableString(pps->getTextureSpritesFPS()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particletype_point_autoemit"))->getController()->setValue(MutableString(pps->isAutoEmit() == true?"1":""));
		} else {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): Unknown particle system type");
		}

		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_particleemitter"))->getActiveConditions().add("open");

		//
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): bbpe");
			auto bbpe = particleSystem->getBoundingBoxParticleEmitters();

			Matrix4x4 rotationMatrix;
			rotationMatrix.identity();
			rotationMatrix.setAxes(bbpe->getObbAxis0(), bbpe->getObbAxis1(), bbpe->getObbAxis2());
			auto rotation = rotationMatrix.computeEulerAngles();

			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type"))->getController()->setValue(MutableString(2));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_type_details"))->getActiveConditions().set("box");
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_x"))->getController()->setValue(MutableString(bbpe->getObbCenter().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_y"))->getController()->setValue(MutableString(bbpe->getObbCenter().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_location_z"))->getController()->setValue(MutableString(bbpe->getObbCenter().getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_x"))->getController()->setValue(MutableString(rotation.getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_y"))->getController()->setValue(MutableString(rotation.getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_rotation_z"))->getController()->setValue(MutableString(rotation.getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_x"))->getController()->setValue(MutableString(bbpe->getObbHalfextension().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_y"))->getController()->setValue(MutableString(bbpe->getObbHalfextension().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_halfsize_z"))->getController()->setValue(MutableString(bbpe->getObbHalfextension().getZ()));
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_box_colorstart"))->setEffectColorMul(bbpe->getColorStart());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_box_colorend"))->setEffectColorMul(bbpe->getColorEnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_count"))->getController()->setValue(MutableString(bbpe->getCount()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_lifetime_min"))->getController()->setValue(MutableString(static_cast<int32_t>(bbpe->getLifeTime())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_lifetime_max"))->getController()->setValue(MutableString(static_cast<int32_t>(bbpe->getLifeTime() + bbpe->getLifeTimeRnd())));
			auto velocityMax = bbpe->getVelocity().clone().add(bbpe->getVelocityRnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_min_x"))->getController()->setValue(MutableString(bbpe->getVelocity().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_min_y"))->getController()->setValue(MutableString(bbpe->getVelocity().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_min_z"))->getController()->setValue(MutableString(bbpe->getVelocity().getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_max_x"))->getController()->setValue(MutableString(velocityMax.getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_max_y"))->getController()->setValue(MutableString(velocityMax.getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_velocity_max_z"))->getController()->setValue(MutableString(velocityMax.getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_mass_min"))->getController()->setValue(MutableString(static_cast<int32_t>(bbpe->getMass())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_box_mass_max"))->getController()->setValue(MutableString(static_cast<int32_t>(bbpe->getMass() + bbpe->getMassRnd())));
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): cpe");
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): cpepv");
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::POINT_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): ppe");
			auto ppse = particleSystem->getPointParticleEmitter();
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_x"))->getController()->setValue(MutableString(ppse->getPosition().getX()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_y"))->getController()->setValue(MutableString(ppse->getPosition().getY()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_location_z"))->getController()->setValue(MutableString(ppse->getPosition().getZ()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_colorstart"))->getController()->setValue(MutableString(0.0f));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_colorend"))->getController()->setValue(MutableString(0.0f));
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_point_colorstart"))->setEffectColorMul(ppse->getColorStart());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("particleemitter_point_colorend"))->setEffectColorMul(ppse->getColorEnd());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_count"))->getController()->setValue(MutableString(ppse->getCount()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_lifetime_min"))->getController()->setValue(MutableString(static_cast<int32_t>(ppse->getLifeTime())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_lifetime_max"))->getController()->setValue(MutableString(static_cast<int32_t>(ppse->getLifeTime() + ppse->getLifeTimeRnd())));
			// TODO:
			// required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_min_x"))->getController()->setValue(MutableString(0.0f));
			// required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_min_y"))->getController()->setValue(MutableString(0.0f));
			// required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_min_z"))->getController()->setValue(MutableString(0.0f));
			// required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_max_x"))->getController()->setValue(MutableString(0.0f));
			// required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_max_y"))->getController()->setValue(MutableString(0.0f));
			// required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_velocity_max_z"))->getController()->setValue(MutableString(0.0f));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_mass_min"))->getController()->setValue(MutableString(static_cast<int32_t>(ppse->getMass())));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("particleemitter_point_mass_max"))->getController()->setValue(MutableString(static_cast<int32_t>(ppse->getMass() + ppse->getMassRnd())));
		} else
		if (particleSystem->getEmitter() == PrototypeParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) {
			Console::println("ParticleSystemEditorTabController::setParticleSystemDetails(): spe");
		}
	} catch (Exception& exception) {
		Console::println(string("ParticleSystemEditorTabController::setParticleSystemDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ParticleSystemEditorTabController::updateDetails(const string& outlinerNode) {
	if (StringTools::startsWith(outlinerNode, "particlesystems.") == true) {
		auto particleSystemIdx = Integer::parseInt(StringTools::substring(outlinerNode, string("particlesystems.").size(), outlinerNode.size()));
		setParticleSystemDetails(particleSystemIdx);
	}
	prototypePhysicsSubController->updateDetails(view->getPrototype(), outlinerNode);
	prototypeSoundsSubController->updateDetails(view->getPrototype(), nullptr, outlinerNode);
}
