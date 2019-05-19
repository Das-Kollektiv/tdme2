#include <tdme/engine/subsystems/manager/VBOManager.h>

#include <map>
#include <string>

#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/utils/Console.h>

using std::map;
using std::string;

using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::utils::Console;

VBOManager::VBOManager(Renderer* renderer): mutex("vbomanager-mutex") {
	this->renderer = renderer;
}

VBOManager::~VBOManager() {
	for (auto it = vbos.begin(); it != vbos.end(); ++it) {
		delete it->second;
	}
}

VBOManager_VBOManaged* VBOManager::addVBO(const string& vboId, int32_t ids, bool useGPUMemory) {
	mutex.lock();
	// check if we already manage this vbo
	auto vboManagedIt = vbos.find(vboId);
	if (vboManagedIt != vbos.end()) {
		auto vboManaged = vboManagedIt->second;
		vboManaged->incrementReferenceCounter();
		mutex.unlock();
		// yep, return vbo managed
		return vboManaged;
	}
	// create vertex buffer objects
	auto vboIds = renderer->createBufferObjects(ids, useGPUMemory);
	// create managed texture
	auto vboManaged = new VBOManager_VBOManaged(vboId, vboIds);
	// add it to our textures
	vboManaged->incrementReferenceCounter();
	vbos[vboManaged->getId()] = vboManaged;
	mutex.unlock();
	// return vbo managed
	return vboManaged;
}

void VBOManager::removeVBO(const string& vboId) {
	mutex.lock();
	auto vboManagedIt = vbos.find(vboId);
	if (vboManagedIt != vbos.end()) {
		auto vboManaged = vboManagedIt->second;
		if (vboManaged->decrementReferenceCounter()) {
			auto vboIds = vboManaged->getVBOIds();
			// delete vbos from renderer
			renderer->disposeBufferObjects(*vboIds);
			// remove from our list
			vbos.erase(vboManagedIt);
			delete vboManaged;
		}
		mutex.unlock();
		return;
	}
	mutex.unlock();
	Console::println(string("Warning: vbo not managed by vbo manager: ") + vboId);
}
