#pragma once

#include <array>
#include <vector>

#include <tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>

using std::array;
using std::vector;

using tdme::utils::FloatBuffer;
using tdme::utils::ShortBuffer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIScreenNode;


struct default_init_tag;

/** 
 * GUI
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::renderer::GUIRenderer final
{

private:
	static constexpr int32_t QUAD_COUNT { 1024 };
	static constexpr float SCREEN_LEFT { -1.0f };
	static constexpr float SCREEN_TOP { 1.0f };
	static constexpr float SCREEN_RIGHT { 1.0f };
	static constexpr float SCREEN_BOTTOM { -1.0f };

public: /* protected */
	GUI* gui {  };

private:
	GLRenderer* renderer {  };
	vector<int32_t>* vboIds {  };
	int32_t quadCount {  };
	ShortBuffer* sbIndices {  };
	FloatBuffer* fbVertices {  };
	FloatBuffer* fbColors {  };
	FloatBuffer* fbTextureCoordinates {  };
	float renderAreaLeft {  };
	float renderAreaTop {  };
	float renderAreaRight {  };
	float renderAreaBottom {  };
	float renderOffsetX {  };
	float renderOffsetY {  };
	GUIScreenNode* screenNode {  };
	array<float, 4> fontColor {  };
	array<float, 4> effectColorMul {  };
	array<float, 4> effectColorAdd {  };
	array<float, 4> guiEffectColorMul {  };
	array<float, 4> guiEffectColorAdd {  };
	array<float, 4> effectColorMulFinal {  };
	array<float, 4> effectColorAddFinal {  };
	float guiEffectOffsetX {  };
	float guiEffectOffsetY {  };

protected:

	/** 
	 * Constructor
	 * @param renderer
	 */
	void ctor(GLRenderer* renderer);

public:

	/** 
	 * Set GUI
	 * @param gui
	 */
	void setGUI(GUI* gui);

	/** 
	 * @return GUI
	 */
	GUI* getGUI();

	/** 
	 * Init
	 */
	void initialize();

	/** 
	 * Dispose
	 */
	void dispose();

	/** 
	 * Init rendering
	 */
	void initRendering();

	/** 
	 * Done rendering
	 */
	void doneRendering();

	/** 
	 * Init screen
	 * @param screen node
	 */
	void initScreen(GUIScreenNode* screenNode);

	/** 
	 * Done screen
	 */
	void doneScreen();

	/** 
	 * Set effect color mul
	 * @param color
	 */
	void setFontColor(GUIColor* color);

	/** 
	 * Set effect color mul
	 * @param color
	 */
	void setEffectColorMul(GUIColor* color);

	/** 
	 * Set effect color add
	 * @param color
	 */
	void setEffectColorAdd(GUIColor* color);

	/** 
	 * Set GUI effect color mul
	 * @param color
	 */
	void setGUIEffectColorMul(GUIColor* color);

	/** 
	 * Set GUI effect color add
	 * @param color
	 */
	void setGUIEffectColorAdd(GUIColor* color);

	/** 
	 * @return GUI effect offset X
	 */
	float getGuiEffectOffsetX();

	/** 
	 * Set GUI effect offset X
	 * @param gui effect offset X
	 */
	void setGUIEffectOffsetX(float guiEffectOffsetX);

	/** 
	 * @return GUI effect offset Y
	 */
	float getGuiEffectOffsetY();

	/** 
	 * Set GUI effect offset Y
	 * @param GUI effect offset Y
	 */
	void setGUIEffectOffsetY(float guiEffectOffsetY);

	/** 
	 * @return render area left
	 */
	float getRenderAreaLeft();

	/** 
	 * Set up render area left
	 * @param render area left
	 */
	void setRenderAreaLeft(float renderAreaLeft);

	/** 
	 * Set sub render area left
	 * @param render area left
	 */
	void setSubRenderAreaLeft(float renderAreaLeft);

	/** 
	 * @return render area top
	 */
	float getRenderAreaTop();

	/** 
	 * Set up render area top
	 * @param render area top
	 */
	void setRenderAreaTop(float renderAreaTop);

	/** 
	 * Set sub render area top
	 * @param render area top
	 */
	void setSubRenderAreaTop(float renderAreaTop);

	/** 
	 * @return render area right
	 */
	float getRenderAreaRight();

	/** 
	 * Set up render area right
	 * @param render area right
	 */
	void setRenderAreaRight(float renderAreaRight);

	/** 
	 * Set sub render area right
	 * @param render area right
	 */
	void setSubRenderAreaRight(float renderAreaRight);

	/** 
	 * @return render area bottom
	 */
	float getRenderAreaBottom();

	/** 
	 * Set up render area bottom
	 * @param render area bottom
	 */
	void setRenderAreaBottom(float renderAreaBottom);

	/** 
	 * Set sub render area bottom
	 * @param render area bottom
	 */
	void setSubRenderAreaBottom(float renderAreaBottom);

	/** 
	 * @return render offset x
	 */
	float getRenderOffsetX();

	/** 
	 * Set render offset x
	 * @param render offset x
	 */
	void setRenderOffsetX(float renderOffsetX);

	/** 
	 * @return render offset y
	 */
	float getRenderOffsetY();

	/** 
	 * Set render offset y
	 * @param render offset y
	 */
	void setRenderOffsetY(float renderOffsetY);

	/** 
	 * Add quad
	 * Note: quad vertices order
	 * 1    2
	 * +----+
	 * |    |
	 * |    |
	 * +----+
	 * 4    3
	 * @param x 1
	 * @param y 1
	 * @param color red 1
	 * @param color green 1
	 * @param color blue 1
	 * @param color alpha 1
	 * @param texture u 1
	 * @param texture v 1
	 * @param x 2
	 * @param y 2
	 * @param color red 2
	 * @param color green 2
	 * @param color blue 2
	 * @param color alpha 2
	 * @param texture u 2
	 * @param texture v 2
	 * @param x 3
	 * @param y 3
	 * @param color red 3
	 * @param color green 3
	 * @param color blue 3
	 * @param color alpha 3
	 * @param texture u 3
	 * @param texture v 3
	 * @param x 4
	 * @param y 4
	 * @param color red 4
	 * @param color green 4
	 * @param color blue 4
	 * @param color alpha 4
	 * @param texture u 4
	 * @param texture v 4
	 */
	void addQuad(float x1, float y1, float colorR1, float colorG1, float colorB1, float colorA1, float tu1, float tv1, float x2, float y2, float colorR2, float colorG2, float colorB2, float colorA2, float tu2, float tv2, float x3, float y3, float colorR3, float colorG3, float colorB3, float colorA3, float tu3, float tv3, float x4, float y4, float colorR4, float colorG4, float colorB4, float colorA4, float tu4, float tv4);

	/** 
	 * Bind texture
	 * @param texture
	 */
	void bindTexture(int32_t textureId);

	/** 
	 * Render 
	 */
	void render();

	GUIRenderer(GLRenderer* renderer);

protected:
	GUIRenderer(const ::default_init_tag&);

private:
	void init();
};
