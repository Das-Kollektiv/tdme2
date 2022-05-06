#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;

/**
 * Playable sound view interface, which represents a view that supports playing sounds additionally
 * @author Andreas Drewke
 */
struct tdme::tools::editor::views::PlayableSoundView
{
	/**
	 * Destructor
	 */
	virtual ~PlayableSoundView() {}

	/**
	 * Play sound
	 * @param soundId sound id
	 */
	virtual void playSound(const string& soundId) = 0;

	/**
	 * Stop sound
	 */
	virtual void stopSound() = 0;

};
