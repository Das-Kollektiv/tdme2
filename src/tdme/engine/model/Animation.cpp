#include <tdme/engine/model/Animation.h>

#include <tdme/math/Matrix4x4.h>

using tdme::engine::model::Animation;
using tdme::math::Matrix4x4;

Animation::Animation(int32_t frames) 
{
	this->frames = frames;
	transformationsMatrices.resize(frames);
	for (auto i = 0; i < frames; i++) {
		transformationsMatrices[i].identity();
	}
}

int32_t Animation::getFrames()
{
	return frames;
}

vector<Matrix4x4>& Animation::getTransformationsMatrices()
{
	return transformationsMatrices;
}
