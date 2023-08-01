#include <tdme/engine/prototype/Prototype.h>

#include <tdme/tdme.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ShaderModel.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeAudio.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/prototype/PrototypeDecal.h>
#include <tdme/engine/prototype/PrototypeLODLevel.h>
#include <tdme/engine/prototype/PrototypeParticleSystem.h>
#include <tdme/engine/prototype/PrototypePhysics.h>
#include <tdme/engine/prototype/PrototypeTerrain.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/StringTools.h>

using tdme::engine::model::Model;
using tdme::engine::model::ShaderModel;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeAudio;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::prototype::PrototypeParticleSystem;
using tdme::engine::prototype::PrototypeTerrain;
using tdme::math::Vector3;
using tdme::utilities::StringTools;

Prototype::Prototype(int id, Prototype_Type* entityType, const string& name, const string& description, const string& fileName, const string& modelFileName, const string& thumbnail, Model* model):
	BaseProperties(name, description)
{
	this->id = id;
	this->type = entityType;
	this->name = name;
	this->description = description;
	this->fileName = fileName;
	this->modelFileName = modelFileName;
	this->thumbnail = thumbnail;
	this->model = model;
	if (this->type == Prototype_Type::PARTICLESYSTEM) {
		this->physics = new PrototypePhysics();
	} else
	if (this->type == Prototype_Type::MODEL) {
		if (model->getShaderModel() == ShaderModel::PBR || model->getShaderModel() == ShaderModel::SPECULARPBR) {
			shaderId = StringTools::startsWith(shaderId, "pbr-") == true || shaderId.empty() == true?shaderId:"pbr-" + shaderId;
		}
		this->physics = new PrototypePhysics();
	} else
	if (this->type == Prototype_Type::TERRAIN) {
		this->terrain = new PrototypeTerrain();
	} else
	if (this->type == Prototype_Type::DECAL) {
		this->decal = new PrototypeDecal();
	}
}

Prototype::~Prototype() {
	if (model != nullptr) delete model;
	if (lodLevel2 != nullptr) delete lodLevel2;
	if (lodLevel3 != nullptr) delete lodLevel3;
	if (physics != nullptr) delete physics;
	for (auto particleSystem: particleSystems) delete particleSystem;
	for (auto boundingVolume: boundingVolumes) delete boundingVolume;
	for (auto sound: sounds) delete sound;
	if (terrain != nullptr) delete terrain;
	if (decal != nullptr) delete decal;
}

void Prototype::setModel(Model* model) {
	if (this->model == model) return;
	if (this->model != nullptr) delete this->model;
	this->model = model;
}

bool Prototype::addBoundingVolume(int idx, PrototypeBoundingVolume* prototypeBoundingVolume)
{
	if (idx < 0)
		return false;

	if (idx > boundingVolumes.size())
		return false;

	if (idx == boundingVolumes.size()) {
		boundingVolumes.push_back(prototypeBoundingVolume);
	}
	return false;
}

void Prototype::removeBoundingVolume(int idx)
{
	if (idx < 0 || idx >= boundingVolumes.size()) return;
	delete boundingVolumes[idx];
	boundingVolumes.erase(boundingVolumes.begin() + idx);
}

void Prototype::setLODLevel2(PrototypeLODLevel* lodLevel) {
	if (this->type != Prototype_Type::MODEL) return;
	if (lodLevel2 != nullptr) delete lodLevel2;
	lodLevel2 = lodLevel;
}

void Prototype::setLODLevel3(PrototypeLODLevel* lodLevel) {
	if (this->type != Prototype_Type::MODEL) return;
	if (lodLevel3 != nullptr) delete lodLevel3;
	lodLevel3 = lodLevel;
}

void Prototype::removeLODLevel(int lodLevel) {
	if (lodLevel == 2) {
		if (lodLevel2 != nullptr) {
			delete lodLevel2;
		}
		if (lodLevel3 == nullptr) {
			lodLevel2 = nullptr;
		} else {
			lodLevel2 = lodLevel3;
			lodLevel3 = nullptr;
		}
	} else
	if (lodLevel == 3) {
		if (lodLevel3 != nullptr) {
			delete lodLevel3;
		}
		lodLevel3 = nullptr;
	}
}

void Prototype::setImposterLOD(PrototypeImposterLOD* imposterLOD) {
	if (this->imposterLOD != nullptr) delete this->imposterLOD;
	if (lodLevel2 != nullptr) {
		delete lodLevel2;
		lodLevel2 = nullptr;
	}
	if (lodLevel3 != nullptr) {
		delete lodLevel3;
		lodLevel3 = nullptr;
	}
	this->imposterLOD = imposterLOD;
}

PrototypeAudio* Prototype::addSound(const string& id) {
	auto sound = getSound(id);
	if (sound != nullptr) return nullptr;
	auto audio = new PrototypeAudio(id);
	soundsById[id] = audio;
	sounds.push_back(audio);
	return audio;
}

