#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/TextureAtlas.h>

using std::string;
using std::to_string;

using tdme::engine::fileio::textures::PNGTextureWriter;
using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::utilities::Console;
using tdme::utilities::TextureAtlas;

int main(int argc, char** argv)
{
	TextureAtlas atlas("textureatlastest");
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_gridon.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_invisible.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_unlinked.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "terrain_smooth.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "material.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "delete.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_visible.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "select.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "slider_horizontal.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "mesh_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "sound.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "foliage_average.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "add.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "tdme_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "terrain_water.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "attention.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "scene_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "search.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "scene.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_snappingoff.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "radiobutton_selected.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "terrain_add.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "import.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "gui.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "arrow_down.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "arrow_right.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "material_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "bv.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "foliage_substract.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "reflection.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "stop.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "trigger.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "slider_vertical.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_gridoff.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "weblink.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "picker.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "reflection_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "bone_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "terrain_substract.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_unchecked.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_locked.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "folder_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "inputslider.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "play.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "knob_marker.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "empty.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "folder.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "mesh.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "foliage_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "info.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "sky_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "particle.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "terrain_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "gizmo.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "scale.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "rotate.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "gui_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_boneon.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_bvon.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "quit.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "radiobutton_unselected.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "translate.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "script.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "tdme_fontlogo_white.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "pause.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "arrow_left.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_unlocked.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "tdme.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "light_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "options.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "terrain_flatten.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "button.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "rendering.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "horizontal_align_right.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "question.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "light.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "horizontal_align_left.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "trigger_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "sky.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "font.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_snappingon.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "foliage.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "colorpicker.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_boneoff.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "vertical_align_center.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "vertical_align_top.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "script_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "arrow_up.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_linked.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "sound_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "pipette.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "new_folder.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "terrain_ramp.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "animation_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "font_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "progressbar.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "gradient.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "particle_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "drive.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "vertical_align_bottom.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "texture.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "new_data.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "knob.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "bv_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "save.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "empty_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "redo.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "horizontal_align_center.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_checked.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "cross.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "checkbox_bvoff.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "bone.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "substract.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "animation.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "terrain.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "foliage_add.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "undo.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "edit.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/images", "texture_big.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "terrain_brush.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "point.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "terrain_gras.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "random.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "sun.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "terrain_dirt.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "terrain_snow.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "terrain_stone.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "terrain_brush_soft.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "white_pixel.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "terrain_ramp.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "groundplate.png"));
	atlas.addTexture(TextureReader::read("./resources/engine/textures", "transparent_pixel.png"));
	atlas.update();

	// dump atlas textures
	for (auto i = 0;; i++) {
		auto atlasTexture = atlas.getAtlasTexture(i);
		if (atlasTexture == nullptr) break;
		Console::println(
			atlasTexture->texture->getId() + ": " +
			"left: " + to_string(atlasTexture->left) + ", " +
			"top: " + to_string(atlasTexture->left) + ", " +
			"width: " + to_string(atlasTexture->width) + ", " +
			"height: " + to_string(atlasTexture->height) + ", " +
			"orientation: " + (atlasTexture->orientation == TextureAtlas::AtlasTexture::ORIENTATION_NONE?"no orientation":(atlasTexture->orientation == TextureAtlas::AtlasTexture::ORIENTATION_ROTATED?"rotated":"standard rotation"))
		);
	}

	// write to PNG
	PNGTextureWriter::write(atlas.getAtlasTexture(), ".", "textureatlastest.png", false, false);
}
