
#pragma once

#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>

using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;

/**
 * Pop ups view
 * @author andreas
 */
class tdme::tools::shared::views::PopUps
{
private:
	InfoDialogScreenController* infoDialogScreenController {  };
	FileDialogScreenController* fileDialogScreenController {  };

public:

	/** 
	 * @return file dialog screen controller
	 */
	virtual FileDialogScreenController* getFileDialogScreenController();

	/** 
	 * @return info dialog scren controller
	 */
	virtual InfoDialogScreenController* getInfoDialogScreenController();

	/** 
	 * Init
	 */
	virtual void initialize();

	/** 
	 * Dispose
	 */
	virtual void dispose();

	/**
	 * Public constructor
	 */
	PopUps();

	/**
	 * Destructor
	 */
	virtual ~PopUps();
};
