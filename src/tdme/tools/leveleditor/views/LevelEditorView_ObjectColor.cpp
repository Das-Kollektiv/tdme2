#include <tdme/tools/leveleditor/views/LevelEditorView_ObjectColor.h>

#include <tdme/tools/leveleditor/views/LevelEditorView.h>

using tdme::tools::leveleditor::views::LevelEditorView_ObjectColor;
using tdme::tools::leveleditor::views::LevelEditorView;

LevelEditorView_ObjectColor::LevelEditorView_ObjectColor(LevelEditorView* levelEditorView, float colorMulR, float colorMulG, float colorMulB, float colorAddR, float colorAddG, float colorAddB)
{
	this->levelEditorView = levelEditorView;
	this->colorMulR = colorMulR;
	this->colorMulG = colorMulG;
	this->colorMulB = colorMulB;
	this->colorAddR = colorAddR;
	this->colorAddG = colorAddG;
	this->colorAddB = colorAddB;
}
