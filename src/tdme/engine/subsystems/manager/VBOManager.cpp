#include <tdme/engine/subsystems/manager/VBOManager.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::unordered_map;

using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::os::threading::ReadWriteLock;
using tdme::utilities::Console;

VBOManager::VBOManager(RendererBackend* rendererBackend): rwLock("vbomanager-rwlock") {
	this->rendererBackend = rendererBackend;
}

VBOManager::~VBOManager() {
	for (auto it = vbos.begin(); it != vbos.end(); ++it) {
		delete it->second;
	}
}

VBOManager::ManagedVBO* VBOManager::addVBO(const string& vboId, int32_t ids, bool useGPUMemory, bool shared, bool& created) {
	rwLock.writeLock();
	// check if we already manage this vbo
	auto managedVBOIt = vbos.find(vboId);
	if (managedVBOIt != vbos.end()) {
		auto vboManaged = managedVBOIt->second;
		vboManaged->incrementReferenceCounter();
		rwLock.unlock();
		// yep, return vbo managed
		created = false;
		return vboManaged;
	}
	// create vertex buffer objects
	auto vboIds = rendererBackend->createBufferObjects(ids, useGPUMemory, shared);
	// create managed texture
	auto managedVBO = new ManagedVBO(vboId, vboIds);
	// add it to our textures
	managedVBO->incrementReferenceCounter();
	vbos[managedVBO->getId()] = managedVBO;
	rwLock.unlock();
	created = true;

	// return vbo managed
	return managedVBO;
}

VBOManager::ManagedVBO* VBOManager::getVBO(const string& vboId) {
	rwLock.readLock();
	// check if we already manage this vbo
	auto managedVBOIt = vbos.find(vboId);
	if (managedVBOIt != vbos.end()) {
		auto vboManaged = managedVBOIt->second;
		vboManaged->incrementReferenceCounter();
		rwLock.unlock();
		// yep, return vbo managed
		return vboManaged;
	}
	// nope
	rwLock.unlock();
	return nullptr;
}

void VBOManager::removeVBO(const string& vboId) {
	rwLock.writeLock();
	auto managedVBOIt = vbos.find(vboId);
	if (managedVBOIt != vbos.end()) {
		auto vboManaged = managedVBOIt->second;
		if (vboManaged->decrementReferenceCounter()) {
			auto vboIds = vboManaged->getVBOIds();
			// delete vbos from renderer
			rendererBackend->disposeBufferObjects(*vboIds);
			// remove from our list
			vbos.erase(managedVBOIt);
			delete vboManaged;
		}
		rwLock.unlock();
		return;
	}
	rwLock.unlock();
	Console::printLine(string("Warning: vbo not managed by vbo manager: ") + vboId);
}
