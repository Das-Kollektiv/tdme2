#pragma once

#include <string>

#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;

/**
 * Playable sound view interface, which represents a view that supports playing sounds additionally
 * @author Andreas Drewke
 * @version $Id$
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

};
