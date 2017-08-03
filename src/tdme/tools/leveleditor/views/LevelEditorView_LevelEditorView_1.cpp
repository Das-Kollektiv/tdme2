// Generated from /tdme/src/tdme/tools/leveleditor/views/LevelEditorView.java
#include <tdme/tools/leveleditor/views/LevelEditorView_LevelEditorView_1.h>

#include <java/lang/String.h>
#include <tdme/engine/Entity.h>
#include <tdme/tools/leveleditor/views/LevelEditorView.h>
#include <tdme/utils/StringUtils.h>

using tdme::tools::leveleditor::views::LevelEditorView_LevelEditorView_1;
using java::lang::String;
using tdme::engine::Entity;
using tdme::tools::leveleditor::views::LevelEditorView;
using tdme::utils::StringUtils;

LevelEditorView_LevelEditorView_1::LevelEditorView_LevelEditorView_1(LevelEditorView *LevelEditorView_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, LevelEditorView_this(LevelEditorView_this)
{
	clinit();
	ctor();
}

bool LevelEditorView_LevelEditorView_1::filterEntity(Entity* entity)
{
	return StringUtils::startsWith(entity->getId(), L"leveleditor.ground@") == false;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorView_LevelEditorView_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* LevelEditorView_LevelEditorView_1::getClass0()
{
	return class_();
}

