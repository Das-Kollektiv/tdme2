#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <agui/agui.h>

#include <agui/gui/textures/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>

using std::string;
using std::unordered_map;
using std::vector;

// namespaces
namespace agui {
namespace utilities {
	using ::agui::gui::textures::GUITexture;
}
}

/**
 * GUITexture atlas
 * @author Andreas Drewke
 */
class agui::utilities::TextureAtlas {
public:
	static constexpr bool VERBOSE { false };
	static constexpr int TEXTURE_IDX_NONE { -1 };

	/**
	 * GUITexture Atlas GUITexture
	 */
	struct AtlasTexture {
		enum Orientation { ORIENTATION_NONE, ORIENTATION_NORMAL, ORIENTATION_ROTATED };
		GUITexture* texture { nullptr };
		Orientation orientation { ORIENTATION_NONE };
		int textureIdx { -1 };
		int left { -1 };
		int top { -1 };
		int width { -1 };
		int height { -1 };
		int line { -1 };
	};

	// forbid class copy
	FORBID_CLASS_COPY(TextureAtlas)

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
	inline int getTextureIdx(GUITexture* texture) {
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
	int addTexture(GUITexture* texture);

	/**
	 * Remove texture
	 * @param texture texture
	 */
	void removeTexture(GUITexture* texture);

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
	inline GUITexture* getAtlasTexture() {
		return atlasTexture;
	}

private:
	bool requiresUpdate { false };
	string atlasTextureId;
	GUITexture* atlasTexture { nullptr };
	unordered_map<GUITexture*, int> textureReferenceCounter;
	unordered_map<GUITexture*, int> textureToAtlasTextureIdxMapping;
	unordered_map<int, AtlasTexture> atlasTextureIdxToAtlasTextureMapping;
	vector<int> freeTextureIds;
};
