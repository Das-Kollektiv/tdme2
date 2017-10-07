#pragma once

#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/gui/effects/GUIEffect.h>

using tdme::gui::effects::GUIEffect;
using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIRenderer;


struct default_init_tag;

/** 
 * GUI color effect
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::effects::GUIColorEffect
	: public GUIEffect
{

public:
	typedef GUIEffect super;

private:
	GUIColor* colorAddStart {  };
	GUIColor* colorAddEnd {  };
	GUIColor* colorMulStart {  };
	GUIColor* colorMulEnd {  };
	GUIColor* colorAdd {  };
	GUIColor* colorMul {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

public:

	/** 
	 * @return color add start
	 */
	virtual GUIColor* getColorAddStart();

	/** 
	 * @return color add end
	 */
	virtual GUIColor* getColorAddEnd();

	/** 
	 * @return color mul start
	 */
	virtual GUIColor* getColorMulStart();

	/** 
	 * @return color mul end
	 */
	virtual GUIColor* getColorMulEnd();
	void update(GUIRenderer* guiRenderer) override;
	void apply(GUIRenderer* guiRenderer) override;

	GUIColorEffect();

protected:
	GUIColorEffect(const ::default_init_tag&);

private:
	void init();
};
