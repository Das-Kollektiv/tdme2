#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>

using std::string;
using std::unordered_map;

using tdme::engine::Texture;
using tdme::engine::subsystems::manager::TextureManager_TextureManaged;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::threading::Mutex;

/**
 * Texture manager
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::TextureManager final
{
	friend class TextureManager_TextureManaged;

private:
	Renderer* renderer { nullptr };
	unordered_map<string, TextureManager_TextureManaged*> textures;
	Mutex mutex;

public:
	// forbid class copy
	FORBID_CLASS_COPY(TextureManager)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	TextureManager(Renderer* renderer);

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
	TextureManager_TextureManaged* addTexture(const string& id, bool& created);

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
	 * Removes a texture from manager / open gl stack
	 * @param textureId texture id
	 */
	void removeTexture(const string& textureId);

};
