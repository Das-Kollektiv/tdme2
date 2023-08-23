#include <tdme/engine/prototype/Prototype.h>

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

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

using std::make_unique;
using std::map;
using std::move;
using std::remove;
using std::string;
using std::unique_ptr;
using std::vector;

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
	this->model = unique_ptr<Model>(model);
	if (this->type == Prototype_Type::PARTICLESYSTEM) {
		this->physics = make_unique<PrototypePhysics>();
	} else
	if (this->type == Prototype_Type::MODEL) {
		if (model->getShaderModel() == ShaderModel::PBR || model->getShaderModel() == ShaderModel::SPECULARPBR) {
			shaderId = StringTools::startsWith(shaderId, "pbr-") == true || shaderId.empty() == true?shaderId:"pbr-" + shaderId;
		}
		this->physics = make_unique<PrototypePhysics>();
	} else
	if (this->type == Prototype_Type::TERRAIN) {
		this->terrain = make_unique<PrototypeTerrain>();
	} else
	if (this->type == Prototype_Type::DECAL) {
		this->decal = make_unique<PrototypeDecal>();
	}
}

Prototype::~Prototype() {
}

void Prototype::setModel(Model* model) {
	this->model = unique_ptr<Model>(model);
}

void Prototype::addBoundingVolume(PrototypeBoundingVolume* prototypeBoundingVolume)
{
	boundingVolumes.push_back(unique_ptr<PrototypeBoundingVolume>(prototypeBoundingVolume));
}

void Prototype::removeBoundingVolume(int idx)
{
	if (idx < 0 || idx >= boundingVolumes.size()) return;
	boundingVolumes.erase(boundingVolumes.begin() + idx);
}

void Prototype::setLODLevel2(PrototypeLODLevel* lodLevel) {
	if (this->type != Prototype_Type::MODEL) return;
	lodLevel2 = unique_ptr<PrototypeLODLevel>(lodLevel);
}

void Prototype::setLODLevel3(PrototypeLODLevel* lodLevel) {
	if (this->type != Prototype_Type::MODEL) return;
	lodLevel3 = unique_ptr<PrototypeLODLevel>(lodLevel);
}

void Prototype::removeLODLevel(int lodLevel) {
	if (lodLevel == 2) {
		lodLevel2 = nullptr;
		if (lodLevel3 != nullptr) {
			lodLevel2 = move(lodLevel3);
			lodLevel3 = nullptr;
		}
	} else
	if (lodLevel == 3) {
		lodLevel3 = nullptr;
	}
}

void Prototype::setImposterLOD(PrototypeImposterLOD* imposterLOD) {
	if (lodLevel2 != nullptr) {
		lodLevel2 = nullptr;
	}
	if (lodLevel3 != nullptr) {
		lodLevel3 = nullptr;
	}
	this->imposterLOD = unique_ptr<PrototypeImposterLOD>(imposterLOD);
}

void Prototype::addSound(PrototypeAudio* sound) {
	removeSound(sound->getId());
	sounds.push_back(unique_ptr<PrototypeAudio>(sound));
	soundsById[sound->getId()] = sound;
}
