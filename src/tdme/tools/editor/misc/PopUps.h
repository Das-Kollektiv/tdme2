#pragma once

#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;

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
	 FileDialogScreenController* getFileDialogScreenController();

	/**
	 * @return info dialog screen controller
	 */
	 InfoDialogScreenController* getInfoDialogScreenController();

	/**
	 * @return progress bar screen controller
	 */
	 ProgressBarScreenController* getProgressBarScreenController();

	/**
	 * Init
	 */
	 void initialize();

	/**
	 * Dispose
	 */
	 void dispose();

};
