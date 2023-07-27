#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unordered_map;

using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::threading::ReadWriteLock;

/**
 * VBO manager
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::VBOManager final
{
	friend class VBOManager_VBOManaged;

private:
	Renderer* renderer { nullptr };
	unordered_map<string, VBOManager_VBOManaged*> vbos;
	ReadWriteLock rwLock;

public:
	// forbid class copy
	FORBID_CLASS_COPY(VBOManager)

	/**
	 * Public constructor
	 */
	VBOManager(Renderer* renderer);

	/**
	 * Destructor
	 */
	~VBOManager();

	/**
	 * Adds a VBO to manager or retrieve VBO if existing
	 * @param vboId VBO id
	 * @param ids VBOs to allocate
	 * @param useGPUMemory use GPU memory
	 * @param shared shared between different threads
	 * @param created returns if VBO was just created
	 */
	VBOManager_VBOManaged* addVBO(const string& vboId, int32_t ids, bool useGPUMemory, bool shared, bool& created);

	/**
	 * Retrieves a VBO managed from manager
	 * @param vboId VBO id
	 * @return VBO managed or nullptr
	 */
	VBOManager_VBOManaged* getVBO(const string& vboId);

	/**
	 * Removes a VBO from manager
	 * @param vboId VBO id
	 */
	void removeVBO(const string& vboId);

};
