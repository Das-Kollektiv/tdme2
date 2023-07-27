#include <tdme/engine/scene/SceneLibrary.h>

#include <algorithm>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Primitives.h>
#include <tdme/utilities/StringTools.h>

using std::remove;
using std::string;
using std::to_string;

using tdme::engine::scene::SceneLibrary;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::scene::Scene;
using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Primitives;
using tdme::utilities::StringTools;

SceneLibrary::SceneLibrary(Scene* scene)
{
	this->scene = scene;
	this->prototypeIdx = 0;
}

SceneLibrary::~SceneLibrary() {
	for (auto prototype: prototypes) {
		delete prototype;
	}
}

void SceneLibrary::clear()
{
	for (auto prototype: prototypes) {
		delete prototype;
	}
	this->prototypesById.clear();
	this->prototypes.clear();
	this->prototypeIdx = 0;
}

void SceneLibrary::addPrototype(Prototype* prototype)
{
	if (prototype->getId() == SceneLibrary::ID_ALLOCATE) prototype->setId(allocatePrototypeId());
	auto prototypeByIdIt = prototypesById.find(prototype->getId());
	if (prototypeByIdIt != prototypesById.end()) {
		throw ExceptionBase("Prototype id already in use");
	}
	prototypes.push_back(prototype);
	prototypesById[prototype->getId()] = prototype;
	if (prototype->getId() >= prototypeIdx)
		prototypeIdx = prototype->getId() + 1;

}

void SceneLibrary::removePrototype(int id)
{
	auto prototypeByIdIt = prototypesById.find(id);
	if (prototypeByIdIt != prototypesById.end()) {
		prototypes.erase(remove(prototypes.begin(), prototypes.end(), prototypeByIdIt->second), prototypes.end());
		delete prototypeByIdIt->second;
		prototypesById.erase(prototypeByIdIt);
	}
}
