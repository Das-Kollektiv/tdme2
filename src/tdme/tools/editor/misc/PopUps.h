#pragma once

#include <memory>

#include <tdme/tdme.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using std::unique_ptr;

using tdme::tools::editor::controllers::AboutDialogScreenController;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::DraggingScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::FindReplaceDialogScreenController;
using tdme::tools::editor::controllers::ImportDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::InputDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::tools::editor::controllers::SelectorDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;

/**
 * Pop ups controller accessor class
 * @author andreas
 */
class tdme::tools::editor::misc::PopUps final
{
private:
	unique_ptr<InfoDialogScreenController> infoDialogScreenController;
	unique_ptr<InputDialogScreenController> inputDialogScreenController;
	unique_ptr<FileDialogScreenController> fileDialogScreenController;
	unique_ptr<ProgressBarScreenController> progressBarScreenController;
	unique_ptr<ColorPickerScreenController> colorPickerScreenController;
	unique_ptr<ContextMenuScreenController> contextMenuScreenController;
	unique_ptr<AboutDialogScreenController> aboutDialogScreenController;
	unique_ptr<FindReplaceDialogScreenController> findReplaceDialogScreenController;
	unique_ptr<ImportDialogScreenController> importDialogScreenController;
	unique_ptr<SelectorDialogScreenController> selectorDialogScreenController;
	unique_ptr<TooltipScreenController> tooltipScreenController;
	unique_ptr<DraggingScreenController> draggingScreenController;

public:
	// forbid class copy
	FORBID_CLASS_COPY(PopUps)

	/**
	 * Public constructor
	 */
	PopUps();

	/**
	 * Destructor
	 */
	~PopUps();

	/**
	 * @returns file dialog screen controller
	 */
	inline FileDialogScreenController* getFileDialogScreenController() {
		return fileDialogScreenController.get();
	}

	/**
	 * @returns input dialog screen controller
	 */
	inline InputDialogScreenController* getInputDialogScreenController() {
		return inputDialogScreenController.get();
	}

	/**
	 * @returns info dialog screen controller
	 */
	inline InfoDialogScreenController* getInfoDialogScreenController() {
		return infoDialogScreenController.get();
	}

	/**
	 * @returns progress bar screen controller
	 */
	inline ProgressBarScreenController* getProgressBarScreenController() {
		return progressBarScreenController.get();
	}

	/**
	 * @returns color picker screen controller
	 */
	inline ColorPickerScreenController* getColorPickerScreenController() {
		return colorPickerScreenController.get();
	}

	/**
 	 * @returns context menu screen controller
	 */
	inline ContextMenuScreenController* getContextMenuScreenController() {
		return contextMenuScreenController.get();
	}

	/**
 	 * @returns about dialog screen controller
	 */
	inline AboutDialogScreenController* getAboutDialogScreenController() {
		return aboutDialogScreenController.get();
	}

	/**
	 * @returns find replace dialog screen controller
	 */
	inline FindReplaceDialogScreenController* getFindReplaceDialogScreenController() {
		return findReplaceDialogScreenController.get();
	}

	/**
	 * @returns import dialog screen controller
	 */
	inline ImportDialogScreenController* getImportDialogScreenController() {
		return importDialogScreenController.get();
	}

	/**
	 * @returns selector dialog screen controller
	 */
	inline SelectorDialogScreenController* getSelectorDialogScreenController() {
		return selectorDialogScreenController.get();
	}

	/**
	 * @returns tooltip screen controller
	 */
	inline TooltipScreenController* getTooltipScreenController() {
		return tooltipScreenController.get();
	}

	/**
	 * @returns dragging screen controller
	 */
	inline DraggingScreenController* getDraggingScreenController() {
		return draggingScreenController.get();
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
