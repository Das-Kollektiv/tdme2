#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>

using std::string;

using tdme::engine::Texture;

/**
 * Prototype decal definition
 * @author Andreas Drewke
 */
class tdme::engine::prototype::PrototypeDecal final
{
private:
	string textureFileName;
	string transparencyTextureFileName;
	Texture* texture { nullptr };

public:
	/**
	 * Public constructor
	 */
	PrototypeDecal();

	/**
	 * Public destructor
	 */
	~PrototypeDecal();

	/**
	 * @return texture
	 */
	inline Texture* getTexture() {
		return texture;
	}

	/**
	 * @return texture file name
	 */
	inline const string& getTextureFileName() {
		return textureFileName;
	}

	/**
	 * @return transparency texture file name
	 */
	inline const string& getTransparencyTextureFileName() {
		return transparencyTextureFileName;
	}

	/**
	 * Set texture file name with optional transparency texture
	 * @param textureFileName texture file name
	 * @param transparencyTextureFileName transparency texture file name
	 */
	void setTextureFileName(const string& textureFileName, const string& transparencyTextureFileName = string());

};
