// Generated from /tdme/src/tdme/tools/shared/controller/FileDialogScreenController.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/controller/ScreenController.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>

using tdme::tools::shared::controller::ScreenController;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIChangeListener;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::utils::MutableString;
using java::lang::Object;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

struct default_init_tag;

/** 
 * File dialog screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::FileDialogScreenController
	: public ScreenController
	, public virtual GUIActionListener
	, public virtual GUIChangeListener
{

public:
	typedef ScreenController super;

private:
	GUIScreenNode* screenNode {  };
	String* cwd {  };
	StringArray* extensions {  };
	String* captionText {  };
	GUITextNode* caption {  };
	GUIElementNode* fileName {  };
	GUIElementNode* files {  };
	MutableString* value {  };
	Action* applyAction {  };
protected:

	/** 
	 * Public constructor
	 * @param model library controller
	 */
	void ctor();

public:
	GUIScreenNode* getScreenNode() override;

	/** 
	 * @return path name
	 */
	virtual String* getPathName();

	/** 
	 * @return file name
	 */
	virtual String* getFileName();
	void initialize() override;
	void dispose() override;

private:

	/** 
	 * Set up file dialog list box
	 */
	void setupFileDialogListBox();

public:

	/** 
	 * Shows the file dialog pop up
	 * @param caption text
	 * @param extensions
	 * @param apply action
	 * @throws IOException 
	 */
	virtual void show(String* cwd, String* captionText, StringArray* extensions, String* fileName, Action* applyAction);

	/** 
	 * Abort the file dialog pop up
	 */
	virtual void close();

	/** 
	 * On value changed
	 */
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	// Generated
	FileDialogScreenController();
protected:
	FileDialogScreenController(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class FileDialogScreenController_setupFileDialogListBox_1;
};
