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
	 * @return file dialog screen controller
	 */
	inline FileDialogScreenController* getFileDialogScreenController() {
		return fileDialogScreenController.get();
	}

	/**
	 * @return input dialog screen controller
	 */
	inline InputDialogScreenController* getInputDialogScreenController() {
		return inputDialogScreenController.get();
	}

	/**
	 * @return info dialog screen controller
	 */
	inline InfoDialogScreenController* getInfoDialogScreenController() {
		return infoDialogScreenController.get();
	}

	/**
	 * @return progress bar screen controller
	 */
	inline ProgressBarScreenController* getProgressBarScreenController() {
		return progressBarScreenController.get();
	}

	/**
	 * @return color picker screen controller
	 */
	inline ColorPickerScreenController* getColorPickerScreenController() {
		return colorPickerScreenController.get();
	}

	/**
 	 * @return context menu screen controller
	 */
	inline ContextMenuScreenController* getContextMenuScreenController() {
		return contextMenuScreenController.get();
	}

	/**
 	 * @return about dialog screen controller
	 */
	inline AboutDialogScreenController* getAboutDialogScreenController() {
		return aboutDialogScreenController.get();
	}

	/**
	 * @return find replace dialog screen controller
	 */
	inline FindReplaceDialogScreenController* getFindReplaceDialogScreenController() {
		return findReplaceDialogScreenController.get();
	}

	/**
	 * @return import dialog screen controller
	 */
	inline ImportDialogScreenController* getImportDialogScreenController() {
		return importDialogScreenController.get();
	}

	/**
	 * @return selector dialog screen controller
	 */
	inline SelectorDialogScreenController* getSelectorDialogScreenController() {
		return selectorDialogScreenController.get();
	}

	/**
	 * @return tooltip screen controller
	 */
	inline TooltipScreenController* getTooltipScreenController() {
		return tooltipScreenController.get();
	}

	/**
	 * @return dragging screen controller
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
