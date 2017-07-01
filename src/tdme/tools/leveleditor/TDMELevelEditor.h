// Generated from /tdme/src/tdme/tools/leveleditor/TDMELevelEditor.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/leveleditor/fwd-tdme.h>
#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Engine;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::leveleditor::views::EmptyView;
using tdme::tools::leveleditor::views::LevelEditorView;
using tdme::tools::leveleditor::views::ModelViewerView;
using tdme::tools::leveleditor::views::ParticleSystemView;
using tdme::tools::leveleditor::views::TriggerView;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;

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
 * TDME Level Editor
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::TDMELevelEditor final
	: public virtual Object
{

public:
	typedef Object super;

private:
	static String* VERSION;
	static TDMELevelEditor* instance;
	Engine* engine {  };
	View* view {  };
	bool quitRequested {  };
	LevelEditorLevel* level {  };
	LevelEditorEntityLibraryScreenController* levelEditorEntityLibraryScreenController {  };
	PopUps* popUps {  };
	LevelEditorView* levelEditorView {  };
	ModelViewerView* modelViewerView {  };
	TriggerView* triggerView {  };
	EmptyView* emptyView {  };
	ParticleSystemView* particleSystemView {  };

public:

	/** 
	 * @param args
	 */
	static void main(StringArray* args);
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

public:

	/** 
	 * @return level editor instance
	 */
	static TDMELevelEditor* getInstance();

	/** 
	 * @return level editor entity library screen controller
	 */
	LevelEditorEntityLibraryScreenController* getLevelEditorEntityLibraryScreenController();

	/** 
	 * @return entity library
	 */
	LevelEditorEntityLibrary* getEntityLibrary();

	/** 
	 * @return level
	 */
	LevelEditorLevel* getLevel();

	/** 
	 * Set up new view
	 * @param view
	 */
	void setView(View* view);

	/** 
	 * @return current view
	 */
	View* getView();

	/** 
	 * Request to exit the viewer
	 */
	void quit();

	/** 
	 * Renders the scene 
	 */
	void display();

	/** 
	 * Shutdown tdme viewer
	 */
	void dispose();

	/** 
	 * Initialize tdme level editor
	 */
	void initialize();

	/** 
	 * reshape tdme level editor
	 */
	void reshape(int32_t x, int32_t y, int32_t width, int32_t height);

	/** 
	 * Switch to level editor
	 */
	void switchToLevelEditor();

	/** 
	 * Switch to model viewer
	 */
	void switchToModelViewer();

	/** 
	 * Switch to trigger view
	 */
	void switchToTriggerView();

	/** 
	 * Switch to empty view
	 */
	void switchToEmptyView();

	/** 
	 * Switch to particle system view
	 */
	void switchToParticleSystemView();

	// Generated
	TDMELevelEditor();
protected:
	TDMELevelEditor(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
