#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::os::threading::ReadWriteLock;

/**
 * VBO manager
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::VBOManager final
{

public:
	/**
	 * Managed VBO
	 */
	class ManagedVBO
	{
		friend class VBOManager;

	private:
		string id;
		vector<int32_t> vboIds;
		int32_t referenceCounter { 0 };
		volatile bool uploaded { false };

		/**
		 * Private constructor
		 * @param id id
		 * @param vboIds VBO ids
		 */
		ManagedVBO(const string& id, vector<int32_t>& vboIds): id(id), vboIds(vboIds) {
			//
		}

	public:
		// forbid class copy
		FORBID_CLASS_COPY(ManagedVBO)

		/**
		 * @return vbo id
		 */
		inline const string& getId() {
			return id;
		}

		/**
		 * @return vbo gl ids
		 */
		inline vector<int32_t>* getVBOIds() {
			return &vboIds;
		}

		/**
		 * @return reference counter
		 */
		inline int32_t getReferenceCounter() {
			return referenceCounter;
		}

		/**
		 * Set uploaded
		 * @param uploaded uploaded
		 */
		inline void setUploaded(bool uploaded) {
			this->uploaded = uploaded;
		}

		/**
		 * @return if vbo's have been uploaded
		 */
		inline bool isUploaded() {
			return uploaded;
		}

	private:
		/**
		 * decrement reference counter
		 * @return if reference counter = 0
		 */
		inline bool decrementReferenceCounter() {
			referenceCounter--;
			return referenceCounter == 0;
		}

		/**
		 * increment reference counter
		 */
		inline void incrementReferenceCounter() {
			referenceCounter++;
		}
	};

public:

	// forbid class copy
	FORBID_CLASS_COPY(VBOManager)

	/**
	 * Public constructor
	 */
	VBOManager(RendererBackend* rendererBackend);

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
	ManagedVBO* addVBO(const string& vboId, int32_t ids, bool useGPUMemory, bool shared, bool& created);

	/**
	 * Retrieves a VBO managed from manager
	 * @param vboId VBO id
	 * @return VBO managed or nullptr
	 */
	ManagedVBO* getVBO(const string& vboId);

	/**
	 * Removes a VBO from manager
	 * @param vboId VBO id
	 */
	void removeVBO(const string& vboId);

private:
	RendererBackend* rendererBackend { nullptr };
	unordered_map<string, ManagedVBO*> vbos;
	ReadWriteLock rwLock;

};
