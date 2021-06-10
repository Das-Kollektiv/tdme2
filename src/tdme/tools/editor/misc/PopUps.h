#pragma once

#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;

/**
 * Pop ups controller accessor class
 * @author andreas
 */
class tdme::tools::editor::misc::PopUps final
{
private:
	InfoDialogScreenController* infoDialogScreenController { nullptr };
	FileDialogScreenController* fileDialogScreenController { nullptr };
	ProgressBarScreenController* progressBarScreenController { nullptr };
	ColorPickerScreenController* colorPickerScreenController { nullptr };
	ContextMenuScreenController* contextMenuScreenController { nullptr };

public:
	/**
	 * Public constructor
	 */
	PopUps();

	/**
	 * Destructor
	 */
	~PopUps();

	/**
	 * @return file dialog screen controller
	 */
	inline FileDialogScreenController* getFileDialogScreenController() {
		return fileDialogScreenController;
	}

	/**
	 * @return info dialog screen controller
	 */
	inline InfoDialogScreenController* getInfoDialogScreenController() {
		return infoDialogScreenController;
	}

	/**
	 * @return progress bar screen controller
	 */
	inline ProgressBarScreenController* getProgressBarScreenController() {
		return progressBarScreenController;
	}

	/**
	 * @return color picker screen controller
	 */
	inline ColorPickerScreenController* getColorPickerScreenController() {
		return colorPickerScreenController;
	}

	/**
 	 * @return context menu screen controller
	 */
	inline ContextMenuScreenController* getContextMenuScreenController() {
		return contextMenuScreenController;
	}

	/**
	 * Init
	 */
	 void initialize();

	/**
	 * Dispose
	 */
	 void dispose();

};
