#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::Texture;

/**
 * Texture atlas
 * @author Andreas Drewke
 */
class tdme::utilities::TextureAtlas {
public:
	static constexpr bool VERBOSE { false };
	static constexpr int TEXTURE_IDX_NONE { -1 };

	/**
	 * Texture Atlas Texture
	 */
	struct AtlasTexture {
		enum Orientation { ORIENTATION_NONE, ORIENTATION_NORMAL, ORIENTATION_ROTATED };
		Texture* texture { nullptr };
		Orientation orientation { ORIENTATION_NONE };
		int textureIdx { -1 };
		int left { -1 };
		int top { -1 };
		int width { -1 };
		int height { -1 };
		int line { -1 };
	};

	// forbid class copy
	CLASS_FORBID_COPY(TextureAtlas)

	/**
	 * Public constructor
	 * @param id texture id
	 */
	TextureAtlas(const string& id);

	/**
	 * Public destructor
	 */
	~TextureAtlas();

	/**
	 * Returns specific atlas texture index within atlas
	 * @param texture texture
	 * @return atlas texture id
	 */
	inline int getTextureIdx(Texture* texture) {
		auto it = textureToAtlasTextureIdxMapping.find(texture);
		if (it == textureToAtlasTextureIdxMapping.end()) {
			return TEXTURE_IDX_NONE;
		}
		return it->second;
	}

	/**
	 * Returns specific atlas texture information within atlas
	 * @param textureIdx texture index
	 * @return atlas texture information
	 */
	inline const AtlasTexture* getAtlasTexture(int textureIdx) {
		auto it = atlasTextureIdxToAtlasTextureMapping.find(textureIdx);
		if (it == atlasTextureIdxToAtlasTextureMapping.end()) {
			return nullptr;
		}
		return &it->second;
	}

	/**
	 * Add texture
	 * @param texture texture
	 * @return atlas texture id
	 */
	int addTexture(Texture* texture);

	/**
	 * Remove texture
	 * @param texture texture
	 */
	void removeTexture(Texture* texture);

	/**
	 * Update texture atlas
	 */
	void update();

	/**
	 * @return is requiring update
	 */
	inline bool isRequiringUpdate() {
		return requiresUpdate;
	}

	/**
	 * @return atlas texture
	 */
	inline Texture* getAtlasTexture() {
		return atlasTexture;
	}

private:
	bool requiresUpdate { false };
	string atlasTextureId;
	Texture* atlasTexture { nullptr };
	unordered_map<Texture*, int> textureReferenceCounter;
	unordered_map<Texture*, int> textureToAtlasTextureIdxMapping;
	unordered_map<int, AtlasTexture> atlasTextureIdxToAtlasTextureMapping;
	vector<int> freeTextureIds;

	/**
	 * Sort atlas textures by height
	 * @param atlasTexture1 atlas texture 1
	 * @param atlasTexture2 atlas texture 2
	 */
	inline static bool sortAtlasTexturesByHeight(const AtlasTexture& atlasTexture1, const AtlasTexture& atlasTexture2) {
		return atlasTexture1.height > atlasTexture2.height;
	}

};
