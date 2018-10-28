#include <tdme/tools/shared/model/LevelEditorEntityModel.h>

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/model/LevelEditorEntityAudio.h>

using tdme::tools::shared::model::LevelEditorEntityModel;

using std::map;
using std::remove;
using std::string;
using std::vector;

using tdme::tools::shared::model::LevelEditorEntityAudio;

LevelEditorEntityModel::~LevelEditorEntityModel() {
	for (auto animationSound: animationSounds) {
		delete animationSound;
	}
}

LevelEditorEntityAudio* LevelEditorEntityModel::createAnimationSound(const string& animation) {
	auto it = animationSoundsById.find(animation);
	if (it != animationSoundsById.end()) return it->second;
	auto animationSound = new LevelEditorEntityAudio(entity, animation);
	animationSoundsById[animationSound->getAnimation()] = animationSound;
	animationSounds.push_back(animationSound);
	return animationSound;
}

LevelEditorEntityAudio* LevelEditorEntityModel::getAnimationSound(const string& animation) {
	auto it = animationSoundsById.find(animation);
	return it == animationSoundsById.end()?nullptr:it->second;
}

void LevelEditorEntityModel::removeAnimationSound(const string& animation) {
	auto it = animationSoundsById.find(animation);
	auto animationSound = it == animationSoundsById.end()?nullptr:it->second;
	if (animationSound == nullptr) return;
	animationSoundsById.erase(it);
	animationSounds.erase(remove(animationSounds.begin(), animationSounds.end(), animationSound), animationSounds.end());
}
