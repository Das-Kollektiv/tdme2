#include <agui/gui/vbos/GUIVBOManager.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/renderer/GUIRendererBackend.h>
#include <agui/os/threading/ReadWriteLock.h>
#include <agui/utilities/Console.h>

using std::string;
using std::unordered_map;

using agui::gui::renderer::GUIRendererBackend;
using agui::gui::vbos::GUIVBOManager;
using agui::os::threading::ReadWriteLock;
using agui::utilities::Console;

GUIVBOManager::GUIVBOManager(GUIRendererBackend* renderer): rwLock("vbomanager-rwlock") {
	this->renderer = renderer;
}

GUIVBOManager::~GUIVBOManager() {
	for (auto it = vbos.begin(); it != vbos.end(); ++it) {
		delete it->second;
	}
}

GUIVBOManager::GUIManagedVBO* GUIVBOManager::addVBO(const string& vboId, int32_t ids, bool useGPUMemory, bool shared, bool& created) {
	rwLock.writeLock();
	// check if we already manage this vbo
	auto vboManagedIt = vbos.find(vboId);
	if (vboManagedIt != vbos.end()) {
		auto vboManaged = vboManagedIt->second;
		vboManaged->incrementReferenceCounter();
		rwLock.unlock();
		// yep, return vbo managed
		created = false;
		return vboManaged;
	}
	// create vertex buffer objects
	auto vboIds = renderer->createBufferObjects(ids, useGPUMemory, shared);
	// create managed texture
	auto vboManaged = new GUIManagedVBO(vboId, vboIds);
	// add it to our textures
	vboManaged->incrementReferenceCounter();
	vbos[vboManaged->getId()] = vboManaged;
	rwLock.unlock();
	created = true;

	// return vbo managed
	return vboManaged;
}

GUIVBOManager::GUIManagedVBO* GUIVBOManager::getVBO(const string& vboId) {
	rwLock.readLock();
	// check if we already manage this vbo
	auto vboManagedIt = vbos.find(vboId);
	if (vboManagedIt != vbos.end()) {
		auto vboManaged = vboManagedIt->second;
		vboManaged->incrementReferenceCounter();
		rwLock.unlock();
		// yep, return vbo managed
		return vboManaged;
	}
	// nope
	rwLock.unlock();
	return nullptr;
}

void GUIVBOManager::removeVBO(const string& vboId) {
	rwLock.writeLock();
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
		rwLock.unlock();
		return;
	}
	rwLock.unlock();
	Console::printLine(string("Warning: vbo not managed by vbo manager: ") + vboId);
}
