// Generated from /tdme/src/tdme/tools/leveleditor/views/LevelEditorView.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/engine/EntityPickingFilter.h>

using java::lang::Object;
using tdme::engine::EntityPickingFilter;
using tdme::engine::Entity;
using tdme::tools::leveleditor::views::LevelEditorView_ObjectColor;
using tdme::tools::leveleditor::views::LevelEditorView;


struct default_init_tag;
class tdme::tools::leveleditor::views::LevelEditorView_LevelEditorView_1
	: public virtual Object
	, public virtual EntityPickingFilter
{

public:
	typedef Object super;
	bool filterEntity(Entity* entity) override;

	// Generated
	LevelEditorView_LevelEditorView_1(LevelEditorView *LevelEditorView_this);
	static ::java::lang::Class *class_();
	LevelEditorView *LevelEditorView_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class LevelEditorView;
	friend class LevelEditorView_ObjectColor;
};
