// Generated from /tdme/src/tdme/engine/model/AnimationSetup.java
#include <tdme/engine/model/AnimationSetup.h>

#include <tdme/engine/model/Model.h>

using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Model;

AnimationSetup::AnimationSetup(Model* model, const wstring& id, int32_t startFrame, int32_t endFrame, bool loop, const wstring& overlayFromGroupId)
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

const wstring& AnimationSetup::getId()
{
	return id;
}

int32_t AnimationSetup::getStartFrame()
{
	return startFrame;
}

int32_t AnimationSetup::getEndFrame()
{
	return endFrame;
}

int32_t AnimationSetup::getFrames()
{
	return frames;
}

bool AnimationSetup::isLoop()
{
	return loop;
}

const wstring& AnimationSetup::getOverlayFromGroupId()
{
	return overlayFromGroupId;
}

int64_t AnimationSetup::computeDuration()
{
	return computeDuration(startFrame, endFrame);
}

int64_t AnimationSetup::computeDuration(int32_t startFrame, int32_t endFrame)
{
	return static_cast< int64_t >((static_cast< float >((endFrame - startFrame + 1)) / static_cast< float >(model->getFPS()) * 1000.0f));
}
