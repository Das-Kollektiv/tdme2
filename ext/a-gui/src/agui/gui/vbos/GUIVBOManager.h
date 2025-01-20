#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/vbos/fwd-agui.h>
#include <agui/gui/renderer/fwd-agui.h>
#include <agui/os/threading/ReadWriteLock.h>
#include <agui/utilities/fwd-agui.h>

using std::string;
using std::unordered_map;
using std::vector;

// namespaces
namespace agui {
namespace gui {
namespace vbos {
	using ::agui::gui::renderer::GUIRendererBackend;
	using ::agui::os::threading::ReadWriteLock;
}
}
}

/**
 * VBO manager
 * @author Andreas Drewke
 */
class agui::gui::vbos::GUIVBOManager final
{
public:
	class GUIManagedVBO
	{
		friend class GUIVBOManager;
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
		GUIManagedVBO(const string& id, vector<int32_t>& vboIds): id(id), vboIds(vboIds) {
			//
		}

	public:
		// forbid class copy
		FORBID_CLASS_COPY(GUIManagedVBO)

		/**
		 * @returns vbo id
		 */
		inline const string& getId() {
			return id;
		}

		/**
		 * @returns vbo gl ids
		 */
		inline vector<int32_t>* getVBOIds() {
			return &vboIds;
		}

		/**
		 * @returns reference counter
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
		 * @returns if vbo's have been uploaded
		 */
		inline bool isUploaded() {
			return uploaded;
		}

	private:
		/**
		 * decrement reference counter
		 * @returns if reference counter = 0
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

private:
	GUIRendererBackend* renderer { nullptr };
	unordered_map<string, GUIManagedVBO*> vbos;
	ReadWriteLock rwLock;

public:
	// forbid class copy
	FORBID_CLASS_COPY(GUIVBOManager)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	GUIVBOManager(GUIRendererBackend* renderer);

	/**
	 * Destructor
	 */
	~GUIVBOManager();

	/**
	 * Adds a VBO to manager or retrieve VBO if existing
	 * @param vboId VBO id
	 * @param ids VBOs to allocate
	 * @param useGPUMemory use GPU memory
	 * @param shared shared between different threads
	 * @param created returns if VBO was just created
	 */
	GUIManagedVBO* addVBO(const string& vboId, int32_t ids, bool useGPUMemory, bool shared, bool& created);

	/**
	 * Retrieves a VBO managed from manager
	 * @param vboId VBO id
	 * @returns VBO managed or nullptr
	 */
	GUIManagedVBO* getVBO(const string& vboId);

	/**
	 * Removes a VBO from manager
	 * @param vboId VBO id
	 */
	void removeVBO(const string& vboId);

};
