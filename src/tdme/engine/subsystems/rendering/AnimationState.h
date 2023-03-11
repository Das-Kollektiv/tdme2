#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>

using tdme::engine::model::AnimationSetup;

/**
 * Animation state entity
 * @author Andreas Drewke
 */
struct tdme::engine::subsystems::rendering::AnimationState final {
	AnimationState():
		setup(nullptr),
		endAtTime(-1LL),
		currentAtTime(-1LL),
		lastAtTime(-1LL),
		finished(true),
		time(-1LL),
		speed(1.0f)
	{}
	AnimationState(
		AnimationSetup* setup,
		int64_t endAtTime,
		int64_t currentAtTime,
		int64_t lastAtTime,
		bool finished,
		float time,
		float speed
	):
		setup(setup),
		endAtTime(endAtTime),
		currentAtTime(currentAtTime),
		lastAtTime(lastAtTime),
		finished(finished),
		time(time),
		speed(speed)
	{}
	AnimationSetup* setup;
	int64_t endAtTime;
	int64_t currentAtTime;
	int64_t lastAtTime;
	bool finished;
	float time;
	float speed;
};
