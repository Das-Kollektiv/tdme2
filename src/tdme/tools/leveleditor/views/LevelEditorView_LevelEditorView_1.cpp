#include <tdme/tools/leveleditor/views/LevelEditorView_LevelEditorView_1.h>

#include <tdme/engine/Entity.h>
#include <tdme/tools/leveleditor/views/LevelEditorView.h>
#include <tdme/utils/StringUtils.h>

using tdme::tools::leveleditor::views::LevelEditorView_LevelEditorView_1;
using tdme::engine::Entity;
using tdme::tools::leveleditor::views::LevelEditorView;
using tdme::utils::StringUtils;

LevelEditorView_LevelEditorView_1::LevelEditorView_LevelEditorView_1(LevelEditorView* levelEditorView)
	: levelEditorView(levelEditorView)
{
}

bool LevelEditorView_LevelEditorView_1::filterEntity(Entity* entity)
{
	return StringUtils::startsWith(entity->getId(), "leveleditor.ground@") == false;
}
