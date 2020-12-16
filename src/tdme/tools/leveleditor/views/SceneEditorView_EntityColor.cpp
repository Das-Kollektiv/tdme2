#include <tdme/tools/leveleditor/views/SceneEditorView_EntityColor.h>

#include <tdme/tools/leveleditor/views/LevelEditorView.h>

using tdme::tools::leveleditor::views::SceneEditorView_EntityColor;
using tdme::tools::leveleditor::views::LevelEditorView;

SceneEditorView_EntityColor::SceneEditorView_EntityColor(LevelEditorView* levelEditorView, float colorMulR, float colorMulG, float colorMulB, float colorAddR, float colorAddG, float colorAddB)
{
	this->levelEditorView = levelEditorView;
	this->colorMulR = colorMulR;
	this->colorMulG = colorMulG;
	this->colorMulB = colorMulB;
	this->colorAddR = colorAddR;
	this->colorAddG = colorAddG;
	this->colorAddB = colorAddB;
}
