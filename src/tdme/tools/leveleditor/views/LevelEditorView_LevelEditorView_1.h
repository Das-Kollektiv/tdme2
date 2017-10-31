
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/engine/EntityPickingFilter.h>

using tdme::engine::EntityPickingFilter;
using tdme::engine::Entity;
using tdme::tools::leveleditor::views::LevelEditorView_ObjectColor;
using tdme::tools::leveleditor::views::LevelEditorView;

class tdme::tools::leveleditor::views::LevelEditorView_LevelEditorView_1
	: public virtual EntityPickingFilter
{
	friend class LevelEditorView;
	friend class LevelEditorView_ObjectColor;

public:
	bool filterEntity(Entity* entity) override;

	// Generated
	LevelEditorView_LevelEditorView_1(LevelEditorView* levelEditorView);

private:
	LevelEditorView* levelEditorView;
};
