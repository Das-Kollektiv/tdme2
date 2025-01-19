#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>

using std::string;
using std::unordered_map;

using tdme::engine::Texture;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::os::threading::Mutex;

/**
 * Texture manager
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::TextureManager final
{
public:
	/**
	 * Managed texture entity
	 * @author Andreas Drewke
	 */
	class ManagedTexture
	{
		friend class TextureManager;

	private:
		string id;
		int32_t rendererId;
		int32_t referenceCounter { 0 };
		volatile bool uploaded { false };

		// forbid class copy
		FORBID_CLASS_COPY(ManagedTexture)

		/**
		 * Protected constructor
		 * @param id id
		 * @param rendererId renderer id
		 */
		ManagedTexture(const string& id, int32_t rendererId): id(id), rendererId(rendererId) {
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

	// forbid class copy
	FORBID_CLASS_COPY(TextureManager)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	TextureManager(RendererBackend* rendererBackend);

	/**
	 * Destructor
	 */
	~TextureManager();

	/**
	 * Adds a texture to manager
	 * @param id id
	 * @param created if managed texture has just been created
	 * @returns texture manager entity
	 */
	ManagedTexture* addTexture(const string& id, bool& created);

	/**
	 * Adds a texture to manager
	 * @param texture texture
	 * @param contextIdx context index
	 * @returns texture id
	 */
	int32_t addTexture(Texture* texture, int contextIdx = 0);

	/**
	 * Adds a cube map texture to manager
	 * @param id id
	 * @param textureLeft texture left
	 * @param textureRight texture right
	 * @param textureTop texture top
	 * @param textureBottom texture bottom
	 * @param textureFront texture front
	 * @param textureBack texture back
	 * @param contextIdx context index or nullptr if using default context
	 * @returns texture id
	 */
	int32_t addCubeMapTexture(const string& id, Texture* textureLeft, Texture* textureRight, Texture* textureTop, Texture* textureBottom, Texture* textureFront, Texture* textureBack, int contextIdx = 0);

	/**
	 * Removes a texture from manager
	 * @param texture texture
	 */
	inline void removeTexture(Texture* texture) {
		removeTexture(texture->getId());
	}

	/**
	 * Removes a texture from manager
	 * @param textureId texture id
	 */
	void removeTexture(const string& textureId);

private:
	RendererBackend* rendererBackend { nullptr };
	unordered_map<string, ManagedTexture*> textures;
	Mutex mutex;

};
