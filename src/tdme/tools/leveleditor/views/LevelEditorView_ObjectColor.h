#pragma once

#include <tdme/tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>

using tdme::tools::leveleditor::views::LevelEditorView;

/** 
 * Object Color
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::views::LevelEditorView_ObjectColor
{
	friend class LevelEditorView;
	friend class LevelEditorView_LevelEditorView_1;

private:
	LevelEditorView* levelEditorView;

	float colorMulR {  };
	float colorMulG {  };
	float colorMulB {  };
	float colorAddR {  };
	float colorAddG {  };
	float colorAddB {  };

public:
	/**
	 * Public constructor
	 * @param level editor view
	 * @param colorMulR
	 * @param colorMulG
	 * @param colorMulB
	 * @param colorAddR
	 * @param colorAddG
	 * @param colorAddB
	 */
	LevelEditorView_ObjectColor(LevelEditorView* levelEditorView, float colorMulR, float colorMulG, float colorMulB, float colorAddR, float colorAddG, float colorAddB);
};
