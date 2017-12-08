#include <tdme/engine/model/AnimationSetup.h>

#include <tdme/engine/model/Model.h>

using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Model;

AnimationSetup::AnimationSetup(Model* model, const string& id, int32_t startFrame, int32_t endFrame, bool loop, const string& overlayFromGroupId)
{
	this->model = model;
	this->id = id;
	this->startFrame = startFrame;
	this->endFrame = endFrame;
	this->frames = (endFrame - startFrame) + 1;
	this->loop = loop;
	this->overlayFromGroupId = overlayFromGroupId;
}

Model* AnimationSetup::getModel()
{
	return model;
}

const string& AnimationSetup::getId()
{
	return id;
}

int32_t AnimationSetup::getStartFrame()
{
	return startFrame;
}

void AnimationSetup::setStartFrame(int32_t startFrame) {
	this->startFrame = startFrame;
	this->frames = (endFrame - startFrame) + 1;
	if (this->frames < 0) this->frames = 0;
}

int32_t AnimationSetup::getEndFrame()
{
	return endFrame;
}

void AnimationSetup::setEndFrame(int32_t endFrame) {
	this->endFrame = endFrame;
	this->frames = (endFrame - startFrame) + 1;
	if (this->frames < 0) this->frames = 0;
}

int32_t AnimationSetup::getFrames()
{
	return frames;
}

bool AnimationSetup::isLoop()
{
	return loop;
}

void AnimationSetup::setLoop(bool loop) {
	this->loop = loop;
}

const string& AnimationSetup::getOverlayFromGroupId()
{
	return overlayFromGroupId;
}

void AnimationSetup::setOverlayFromGroupId(const string& overlayFromGroupId) {
	this->overlayFromGroupId = overlayFromGroupId;
}

int64_t AnimationSetup::computeDuration()
{
	return computeDuration(startFrame, endFrame);
}

int64_t AnimationSetup::computeDuration(int32_t startFrame, int32_t endFrame)
{
	return static_cast< int64_t >((static_cast< float >((endFrame - startFrame + 1)) / static_cast< float >(model->getFPS()) * 1000.0f));
}
