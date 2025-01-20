#pragma once

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/gui/renderer/GUIRendererBackend.h>
#include <agui/os/threading/Mutex.h>

using std::string;
using std::unordered_map;

// namespaces
namespace agui {
namespace gui {
namespace textures {
	using ::agui::gui::renderer::GUIRendererBackend;
	using ::agui::os::threading::Mutex;
}
}
}

/**
 * GUITexture manager
 * @author Andreas Drewke
 */
class agui::gui::textures::GUITextureManager final
{
public:
	/**
	 * GUI managed texture
	 */
	class GUIManagedTexture
	{
		friend class GUITextureManager;

	private:
		string id;
		int32_t rendererId;
		int32_t referenceCounter { 0 };
		volatile bool uploaded { false };

	private:
		// forbid class copy
		FORBID_CLASS_COPY(GUIManagedTexture)

		/**
		 * Protected constructor
		 * @param id id
		 * @param rendererId renderer id
		 */
		GUIManagedTexture(const string& id, int32_t rendererId): id(id), rendererId(rendererId) {
			//
		}

	public:
		/**
		 * @returns texture id
		 */
		inline const string& getId() {
			return id;
		}

		/**
		 * @returns reference counter
		 */
		inline int32_t getReferenceCounter() {
			return referenceCounter;
		}

		/**
		 * @returns texture renderer id
		 */
		inline int32_t getRendererId() {
			return rendererId;
		}

		/**
		 * Set uploaded
		 * @param uploaded uploaded
		 */
		inline void setUploaded(bool uploaded) {
			this->uploaded = uploaded;
		}

		/**
		 * @returns if texture has been uploaded
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
	unordered_map<string, GUIManagedTexture*> textures;
	Mutex mutex;

public:
	// forbid class copy
	FORBID_CLASS_COPY(GUITextureManager)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	GUITextureManager(GUIRendererBackend* renderer);

	/**
	 * Destructor
	 */
	~GUITextureManager();

	/**
	 * Adds a texture to manager
	 * @param id id
	 * @param created if managed texture has just been created
	 * @returns texture manager entity
	 */
	GUIManagedTexture* addTexture(const string& id, bool& created);

	/**
	 * Adds a texture to manager
	 * @param texture texture
	 * @param contextIdx context index
	 * @returns texture id
	 */
	int32_t addTexture(GUITexture* texture, int contextIdx = 0);

	/**
	 * Removes a texture from manager
	 * @param texture texture
	 */
	inline void removeTexture(GUITexture* texture) {
		removeTexture(texture->getId());
	}

	/**
	 * Removes a texture from manager
	 * @param textureId texture id
	 */
	void removeTexture(const string& textureId);

};
