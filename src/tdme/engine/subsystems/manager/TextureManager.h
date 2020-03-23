#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/os/threading/Mutex.h>

using std::map;
using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager_TextureManaged;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::threading::Mutex;

/** 
 * Texture manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::manager::TextureManager final
{
	friend class TextureManager_TextureManaged;

public:
	enum TextureType {
		TEXTURETYPE_TEXTURE,
		TEXTURETYPE_CUBEMAP_POSITIVE_X,
		TEXTURETYPE_CUBEMAP_NEGATIVE_X,
		TEXTURETYPE_CUBEMAP_POSITIVE_Y,
		TEXTURETYPE_CUBEMAP_NEGATIVE_Y,
		TEXTURETYPE_CUBEMAP_POSITIVE_Z,
		TEXTURETYPE_CUBEMAP_NEGATIVE_Z
	};

private:
	Renderer* renderer { nullptr };
	map<string, TextureManager_TextureManaged*> textures;
	Mutex mutex;

	/**
	 * @return renderer texture type
	 */
	inline int32_t getTextureType(TextureType textureType) {
		switch(textureType){
			case TEXTURETYPE_TEXTURE: return renderer->TEXTURETYPE_TEXTURE;
			case TEXTURETYPE_CUBEMAP_POSITIVE_X: return renderer->TEXTURETYPE_CUBEMAP_POSITIVE_X;
			case TEXTURETYPE_CUBEMAP_NEGATIVE_X: return renderer->TEXTURETYPE_CUBEMAP_NEGATIVE_X;
			case TEXTURETYPE_CUBEMAP_POSITIVE_Y: return renderer->TEXTURETYPE_CUBEMAP_POSITIVE_Y;
			case TEXTURETYPE_CUBEMAP_NEGATIVE_Y: return renderer->TEXTURETYPE_CUBEMAP_NEGATIVE_Y;
			case TEXTURETYPE_CUBEMAP_POSITIVE_Z: return renderer->TEXTURETYPE_CUBEMAP_POSITIVE_Z;
			case TEXTURETYPE_CUBEMAP_NEGATIVE_Z: return renderer->TEXTURETYPE_CUBEMAP_NEGATIVE_Z;
			default: return -1;
		}
	}

public:

	/**
	 * Adds a texture to manager
	 * @param id id
	 * @param textureType texture type
	 * @param created if managed texture has just been created
	 * @returns texture manager entity
	 */
	TextureManager_TextureManaged* addTexture(const string& id, TextureType textureType, bool& created);

	/** 
	 * Adds a texture to manager
	 * @param texture texture
	 * @param textureType texture type
	 * @param context context or nullptr if using default context
	 * @returns texture id
	 */
	int32_t addTexture(Texture* texture, TextureType textureType, void* context = nullptr);

	/** 
	 * Removes a texture from manager / open gl stack
	 * @param textureId texture id
	 */
	void removeTexture(const string& textureId);

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	TextureManager(Renderer* renderer);

	/**
	 * Destructor
	 */
	~TextureManager();
};
