// Generated from /tdme/src/tdme/engine/model/AnimationSetup.java
#include <tdme/engine/model/AnimationSetup.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Model.h>

using tdme::engine::model::AnimationSetup;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Model;

AnimationSetup::AnimationSetup(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

AnimationSetup::AnimationSetup(Model* model, String* id, int32_t startFrame, int32_t endFrame, bool loop, String* overlayFromGroupId) 
	: AnimationSetup(*static_cast< ::default_init_tag* >(0))
{
	ctor(model,id,startFrame,endFrame,loop,overlayFromGroupId);
}

void AnimationSetup::ctor(Model* model, String* id, int32_t startFrame, int32_t endFrame, bool loop, String* overlayFromGroupId)
{
	super::ctor();
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

String* AnimationSetup::getId()
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

String* AnimationSetup::getOverlayFromGroupId()
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

String* AnimationSetup::toString()
{
	return ::java::lang::StringBuilder().append(u"AnimationSetup [id="_j)->append(id)
		->append(u", startFrame="_j)
		->append(startFrame)
		->append(u", endFrame="_j)
		->append(endFrame)
		->append(u", frames="_j)
		->append(frames)
		->append(u", loop="_j)
		->append(loop)
		->append(u", overlayFromGroupId="_j)
		->append(overlayFromGroupId)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AnimationSetup::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.AnimationSetup", 32);
    return c;
}

java::lang::Class* AnimationSetup::getClass0()
{
	return class_();
}

