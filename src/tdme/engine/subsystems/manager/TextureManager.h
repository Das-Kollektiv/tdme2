#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager_TextureManaged;
using tdme::engine::subsystems::renderer::Renderer;

/** 
 * Texture manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::manager::TextureManager final
{
	friend class TextureManager_TextureManaged;

private:
	Renderer* renderer {  };
	map<string, TextureManager_TextureManaged*> textures {  };

public:

	/** 
	 * Adds a texture to manager / open gl stack
	 * @param texture texture
	 * @returns gl texture id
	 */
	int32_t addTexture(Texture* texture);

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
