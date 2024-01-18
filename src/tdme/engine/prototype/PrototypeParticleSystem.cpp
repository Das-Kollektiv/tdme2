#include <tdme/engine/prototype/PrototypeParticleSystem.h>

#include <memory>

#include <tdme/tdme.h>
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
#include <tdme/utilities/Console.h>

using std::make_unique;
using std::unique_ptr;

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
using tdme::utilities::Console;

PrototypeParticleSystem::PrototypeParticleSystem()
{
	type = PrototypeParticleSystem_Type::NONE;
	emitter = PrototypeParticleSystem_Emitter::NONE;
}

PrototypeParticleSystem::~PrototypeParticleSystem() {
	unsetType();
	unsetEmitter();
}

void PrototypeParticleSystem::unsetType() {
	if (type == PrototypeParticleSystem_Type::NONE) {
	} else
	if (type == PrototypeParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) {
		ops = nullptr;
	} else
	if (type == PrototypeParticleSystem_Type::POINT_PARTICLE_SYSTEM) {
		pps = nullptr;
	} else
	if (type == PrototypeParticleSystem_Type::FOG_PARTICLE_SYSTEM) {
		fps = nullptr;
	} else {
		Console::printLine(string("PrototypeParticleSystem::setType(): unknown type '" + this->type->getName() + "'"));
	}
}

void PrototypeParticleSystem::setType(PrototypeParticleSystem_Type* type)
{
	unsetType();
	this->type = type;
	if (type == PrototypeParticleSystem_Type::NONE) {
		// no op
	} else
	if (type == PrototypeParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) {
		ops = make_unique<PrototypeParticleSystem_ObjectParticleSystem>();
	} else
	if (type == PrototypeParticleSystem_Type::POINT_PARTICLE_SYSTEM) {
		pps = make_unique<PrototypeParticleSystem_PointParticleSystem>();
	} else
	if (type == PrototypeParticleSystem_Type::FOG_PARTICLE_SYSTEM) {
		fps = make_unique<PrototypeParticleSystem_FogParticleSystem>();
	} else {
		Console::printLine(string("PrototypeParticleSystem::setType(): unknown type '" + this->type->getName() + "'"));
	}
}

void PrototypeParticleSystem::unsetEmitter() {
	if (emitter == PrototypeParticleSystem_Emitter::NONE) {
		// no op
	} else
	if (emitter == PrototypeParticleSystem_Emitter::POINT_PARTICLE_EMITTER) {
		ppe = nullptr;
	} else
	if (emitter == PrototypeParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) {
		bbpe = nullptr;
	} else
	if (emitter == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) {
		cpe = nullptr;
	} else
	if (emitter == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
		cpepv = nullptr;
	} else
	if (emitter == PrototypeParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) {
		spe = nullptr;
	} else {
		Console::printLine(string("PrototypeParticleSystem::setEmitter(): unknown emitter '" + this->emitter->getName() + "'"));
	}
}

void PrototypeParticleSystem::setEmitter(PrototypeParticleSystem_Emitter* emitter)
{
	unsetEmitter();
	this->emitter = emitter;
	if (emitter == PrototypeParticleSystem_Emitter::NONE) {
		// no op
	} else
	if (emitter == PrototypeParticleSystem_Emitter::POINT_PARTICLE_EMITTER) {
		ppe = make_unique<PrototypeParticleSystem_PointParticleEmitter>();
	} else
	if (emitter == PrototypeParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) {
		bbpe = make_unique<PrototypeParticleSystem_BoundingBoxParticleEmitter>();
	} else
	if (emitter == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) {
		cpe = make_unique<PrototypeParticleSystem_CircleParticleEmitter>();
	} else
	if (emitter == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
		cpepv = make_unique<PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity>();
	} else
	if (emitter == PrototypeParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) {
		spe = make_unique<PrototypeParticleSystem_SphereParticleEmitter>();
	} else {
		Console::printLine(string("PrototypeParticleSystem::setEmitter(): unknown emitter '" + this->emitter->getName() + "'"));
	}
}
