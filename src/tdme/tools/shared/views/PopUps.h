// Generated from /tdme/src/tdme/tools/shared/views/PopUps.java

#pragma once

#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;


struct default_init_tag;

/** 
 * Pop ups view
 * @author andreas
 */
class tdme::tools::shared::views::PopUps
	: public virtual Object
{

public:
	typedef Object super;

private:
	InfoDialogScreenController* infoDialogScreenController {  };
	FileDialogScreenController* fileDialogScreenController {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

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

	// Generated
	PopUps();
protected:
	PopUps(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
