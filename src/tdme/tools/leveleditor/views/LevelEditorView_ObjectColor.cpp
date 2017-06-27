// Generated from /tdme/src/tdme/tools/leveleditor/views/LevelEditorView.java
#include <tdme/tools/leveleditor/views/LevelEditorView_ObjectColor.h>

#include <tdme/tools/leveleditor/views/LevelEditorView.h>

using tdme::tools::leveleditor::views::LevelEditorView_ObjectColor;
using tdme::tools::leveleditor::views::LevelEditorView;

LevelEditorView_ObjectColor::LevelEditorView_ObjectColor(LevelEditorView *LevelEditorView_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, LevelEditorView_this(LevelEditorView_this)
{
	clinit();
}

LevelEditorView_ObjectColor::LevelEditorView_ObjectColor(LevelEditorView *LevelEditorView_this, float colorMulR, float colorMulG, float colorMulB, float colorAddR, float colorAddG, float colorAddB) 
	: LevelEditorView_ObjectColor(LevelEditorView_this, *static_cast< ::default_init_tag* >(0))
{
	ctor(colorMulR,colorMulG,colorMulB,colorAddR,colorAddG,colorAddB);
}

void LevelEditorView_ObjectColor::init()
{
	colorMulR = 1.0f;
	colorMulG = 1.0f;
	colorMulB = 1.0f;
	colorAddR = 0.0f;
	colorAddG = 0.0f;
	colorAddB = 0.0f;
}

void LevelEditorView_ObjectColor::ctor(float colorMulR, float colorMulG, float colorMulB, float colorAddR, float colorAddG, float colorAddB)
{
	super::ctor();
	init();
	this->colorMulR = colorMulR;
	this->colorMulG = colorMulG;
	this->colorMulB = colorMulB;
	this->colorAddR = colorAddR;
	this->colorAddG = colorAddG;
	this->colorAddB = colorAddB;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorView_ObjectColor::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.leveleditor.views.LevelEditorView.ObjectColor", 56);
    return c;
}

java::lang::Class* LevelEditorView_ObjectColor::getClass0()
{
	return class_();
}

