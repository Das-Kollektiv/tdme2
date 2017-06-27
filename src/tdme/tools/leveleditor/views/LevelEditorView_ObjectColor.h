// Generated from /tdme/src/tdme/tools/leveleditor/views/LevelEditorView.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::tools::leveleditor::views::LevelEditorView;


struct default_init_tag;

/** 
 * Object Color
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::views::LevelEditorView_ObjectColor
	: public virtual Object
{

public:
	typedef Object super;
protected:

	/** 
	 * Public constructor
	 * @param name
	 * @param colorMulR
	 * @param colorMulG
	 * @param colorMulB
	 * @param colorAddR
	 * @param colorAddG
	 * @param colorAddB
	 */
	void ctor(float colorMulR, float colorMulG, float colorMulB, float colorAddR, float colorAddG, float colorAddB);

public: /* protected */
	float colorMulR {  };
	float colorMulG {  };
	float colorMulB {  };
	float colorAddR {  };
	float colorAddG {  };
	float colorAddB {  };

	// Generated

public:
	LevelEditorView_ObjectColor(LevelEditorView *LevelEditorView_this, float colorMulR, float colorMulG, float colorMulB, float colorAddR, float colorAddG, float colorAddB);
protected:
	LevelEditorView_ObjectColor(LevelEditorView *LevelEditorView_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	LevelEditorView *LevelEditorView_this;
	virtual ::java::lang::Class* getClass0();
	friend class LevelEditorView;
	friend class LevelEditorView_LevelEditorView_1;
};
